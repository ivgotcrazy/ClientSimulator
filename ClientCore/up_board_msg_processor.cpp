/*##############################################################################
 * �ļ���up_board_msg_processor.cpp
 * ������UpBoardMsgProcessorʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "up_board_msg_processor.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ����[in] msg_converter ��Ϣ�߳�ת����
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::SetMsgConverter(const ThreadMsgConverterSP& msg_converter)
{
	m_msg_converter = msg_converter;
	m_msg_converter->AddUpMsgProcessor(this);
}

/*------------------------------------------------------------------------------
 * ��  �����ڵ��ϵ�������Ϣ����ʹ��Ĭ�ϴ���ʽ
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	OnDefaultDownMsg(msg_type, msg_data);
}

/*------------------------------------------------------------------------------
 * ��  �����ڵ��ϵ�������Ϣ�������ﲻ��ʹ��Ĭ�ϴ���ʽ����Ҫ����Ϣ���׸���Ϣ
 *         �߳�ת�������߳�ת����ͬʱ�����߳�ת�������Ϣ������һ�����ϡ�
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	if (m_msg_converter)
	{
		m_msg_converter->DeliverMessage(msg_type, msg_data, static_cast<IThreadMsgProcessor*>(this));
	}
	else
	{
		LOG(_T("Invalid msg converter.\n"));
	}
}

/*------------------------------------------------------------------------------
 * ��  ������Ϣת����������Ϣ�ص��Ľӿڣ�����UpBoardMsgProcessor��˵һ�㲻�����
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnThreadDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	LOG(_T("Unexpected DownUpMsgProcessor::OnThreadDownMsg.\n"));
}

/*------------------------------------------------------------------------------
 * ��  ������Ϣת����������Ϣ�ص��Ľӿڣ�ʹ��Ĭ�ϴ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnThreadUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	OnDefaultUpMsg(msg_type, msg_data);
}

/*------------------------------------------------------------------------------
 * ��  �����ڴ���ڵ��Ϸ���������Ϣ����ΪҪ����Ϣת������˲���ʹ��Ĭ�ϴ���
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::SendUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	OnUpMsg(msg_type, msg_data);
}