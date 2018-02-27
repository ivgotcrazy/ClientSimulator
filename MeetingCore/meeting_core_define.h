#pragma once

#include <memory>
#include "fs_types.h"
#include "client_public.h"
#include "client_core_define.h"

using namespace clientcore;

namespace meetingcore
{

////////////////////////////////////////////////////////////////////////////////


enum ClientStatePhase
{
	CLIENT_STATE_PHASE_INVALID,
	CLIENT_STATE_PHASE_PROCESSING,
	CLIENT_STATE_PHASE_END
};

class IClientState
{
public:
	virtual ~IClientState(){}

	virtual bool Run() = 0;
	
	virtual ClientStateType GetClientStateType() = 0;
};

typedef std::shared_ptr<IClientState> IClientStateSP;

////////////////////////////////////////////////////////////////////////////////

class ConfManager;
typedef std::shared_ptr<ConfManager> ConfManagerSP;

class AvManager;
typedef std::shared_ptr<AvManager> AvManagerSP;

class ClientStateMachine;
typedef std::weak_ptr<ClientStateMachine> ClientStateMachineWP;
typedef std::shared_ptr<ClientStateMachine> ClientStateMachineSP;

}