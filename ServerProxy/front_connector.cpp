/*##############################################################################
 * �ļ���front_connector.cpp
 * ������FrontConnectorʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
 * ��  �������캯��
 * ��  ����[in] state_machine ״̬��
 * ����ֵ����
------------------------------------------------------------------------------*/
FrontConnector::FrontConnector(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, m_front_session_id(0)
{
}

/*------------------------------------------------------------------------------
 * ��  ������������
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
FrontConnector::~FrontConnector()
{
	StopThread();
}

/*------------------------------------------------------------------------------
 * ��  ������ʼ��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
bool FrontConnector::Init()
{
	if (!m_msg_sender.Init(m_state_machine->GetSessionManager()))
	{
		LOG(_T("Failed to init front msg sender.\n"));
		return false;
	}

	// ������Ϣע��
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN,			FrontConnector::OnLoginByUserMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_GET_ROOM_LIST,	FrontConnector::OnGetRoomListMsg);
	DOWN_MSG_PRE_MAP(DOWN_MSG_LOGIN_FRONT_ROOM, FrontConnector::OnLoginFrontRoomMsg);

	StartThread();

	return true;
}

/*------------------------------------------------------------------------------
 * ��  �����ϲ㷢�͵�¼ǰ��������Ϣ����
 * ��  ����[in] msg_data ��Ϣ����
 * ����ֵ���Ƿ�����ַ���Ϣ
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
		// TODO: �쳣����
	}

	return false;
}

/*------------------------------------------------------------------------------
 * ��  �����ϲ㷢�ͻ�ȡ�������б�������Ϣ����
 * ��  ����[in] msg_data ��Ϣ����
 * ����ֵ���Ƿ�����ַ���Ϣ
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
 * ��  �����߳���Ϣ������
 * ��  ����[in] msg �߳���Ϣ
 * ����ֵ����
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
 * ��  �����Ự�¼��������
 * ��  ����[in] session_event �Ự�¼�
 * ����ֵ����
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
 * ��  �����Ự�����ɹ��¼�����
 * ��  ����[in] session_event �Ự�¼�
 * ����ֵ���� 
------------------------------------------------------------------------------*/
void FrontConnector::OnSessionCreated(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionCreated,sessionid = %d.\n"), session_event->nSessionID);

	SendUpMsg(UP_MSG_CONNECT_FRONT_SUCCESS, NULL);

	SendLoginReq();
}

/*------------------------------------------------------------------------------
 * ��  �����Ự�رճɹ��¼�����
 * ��  ����[in] session_event �Ự�¼�
 * ����ֵ���� 
------------------------------------------------------------------------------*/
void FrontConnector::OnSessionClosed(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionClosed,sessionid = %d.\n"), session_event->nSessionID);
}

/*------------------------------------------------------------------------------
 * ��  �����Ự����ʧ���¼�����
 * ��  ����[in] session_event �Ự�¼�
 * ����ֵ���� 
------------------------------------------------------------------------------*/
void FrontConnector::OnSessionCreateFailed(SESSION_EVENT *session_event)
{
	LOG(_T("ConfManager::OnSessionCreateFailed,sessionid = %d.\n"), session_event->nSessionID);

	SendUpMsg(UP_MSG_CONNECT_FRONT_FAILED, NULL);
}

/*------------------------------------------------------------------------------
 * ��  �����Ự��Ϣ����
 * ��  ����[in] data_ptr ��Ϣ���� 
 *         [in] data_len ��Ϣ���� 
 * ����ֵ���� 
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
 * ��  ������ȡ�ỰNotify
 * ��  ������
 * ����ֵ��Notify 
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
 * ��  ������¼ǰ�÷�����Ӧ��Ϣ����
 * ��  ����[in] element ��Ϣ���� 
 * ����ֵ���� 
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
		// TODO: �쳣����
	}
}

/*------------------------------------------------------------------------------
 * ��  ������¼ǰ����Ӧ��Ϣ����
 * ��  ����[in] element ��Ϣ���� 
 * ����ֵ���� 
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
		// TODO: �쳣����
	}
}

/*------------------------------------------------------------------------------
 * ��  �������͵�¼ǰ����Ϣ
 * ��  ������ 
 * ����ֵ���� 
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
 * ��  �������ͻ�ȡ�������б���Ϣ
 * ��  ������
 * ����ֵ���� 
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
 * ��  ������ȡ�������б���Ӧ��Ϣ����
 * ��  ����[in] element ��Ϣ���� 
 * ����ֵ���� 
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
 * ��  ������¼ǰ�÷���������Ϣ����
 * ��  ����[in] element ��Ϣ���� 
 * ����ֵ���� 
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