/*##############################################################################
 * �ļ���room_data_mgr.cpp
 * ������RoomDataMgrʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "room_data_mgr.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
RoomDataMgr::RoomDataMgr()
	: m_local_user_id(-1)
	, m_room_id(0)
	, m_local_user_verify_mode(VERIFY_MODE_INVALID)
{
}

/*------------------------------------------------------------------------------
 * ��  �������ýڵ�ID
 * ��  ����[in] node_id �ڵ�ID
 * ����ֵ����
------------------------------------------------------------------------------*/
void RoomDataMgr::SetLocalNodeId(const std::string& node_id)
{
	m_local_node_id = node_id;
}

/*------------------------------------------------------------------------------
 * ��  ���������û�ID
 * ��  ����[in] user_id �û�ID
 * ����ֵ����
------------------------------------------------------------------------------*/
void RoomDataMgr::SetLocalUserId(FS_UINT32 user_id)
{
	m_local_user_id = user_id;

	// TODO: UserDataδ��ʼ�����з���
	m_room_user_map.insert(std::make_pair(user_id, UserData()));
}

/*------------------------------------------------------------------------------
 * ��  ������ȡ�û�ID
 * ��  ������
 * ����ֵ���û�ID
------------------------------------------------------------------------------*/
FS_UINT32 RoomDataMgr::GetLocalUserId() const
{
	return m_local_user_id;
}

/*------------------------------------------------------------------------------
 * ��  ������ȡ�ڵ�ID
 * ��  ������
 * ����ֵ���ڵ�ID
------------------------------------------------------------------------------*/
std::string RoomDataMgr::GetLocalNodeId() const
{
	return m_local_node_id;
}

/*------------------------------------------------------------------------------
 * ��  ������¼ǰ�÷�����Ӧ��Ϣ����
 * ��  ����[in] rep_msg ��Ӧ��Ϣ
 * ����ֵ���ɹ�/ʧ��
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
 * ��  ������¼������Ӧ��Ϣ���� 
 * ��  ����[in] rep_msg ��Ӧ��Ϣ
 * ����ֵ���ɹ�/ʧ�� 
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
 * ��  ������ȡ������Ϣ
 * ��  ������
 * ����ֵ��������Ϣ
------------------------------------------------------------------------------*/
const RoomSrvInfo& RoomDataMgr::GetRoomSrvInfo() const
{
	return m_room_srv_info;
}

/*------------------------------------------------------------------------------
 * ��  ������������Ƶ�豸��Ϣ���� 
 * ��  ����[in] refresh_msg ������Ϣ
 * ����ֵ���ɹ�/ʧ�� 
------------------------------------------------------------------------------*/
bool RoomDataMgr::OnRefreshAvDevices(const RefreshAvDevicesMsgSP& refresh_msg)
{
	auto iter = m_room_user_map.find(m_local_user_id);
	if (iter == m_room_user_map.end())
	{
		LOG(_T("Cannot find user.\n"));
		return false;
	}

	// ��Ƶͨ��
	iter->second.m_audio_channel.cap_dev_index	= refresh_msg->audio_dev.dev_index;
	iter->second.m_audio_channel.dev_name		= refresh_msg->audio_dev.dev_name;
	iter->second.m_audio_channel.has_audio		= true;
	iter->second.m_audio_channel.media_id		= 0;
	iter->second.m_audio_channel.media_state	= 0;
	iter->second.m_audio_channel.operation		= 1;
	iter->second.m_audio_channel.source_id		= 1;

	// ��Ƶͨ��
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
 * ��  ������ȡ�����û���Ƶͨ��
 * ��  ������
 * ����ֵ����Ƶͨ��
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
 * ��  ������ȡ�����û���Ƶͨ��
 * ��  ������
 * ����ֵ����Ƶͨ��
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
 * ��  ������ȡRoomSrvNodeId
 * ��  ������
 * ����ֵ��RoomSrvNodeId
------------------------------------------------------------------------------*/
std::string RoomDataMgr::GetRoomSrvNodeId() const
{
	return m_room_srv_node_id;
}

/*------------------------------------------------------------------------------
 * ��  ������ȡ�û���¼Token
 * ��  ������
 * ����ֵ��Token
------------------------------------------------------------------------------*/
std::string RoomDataMgr::GetLocalUserToken() const
{
	return m_local_user_token;
}

/*------------------------------------------------------------------------------
 * ��  ������ȡָ���û���Ϣ
 * ��  ����[in] user_id �û�ID
 *         [out] user_info �û���Ϣ
 * ����ֵ���ɹ�/ʧ�ܣ��Ƿ��ҵ��û�
------------------------------------------------------------------------------*/
bool RoomDataMgr::GetRoomUserInfo(FS_UINT32 user_id, RoomUserInfo* user_info) const
{
	return false;
}

/*------------------------------------------------------------------------------
 * ��  ������ȡ�û���֤ģʽ
 * ��  ������
 * ����ֵ���û���֤ģʽ
------------------------------------------------------------------------------*/
VerifyMode RoomDataMgr::GetVerifyMode() const
{
	return m_local_user_verify_mode;
}

/*------------------------------------------------------------------------------
 * ��  ������ȡ������ID
 * ��  ������
 * ����ֵ��������ID
------------------------------------------------------------------------------*/
FS_UINT32 RoomDataMgr::GetRoomId() const
{
	return m_room_id;
}