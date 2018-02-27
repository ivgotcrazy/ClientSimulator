/*##############################################################################
 * 文件：client_core_define.h
 * 描述：内部（相对于ClientCoreMgr）公开的数据声明（目前不够严格，需要重构）
 * 作者：Teck
 * 时间：2016年12月04日
 * 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/

#pragma once

#include <vector>
#include <functional>
#include <memory>
#include "client_public.h"

using namespace FsMeeting;

#ifdef _UNICODE
#define ConvertUtf8ToString ConvertUtf8ToUnicode
#else
#define ConvertUtf8ToString ConvertUtf8ToAnsi
#endif

namespace clientcore
{

////////////////////////////////////////////////////////////////////////////////
//-- 下行消息类型定义

enum DownMsgType
{
	DOWN_MSG_BEGIN = 0xFF,	// !!!所有下行消息定义必须在此项之后

	DOWN_MSG_START_UPDATE_CHECK,
	DOWN_MSG_LOGIN,
	DOWN_MSG_GET_ROOM_LIST,
	DOWN_MSG_AV_CONFIG,
	DOWN_MSG_LOGIN_FRONT_ROOM,
	DOWN_MSG_LOGIN_ROOM,
	DOWN_MSG_INIT_COMPLETE,
	DOWN_MSG_CREATE_AV_COMPONENT,
	DOWN_MSG_LOGIN_AV_ROOM,
	DOWN_MSG_BROADCAST_USER_AV_INFO,
	DOWN_MSG_START_RECV_MEDIA,
	DOWN_MSG_PREVIEW_VIDEO_DEV,
	DOWN_MSG_SET_VIDEO_PARAM,
	DOWN_MSG_SET_AUDIO_PARAM,
	DOWN_MSG_LOGOUT_ROOM,

	DOWN_MSG_END	// !!!所有下行消息定义必须在此项之前
};

////////////////////////////////////////////////////////////////////////////////
//-- 下行消息数据定义

struct UpdateCheckReqMsg
{
	std::string server_addr;
	std::string product_id;
	std::string client_ver;
};

struct UpdateCheckRepMsg
{
	int							result;
	std::string					last_ver;
	std::string					min_ver;
	std::vector<std::string>	download_url;
};

//------------------------------------------------------------------------------

struct LoginReqMsg
{
	std::string		server_addr;
	tstring			user_name;
	std::string		user_pwd;
	std::string		product_name;

	ClientType		client_type;
	TerminalType	terminal_type;
	UserType		user_type;

	FS_UINT32		room_app_id;
	FS_UINT32		front_app_id;
};

typedef std::shared_ptr<LoginReqMsg> LoginReqMsgSP;

//------------------------------------------------------------------------------

struct LoginRepMsg
{
	FS_INT32	login_result;
	FS_INT32	local_user_id;
	std::string local_node_id;
};

typedef std::shared_ptr<LoginRepMsg> LoginRepMsgSP;

//------------------------------------------------------------------------------

struct FrontRoomInfo
{
	FS_UINT32	room_id;
	FS_INT16	room_app_id;
	FS_UINT32	max_user_count;
	FS_UINT32	cur_user_count;
	std::string room_name;
	BOOL		is_top_node;
	std::string room_node_id;
};

struct GetRoomListRepMsg
{
	FS_INT32 get_result;
	std::vector<FrontRoomInfo> room_list;
};

//------------------------------------------------------------------------------

struct AvConfigMsg
{
	IVideoDevice*	video_source;
	IAudioDevice*	audio_source;
	FS_UINT32		video_count;

	FS_UINT32		video_dev_index;
	FS_UINT32		width;
	FS_UINT32		height;
	FS_UINT32		frame_rate;
	FS_UINT32		bit_rate;
	FS_UINT32		encode_mode;
};

typedef std::shared_ptr<AvConfigMsg> AvConfigMsgSP;

//------------------------------------------------------------------------------

struct RoomServiceInfo
{
	std::string		srv_addr;
	std::wstring	srv_name;
};

typedef std::vector<RoomServiceInfo> RoomServiceList;

//------------------------------------------------------------------------------

struct LoginFrontRoomReqMsg
{
	FS_UINT32	room_id;
	FS_UINT32	room_app_id;
	std::string room_node_id;
};

typedef std::shared_ptr<LoginFrontRoomReqMsg> LoginFrontRoomReqMsgSP;

//------------------------------------------------------------------------------

struct LoginFrontRoomRepMsg
{
	FS_INT32		login_result;
	BOOL			is_top_node;
	std::string		room_node_id;
	FS_UINT32		room_id;
	UserRight		user_right;
	VerifyMode		verify_mode;
	FS_UINT32		room_user_id;
	std::string		room_srv_node_id;
	std::string		token;
	RoomServiceList srv_list;
};

typedef std::shared_ptr<LoginFrontRoomRepMsg> LoginFrontRoomRepMsgSP;

//------------------------------------------------------------------------------

struct AudioChannel
{
	FS_INT32	cap_dev_index;
	FS_INT32	operation;
	FS_INT32	media_id;
	FS_INT32	media_state;
	FS_UINT32	source_id;
	bool		has_audio;
	tstring		dev_name;
};

struct VideoChannel
{
	FS_INT32	cap_dev_index;
	FS_INT32	operation;
	FS_INT32	media_id;		//媒体ID
	FS_INT32	media_state;	//视频广播状态 
	bool		has_video;		//设备是否有效
	bool		recv_video;		//是否接收该路视频
	tstring		dev_name;
};

typedef std::map<DWORD, VideoChannel> VideoChannelMap;

//------------------------------------------------------------------------------

struct LoginRoomReqMsg
{
	ClientType		client_type;
	TerminalType	terminal_type;
	std::string		room_srv_node_id;
	FS_UINT32		room_id;
	FS_UINT32		user_id;
	std::wstring	user_name;
	UserType		user_type;
	std::string		token;
	VerifyMode		verify_mode;
	std::string		room_password;
	FS_INT32		lan_code;
	ClientMode		client_mode;
	FS_UINT32		download_bitrate;
};

struct RoomInfo{

	DWORD	dwRoomID;
	WORD	wRoomAppID;
	DWORD   dwRoomUserID;
	DWORD	dwMaxUserCount;
	DWORD	dwCurUserCount;
	tstring strRoomName;
	int     nVerifyMode; //1、用户密码验证；2、会议室密码验证；3、匿名登录
	BOOL	bIsTopNode;

	RoomServiceList lsService;
	std::string strRoomNodeID;
	std::string strRoomSrvNodeID;
	std::string strToken;

	BYTE	bRoomMode;
	BYTE	bRoomLock;
	BOOL	bEnableRecord;
	BOOL	bEnableChat;
	BOOL	bEnableP2PChat;
	BOOL	bEnablePubChat;
	BOOL	bEnableSendFile;
	BOOL	bEnableSaveWB;
	BOOL	bReservePresenterVideo;
	BOOL	bWaterMarkState;				// 水印状态;

	BYTE	bUserSrvAVSetting;	//是否启用服务器端音视频参数设置
	BYTE	bUserRight;			//前置返回当前会议室用户权限,用户会议室权限1为主持人、2为出席、3为旁听

	time_t	tStartTime;			//会议开始时间
};

struct RoomConfig
{
	BYTE		bEnableWB;
	BYTE		bEnableWEB;
	BYTE		bEnableApp;
	BYTE		bEnableMedia;
	BYTE		bEnableChat;
	BYTE		bEnableFile;
	BOOL		bEnableVote;
	BOOL		bEnablePhoneInvite; //电话邀请 loki 2015-01-20

	BYTE		bEnableAudio;
	BYTE		bEnableVideo;
	BYTE		bEnableMultiVideo;
	BYTE		bEnableDualDisp;
	BYTE		bEnableAVMix;
	BYTE		bWndMode;
	DWORD		dwAudioBrdCount;
	DWORD		dwVideoBrdCount;
	DWORD		dwVideoRcvCountChair;
	DWORD		dwVideoRcvCountAttender;
	DWORD		dwVideoWidth;
	DWORD		dwVideoHeight;
	DWORD		dwVideoBitrate;
	DWORD		dwVideoFrameRate;
	DWORD		dwMediaBitrate;
};

struct RoomUserInfo
{
	DWORD	dwUserID;
	int     nSeatList;
	DWORD	dwPrivateTalkDstUserID;			//私聊对方用户ID
	TerminalType terminal_type;
	BYTE    bUserState;						//是否在线
	BYTE	bUserType;						//用户类型,注册或非注册
	BYTE	bUserRight;						//用户权限
	BYTE    bUserLevel;						//用户级别
	BYTE	bSex;
	BYTE    bCallRight;                     //电话邀请权限 0，无权限，1，已授权。
	DWORD   dwBuyServer;                    //购买的服务 0 无任何服务 loki 2014-12-12  0x000000000000000
	BYTE	bDataState;
	BYTE	bVNCState;
	BYTE	bPrivateTalkState;				//私聊状态
	BYTE	bAudioShareID;
	BYTE	bVideoShareID;
	BYTE	bAudioOutMute;					//被关闭声音输出
	BYTE	bGroupState;					//分组会议状态
	BOOL	bEnableChat;
	BYTE	bWBMarkState;					//白板标注权限状态

	BOOL	bEnableWaterMark;				// 是否具备水印功能

	std::string  strUserIP;
	std::wstring strDeptID;
	std::wstring strNodeID;
	std::wstring strUserName;
	std::wstring strNickName;
	std::string  strTel;
	std::string  strMobile;
	std::wstring strEMail;

	AudioChannel audioChannel;
	VideoChannelMap vclMgr;
};

struct RoomSrvInfo
{
	std::string strConfSrvProtocolVersion;

	WORD		wAVSrvAppID;
	DWORD		dwAVCheckCode;
	std::string strAVSrvAddr;
	GUID		guidMedia;

	WORD		wVNCSrvAppID;
	DWORD		dwVNCCheckCode;
	std::string strVNCSrvAddr;
	GUID		guidVNC;

	WORD		wWBSrvAppID;
	DWORD		dwWBCheckCode;
	GUID		guidWBDoc;
	std::string strWBSrvAddr;

	WORD		wWebSrvAppID;
	DWORD		dwWebCheckCode;
	GUID		guidWebDoc;
	std::string strWebSrvAddr;
	WORD        wFileSrvAppID;
	std::string strFileSrvAddr;
};

struct VideoParam
{
	int				nEncoderID;
	int				nEncoderMode;
	int				nFrameRate;
	int				nVBRQuality;
	int				nBitrate;
	int				nKeyFrameInterval;
	int				nCapDevIndex;
	int				nWidth;
	int				nHeigth;
	int				nVideoInput;
	int				nVideoStandand;
	BOOL			bAutoAdjust;
	BOOL			bDenoise;
	BOOL			bShowSysTime;		//在视频上是否显示系统时间
	BOOL			bShowUserName;
	BOOL			bVSlip;
#ifdef ANDROID
	int				nVideoCsp;
#endif
};

struct DeptNodeInfo
{
	int		nNodeType;						// 1 node 2 dept
	int		nLevel;							// TOP Level = 1
	tstring	strNodeID;
	tstring	strNodeName;
	tstring	strParentID;
};

typedef std::vector<DeptNodeInfo>	DeptNodeList;

struct LoginRoomRepMsg
{
	FS_INT32		login_result;
	RoomInfo		room_info;
	RoomConfig		room_config;
	RoomUserInfo	room_user_info;
	RoomSrvInfo		room_srv_info;
	VideoParam		video_param;
	DeptNodeList	dept;
	DeptNodeList	node;
};

typedef std::shared_ptr<LoginRoomRepMsg> LoginRoomRepMsgSP;

//------------------------------------------------------------------------------

struct LoginAvRoomReqMsg
{
	GUID		group_guid;
	FS_UINT32	user_id;
	FS_UINT32	check_code;
	FS_UINT32	app_id;
	std::string	server_addr;
};

typedef std::shared_ptr<LoginAvRoomReqMsg> LoginAvRoomReqMsgSP;

//------------------------------------------------------------------------------

struct UserAvInfoMsg
{
	FS_UINT32		user_id;
	AudioChannel	audio_channel;
	VideoChannelMap video_channels;
};

typedef std::shared_ptr<UserAvInfoMsg> UserAvInfoMsgSP;

//------------------------------------------------------------------------------

struct MediaInfo
{
	FS_UINT32	media_type;
	FS_UINT32	media_id;
	FS_UINT32	media_state;
};

struct StartRecvMediaMsg
{
	FS_UINT32	user_id;
	std::vector<MediaInfo> media_infos;
};

typedef std::shared_ptr<StartRecvMediaMsg> StartRecvMediaMsgSP;

//------------------------------------------------------------------------------

struct VideoDevCapParam
{
	FS_UINT32	dev_index;
	FS_UINT32	width;
	FS_UINT32	height;
	FS_UINT32	frame_rate;
	FS_UINT32	bit_rate;
	FS_UINT32	encode_mode;
};

struct PreviewVideoDevMsg
{
	VideoDevCapParam	cap_param;
	HWND				render_wnd;
};

typedef std::shared_ptr<PreviewVideoDevMsg> PreviewVideoDevMsgSP;

//------------------------------------------------------------------------------

struct SetVideoParamMsg
{
	VideoDevCapParam cap_param;
};

typedef std::shared_ptr<SetVideoParamMsg> SetVideoParamMsgSP;

struct AudioCapDevParam
{
	FS_UINT32 dev_index;
};

struct SetAudioParamMsg
{
	AudioCapDevParam cap_param;
};

typedef std::shared_ptr<SetAudioParamMsg> SetAudioParamMsgSP;

//------------------------------------------------------------------------------

struct LogoutRoomMsg
{
	FS_UINT32 user_id;
	FS_UINT32 room_id;
	std::string room_srv_node_id;
};

typedef std::shared_ptr<LogoutRoomMsg> LogoutRoomMsgSP;

////////////////////////////////////////////////////////////////////////////////
//-- 上行消息类型定义

enum UpMsgType
{
	UP_MSG_BEGIN = 0xFFFF, // !!!所有上行消息定义必须在此项之后

	UP_MSG_STATE_START,
	UP_MSG_STATE_STOP,

	UP_MSG_ERROR,

	UP_MSG_CONNECT_FRONT_SUCCESS,
	UP_MSG_CONNECT_FRONT_FAILED,

	// update state
	UP_MSG_UPDATE_CHECK_RESULT,

	// login state
	UP_MSG_LOGIN_REP,

	// select room state
	UP_MSG_GET_ROOM_LIST_REP,

	// startup room state
	UP_MSG_LOGIN_FRONT_ROOM_REP,

	UP_MSG_CONNECT_CONF_SUCCESS,
	UP_MSG_CONNECT_CONF_FAILED,

	UP_MSG_LOGIN_ROOM_REP,

	UP_MSG_CREATE_AV_COMPONENT_REP,

	UP_MSG_LOGIN_AV_ROOM_REP,

	UP_MSG_REFRESH_AV_DEVICES,

	UP_MSG_USER_STATE_CHANGED,

	UP_MSG_USER_AV_INFO_NOTIFY,

	UP_MSG_USER_ENTER_NOTIFY,

	UP_MSG_USER_LOGIN_RESULT,

	UP_MSG_HAS_NO_VIDEO_DEV,

	UP_MSG_APP_RUN_ERROR,

	UP_MSG_END	// !!!所有上行消息定义必须在此项之前
};

////////////////////////////////////////////////////////////////////////////////
//-- 上行消息数据定义

////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------

struct StateStartMsg
{
	tstring			user_name;
	FS_UINT32		user_id;
	ClientStateType state_type;
};

typedef std::shared_ptr<StateStartMsg> StateStartMsgSP;

//------------------------------------------------------------------------------

struct StateStopMsg
{
	ClientStateType state_type;
};

typedef std::shared_ptr<StateStopMsg> StateStopMsgSP;

//------------------------------------------------------------------------------

struct VerCheckMsg
{
	FS_UINT32 check_result;
};

//------------------------------------------------------------------------------

struct CreateAvComponentRepMsg
{
	FS_INT32 create_result;
};

typedef std::shared_ptr<CreateAvComponentRepMsg> CreateAvComponentRepMsgSP;

//------------------------------------------------------------------------------

struct LoginAvRoomRepMsg
{
	FS_INT32 login_result;
};

typedef std::shared_ptr<LoginAvRoomRepMsg> LoginAvRoomRepMsgSP;

//------------------------------------------------------------------------------

struct AudioDevInfo
{
	FS_UINT32	dev_index;
	tstring		dev_name;
};

struct VideoDevInfo
{
	FS_UINT32	dev_index;
	tstring		dev_name;
};

typedef std::vector<VideoDevInfo> VideoDevInfoVec;

struct RefreshAvDevicesMsg
{
	AudioDevInfo audio_dev;
	VideoDevInfoVec video_devs;
};

typedef std::shared_ptr<RefreshAvDevicesMsg> RefreshAvDevicesMsgSP;

//------------------------------------------------------------------------------

struct UserStateChangedMsg
{
	FS_UINT32	user_id;

	bool		has_audio_state;
	FS_INT32	audio_id;
	FS_INT32	audio_state;

	VideoChannelMap video_channels;

	bool		has_data_state;
	FS_INT32	data_state;

	bool		has_vnc_state;
	FS_INT32	vnc_state;

	bool		has_wb_mark_state;
	FS_INT32	wb_mark_state;
};

typedef std::shared_ptr<UserStateChangedMsg> UserStateChangedMsgSP;

//------------------------------------------------------------------------------

struct UserAvInfoNotifyMsg
{
	FS_UINT32		user_id;

	bool			has_audio_info;
	AudioChannel	audio_channel;

	VideoChannelMap	video_channels;
};

typedef std::shared_ptr<UserAvInfoNotifyMsg> UserAvInfoNotifyMsgSP;

//------------------------------------------------------------------------------

struct UserEnterNotifyMsg
{
	std::vector<RoomUserInfo> users;
};

typedef std::shared_ptr<UserEnterNotifyMsg> UserEnterNotifyMsgSP;

//------------------------------------------------------------------------------

struct UserLoginResultMsg
{
	ErrCode		login_result;
	FS_UINT32	user_id;
	tstring		user_name;
	FS_UINT32	login_time; // 登录时长
};

typedef std::shared_ptr<UserLoginResultMsg> UserLoginResultMsgSP;

//------------------------------------------------------------------------------

struct AppRunErrMsg
{
	ErrCode	run_err;
};

typedef std::shared_ptr<AppRunErrMsg> AppRunErrMsgSP;

////////////////////////////////////////////////////////////////////////////////


typedef std::function<bool(const MsgData&)> DownMsgHandler;
typedef std::function<bool(const MsgData&)> UpMsgHandler;

class IMsgProcessor
{
public:
	virtual ~IMsgProcessor() {}
	virtual void OnDownMsg(DownMsgType msg_type, const MsgData& msg_data) = 0;
	virtual void OnUpMsg(UpMsgType msg_type, const MsgData& msg_data) = 0;
};

typedef std::shared_ptr<IMsgProcessor> IMsgProcessorSP;

class IThreadMsgProcessor
{
public:
	virtual ~IThreadMsgProcessor() {}
	virtual void OnThreadDownMsg(DownMsgType msg_type, const MsgData& msg_data) = 0;
	virtual void OnThreadUpMsg(UpMsgType msg_type, const MsgData& msg_data) = 0;
};

////////////////////////////////////////////////////////////////////////////////

#define DOWN_MSG_PRE_MAP(msg_type,msg_proc) \
	AddDownMsgPreHandler(msg_type, std::bind(&msg_proc, this, std::placeholders::_1));

#define DOWN_MSG_POST_MAP(msg_type,msg_proc) \
	AddDownMsgPostHandler(msg_type, std::bind(&msg_proc, this, std::placeholders::_1));

#define UP_MSG_PRE_MAP(msg_type,msg_proc) \
	AddUpMsgPreHandler(msg_type, std::bind(&msg_proc, this, std::placeholders::_1));

#define UP_MSG_POST_MAP(msg_type,msg_proc) \
	AddUpMsgPostHandler(msg_type, std::bind(&msg_proc, this, std::placeholders::_1));

#define SET_DOWN_MSG_ROUTE(msg_type,msg_processor) \
	SetDownMsgRoute(msg_type, msg_processor);

#define RESET_DOWN_MSG_ROUTE(msg_type) RemoveDownMsgRoute(msg_type);

////////////////////////////////////////////////////////////////////////////////

class ThreadMsgConverter;
typedef std::shared_ptr<ThreadMsgConverter> ThreadMsgConverterSP;

////////////////////////////////////////////////////////////////////////////////

struct UserData
{
	RoomUserInfo	m_room_user_info;
	AudioChannel	m_audio_channel;
	VideoChannelMap	m_video_channels;
};

typedef std::map<FS_UINT32, UserData> UserDataMap;

struct RoomData
{
	FS_INT32		m_local_user_id;

	// 会议用户列表
	UserDataMap		m_room_user_map;

	// 服务端配置
	RoomInfo		m_room_info;

	// 客户端配置
	RoomConfig		m_room_config;

	// 会议包含的服务，比如音视频服务、屏幕共享服务等。
	RoomSrvInfo		m_room_srv_info;

	VideoParam		m_video_param;

	// 部门信息
	DeptNodeList	m_dept;
	DeptNodeList	m_node;
};



}