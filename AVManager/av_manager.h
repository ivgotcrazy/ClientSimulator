/*##############################################################################
 * 文件：av_manager.h
 * 描述：AvManager声明文件
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "up_board_msg_processor.h"
#include "meeting_core_define.h"
#include "IVirtualVideoDevice.h"
#include "IVideoSource.h"

class IAudioDevice;
class IVideoDevice;
class IVideoRenderManager;
class IMultiAVMP;

namespace meetingcore
{

/*==============================================================================
 * 描述：音视频处理相关处理，内部隐藏了AVCore的调用。另外，此对象是一个上行边缘
 *       消息处理器，所有上行消息，在此处会经过线程转换。
==============================================================================*/
class AvManager : public UpBoardMsgProcessor
{
public:
	AvManager(const ClientStateMachineSP& state_machine);

	bool Init();
	void OnAvMpNotify(UINT nMsgID, DWORD wParam, DWORD lParam, DWORD dwReserved);

private:
	bool CreateAvComponent();
	bool OnCreateAvComponentMsg(const MsgData& msg_data);
	bool OnLoginAvRoomMsg(const MsgData& msg_data);
	bool OnAvConfigMsg(const MsgData& msg_data);
	void RefreshAvDevices();
	bool OnStartRecvMediaMsg(const MsgData& msg_data);

private:
	IComponentFactory*		m_factory;
	IAudioDevice*			m_audio_dev;
	IVideoDevice*			m_video_devs[16];
	IVideoRenderManager*	m_local_video_renders[16];
	IMultiAVMP*				m_av_mp;
	IVideoRenderManager*	m_remote_video_render;
	AvConfigMsgSP			m_av_config;
	ClientStateMachineSP	m_state_machine;
};

}