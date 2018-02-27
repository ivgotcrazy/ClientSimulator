#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "client_state_shim.h"

namespace meetingcore
{

class SelectRoomState 
	: public ClientStateShim
	, public std::enable_shared_from_this<SelectRoomState>
{
public:
	SelectRoomState(const ClientStateMachineSP& state_machine);
	~SelectRoomState();

	virtual bool Run() override;

private:
	bool Init();
	bool OnGetRoomListRep(const MsgData& msg_data);

private:
	ClientStateMachineSP m_state_machine;
};

}

