/*##############################################################################
 * 文件：msg_thread.h
 * 描述：MsgThread相关声明/定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fs_types.h"
#include "client_public.h"

using namespace FsMeeting;

namespace clientcore
{

/*==============================================================================
 * 描述：消息定义
==============================================================================*/
struct QueueMsg
{
	QueueMsg() : msg_type(0), msg_source(nullptr) 
	{
	}

	QueueMsg(FS_UINT32 type, MsgData data, void* source)
		: msg_type(type), msg_data(data), msg_source(source)
	{
	}

	FS_UINT32	msg_type;
	MsgData		msg_data;
	void*		msg_source;
};

typedef std::queue<QueueMsg> QueueMsgList;

/*==============================================================================
 * 描述：消息队列定义
==============================================================================*/
class MsgQueue
{
public:
	MsgQueue(FS_UINT32 max_queue_size = 1024);

	bool PushMsg(QueueMsg msg);
	QueueMsg PopMsg();

private:
	QueueMsgList m_msg_list;
	std::mutex m_queue_mutex;
	std::condition_variable m_con_var;
	FS_UINT32 m_max_queue_size;
};

/*==============================================================================
 * 描述：消息处理线程
==============================================================================*/
class MsgThread
{
public:
	MsgThread();

	void StartThread();
	void StopThread();

	bool DeliverMessage(FS_UINT32 msg_type, const MsgData& msg_data, void* user_data);

	virtual void ThreadMsgProc(FS_UINT32 msg_type, const MsgData& msg_data, void* msg_source) = 0;

private:
	void ThreadProc();

private:
	MsgQueue m_msg_queue;

	std::thread m_thread;

	bool m_stop_flag;
};


}