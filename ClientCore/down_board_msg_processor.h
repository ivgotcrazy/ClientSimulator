/*##############################################################################
 * �ļ���down_board_msg_processor.h
 * ������DownBoardMsgProcessor����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
 * �������ϱ߽���Ϣ��������������Ϣ�ڴ˽ڵ�ᷢ���߳��л������Ա�֤�ڲ�������Զ
 *       �ǵ��̡߳�
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

	//-- ���ǻ���MsgProcessorʵ��
	void SendDownMsg(DownMsgType msg_type, const MsgData& msg_data);

private:
	ThreadMsgConverterSP m_msg_converter;
};

}