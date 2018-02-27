/*##############################################################################
 * �ļ���room_data_mgr.h
 * ������RoomDataMgr����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include <vector>
#include <map>
#include "client_core_define.h"

namespace clientcore
{

/*==============================================================================
 * �������������������ݣ������������á���Ϣ���û��ȣ����崦�������ģ��
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

	// �����û��Ķ�����Ϣ
	FS_INT32		m_local_user_id;
	std::string		m_local_user_token;
	VerifyMode		m_local_user_verify_mode;

	UserDataMap		m_room_user_map;	// �����û��б�
	RoomInfo		m_room_info;		// ���������
	RoomConfig		m_room_config;		// �ͻ�������

	// ��������ķ��񣬱�������Ƶ������Ļ�������ȡ�
	RoomSrvInfo		m_room_srv_info;

	// �������Ƶ��������
	VideoParam		m_video_param;

	// ������Ϣ
	DeptNodeList	m_dept;
	DeptNodeList	m_node;

};

}