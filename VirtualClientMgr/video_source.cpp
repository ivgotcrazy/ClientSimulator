#include "stdafx.h"
#include "video_source.h"
#include "framework.h"

#define NO_CAPTURING_DEV	0xFFFFFFFF
#define INVALID_RENDER_ID	0xFFFFFFFF

VideoSource::VideoSource(IComponentFactory* factory, VideoParamInfo video_param)
	: m_facotry(factory)
	, m_video_param(video_param)
	, m_video_dev_count(0)
	, m_capturing_dev_index(NO_CAPTURING_DEV)
	, m_render_id(INVALID_RENDER_ID)
{
	ZeroMemory(m_video_devs, sizeof(m_video_devs));
	ZeroMemory(m_video_renders, sizeof(m_video_renders));
}

VideoSource::~VideoSource()
{
	StopCapture();
}

bool VideoSource::Init()
{
	int i = 0;
	do
	{
		HRESULT hr = m_facotry->CreateComponent(
			CLSID_VideoDevice, IID_IVideoDevice, NULL, (void**)&m_video_devs[i]);
		if (FAILED(hr))
		{
			LOG(_T("Create Video Device Component Failed.\n"));
			return false;
		}

		if (m_video_dev_count == 0)
		{
			m_video_dev_count = m_video_devs[0] == NULL ? 0 : m_video_devs[0]->GetCapDevicesCount();
			if (m_video_dev_count == 0 && m_video_devs[0])
			{
				m_video_devs[0]->Release();
				m_video_devs[0] = NULL;
				return true;
			}
			if (m_video_dev_count > 6)
				m_video_dev_count = 6;
		}
		hr = m_video_devs[i]->QueryInterface(IID_IVideoRenderManager, (void**)&m_video_renders[i]);
		if (FAILED(hr))
		{
			LOG(_T("Query Local VideoRenderManager Interface Failed.\n"));
		}
		i++;
	} while (m_video_devs[0] != NULL && i < m_video_dev_count);

	return true;
}

bool VideoSource::StartCapture(const VideoDevCapParam& cap_param, HWND hWnd)
{
	if (m_video_dev_count == 0)
	{
		LOG(_T("None video device.\n"));
		return false;
	}

	if (cap_param.dev_index >= m_video_dev_count)
	{
		LOG(_T("Invalid video device index = %u.\n"), cap_param.dev_index);
		return false;
	}

	// 设备已经在采集中，直接返回
	if (cap_param.dev_index == m_capturing_dev_index)
		return true;

	// 其他设备在采集中，需要先停止其他设备 
	StopCapture();

	Video_CapEnc_Param param = GetCapEncParam(cap_param);
	HRESULT hr = m_video_devs[cap_param.dev_index]->StartCapture(&param);
	if (FAILED(hr))
	{
		LOG(_T("Failed to start capturing video device.\n"));
		m_capturing_dev_index = NO_CAPTURING_DEV;
		return false;
	}
	m_capturing_dev_index = cap_param.dev_index;

	// 渲染
	if (hWnd != NULL)
		AddRender(m_capturing_dev_index, hWnd);

	return true;
}

Video_CapEnc_Param VideoSource::GetCapEncParam(const VideoDevCapParam& cap_param)
{
	Video_CapEnc_Param param;
	ZeroMemory(&param, sizeof(param));
	param.CapParam.nCapDevIndex = cap_param.dev_index;
	param.CapParam.nFrameRate = cap_param.frame_rate;
	param.CapParam.nWidth = cap_param.width;
	param.CapParam.nHeight = cap_param.height;
	param.CapParam.nVideoInputIndex = 0;
	param.CapParam.nVideoStandand = VIDEO_STANDAND_PAL;

	param.EncParam.nBitRate = cap_param.bit_rate;
	param.EncParam.nEncoderID = VIDEO_CODEC_H264;
	param.EncParam.nEncoderMode = cap_param.encode_mode;
	param.EncParam.nFrameRate = cap_param.frame_rate;
	param.EncParam.nKeyFrameInterval = cap_param.frame_rate * 2;
	param.EncParam.nQuality = 100;
	param.EncParam.nVBRQuality = 80;

	return param;
}

void VideoSource::StopCapture()
{
	if (m_video_dev_count == 0)
	{
		LOG(_T("Cannot stop device, none video device.\n"));
		return;
	}

	if (m_capturing_dev_index == NO_CAPTURING_DEV)
		return;

	if (m_capturing_dev_index >= m_video_dev_count)
	{
		LOG(_T("Cannot stop device, invalid capturing video device = %u.\n"), m_capturing_dev_index);
		return;
	}

	if (m_render_id != INVALID_RENDER_ID)
	{
		HRESULT hr = m_video_renders[m_capturing_dev_index]->RemoveRender(m_render_id);
		if (FAILED(hr))
		{
			LOG(_T("Failed to remove render = %u.\n"), m_render_id);
		}
		m_render_id = INVALID_RENDER_ID;
	}
		
	HRESULT hr = m_video_devs[m_capturing_dev_index]->StopCapture();
	if (FAILED(hr))
	{
		LOG(_T("Failed to stop capturing video device.\n"));
	}

	m_capturing_dev_index = NO_CAPTURING_DEV;
}

VideoDevNameVec VideoSource::GetVideoDeviceNames()
{
	VideoDevNameVec dev_vec;

	WCHAR szDevName[128];
	for (int i = 0; i < m_video_dev_count; i++)
	{
		assert(m_video_devs[0] != NULL);
		HRESULT hr = m_video_devs[0]->GetCapDeviceInfo(i, szDevName, 128);
		if (SUCCEEDED(hr))
		{
			dev_vec.push_back(szDevName);
		}
		else
		{
			LOG(_T("Failed to get device info, index = %u.\n"), i);
			continue;
		}
	}
	
	return dev_vec;
}

IVideoDevice* VideoSource::GetVideoDevice(FS_UINT32 dev_index)
{
	if (dev_index >= m_video_dev_count)
		return nullptr;

	return m_video_devs[dev_index];
}

void VideoSource::AddRender(FS_UINT32 dev_index, HWND hWnd)
{
	WBASE_NOTIFY notify;
	notify.nNotifyMode = WBASE_NOTIFYMODE_NONE;
	notify.CallbackMode.dwUserData = (FS_UINT)this;
	notify.CallbackMode.pCallback = NULL;
	notify.CallbackMode.nMsgID = 10000;

	m_render_id = m_video_renders[dev_index]->AddRender(hWnd, &notify);
}

bool VideoSource::SetVideoParam(VideoDevCapParam& cap_param)
{
	if (cap_param.dev_index != m_capturing_dev_index)
	{
		LOG(_T("Set video param with invalid device index =  %u.\n"), cap_param.dev_index);
		return false;
	}
		
	Video_CapEnc_Param param = GetCapEncParam(cap_param);
	HRESULT hr = m_video_devs[m_capturing_dev_index]->SetParam(&param);
	if (FAILED(hr))
	{
		LOG(_T("Failed to set param of video device = %u.\n"), cap_param.dev_index);
		return false;
	}
	
	return true;
}