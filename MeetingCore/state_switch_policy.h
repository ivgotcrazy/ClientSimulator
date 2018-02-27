#pragma once

#include "client_public.h"

using namespace clientcore;

namespace meetingcore
{

class IStateSwitchPolicy
{
public:
	virtual ClientStateType GetNextClientState(ClientStateType curr_state) = 0;
};

class LoginByUserPwdStateSwitchPolicy : public IStateSwitchPolicy
{
private:
	virtual ClientStateType GetNextClientState(ClientStateType curr_state) override;
};

class LoginByRoomIdStateSwitchPolicy : public IStateSwitchPolicy
{
private:
	virtual ClientStateType GetNextClientState(ClientStateType curr_state) override;
};

typedef std::shared_ptr<IStateSwitchPolicy> IStateSwitchPolicySP;

}