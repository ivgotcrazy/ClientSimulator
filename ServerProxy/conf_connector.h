/*##############################################################################
 * �ļ���conf_connector.h
 * ������ConfConnector����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "meeting_core_define.h"
#include "common_msg_processor.h"
#include "wthread_wrapper.h"
#include "xmlmsgiopack.h"

namespace meetingcore
{

/*==============================================================================
 * �����������������������������������ص���Ϣ��Ҫ�����˶���
==============================================================================*/
class ConfConnector 
	: public CommonMsgProcessor
	, public WThreadWrapper
{
public:
	ConfConnector(const ClientStateMachineSP& state_machine);

	bool Init();

	void SetRoomServiceList(const RoomServiceList& service_list);

private:
	void ProcessSessionEvent(SESSION_EVENT *session_event);
	void OnSessionCreated(SESSION_EVENT *session_event);
	void OnSessionClosed(SESSION_EVENT *session_event);
	void OnSessionCreateFailed(SESSION_EVENT *session_event);
	void ProcessSessionMsg(PBYTE data_ptr, FS_UINT32 data_len);

	virtual void ThreadMsgProc(const Thread_MSG& msg) override;

	WBASE_NOTIFY GetSessionNotify();

	bool OnLoginRoomMsg(const MsgData& msg_data);
	bool OnLoginRoomRep(TiXmlElement& element);
	void SendLoginRoomReq();
	bool OnInitCompleteMsg(const MsgData& msg_data);
	bool OnBroadcastUserAvInfoMsg(const MsgData& msg_data);
	bool OnUserStateChanged(TiXmlElement& element);
	bool OnUserAvInfoNotify(TiXmlElement& element);
	bool OnLogoutRoom(const MsgData& msg_data);
	bool OnUserEnterNotify(TiXmlElement& element);

private:
	ClientStateMachineSP	m_state_machine;
	FS_UINT16				m_conf_session_id;
	CXmlMsgIOPack			m_msg_sender;
	RoomServiceList			m_room_service_list;

	std::shared_ptr<LoginRoomReqMsg>	m_login_room_req_msg;
};

}