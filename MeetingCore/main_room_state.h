#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "client_state_shim.h"

namespace meetingcore
{

class MainRoomState 
	: public ClientStateShim
	, public std::enable_shared_from_this<MainRoomState>
{
public:
	MainRoomState(const ClientStateMachineSP& state_machine);
	~MainRoomState();

	virtual bool Run() override;

private:
	bool Init();

private:
	ClientStateMachineSP m_state_machine;
};

}