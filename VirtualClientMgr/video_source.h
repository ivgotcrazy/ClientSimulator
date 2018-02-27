#pragma once

#include "IVideoDevice.h"
#include "define.h"
#include "client_core_define.h"

using namespace clientmgr;


class VideoSource
{
public:
	VideoSource(IComponentFactory* factory, VideoParamInfo video_param);
	~VideoSource();

	bool Init();
	bool StartCapture(const VideoDevCapParam& cap_param, HWND hWnd);
	void StopCapture();
	bool SetVideoParam(VideoDevCapParam& cap_param);
	
	VideoDevNameVec GetVideoDeviceNames();
	IVideoDevice* GetVideoDevice(FS_UINT32 dev_index);

private:
	void AddRender(FS_UINT32 dev_index, HWND hWnd);
	Video_CapEnc_Param GetCapEncParam(const VideoDevCapParam& cap_param);

private:
	IVideoDevice* m_video_devs[6];
	IVideoRenderManager* m_video_renders[6];

	FS_UINT32 m_video_dev_count;

	FS_UINT32 m_render_id;

	FS_UINT32 m_capturing_dev_index;

	IComponentFactory* m_facotry;
	VideoParamInfo	m_video_param;
};