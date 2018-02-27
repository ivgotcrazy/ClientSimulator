/*##############################################################################
 * �ļ���client_core_mgr.h
 * ������ClientCoreMgrʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "client_core_mgr.h"
#include "meeting_core_define.h"
#include "client_state_machine.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
ClientCoreMgr::ClientCoreMgr(ClientBaseComponents* base_objs, 
	const ClientConfig& client_config)
	: m_base_objs(base_objs)
	, m_client_config(client_config)
{
}

/*------------------------------------------------------------------------------
 * ��  ������ʼ��
 * ��  ������
 * ����ֵ���ɹ�/ʧ��
------------------------------------------------------------------------------*/
bool ClientCoreMgr::Init()
{
	LOG(_T("ClientCoreMgr::Init.\n"));

	m_msg_converter.reset(new ThreadMsgConverter());
	SetMsgConverter(m_msg_converter);

	m_state_machine.reset(new ClientStateMachine(
		m_base_objs, m_msg_converter, m_client_config));

	// Up msg flow: ClientCoreMgr<-ClientStateMachine
	m_state_machine->SetUpMsgProcSuccessor(shared_from_this());

	// Down msg flow: ClientCoreMgr->ClientStateMachine
	SetDownMsgProcSuccessor(m_state_machine);

	// ������Ϣӳ��
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN, ClientCoreMgr::OnLoginReq);
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGOUT_ROOM, ClientCoreMgr::OnLogoutRoom);

	// ������Ϣӳ��
	UP_MSG_POST_MAP(UP_MSG_STATE_START,			ClientCoreMgr::OnStateStart);
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_REP,			ClientCoreMgr::OnLoginRep);
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_FRONT_ROOM_REP, ClientCoreMgr::OnLoginFrontRoomRep);
	UP_MSG_PRE_MAP(UP_MSG_LOGIN_ROOM_REP,		ClientCoreMgr::OnLoginRoomRep);
	UP_MSG_PRE_MAP(UP_MSG_REFRESH_AV_DEVICES,	ClientCoreMgr::OnRefreshAvDevices);
	UP_MSG_PRE_MAP(UP_MSG_USER_AV_INFO_NOTIFY,	ClientCoreMgr::OnUserAvInfoNotify);
	UP_MSG_PRE_MAP(UP_MSG_USER_STATE_CHANGED,	ClientCoreMgr::OnUserStateChanged);
	UP_MSG_PRE_MAP(UP_MSG_USER_ENTER_NOTIFY,	ClientCoreMgr::OnUserEnterNotify);

	return true;
}

/*------------------------------------------------------------------------------
 * ��  ����������¼
 * ��  ����[in] login_type ͨ���˲���ȷ����¼����
 * ����ֵ���ɹ�/ʧ��
------------------------------------------------------------------------------*/
bool ClientCoreMgr::Start(RoomLoginType login_type)
{
	LOG(_T("ClientCoreMgr::Start.\n"));
	
	if (!Init())
	{
		LOG(_T("Failed to init ClientCoreMgr.\n"));
		return false;
	}

	if (!m_state_machine->Start(login_type))
	{
		LOG(_T("Failed to start state machine.\n"));
		return false;
	}

	m_msg_converter->Start();

	return true;
}

/*------------------------------------------------------------------------------
 * ��  ����ֹͣ
 * ��  ������
 * ����ֵ���� 
------------------------------------------------------------------------------*/
void ClientCoreMgr::Stop()
{
	LOG(_T("ClientCoreMgr::Stop.\n"));

	if (m_state_machine)
		m_state_machine->Stop();

	if (m_msg_converter)
		m_msg_converter->Stop();
}

/*------------------------------------------------------------------------------
 * ��  �����û���¼��Ϣ������Ҫ��������ȡ�û���
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ���˴�ֻ�������ɴ�����Ҫ���¼����ַ�
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnLoginReq(const MsgData& msg_data)
{
	LoginReqMsgSP login_msg = std::static_pointer_cast<LoginReqMsg>(msg_data);

	// �����û�������û���
	m_user_name = login_msg->user_name;

	return true;
}

/*------------------------------------------------------------------------------
 * ��  �����û���¼ǰ�÷�������Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnLoginFrontRoomRep(const MsgData& msg_data)
{
	LoginFrontRoomRepMsgSP rep_msg = 
		std::static_pointer_cast<LoginFrontRoomRepMsg>(msg_data);

	if (rep_msg->login_result == 0) // ��¼�ɹ�
	{
		if (!m_room_data_mgr.OnLoginFrontRoomRep(rep_msg))
		{
			return false; // TODO:
		}
		else // ��¼ǰ�÷���ɹ���������¼���鷿��
		{
			SendLoginRoomReqMsg();
		}
	}

	return true;
}

/*------------------------------------------------------------------------------
 * ��  �����û���¼ǰ�ý����Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnLoginRep(const MsgData& msg_data)
{
	LoginRepMsgSP rep_msg = std::static_pointer_cast<LoginRepMsg>(msg_data);

	m_room_data_mgr.SetLocalUserId(rep_msg->local_user_id);
	m_room_data_mgr.SetLocalNodeId(rep_msg->local_node_id);

	return true;
}

/*------------------------------------------------------------------------------
 * ��  ����״̬��״̬��ʼ��Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnStateStart(const MsgData& msg_data)
{
	StateStartMsgSP start_msg = std::static_pointer_cast<StateStartMsg>(msg_data);

	if (start_msg->state_type == CLIENT_STATE_TYPE_MAIN_ROOM)
	{
		SendUserAvInfoMsg(); // �㲥��������Ƶ�豸��Ϣ
	}

	// ��丽����Ϣ
	start_msg->user_id = m_room_data_mgr.GetLocalUserId();

	return true; // �������Ϸ��ɴ���
}

/*------------------------------------------------------------------------------
 * ��  �����û���¼��������Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnLoginRoomRep(const MsgData& msg_data)
{
	LoginRoomRepMsgSP rep_msg = std::static_pointer_cast<LoginRoomRepMsg>(msg_data);

	if (rep_msg->login_result == 0)
	{
		if (!m_room_data_mgr.OnLoginRoomRep(rep_msg))
		{
			LOG(_T(""));
			return false; // TODO:	
		}
		SendLoginAvRoomMsg();
	}

	return true;
}

/*------------------------------------------------------------------------------
 * ��  �����ײ㴴������Ƶ�豸��ˢ����Ƶ�豸��Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnRefreshAvDevices(const MsgData& msg_data)
{
	std::shared_ptr<RefreshAvDevicesMsg> refresh_msg = 
		std::static_pointer_cast<RefreshAvDevicesMsg>(msg_data);

	if (!m_room_data_mgr.OnRefreshAvDevices(refresh_msg))
	{
		LOG(_T("Failed to call OnRefreshAvDevices.\n"));
	}

	return false; // �ϲ㲻��Ҫ�������Ϣ
}

/*------------------------------------------------------------------------------
 * ��  ���������û���������Ƶ�豸��Ϣ��Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnUserAvInfoNotify(const MsgData& msg_data)
{
	LOG(_T("ClientCoreMgr::OnUserAvInfoNotify.\n"));

	std::shared_ptr<UserAvInfoNotifyMsg> notify_msg =
		std::static_pointer_cast<UserAvInfoNotifyMsg>(msg_data);

	// TODO: ��δ����

	return false;
}

/*------------------------------------------------------------------------------
 * ��  �����û����������Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnUserEnterNotify(const MsgData& msg_data)
{
	UserEnterNotifyMsgSP enter_msg =
		std::static_pointer_cast<UserEnterNotifyMsg>(msg_data);

	for each(RoomUserInfo user_info in enter_msg->users)
	{
		StartRecvMediaMsgSP recv_msg(new StartRecvMediaMsg);
		recv_msg->user_id = user_info.dwUserID;

		if (user_info.audioChannel.has_audio && user_info.audioChannel.media_state != 0)
		{
			MediaInfo media_info;
			media_info.media_type = 1;
			media_info.media_id = user_info.audioChannel.media_id;
			media_info.media_state = user_info.audioChannel.media_state;
			recv_msg->media_infos.push_back(media_info);
		}

		for each(std::pair<DWORD, VideoChannel> item in user_info.vclMgr)
		{
			if (item.second.has_video && item.second.media_state != 0)
			{
				MediaInfo media_info;
				media_info.media_type = 2;
				media_info.media_id = item.second.media_id;
				media_info.media_state = item.second.media_state;
				recv_msg->media_infos.push_back(media_info);
			}
		}

		if (!recv_msg->media_infos.empty())
			SendDownMsg(DOWN_MSG_START_RECV_MEDIA, recv_msg);
	}

	return false;
}

/*------------------------------------------------------------------------------
 * ��  ���������û�״̬�ı���Ϣ����
 * ��  ����[in] msg_data ��Ϣ
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnUserStateChanged(const MsgData& msg_data)
{
	LOG(_T("ClientCoreMgr::OnUserStateChanged.\n"));

	std::shared_ptr<UserStateChangedMsg> state_msg = 
		std::static_pointer_cast<UserStateChangedMsg>(msg_data);

	// �����ݲ�����
	if (state_msg->user_id == m_room_data_mgr.GetLocalUserId())
		return false;

	// �ж����ÿ����Ƿ��������Զ������Ƶ
	if (!m_client_config.if_recv_av)
		return false;

	std::shared_ptr<StartRecvMediaMsg> recv_msg(new StartRecvMediaMsg);

	if (state_msg->has_audio_state)
	{
		MediaInfo media_info;
		media_info.media_type = 1;
		media_info.media_id = state_msg->audio_id;
		media_info.media_state = state_msg->audio_state;

		recv_msg->media_infos.push_back(media_info);
	}
	else if (!state_msg->video_channels.empty())
	{
		for each (std::pair<FS_INT32, VideoChannel> iter in state_msg->video_channels)
		{
			MediaInfo media_info;
			media_info.media_type = 2;
			media_info.media_id = iter.second.media_id;
			media_info.media_state = iter.second.media_state;

			recv_msg->media_infos.push_back(media_info);
		}
	}

	recv_msg->user_id = state_msg->user_id;

	SendDownMsg(DOWN_MSG_START_RECV_MEDIA, recv_msg);

	return false;
}

/*------------------------------------------------------------------------------
 * ��  �������͵�¼����Ƶ������Ϣ
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ClientCoreMgr::SendLoginAvRoomMsg()
{
	std::shared_ptr<LoginAvRoomReqMsg> login_msg(new LoginAvRoomReqMsg);

	login_msg->user_id		= m_room_data_mgr.GetLocalUserId();
	login_msg->group_guid	= m_room_data_mgr.GetRoomSrvInfo().guidMedia;
	login_msg->check_code	= m_room_data_mgr.GetRoomSrvInfo().dwAVCheckCode;
	login_msg->app_id		= m_room_data_mgr.GetRoomSrvInfo().wAVSrvAppID;
	login_msg->server_addr	= m_room_data_mgr.GetRoomSrvInfo().strAVSrvAddr;

	SendDownMsg(DOWN_MSG_LOGIN_AV_ROOM, login_msg);
}

/*------------------------------------------------------------------------------
 * ��  �������͵�¼���鷿����Ϣ
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ClientCoreMgr::SendLoginRoomReqMsg()
{
	std::shared_ptr<LoginRoomReqMsg> req_msg(new LoginRoomReqMsg);

	req_msg->client_mode		= m_client_config.client_mode;
	req_msg->client_type		= m_client_config.client_type;
	req_msg->download_bitrate	= 1000000;	// TODO:
	req_msg->lan_code			= 1;		// TODO:
	req_msg->room_id			= m_client_config.room_id;
	req_msg->room_password		= m_client_config.room_pwd;
	req_msg->room_srv_node_id	= m_room_data_mgr.GetRoomSrvNodeId();
	req_msg->terminal_type		= m_client_config.terminal_type;
	req_msg->token				= m_room_data_mgr.GetLocalUserToken();
	req_msg->user_id			= m_room_data_mgr.GetLocalUserId();
	req_msg->user_name			= m_user_name;	// TODO:
	req_msg->verify_mode		= m_room_data_mgr.GetVerifyMode();
	req_msg->user_type			= m_client_config.user_type;

	SendDownMsg(DOWN_MSG_LOGIN_ROOM, req_msg);
}

/*------------------------------------------------------------------------------
 * ��  �������ͱ�������Ƶ�豸��Ϣ
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ClientCoreMgr::SendUserAvInfoMsg()
{
	std::shared_ptr<UserAvInfoMsg> av_msg(new UserAvInfoMsg);

	av_msg->user_id = m_room_data_mgr.GetLocalUserId();
	av_msg->audio_channel = m_room_data_mgr.GetLocalUserAudioChannel();
	av_msg->video_channels = m_room_data_mgr.GetLocalUserVideoChannels();

	SendDownMsg(DOWN_MSG_BROADCAST_USER_AV_INFO, av_msg);
}

/*------------------------------------------------------------------------------
 * ��  �������͵ǳ����鷿����Ϣ
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
bool ClientCoreMgr::OnLogoutRoom(const MsgData& msg_data)
{
	LogoutRoomMsgSP logout_msg =
		std::static_pointer_cast<LogoutRoomMsg>(msg_data);

	logout_msg->user_id = m_room_data_mgr.GetLocalUserId();
	logout_msg->room_id = m_room_data_mgr.GetRoomId();
	logout_msg->room_srv_node_id = m_room_data_mgr.GetRoomSrvNodeId();

	return true;
}