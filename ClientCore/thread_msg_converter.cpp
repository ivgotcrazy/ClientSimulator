/*##############################################################################
 * 文件：thread_msg_converter.h
 * 描述：ThreadMsgConverter实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "thread_msg_converter.h"
#include "client_public.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * 描  述：启动
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::Start()
{
	StartThread();
}

/*------------------------------------------------------------------------------
 * 描  述：停止
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::Stop()
{
	StopThread();
}

/*------------------------------------------------------------------------------
 * 描  述：添加下行消息处理器，当前只用作消息处理器校验
 * 参  数：[in] msg_processor 消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::AddDownMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_down_msg_processors.insert(msg_processor);
}

/*------------------------------------------------------------------------------
 * 描  述：删除下行消息处理器
 * 参  数：[in] msg_processor 消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::DelDownMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_down_msg_processors.erase(msg_processor);
}

/*------------------------------------------------------------------------------
 * 描  述：添加上行消息处理器，当前只用作消息处理器校验
 * 参  数：[in] msg_processor 消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::AddUpMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_up_msg_processors.insert(msg_processor);
}

/*------------------------------------------------------------------------------
 * 描  述：删除上行消息处理器
 * 参  数：[in] msg_processor 消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::DelUpMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_up_msg_processors.erase(msg_processor);
}

/*------------------------------------------------------------------------------
 * 描  述：消息线程转换处理
 * 参  数：[in] msg_type 消息类型
 *         [in] msg_data 消息数据
 *         [in] msg_source 消息源
 * 返回值：无
------------------------------------------------------------------------------*/
void ThreadMsgConverter::ThreadMsgProc(FS_UINT32 msg_type, const MsgData& msg_data, void* msg_source)
{
	if (msg_source == nullptr) // 必须要有消息源
	{
		LOG(_T("Msg without msg source, msg_type = %u.\n"), msg_type);
		return;
	}

	std::lock_guard<std::mutex> lock(m_processor_mutex);

	// 下行消息处理
	if (msg_type > DOWN_MSG_BEGIN && msg_type < DOWN_MSG_END)
	{
		IThreadMsgProcessor* processor = static_cast<IThreadMsgProcessor*>(msg_source);
		if (m_down_msg_processors.end() == m_down_msg_processors.find(processor))
		{
			LOG(_T("Failed to find msg processor.\n"));
			return;
		}

		processor->OnThreadDownMsg(static_cast<DownMsgType>(msg_type), msg_data);	
	}
	// 上行消息处理
	else if (msg_type > UP_MSG_BEGIN && msg_type < UP_MSG_END)
	{
		IThreadMsgProcessor* processor = static_cast<IThreadMsgProcessor*>(msg_source);
		if (m_up_msg_processors.end() == m_up_msg_processors.find(processor))
		{
			LOG(_T("Failed to find msg processor.\n"));
			return;
		}

		processor->OnThreadUpMsg(static_cast<UpMsgType>(msg_type), msg_data);
	}
	else
	{
		LOG(_T("Unexpected msg type = %u.\n"), msg_type);
	}	
}

