#include "stdafx.h"
#include "virtual_client.h"

VirtualClient::VirtualClient(const ClientConfig& client_cfg, 
	const ClientBaseComponents& base_comps)
	: m_client_cfg(client_cfg)
	, m_base_comps(base_comps)
{

}

bool VirtualClient::Init()
{
	m_client_mgr.reset(new ClientCoreMgr(&m_base_comps, m_client_cfg));

	// Down msg flow: ClientSimulator->ClientCoreMgr
	SetDownMsgProcSuccessor(m_client_mgr);

	// Up msg flwo: ClientSimulator<-ClientCoreMgr
	m_client_mgr->SetUpMsgProcSuccessor(shared_from_this());

	// 上行消息映射
	UP_MSG_PRE_MAP(UP_MSG_STATE_START,			VirtualClient::OnStateStart);
	UP_MSG_PRE_MAP(UP_MSG_UPDATE_CHECK_RESULT,	VirtualClient::OnUpdateCheckResult);
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_REP,			VirtualClient::OnLoginRep);
	UP_MSG_PRE_MAP(UP_MSG_GET_ROOM_LIST_REP,	VirtualClient::OnGetRoomListRep);
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_FRONT_ROOM_REP, VirtualClient::OnLoginFrontRoomRep);
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_ROOM_REP,		VirtualClient::OnLoginRoomRep);

	return true;
}

bool VirtualClient::Start()
{
	if (!Init())
	{
		LOG(_T("Failed to init VirtualClient.\n"));
		return false;
	}

	RoomLoginType login_type = ROOM_LOGIN_USER_PWD;
	if (m_client_cfg.user_type == USER_TYPE_REGISTER)
	{
		login_type = ROOM_LOGIN_USER_PWD;
	}
	else
	{
		login_type = ROOM_LOGIN_ROOMID;
	}

	if (!m_client_mgr->Start(login_type))
	{
		LOG(_T("Failed to start ClientCoreMgr.\n"));
		return false;
	}

	return true;
}

bool VirtualClient::Stop()
{
	m_client_mgr->Stop();

	return true;
}

bool VirtualClient::OnStateStart(const MsgData& msg_data)
{
	std::shared_ptr<StateStartMsg> start_msg =
		std::static_pointer_cast<StateStartMsg>(msg_data);

	LOG(_T("ClientSimulator::OnStateStart, state = %u.\n"), start_msg->state_type);

	if (start_msg->state_type == CLIENT_STATE_TYPE_UPDATE)
	{
		SendStartUpdateCheckMsg();
	}
	else if (start_msg->state_type == CLIENT_STATE_TYPE_LOGIN)
	{
		SendLoginMsg();
	}
	else if (start_msg->state_type == CLIENT_STATE_TYPE_SELECT_ROOM)
	{
		if (m_client_cfg.user_type == USER_TYPE_REGISTER)
		{
			SendDownMsg(DOWN_MSG_GET_ROOM_LIST, nullptr);
		}
	}
	else if (start_msg->state_type == CLIENT_STATE_TYPE_STARTUP_ROOM)
	{
		SendAvConfigMsg();
		TryToSendLoginFrontRoomMsg();
	}
	else if (start_msg->state_type == CLIENT_STATE_TYPE_MAIN_ROOM)
	{
		; // TODO:
	}
	else
	{
		LOG(_T("ClientSimulator::OnStateStart - Unhandled state = %u.\n"),
			start_msg->state_type);
	}

	return false;
}

bool VirtualClient::OnUpdateCheckResult(const MsgData& msg_data)
{
	LOG(_T("VirtualClient::OnUpdateCheckResult.\n"));

	std::shared_ptr<UpdateCheckRepMsg> update_rep =
		std::static_pointer_cast<UpdateCheckRepMsg>(msg_data);

	LOG(_T(">>> Update check result = %u.\n"), update_rep->result);

	return false;
}

bool VirtualClient::OnLoginRep(const MsgData& msg_data)
{
	LOG(_T("VirtualClient::OnLoginRep.\n"));

	std::shared_ptr<LoginRepMsg> rep_msg =
		std::static_pointer_cast<LoginRepMsg>(msg_data);

	LOG(_T(">>> Login result: %u.\n"), rep_msg->login_result);

	return false;
}

bool VirtualClient::OnGetRoomListRep(const MsgData& msg_data)
{
	LOG(_T("VirtualClient::OnGetRoomListRep.\n"));

	std::shared_ptr<GetRoomListRepMsg> rep_msg =
		std::static_pointer_cast<GetRoomListRepMsg>(msg_data);

	LOG(_T(">>> Room count: %u.\n"), rep_msg->room_list.size());

	m_room_list = rep_msg->room_list;

	return false;
}

bool VirtualClient::OnLoginFrontRoomRep(const MsgData& msg_data)
{
	LOG(_T("VirtualClient::OnLoginFrontRoomRep.\n"));

	std::shared_ptr<LoginFrontRoomRepMsg> rep_msg =
		std::static_pointer_cast<LoginFrontRoomRepMsg>(msg_data);

	LOG(_T(">>> Login front room result = %u.\n"), rep_msg->login_result);

	return false;
}

bool VirtualClient::OnLoginRoomRep(const MsgData& msg_data)
{
	LOG(_T("VirtualClient::OnLoginRoomRep.\n"));

	std::shared_ptr<LoginRoomRepMsg> rep_msg =
		std::static_pointer_cast<LoginRoomRepMsg>(msg_data);

	LOG(_T(">>> Login room result = %u.\n"), rep_msg->login_result);

	return false;
}

void VirtualClient::SendAvConfigMsg()
{
	std::shared_ptr<AvConfigMsg> config_msg(new AvConfigMsg);

	config_msg->video_count		= m_client_cfg.video_count;
	config_msg->video_source	= m_client_cfg.video_src;

	SendDownMsg(DOWN_MSG_AV_CONFIG, config_msg);
}

void VirtualClient::SendLoginFrontRoomMsg()
{
	std::shared_ptr<LoginFrontRoomReqMsg> req_msg(new LoginFrontRoomReqMsg);

	req_msg->room_app_id	= m_client_cfg.room_app_id;
	req_msg->room_id		= m_client_cfg.room_id;
	req_msg->room_node_id	= "1";

	SendDownMsg(DOWN_MSG_LOGIN_FRONT_ROOM, req_msg);
}

void VirtualClient::SendLoginMsg()
{
	std::shared_ptr<LoginReqMsg> login_msg(new LoginReqMsg);

	login_msg->user_name	= m_client_cfg.user_name;
	login_msg->user_pwd		= m_client_cfg.user_pwd;
	login_msg->server_addr	= m_client_cfg.front_addr;
	login_msg->front_app_id = m_client_cfg.front_app_id;
	login_msg->room_app_id	= m_client_cfg.room_app_id;
	login_msg->client_type	= m_client_cfg.client_type;
	login_msg->user_type	= m_client_cfg.user_type;
	login_msg->product_name = m_client_cfg.product_id;
	login_msg->terminal_type= m_client_cfg.terminal_type;

	SendDownMsg(DOWN_MSG_LOGIN, login_msg);
}

void VirtualClient::SendStartUpdateCheckMsg()
{
	std::shared_ptr<UpdateCheckReqMsg> update_msg(new UpdateCheckReqMsg);

	update_msg->server_addr = m_client_cfg.front_addr;
	update_msg->product_id	= m_client_cfg.product_id;
	update_msg->client_ver	= m_client_cfg.client_ver;

	SendDownMsg(DOWN_MSG_START_UPDATE_CHECK, update_msg);
}

void VirtualClient::TryToSendLoginFrontRoomMsg()
{
	// 如果是注册用户登录，则需要判断待登录会议室是否在
	// 返回的会议室列表中，如果不存在则返回错误
	if (m_client_cfg.user_type == USER_TYPE_REGISTER)
	{
		bool room_exist = false;
		for each (FrontRoomInfo room_info in m_room_list)
		{
			if (room_info.room_id == m_client_cfg.room_id)
			{
				room_exist = true;
				break;
			}
		}

		if (!room_exist)
		{
			LOG(_T("Failed to find loginingg room.\n"));
			Stop();
			return;
		}
	}

	SendLoginFrontRoomMsg();
}