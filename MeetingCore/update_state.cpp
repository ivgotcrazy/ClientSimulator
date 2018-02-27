#include "stdafx.h"
#include <atlconv.h>
#include "update_state.h"
#include "client_state_machine.h"
#include "xmlprotocolparser.h"
#include "UpdateMgrProtocol.h"
#include "conf_manager.h"

using namespace clientcore;
using namespace meetingcore;

#define THREAD_MSG_TCPNETWORK		WM_USER+100

UpdateState::UpdateState(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, ClientStateShim(CLIENT_STATE_TYPE_UPDATE)
{
	LOG(_T("UpdateState::UpdateState.\n"));
}

UpdateState::~UpdateState()
{
	LOG(_T("UpdateState::~UpdateState.\n"));
}

bool UpdateState::Init()
{
	ConfManagerSP conf_mgr = m_state_machine->GetConfManager();

	// UpdateState->ConfManager
	SetDownMsgProcSuccessor(conf_mgr);

	// UpdateState<-ConfManager
	conf_mgr->SetUpMsgProcSuccessor(shared_from_this());

	// 上行消息映射
	UP_MSG_POST_MAP(UP_MSG_UPDATE_CHECK_RESULT, UpdateState::OnUpdateCheckResult);

	return true;
}

bool UpdateState::Run()
{
	LOG(_T("UpdateState::Run.\n"));

	if (!Init())
	{
		LOG(_T("Failed to init UpdateState.\n"));
		return false;
	}

	SendStateStartMsg();

	return true;
}

bool UpdateState::OnUpdateCheckResult(const MsgData& msg_data)
{
	SendStateStopMsg();

	return true;
}