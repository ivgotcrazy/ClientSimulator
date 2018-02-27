/*##############################################################################
 * �ļ���av_manager.h
 * ������AvManager�����ļ�
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
 * ����������Ƶ������ش����ڲ�������AVCore�ĵ��á����⣬�˶�����һ�����б�Ե
 *       ��Ϣ������������������Ϣ���ڴ˴��ᾭ���߳�ת����
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