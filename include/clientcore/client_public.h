/*##############################################################################
 * 文件：client_public.h
 * 描述：对外（相对于ClientCoreMgr）公开的数据声明（不够严格）
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/

#pragma once

#include <vector>
#include <windows.h>
#include "fs_types.h"
#include "wtimermanager.h"
#include "framework.h"
#include "isessionmanager.h"
#include <functional>
#include <memory>

using namespace WBASELIB;
using namespace FsMeeting;

class IVideoDevice;
class IAudioDevice;

#ifdef _UNICODE
typedef std::wstring			tstring;
#else
typedef std::string				tstring;
#endif

namespace clientcore
{

typedef std::shared_ptr<void> MsgData;

enum ClientStateType
{
	CLIENT_STATE_TYPE_INVALID,
	CLIENT_STATE_TYPE_INIT,
	CLIENT_STATE_TYPE_UPDATE,
	CLIENT_STATE_TYPE_LOGIN,
	CLIENT_STATE_TYPE_SELECT_ROOM,
	CLIENT_STATE_TYPE_STARTUP_ROOM,
	CLIENT_STATE_TYPE_MAIN_ROOM,
	CLIENT_STATE_TYPE_SWITCH_GROUP_ROOM,
	CLIENT_STATE_TYPE_GROUP_ROOM,
	CLIENT_STATE_TYPE_SWITCH_MAIN_ROOM,
	CLIENT_STATE_TYPE_QUIT
};

enum ErrCode
{
	ERR_CODE_SUCCESS,
	ERR_CODE_FAIL,
	ERR_CODE_INVALID_STATE,
	ERR_CODE_START_AUDIO_FAILED,
	ERR_CODE_START_VIDEO_FAILED
};

////////////////////////////////////////////////////////////////////////////////
//-- 客户端基础对象

struct ClientBaseComponents
{
	IComponentFactory*	factory;
	ISessionManager2*	session_mgr;
	IWNetwork*			network;
	WTimerManager		timer_mgr;
};

////////////////////////////////////////////////////////////////////////////////
//-- 客户端配置项


//终端类型
enum TerminalType
{
	TERMINAL_TYPE_DESKTOP	= 1,
	TERMINAL_TYPE_HARDWARE	= 2,
	TERMINAL_TYPE_MOBILE	= 3,
	TERMINAL_TYPE_TELEPHONE	= 4,
	TERMINAL_TYPE_RECORD	= 5
};

enum ClientType
{
	CLIENT_TYPE_VIDEOCONF = 1,
	CLIENT_TYPE_IM,
	CLIENT_TYPE_G3
};

enum ClientMode
{
	CLIENT_MODE_FULL = 1,		//全功能
	CLIENT_MODE_MIX,			//桌面合成模式
	CLIENT_MODE_MINI			//手机最小模式
};

enum UserType
{
	USER_TYPE_UNREGISTER = 0,
	USER_TYPE_REGISTER
};

enum VerifyMode
{
	VERIFY_MODE_INVALID = 0,
	VERIFY_MODE_USER_PASSWORD = 1,
	VERIFY_MODE_ROOM_PASSWORD,
	VERIFY_MODE_ANONYMOUS
};

enum UserRight
{
	USER_RIGHT_CHAIR,
	USER_RIGHT_ATTENDER,
	USER_RIGHT_LISTENER
};

enum RoomMode
{
	ROOM_MODE_FREE,
	ROOM_MODE_CONTROL
};

enum VideoSrcType
{
	VIDEO_SRC_SELF_CREATE,	// 自己创建视频源(物理设备)
	VIDEO_SRC_EXTERNAL		// 外部视频源
};

enum RoomLoginType
{
	ROOM_LOGIN_USER_PWD,
	ROOM_LOGIN_ROOMID
};

struct ClientConfig
{
	std::string		client_ver;
	std::string		product_id;

	std::string		front_addr;
	FS_UINT32		front_app_id;
	FS_UINT32		room_app_id;

	ClientType		client_type;
	TerminalType	terminal_type;
	ClientMode		client_mode;

	UserType		user_type;
	tstring			user_name;
	std::string		user_pwd;

	FS_UINT32		room_id;
	std::string		room_pwd;

	FS_UINT32		video_width;
	FS_UINT32		video_height;
	FS_UINT32		video_frame_rate;
	FS_UINT32		video_bit_rate;
	FS_UINT32		encode_mode;
	FS_UINT32		video_dev_index;
	IVideoDevice*	video_src;
	IAudioDevice*	audio_src;
	FS_UINT32		video_count;

	bool			if_recv_av;
};

////////////////////////////////////////////////////////////////////////////////
//-- 通知消息类型定义

enum NotifyType
{
	NOTIFY_STATE_START,
	NOTIFY_UPDATE_CHECK_RESULT,
	NOTIFY_LOGIN_RESULT,
	NOTIFY_GET_ROOM_LIST_REP,
	NOTIFY_LOGIN_FRONT_ROOM_RESULT,
	NOTIFY_LOGIN_ROOM_RESULT
};

////////////////////////////////////////////////////////////////////////////////
//-- 通知消息数据定义

//------------------------------------------------------------------------------
struct StateStartNotify
{
	ClientStateType state_type;
};

//------------------------------------------------------------------------------
#define		UPDATE_RESULT_OK				0
#define		UPDATE_RESULT_CONNECTFAILED		1
#define		UPDATE_RESULT_ADVICEUPDATE		2
#define		UPDATE_RESULT_MUSTUPDATE		3

struct UpdateCheckNotify
{
	FS_UINT32 check_result;
};

//------------------------------------------------------------------------------
struct LoginResultNotify
{
	FS_INT32 login_result;
};

//------------------------------------------------------------------------------

struct SimpleRoomInfo
{
	FS_UINT32	room_id;
	FS_UINT32	max_user_count;
	FS_UINT32	cur_user_count;
	std::string room_name;
};

struct GetRoomListNotify
{
	std::vector<SimpleRoomInfo> room_list;
};

//------------------------------------------------------------------------------

struct LoginFrontRoomNotify
{
	FS_INT32 login_result;
};

//------------------------------------------------------------------------------

struct LoginRoomNotify
{
	FS_INT32 login_result;
};

//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//-- 通知消息处理接口

class INotifySink
{
public:
	virtual void OnNotify(NotifyType notify_type, void* notify_data) = 0;
};

}