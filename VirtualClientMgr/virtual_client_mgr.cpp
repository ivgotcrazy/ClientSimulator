#include "stdafx.h"

#include <atlconv.h>

#include "virtual_client_mgr.h"
#include "tixmlfunction.h"
#include "XMLProtocolParser.h"

#define MAX_CHAR_SIZE	256

using namespace clientmgr;

static FS_UINT32 timer_id = 0;

#define TIMER_INTERVAL	1000

VirtualClientMgr::VirtualClientMgr()
	: m_next_login_user_index(0)
	, m_thread_stop_flag(false)
	, m_start_flag(false)
{
	m_concurrent_login_count = 0;
	m_current_second_login_count = 0;
}

static LRESULT TimerCallback(FS_UINT32 uTimerID, FS_UINT dwUserData)
{
	if (uTimerID == timer_id)
	{
		VirtualClientMgr* pClientMgr = reinterpret_cast<VirtualClientMgr*>(dwUserData);
		pClientMgr->OnTimer();
	}

	return 0;
}

bool VirtualClientMgr::Init(IComponentFactory* factory)
{
	if (!CreateBaseComponents(factory))
	{
		LOG(_T("Failed to create base components.\n"));
		return false;
	}

	if (GlobalConfigMgr::GetInstance().GetGlobalConfig().users.empty())
	{
		LOG(_T("None user.\n"));
		return false;
	}

	m_video_source.reset(new VideoSource(m_base_comps.factory,
	GlobalConfigMgr::GetInstance().GetGlobalConfig().video_param));
	if (!m_video_source->Init())
	{
		LOG(_T("Failed to init video source.\n"));
		return false;
	}

	m_audio_source.reset(new AudioSource(m_base_comps.factory));
	if (!m_audio_source->Init())
	{
		LOG(_T("Failed to init audio source.\n"));
		return false;
	}

	// 下行消息映射
	DOWN_MSG_PRE_MAP(DOWN_MSG_PREVIEW_VIDEO_DEV, VirtualClientMgr::OnPreviewVideoDev);
	DOWN_MSG_PRE_MAP(DOWN_MSG_SET_VIDEO_PARAM, VirtualClientMgr::OnSetVideoParam);
	DOWN_MSG_PRE_MAP(DOWN_MSG_SET_AUDIO_PARAM, VirtualClientMgr::OnSetAudioParam);

	// 上行消息映射
	UP_MSG_PRE_MAP(UP_MSG_USER_LOGIN_RESULT, VirtualClientMgr::OnUserLoginResultMsg);

	return true;
}

bool VirtualClientMgr::CreateBaseComponents(IComponentFactory* factory)
{
	m_base_comps.factory = factory;

	HRESULT hr = factory->CreateComponent(
		CLSID_SessionManager2,
		IID_ISessionManager2, 
		NULL, 
		(void**)&m_base_comps.session_mgr);
	if (FAILED(hr))
	{
		LOG(_T("Failed to create session manager.\n"));
		return false;
	}

	hr = m_base_comps.timer_mgr.StartTimer();
	if (FAILED(hr))
	{
		LOG(_T("Failed to start timer manager.\n"));
		return false;
	}

	hr = m_base_comps.session_mgr->Start();
	if (FAILED(hr))
	{
		LOG(_T("Failed to start session manager.\n"));
		return false;
	}

	// 版本查询要用到
	hr = factory->QueryInterface(IID_IWNetwork, (void**)&m_base_comps.network);
	if (FAILED(hr))
	{
		LOG(_T("Failed to query IID_IWNetwork.\n"));
		return false;
	}

	return true;
}

bool VirtualClientMgr::Start()
{
	LOG(_T("VirtualClientMgr::Start.\n"));

	m_start_flag = true;
	m_thread_stop_flag = false;
	
	// 未找到本地视频设备，通知上层应用
	if (m_video_source->GetVideoDeviceNames().empty())
	{
		SendUpMsg(UP_MSG_HAS_NO_VIDEO_DEV, nullptr);
	}

	const GlobalConfig& cfg = 
		GlobalConfigMgr::GetInstance().GetGlobalConfig();

	VideoDevCapParam cap_param;
	cap_param.dev_index		= cfg.video_param.video_dev_index;
	cap_param.width			= cfg.video_param.width;
	cap_param.height		= cfg.video_param.height;
	cap_param.frame_rate	= cfg.video_param.frame_rate;
	cap_param.bit_rate		= cfg.video_param.bit_rate;
	cap_param.encode_mode	= cfg.video_param.encode_mode;

	if (!m_video_source->StartCapture(cap_param, NULL))
	{
		LOG(_T("Failed to start video source.\n"));

		AppRunErrMsgSP err_msg(new AppRunErrMsg);
		err_msg->run_err = ERR_CODE_START_VIDEO_FAILED;
		SendUpMsg(UP_MSG_APP_RUN_ERROR, err_msg);
	}

	if (!m_audio_source->StartCapture(cfg.audio_param.audio_dev_index))
	{
		LOG(_T("Failed to start audio source.\n"));
		
		AppRunErrMsgSP err_msg(new AppRunErrMsg);
		err_msg->run_err = ERR_CODE_START_AUDIO_FAILED;
		SendUpMsg(UP_MSG_APP_RUN_ERROR, err_msg);
	}

	// 启动登录线程
	m_login_thread.swap(std::thread(&VirtualClientMgr::ThreadProc, this));

	// 创建定时器
	timer_id = m_base_comps.timer_mgr.AddTimer(
		TimerCallback, (FS_UINT)this, TIMER_INTERVAL);
	if (timer_id == 0)
	{
		LOG(_T("Failed to add timer.\n"));
		return false;
	}

	return true;
}

void VirtualClientMgr::OnTimer()
{
	m_current_second_login_count = 0;
	m_login_contiue_cond.notify_one();

	// 这里可能有性能问题，暂时先简单处理
	std::lock_guard<std::mutex> lock(m_client_mutex);
	for each (VirtualClientSP client in m_login_clients)
	{
		client->OnTimer();
	}
}

void VirtualClientMgr::WaitForContinueLogin()
{
	const GlobalConfig& cfg = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	std::unique_lock<std::mutex> lock(m_client_mutex);

	while (m_concurrent_login_count >= cfg.login_param.concurrent_login_count
		|| m_current_second_login_count >= cfg.login_param.login_count_per_second)
	{
		m_login_contiue_cond.wait(lock);
	}
}

VirtualClientSP VirtualClientMgr::BuildNewVirtualClient(const UserInfo& user_info)
{
	const GlobalConfig& cfg = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	ClientConfig client_cfg;
	client_cfg.client_mode = cfg.common_info.client_mode;
	client_cfg.client_type = cfg.common_info.client_type;
	client_cfg.client_ver = cfg.common_info.client_ver;
	client_cfg.front_addr = cfg.common_info.front_addr;
	client_cfg.front_app_id = cfg.common_info.front_app_id;
	client_cfg.product_id = cfg.common_info.product_id;
	client_cfg.room_app_id = cfg.common_info.room_app_id;
	client_cfg.terminal_type = cfg.common_info.terminal_type;
	client_cfg.room_id = cfg.common_info.room_id;
	client_cfg.room_pwd = cfg.common_info.room_pwd;
	client_cfg.if_recv_av = cfg.common_info.if_recv_av;
	client_cfg.user_name = user_info.user_name;
	client_cfg.user_pwd = user_info.user_pwd;
	client_cfg.user_type = user_info.user_type;

	client_cfg.video_dev_index = cfg.video_param.video_dev_index;
	client_cfg.video_width = cfg.video_param.width;
	client_cfg.video_height = cfg.video_param.height;
	client_cfg.video_frame_rate = cfg.video_param.frame_rate;
	client_cfg.video_bit_rate = cfg.video_param.bit_rate;
	client_cfg.video_count = user_info.video_count;
	client_cfg.encode_mode = cfg.video_param.encode_mode;
	client_cfg.video_src = m_video_source->GetVideoDevice(cfg.video_param.video_dev_index);
	client_cfg.audio_src = m_audio_source->GetAudioDevice();

	 VirtualClientSP vclient(new VirtualClient(client_cfg, m_base_comps));

	// Up message flow: VirtualClientMgr <- VirtualClient
	vclient->SetUpMsgProcSuccessor(shared_from_this());

	return vclient;
}

void VirtualClientMgr::ThreadProc()
{
	const GlobalConfig& cfg = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	while (true)
	{
		WaitForContinueLogin();

		if (m_thread_stop_flag)
			break;

		if (m_next_login_user_index >= cfg.users.size())
			break;

		const UserInfo& user_info = cfg.users[m_next_login_user_index];

		VirtualClientSP vclient = BuildNewVirtualClient(user_info);
		if (vclient->Start())
		{
			std::lock_guard<std::mutex> lock(m_client_mutex);
			m_login_clients.push_back(vclient);
			m_concurrent_login_count++;
		}
		else
		{			
			UserLoginResultMsgSP result_msg(new UserLoginResultMsg);
			result_msg->login_result = ERR_CODE_FAIL;
			result_msg->login_time = timeGetTime();
			result_msg->user_name = user_info.user_name;
			result_msg->user_id = 0;
			SendUpMsg(UP_MSG_USER_LOGIN_RESULT, result_msg);

			LOG(_T("Failed to start virtual client.\n"));
		}
		m_next_login_user_index++;
	}
}

bool VirtualClientMgr::Stop()
{
	if (!m_start_flag || m_thread_stop_flag)
		return true;

	// 清理所有虚拟客户端
	for each (VirtualClientSP client in m_login_clients)
	{
		client->Stop();
	}
	m_login_clients.clear();

	// 关闭定时器
	m_base_comps.timer_mgr.RemoveTimer(timer_id);
	m_base_comps.timer_mgr.StopTimer();

	// 结束线程
	m_thread_stop_flag = true;
	m_login_contiue_cond.notify_one();
	m_login_thread.join();

	// 停止视频源设备 
	m_video_source->StopCapture();

	// 停止SessionManager
	m_base_comps.session_mgr->Stop();

	return true;
}

VideoDevNameVec VirtualClientMgr::GetVideoDeviceNames()
{
	return m_video_source->GetVideoDeviceNames();
}

AudioDevNameVec VirtualClientMgr::GetAudioCapDevNames()
{
	return m_audio_source->GetAudioCapDevices();
}

bool VirtualClientMgr::OnPreviewVideoDev(const MsgData& msg_data)
{
	PreviewVideoDevMsgSP preview_msg =
		std::static_pointer_cast<PreviewVideoDevMsg>(msg_data);

	if (!m_video_source->StartCapture(preview_msg->cap_param, 
		preview_msg->render_wnd))
	{
		LOG(_T("Failed to start capture %u.\n"), preview_msg->cap_param.dev_index);
	}
	
	return false;
}

bool VirtualClientMgr::OnSetVideoParam(const MsgData& msg_data)
{
	SetVideoParamMsgSP set_msg =
		std::static_pointer_cast<SetVideoParamMsg>(msg_data);

	if (!m_video_source->SetVideoParam(set_msg->cap_param))
	{
		LOG(_T("Failed to set video param, dev = %u.\n"), set_msg->cap_param.dev_index);
		return false;
	}

	return false;
}

bool VirtualClientMgr::OnSetAudioParam(const MsgData& msg_data)
{
	SetAudioParamMsgSP set_msg =
		std::static_pointer_cast<SetAudioParamMsg>(msg_data);

	if (!m_audio_source->SetAudioCapDevParam(set_msg->cap_param))
	{
		LOG(_T("Failed to set auido capture device param, dev = %u.\n"), set_msg->cap_param.dev_index);
		return false;
	}

	return true;
}

bool VirtualClientMgr::OnUserLoginResultMsg(const MsgData& msg_data)
{
	m_current_second_login_count++;
	m_concurrent_login_count--;

	m_login_contiue_cond.notify_one();

	return true;
}