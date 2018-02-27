/*##############################################################################
 * 文件：up_board_msg_processor.cpp
 * 描述：UpBoardMsgProcessor实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "up_board_msg_processor.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：[in] msg_converter 消息线程转换器
 * 返回值：无
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::SetMsgConverter(const ThreadMsgConverterSP& msg_converter)
{
	m_msg_converter = msg_converter;
	m_msg_converter->AddUpMsgProcessor(this);
}

/*------------------------------------------------------------------------------
 * 描  述：节点上的下行消息处理，使用默认处理方式
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_data 下行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	OnDefaultDownMsg(msg_type, msg_data);
}

/*------------------------------------------------------------------------------
 * 描  述：节点上的上行消息处理，这里不能使用默认处理方式，需要将消息先抛给消息
 *         线程转换器做线程转换，同时，将线程转换后的消息处理器一并附上。
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_data 上行消息数据
 * 返回值：无
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
 * 描  述：消息转换器下行消息回调的接口，对于UpBoardMsgProcessor来说一般不会调用
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_data 下行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnThreadDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	LOG(_T("Unexpected DownUpMsgProcessor::OnThreadDownMsg.\n"));
}

/*------------------------------------------------------------------------------
 * 描  述：消息转换器上行消息回调的接口，使用默认处理策略
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_data 上行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::OnThreadUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	OnDefaultUpMsg(msg_type, msg_data);
}

/*------------------------------------------------------------------------------
 * 描  述：在处理节点上发送上行消息，因为要做消息转换，因此不能使用默认处理
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_data 上行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void UpBoardMsgProcessor::SendUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	OnUpMsg(msg_type, msg_data);
}