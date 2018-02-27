/*##############################################################################
 * �ļ���update_checker.cpp
 * ������UpdateCheckerʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"

#include <atlconv.h>

#include "update_checker.h"
#include "client_state_machine.h"
#include "XMLDocProtocol.h"
#include "xmlprotocolparser.h"
#include "UpdateMgrProtocol.h"
#include "conf_msg_processor.h"

using namespace meetingcore;

#define THREAD_MSG_TCPNETWORK		WM_USER+200

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ����[in] state_machine ״̬��
 * ����ֵ����
------------------------------------------------------------------------------*/
UpdateChecker::UpdateChecker(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
	, m_curr_update_addr_index(0)
	, m_update_addr_count(0)
	, m_recved_len(0)
{
	ZeroMemory(&m_notify, sizeof(m_notify));
}

/*------------------------------------------------------------------------------
 * ��  ������������
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
UpdateChecker::~UpdateChecker()
{
	StopThread();
}

/*------------------------------------------------------------------------------
 * ��  ������ʼ��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
bool UpdateChecker::Init()
{
	DOWN_MSG_PRE_MAP(DOWN_MSG_START_UPDATE_CHECK, UpdateChecker::OnStartUpdateCheck);

	StartThread();

	return true;
}

/*------------------------------------------------------------------------------
 * ��  ���������汾���
 * ��  ����[in] msg_data ��Ϣ����
 * ����ֵ���Ƿ�����ַ���Ϣ
------------------------------------------------------------------------------*/
bool UpdateChecker::OnStartUpdateCheck(const MsgData& msg_data)
{
	const std::shared_ptr<UpdateCheckReqMsg> update_msg_data = 
		std::static_pointer_cast<UpdateCheckReqMsg>(msg_data);

	if (TryParseServerAddr(update_msg_data->server_addr))
	{
		CheckVerUpdate();
	}
	else
	{
		LOG(_T("Failed to parse update server address.\n"));
	}

	return false;
}

/*------------------------------------------------------------------------------
 * ��  �����߳���Ϣ������
 * ��  ����[in] msg �߳���Ϣ
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpdateChecker::ThreadMsgProc(const Thread_MSG& msg)
{
	if (msg.message == THREAD_MSG_TCPNETWORK)
	{
		ProcTcpNetworkMsg(msg);
	}
	else
	{
		LOG(_T("Unhandled thread msg = %u.\n"), msg.message);
	}
}

/*------------------------------------------------------------------------------
 * ��  ����������������ַ
 * ��  ����[in] server_addr ��������ַ
 * ����ֵ���ɹ�/ʧ�� 
------------------------------------------------------------------------------*/
bool UpdateChecker::TryParseServerAddr(const std::string& server_addr)
{
	HANDLE stop_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	SESSIONSRVADDRITEM *addr_item = NULL;

	// ��������
	FS_UINT32 addr_item_count = m_state_machine->GetSessionManager()
		->ParseAndSortAddrLink(server_addr.c_str(),
		SESSION_SRVADDRTYPE_TCP,
		SESSION_SRVADDRTYPE_TCP,
		stop_event,
		&addr_item);
	if (addr_item == NULL || addr_item_count == 0)
	{
		FWLOGA("ParseAndSortAddrLink failed,AddrLink = %s.\n",
			m_state_machine->GetClientConfig().front_addr.c_str());
		return false;
	}

	m_update_addr_count = addr_item_count > MAX_UPDATE_ADDR_COUNT 
		? MAX_UPDATE_ADDR_COUNT : addr_item_count;
	memcpy(m_update_addr, addr_item, sizeof(SESSIONSRVADDRITEM) * m_update_addr_count);

	return true;
}

/*------------------------------------------------------------------------------
 * ��  �����汾���¼��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpdateChecker::CheckVerUpdate()
{
	if (m_curr_update_addr_index >= m_update_addr_count)
	{
		LOG(_T("Have tried all server to check client version, but failed.\n"));
		return; // TODO: ����������Ӧ��֪ͨ�ⲿ�汾�������ʧ��
	}

	FS_UINT32 ip = m_update_addr[m_curr_update_addr_index].dwIP;
	FS_UINT16 port = m_update_addr[m_curr_update_addr_index].wPort;

	IWNetwork* network = m_state_machine->GetNetwork();
	WBASE_NOTIFY notify = GetTcpNetworkNotify();

	WSOCKET sock = network->TCP_Connect(ip, port, 15000, &notify, 0);
	if (sock != 0)
	{
		TrySendVerCheckReq(sock);
	}
	else
	{
		LOG(_T("Client Update,Connect Server Failed,Server IP = %u,Port = %d.\n"), ip, port);

		// ��ǰֻ��������ʧ�ܵ��µ��������ʧ�����
		++m_curr_update_addr_index;
		CheckVerUpdate();
	}
}

/*------------------------------------------------------------------------------
 * ��  �������Ͱ汾���¼������
 * ��  ����[in] sockID socket
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpdateChecker::TrySendVerCheckReq(WSOCKET sockID)
{
	USES_CONVERSION;
	TiXmlElement element = ConfMsgProcessor::ConstructClientVerCheckReq(
		A2T(m_state_machine->GetClientConfig().product_id.c_str()),
		A2T(m_state_machine->GetClientConfig().client_ver.c_str()));

	TIXML_OSTREAM stream;
	stream << element;

	CHAR szSendBuffer[1024];
	UPDATE_CMD_HEADER *pHead = (UPDATE_CMD_HEADER*)szSendBuffer;
	pHead->dwHeadTag = UPDATE_PROTOCOL_TAG;
	pHead->dwLen = sizeof(UPDATE_CMD_HEADER) + stream.length();

	CopyMemory(szSendBuffer + sizeof(UPDATE_CMD_HEADER), (PBYTE)stream.c_str(), stream.length());

	m_state_machine->GetNetwork()->TCP_Send(sockID, szSendBuffer, pHead->dwLen);
}

/*------------------------------------------------------------------------------
 * ��  ��������TCP��Ϣ
 * ��  ����[in] msg ��Ϣ
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpdateChecker::ProcTcpNetworkMsg(MSG msg)
{
	int result;
	BOOL exit_flag = false;
	WNET_EVENT* net_event = NULL;

	while (net_event = m_state_machine->GetNetwork()->TCP_PopupMsg(msg.lParam, 0))
	{
		if (!exit_flag)
		{
			switch (net_event->nEventType)
			{
			case WNET_EVENT_TCP_RECV_COMPLETE:
				exit_flag = OnRecvComplete((PBYTE)net_event->pData, net_event->nDataLen, &result);
				break;
			case WNET_EVENT_TCP_CLOSE:
				LOG(_T("Client Update,Tcp Sock Closed.\n"));
				result = UPDATE_RESULT_CONNECTFAILED;
				exit_flag = TRUE;
				break;
			default:
				LOG(_T("Client update, unexpected event type = %u.\n"), net_event->nEventType);
				break;
			}
		}
		m_state_machine->GetNetwork()->TCP_FreeMsg(msg.lParam, net_event);
	}
}

/*------------------------------------------------------------------------------
 * ��  ����Tcp��Ϣ������ɴ���
 * ��  ����[in] data_ptr ��Ϣ���� 
 *         [in] data_len ��Ϣ����
 *         [in] result �汾���¼���� 
 * ����ֵ���ɹ�/ʧ�� 
------------------------------------------------------------------------------*/
BOOL UpdateChecker::OnRecvComplete(PBYTE data_ptr, DWORD data_len, int* result)
{
	if (data_len + m_recved_len > UPDATERECV_BUFFER_SIZE)
	{
		*result = UPDATE_RESULT_CONNECTFAILED;
		return TRUE;
	}
	CopyMemory(m_recv_buffer + m_recved_len, data_ptr, data_len);
	m_recved_len += data_len;

	// ��Ϣͷ��û��������
	if (m_recved_len < sizeof(UPDATE_CMD_HEADER))
		return FALSE;

	// ��Ϣ�廹û��������
	UPDATE_CMD_HEADER *head = (UPDATE_CMD_HEADER*)m_recv_buffer;
	if (m_recved_len < head->dwLen)
		return FALSE;

	std::shared_ptr<UpdateCheckRepMsg> rep_msg_data(new UpdateCheckRepMsg);
	if (ConfMsgProcessor::ParseClientVerCheckRep(
		reinterpret_cast<CHAR*>(m_recv_buffer + sizeof(UPDATE_CMD_HEADER)),
		m_recved_len - sizeof(UPDATE_CMD_HEADER), rep_msg_data.get()))
	{
		std::string client_ver = m_state_machine->GetClientConfig().client_ver;
		if (strcmp(rep_msg_data->min_ver.c_str(), client_ver.c_str()) > 0)
			rep_msg_data->result = UPDATE_RESULT_MUSTUPDATE;
		else if (strcmp(rep_msg_data->last_ver.c_str(), client_ver.c_str()) > 0)
			rep_msg_data->result = UPDATE_RESULT_ADVICEUPDATE;
		else
			rep_msg_data->result = UPDATE_RESULT_OK;

		SendUpMsg(UP_MSG_UPDATE_CHECK_RESULT, rep_msg_data);
	}
	else
	{
		; // TODO: �쳣
	}

	return TRUE;
}

/*------------------------------------------------------------------------------
 * ��  ������ȡNotify
 * ��  ������
 * ����ֵ��Notify
------------------------------------------------------------------------------*/
WBASE_NOTIFY UpdateChecker::GetTcpNetworkNotify()
{
	WBASE_NOTIFY notify;
#ifdef _WIN32
	notify.nNotifyMode = WBASE_NOTIFYMODE_THREADMSG;
	notify.ThreadMsgMode.nThreadID = m_unThreadID;
	notify.ThreadMsgMode.nNotifyMsg = THREAD_MSG_TCPNETWORK;
#else
	notify.nNotifyMode = WBASE_NOTIFYMODE_CALLBACK;
	notify.CallbackMode.pCallback = (void*)OnMsgCallback;
	notify.CallbackMode.dwUserData = (DWORD)this;
	notify.CallbackMode.nMsgID = THREAD_MSG_TCPNETWORK;
#endif

	return notify;
}