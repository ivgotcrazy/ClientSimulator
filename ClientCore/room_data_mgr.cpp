/*##############################################################################
 * 文件：room_data_mgr.cpp
 * 描述：RoomDataMgr实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "room_data_mgr.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
RoomDataMgr::RoomDataMgr()
	: m_local_user_id(-1)
	, m_room_id(0)
	, m_local_user_verify_mode(VERIFY_MODE_INVALID)
{
}

/*------------------------------------------------------------------------------
 * 描  述：设置节点ID
 * 参  数：[in] node_id 节点ID
 * 返回值：无
------------------------------------------------------------------------------*/
void RoomDataMgr::SetLocalNodeId(const std::string& node_id)
{
	m_local_node_id = node_id;
}

/*------------------------------------------------------------------------------
 * 描  述：设置用户ID
 * 参  数：[in] user_id 用户ID
 * 返回值：无
------------------------------------------------------------------------------*/
void RoomDataMgr::SetLocalUserId(FS_UINT32 user_id)
{
	m_local_user_id = user_id;

	// TODO: UserData未初始化，有风险
	m_room_user_map.insert(std::make_pair(user_id, UserData()));
}

/*------------------------------------------------------------------------------
 * 描  述：获取用户ID
 * 参  数：无
 * 返回值：用户ID
------------------------------------------------------------------------------*/
FS_UINT32 RoomDataMgr::GetLocalUserId() const
{
	return m_local_user_id;
}

/*------------------------------------------------------------------------------
 * 描  述：获取节点ID
 * 参  数：无
 * 返回值：节点ID
------------------------------------------------------------------------------*/
std::string RoomDataMgr::GetLocalNodeId() const
{
	return m_local_node_id;
}

/*------------------------------------------------------------------------------
 * 描  述：登录前置房间响应消息处理
 * 参  数：[in] rep_msg 响应消息
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool RoomDataMgr::OnLoginFrontRoomRep(const LoginFrontRoomRepMsgSP& rep_msg)
{
	if (m_local_user_id != rep_msg->room_user_id)
	{
		LOG(_T("Invalid local user id = %d.\n"), rep_msg->room_user_id);
		return false;
	}

	auto iter = m_room_user_map.find(m_local_user_id);
	if (iter == m_room_user_map.end())
	{
		LOG(_T("Cannot find user.\n"));
		return false;
	}

	m_local_user_token = rep_msg->token;
	m_local_user_verify_mode = rep_msg->verify_mode;
	m_room_srv_node_id = rep_msg->room_srv_node_id;

	iter->second.m_room_user_info.bUserRight = rep_msg->user_right;

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：登录房间响应消息处理 
 * 参  数：[in] rep_msg 响应消息
 * 返回值：成功/失败 
------------------------------------------------------------------------------*/
bool RoomDataMgr::OnLoginRoomRep(const LoginRoomRepMsgSP& rep_msg)
{
	auto iter = m_room_user_map.find(m_local_user_id);
	if (iter == m_room_user_map.end())
	{
		LOG(_T("Cannot find user.\n"));
		return false;
	}

	m_room_info		= rep_msg->room_info;
	m_room_config	= rep_msg->room_config;
	m_room_srv_info = rep_msg->room_srv_info;
	m_video_param	= rep_msg->video_param;

	iter->second.m_room_user_info = rep_msg->room_user_info;

	m_dept = rep_msg->dept;
	m_node = rep_msg->node;

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：获取房间信息
 * 参  数：无
 * 返回值：房间信息
------------------------------------------------------------------------------*/
const RoomSrvInfo& RoomDataMgr::GetRoomSrvInfo() const
{
	return m_room_srv_info;
}

/*------------------------------------------------------------------------------
 * 描  述：更新音视频设备消息处理 
 * 参  数：[in] refresh_msg 更新消息
 * 返回值：成功/失败 
------------------------------------------------------------------------------*/
bool RoomDataMgr::OnRefreshAvDevices(const RefreshAvDevicesMsgSP& refresh_msg)
{
	auto iter = m_room_user_map.find(m_local_user_id);
	if (iter == m_room_user_map.end())
	{
		LOG(_T("Cannot find user.\n"));
		return false;
	}

	// 音频通道
	iter->second.m_audio_channel.cap_dev_index	= refresh_msg->audio_dev.dev_index;
	iter->second.m_audio_channel.dev_name		= refresh_msg->audio_dev.dev_name;
	iter->second.m_audio_channel.has_audio		= true;
	iter->second.m_audio_channel.media_id		= 0;
	iter->second.m_audio_channel.media_state	= 0;
	iter->second.m_audio_channel.operation		= 1;
	iter->second.m_audio_channel.source_id		= 1;

	// 视频通道
	for (int i = 0; i < refresh_msg->video_devs.size(); i++)
	{
		VideoChannel video_channel;
		video_channel.cap_dev_index = refresh_msg->video_devs[i].dev_index;
		video_channel.dev_name		= refresh_msg->video_devs[i].dev_name;
		video_channel.has_video		= true;
		video_channel.media_id		= i;
		video_channel.media_state	= 0;
		video_channel.operation		= 1;
		video_channel.recv_video	= 0;

		iter->second.m_video_channels.insert(std::make_pair(i, video_channel));
	}

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：获取本地用户音频通道
 * 参  数：无
 * 返回值：音频通道
------------------------------------------------------------------------------*/
const AudioChannel& RoomDataMgr::GetLocalUserAudioChannel() const
{
	auto iter = m_room_user_map.find(m_local_user_id);
	if (iter == m_room_user_map.end())
	{
		assert(false);
		LOG(_T("Cannot find user.\n"));
	}

	return iter->second.m_audio_channel;
}

/*------------------------------------------------------------------------------
 * 描  述：获取本地用户视频通道
 * 参  数：无
 * 返回值：视频通道
------------------------------------------------------------------------------*/
const VideoChannelMap& RoomDataMgr::GetLocalUserVideoChannels() const
{
	auto iter = m_room_user_map.find(m_local_user_id);
	if (iter == m_room_user_map.end())
	{
		assert(false);
		LOG(_T("Cannot find user.\n"));
	}

	return iter->second.m_video_channels;
}

/*------------------------------------------------------------------------------
 * 描  述：获取RoomSrvNodeId
 * 参  数：无
 * 返回值：RoomSrvNodeId
------------------------------------------------------------------------------*/
std::string RoomDataMgr::GetRoomSrvNodeId() const
{
	return m_room_srv_node_id;
}

/*------------------------------------------------------------------------------
 * 描  述：获取用户登录Token
 * 参  数：无
 * 返回值：Token
------------------------------------------------------------------------------*/
std::string RoomDataMgr::GetLocalUserToken() const
{
	return m_local_user_token;
}

/*------------------------------------------------------------------------------
 * 描  述：获取指定用户信息
 * 参  数：[in] user_id 用户ID
 *         [out] user_info 用户信息
 * 返回值：成功/失败，是否找到用户
------------------------------------------------------------------------------*/
bool RoomDataMgr::GetRoomUserInfo(FS_UINT32 user_id, RoomUserInfo* user_info) const
{
	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：获取用户验证模式
 * 参  数：无
 * 返回值：用户验证模式
------------------------------------------------------------------------------*/
VerifyMode RoomDataMgr::GetVerifyMode() const
{
	return m_local_user_verify_mode;
}

/*------------------------------------------------------------------------------
 * 描  述：获取会议室ID
 * 参  数：无
 * 返回值：会议室ID
------------------------------------------------------------------------------*/
FS_UINT32 RoomDataMgr::GetRoomId() const
{
	return m_room_id;
}