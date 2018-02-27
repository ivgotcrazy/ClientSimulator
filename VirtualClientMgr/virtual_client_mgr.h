#pragma once

#include <atomic>
#include "define.h"
#include "video_source.h"
#include "audio_source.h"
#include "virtual_client.h"
#include "global_config_mgr.h"

namespace clientmgr
{

class VirtualClientMgr
	: public CommonMsgProcessor
	, public std::enable_shared_from_this < VirtualClientMgr >
{
public:
	VirtualClientMgr();

	bool Init(IComponentFactory* factory);

	bool Start();
	bool Stop();
	void OnTimer();

	// 对外接口
	VideoDevNameVec GetVideoDeviceNames();
	AudioDevNameVec GetAudioCapDevNames();

private:
	bool CreateBaseComponents(IComponentFactory* factory);
	bool OnPreviewVideoDev(const MsgData& msg_data);
	bool OnSetVideoParam(const MsgData& msg_data);
	bool OnSetAudioParam(const MsgData& msg_data);
	void ThreadProc();
	void WaitForContinueLogin();
	bool OnUserLoginResultMsg(const MsgData& msg_data);
	VirtualClientSP BuildNewVirtualClient(const UserInfo& user_info);

private:
	ClientBaseComponents	m_base_comps;

	typedef std::vector<VirtualClientSP> VirtualClientVec;
	VirtualClientVec m_login_clients;

	VideoSrcType			m_video_src_type;

	typedef std::shared_ptr<VideoSource> VideoSourceSP;
	VideoSourceSP			m_video_source;

	typedef std::shared_ptr<AudioSource> AudioSourceSP;
	AudioSourceSP			m_audio_source;

	std::thread				m_login_thread;
	std::mutex				m_client_mutex;
	std::condition_variable m_login_contiue_cond;

	std::atomic_long m_concurrent_login_count;
	std::atomic_long m_current_second_login_count;

	FS_UINT32 m_next_login_user_index;

	bool m_thread_stop_flag;
	bool m_start_flag;
};

typedef std::shared_ptr<VirtualClientMgr> VirtualClientMgrSP;

}