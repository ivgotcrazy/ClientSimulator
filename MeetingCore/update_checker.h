#pragma once

#include "client_define.h"
#include "meeting_core_define.h"

#define UPDATERECV_BUFFER_SIZE			2048

namespace meetingcore
{

class UpdateChecker : public ThreadMsgProcessor
{
public:
	UpdateChecker(const ClientStateMachineSP& state_machine);
	~UpdateChecker();

	void Start();

private:
	FS_UINT32 GetVerCheckResult();
	virtual FS_UINT32 ThreadProcEx() override;

	WBASE_NOTIFY GetNotify();
	int GetVersion(WSOCKET sock);
	void WriteVersionReq(WSOCKET sockID, const TCHAR* szProductID, const TCHAR *szClientVersion);
	BOOL OnRecvComplete(PBYTE pbData, DWORD dwDataLen, int& nResult);

private:
	ClientStateMachineSP		m_state_machine;

	std::list<std::wstring>		m_lsDowloadUrl;
	std::string					m_strMinVersion;
	std::string					m_strLastVersion;

	BYTE						m_pbRecvBuffer[UPDATERECV_BUFFER_SIZE];
	DWORD						m_dwRecvedLen;
};

}