/*##############################################################################
 * 文件：thread_wrapper.h
 * 描述：WThreadWrapper定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "wthread.h"

using namespace WBASELIB;

namespace clientcore
{

/*==============================================================================
 * 描述：对WThread进行封装，使得上层使用更简单。
==============================================================================*/
class WThreadWrapper : public WThread
{
public:
	virtual void ThreadMsgProc(const Thread_MSG& msg) = 0;

private:
	virtual FS_UINT32 ThreadProcEx() override;
};

}