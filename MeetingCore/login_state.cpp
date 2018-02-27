#include "stdafx.h"
#include "login_state.h"
#include "client_state_machine.h"
#include "client_public.h"
#include "wnetfunction.h"
#include "FrontProtocol.h"
#include "ProtocolError.h"
#include "conf_manager.h"

using namespace clientcore;
using namespace meetingcore;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "zlib32.lib")

#define WM_SESSIONMSG		WM_USER+100

LoginState::LoginState(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, ClientStateShim(CLIENT_STATE_TYPE_LOGIN)
{
	LOG(_T("LoginState::LoginState.\n"));
}

LoginState::~LoginState()
{
	LOG(_T("LoginState::~LoginState.\n"));

}

bool LoginState::Init()
{
	ConfManagerSP conf_mgr = m_state_machine->GetConfManager();

	// UpdateState->ConfManager
	SetDownMsgProcSuccessor(conf_mgr);

	// UpdateState<-ConfManager
	conf_mgr->SetUpMsgProcSuccessor(shared_from_this());

	// 上行消息映射
	UP_MSG_POST_MAP(UP_MSG_LOGIN_REP, LoginState::OnLoginRep);

	return true;
}

bool LoginState::Run()
{
	LOG(_T("LoginState::Run.\n"));

	if (!Init())
	{
		LOG(_T("Failed to init LoginState.\n"));
		return false;
	}

	SendStateStartMsg();

	return true;
}

bool LoginState::OnLoginRep(const MsgData& msg_data)
{
	SendStateStopMsg();

	return true;
}

