#include "stdafx.h"
#include "main_room_state.h"
#include "client_state_machine.h"
#include "conf_manager.h"
#include "av_manager.h"

using namespace meetingcore;

MainRoomState::MainRoomState(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, ClientStateShim(CLIENT_STATE_TYPE_MAIN_ROOM)
{
	LOG(_T("MainRoomState::MainRoomState.\n"));
}

MainRoomState::~MainRoomState()
{
	LOG(_T("MainRoomState::~MainRoomState.\n"));
}

bool MainRoomState::Run()
{
	LOG(_T("MainRoomState::Run.\n"));

	if (!Init())
	{
		LOG(_T("Failed to init MainRoomState.\n"));
		return false;
	}

	SendStateStartMsg();

	// 通告初始化完成
	m_state_machine->GetConfManager()->OnDownMsg(DOWN_MSG_INIT_COMPLETE, nullptr);

	return true;
}

bool MainRoomState::Init()
{
	ConfManagerSP conf_mgr = m_state_machine->GetConfManager();

	// Up msg flow: MainRoomState<-ConfManager
	conf_mgr->SetUpMsgProcSuccessor(shared_from_this());

	AvManagerSP av_mgr = m_state_machine->GetAvManager();

	// Up msg flow: MainRoomState<-AvManager
	av_mgr->SetUpMsgProcSuccessor(shared_from_this());

	// 消息路由
	SET_DOWN_MSG_ROUTE(DOWN_MSG_START_RECV_MEDIA, av_mgr);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_INIT_COMPLETE, conf_mgr);
	SET_DOWN_MSG_ROUTE(DOWN_MSG_BROADCAST_USER_AV_INFO, conf_mgr);

	return true;
}