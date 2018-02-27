#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"

namespace meetingcore
{

class ClientStateShim 
	: public IClientState
	, public CommonMsgProcessor
{
public:
	ClientStateShim(ClientStateType state_type) : m_state_type(state_type)
	{
	}

	virtual ClientStateType GetClientStateType() override
	{
		return m_state_type;
	}

protected:
	void SendStateStartMsg()
	{
		std::shared_ptr<StateStartMsg> start_msg_data(new StateStartMsg);
		start_msg_data->state_type = m_state_type;

		SendUpMsg(UP_MSG_STATE_START, start_msg_data);
	}

	void SendStateStopMsg()
	{
		std::shared_ptr<StateStopMsg> stop_msg_data(new StateStopMsg);
		stop_msg_data->state_type = m_state_type;

		SendUpMsg(UP_MSG_STATE_STOP, stop_msg_data);
	}

private:
	ClientStateType m_state_type;
};

}