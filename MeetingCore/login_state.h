#pragma once
#include "meeting_core_define.h"
#include "xmlmsgiopack.h"
#include "common_msg_processor.h"
#include "client_state_shim.h"

namespace meetingcore
{

class LoginState 
	: public ClientStateShim
	, public std::enable_shared_from_this<LoginState>
{
public:
	LoginState(const ClientStateMachineSP& state_machine);
	~LoginState();

	virtual bool Run() override;

private:
	bool Init();
	bool OnLoginRep(const MsgData& msg_data);

private:
	ClientStateMachineSP m_state_machine;
};

}

