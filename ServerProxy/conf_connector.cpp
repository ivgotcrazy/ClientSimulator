/*##############################################################################
 * 文件：conf_connector.cpp
 * 描述：ConfConnector实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "conf_connector.h"
#include "client_state_machine.h"
#include "xmlprotocolparser.h"
#include "tinyxml.h"
#include "ConfProtocol.h"
#include "conf_msg_processor.h"

using namespace meetingcore;

#define WM_SESSIONMSG				WM_USER+100

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：[in] state_machine 状态机
 * 返回值：无
------------------------------------------------------------------------------*/
ConfConnector::ConfConnector(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, m_conf_session_id(0)
	, m_login_room_req_msg(nullptr)
{
}

/*------------------------------------------------------------------------------
 * 描  述：初始化
 * 参  数：无
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfConnector::Init()
{
	if (!m_msg_sender.Init(m_state_machine->GetSessionManager()))
	{
		LOG(_T("Failed to init front msg sender.\n"));
		return false;
	}

	// 下行消息注册
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN_ROOM, ConfConnector::OnLoginRoomMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_INIT_COMPLETE, ConfConnector::OnInitCompleteMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_BROADCAST_USER_AV_INFO, ConfConnector::OnBroadcastUserAvInfoMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGOUT_ROOM, ConfConnector::OnLogoutRoom);

	StartThread();

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：线程消息处理函数
 * 参  数：[in] msg 线程消息
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::ThreadMsgProc(const Thread_MSG& msg)
{
	if (msg.message == WM_SESSIONMSG)
	{
		ProcessSessionEvent(m_state_machine->GetSessionManager()->GetEvent(m_conf_session_id));
	}
	else
	{
		LOG(_T("Unhandled thread msg = %u.\n"), msg.message);
	}
}

/*------------------------------------------------------------------------------
 * 描  述：会话事件处理入口
 * 参  数：[in] session_event 会话事件
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::ProcessSessionEvent(SESSION_EVENT *session_event)
{
	if (session_event == NULL) // ??? 这里可能出现，暂未分析原因
	{
		LOG(_T("Invalid session event.\n"));
		return;
	}

	switch (session_event->nEventType)
	{
	case SESSION_EVENT_ACCEPT:
		break;
	case SESSION_EVENT_CREATED:
		OnSessionCreated(session_event);
		break;
	case SESSION_EVENT_CREATEFAIL:
		OnSessionCreateFailed(session_event);
		break;
	case SESSION_EVENT_CLOSED:
		OnSessionClosed(session_event);
		break;
	case SESSION_EVENT_DATA:
		ProcessSessionMsg(session_event->pbData, session_event->dwDataLen);
		break;
	case SESSION_EVENT_RECONNECTING:
		break;
	case SESSION_EVENT_RECONNECTED:
		break;
	case SESSION_EVENT_SEND:
		break;
	default:
		LOG(_T("Invalid session event type = %u.\n"), session_event->nEventType);
		break;
	}
}

/*------------------------------------------------------------------------------
 * 描  述：会话创建事件处理函数
 * 参  数：[in] session_event 会话事件
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::OnSessionCreated(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionCreated,sessionid = %d.\n"), session_event->nSessionID);

	SendUpMsg(UP_MSG_CONNECT_CONF_SUCCESS, NULL);

	SendLoginRoomReq();
}

/*------------------------------------------------------------------------------
 * 描  述：会话关闭事件处理函数
 * 参  数：[in] session_event 会话事件
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::OnSessionClosed(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionClosed,sessionid = %d.\n"), session_event->nSessionID);
}

/*------------------------------------------------------------------------------
 * 描  述：会话创建失败处理函数
 * 参  数：[in] session_event 会话事件
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::OnSessionCreateFailed(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionCreateFailed,sessionid = %d.\n"), session_event->nSessionID);

	SendUpMsg(UP_MSG_CONNECT_CONF_FAILED, NULL);
}

/*------------------------------------------------------------------------------
 * 描  述：会话消息处理函数
 * 参  数：[in] data_ptr 消息内容
 *         [in] data_len 消息长度
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::ProcessSessionMsg(PBYTE data_ptr, FS_UINT32 data_len)
{
	//LOG(_T("ConfConnector::ProcessSessionMsg\n"));

	TiXmlElement element("cmd");
	if (!m_msg_sender.Input(data_ptr, data_len, element))
	{
		LOG(_T("Failed to parse xml data.\n"));
		return;
	}

	BOOL bResult = FALSE;
	FS_UINT16 command_type;
	if (!WXmlParser_GetCommand(&element, command_type))
	{
		LOG(_T("Failed to get command type from xml data.\n"));
		return;
	}

	switch (command_type)
	{
	case CONF_CMDID_LOGINREP:
		OnLoginRoomRep(element);
		break;

	case CONF_CMDID_USERSTATECHANGED:
		OnUserStateChanged(element);
		break;

	case CONF_CMDID_AVINFONOTIFY:
		OnUserAvInfoNotify(element);
		break;

	case CONF_CMDID_USERENTER:
		OnUserEnterNotify(element);
		break;

	default:
		//LOG(_T("Unexpected command type = %u.\n"), command_type);
		break;
	}
}

/*------------------------------------------------------------------------------
 * 描  述：获取Notify结构
 * 参  数：无
 * 返回值：Notify结构
------------------------------------------------------------------------------*/
WBASE_NOTIFY ConfConnector::GetSessionNotify()
{
	WBASE_NOTIFY notify;
#ifdef _WIN32
	notify.nNotifyMode = WBASE_NOTIFYMODE_THREADMSG;
	notify.ThreadMsgMode.nThreadID = m_unThreadID;
	notify.ThreadMsgMode.nNotifyMsg = WM_SESSIONMSG;
#else
	notify.nNotifyMode = WBASE_NOTIFYMODE_CALLBACK;
	notify.CallbackMode.pCallback = (void*)OnMsgCallback;
	notify.CallbackMode.dwUserData = (DWORD)this;
	notify.CallbackMode.nMsgID = WM_SESSIONMSG;
#endif

	return notify;
}

/*------------------------------------------------------------------------------
 * 描  述：登录房间请求消息处理
 * 参  数：[in] msg_data 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnLoginRoomMsg(const MsgData& msg_data)
{
	if (m_room_service_list.empty())
	{
		LOG(_T("Empty service list.\n"));
		return false;
	}

	// 会话还未创建，消息先保存起来
	m_login_room_req_msg = std::static_pointer_cast<LoginRoomReqMsg>(msg_data);

	WBASE_NOTIFY notify = GetSessionNotify();

	m_conf_session_id = m_state_machine->GetSessionManager()->CreateSession(
		m_room_service_list[0].srv_addr.c_str(),
		SESSIONTYPE_RELIABLE,
		11,
		&notify);
	if (m_conf_session_id == 0)
	{
		LOG(_T("Failed to create front session.\n"));
		// TODO: 异常处理
	}

	return false;
}

void ConfConnector::SetRoomServiceList(const RoomServiceList& service_list)
{
	m_room_service_list = service_list;
}

/*------------------------------------------------------------------------------
 * 描  述：登录房间响应消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnLoginRoomRep(TiXmlElement& element)
{
	std::shared_ptr<LoginRoomRepMsg> rep_msg(new LoginRoomRepMsg);
	if (ConfMsgProcessor::ParseLoginRoomRep(element, rep_msg.get()))
	{
		SendUpMsg(UP_MSG_LOGIN_ROOM_REP, rep_msg);
	}
	else
	{
		LOG(_T("Failed to parse LoginRoomRep.\n"));
		// TODO:
	}

	return false; // 原始消息上层无法处理
}

bool ConfConnector::OnUserEnterNotify(TiXmlElement& element)
{
	LOG(_T("ConfConnector::OnUserEnterNotify.\n"));

	std::shared_ptr<UserEnterNotifyMsg> enter_notify(new UserEnterNotifyMsg);
	if (ConfMsgProcessor::ParseUserEnterNotifyMsg(element, enter_notify.get()))
	{
		SendUpMsg(UP_MSG_USER_ENTER_NOTIFY, enter_notify);
	}
	else
	{
		LOG(_T("Failed to parse OnUserEnterNotify.\n"));
		// TODO:
	}

	return false; // 原始消息上层无法处理
}

/*------------------------------------------------------------------------------
 * 描  述：用户音视频信息消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnUserAvInfoNotify(TiXmlElement& element)
{
	LOG(_T("ConfConnector::OnUserAvInfoNotify.\n"));

	std::shared_ptr<UserAvInfoNotifyMsg> av_notify(new UserAvInfoNotifyMsg);
	if (ConfMsgProcessor::ParseUserAvInfoNotifyMsg(element, av_notify.get()))
	{
		SendUpMsg(UP_MSG_USER_AV_INFO_NOTIFY, av_notify);
	}
	else
	{
		LOG(_T("Failed to parse OnUserAvInfoNotify.\n"));
		// TODO:
	}

	return false; // 原始消息上层无法处理
}

/*------------------------------------------------------------------------------
 * 描  述：用户状态改变消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnUserStateChanged(TiXmlElement& element)
{
	LOG(_T("ConfConnector::OnUserStateChanged.\n"));

	std::shared_ptr<UserStateChangedMsg> state_msg(new UserStateChangedMsg);
	if (ConfMsgProcessor::ParseUserStateChangedMsg(element, state_msg.get()))
	{
		SendUpMsg(UP_MSG_USER_STATE_CHANGED, state_msg);
	}
	else
	{
		LOG(_T("Failed to parse OnUserStateChanged.\n"));
		// TODO:
	}

	LOG(_T("ConfConnector::OnUserStateChanged.\n"));

	return false; // 原始消息上层无法处理
}

/*------------------------------------------------------------------------------
 * 描  述：发送登录房间请求
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void ConfConnector::SendLoginRoomReq()
{
	TiXmlElement element = ConfMsgProcessor::ConstructLoginRoomReq(m_login_room_req_msg.get());

	HRESULT hr = m_msg_sender.Output(element, m_conf_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send LoginRoomReq.\n"));
		// TODO:
	}
}

/*------------------------------------------------------------------------------
 * 描  述：发送初始化完成消息
 * 参  数：[in] msg_data 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnInitCompleteMsg(const MsgData& msg_data)
{
	TiXmlElement element = ConfMsgProcessor::ConstructInitCompleteMsg();

	HRESULT hr = m_msg_sender.Output(element, m_conf_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send LoginRoomReq.\n"));
		// TODO:
	}

	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：上层请求广播用户音视频信息消息处理
 * 参  数：[in] msg_data 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnBroadcastUserAvInfoMsg(const MsgData& msg_data)
{
	std::shared_ptr<UserAvInfoMsg> av_msg = std::static_pointer_cast<UserAvInfoMsg>(msg_data);

	TiXmlElement element = ConfMsgProcessor::ConstructUserAvInfoMsg(av_msg->user_id, 
		av_msg->audio_channel, av_msg->video_channels);

	HRESULT hr = m_msg_sender.Output(element, m_conf_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send BroadcastUserAvInfoMsg.\n"));
		// TODO:
	}

	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：上层请求退出会议室消息处理
 * 参  数：[in] msg_data 消息数据 
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool ConfConnector::OnLogoutRoom(const MsgData& msg_data)
{
	LogoutRoomMsgSP logout_msg =
		std::static_pointer_cast<LogoutRoomMsg>(msg_data);

	TiXmlElement element = ConfMsgProcessor::ConstructLogoutRoomMsg(logout_msg->user_id, 
		logout_msg->room_id, logout_msg->room_srv_node_id.c_str());

	HRESULT hr = m_msg_sender.Output(element, m_conf_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send LogoutRoomMsgSP.\n"));
		// TODO:
	}

	return false;
}