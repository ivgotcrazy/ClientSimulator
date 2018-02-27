/*##############################################################################
 * 文件：front_connector.cpp
 * 描述：FrontConnector实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "front_connector.h"
#include "FrontProtocol.h"
#include "xmlprotocolparser.h"
#include "tinyxml.h"
#include "client_state_machine.h"
#include "conf_msg_processor.h"
#include "ProtocolError.h"
#include "wnetfunction.h"

using namespace meetingcore;

#define WM_SESSIONMSG				WM_USER+100

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：[in] state_machine 状态机
 * 返回值：无
------------------------------------------------------------------------------*/
FrontConnector::FrontConnector(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, m_front_session_id(0)
{
}

/*------------------------------------------------------------------------------
 * 描  述：析构函数
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
FrontConnector::~FrontConnector()
{
	StopThread();
}

/*------------------------------------------------------------------------------
 * 描  述：初始化
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
bool FrontConnector::Init()
{
	if (!m_msg_sender.Init(m_state_machine->GetSessionManager()))
	{
		LOG(_T("Failed to init front msg sender.\n"));
		return false;
	}

	// 下行消息注册
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN,			FrontConnector::OnLoginByUserMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_GET_ROOM_LIST,	FrontConnector::OnGetRoomListMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN_FRONT_ROOM, FrontConnector::OnLoginFrontRoomMsg);

	StartThread();

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：上层发送登录前置请求消息处理
 * 参  数：[in] msg_data 消息数据
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool FrontConnector::OnLoginByUserMsg(const MsgData& msg_data)
{
	m_login_msg = std::static_pointer_cast<LoginReqMsg>(msg_data);

	WBASE_NOTIFY notify = GetSessionNotify();

	m_front_session_id = m_state_machine->GetSessionManager()->CreateSession(
		m_login_msg->server_addr.c_str(),
		SESSIONTYPE_RELIABLE,
		m_login_msg->front_app_id,
		&notify);
	if (m_front_session_id == 0)
	{
		LOG(_T("Failed to create front session.\n"));
		// TODO: 异常处理
	}

	return false;
}

/*------------------------------------------------------------------------------
 * 描  述：上层发送获取会议室列表请求消息处理
 * 参  数：[in] msg_data 消息数据
 * 返回值：是否继续分发消息
------------------------------------------------------------------------------*/
bool FrontConnector::OnGetRoomListMsg(const MsgData& msg_data)
{
	if (m_front_session_id == 0)
	{
		LOG(_T("Invalid front session.\n"));
		// TODO:
		return false;
	}

	SendGetRoomListReq();

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：线程消息处理函数
 * 参  数：[in] msg 线程消息
 * 返回值：无
------------------------------------------------------------------------------*/
void FrontConnector::ThreadMsgProc(const Thread_MSG& msg)
{
	if (msg.message == WM_SESSIONMSG)
	{
		SESSION_EVENT* session_event = m_state_machine->GetSessionManager()->GetEvent(m_front_session_id);
		ProcessSessionEvent(session_event);
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
void FrontConnector::ProcessSessionEvent(SESSION_EVENT *session_event)
{
	if (session_event == NULL)
	{
		LOG(_T("Invalid session event pointer.\n"));
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
 * 描  述：会话创建成功事件处理
 * 参  数：[in] session_event 会话事件
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::OnSessionCreated(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionCreated,sessionid = %d.\n"), session_event->nSessionID);

	SendUpMsg(UP_MSG_CONNECT_FRONT_SUCCESS, NULL);

	SendLoginReq();
}

/*------------------------------------------------------------------------------
 * 描  述：会话关闭成功事件处理
 * 参  数：[in] session_event 会话事件
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::OnSessionClosed(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionClosed,sessionid = %d.\n"), session_event->nSessionID);
}

/*------------------------------------------------------------------------------
 * 描  述：会话创建失败事件处理
 * 参  数：[in] session_event 会话事件
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::OnSessionCreateFailed(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionCreateFailed,sessionid = %d.\n"), session_event->nSessionID);

	SendUpMsg(UP_MSG_CONNECT_FRONT_FAILED, NULL);
}

/*------------------------------------------------------------------------------
 * 描  述：会话消息处理
 * 参  数：[in] data_ptr 消息数据 
 *         [in] data_len 消息长度 
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::ProcessSessionMsg(PBYTE data_ptr, FS_UINT32 data_len)
{
	LOG(_T("ConfManager::ProcessSessionMsg\n"));

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
	case FRONT_CMDID_TERMINAL_USERLOGIN_REP:
		OnUserLoginRep(element);
		break;
	case FRONT_CMDID_TERMINAL_ROOMLIST_REP:
		OnGetRoomListRep(element);
		break;
	case FRONT_CMDID_TERMINAL_LOGINROOM_REP:
		OnLoginFrontRoomRep(element);
		break;
	default:
		LOG(_T("Unexpected command type = %u.\n"), command_type);
		break;
	}
}

/*------------------------------------------------------------------------------
 * 描  述：获取会话Notify
 * 参  数：无
 * 返回值：Notify 
------------------------------------------------------------------------------*/
WBASE_NOTIFY FrontConnector::GetSessionNotify()
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
 * 描  述：登录前置房间响应消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::OnLoginFrontRoomRep(TiXmlElement& element)
{
	std::shared_ptr<LoginFrontRoomRepMsg> rep_msg(new LoginFrontRoomRepMsg);
	if (ConfMsgProcessor::ParseLoginFrontRoomRep(element, rep_msg.get()))
	{
		SendUpMsg(UP_MSG_LOGIN_FRONT_ROOM_REP, rep_msg);
	}
	else
	{
		LOG(_T("Failed to parse LoginRoomRep.\n"));
		// TODO: 异常处理
	}
}

/*------------------------------------------------------------------------------
 * 描  述：登录前置响应消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::OnUserLoginRep(TiXmlElement& element)
{
	LOG(_T("LoginState::OnUserLoginRep.\n"));

	std::shared_ptr<LoginRepMsg> rep_msg(new LoginRepMsg);
	if (ConfMsgProcessor::ParseFrontUserLoginRep(element, rep_msg.get()))
	{
		SendUpMsg(UP_MSG_LOGIN_REP, rep_msg);

		if (rep_msg->login_result != WPROTOCOL_RESULT_SUCCESS)
		{
			LOG(_T("Failed to login front.\n"));
			m_state_machine->GetSessionManager()->CloseSession(m_front_session_id);
		}
	}
	else
	{
		LOG(_T("Failed to parse front user login reply.\n"));
		// TODO: 异常处理
	}
}

/*------------------------------------------------------------------------------
 * 描  述：发送登录前置消息
 * 参  数：无 
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::SendLoginReq()
{
	LOG(_T("LoginState::SendLoginReq.\n"));

	if (m_front_session_id == 0)
	{
		LOG(_T("Invalid session while send front user login request.\n"));
		return;
	}

	SESSIONINFO sessionInfo;
	if (FAILED(m_state_machine->GetSessionManager()->GetSessionInfo(m_front_session_id, &sessionInfo)))
	{
		LOG(_T("Failed to get session info.\n"));
		return;
	}

	CHAR server_addr[MAX_PATH] = { 0 };
	CHAR server_ip[64] = { 0 };
	IPToString(sessionInfo.dwRemoteIP, server_ip);
	sprintf(server_addr, "%s:%d", server_ip, sessionInfo.wRemotePort);

	TiXmlElement element = ConfMsgProcessor::ConstructLoginReq(m_login_msg);

	HRESULT hr = m_msg_sender.Output(element, m_front_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send FrontUserLoginReq.\n"));
		// TODO:
	}
}

/*------------------------------------------------------------------------------
 * 描  述：发送获取会议室列表消息
 * 参  数：无
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::SendGetRoomListReq()
{
	TiXmlElement element = ConfMsgProcessor::ConstructGetRoomListReq();

	HRESULT hr = m_msg_sender.Output(element, m_front_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send GetRoomListReq.\n"));
		// TODO:
	}
}

/*------------------------------------------------------------------------------
 * 描  述：获取会议室列表响应消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：无 
------------------------------------------------------------------------------*/
void FrontConnector::OnGetRoomListRep(TiXmlElement& element)
{
	std::shared_ptr<GetRoomListRepMsg> msg_data(new GetRoomListRepMsg);

	if (ConfMsgProcessor::ParseGetRoomListRep(element, msg_data.get()))
	{
		SendUpMsg(UP_MSG_GET_ROOM_LIST_REP, msg_data);
	}
	else
	{
		; // TODO:
	}
}

/*------------------------------------------------------------------------------
 * 描  述：登录前置房间请求消息处理
 * 参  数：[in] element 消息数据 
 * 返回值：无 
------------------------------------------------------------------------------*/
bool FrontConnector::OnLoginFrontRoomMsg(const MsgData& msg_data)
{
	std::shared_ptr<LoginFrontRoomReqMsg> req_msg 
		= std::static_pointer_cast<LoginFrontRoomReqMsg>(msg_data);

	TiXmlElement element = ConfMsgProcessor::ConstructLoginFrontRoomReq(
		req_msg->room_node_id.c_str(), 
		req_msg->room_id, 
		req_msg->room_app_id);
	
	HRESULT hr = m_msg_sender.Output(element, m_front_session_id);
	if (FAILED(hr))
	{
		LOG(_T("Failed to send FrontUserLoginReq.\n"));
		// TODO:
	}

	return false;
}