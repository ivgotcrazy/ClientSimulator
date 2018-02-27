/*##############################################################################
 * �ļ���client_core_mgr.h
 * �������ͻ��˴���Ķ���ӿڲ㣬�������ڲ�ʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/

#pragma once

#include <vector>
#include <list>
#include "framework.h"
#include "client_public.h"
#include "client_core_define.h"
#include "meeting_core_define.h"
#include "down_board_msg_processor.h"
#include "room_data_mgr.h"

using namespace meetingcore;

namespace clientcore
{

/*==============================================================================
 * �������ϲ�Ӧ��ֻ��������࣬�ܹ��������ҵ����Ϣ����ά��ҵ�����ݽṹ���䱾��
 *       ��һ�����б�Ե��Ϣ������������������Ϣ�����ڴ˶����ڲ������߳��л��� 
==============================================================================*/
class ClientCoreMgr 
	: public DownBoardMsgProcessor
	, public std::enable_shared_from_this<ClientCoreMgr>
{
public:
	ClientCoreMgr(ClientBaseComponents* base_objs, const ClientConfig& client_config);

	bool Start(RoomLoginType login_type);
	void Stop();

private:
	bool Init();

	bool OnLoginReq(const MsgData& msg_data);
	bool OnStateStart(const MsgData& msg_data);
	bool OnLoginRep(const MsgData& msg_data);
	bool OnLoginFrontRoomRep(const MsgData& msg_data);
	bool OnLoginRoomRep(const MsgData& msg_data);
	bool OnRefreshAvDevices(const MsgData& msg_data);
	bool OnUserAvInfoNotify(const MsgData& msg_data);
	bool OnUserStateChanged(const MsgData& msg_data);
	bool OnLogoutRoom(const MsgData& msg_data);
	bool OnUserEnterNotify(const MsgData& msg_data);

	void SendLoginAvRoomMsg();
	void SendLoginRoomReqMsg();
	void SendUserAvInfoMsg();

private:
	ClientConfig			m_client_config;
	ClientBaseComponents*	m_base_objs;
	ThreadMsgConverterSP	m_msg_converter;
	ClientStateMachineSP	m_state_machine;

	tstring		m_user_name;
	std::string	m_local_node_id;
	RoomDataMgr	m_room_data_mgr;
};

}