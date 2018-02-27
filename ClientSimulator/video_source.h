#pragma once

#include "IVideoDevice.h"
#include "define.h"

class VideoSource
{
public:
	VideoSource(IComponentFactory* factory, VideoParamInfo video_param);

	bool Start();
	bool Stop();

	IVideoDevice* GetVideoDevice() const;

private:
	bool Init();

private:
	IVideoDevice* m_video_devs[6];
	FS_UINT32 m_video_dev_count;

	IComponentFactory* m_facotry;
	VideoParamInfo	m_video_param;
};