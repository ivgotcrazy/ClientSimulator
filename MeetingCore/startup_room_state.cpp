#include "stdafx.h"
#include "startup_room_state.h"
#include "client_state_machine.h"
#include "conf_manager.h"
#include "av_manager.h"

using namespace meetingcore;

StartupRoomState::StartupRoomState(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, ClientStateShim(CLIENT_STATE_TYPE_STARTUP_ROOM)
{
	LOG(_T("StartupRoomState::StartupRoomState.\n"));
}


StartupRoomState::~StartupRoomState()
{
	LOG(_T("StartupRoomState::~StartupRoomState.\n"));
}

bool StartupRoomState::Run()
{
	if (!Init())
	{
		LOG(_T("Failed to init StartupRoomState.\n"));
		return false;
	}

	SendStateStartMsg();

	return true;
}

bool StartupRoomState::Init()
{
	ConfManagerSP conf_mgr = m_state_machine->GetConfManager();

	// Up msg flow: StartupRoomState<-ConfManager
	conf_mgr->SetUpMsgProcSuccessor(shared_from_this());

	AvManagerSP av_mgr = m_state_machine->GetAvManager();

	// Up msg flow: StartupRoomState<-AvManager
	av_mgr->SetUpMsgProcSuccessor(shared_from_this());

	// 上行消息注册
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_ROOM_REP, StartupRoomState::OnLoginRoomRep);
	UP_MSG_PRE_MAP(UP_MSG_CREATE_AV_COMPONENT_REP, StartupRoomState::OnCreateAvComponentRep);
	UP_MSG_POST_MAP(UP_MSG_LOGIN_AV_ROOM_REP, StartupRoomState::OnLoginAvRoomRep);

	// 下行消息路由
	SET_DOWN_MSG_ROUTE(DOWN_MSG_CREATE_AV_COMPONENT,av_mgr);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_AV_CONFIG,			av_mgr);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_AV_ROOM,		av_mgr);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_START_RECV_MEDIA,	av_mgr);

	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_FRONT_ROOM,	conf_mgr);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_LOGIN_ROOM,			conf_mgr);

	return true;
}

bool StartupRoomState::OnLoginRoomRep(const MsgData& msg_data)
{
	// 保存响应消息
	m_login_room_rep_msg = std::static_pointer_cast<LoginRoomRepMsg>(msg_data);

	// 通知创建音视频组件和设备
	SendDownMsg(DOWN_MSG_CREATE_AV_COMPONENT, nullptr);

	return false;
}

bool StartupRoomState::OnCreateAvComponentRep(const MsgData& msg_data)
{
	CreateAvComponentRepMsgSP rep_msg =
		std::static_pointer_cast<CreateAvComponentRepMsg>(msg_data);

	if (rep_msg->create_result == 0)
	{
		SendUpMsg(UP_MSG_LOGIN_ROOM_REP, m_login_room_rep_msg);
	}
	else
	{
		LOG(_T("Failed to create av components.\n"));
		// TODO:
	}

	return false;
}

bool StartupRoomState::OnLoginAvRoomRep(const MsgData& msg_data)
{
	LoginAvRoomRepMsgSP rep_msg =
		std::static_pointer_cast<LoginAvRoomRepMsg>(msg_data);

	if (rep_msg->login_result == 1)
	{
		SendStateStopMsg();
	}
	else
	{
		; // TODO:
	}

	return true;
}