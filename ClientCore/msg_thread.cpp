/*##############################################################################
 * �ļ���msg_thread.cpp
 * ������MsgThread���ʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "msg_thread.h"
#include <chrono>

using namespace clientcore;
using namespace std::chrono;

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ����[in] max_queue_size ��Ϣ���д�С
 * ����ֵ����
------------------------------------------------------------------------------*/
MsgQueue::MsgQueue(FS_UINT32 max_queue_size /* = 1024 */)
	: m_max_queue_size(max_queue_size)
{
}

/*------------------------------------------------------------------------------
 * ��  ����ѹ����Ϣ
 * ��  ����[in] msg ��Ϣ
 * ����ֵ���ɹ�/ʧ��
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
 * ��  ����������Ϣ
 * ��  ������
 * ����ֵ����Ϣ�������ǷǷ���Ϣ
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
 * ��  �������캯��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
MsgThread::MsgThread() : m_stop_flag(false)
{
#ifdef _WIN32
	HANDLE handle = m_thread.native_handle();
	
#endif
}

/*------------------------------------------------------------------------------
 * ��  ���������߳�
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgThread::StartThread()
{
	m_thread.swap(std::thread(&MsgThread::ThreadProc, this));
}

/*------------------------------------------------------------------------------
 * ��  ����ֹͣ�߳�
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgThread::StopThread()
{
	m_stop_flag = true;
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ�߳�Ͷ����Ϣ
 * ��  ����[in] msg_type ��Ϣ����
 *         [in] msg_data ��Ϣ����
 *         [in] msg_source ��ϢԴ��������ָ�߳�ת�������Ϣ������
 * ����ֵ���ɹ�/ʧ��
------------------------------------------------------------------------------*/
bool MsgThread::DeliverMessage(FS_UINT32 msg_type, const MsgData& msg_data, void* msg_source)
{
	return m_msg_queue.PushMsg(QueueMsg(msg_type, msg_data, msg_source));
}

/*------------------------------------------------------------------------------
 * ��  �����̺߳���
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgThread::ThreadProc()
{
	while (!m_stop_flag)
	{
		QueueMsg queue_msg = m_msg_queue.PopMsg();

		// 0������Ϣ��ʶΪ�Ƿ���Ϣ����������Ϣ���г�ʱ���ص�
		if (queue_msg.msg_type == 0)
			continue;

		ThreadMsgProc(queue_msg.msg_type, queue_msg.msg_data, queue_msg.msg_source);
	}
}
