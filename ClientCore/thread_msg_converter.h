/*##############################################################################
 * �ļ���thread_msg_converter.h
 * ������ThreadMsgConverter����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include <set>
#include <mutex>

#include "msg_thread.h"
#include "client_core_define.h"

namespace clientcore
{

/*==============================================================================
 * ��������Ϣ�߳�ת����
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