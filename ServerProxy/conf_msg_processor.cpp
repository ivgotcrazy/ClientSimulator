/*##############################################################################
 * 文件：conf_msg_processor.cpp
 * 描述：ConfMsgProcessor实现
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#include "stdafx.h"
#include "conf_msg_processor.h"
#include "xmlprotocolparser.h"
#include "ConfProtocol.h"
#include "FrontProtocol.h"
#include "ProtocolError.h"
#include "UpdateMgrProtocol.h"

using namespace meetingcore;
//#pragma warning(disable:4786)

/*------------------------------------------------------------------------------
 * 描  述：构造客户端版本检查请求消息
 * 参  数：[in] product_id 产品ID
 *         [in] client_ver 客户端版本
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructClientVerCheckReq(
	const WCHAR* product_id, const WCHAR* client_ver)
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, UPDATE_CMDID_VERSIONREQ);
	WXmlParser_SetVersion(&element, UPDATE_PROTOCOL_VERSION);
	WXmlParser_AddFieldValue(&element, "ProductID", product_id);
	WXmlParser_AddFieldValue(&element, "Version", client_ver);

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造登录前置请求消息
 * 参  数：[in] login_msg 登录消息数据
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructLoginReq(
	const std::shared_ptr<LoginReqMsg>& login_msg)
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, FRONT_CMDID_TERMINAL_USERLOGIN_REQ);
	WXmlParser_SetVersion(&element, FRONT_PROTOCOL_VERSION);
	WXmlParser_AddFieldValue(&element, "ClientType", login_msg->client_type); // VIDEOCONF_CLIENT
	WXmlParser_AddFieldValue(&element, "TerminalType", login_msg->terminal_type); // DESKTOP_CLIENT
	WXmlParser_AddFieldValue(&element, "UserType", login_msg->user_type); // USERTYPE_REGISTER
	WXmlParser_AddFieldValue(&element, "AppType", (WORD)(login_msg->room_app_id));
	WXmlParser_AddFieldValue(&element, "UserLoginType", 1); // 用户账号登录
	WXmlParser_AddFieldValue(&element, "UserName", login_msg->user_name.c_str());
	WXmlParser_AddFieldValue(&element, "ProductName", login_msg->product_name.c_str());
	WXmlParser_AddFieldValue(&element, "UserPassword", login_msg->user_pwd.c_str());
	WXmlParser_AddFieldValue(&element, "LoginServerAddr", login_msg->server_addr.c_str());

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造获取会议室列表请求消息
 * 参  数：无
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructGetRoomListReq()
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, FRONT_CMDID_TERMINAL_ROOMLIST_REQ);
	WXmlParser_SetVersion(&element, FRONT_PROTOCOL_VERSION);
	WXmlParser_AddFieldValue(&element, "IsGetAllList", 1);
	WXmlParser_AddFieldValue(&element, "IsGetRoomDesc", 0);

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造登录前置房间请求消息
 * 参  数：[in] room_node_id 房间节点ID
 *         [in] room_id 房间ID
 *         [in] room_app_id AppID
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructLoginFrontRoomReq(
	const CHAR* room_node_id,
	FS_UINT32 room_id,
	FS_UINT32 room_app_id)
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, FRONT_CMDID_TERMINAL_LOGINROOM_REQ);
	WXmlParser_SetVersion(&element, FRONT_PROTOCOL_VERSION);
	WXmlParser_AddFieldValue(&element, "RoomID", room_id);
	WXmlParser_AddFieldValue(&element, "RoomNodeID", room_node_id);
	WXmlParser_AddFieldValue(&element, "RoomAppID", room_app_id);

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造登录房间请求消息
 * 参  数：[in] req_msg 请求消息数据
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructLoginRoomReq(LoginRoomReqMsg* req_msg)
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, CONF_CMDID_LOGINREQ);
	WXmlParser_SetVersion(&element, CONF_PROTOCOL_VERSION);
	WXmlParser_AddFieldValue(&element, "ClientType", req_msg->client_type);
	WXmlParser_AddFieldValue(&element, "TerminalType", req_msg->terminal_type);
	WXmlParser_AddFieldValue(&element, "RoomSrvNodeID", req_msg->room_srv_node_id.c_str());
	WXmlParser_AddFieldValue(&element, "RoomID", req_msg->room_id);
	WXmlParser_AddFieldValue(&element, "UserID", req_msg->user_id);
	WXmlParser_AddFieldValue(&element, "UserName", req_msg->user_name.c_str());
	WXmlParser_AddFieldValue(&element, "UserType", req_msg->user_type);
	WXmlParser_AddFieldValue(&element, "Token", req_msg->token.c_str());
	WXmlParser_AddFieldValue(&element, "VerifyMode", req_msg->verify_mode);
	WXmlParser_AddFieldValue(&element, "RoomPassword", req_msg->room_password.c_str());
	WXmlParser_AddFieldValue(&element, "LanCode", req_msg->lan_code);
	WXmlParser_AddFieldValue(&element, "LoginServerAddr", "");

	TiXmlElement CapaElement("Capability");
	TiXmlElement *pElement = element.InsertEndChild(CapaElement)->ToElement();

	WXmlParser_AddFieldValue(pElement, "Mode", req_msg->client_mode);
	WXmlParser_AddFieldValue(pElement, "DownBitrate", req_msg->download_bitrate);

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造初始化完成消息
 * 参  数：无
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructInitCompleteMsg()
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, CONF_CMDID_INITCOMPLETE);

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造用户音视频信息消息
 * 参  数：[in] user_id 用户ID
 *         [in] audio_channel 音频通道
 *         [in] video_channels 视频通道
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructUserAvInfoMsg(
	FS_UINT32 user_id,
	const AudioChannel& audio_channel,
	const VideoChannelMap& video_channels)
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, CONF_CMDID_AVINFO);
	WXmlParser_AddFieldValue(&element, "UserID", user_id);
	if (audio_channel.has_audio)
	{
		TiXmlElement audioElement("Audio");
		TiXmlElement* pElement = element.InsertEndChild(audioElement)->ToElement();
		WXmlParser_AddFieldValue(pElement, "Operation", audio_channel.operation);
		WXmlParser_AddFieldValue(pElement, "ID", audio_channel.media_id);
		WXmlParser_AddFieldValue(pElement, "Name", audio_channel.dev_name.c_str());
	}

	VideoChannelMap::const_iterator it;
	for (it = video_channels.begin(); it != video_channels.end(); it++)
	{
		TiXmlElement videoElement("Video");
		TiXmlElement* pElement = element.InsertEndChild(videoElement)->ToElement();
		WXmlParser_AddFieldValue(pElement, "Operation", (*it).second.operation);
		WXmlParser_AddFieldValue(pElement, "ID", (*it).second.media_id);
		WXmlParser_AddFieldValue(pElement, "Name", (*it).second.dev_name.c_str());
	}

	return element;
}

/*------------------------------------------------------------------------------
 * 描  述：构造登出消息
 * 参  数：[in] user_id 用户ID
 *         [in] room_id RoomID
 *         [in] room_srv_node_id ID
 * 返回值：消息
------------------------------------------------------------------------------*/
TiXmlElement ConfMsgProcessor::ConstructLogoutRoomMsg(
	FS_UINT32 user_id,
	FS_UINT32 room_id,
	const CHAR* room_srv_node_id)
{
	TiXmlElement element("cmd");
	WXmlParser_SetCommand(&element, CONF_CMDID_LOGOUTREQ);
	WXmlParser_AddFieldValue(&element, "UserID", user_id);
	WXmlParser_AddFieldValue(&element, "RoomID", room_id);
	WXmlParser_AddFieldValue(&element, "RoomSrvNodeID", room_srv_node_id);

	return element;
}

////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------------
 * 描  述：解析版本检查响应消息
 * 参  数：[in] data_ptr 消息数据
 *         [in] data_len 消息长度
 *         [in] rep_msg 响应消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseClientVerCheckRep(
	const CHAR* data_ptr, 
	FS_UINT32 data_len, 
	UpdateCheckRepMsg* rep_msg)
{
	TiXmlElement element("cmd");
	if (!WXmlParser_LoadCommand(element, data_ptr, data_len))
	{
		LOG(_T("Client Update,WXmlParser_LoadCommand Failed.\n"));
		return false;
	}

	WORD command;
	if (!WXmlParser_GetCommand(&element, command)){
		LOG(_T("Client Update,WXmlParser_GetCommand Failed.\n"));
		return false;
	}

	if (command != UPDATE_CMDID_VERSIONREP){
		LOG(_T("Client Update,Invalid Command,Command = %d.\n"), command);
		return false;
	}

	const CHAR* value = NULL;
	value = WXmlParser_GetFieldValue(&element, "NewVersion");
	if (value)
		rep_msg->last_ver = value;

	value = WXmlParser_GetFieldValue(&element, "MinVersion");
	if (value)
		rep_msg->min_ver = value;

	rep_msg->download_url.clear();
	TiXmlElement* child_element = element.FirstChildElement("DownloadURL");
	while (child_element)
	{
		value = child_element->Attribute("val");
		if (value)
			rep_msg->download_url.push_back(value);

		child_element = child_element->NextSiblingElement("DownloadURL");
	}

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：解析登录前置响应消息
 * 参  数：[in] element 消息数据
 *         [in] rep_msg 响应消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseFrontUserLoginRep(TiXmlElement& element, 
	LoginRepMsg* rep_msg)
{
	assert(rep_msg);

	const CHAR* value = NULL;

	WXmlParser_GetFieldValue(&element, "Result", rep_msg->login_result);
	if (rep_msg->login_result == WPROTOCOL_RESULT_SUCCESS)
	{
		value = WXmlParser_GetFieldValue(&element, "LocalNodeID");
		if (NULL == value)
		{
			LOG(_T("Failed to get 'LocalNodeID' filed.\n"));
			return false;
		}
		rep_msg->local_node_id = value;

		WXmlParser_GetFieldValue(&element, "LocalUserID", rep_msg->local_user_id);
	}

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：解析获取会议室列表响应消息
 * 参  数：[in] element 消息数据
 *         [in] rep_msg 响应消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseGetRoomListRep(TiXmlElement& element, 
	GetRoomListRepMsg* rep_msg)
{
	int	nValue = -1;

	WXmlParser_GetFieldValue( &element,"Result",rep_msg->get_result );
	if (rep_msg->get_result == WPROTOCOL_RESULT_SUCCESS)
	{
		const CHAR* szValue = NULL;
		BOOL  bIsTopNode = TRUE;
		const CHAR* szRoomNodeID = WXmlParser_GetFieldValue( &element,"RoomNodeID" );
		if( NULL == szRoomNodeID )
			return false;
		if( WXmlParser_GetFieldValue( &element,"IsTopNode",nValue ))
			bIsTopNode = nValue;		
		//RoomInfo
		TiXmlElement *pElement = element.FirstChildElement("RoomInfo");
		while( pElement )
		{
			FrontRoomInfo info;
			info.is_top_node = bIsTopNode;
			info.room_node_id = szRoomNodeID;

			szValue = WXmlParser_GetFieldValue( pElement,"Name" );
			if( NULL != szValue )
				info.room_name = szValue;
			WXmlParser_GetFieldValue( pElement,"RoomAppID",nValue );
			info.room_app_id = nValue;
			WXmlParser_GetFieldValue( pElement,"MaxUserCount",nValue );
			info.max_user_count = nValue;
			WXmlParser_GetFieldValue( pElement,"CurUserCount",nValue );
			info.cur_user_count = nValue;
			WXmlParser_GetFieldValue( pElement,"RoomID",nValue );
			info.room_id = nValue;

			rep_msg->room_list.push_back(info);

			pElement = pElement->NextSiblingElement("RoomInfo");
		}
	}

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：解析登录前置房间响应消息
 * 参  数：[in] element 消息数据
 *         [in] rep_msg 响应消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseLoginFrontRoomRep(TiXmlElement& element, 
	LoginFrontRoomRepMsg* rep_msg)
{
	int	nValue = -1;
	const CHAR* szValue = NULL;
	RoomInfo info;
	WXmlParser_GetFieldValue(&element, "Result", rep_msg->login_result);
	rep_msg->is_top_node = TRUE;

	if (rep_msg->login_result == WPROTOCOL_RESULT_SUCCESS)
	{
		szValue = WXmlParser_GetFieldValue( &element,"RoomNodeID" );
		if( szValue )
			rep_msg->room_node_id = szValue;
		WXmlParser_GetFieldValue( &element,"RoomID",nValue );
		rep_msg->room_id = nValue;
		WXmlParser_GetFieldValue( &element,"UserRight",nValue );
		rep_msg->user_right = static_cast<UserRight>(nValue);
		nValue = 1;
		WXmlParser_GetFieldValue( &element,"RoomVerifyMode",nValue );
		rep_msg->verify_mode = static_cast<VerifyMode>(nValue);
		nValue = 0;
		WXmlParser_GetFieldValue( &element,"RoomUserID",nValue );
		rep_msg->room_user_id = nValue;
		szValue = WXmlParser_GetFieldValue( &element, "RoomSrvNodeID" );
		if (szValue)
			rep_msg->room_srv_node_id = szValue;
		szValue = WXmlParser_GetFieldValue( &element, "Token" );
		if (szValue)
			rep_msg->token = szValue;

		TCHAR szTemp[128];
		szTemp[0] = 0;
		TiXmlElement *pSrvElement = element.FirstChildElement("Server");
		while( pSrvElement )
		{
			const CHAR* szSrvAddr = WXmlParser_GetFieldValue( pSrvElement, "SrvAddr" );
			const CHAR* szSrvName = WXmlParser_GetFieldValue( pSrvElement, "SrvName" );
			if( szSrvAddr && szSrvName )
			{
				RoomServiceInfo srvInfo;
				srvInfo.srv_addr = szSrvAddr;
				ConvertUtf8ToUnicode(szSrvName, szTemp, 128);
				srvInfo.srv_name = szTemp;
				rep_msg->srv_list.push_back( srvInfo );
			}
			pSrvElement = pSrvElement->NextSiblingElement("Server");
		}
	}

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：解析登录房间响应消息
 * 参  数：[in] element 消息数据
 *         [in] rep_msg 响应消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseLoginRoomRep(TiXmlElement& element, 
	LoginRoomRepMsg* rep_msg)
{
#define STRING_BUFFER_SIZE		512

	const CHAR*	szVersion = WXmlParser_GetVersion(&element);

	int nResult = -1;
	WXmlParser_GetFieldValue( &element,"Result",nResult );
	rep_msg->login_result = nResult;

	const CHAR* szUserSrvNodeID = WXmlParser_GetFieldValue( &element,"UserSrvNodeID" );

	if( szVersion )
		rep_msg->room_srv_info.strConfSrvProtocolVersion = szVersion;

	rep_msg->room_info.bEnableChat = TRUE;
	rep_msg->room_info.bEnableP2PChat = TRUE;
	rep_msg->room_info.bEnablePubChat = TRUE;
	rep_msg->room_info.bEnableSendFile = TRUE;
	rep_msg->room_info.bEnableSaveWB = FALSE;
	rep_msg->room_info.bReservePresenterVideo = FALSE;
	rep_msg->room_info.bWaterMarkState = FALSE;

	if( nResult == WPROTOCOL_RESULT_SUCCESS )
	{
		int			nValue = -1;
		const CHAR* szValue = NULL;
		TCHAR		szTemp[128];
		ZeroMemory( szTemp,sizeof(szTemp));

		//获取节点信息
		TiXmlElement *pNodeElement = element.FirstChildElement( "NodeInfo" );
		if(pNodeElement)
		{
			TiXmlElement *pNode = pNodeElement->FirstChildElement( "Node" );
			while (pNode)
			{
				DeptNodeInfo depNode;
				depNode.nNodeType = 1;

				if( szValue = WXmlParser_GetFieldValue(pNode,"NodeID")){
					if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
						depNode.strNodeID = szTemp;
				}

				if( szValue = WXmlParser_GetFieldValue(pNode,"NodeName")){
					if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
						depNode.strNodeName = szTemp;
				}

				if( szValue = WXmlParser_GetFieldValue(pNode,"ParentNodeID")){
					if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
						depNode.strParentID = szTemp;	
				}

				rep_msg->node.push_back(depNode);	
				pNode = pNode->NextSiblingElement( "Node" );
			}
		}

		//获取部门信息
		TiXmlElement *pDeptElement = element.FirstChildElement( "DeptInfo" );
		if(pDeptElement)
		{
			TiXmlElement *pNode = pDeptElement->FirstChildElement( "Dept" );
			while (pNode)
			{

				DeptNodeInfo depNode;
				depNode.nNodeType = 2;

				if( szValue = WXmlParser_GetFieldValue(pNode,"DeptID")){
					if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
						depNode.strNodeID = szTemp;
				}

				if( szValue = WXmlParser_GetFieldValue(pNode,"DeptName")){
					if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
						depNode.strNodeName = szTemp;
				}

				if( szValue = WXmlParser_GetFieldValue(pNode,"ParentDeptID")){
					if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
						depNode.strParentID = szTemp;	
				}

				rep_msg->dept.push_back(depNode);	
				pNode = pNode->NextSiblingElement( "Dept" );
			}
		}

		TiXmlElement *pRoomElement = element.FirstChildElement( "RoomInfo" );
		if( pRoomElement )
		{
			if( szValue = WXmlParser_GetFieldValue(pRoomElement,"Name"))
			{
				if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE))
					rep_msg->room_info.strRoomName = szTemp;						
			}
			if( WXmlParser_GetFieldValue( pRoomElement,"Mode",nValue ))
				rep_msg->room_info.bRoomMode = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"Lock",nValue))
				rep_msg->room_info.bRoomLock = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnableRecord",nValue ))
				rep_msg->room_info.bEnableRecord = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnableChat",nValue ))
				rep_msg->room_info.bEnableChat = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnableP2PChat",nValue ))
				rep_msg->room_info.bEnableP2PChat = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnablePubChat",nValue ))
				rep_msg->room_info.bEnablePubChat = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnableSendFile",nValue ))
				rep_msg->room_info.bEnableSendFile = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnableSaveWB",nValue ))
				rep_msg->room_info.bEnableSaveWB = nValue;
			if( WXmlParser_GetFieldValue( pRoomElement,"EnableKeepVideo",nValue ))
				rep_msg->room_info.bReservePresenterVideo = nValue;
			rep_msg->room_info.tStartTime = time(NULL);
			int nStartTime,nCurTime;
			if( WXmlParser_GetFieldValue( pRoomElement,"StartTime",nStartTime ) &&
				WXmlParser_GetFieldValue( pRoomElement,"CurTime",nCurTime ) ){
				rep_msg->room_info.tStartTime -= (nCurTime - nStartTime);
			}

			TiXmlElement *pConfigElement = pRoomElement->FirstChildElement("RoomConfig" );
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableAudio",nValue ))
				rep_msg->room_config.bEnableAudio = nValue;
			else
				rep_msg->room_config.bEnableAudio = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableVideo",nValue ))
				rep_msg->room_config.bEnableVideo = nValue;
			else
				rep_msg->room_config.bEnableVideo = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableWB",nValue ))
				rep_msg->room_config.bEnableWB = nValue;
			else
				rep_msg->room_config.bEnableWB = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableApp",nValue ))
				rep_msg->room_config.bEnableApp = nValue;
			else
				rep_msg->room_config.bEnableApp = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableMedia",nValue ))
				rep_msg->room_config.bEnableMedia = nValue;
			else
				rep_msg->room_config.bEnableMedia = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableWeb",nValue ))
				rep_msg->room_config.bEnableWEB = nValue;
			else
				rep_msg->room_config.bEnableWEB = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableChat",nValue ))
				rep_msg->room_config.bEnableChat = nValue;
			else
				rep_msg->room_config.bEnableChat = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableFile",nValue ))
				rep_msg->room_config.bEnableFile = nValue;
			else
				rep_msg->room_config.bEnableFile = TRUE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableVote",nValue ))
				rep_msg->room_config.bEnableVote = nValue;
			else
				rep_msg->room_config.bEnableVote = TRUE;

			if( WXmlParser_GetFieldValue(pConfigElement,"EnablePhoneInvite",nValue )) //loki 2015-01-20
				rep_msg->room_config.bEnablePhoneInvite = nValue;
			else
				rep_msg->room_config.bEnablePhoneInvite = TRUE;

			if( WXmlParser_GetFieldValue(pConfigElement,"EnableMultiVideo",nValue ))
				rep_msg->room_config.bEnableMultiVideo = nValue;
			else
				rep_msg->room_config.bEnableMultiVideo = FALSE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableDualDisp",nValue ))
				rep_msg->room_config.bEnableDualDisp = nValue;
			else
				rep_msg->room_config.bEnableDualDisp = FALSE;
			if( WXmlParser_GetFieldValue(pConfigElement,"EnableAVMix",nValue ))
				rep_msg->room_config.bEnableAVMix = nValue;
			else
				rep_msg->room_config.bEnableAVMix = FALSE;
			if( WXmlParser_GetFieldValue(pConfigElement,"WndMode",nValue ))
				rep_msg->room_config.bWndMode = nValue;
			else
				rep_msg->room_config.bWndMode = 0;

			if( WXmlParser_GetFieldValue(pConfigElement,"AudioBrdCount",nValue ))
				rep_msg->room_config.dwAudioBrdCount = nValue;
			else
				rep_msg->room_config.dwAudioBrdCount = 16;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoBrdCount",nValue ))
				rep_msg->room_config.dwVideoBrdCount = nValue;
			else
				rep_msg->room_config.dwVideoBrdCount = 16;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoRcvCountChair",nValue ))
				rep_msg->room_config.dwVideoRcvCountChair = nValue;
			else
				rep_msg->room_config.dwVideoRcvCountChair = 16;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoRcvCountAttender",nValue ))
				rep_msg->room_config.dwVideoRcvCountAttender = nValue;
			else
				rep_msg->room_config.dwVideoRcvCountAttender = 16;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoWidth",nValue ))
				rep_msg->room_config.dwVideoWidth = nValue;
			else
				rep_msg->room_config.dwVideoWidth = 720;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoHeight",nValue ))
				rep_msg->room_config.dwVideoHeight = nValue;
			else
				rep_msg->room_config.dwVideoHeight = 576;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoBitrate",nValue ))
				rep_msg->room_config.dwVideoBitrate = nValue;
			else
				rep_msg->room_config.dwVideoBitrate = 1000;
			rep_msg->room_config.dwMediaBitrate = rep_msg->room_config.dwVideoBitrate;
			if( WXmlParser_GetFieldValue(pConfigElement,"VideoFrameRate",nValue ))
				rep_msg->room_config.dwVideoFrameRate = nValue;
			else
				rep_msg->room_config.dwVideoFrameRate = 30;
		}

		TiXmlElement *pAVElement = element.FirstChildElement("AVSetting");
		if( pAVElement )
		{
			//是否启用服务器端音视频参数设置
			rep_msg->room_info.bUserSrvAVSetting = 0;
			if( WXmlParser_GetFieldValue( pAVElement,"UseSetting",nValue ))
				rep_msg->room_info.bUserSrvAVSetting = nValue;

			if (rep_msg->room_info.bUserSrvAVSetting)
			{
				WXmlParser_GetFieldValue( pAVElement,"VideoCodec",rep_msg->video_param.nEncoderID );
				WXmlParser_GetFieldValue( pAVElement,"VideoSize",nValue );
				switch(nValue)
				{
				case 0:
					rep_msg->video_param.nWidth = 160;
					rep_msg->video_param.nHeigth = 120;
					break;
				case 1:
					rep_msg->video_param.nWidth = 176;
					rep_msg->video_param.nHeigth = 144;
					break;
				case 2:
					rep_msg->video_param.nWidth = 320;
					rep_msg->video_param.nHeigth = 240;
					break;
				case 3:
					rep_msg->video_param.nWidth = 352;
					rep_msg->video_param.nHeigth = 288;
					break;
				case 4:
					rep_msg->video_param.nWidth = 640;
					rep_msg->video_param.nHeigth = 480;
					break;
				case 5:
					rep_msg->video_param.nWidth = 704;
					rep_msg->video_param.nHeigth = 576;
					break;
				case 6:
					rep_msg->video_param.nWidth = 720;
					rep_msg->video_param.nHeigth = 576;
					break;
				case 7:
					rep_msg->video_param.nWidth = 1280;
					rep_msg->video_param.nHeigth = 720;
					break;
				case 8:
					rep_msg->video_param.nWidth = 1920;
					rep_msg->video_param.nHeigth = 1080;
					break;
				default:
					rep_msg->video_param.nWidth = 320;
					rep_msg->video_param.nHeigth = 240;
					break;
				}
				WXmlParser_GetFieldValue(pAVElement, "VideoEncoderMode", rep_msg->video_param.nEncoderMode);
				WXmlParser_GetFieldValue(pAVElement, "VideoQuality", rep_msg->video_param.nVBRQuality);
				WXmlParser_GetFieldValue(pAVElement, "VideoBitrate", rep_msg->video_param.nBitrate);
			}
		}
		TiXmlElement *pUserElement = element.FirstChildElement("UserInfo");
		if( pUserElement )
		{
			if( WXmlParser_GetFieldValue( pUserElement,"Right",nValue ))
				rep_msg->room_user_info.bUserRight = nValue;
			if( szValue = WXmlParser_GetFieldValue(pUserElement,"DisplayName")){
				if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE))
					rep_msg->room_user_info.strNickName = szTemp;
			}
			if (WXmlParser_GetFieldValue( pUserElement,"UserLevel",nValue) )
				rep_msg->room_user_info.bUserLevel = nValue;
			rep_msg->room_user_info.nSeatList = 0;
			if (WXmlParser_GetFieldValue( pUserElement,"SeatList", nValue) )
				rep_msg->room_user_info.nSeatList = nValue;
			if( szValue = WXmlParser_GetFieldValue(pUserElement,"UserNodeID")){
				if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
					rep_msg->room_user_info.strNodeID = szTemp;
			}
			if ( szValue = WXmlParser_GetFieldValue( pUserElement,"DeptID") ){
				if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
					rep_msg->room_user_info.strDeptID = szTemp;
			}
			if( szValue = WXmlParser_GetFieldValue(pUserElement,"UserIP")){
				rep_msg->room_user_info.strUserIP = szValue;
			}
			if (WXmlParser_GetFieldValue( pUserElement,"Sex",nValue) )
				rep_msg->room_user_info.bSex = nValue;
			if( szValue = WXmlParser_GetFieldValue(pUserElement,"Tel")){
				//if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
					//rep_msg->room_user_info.strTel = szTemp;
			}
			if( szValue = WXmlParser_GetFieldValue(pUserElement,"Mobile")){
				//if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
					//rep_msg->room_user_info.strMobile = szTemp;
			}
			if( szValue = WXmlParser_GetFieldValue(pUserElement,"EMail")){
				if( ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE ) )
					rep_msg->room_user_info.strEMail = szTemp;
			}
#ifdef WIN32
			if( WXmlParser_GetFieldValue( pUserElement,"CallRight",nValue ))//电话权限标识 2014-05-28 loki
				rep_msg->room_user_info.bCallRight = nValue;
			else
				rep_msg->room_user_info.bCallRight = 0;

			if (WXmlParser_GetFieldValue( pUserElement,"BuyServer",nValue) )//购买服务标识 2014-12-12 loki
				rep_msg->room_user_info.dwBuyServer = nValue >= 0 ? nValue : 0;
			else
				rep_msg->room_user_info.dwBuyServer = -1;
#else
			userInfo.dwBuyServer = 0;
			userInfo.bCallRight  = 0;
#endif
		}
		TiXmlElement *pSrvElement = element.FirstChildElement("AVServer");
		if( pSrvElement )
		{
			if( WXmlParser_GetFieldValue( pSrvElement,"AppID",nValue ))
				rep_msg->room_srv_info.wAVSrvAppID = nValue;
			if( WXmlParser_GetFieldValue( pSrvElement,"CheckCode",nValue))
				rep_msg->room_srv_info.dwAVCheckCode = nValue;
			if( szValue = WXmlParser_GetFieldValue( pSrvElement,"Addr" )){
				rep_msg->room_srv_info.strAVSrvAddr = szValue;
			}
			WXmlParser_GetFieldValue(pSrvElement, "Guid", rep_msg->room_srv_info.guidMedia);
		}
		pSrvElement = element.FirstChildElement("VNCServer");
		if( pSrvElement )
		{
			if( WXmlParser_GetFieldValue( pSrvElement,"AppID",nValue ))
				rep_msg->room_srv_info.wVNCSrvAppID = nValue;
			if( WXmlParser_GetFieldValue( pSrvElement,"CheckCode",nValue))
				rep_msg->room_srv_info.dwVNCCheckCode = nValue;
			if( szValue = WXmlParser_GetFieldValue( pSrvElement,"Addr" )){
				rep_msg->room_srv_info.strVNCSrvAddr = szValue;
			}
			WXmlParser_GetFieldValue(pSrvElement, "Guid", rep_msg->room_srv_info.guidVNC);
		}	
		pSrvElement = element.FirstChildElement("WBDoc");
		if( pSrvElement )
		{
			if( WXmlParser_GetFieldValue( pSrvElement,"AppID",nValue ))
				rep_msg->room_srv_info.wWBSrvAppID = nValue;
			if( WXmlParser_GetFieldValue( pSrvElement,"CheckCode",nValue))
				rep_msg->room_srv_info.dwWBCheckCode = nValue;
			if( szValue = WXmlParser_GetFieldValue( pSrvElement,"Addr" )){
				rep_msg->room_srv_info.strWBSrvAddr = szValue;
			}
			WXmlParser_GetFieldValue(pSrvElement, "Guid", rep_msg->room_srv_info.guidWBDoc);
		}
		pSrvElement = element.FirstChildElement("WebDoc");
		if( pSrvElement )
		{
			if( WXmlParser_GetFieldValue( pSrvElement,"AppID",nValue ))
				rep_msg->room_srv_info.wWebSrvAppID = nValue;
			if( WXmlParser_GetFieldValue( pSrvElement,"CheckCode",nValue))
				rep_msg->room_srv_info.dwWebCheckCode = nValue;
			if( szValue = WXmlParser_GetFieldValue( pSrvElement,"Addr" ))
				rep_msg->room_srv_info.strWebSrvAddr = szValue;
			WXmlParser_GetFieldValue(pSrvElement, "Guid", rep_msg->room_srv_info.guidWebDoc);
		}
		pSrvElement = element.FirstChildElement("FilesServer");
		if (pSrvElement)
		{
			if( WXmlParser_GetFieldValue( pSrvElement,"AppID",nValue ))
				rep_msg->room_srv_info.wFileSrvAppID = nValue;
			if( szValue = WXmlParser_GetFieldValue( pSrvElement,"Addr" ))
				rep_msg->room_srv_info.strFileSrvAddr = szValue;
		}
	}

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：解析用户状态改变消息
 * 参  数：[in] element 消息数据
 *         [in] rep_msg 响应消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseUserStateChangedMsg(TiXmlElement& element,
	UserStateChangedMsg* state_msg)
{
	int nUserID = -1;
	WXmlParser_GetFieldValue(&element, "UserID", nUserID);
	if (nUserID != -1)
	{
		state_msg->user_id = nUserID;
	}
	else
	{
		return false;
	}

	TiXmlElement *pElementAudio = element.FirstChildElement("Audio");
	int nAudioID = -1;
	int nAudioState = -1;
	if (pElementAudio)
	{
		state_msg->has_audio_state = true;

		WXmlParser_GetFieldValue( pElementAudio,"ID",state_msg->audio_id );
		WXmlParser_GetFieldValue( pElementAudio,"State",state_msg->audio_state );
	}
	else
	{
		state_msg->has_audio_state = false;
	}

	TiXmlElement *pElementVideo = element.FirstChildElement("Video");
	while (pElementVideo)
	{
		VideoChannel videoChannel;
		videoChannel.operation = -1;
		int nValue = -1;
		WXmlParser_GetFieldValue( pElementVideo,"ID",nValue );
		videoChannel.media_id = nValue;
		WXmlParser_GetFieldValue( pElementVideo,"State", nValue);
		videoChannel.media_state = nValue;

		VideoChannelMap::iterator i = state_msg->video_channels.find( videoChannel.media_id );
		if (i == state_msg->video_channels.end())
		{
			state_msg->video_channels.insert(
				VideoChannelMap::value_type(videoChannel.media_id, videoChannel));
		}
		else
		{
			(*i).second = videoChannel;
		}
		pElementVideo = pElementVideo->NextSiblingElement("Video");
	}

	int nDataState = -1;
	WXmlParser_GetFieldValue( &element,"DataState",nDataState );
	if (nDataState != -1)
	{
		state_msg->has_data_state = true;
		state_msg->data_state = nDataState;
	}
	else
	{
		state_msg->has_data_state = false;
	}

	int nVNCState = -1;
	WXmlParser_GetFieldValue( &element,"VNCState",nVNCState );
	if (nVNCState != -1)
	{
		state_msg->has_vnc_state = true;
		state_msg->vnc_state = nVNCState;
	}
	else
	{
		state_msg->has_vnc_state = false;
	}

	int nWBMarkState = -1;
	WXmlParser_GetFieldValue( &element,"WBMarkState",nWBMarkState );
	if (nWBMarkState != -1)
	{
		state_msg->has_wb_mark_state = true;;
		state_msg->wb_mark_state = nWBMarkState;
	}
	else
	{
		state_msg->has_wb_mark_state = false;
	}

#if 0 // 这一段暂时用不着
	TiXmlElement *pElementPrivateTalk = element.FirstChildElement("PrivateTalk");
	int nOptUserID = -1;
	int nDstUserID = -1;
	int nPrivateTalkState = -1;
	if (pElementPrivateTalk)
	{
		WXmlParser_GetFieldValue( pElementPrivateTalk,"OptUserID",nOptUserID );
		WXmlParser_GetFieldValue( pElementPrivateTalk,"DstUserID",nDstUserID );
		WXmlParser_GetFieldValue( pElementPrivateTalk,"State",nPrivateTalkState );
		if( nUserID != -1 && nOptUserID != -1 && nDstUserID != -1 && nPrivateTalkState != -1){
			m_pReadCallback->OnUserPrivateTalkState( nOptUserID,nUserID,nDstUserID,nPrivateTalkState );
		}
	}
	int nAudioShareID = 0;
	int nVideoShareID = 0;
	if( WXmlParser_GetFieldValue( &element,"AudioShareID",nAudioShareID ) &&
		WXmlParser_GetFieldValue( &element,"VideoShareID",nVideoShareID ) ){
		m_pReadCallback->OnUserMediaShare( nUserID,nAudioShareID,nVideoShareID );
	}
	int nAudioOutMute = 0;
	if( WXmlParser_GetFieldValue( &element,"AudioOutMute",nAudioOutMute )){
		m_pReadCallback->OnUserAudioOutMute( nUserID,nAudioOutMute );
	}
	int nRight = 0;
	if( WXmlParser_GetFieldValue( &element,"Right",nRight )){
		m_pReadCallback->OnUserRight( nUserID,nRight );
	}
	int nEnableChat = 0;
	if( WXmlParser_GetFieldValue( &element,"EnableChat",nEnableChat )){
		m_pReadCallback->OnUserEnableChat( nUserID,nEnableChat );
	}
	int nGroupState = 0;
	if( WXmlParser_GetFieldValue( &element,"GroupState",nGroupState )){
		m_pReadCallback->OnUserGroupStateMsg( nUserID,nGroupState );
	}
	TiXmlElement *pInfoElement = element.FirstChildElement("Info");
	if( pInfoElement ){
		RoomUserInfo info;
		info.dwUserID = nUserID;
		int nSex = 0;
		WXmlParser_GetFieldValue( pInfoElement,"Sex",nSex );
		info.bSex = nSex;
		TCHAR szValue[MAX_PATH];
		if( WXmlParser_GetFieldValue( pInfoElement,"DisplayName",szValue,MAX_PATH ))
			info.strNickName = szValue;
		if( WXmlParser_GetFieldValue( pInfoElement,"Tel",szValue,MAX_PATH ))
			info.strTel = szValue;
		if( WXmlParser_GetFieldValue( pInfoElement,"Mobile",szValue,MAX_PATH ))
			info.strMobile = szValue;
		if( WXmlParser_GetFieldValue( pInfoElement,"EMail",szValue,MAX_PATH ))
			info.strEMail = szValue;

		m_pReadCallback->OnUserUpdateInfo( info );
	}
#endif

	return true;
}

/*------------------------------------------------------------------------------
 * 描  述：解析用户音视频信息通知消息
 * 参  数：[in] element 消息数据
 *         [in] notify_msg 通知消息结构
 * 返回值：成功/失败
------------------------------------------------------------------------------*/
bool ConfMsgProcessor::ParseUserAvInfoNotifyMsg(TiXmlElement& element, 
	UserAvInfoNotifyMsg* notify_msg)
{
	int nUserID = -1;
	int nValue = -1;
	TCHAR szTemp[STRING_BUFFER_SIZE];
	const CHAR* szValue = NULL;
	WXmlParser_GetFieldValue( &element,"UserID",nUserID );
	if (nUserID < 0)
	{
		return false;
	}
	else
	{
		notify_msg->user_id = nUserID;
	}

	TiXmlElement *pElementAudio = element.FirstChildElement("Audio");
	if (pElementAudio)
	{
		WXmlParser_GetFieldValue( pElementAudio,"Operation",notify_msg->audio_channel.operation );
		WXmlParser_GetFieldValue( pElementAudio,"ID",nValue );
		notify_msg->audio_channel.media_id = nValue;
		szValue = WXmlParser_GetFieldValue( pElementAudio,"Name" );
		if( NULL == szValue )
			return FALSE;
		if( !ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE))
			return FALSE;					
		notify_msg->audio_channel.dev_name = szTemp;
		notify_msg->audio_channel.has_audio = true;
		notify_msg->audio_channel.media_state = STATE_NONE;
		notify_msg->audio_channel.source_id = 0;
		notify_msg->has_audio_info = true;
	}

	TiXmlElement *pElementVideo = element.FirstChildElement("Video");
	while (pElementVideo)
	{
		VideoChannel videoChannel;				
		WXmlParser_GetFieldValue( pElementVideo,"Operation",nValue );
		videoChannel.operation = nValue;
		WXmlParser_GetFieldValue( pElementVideo,"ID",nValue );
		videoChannel.media_id = nValue;
		szValue = WXmlParser_GetFieldValue( pElementVideo,"Name");
		if( NULL == szValue )
			return FALSE;
		if( !ConvertUtf8ToString( szValue,szTemp,STRING_BUFFER_SIZE))
			return FALSE;
		videoChannel.dev_name = szTemp;
		videoChannel.has_video = TRUE;
		videoChannel.media_state = STATE_NONE;
		VideoChannelMap::iterator i = notify_msg->video_channels.find( videoChannel.media_id );
		if (i == notify_msg->video_channels.end())
		{
			notify_msg->video_channels.insert(
				VideoChannelMap::value_type(videoChannel.media_id, videoChannel));
		}
		else
		{
			(*i).second = videoChannel;
		}
		pElementVideo = pElementVideo->NextSiblingElement("Video");
	}

	return true;
}

bool ConfMsgProcessor::ParseUserEnterNotifyMsg(TiXmlElement &element, 
	UserEnterNotifyMsg* notify_msg)
{
	int			nValue = -1;
	const CHAR* szValue = NULL;
	TCHAR		szTemp[STRING_BUFFER_SIZE];
	ZeroMemory(szTemp, sizeof(szTemp));

	TiXmlElement *pElement = element.FirstChildElement("User");
	while (pElement)
	{
		RoomUserInfo info;
		info.bUserState = 0; // USER_ONLINE
		if (!WXmlParser_GetFieldValue(pElement, "UserID", nValue))
			break;
		info.dwUserID = nValue;
		if (!WXmlParser_GetFieldValue(pElement, "Right", nValue))
			break;
		info.bUserRight = nValue;

		if (!WXmlParser_GetFieldValue(pElement, "UserLevel", nValue))
			break;
		info.bUserLevel = nValue;

		info.nSeatList = 0;
		if (WXmlParser_GetFieldValue(pElement, "SeatList", nValue))
			info.nSeatList = nValue;

		szValue = WXmlParser_GetFieldValue(pElement, "Name");
		if (NULL == szValue)
			break;
#ifdef _WIN32
		if (!ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
			break;
		info.strUserName = szTemp;
#else
		info.strUserName = szValue;
#endif
		szValue = WXmlParser_GetFieldValue(pElement, "DisplayName");
		if (NULL == szValue)
			break;
#ifdef _WIN32
		if (!ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
			break;
		info.strNickName = szTemp;
#else
		info.strNickName = szValue;
#endif

		if (!WXmlParser_GetFieldValue(pElement, "DataState", nValue))
			break;
		info.bDataState = nValue;
		if (!WXmlParser_GetFieldValue(pElement, "VNCState", nValue))
			break;
		info.bVNCState = nValue;
		if (WXmlParser_GetFieldValue(pElement, "GroupState", nValue))
			info.bGroupState = nValue;
		else
			info.bGroupState = 0;
		if (WXmlParser_GetFieldValue(pElement, "WBMarkState", nValue))
			info.bWBMarkState = nValue;
		else
			info.bWBMarkState = 0;

#ifdef _WIN32
		if (szValue = WXmlParser_GetFieldValue(pElement, "UserNodeID"))
		{
			if (ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				info.strNodeID = szTemp;
		}
		if (szValue = WXmlParser_GetFieldValue(pElement, "DeptID"))
		{
			if (ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				info.strDeptID = szTemp;
		}
		if (szValue = WXmlParser_GetFieldValue(pElement, "UserIP"))
		{
			info.strUserIP = szValue;
		}
		info.bUserType = 0;
		if (WXmlParser_GetFieldValue(pElement, "UserType", nValue)){
			info.bUserType = nValue;
		}
		if (WXmlParser_GetFieldValue(pElement, "Sex", nValue))
			info.bSex = nValue;
		if (szValue = WXmlParser_GetFieldValue(pElement, "Tel")) {
			if (ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				//info.strTel = szTemp;
				info.strTel.clear();
		}
		if (szValue = WXmlParser_GetFieldValue(pElement, "Mobile")) {
			if (ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				//info.strMobile = szTemp;
				info.strMobile.clear();
		}
		if (szValue = WXmlParser_GetFieldValue(pElement, "EMail")) {
			if (ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				info.strEMail = szTemp;
		}
#else
		if (szValue = WXmlParser_GetFieldValue(pElement, "UserNodeID"))
			info.strNodeID = szValue;

		if (szValue = WXmlParser_GetFieldValue(pElement, "DeptID"))
			info.strDeptID = szValue;

		if (szValue = WXmlParser_GetFieldValue(pElement, "UserIP"))
			info.strUserIP = szValue;

		info.bUserType = 0;
		if (WXmlParser_GetFieldValue(pElement, "UserType", nValue))
			info.bUserType = nValue;

		if (WXmlParser_GetFieldValue(pElement, "Sex", nValue))
			info.bSex = nValue;

		if (szValue = WXmlParser_GetFieldValue(pElement, "Tel"))
			info.strTel = szValue;

		if (szValue = WXmlParser_GetFieldValue(pElement, "Mobile"))
			info.strMobile = szValue;

		if (szValue = WXmlParser_GetFieldValue(pElement, "EMail"))
			info.strEMail = szValue;

#endif
		info.audioChannel.has_audio = FALSE;
		info.audioChannel.media_state = STATE_NONE;
		info.audioChannel.media_id = 0;
		info.audioChannel.cap_dev_index = 0;
		info.audioChannel.source_id = 0;
		TiXmlElement* pAudioElement = pElement->FirstChildElement("Audio");
		while (pAudioElement)
		{
			if (!WXmlParser_GetFieldValue(pAudioElement, "ID", nValue))
				break;
			info.audioChannel.media_id = nValue;
			szValue = WXmlParser_GetFieldValue(pAudioElement, "Name");
			if (NULL == szValue)
				break;
#ifdef _WIN32
			if (!ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				break;
			info.audioChannel.dev_name = szTemp;
#else
			info.audioChannel.strName = szValue;
#endif 
			if (!WXmlParser_GetFieldValue(pAudioElement, "State", nValue))
				break;
			info.audioChannel.media_state = nValue;
			info.audioChannel.has_audio = TRUE;

			pAudioElement = pAudioElement->NextSiblingElement("Audio");
		};

		TiXmlElement* pVideoElement = pElement->FirstChildElement("Video");
		while (pVideoElement)
		{
			VideoChannel videoChannel;
			if (!WXmlParser_GetFieldValue(pVideoElement, "ID", nValue))
				break;
			videoChannel.media_id = nValue;
			szValue = WXmlParser_GetFieldValue(pVideoElement, "Name");
			if (NULL == szValue)
				break;
#ifdef _WIN32
			if (!ConvertUtf8ToString(szValue, szTemp, STRING_BUFFER_SIZE))
				break;
			videoChannel.dev_name = szTemp;

#else
			videoChannel.strName = szValue;
#endif
			if (!WXmlParser_GetFieldValue(pVideoElement, "State", nValue))
				break;
			videoChannel.media_state = nValue;
			videoChannel.recv_video = FALSE;
			info.vclMgr.insert(std::make_pair(videoChannel.cap_dev_index, videoChannel));
			pVideoElement = pVideoElement->NextSiblingElement("Video");
		};

		TiXmlElement* pPrivateTalkElement = pElement->FirstChildElement("PrivateTalk");
		if (pPrivateTalkElement)
		{
			if (!WXmlParser_GetFieldValue(pPrivateTalkElement, "DstUserID", nValue))
				break;
			info.dwPrivateTalkDstUserID = nValue;

			if (!WXmlParser_GetFieldValue(pPrivateTalkElement, "State", nValue))
				break;
			info.bPrivateTalkState = nValue;
		}
		info.bAudioShareID = 0;
		info.bVideoShareID = 0;
		if (WXmlParser_GetFieldValue(pElement, "AudioShareID", nValue))
			info.bAudioShareID = nValue;
		if (WXmlParser_GetFieldValue(pElement, "VideoShareID", nValue))
			info.bVideoShareID = nValue;

		info.bAudioOutMute = 0;
		if (WXmlParser_GetFieldValue(pElement, "AudioOutMute", nValue))
			info.bAudioOutMute = nValue;

		if (WXmlParser_GetFieldValue(pElement, "TerminalType", nValue))
			info.terminal_type = (TerminalType)nValue;
		else
			info.terminal_type = TERMINAL_TYPE_DESKTOP;

		info.bEnableChat = 1;
		if (WXmlParser_GetFieldValue(pElement, "EnableChat", nValue))
			info.bEnableChat = nValue;

		info.bEnableWaterMark = false;

		notify_msg->users.push_back(info);
		pElement = pElement->NextSiblingElement("User");
	};

	return true;
}