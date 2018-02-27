/*##############################################################################
 * 文件：thread_wrapper.cpp
 * 描述：WThreadWrapper实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "wthread_wrapper.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * 描  述：线程消息处理函数，将线程处理框架封装起来，上层只需要实现ThreadMsgProc
 * 参  数：无
 * 返回值：未知
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