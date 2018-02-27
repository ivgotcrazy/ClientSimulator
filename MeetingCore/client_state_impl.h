#pragma once
#include "meeting_core_define.h"

namespace meetingcore
{

class ClientStateShim : public IClientState
{
public:
	virtual ~ClientStateShim(){};

	virtual bool Run() 
	{
		return PreProc() && Process() && PostProc();
	}

	virtual ClientStateType GetClientStateType() { return m_state_type;  }
	virtual ClientStatePhase GetClientStatePhase() { return m_state_phase; }

protected:
	virtual bool PreProc() = 0;
	virtual bool Process() = 0;
	virtual bool PostProc() = 0;

protected:
	ClientStateType m_state_type;
	ClientStatePhase m_state_phase;
};

}

