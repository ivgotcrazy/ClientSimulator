#include "stdafx.h"
#include "init_state.h"
#include "client_state_machine.h"
#include "client_public.h"

using namespace clientcore;
using namespace meetingcore;

InitState::InitState(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, ClientStateShim(CLIENT_STATE_TYPE_INIT)
{
	LOG(_T("InitState::InitState.\n"));
}

InitState::~InitState()
{
	LOG(_T("InitState::~InitState.\n"));
}

bool InitState::Run()
{
	LOG(_T("InitState::Start.\n"));

	SendStateStartMsg();

	// TODO: ≥ı ºªØ

	SendStateStopMsg();

	return true;
}