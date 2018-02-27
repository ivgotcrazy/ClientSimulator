/*##############################################################################
 * �ļ���thread_msg_converter.h
 * ������ThreadMsgConverterʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "thread_msg_converter.h"
#include "client_public.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * ��  ��������
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::Start()
{
	StartThread();
}

/*------------------------------------------------------------------------------
 * ��  ����ֹͣ
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::Stop()
{
	StopThread();
}

/*------------------------------------------------------------------------------
 * ��  �������������Ϣ����������ǰֻ������Ϣ������У��
 * ��  ����[in] msg_processor ��Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::AddDownMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_down_msg_processors.insert(msg_processor);
}

/*------------------------------------------------------------------------------
 * ��  ����ɾ��������Ϣ������
 * ��  ����[in] msg_processor ��Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::DelDownMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_down_msg_processors.erase(msg_processor);
}

/*------------------------------------------------------------------------------
 * ��  �������������Ϣ����������ǰֻ������Ϣ������У��
 * ��  ����[in] msg_processor ��Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::AddUpMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_up_msg_processors.insert(msg_processor);
}

/*------------------------------------------------------------------------------
 * ��  ����ɾ��������Ϣ������
 * ��  ����[in] msg_processor ��Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::DelUpMsgProcessor(IThreadMsgProcessor* msg_processor)
{
	std::lock_guard<std::mutex> lock(m_processor_mutex);

	m_up_msg_processors.erase(msg_processor);
}

/*------------------------------------------------------------------------------
 * ��  ������Ϣ�߳�ת������
 * ��  ����[in] msg_type ��Ϣ����
 *         [in] msg_data ��Ϣ����
 *         [in] msg_source ��ϢԴ
 * ����ֵ����
------------------------------------------------------------------------------*/
void ThreadMsgConverter::ThreadMsgProc(FS_UINT32 msg_type, const MsgData& msg_data, void* msg_source)
{
	if (msg_source == nullptr) // ����Ҫ����ϢԴ
	{
		LOG(_T("Msg without msg source, msg_type = %u.\n"), msg_type);
		return;
	}

	std::lock_guard<std::mutex> lock(m_processor_mutex);

	// ������Ϣ����
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
	// ������Ϣ����
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

