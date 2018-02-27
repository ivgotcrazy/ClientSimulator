/*##############################################################################
 * 文件：down_board_msg_processor.h
 * 描述：DownBoardMsgProcessor定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "msg_processor.h"
#include "wthread.h"
#include "client_core_define.h"
#include "thread_msg_converter.h"

using namespace WBASELIB;

namespace clientcore
{

/*==============================================================================
 * 描述：上边界消息处理器，上行消息在此节点会发生线程切换，用以保证内部处理永远
 *       是单线程。
==============================================================================*/
class DownBoardMsgProcessor 
	: public MsgProcessor
	, public IThreadMsgProcessor
{
public:
	void SetMsgConverter(const ThreadMsgConverterSP& msg_converter);

	//-- IMsgProcessor
	virtual void OnDownMsg(DownMsgType msg_type, const MsgData& msg_data) override;
	virtual void OnUpMsg(UpMsgType msg_type, const MsgData& msg_data) override;

	//-- IThreadMsgProcessor
	virtual void OnThreadDownMsg(DownMsgType msg_type, const MsgData& msg_data) override;
	virtual void OnThreadUpMsg(UpMsgType msg_type, const MsgData& msg_data) override;

	//-- 覆盖基类MsgProcessor实现
	void SendDownMsg(DownMsgType msg_type, const MsgData& msg_data);

private:
	ThreadMsgConverterSP m_msg_converter;
};

}