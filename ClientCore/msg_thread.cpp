/*##############################################################################
 * 文件：msg_thread.cpp
 * 描述：MsgThread相关实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "msg_thread.h"
#include <chrono>

using namespace clientcore;
using namespace std::chrono;

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：[in] max_queue_size 消息队列大小
 * 返回值：无
------------------------------------------------------------------------------*/
MsgQueue::MsgQueue(FS_UINT32 max_queue_size /* = 1024 */)
	: m_max_queue_size(max_queue_size)
{
}

/*------------------------------------------------------------------------------
 * 描  述：压入消息
 * 参  数：[in] msg 消息
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool MsgQueue::PushMsg(QueueMsg msg)
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);

	if (m_msg_list.size() >= m_max_queue_size)
		return false;

	m_msg_list.push(msg);

	m_con_var.notify_one();

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：弹出消息
 * 参  数：无
 * 返回值：消息，可能是非法消息
------------------------------------------------------------------------------*/
QueueMsg MsgQueue::PopMsg()
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);

	if (m_msg_list.empty())
	{
		std::cv_status ret = m_con_var.wait_until(lock,
			system_clock::now() + milliseconds(10));
		if (ret == std::cv_status::timeout || m_msg_list.empty())
			return QueueMsg();
	}

	QueueMsg msg_data = m_msg_list.front();
	m_msg_list.pop();

	return msg_data;
}

////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
MsgThread::MsgThread() : m_stop_flag(false)
{
#ifdef _WIN32
	HANDLE handle = m_thread.native_handle();
	
#endif
}

/*------------------------------------------------------------------------------
 * 描  述：启动线程
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgThread::StartThread()
{
	m_thread.swap(std::thread(&MsgThread::ThreadProc, this));
}

/*------------------------------------------------------------------------------
 * 描  述：停止线程
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgThread::StopThread()
{
	m_stop_flag = true;
}

/*------------------------------------------------------------------------------
 * 描  述：向消息线程投递消息
 * 参  数：[in] msg_type 消息类型
 *         [in] msg_data 消息数据
 *         [in] msg_source 消息源，这里特指线程转换后的消息处理器
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool MsgThread::DeliverMessage(FS_UINT32 msg_type, const MsgData& msg_data, void* msg_source)
{
	return m_msg_queue.PushMsg(QueueMsg(msg_type, msg_data, msg_source));
}

/*------------------------------------------------------------------------------
 * 描  述：线程函数
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgThread::ThreadProc()
{
	while (!m_stop_flag)
	{
		QueueMsg queue_msg = m_msg_queue.PopMsg();

		// 0类型消息标识为非法消息，可能是消息队列超时返回的
		if (queue_msg.msg_type == 0)
			continue;

		ThreadMsgProc(queue_msg.msg_type, queue_msg.msg_data, queue_msg.msg_source);
	}
}
