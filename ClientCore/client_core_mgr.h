/*##############################################################################
 * 文件：client_core_mgr.h
 * 描述：客户端处理的对外接口层，隐藏了内部实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
 * 描述：上层应用只看到这个类，能够处理各种业务消息，并维护业务数据结构。其本身
 *       是一个下行边缘消息处理器，所有下行消息都会在此对象内部进行线程切换。 
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