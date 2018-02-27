#include "stdafx.h"
#include <atlconv.h>
#include "update_checker.h"
#include "isessionmanager.h"
#include "meeting_core_define.h"
#include "xmlprotocolparser.h"
#include "UpdateMgrProtocol.h"
#include "client_state_machine.h"

using namespace clientcore;
using namespace meetingcore;

#define THREAD_MSG_TCPNETWORK		WM_USER+100

UpdateChecker::UpdateChecker(const ClientStateMachineSP& state_machine)
	: m_state_machine(state_machine)
{
}

UpdateChecker::~UpdateChecker()
{
	
}

void UpdateChecker::Start()
{
	StartThread();
}

WBASE_NOTIFY UpdateChecker::GetNotify()
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

FS_UINT32 UpdateChecker::GetVerCheckResult()
{
	HANDLE stop_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	SESSIONSRVADDRITEM *addr_item = NULL;

	// 域名解析
	FS_UINT32 addr_item_count = m_state_machine->GetSessionManager()->ParseAndSortAddrLink(
		m_state_machine->GetClientConfig().front_addr_link.c_str(),
		SESSION_SRVADDRTYPE_TCP,
		SESSION_SRVADDRTYPE_TCP,
		stop_event,
		&addr_item);
	if (addr_item == NULL || addr_item_count == 0)
	{
		FWLOGA("ParseAndSortAddrLink failed,AddrLink = %s.\n", 
			m_state_machine->GetClientConfig().front_addr_link.c_str());
		return UPDATE_RESULT_CONNECTFAILED;
	}

	WBASE_NOTIFY notify = GetNotify();

	int nResult = UPDATE_RESULT_CONNECTFAILED;
	LOG(_T("First Server IP = %u,Port = %d.\n"), addr_item[0].dwIP, addr_item[0].wPort);

	for (FS_UINT32 i = 0; i < addr_item_count; i++)
	{
		FS_UINT32 dwIP = addr_item[i].dwIP;
		FS_UINT16 wPort = addr_item[i].wPort;

		WSOCKET sock = m_state_machine->GetNetwork()->TCP_Connect(dwIP, wPort, 15000, &notify, 0);
		if (sock == 0){
			LOG(_T("Client Update,Connect Server Failed,Server IP = %u,Port = %d.\n"), dwIP, wPort);
			continue;
		}
		nResult = GetVersion(sock);

		m_state_machine->GetNetwork()->TCP_Close(sock);

		LOG(_T("Client Update Result = %d,Server IP = %u,Port = %d.\n"), nResult, dwIP, wPort);
		if (nResult != UPDATE_RESULT_CONNECTFAILED)
			break;
	}
	m_state_machine->GetSessionManager()->FreeSrvAddrItem(addr_item);

	return nResult;
}

int UpdateChecker::GetVersion(WSOCKET sock)
{
	USES_CONVERSION;
	WriteVersionReq(sock, A2T(m_state_machine->GetClientConfig().product_id.c_str()),
		A2T(m_state_machine->GetClientConfig().client_version.c_str()));

	int		nResult = UPDATE_RESULT_OK;
	BOOL	bExitLoop = FALSE;
	HANDLE	pHandle[] = { m_evStop };
	DWORD	dwRet = 0;
	DWORD	dwStartTime = GetTickCount();

	m_dwRecvedLen = 0;
	while (!bExitLoop && !m_bStop)
	{
#ifdef _WIN32
		dwRet = MsgWaitForMultipleObjects(1, pHandle, FALSE, 1000, QS_ALLEVENTS);
		if (dwRet == WAIT_OBJECT_0)
			break;
		if (dwRet == WAIT_OBJECT_0 + 1){
			MSG 	msg;
			MSG* 	pMsg = &msg;
			while (PeekMessage(pMsg, NULL, 0, 0, PM_REMOVE)){
#else
		WBASE_MSG *pMsg = m_MsgQueue.PopMsg(2000);
		if (NULL == pMsg)
			continue;
		if (pMsg)
		{
			{
#endif
				if (pMsg->message == THREAD_MSG_TCPNETWORK){

					WNET_EVENT *pEvent = NULL;
					while (pEvent = m_state_machine->GetNetwork()->TCP_PopupMsg(pMsg->lParam, 0)){

						if (!bExitLoop){
							switch (pEvent->nEventType) {
							case WNET_EVENT_TCP_RECV_COMPLETE:
								bExitLoop = OnRecvComplete((PBYTE)pEvent->pData, pEvent->nDataLen, nResult);
								break;
							case WNET_EVENT_TCP_CLOSE:
								LOG(_T("Client Update,Tcp Sock Closed,sock = %d.\n"), sock);
								nResult = UPDATE_RESULT_CONNECTFAILED;
								bExitLoop = TRUE;
								break;
							}
						}
						m_state_machine->GetNetwork()->TCP_FreeMsg(pMsg->lParam, pEvent);
					}
				}
			}
#ifndef _WIN32
			m_MsgAllocator.Free(pMsg);
#endif
		}
		if (GetTickCount() - dwStartTime >= 5000){
			LOG(_T("Client Update,Recv timeout,sock = %d.\n"), sock);
			nResult = UPDATE_RESULT_CONNECTFAILED;
			break;
		}
			}
	return nResult;
}

void UpdateChecker::WriteVersionReq(WSOCKET sockID, const TCHAR* szProductID, const TCHAR *szClientVersion)
{
	CHAR szSendBuffer[1024];

	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, UPDATE_CMDID_VERSIONREQ);
	WXmlParser_SetVersion(&element, UPDATE_PROTOCOL_VERSION);
	WXmlParser_AddFieldValue(&element, "ProductID", szProductID);
	WXmlParser_AddFieldValue(&element, "Version", szClientVersion);

	TIXML_OSTREAM stream;
	stream << element;

	UPDATE_CMD_HEADER *pHead = (UPDATE_CMD_HEADER*)szSendBuffer;
	pHead->dwHeadTag = UPDATE_PROTOCOL_TAG;
	pHead->dwLen = sizeof(UPDATE_CMD_HEADER) + stream.length();

	CopyMemory(szSendBuffer + sizeof(UPDATE_CMD_HEADER), (PBYTE)stream.c_str(), stream.length());

	m_state_machine->GetNetwork()->TCP_Send(sockID, szSendBuffer, pHead->dwLen);
}

BOOL UpdateChecker::OnRecvComplete(PBYTE pbData, DWORD dwDataLen, int& nResult)
{
	if (dwDataLen + m_dwRecvedLen > UPDATERECV_BUFFER_SIZE){
		nResult = UPDATE_RESULT_CONNECTFAILED;
		return TRUE;
	}
	CopyMemory(m_pbRecvBuffer + m_dwRecvedLen, pbData, dwDataLen);
	m_dwRecvedLen += dwDataLen;

	if (m_dwRecvedLen >= sizeof(UPDATE_CMD_HEADER)){

		UPDATE_CMD_HEADER *pHead = (UPDATE_CMD_HEADER*)m_pbRecvBuffer;
		if (m_dwRecvedLen >= pHead->dwLen){

			TiXmlElement element("cmd");
			if (!WXmlParser_LoadCommand(element, (CHAR*)m_pbRecvBuffer + sizeof(UPDATE_CMD_HEADER), m_dwRecvedLen - sizeof(UPDATE_CMD_HEADER))){
				LOG(_T("Client Update,WXmlParser_LoadCommand Failed.\n"));
				nResult = UPDATE_RESULT_CONNECTFAILED;
				return TRUE;
			}
			WORD wCommand;
			if (!WXmlParser_GetCommand(&element, wCommand)){
				LOG(_T("Client Update,WXmlParser_GetCommand Failed.\n"));
				nResult = UPDATE_RESULT_CONNECTFAILED;
				return TRUE;
			}

			if (wCommand != UPDATE_CMDID_VERSIONREP){
				LOG(_T("Client Update,Invalid Command,Command = %d.\n"), wCommand);
				nResult = UPDATE_RESULT_CONNECTFAILED;
				return TRUE;
			}

			const CHAR* szValue = NULL;
			szValue = WXmlParser_GetFieldValue(&element, "NewVersion");
			if (szValue)
				m_strLastVersion = szValue;
			szValue = WXmlParser_GetFieldValue(&element, "MinVersion");
			if (szValue)
				m_strMinVersion = szValue;

			m_lsDowloadUrl.clear();
			TiXmlElement* pElement = element.FirstChildElement("DownloadURL");
			while (pElement)
			{
				const CHAR* szValue = pElement->Attribute("val");
				if (szValue){
#ifdef _UNICODE				
					WCHAR wszUrl[MAX_PATH];
					if (ConvertUtf8ToUnicode(szValue, wszUrl, MAX_PATH) > 0)
						m_lsDowloadUrl.push_back(wszUrl);
#else
					m_lsDowloadUrl.push_back(szValue);
#endif
				}
				pElement = pElement->NextSiblingElement("DownloadURL");
			}
			FWLOGA(("Client Update Version,MinVersion = %s,LastVersion = %s.\n"), (m_strMinVersion.c_str()), (m_strLastVersion.c_str()));

			CHAR szClientVersion[64];
			ZeroMemory(szClientVersion, sizeof(szClientVersion));
			if (strcmp(m_strMinVersion.c_str(), m_state_machine->GetClientConfig().client_version.c_str()) > 0)
				nResult = UPDATE_RESULT_MUSTUPDATE;
			else if (strcmp(m_strLastVersion.c_str(), szClientVersion) > 0)
				nResult = UPDATE_RESULT_ADVICEUPDATE;
			else
				nResult = UPDATE_RESULT_OK;
			return TRUE;
		}
	}
	return FALSE;
}

FS_UINT32 UpdateChecker::ThreadProcEx()
{
	// 获取版本查询结果
	FS_UINT32 result = GetVerCheckResult();

	// 向外部发送版本查询结果
	VerCheckMsgData* msg_data = new VerCheckMsgData;
	msg_data->check_result = result;
	m_state_machine->ProcStateOutMsg(STATE_OUT_MSG_VER_CHECK_RESULT, msg_data);

	StateStopMsgData* stop_msg_data = new StateStopMsgData;
	stop_msg_data->state_type = CLIENT_STATE_TYPE_UPDATE;
	m_state_machine->ProcStateOutMsg(STATE_OUT_MSG_STATE_STOP, stop_msg_data);

	return 0;
}