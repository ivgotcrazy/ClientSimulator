#include "stdafx.h"
#include "client_state_machine.h"
#include "init_state.h"
#include "update_state.h"
#include "login_state.h"
#include "select_room_state.h"
#include "startup_room_state.h"
#include "main_room_state.h"
#include "conf_manager.h"
#include "av_manager.h"

using namespace clientcore;
using namespace meetingcore;

ClientStateMachine::ClientStateMachine(ClientBaseComponents* base_objs,
	const ThreadMsgConverterSP& msg_converter,
	const ClientConfig& client_cfg)
	: m_base_objs(base_objs)
	, m_msg_converter(msg_converter)
	, m_client_cfg(client_cfg)
{
	
}

bool ClientStateMachine::Init()
{
	m_conf_mgr.reset(new ConfManager(shared_from_this()));
	if (!m_conf_mgr->Init())
	{
		LOG(_T("Failed to init ConfManager.\n"));
		return false;
	}

	m_av_mgr.reset(new AvManager(shared_from_this()));
	if (!m_av_mgr->Init())
	{
		LOG(_T("Failed to init AvManager.\n"));
		return false;
	}

	// 上行消息注册
	UP_MSG_PRE_MAP(UP_MSG_STATE_STOP, ClientStateMachine::OnStateStop);

	// 下行消息注册
	

	return true;
}

void ClientStateMachine::BuildMsgProcLink()
{
	IMsgProcessorSP state = std::dynamic_pointer_cast<IMsgProcessor>(m_current_state);

	// StateMachine->ClientState
	SetDownMsgProcSuccessor(state);

	std::shared_ptr<CommonMsgProcessor> processor =
		std::dynamic_pointer_cast<CommonMsgProcessor>(m_current_state);

	// StateMachine<-ClientState
	processor->SetUpMsgProcSuccessor(shared_from_this());
}

void ClientStateMachine::StartInitState()
{
	LOG(_T("ClientStateMachine::StartInitState.\n"));

	m_current_state.reset(new InitState(shared_from_this()));

	BuildMsgProcLink();

	m_current_state->Run();
}

void ClientStateMachine::StartUpdateState()
{
	LOG(_T("ClientStateMachine::StartUpdateState.\n"));

	m_current_state.reset(new UpdateState(shared_from_this()));

	BuildMsgProcLink();

	m_current_state->Run();
}

void ClientStateMachine::StartLoginState()
{
	LOG(_T("ClientStateMachine::StartLoginState.\n"));

	m_current_state.reset(new LoginState(shared_from_this()));

	BuildMsgProcLink();

	m_current_state->Run();
}

void ClientStateMachine::StartSelectRoomState()
{
	LOG(_T("ClientStateMachine::StartSelectRoomState.\n"));

	m_current_state.reset(new SelectRoomState(shared_from_this()));

	BuildMsgProcLink();

	m_current_state->Run();
}

void ClientStateMachine::StartStartupRoomState()
{
	LOG(_T("ClientStateMachine::StartStartupRoomState.\n"));

	m_current_state.reset(new StartupRoomState(shared_from_this()));

	BuildMsgProcLink();

	m_current_state->Run();
}

void ClientStateMachine::StartMainRoomState()
{
	LOG(_T("ClientStateMachine::StartMainRoomState.\n"));

	m_current_state.reset(new MainRoomState(shared_from_this()));

	BuildMsgProcLink();

	m_current_state->Run();
}

bool ClientStateMachine::Start(RoomLoginType login_type)
{
	LOG(_T("ClientStateMachine::Start.\n"));

	if (!Init())
	{
		LOG(_T("Failed to init ClientStateMachine.\n"));
		return false;
	}

	if (login_type == ROOM_LOGIN_USER_PWD)
	{
		m_state_switch_policy.reset(new LoginByUserPwdStateSwitchPolicy);
	}
	else if (login_type == ROOM_LOGIN_ROOMID)
	{
		m_state_switch_policy.reset(new LoginByRoomIdStateSwitchPolicy);
	}
	else
	{
		LOG(_T("Invalid room login type = %u."), login_type);
		return false;
	}

	SwitchToNextState();

	return true;
}

void ClientStateMachine::Stop()
{
	LOG(_T("ClientStateMachine::Stop.\n"));
}

bool ClientStateMachine::OnStateStop(const MsgData& msg_data)
{
	LOG(_T("ClientStateMachine::OnStateStop.\n"));

	SwitchToNextState();

	return false; // 状态转换内部处理，外部接收StateStart消息
}

IComponentFactory* ClientStateMachine::GetFactory() const
{
	assert(m_base_objs);
	assert(m_base_objs->factory);

	return m_base_objs->factory;
}

ISessionManager2* ClientStateMachine::GetSessionManager() const
{
	assert(m_base_objs);
	assert(m_base_objs->session_mgr);

	return m_base_objs->session_mgr;
}

IWNetwork* ClientStateMachine::GetNetwork() const
{
	assert(m_base_objs);
	assert(m_base_objs->network);

	return m_base_objs->network;
}

const ClientConfig& ClientStateMachine::GetClientConfig() const
{
	return m_client_cfg;
}

ConfManagerSP ClientStateMachine::GetConfManager() const
{
	return m_conf_mgr;
}

AvManagerSP ClientStateMachine::GetAvManager() const
{
	return m_av_mgr;
}

ThreadMsgConverterSP ClientStateMachine::GetMsgConverter() const
{
	return m_msg_converter;
}

ClientStateType	ClientStateMachine::GetCurrStateType() const
{
	if (m_current_state)
	{
		return m_current_state->GetClientStateType();
	}
	else
	{
		return CLIENT_STATE_TYPE_INVALID;
	}
}

void ClientStateMachine::SwitchToNextState()
{	
	ClientStateType curr_state = CLIENT_STATE_TYPE_INVALID;
	if (m_current_state)
	{
		curr_state = m_current_state->GetClientStateType();
	}
	
	ClientStateType next_state = m_state_switch_policy->GetNextClientState(curr_state);

	switch (next_state)
	{
	case CLIENT_STATE_TYPE_INIT:
		StartInitState();
		break;
	case CLIENT_STATE_TYPE_UPDATE:
		StartUpdateState();
		break;
	case CLIENT_STATE_TYPE_LOGIN:
		StartLoginState();
		break;
	case CLIENT_STATE_TYPE_SELECT_ROOM:
		StartSelectRoomState();
		break;
	case CLIENT_STATE_TYPE_STARTUP_ROOM:
		StartStartupRoomState();
		break;
	case CLIENT_STATE_TYPE_MAIN_ROOM:
		StartMainRoomState();
		break;
	default:
		LOG(_T("ClientStateMachine::Unexpected state type = %u.\n"), next_state);
		break;
	}
}