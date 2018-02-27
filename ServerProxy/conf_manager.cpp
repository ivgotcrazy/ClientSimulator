/*##############################################################################
 * �ļ���conf_manager.cpp
 * ������ConfManagerʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"

#include <atlconv.h>

#include "conf_manager.h"
#include "client_state_machine.h"
#include "xmlprotocolparser.h"
#include "conf_msg_processor.h"
#include "UpdateMgrProtocol.h"
#include "FrontProtocol.h"

using namespace meetingcore;

#define THREAD_MSG_START_VER_CHECK	WM_USER+201

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ����[in] state_machine ״̬��
 * ����ֵ����
------------------------------------------------------------------------------*/
ConfManager::ConfManager(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
{
}

/*------------------------------------------------------------------------------
 * ��  ������ʼ��
 * ��  ������
 * ����ֵ���ɹ�/ʧ��
------------------------------------------------------------------------------*/
bool ConfManager::Init()
{
	// ��Ϣ�߳�ת��ע��
	SetMsgConverter(m_state_machine->GetMsgConverter());

	if (!m_msg_sender.Init(m_state_machine->GetSessionManager()))
	{
		LOG(_T("Failed to init msg sender.\n"));
		return false;
	}

	//-- UpdateChecker
	
	m_update_checker.reset(new UpdateChecker(m_state_machine));
	if (!m_update_checker->Init())
	{
		LOG(_T("Failed to init UpdateChecker.\n"));
		return false;
	}

	// ConfManager<-UpdateChecker
	m_update_checker->SetUpMsgProcSuccessor(shared_from_this());

	//-- FrontConnector

	m_front_connector.reset(new FrontConnector(m_state_machine));
	if (!m_front_connector->Init())
	{
		LOG(_T("Failed to init FrontConnector.\n"));
		return false;
	}

	// ConfManager<-FrontConnector
	m_front_connector->SetUpMsgProcSuccessor(shared_from_this());

	//-- ConfConnector

	m_conf_connector.reset(new ConfConnector(m_state_machine));
	if (!m_conf_connector->Init())
	{
		LOG(_T("Failed to init ConfConnector.\n"));
		return false;
	}
	// ConfManager<-ConfConnector
	m_conf_connector->SetUpMsgProcSuccessor(shared_from_this());

	// ������Ϣ·��
	SET_DOWN_MSG_ROUTE(DOWN_MSG_START_UPDATE_CHECK,		m_update_checker);

	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN,					m_front_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_GET_ROOM_LIST,			m_front_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_FRONT_ROOM,		m_front_connector);

	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_ROOM,				m_conf_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_INIT_COMPLETE,			m_conf_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_BROADCAST_USER_AV_INFO, m_conf_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGOUT_ROOM,			m_conf_connector);

	// ������Ϣע��
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_FRONT_ROOM_REP, ConfManager::OnLoginFrontRoomRep);
	
	// ������Ϣӳ��
	DOWN_MSG_POST_MAP(DOWN_MSG_INIT_COMPLETE, ConfManager::OnInitCompleteMsg);

	return true;
}

/*------------------------------------------------------------------------------
 * ��  ������¼ǰ�÷�����Ӧ��Ϣ����
 * ��  ����[in] msg_data ��Ϣ����
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ConfManager::OnLoginFrontRoomRep(const MsgData& msg_data)
{
	LoginFrontRoomRepMsgSP rep_msg = 
		std::static_pointer_cast<LoginFrontRoomRepMsg>(msg_data);

	m_conf_connector->SetRoomServiceList(rep_msg->srv_list);

	return true;
}

/*------------------------------------------------------------------------------
 * ��  �������ͳ�ʼ���ɹ���Ϣ����
 * ��  ����[in] msg_data ��Ϣ����
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ConfManager::OnInitCompleteMsg(const MsgData& msg_data)
{
	// ��������Һ�Ϊ�˽�Լ�߳����ģ��������ͷŵ�
	// �����������Ļ���Ҫ����ֹͣ���ֿ�ʼ��¼�����

	RESET_DOWN_MSG_ROUTE(DOWN_MSG_START_UPDATE_CHECK);
	m_update_checker.reset();

	RESET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN);
	RESET_DOWN_MSG_ROUTE(DOWN_MSG_GET_ROOM_LIST);
	RESET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_FRONT_ROOM);
	m_front_connector.reset();

	return true;
}
