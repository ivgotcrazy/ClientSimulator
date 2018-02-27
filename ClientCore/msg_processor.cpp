/*##############################################################################
 * �ļ���msg_processor.cpp
 * ������MsgProcessorʵ��
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "msg_processor.h"

using namespace clientcore;

/*------------------------------------------------------------------------------
 * ��  �������캯��
 * ��  ������
 * ����ֵ����
------------------------------------------------------------------------------*/
MsgProcessor::MsgProcessor() : m_down_msg_proc_successor(nullptr)
	, m_up_msg_proc_successor(nullptr)
	, m_down_msg_proc_naked_successor(nullptr)
	, m_up_msg_proc_naked_successor(nullptr)
{
}

/*------------------------------------------------------------------------------
 * ��  ����ʹ������ָ��������Ϣ��̴���ڵ�
 * ��  ����[in] msg_processor ��Ϣ����ڵ�
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SetDownMsgProcSuccessor(const IMsgProcessorSP& msg_processor)
{
	m_down_msg_proc_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * ��  ����ʹ����ָ��������Ϣ��̴���ڵ�
 * ��  ����[in] msg_processor ��Ϣ����ڵ�
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SetDownMsgProcSuccessor(IMsgProcessor* msg_processor)
{
	m_down_msg_proc_naked_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * ��  ����ʹ������ָ��������Ϣ��̴���ڵ�
 * ��  ����[in] msg_processor ��Ϣ����ڵ�
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SetUpMsgProcSuccessor(const IMsgProcessorSP& msg_processor)
{
	m_up_msg_proc_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * ��  ����ʹ����ָ��������Ϣ��̴���ڵ�
 * ��  ����[in] msg_processor ��Ϣ����ڵ�
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SetUpMsgProcSuccessor(IMsgProcessor* msg_processor)
{
	m_up_msg_proc_naked_successor = msg_processor;
}

/*------------------------------------------------------------------------------
 * ��  ��������������Ϣ·�ɣ���ʡӦ�ò����
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_processor ��Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SetDownMsgRoute(DownMsgType msg_type, const IMsgProcessorSP& msg_processor)
{
	MsgProcessor::m_down_msg_route_map.insert(std::make_pair(msg_type, msg_processor));
}

/*------------------------------------------------------------------------------
 * ��  �����Ƴ�������Ϣ·�ɣ���ĳЩ�������ã�������Ҫ�ֶ�������Ϣ��������������
 * ��  ����[in] msg_type ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::RemoveDownMsgRoute(DownMsgType msg_type)
{
	m_down_msg_route_map.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ������������Ϣǰ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_handler ������Ϣ������
 * ����ֵ����
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
 * ��  ��������Ϣ����ڵ���ɾ��������Ϣǰ������
 * ��  ����[in] msg_type ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::DelDownMsgPreHandler(DownMsgType msg_type)
{
	m_down_msg_pre_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ������������Ϣ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_handler ������Ϣ������
 * ����ֵ����
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
 * ��  ��������Ϣ����ڵ���ɾ��������Ϣ������
 * ��  ����[in] msg_type ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::DelDownMsgPostHandler(DownMsgType msg_type)
{
	m_down_msg_post_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ������������Ϣǰ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_handler ������Ϣ������
 * ����ֵ����
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
 * ��  ��������Ϣ����ڵ���ɾ��������Ϣǰ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_handler ������Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::DelUpMsgPreHandler(UpMsgType msg_type)
{
	m_up_msg_pre_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ������������Ϣ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_handler ������Ϣ������
 * ����ֵ����
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
 * ��  ��������Ϣ����ڵ���ɾ��������Ϣ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_handler ������Ϣ������
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::DelUpMsgPostHandler(UpMsgType msg_type)
{
	m_up_msg_post_handlers.erase(msg_type);
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ��Ϸ���������Ϣ������Ϣ�Զ�������Ϣ���ַ�
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SendDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	//������ʹ������ָ������Ϣ������
	if (m_down_msg_proc_successor != nullptr)
	{
		m_down_msg_proc_successor->OnDownMsg(msg_type, msg_data);
	}
	// Ȼ��ʹ����ָ������Ϣ������
	else if (m_down_msg_proc_naked_successor != nullptr)
	{
		m_down_msg_proc_naked_successor->OnDownMsg(msg_type, msg_data);
	}
	else // �Ҳ��������Ϣ���������������Ϣ·��
	{
		auto iter = m_down_msg_route_map.find(msg_type);
		if (iter != m_down_msg_route_map.end())
		{
			iter->second->OnDownMsg(msg_type, msg_data);
		}
	}
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ��Ϸ���������Ϣ������Ϣ�Զ�������Ϣ���ַ�
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::SendUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	//������ʹ������ָ������Ϣ������
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
 * ��  ��������Ϣ����ڵ���������ϢĬ�ϴ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::OnDefaultDownMsg(DownMsgType msg_type, const MsgData& msg_data)
{
	// ǰ����
	auto pre_iter = m_down_msg_pre_handlers.find(msg_type);
	if (pre_iter != m_down_msg_pre_handlers.end())
	{
		if (!((pre_iter->second)(msg_data)))
			return; // ǰ��������ٴ���
	}

	// �������´���
	SendDownMsg(msg_type, msg_data);

	// ����
	auto post_iter = m_down_msg_post_handlers.find(msg_type);
	if (post_iter != m_down_msg_post_handlers.end())
	{
		(post_iter->second)(msg_data);
	}
}

/*------------------------------------------------------------------------------
 * ��  ��������Ϣ����ڵ���������ϢĬ�ϴ������
 * ��  ����[in] msg_type ������Ϣ����
 *         [in] msg_data ������Ϣ����
 * ����ֵ����
------------------------------------------------------------------------------*/
void MsgProcessor::OnDefaultUpMsg(UpMsgType msg_type, const MsgData& msg_data)
{
	// ǰ����
	auto pre_iter = m_up_msg_pre_handlers.find(msg_type);
	if (pre_iter != m_up_msg_pre_handlers.end())
	{
		if (!((pre_iter->second)(msg_data)))
			return;	// ǰ��������ٴ���
	}

	// �������ϴ���
	SendUpMsg(msg_type, msg_data);

	// ����
	auto post_iter = m_up_msg_post_handlers.find(msg_type);
	if (post_iter != m_up_msg_post_handlers.end())
	{
		(post_iter->second)(msg_data);
	}
}