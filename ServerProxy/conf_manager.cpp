/*##############################################################################
 * 文件：conf_manager.cpp
 * 描述：ConfManager实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
 * 描  述：构造函数
 * 参  数：[in] state_machine 状态机
 * 返回值：无
------------------------------------------------------------------------------*/
ConfManager::ConfManager(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
{
}

/*------------------------------------------------------------------------------
 * 描  述：初始胡
 * 参  数：无
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfManager::Init()
{
	// 消息线程转换注册
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

	// 下行消息路由
	SET_DOWN_MSG_ROUTE(DOWN_MSG_START_UPDATE_CHECK,		m_update_checker);

	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN,					m_front_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_GET_ROOM_LIST,			m_front_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_FRONT_ROOM,		m_front_connector);

	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_ROOM,				m_conf_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_INIT_COMPLETE,			m_conf_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_BROADCAST_USER_AV_INFO, m_conf_connector);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGOUT_ROOM,			m_conf_connector);

	// 上行消息注册
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_FRONT_ROOM_REP, ConfManager::OnLoginFrontRoomRep);
	
	// 下行消息映射
	DOWN_MSG_POST_MAP(DOWN_MSG_INIT_COMPLETE, ConfManager::OnInitCompleteMsg);

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：登录前置房间响应消息处理
 * 参  数：[in] msg_data 消息数据
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfManager::OnLoginFrontRoomRep(const MsgData& msg_data)
{
	LoginFrontRoomRepMsgSP rep_msg = 
		std::static_pointer_cast<LoginFrontRoomRepMsg>(msg_data);

	m_conf_connector->SetRoomServiceList(rep_msg->srv_list);

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：发送初始化成功消息处理
 * 参  数：[in] msg_data 消息数据
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfManager::OnInitCompleteMsg(const MsgData& msg_data)
{
	// 进入会议室后，为了节约线程消耗，将对象释放掉
	// 不过，这样的话，要考虑停止后又开始登录的情况

	RESET_DOWN_MSG_ROUTE(DOWN_MSG_START_UPDATE_CHECK);
	m_update_checker.reset();

	RESET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN);
	RESET_DOWN_MSG_ROUTE(DOWN_MSG_GET_ROOM_LIST);
	RESET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_FRONT_ROOM);
	m_front_connector.reset();

	return true;
}
