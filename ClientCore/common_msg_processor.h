/*##############################################################################
 * 文件：common_msg_processor.h
 * 描述：CommonMsgProcessor定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "msg_processor.h"

namespace clientcore
{

/*==============================================================================
 * 描述：普通消息处理器封装，消息分发不会发生线程切换
==============================================================================*/
class CommonMsgProcessor : public MsgProcessor
{
public:
	virtual void OnDownMsg(DownMsgType msg_type, const MsgData& msg_data) override
	{
		OnDefaultDownMsg(msg_type, msg_data);
	}

	virtual void OnUpMsg(UpMsgType msg_type, const MsgData& msg_data) override
	{
		OnDefaultUpMsg(msg_type, msg_data);
	}
};

}