/*##############################################################################
 * �ļ���thread_wrapper.h
 * ������WThreadWrapper����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "wthread.h"

using namespace WBASELIB;

namespace clientcore
{

/*==============================================================================
 * ��������WThread���з�װ��ʹ���ϲ�ʹ�ø��򵥡�
==============================================================================*/
class WThreadWrapper : public WThread
{
public:
	virtual void ThreadMsgProc(const Thread_MSG& msg) = 0;

private:
	virtual FS_UINT32 ThreadProcEx() override;
};

}