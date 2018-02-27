/*##############################################################################
 * 文件：room_data_mgr.h
 * 描述：RoomDataMgr定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include <vector>
#include <map>
#include "client_core_define.h"

namespace clientcore
{

/*==============================================================================
 * 描述：管理会议相关数据，包括会议配置、信息、用户等，定义处理的数据模型
==============================================================================*/
class RoomDataMgr
{
public:
	RoomDataMgr();

	void SetLocalNodeId(const std::string& node_id);
	void SetLocalUserId(FS_UINT32 user_id);

	FS_UINT32	GetLocalUserId() const;
	std::string GetLocalNodeId() const;
	std::string GetRoomSrvNodeId() const;
	std::string GetLocalUserToken() const;
	VerifyMode	GetVerifyMode() const;
	bool		GetRoomUserInfo(FS_UINT32 user_id, RoomUserInfo* user_info) const;
	FS_UINT32	GetRoomId() const;

	const RoomSrvInfo& GetRoomSrvInfo() const;

	const AudioChannel& GetLocalUserAudioChannel() const;
	const VideoChannelMap& GetLocalUserVideoChannels() const;

	bool OnLoginFrontRoomRep(const LoginFrontRoomRepMsgSP& rep_msg);
	bool OnLoginRoomRep(const LoginRoomRepMsgSP& rep_msg);
	bool OnRefreshAvDevices(const RefreshAvDevicesMsgSP& refresh_msg);
	
private:
	struct UserData
	{
		RoomUserInfo	m_room_user_info;
		AudioChannel	m_audio_channel;
		VideoChannelMap	m_video_channels;
	};

	typedef std::map<FS_UINT32, UserData> UserDataMap;

	FS_UINT32		m_room_id;
	std::string		m_local_node_id;
	std::string		m_room_srv_node_id;

	// 本地用户的额外信息
	FS_INT32		m_local_user_id;
	std::string		m_local_user_token;
	VerifyMode		m_local_user_verify_mode;

	UserDataMap		m_room_user_map;	// 会议用户列表
	RoomInfo		m_room_info;		// 服务端配置
	RoomConfig		m_room_config;		// 客户端配置

	// 会议包含的服务，比如音视频服务、屏幕共享服务等。
	RoomSrvInfo		m_room_srv_info;

	// 会议的视频参数设置
	VideoParam		m_video_param;

	// 部门信息
	DeptNodeList	m_dept;
	DeptNodeList	m_node;

};

}