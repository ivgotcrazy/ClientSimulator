#include "stdafx.h"
#include "state_switch_policy.h"

using namespace meetingcore;

ClientStateType LoginByUserPwdStateSwitchPolicy::GetNextClientState(ClientStateType curr_state)
{
	ClientStateType next_state = CLIENT_STATE_TYPE_QUIT;

	switch (curr_state)
	{
	case CLIENT_STATE_TYPE_INVALID:
		next_state = CLIENT_STATE_TYPE_INIT;
		break;

	case CLIENT_STATE_TYPE_INIT:
		next_state = CLIENT_STATE_TYPE_UPDATE;
		break;

	case CLIENT_STATE_TYPE_UPDATE:
		next_state = CLIENT_STATE_TYPE_LOGIN;
		break;

	case CLIENT_STATE_TYPE_LOGIN:
		next_state = CLIENT_STATE_TYPE_SELECT_ROOM;
		break;

	case CLIENT_STATE_TYPE_SELECT_ROOM:
		next_state = CLIENT_STATE_TYPE_STARTUP_ROOM;
		break;

	case CLIENT_STATE_TYPE_STARTUP_ROOM:
		next_state = CLIENT_STATE_TYPE_MAIN_ROOM;
		break;

	case CLIENT_STATE_TYPE_MAIN_ROOM:
		next_state = CLIENT_STATE_TYPE_SWITCH_GROUP_ROOM;
		break;

	case CLIENT_STATE_TYPE_SWITCH_GROUP_ROOM:
		next_state = CLIENT_STATE_TYPE_GROUP_ROOM;
		break;

	case CLIENT_STATE_TYPE_GROUP_ROOM:
		next_state = CLIENT_STATE_TYPE_SWITCH_MAIN_ROOM;
		break;

	case CLIENT_STATE_TYPE_SWITCH_MAIN_ROOM:
		next_state = CLIENT_STATE_TYPE_MAIN_ROOM;
		break;

	default:
		next_state = CLIENT_STATE_TYPE_MAIN_ROOM;
		break;
	}

	return next_state;
}


ClientStateType LoginByRoomIdStateSwitchPolicy::GetNextClientState(ClientStateType curr_state)
{
	ClientStateType next_state = CLIENT_STATE_TYPE_QUIT;

	switch (curr_state)
	{
	case CLIENT_STATE_TYPE_INVALID:
		next_state = CLIENT_STATE_TYPE_INIT;
		break;

	case CLIENT_STATE_TYPE_INIT:
		next_state = CLIENT_STATE_TYPE_UPDATE;
		break;

	case CLIENT_STATE_TYPE_UPDATE:
		next_state = CLIENT_STATE_TYPE_LOGIN;
		break;

	case CLIENT_STATE_TYPE_LOGIN:
		next_state = CLIENT_STATE_TYPE_STARTUP_ROOM;
		break;

	case CLIENT_STATE_TYPE_SELECT_ROOM:
		LOG(_T("Cannot be here.\n"));
		break;

	case CLIENT_STATE_TYPE_STARTUP_ROOM:
		next_state = CLIENT_STATE_TYPE_MAIN_ROOM;
		break;

	case CLIENT_STATE_TYPE_MAIN_ROOM:
		next_state = CLIENT_STATE_TYPE_SWITCH_GROUP_ROOM;
		break;

	case CLIENT_STATE_TYPE_SWITCH_GROUP_ROOM:
		next_state = CLIENT_STATE_TYPE_GROUP_ROOM;
		break;

	case CLIENT_STATE_TYPE_GROUP_ROOM:
		next_state = CLIENT_STATE_TYPE_SWITCH_MAIN_ROOM;
		break;

	case CLIENT_STATE_TYPE_SWITCH_MAIN_ROOM:
		next_state = CLIENT_STATE_TYPE_MAIN_ROOM;
		break;

	default:
		next_state = CLIENT_STATE_TYPE_MAIN_ROOM;
		break;
	}

	return next_state;
}