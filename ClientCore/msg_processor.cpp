/*##############################################################################
 * 文件：msg_processor.cpp
 * 描述：MsgProcessor实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "msg_processor.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * 描  述：构造函数
 * 参  数：无
 * 返回值：无
------------------------------------------------------------------------------*/
MsgProcessor::MsgProcessor() : m_down_msg_proc_successor(nullptr)
	, m_up_msg_proc_successor(nullptr)
	, m_down_msg_proc_naked_successor(nullptr)
	, m_up_msg_proc_naked_successor(nullptr)
{
}

/*------------------------------------------------------------------------------
 * 描  述：使用智能指针设置消息后继处理节点
 * 参  数：[in] msg_processor 消息处理节点
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SetDownMsgProcSuccessor(const IMsgProcessorSP& msg_processor)
{
	m_down_msg_proc_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * 描  述：使用裸指针设置消息后继处理节点
 * 参  数：[in] msg_processor 消息处理节点
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SetDownMsgProcSuccessor(IMsgProcessor* msg_processor)
{
	m_down_msg_proc_naked_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * 描  述：使用智能指针设置消息后继处理节点
 * 参  数：[in] msg_processor 消息处理节点
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SetUpMsgProcSuccessor(const IMsgProcessorSP& msg_processor)
{
	m_up_msg_proc_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * 描  述：使用裸指针设置消息后继处理节点
 * 参  数：[in] msg_processor 消息处理节点
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SetUpMsgProcSuccessor(IMsgProcessor* msg_processor)
{
	m_up_msg_proc_naked_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * 描  述：设置下行消息路由，节省应用层代码
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_processor 消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SetDownMsgRoute(DownMsgType msg_type, const IMsgProcessorSP& msg_processor)
{
	MsgProcessor::m_down_msg_route_map.insert(std::make_pair(msg_type, msg_processor));
}

/*------------------------------------------------------------------------------
 * 描  述：移除下行消息路由，在某些场景有用，比如需要手动控制消息处理器声明周期
 * 参  数：[in] msg_type 下行消息类型
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::RemoveDownMsgRoute(DownMsgType msg_type)
{
	m_down_msg_route_map.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上添加下行消息前处理器
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_handler 下行消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::AddDownMsgPreHandler(DownMsgType msg_type, DownMsgHandler msg_handler)
{
	auto iter = m_down_msg_pre_handlers.find(msg_type);
	if (iter == m_down_msg_pre_handlers.end())
	{
		m_down_msg_pre_handlers.insert(std::make_pair(msg_type, msg_handler));
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上删除下行消息前处理器
 * 参  数：[in] msg_type 下行消息类型
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::DelDownMsgPreHandler(DownMsgType msg_type)
{
	m_down_msg_pre_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上添加下行消息后处理器
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_handler 下行消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::AddDownMsgPostHandler(DownMsgType msg_type, DownMsgHandler msg_handler)
{
	auto iter = m_down_msg_post_handlers.find(msg_type);
	if (iter == m_down_msg_post_handlers.end())
	{
		m_down_msg_post_handlers.insert(std::make_pair(msg_type, msg_handler));
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上删除下行消息后处理器
 * 参  数：[in] msg_type 下行消息类型
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::DelDownMsgPostHandler(DownMsgType msg_type)
{
	m_down_msg_post_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上添加上行消息前处理器
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_handler 上行消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::AddUpMsgPreHandler(UpMsgType msg_type, UpMsgHandler msg_handler)
{
	auto iter = m_up_msg_pre_handlers.find(msg_type);
	if (iter == m_up_msg_pre_handlers.end())
	{
		m_up_msg_pre_handlers.insert(std::make_pair(msg_type, msg_handler));
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上删除上行消息前处理器
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_handler 上行消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::DelUpMsgPreHandler(UpMsgType msg_type)
{
	m_up_msg_pre_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上添加上行消息后处理器
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_handler 上行消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::AddUpMsgPostHandler(UpMsgType msg_type, UpMsgHandler msg_handler)
{
	auto iter = m_up_msg_post_handlers.find(msg_type);
	if (iter == m_up_msg_post_handlers.end())
	{
		m_up_msg_post_handlers.insert(std::make_pair(msg_type, msg_handler));
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上删除上行消息后处理器
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_handler 上行消息处理器
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::DelUpMsgPostHandler(UpMsgType msg_type)
{
	m_up_msg_post_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上发送下行消息，此消息自动沿着消息链分发
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_data 下行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SendDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	//　优先使用智能指针后继消息处理器
	if (m_down_msg_proc_successor != nullptr)
	{
		m_down_msg_proc_successor->OnDownMsg(msg_type, msg_data);
	}
	// 然后使用裸指针后继消息处理器
	else if (m_down_msg_proc_naked_successor != nullptr)
	{
		m_down_msg_proc_naked_successor->OnDownMsg(msg_type, msg_data);
	}
	else // 找不到后继消息处理器，则进行消息路由
	{
		auto iter = m_down_msg_route_map.find(msg_type);
		if (iter != m_down_msg_route_map.end())
		{
			iter->second->OnDownMsg(msg_type, msg_data);
		}
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上发送上行消息，此消息自动沿着消息链分发
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_data 上行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::SendUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	//　优先使用智能指针后继消息处理器
	if (m_up_msg_proc_successor != nullptr)
	{
		m_up_msg_proc_successor->OnUpMsg(msg_type, msg_data);
	}
	else if (m_up_msg_proc_naked_successor != nullptr)
	{
		m_up_msg_proc_naked_successor->OnUpMsg(msg_type, msg_data);
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上下行消息默认处理策略
 * 参  数：[in] msg_type 下行消息类型
 *         [in] msg_data 下行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::OnDefaultDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	// 前处理
	auto pre_iter = m_down_msg_pre_handlers.find(msg_type);
	if (pre_iter != m_down_msg_pre_handlers.end())
	{
		if (!((pre_iter->second)(msg_data)))
			return; // 前处理完后不再传递
	}

	// 继续向下传递
	SendDownMsg(msg_type, msg_data);

	// 后处理
	auto post_iter = m_down_msg_post_handlers.find(msg_type);
	if (post_iter != m_down_msg_post_handlers.end())
	{
		(post_iter->second)(msg_data);
	}
}

/*------------------------------------------------------------------------------
 * 描  述：在消息处理节点上上行消息默认处理策略
 * 参  数：[in] msg_type 上行消息类型
 *         [in] msg_data 上行消息数据
 * 返回值：无
------------------------------------------------------------------------------*/
void MsgProcessor::OnDefaultUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	// 前处理
	auto pre_iter = m_up_msg_pre_handlers.find(msg_type);
	if (pre_iter != m_up_msg_pre_handlers.end())
	{
		if (!((pre_iter->second)(msg_data)))
			return;	// 前处理完后不再传递
	}

	// 继续向上传递
	SendUpMsg(msg_type, msg_data);

	// 后处理
	auto post_iter = m_up_msg_post_handlers.find(msg_type);
	if (post_iter != m_up_msg_post_handlers.end())
	{
		(post_iter->second)(msg_data);
	}
}