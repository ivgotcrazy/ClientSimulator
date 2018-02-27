#pragma once


#include "IAudioDevice.h"
#include "define.h"
#include "client_core_define.h"

using namespace clientmgr;

class AudioSource
{
public:
	AudioSource(IComponentFactory* factory);
	
	bool Init();
	bool StartCapture(int dev_index);
	void StopCapture();

	IAudioDevice* GetAudioDevice();
	AudioDevNameVec GetAudioCapDevices();

	bool SetAudioCapDevParam(const AudioCapDevParam& cap_param);

private:
	IAudioDevice* m_audio_dev;
	IComponentFactory* m_facotry;
	FS_UINT32 m_cur_dev_index;
};