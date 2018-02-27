#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "client_state_shim.h"

namespace meetingcore
{

class StartupRoomState
	: public ClientStateShim
	, public std::enable_shared_from_this<StartupRoomState>
{
public:
	StartupRoomState(const ClientStateMachineSP& state_machine);
	~StartupRoomState();

	virtual bool Run() override;

private:
	bool Init();
	bool OnLoginRoomRep(const MsgData& msg_data);
	bool OnCreateAvComponentRep(const MsgData& msg_data);
	bool OnLoginAvRoomRep(const MsgData& msg_data);

private:
	ClientStateMachineSP m_state_machine;
	std::shared_ptr<LoginRoomRepMsg> m_login_room_rep_msg;
};

}
