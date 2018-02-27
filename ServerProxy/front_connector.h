/*##############################################################################
 * 文件：front_connector.h
 * 描述：FrontConnector定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "wthread_wrapper.h"
#include "xmlmsgiopack.h"

namespace meetingcore
{

/*==============================================================================
 * 描述：前置服务连接器，所有与前置服务相关的消息都要经过此对象（版本控制除外）。
==============================================================================*/
class FrontConnector 
	: public CommonMsgProcessor
	, public WThreadWrapper
{
public:
	FrontConnector(const ClientStateMachineSP& state_machine);
	~FrontConnector();

	bool Init();

private:
	virtual void ThreadMsgProc(const Thread_MSG& msg) override;

	void ProcessSessionEvent(SESSION_EVENT *session_event);
	void OnSessionCreated(SESSION_EVENT *session_event);
	void OnSessionClosed(SESSION_EVENT *session_event);
	void OnSessionCreateFailed(SESSION_EVENT *session_event);
	void ProcessSessionMsg(PBYTE data_ptr, FS_UINT32 data_len);

	void SendLoginReq();
	bool OnLoginByUserMsg(const MsgData& msg_data);
	void OnUserLoginRep(TiXmlElement& element);

	void SendGetRoomListReq();
	bool OnGetRoomListMsg(const MsgData& msg_data);
	void OnGetRoomListRep(TiXmlElement& element);

	void OnLoginFrontRoomRep(TiXmlElement& element);
	bool OnLoginFrontRoomMsg(const MsgData& msg_data);

	WBASE_NOTIFY GetSessionNotify();

private:
	ClientStateMachineSP m_state_machine;

	FS_UINT16 m_front_session_id;

	std::shared_ptr<LoginReqMsg> m_login_msg;

	CXmlMsgIOPack	m_msg_sender;
};

}

