/*##############################################################################
 * 文件：msg_processor.h
 * 描述：MsgProcessor定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "client_core_define.h"

namespace clientcore
{

/*==============================================================================
 * 描述：消息处理框架核心类，内部定义了消息分发和消息处理策略，暂时没有考虑线程
 *       安全，后续需要完善！！！
==============================================================================*/
class MsgProcessor : public IMsgProcessor
{
public:
	MsgProcessor();

	//-- IMsgProcessor
	virtual void OnDownMsg(DownMsgType msg_type, const MsgData& msg_data) = 0;
	virtual void OnUpMsg(UpMsgType msg_type, const MsgData& msg_data) = 0;

	void SetDownMsgProcSuccessor(const IMsgProcessorSP& msg_processor);
	void SetDownMsgProcSuccessor(IMsgProcessor* msg_processor);
	void SetUpMsgProcSuccessor(const IMsgProcessorSP& msg_processor);
	void SetUpMsgProcSuccessor(IMsgProcessor* msg_processor);
	void SetDownMsgRoute(DownMsgType msg_type, const IMsgProcessorSP& msg_processor);
	void RemoveDownMsgRoute(DownMsgType msg_type);

protected:
	void AddDownMsgPreHandler(DownMsgType msg_type, DownMsgHandler msg_handler);
	void DelDownMsgPreHandler(DownMsgType msg_type);
	void AddDownMsgPostHandler(DownMsgType msg_type, DownMsgHandler msg_handler);
	void DelDownMsgPostHandler(DownMsgType msg_type);
	void AddUpMsgPreHandler(UpMsgType msg_type, UpMsgHandler msg_handler);
	void DelUpMsgPreHandler(UpMsgType msg_type);
	void AddUpMsgPostHandler(UpMsgType msg_type, UpMsgHandler msg_handler);
	void DelUpMsgPostHandler(UpMsgType msg_type);
	void SendDownMsg(DownMsgType msg_type, const MsgData& msg_data);
	void SendUpMsg(UpMsgType msg_type, const MsgData& msg_data);
	void OnDefaultDownMsg(DownMsgType msg_type, const MsgData& msg_data);
	void OnDefaultUpMsg(UpMsgType msg_type, const MsgData& msg_data);

protected:
	typedef std::map<DownMsgType, DownMsgHandler> DownMsgHandlerMap;

	// 下行消息的前处理器和后处理器，这些消息需要在节点上进行处理
	DownMsgHandlerMap m_down_msg_pre_handlers;
	DownMsgHandlerMap m_down_msg_post_handlers;

	typedef std::map<UpMsgType, UpMsgHandler> UpMsgHandlerMap;

	// 上行消息的前处理器和后处理器，这些消息需要在节点上进行处理
	UpMsgHandlerMap m_up_msg_pre_handlers;
	UpMsgHandlerMap m_up_msg_post_handlers;

	//-- 智能指针后继处节点
	// 尽量使用智能指针方式

	// 下行消息后继处理节点
	IMsgProcessorSP m_down_msg_proc_successor;

	// 上行消息后继处理节点
	IMsgProcessorSP m_up_msg_proc_successor;

	//-- 裸指针后继处理节点
	// 本来想只使用智能指针的后级处理器，考虑到外部消息处理对象不是使用
	// 智能指针来管理生命周期，此时share_from_this无法使用，因此，只能
	// 退而求其次，再额外提供裸指针方式的后继处理器，有点违和！！！
	
	// 下行消息后继处理节点
	IMsgProcessor* m_down_msg_proc_naked_successor;

	// 上行消息后继处理节点
	IMsgProcessor* m_up_msg_proc_naked_successor;

	typedef std::map<DownMsgType, IMsgProcessorSP> DownMsgRouteMap;

	// 明确指定消息路由
	// 当前只实现下行消息的路由指定，上行消息无法指定消息路由，必须由
	// 应用层逻辑去控制，消息路由指定上下行是不对称的。
	DownMsgRouteMap m_down_msg_route_map;
};

}