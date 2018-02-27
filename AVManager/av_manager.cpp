/*##############################################################################
 * 文件：av_manager.cpp
 * 描述：AvManager实现文件
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/

#include "stdafx.h"
#include "av_manager.h"
#include "client_state_machine.h"

//#include "winitguid.h"
#include "IAudioDevice.h"
#include "IVideoDevice.h"
#include "IMultiAVMP.h"

#define WM_AVMPNOTIFY	(WM_USER + 100)

using namespace meetingcore;

////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------------
 * 描  述：MultiAVMP回调函数
 * 参  数：略
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
BOOL __stdcall OnMsgCallback(UINT nMsgID, DWORD wParam, DWORD lParam, DWORD dwReserved, DWORD dwUserData)
{
	AvManager* av_manager = reinterpret_cast<AvManager*>(dwUserData);

	av_manager->OnAvMpNotify(nMsgID, wParam, lParam, dwReserved);

	return TRUE;
}

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：略
 * 返回值：无
------------------------------------------------------------------------------*/
AvManager::AvManager(const ClientStateMachineSP& state_machine)
	: m_factory(nullptr)
	, m_audio_dev(nullptr)
	, m_av_mp(nullptr)
	, m_remote_video_render(nullptr)
	, m_state_machine(state_machine)
{
	ZeroMemory(m_video_devs, sizeof(m_video_devs));
	ZeroMemory(m_local_video_renders, sizeof(m_local_video_renders));
}

/*------------------------------------------------------------------------------
 * 描  述：初始化函数
 * 参  数：无
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool AvManager::Init()
{
	SetMsgConverter(m_state_machine->GetMsgConverter());

	// 下行消息映射
	DOWN_MSG_PRE_MAP(DOWN_MSG_CREATE_AV_COMPONENT,	AvManager::OnCreateAvComponentMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN_AV_ROOM,		AvManager::OnLoginAvRoomMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_AV_CONFIG,			AvManager::OnAvConfigMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_START_RECV_MEDIA,		AvManager::OnStartRecvMediaMsg);

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：通知创建音视频相关设备消息处理
 * 参  数：[in] msg_data 消息
 * 返回值：消息是否继续分发
------------------------------------------------------------------------------*/
bool AvManager::OnCreateAvComponentMsg(const MsgData& msg_data)
{
	CreateAvComponentRepMsgSP rep_msg(new CreateAvComponentRepMsg);

	rep_msg->create_result = CreateAvComponent() ? 0 : -1;

	SendUpMsg(UP_MSG_CREATE_AV_COMPONENT_REP, rep_msg);

	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：创建音视频设备
 * 参  数：无
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool AvManager::CreateAvComponent()
{
	HRESULT hr = m_state_machine->GetFactory()->CreateComponent(
		CLSID_AudioDevice, IID_IAudioDevice, NULL, (void**)&m_audio_dev);
	if (FAILED(hr))
	{
		LOG(_T("Create Audio Device Component Failed.\n"));
	}

	hr = m_state_machine->GetFactory()->CreateComponent(
		CLSID_MultiAVMP, IID_IMultiAVMP, NULL, (void**)&m_av_mp);
	if (FAILED(hr))
	{
		LOG(_T("Create videomp component failed.\n"));
		return false;
	}

	hr = m_state_machine->GetFactory()->CreateComponent(
		CLSID_VideoRenderManager, 
		IID_IVideoRenderManager, 
		NULL, 
		(void**)&m_remote_video_render);
	if (FAILED(hr))
	{
		LOG(_T("Create Remote VideoRenderManager Failed.\n"));
		return false;
	}

	hr = m_av_mp->Initialize(m_av_config->audio_source, m_remote_video_render, 
		m_state_machine->GetSessionManager());
	if (FAILED(hr))
	{
		LOG(_T("Initialize videomp failed.\n"));
		return false;
	}

	VideoMaxParam max_param;
	max_param.nMaxBitrate = 10000000;
	max_param.nMaxFrameRate = 30;
	max_param.nMaxWidth = 1920;
	max_param.nMaxHeight = 1080;

	// 连接视频设备到MultiAVMP
	for (int i = 0; i < m_av_config->video_count; i++)
	{
		hr = m_av_mp->AddSource(MULTIAV_MEDIATYPE_VIDEO, i, m_av_config->video_source);
		if (FAILED(hr))
		{
			LOG(_T("add video device failed.\n"));
			return false;
		}
		else{
			m_av_mp->SetVideoSourceMaxParam(i, &max_param);
		}
	}

	// 连接音频设备到MultiAVMP
	hr = m_av_mp->AddSource(MULTIAV_MEDIATYPE_AUDIO, 0, m_av_config->audio_source/*m_audio_dev*/);
	if (FAILED(hr))
	{
		LOG(_T("add audio device failed.\n"));
		return false;
	}

	RefreshAvDevices();

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：通知登录音视频服务消息处理
 * 参  数：[in] msg_data 消息
 * 返回值：消息是否继续分发
------------------------------------------------------------------------------*/
bool AvManager::OnLoginAvRoomMsg(const MsgData& msg_data)
{
	LoginAvRoomReqMsgSP login_msg =
		std::static_pointer_cast<LoginAvRoomReqMsg>(msg_data);

	WBASE_NOTIFY notify;
	notify.nNotifyMode = WBASE_NOTIFYMODE_CALLBACK;
	notify.CallbackMode.pCallback = (void*)OnMsgCallback;
	notify.CallbackMode.dwUserData = (DWORD)this;
	notify.CallbackMode.nMsgID = WM_AVMPNOTIFY;

	HRESULT hr = m_av_mp->Login(
		login_msg->group_guid,
		login_msg->user_id,
		login_msg->check_code,
		login_msg->app_id,
		login_msg->server_addr.c_str(),
		&notify);
	if (FAILED(hr))
	{
		LOG(_T("Failed to login av room.\n"));
		// TODO:
	}

	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：通知上层音视频服务登录结果
 * 参  数：略
 * 返回值：无
------------------------------------------------------------------------------*/
void AvManager::OnAvMpNotify(UINT nMsgID, DWORD wParam, DWORD lParam, DWORD dwReserved)
{
	LOG(_T("AvManager::OnAvMpNotify.\n"));

	LoginAvRoomRepMsgSP rep_msg(new LoginAvRoomRepMsg);
	rep_msg->login_result = wParam;

	SendUpMsg(UP_MSG_LOGIN_AV_ROOM_REP, rep_msg);
}

/*------------------------------------------------------------------------------
 * 描  述：音视频设备创建完成后，通知上层音视频设备信息
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void AvManager::RefreshAvDevices()
{
	std::shared_ptr<RefreshAvDevicesMsg> msg_data(new RefreshAvDevicesMsg);

	if (m_audio_dev != nullptr)
	{
		WCHAR dev_name[256];
		int ret = m_audio_dev->GetCapDeviceInfo(0, dev_name, 256);
		if (ret == 0)
		{
			msg_data->audio_dev.dev_index = 0;
			msg_data->audio_dev.dev_name = dev_name;
		}
		else
		{
			LOG(_T("Failed to get audio device info.\n"));
		}
	}

	for (int i = 0; i < m_av_config->video_count; i++)
	{
		WCHAR dev_name[256];
		HRESULT hr = m_av_config->video_source->GetCapDeviceInfo(
			m_av_config->video_dev_index, dev_name, 256);
		if (FAILED(hr))
		{
			LOG(_T("Failed to get video capture device info, index = %d.\n"), i);
			continue;
		}

		VideoDevInfo dev_info;
		dev_info.dev_index = i;
		dev_info.dev_name = dev_name;
		msg_data->video_devs.push_back(dev_info);
	}
	
	SendUpMsg(UP_MSG_REFRESH_AV_DEVICES, msg_data);
}

/*------------------------------------------------------------------------------
 * 描  述：保存上层下发的用户音视频配置信息
 * 参  数：[in] msg_data 消息
 * 返回值：消息是否继续分发
------------------------------------------------------------------------------*/
bool AvManager::OnAvConfigMsg(const MsgData& msg_data)
{
	LOG(_T("AvManager::OnAvConfigMsg.\n"));

	m_av_config = std::static_pointer_cast<AvConfigMsg>(msg_data);
	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：通知接收远端用户音视频数据消息处理
 * 参  数：[in] msg_data 消息
 * 返回值：消息是否继续分发
------------------------------------------------------------------------------*/
bool AvManager::OnStartRecvMediaMsg(const MsgData& msg_data)
{
	StartRecvMediaMsgSP recv_msg =
		std::static_pointer_cast<StartRecvMediaMsg>(msg_data);

	for each (MediaInfo media_info in recv_msg->media_infos)
	{
		FS_UINT32 render_id = 0;
		if (media_info.media_type == 2)
		{
			HWND hWnd = ::GetShellWindow();
			FS_UINT32 render_id = m_remote_video_render->AddRender(hWnd, NULL);
		}
		
		if (media_info.media_state == 0) // 0: STATE_NONE
		{
			HRESULT hr = m_av_mp->StopRecvMedia(
				recv_msg->user_id,
				media_info.media_type,
				media_info.media_id);
			if (FAILED(hr))
			{
				LOG(_T("Failed to stop recv media, media_type = %d, media_id = %d.\n"),
					media_info.media_type, media_info.media_id);
			}
		}
		else
		{

			HRESULT hr = m_av_mp->StartRecvMedia(
				recv_msg->user_id,
				media_info.media_type,
				media_info.media_id,
				render_id);
			if (FAILED(hr))
			{
				LOG(_T("Failed to start recv media, media_type = %d, media_id = %d.\n"),
					media_info.media_type, media_info.media_id);
			}
		}
	}

	return false;
}