#include "stdafx.h"
#include "audio_source.h"

#define DEV_NAME_LEN	256

typedef struct{
	int				nCapDevIndex;
	int				nPlayDevIndex;
	int				nCapInput;
	int				nCapVolume;
	int				nPlayVolume;
	BOOL			bCapVolumeAutoAdjust;
	int				nEncoderID;
	int				nAEC;
	int				nANS;
	int				nFEC;
	int				nAGC;
	int				nVAD;
	BOOL			bAutoAdjust;
	int				bAudioEngine;
	tstring			strLastCapDevName;
	tstring			strLastPlayDevName;
}AudioParam;

AudioSource::AudioSource(IComponentFactory* factory)
	: m_audio_dev(nullptr)
	, m_facotry(factory)
	, m_cur_dev_index(0)
{

}

bool AudioSource::Init()
{
	HRESULT hr = m_facotry->CreateComponent(CLSID_AudioDevice, 
		IID_IAudioDevice, NULL, (void**)&m_audio_dev);
	if (FAILED(hr))
	{
		LOG(_T("Create Audio Device Component Failed.\n"));
		return false;
	}

	AudioParam param;
	ZeroMemory(&param, sizeof(param));
	param.bAudioEngine = 0;	// 0: Normal, 1: CPVE
	param.bAutoAdjust = TRUE;
	param.bCapVolumeAutoAdjust = FALSE;
	param.nAEC = 1;
	param.nAGC = 0;
	param.nANS = 1;
	param.nFEC = 1;
	param.nVAD = 0;
	param.nEncoderID = 6; // G7221 24 kbps
	param.nCapDevIndex = 0;
	param.nPlayDevIndex = 0;
	param.nCapVolume = 100;
	param.nPlayVolume = 100;

	hr = m_audio_dev->SetAudioEngine(param.bAudioEngine);
	if (FAILED(hr))
	{
		LOG(_T("Create Audio Device Component Failed.\n"));
		return false;
	}

	hr = m_audio_dev->StartAudioDevice(param.nCapDevIndex, param.nPlayDevIndex);
	if (FAILED(hr))
	{
		LOG(_T("Failed to start audio device.\n"));
		return false;
	}

	m_audio_dev->SetCapInputType(param.nCapInput);
	m_audio_dev->SetCapVolume(param.nCapVolume);
	m_audio_dev->SetPlayVolume(param.nPlayVolume);
	m_audio_dev->SetCapMute(FALSE);
	m_audio_dev->SetPlayMute(FALSE);
	m_audio_dev->SetParam(AUDIO_PARAM_AEC, (void*)&param.nAEC, sizeof(param.nAEC));
	m_audio_dev->SetParam(AUDIO_PARAM_ANS, (void*)&param.nANS, sizeof(param.nANS));
	m_audio_dev->SetParam(AUDIO_PARAM_VAD, (void*)&param.nVAD, sizeof(param.nVAD));
	m_audio_dev->SetParam(AUDIO_PARAM_AGC, (void*)&param.nAGC, sizeof(param.nAGC));
	//m_audio_dev->SetParam( AUDIO_PARAM_FEC,(void*)&param.nFEC,sizeof(param.nFEC) );
	m_audio_dev->SetParam(AUDIO_PARAM_ENCODER, (void*)&param.nEncoderID, sizeof(param.nEncoderID));
	m_audio_dev->SetParam(AUDIO_PARAM_CAPAUTOVOLUME, (void*)&param.bCapVolumeAutoAdjust, sizeof(param.bCapVolumeAutoAdjust));

	return true;
}

bool AudioSource::StartCapture(int dev_index)
{
	if (m_audio_dev == nullptr)
		return false;

	if (dev_index >= m_audio_dev->GetCapDevicesCount())
	{
		LOG(_T("Invalid audio device index = %d.\n"), dev_index);
		return false;
	}

	HRESULT hr = m_audio_dev->StartCapture(dev_index);
	if (FAILED(hr))
	{
		LOG(_T("Failed to start capturing audio device = %d.\n"), dev_index);
		return false;
	}

	return true;
}

void AudioSource::StopCapture()
{
	if (m_audio_dev != nullptr)
	{
		if (FAILED(m_audio_dev->StopCapture()))
		{
			LOG(_T("Failed to stop capturing audio device."));
		}
	}
}

IAudioDevice* AudioSource::GetAudioDevice()
{
	return m_audio_dev;
}

AudioDevNameVec AudioSource::GetAudioCapDevices()
{
	AudioDevNameVec audio_devs;

	if (m_audio_dev != nullptr)
	{
		int dev_count = m_audio_dev->GetCapDevicesCount();
		for (int i = 0; i < dev_count; i++)
		{
			WCHAR szDevName[DEV_NAME_LEN];
			if (FAILED(m_audio_dev->GetCapDeviceInfo(i, szDevName, DEV_NAME_LEN)))
			{
				LOG(_T("Failed to get audio device info, index = %d.\n"), i);
				continue;
			}
			audio_devs.push_back(szDevName);
		}
	}

	return audio_devs;
}

bool AudioSource::SetAudioCapDevParam(const AudioCapDevParam& cap_param)
{
	return true;
}