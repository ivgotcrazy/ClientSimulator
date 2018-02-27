#pragma once

#include "framework.h"
#include "wthread.h"
#include "meeting_core_define.h"
#include "client_public.h"
#include "isessionmanager.h"
#include "common_msg_processor.h"
#include "state_switch_policy.h"

using namespace FsMeeting;
using namespace clientcore;

namespace meetingcore
{

class ClientStateMachine 
	: public CommonMsgProcessor
	, public std::enable_shared_from_this<ClientStateMachine>
{
public:
	ClientStateMachine(ClientBaseComponents* base_objs, 
		const ThreadMsgConverterSP& msg_converter,
		const ClientConfig& client_cfg);

	bool Start(RoomLoginType login_type);
	void Stop();

	ClientStateType		GetCurrStateType() const;
	const ClientConfig& GetClientConfig() const;

	IComponentFactory*	GetFactory() const;
	ISessionManager2*	GetSessionManager() const;
	IWNetwork*			GetNetwork() const;
	ThreadMsgConverterSP GetMsgConverter() const;
	ConfManagerSP		GetConfManager() const;
	AvManagerSP			GetAvManager() const;

private:
	bool Init();
	void SwitchToNextState();
	bool OnStateStop(const MsgData& msg_data);

	void BuildMsgProcLink();
	void StartInitState();
	void StartUpdateState();
	void StartLoginState();
	void StartSelectRoomState();
	void StartStartupRoomState();
	void StartMainRoomState();

private:
	ClientBaseComponents*	m_base_objs;
	ClientConfig			m_client_cfg;
	IClientStateSP			m_current_state;
	ThreadMsgConverterSP	m_msg_converter;

	// 会议相关处理，包括登录过程
	ConfManagerSP m_conf_mgr;

	// 音视频相关处理
	AvManagerSP	m_av_mgr;

	// 状态机状态跳转流程，这里使用策略模式
	IStateSwitchPolicySP m_state_switch_policy;
};

}