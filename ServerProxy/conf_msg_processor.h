/*##############################################################################
 * 文件：conf_msg_processor.h
 * 描述：ConfMsgProcessor定义
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "client_public.h"
#include "client_core_define.h"
#include "meeting_core_define.h"
#include "tinyxml.h"

using namespace WBASELIB;

namespace meetingcore
{

/*==============================================================================
 * 描述：会议相关消息构建和解析处理
==============================================================================*/
class ConfMsgProcessor
{
public:
	
	static TiXmlElement ConstructClientVerCheckReq(
		const WCHAR* product_id,
		const WCHAR* client_ver);

	static TiXmlElement ConstructLoginReq(
		const std::shared_ptr<LoginReqMsg>& login_msg);

	static TiXmlElement ConstructGetRoomListReq();

	static TiXmlElement ConstructLoginFrontRoomReq(
		const CHAR* room_node_id,
		FS_UINT32 room_id,
		FS_UINT32 room_app_id);

	static TiXmlElement ConstructLoginRoomReq(
		LoginRoomReqMsg* req_msg);

	static TiXmlElement ConstructInitCompleteMsg();

	static TiXmlElement ConstructUserAvInfoMsg(
		FS_UINT32 user_id,
		const AudioChannel& audio_channel, 
		const VideoChannelMap& video_channels);

	static TiXmlElement ConstructLogoutRoomMsg(
		FS_UINT32 user_id,
		FS_UINT32 room_id,
		const CHAR* room_srv_node_id);

	////////////////////////////////////////////////////////////////////////////

	static bool ParseClientVerCheckRep(
		const CHAR* data_ptr,
		FS_UINT32 data_len,
		UpdateCheckRepMsg* rep_msg);

	static bool ParseFrontUserLoginRep(
		TiXmlElement& element, 
		LoginRepMsg* rep_msg);

	static bool ParseGetRoomListRep(
		TiXmlElement& element,
		GetRoomListRepMsg* rep_msg);

	static bool ParseLoginFrontRoomRep(
		TiXmlElement& element,
		LoginFrontRoomRepMsg* rep_msg);

	static bool ParseLoginRoomRep(
		TiXmlElement& element,
		LoginRoomRepMsg* rep_msg);

	static bool ParseUserStateChangedMsg(
		TiXmlElement& element,
		UserStateChangedMsg* state_msg);

	static bool ParseUserAvInfoNotifyMsg(
		TiXmlElement& element,
		UserAvInfoNotifyMsg* notify_msg);

	static bool ParseUserEnterNotifyMsg(
		TiXmlElement &element,
		UserEnterNotifyMsg* notify_msg);
};

}
