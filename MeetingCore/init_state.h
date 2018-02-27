#pragma once
#include "meeting_core_define.h"
#include "client_state_shim.h"
#include "common_msg_processor.h"

namespace meetingcore
{

class InitState : public ClientStateShim
{
public:
	InitState(const ClientStateMachineSP& state_machine);
	~InitState();

	virtual bool Run() override;

private:
	ClientStateMachineSP m_state_machine;
};

}

