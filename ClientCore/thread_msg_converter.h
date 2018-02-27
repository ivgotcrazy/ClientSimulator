/*##############################################################################
 * 文件：thread_msg_converter.h
 * 描述：ThreadMsgConverter定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include <set>
#include <mutex>

#include "msg_thread.h"
#include "client_core_define.h"

namespace clientcore
{

/*==============================================================================
 * 描述：消息线程转换器
==============================================================================*/
class ThreadMsgConverter : public MsgThread
{
public:
	virtual void ThreadMsgProc(FS_UINT32 msg_type, const MsgData& msg_data, void* msg_source) override;

	void Start();
	void Stop();

	void AddDownMsgProcessor(IThreadMsgProcessor* msg_processor);
	void DelDownMsgProcessor(IThreadMsgProcessor* msg_processor);

	void AddUpMsgProcessor(IThreadMsgProcessor* msg_processor);
	void DelUpMsgProcessor(IThreadMsgProcessor* msg_processor);
	
private:
	std::set<IThreadMsgProcessor*> m_down_msg_processors;
	std::set<IThreadMsgProcessor*> m_up_msg_processors;

	std::mutex m_processor_mutex;
};
}