/*##############################################################################
 * �ļ���msg_processor.h
 * ������MsgProcessor����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "client_core_define.h"

namespace clientcore
{

/*==============================================================================
 * ��������Ϣ�����ܺ����࣬�ڲ���������Ϣ�ַ�����Ϣ������ԣ���ʱû�п����߳�
 *       ��ȫ��������Ҫ���ƣ�����
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

	// ������Ϣ��ǰ�������ͺ���������Щ��Ϣ��Ҫ�ڽڵ��Ͻ��д���
	DownMsgHandlerMap m_down_msg_pre_handlers;
	DownMsgHandlerMap m_down_msg_post_handlers;

	typedef std::map<UpMsgType, UpMsgHandler> UpMsgHandlerMap;

	// ������Ϣ��ǰ�������ͺ���������Щ��Ϣ��Ҫ�ڽڵ��Ͻ��д���
	UpMsgHandlerMap m_up_msg_pre_handlers;
	UpMsgHandlerMap m_up_msg_post_handlers;

	//-- ����ָ���̴��ڵ�
	// ����ʹ������ָ�뷽ʽ

	// ������Ϣ��̴���ڵ�
	IMsgProcessorSP m_down_msg_proc_successor;

	// ������Ϣ��̴���ڵ�
	IMsgProcessorSP m_up_msg_proc_successor;

	//-- ��ָ���̴���ڵ�
	// ������ֻʹ������ָ��ĺ󼶴����������ǵ��ⲿ��Ϣ���������ʹ��
	// ����ָ���������������ڣ���ʱshare_from_this�޷�ʹ�ã���ˣ�ֻ��
	// �˶�����Σ��ٶ����ṩ��ָ�뷽ʽ�ĺ�̴��������е�Υ�ͣ�����
	
	// ������Ϣ��̴���ڵ�
	IMsgProcessor* m_down_msg_proc_naked_successor;

	// ������Ϣ��̴���ڵ�
	IMsgProcessor* m_up_msg_proc_naked_successor;

	typedef std::map<DownMsgType, IMsgProcessorSP> DownMsgRouteMap;

	// ��ȷָ����Ϣ·��
	// ��ǰֻʵ��������Ϣ��·��ָ����������Ϣ�޷�ָ����Ϣ·�ɣ�������
	// Ӧ�ò��߼�ȥ���ƣ���Ϣ·��ָ���������ǲ��ԳƵġ�
	DownMsgRouteMap m_down_msg_route_map;
};

}