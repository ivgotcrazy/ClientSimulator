/*##############################################################################
 * 文件：conf_manager.h
 * 描述：ConfManager定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
 * 描述：会议交互相关处理，包括前置，向上屏蔽底层协议交互。
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