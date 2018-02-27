/*##############################################################################
 * �ļ���update_checker.h
 * ������UpdateChecker����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "wthread_wrapper.h"

#define MAX_UPDATE_ADDR_COUNT	8
#define UPDATERECV_BUFFER_SIZE	2048

namespace meetingcore
{

/*==============================================================================
 * ����������汾���¼����ش���
==============================================================================*/
class UpdateChecker 
	: public CommonMsgProcessor
	, public WThreadWrapper
{
public:
	UpdateChecker(const ClientStateMachineSP& state_machine);
	~UpdateChecker();

	bool Init();

private:
	virtual void ThreadMsgProc(const Thread_MSG& msg) override;

	bool TryParseServerAddr(const std::string& server_addr);
	void CheckVerUpdate();
	void TrySendVerCheckReq(WSOCKET sockID);
	BOOL OnRecvComplete(PBYTE data_ptr, DWORD data_len, int* result);
	bool OnStartUpdateCheck(const MsgData& msg_data);
	void ProcTcpNetworkMsg(MSG msg);
	WBASE_NOTIFY GetTcpNetworkNotify();

private:
	ClientStateMachineSP	m_state_machine;

	WBASE_NOTIFY			m_notify;

	SESSIONSRVADDRITEM		m_update_addr[MAX_UPDATE_ADDR_COUNT];
	FS_UINT32				m_update_addr_count;
	FS_UINT32				m_curr_update_addr_index;

	BYTE					m_recv_buffer[UPDATERECV_BUFFER_SIZE];
	DWORD					m_recved_len;
};

}