/*##############################################################################
 * �ļ���thread_wrapper.cpp
 * ������WThreadWrapperʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "wthread_wrapper.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * ��  �����߳���Ϣ�����������̴߳����ܷ�װ�������ϲ�ֻ��Ҫʵ��ThreadMsgProc
 * ��  ������
 * ����ֵ��δ֪
------------------------------------------------------------------------------*/
FS_UINT32 WThreadWrapper::ThreadProcEx()
{
	while (!m_bStop)
	{
		Thread_MSG msg;
		FS_UINT32 ret = WaitForThreadMsg(100, &msg);
		switch (ret)
		{
		case WAIT_THREAD_EXIT:
			break;
		case WAIT_THREAD_MSG:
			do
			{
				ThreadMsgProc(msg);
			} while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE));
			break;
		case WAIT_THREAD_TIMEOUT:
			//LOG(_T("ClientStateMachine::ThreadProcEx, WAIT_THREAD_TIMEOUT.\n"));
			break;
		default:
			//LOG(_T("ClientStateMachine::ThreadProcEx, Default.\n"));
			break;
		}
	}
	return 0;
}