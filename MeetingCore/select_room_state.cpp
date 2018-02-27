#include "stdafx.h"
#include "select_room_state.h"
#include "client_state_machine.h"
#include "conf_manager.h"
#include "conf_msg_processor.h"

using namespace meetingcore;

SelectRoomState::SelectRoomState(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, ClientStateShim(CLIENT_STATE_TYPE_SELECT_ROOM)
{
	LOG(_T("SelectRoomState::SelectRoomState.\n"));
}

SelectRoomState::~SelectRoomState()
{
	LOG(_T("SelectRoomState::~SelectRoomState.\n"));
}

bool SelectRoomState::Init()
{
	ConfManagerSP conf_mgr = m_state_machine->GetConfManager();

	// Down msg flow: UpdateState->ConfManager
	SetDownMsgProcSuccessor(conf_mgr);

	// Up msg flow: UpdateState<-ConfManager
	conf_mgr->SetUpMsgProcSuccessor(shared_from_this());

	// 上行消息映射
	UP_MSG_POST_MAP(UP_MSG_GET_ROOM_LIST_REP, SelectRoomState::OnGetRoomListRep);

	return true;
}

bool SelectRoomState::Run()
{
	LOG(_T("SelectRoomState::Run.\n"));

	if (!Init())
	{
		LOG(_T("Failed to init SelectRoomState.\n"));
		return false;
	}

	SendStateStartMsg();

	return true;
}

bool SelectRoomState::OnGetRoomListRep(const MsgData& msg_data)
{
	SendStateStopMsg();

	return false;
}