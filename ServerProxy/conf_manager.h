/*##############################################################################
 * �ļ���conf_manager.h
 * ������ConfManager����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "wthread.h"
#include "meeting_core_define.h"
#include "up_board_msg_processor.h"
#include "update_checker.h"
#include "front_connector.h"
#include "conf_connector.h"
#include "xmlmsgiopack.h"

using namespace FsMeeting;
using namespace WBASELIB;

namespace meetingcore
{

/*==============================================================================
 * ���������齻����ش�������ǰ�ã��������εײ�Э�齻����
==============================================================================*/
class ConfManager 
	: public UpBoardMsgProcessor
	, public std::enable_shared_from_this<ConfManager>
{
public:
	ConfManager(const ClientStateMachineSP& state_machine);

	bool Init();

private:
	bool OnLoginFrontRoomRep(const MsgData& msg_data);
	bool OnInitCompleteMsg(const MsgData& msg_data);

private:
	ClientStateMachineSP m_state_machine;
	std::string m_server_addr;

	std::shared_ptr<UpdateChecker>	m_update_checker;
	std::shared_ptr<FrontConnector>	m_front_connector;
	std::shared_ptr<ConfConnector>	m_conf_connector;

	CXmlMsgIOPack	m_msg_sender;
};

}