#pragma once
#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "client_state_shim.h"

namespace meetingcore
{

class UpdateState 
	: public ClientStateShim
	, public std::enable_shared_from_this<UpdateState>
{
public:
	UpdateState(const ClientStateMachineSP& state_machine);
	~UpdateState();

	virtual bool Run() override;

private:
	bool Init();
	bool OnUpdateCheckResult(const MsgData& msg_data);

private:
	ClientStateMachineSP m_state_machine;
};

}

