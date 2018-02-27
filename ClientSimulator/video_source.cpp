#include "stdafx.h"
#include "video_source.h"
#include "framework.h"

VideoSource::VideoSource(IComponentFactory* factory, VideoParamInfo video_param)
	: m_facotry(factory)
	, m_video_param(video_param)
	, m_video_dev_count(0)
{

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
				return false;
			}
			if (m_video_dev_count > 6)
				m_video_dev_count = 6;
		}

		i++;
	} while (m_video_devs[0] != NULL && i < m_video_dev_count);

	return true;
}

bool VideoSource::Start()
{
	if (!Init())
	{
		LOG(_T("Failed to start VideoSource.\n"));
		return false;
	}

	if (m_video_dev_count == 0)
	{
		LOG(_T("None video device.\n"));
		return false;
	}

	Video_CapEnc_Param param;
	ZeroMemory(&param, sizeof(param));
	param.CapParam.nCapDevIndex = 0;
	param.CapParam.nFrameRate = m_video_param.frame_rate;
	param.CapParam.nWidth = m_video_param.width;
	param.CapParam.nHeight = m_video_param.height;
	param.CapParam.nVideoInputIndex = 0;
	param.CapParam.nVideoStandand = VIDEO_STANDAND_PAL;

	param.EncParam.nBitRate = m_video_param.bit_rate;
	param.EncParam.nEncoderID = VIDEO_CODEC_WMV9;
	param.EncParam.nEncoderMode = VIDEO_ENCODER_MODE_ABR;
	param.EncParam.nFrameRate = m_video_param.frame_rate;
	param.EncParam.nKeyFrameInterval = m_video_param.frame_rate * 2;
	param.EncParam.nQuality = 100;
	param.EncParam.nVBRQuality = 80;

	HRESULT hr = m_video_devs[0]->StartCapture(&param);
	if (FAILED(hr))
	{
		LOG(_T("Failed to start capturing video device.\n"));
		return false;
	}

	return true;
}

bool VideoSource::Stop()
{
	if (m_video_dev_count == 0)
	{
		LOG(_T("None video device.\n"));
		return false;
	}

	HRESULT hr = m_video_devs[0]->StopCapture();
	if (FAILED(hr))
	{
		LOG(_T("Failed to stop capturing video device.\n"));
		return false;
	}

	return true;
}

IVideoDevice* VideoSource::GetVideoDevice() const
{
	return m_video_devs[0]; // 默认取第一个视频设备 
}