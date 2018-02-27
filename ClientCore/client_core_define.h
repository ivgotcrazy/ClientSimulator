/*##############################################################################
 * �ļ���client_core_define.h
 * �������ڲ��������ClientCoreMgr������������������Ŀǰ�����ϸ���Ҫ�ع���
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
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
//-- ������Ϣ���Ͷ���

enum DownMsgType
{
	DOWN_MSG_BEGIN = 0xFF,	// !!!����������Ϣ��������ڴ���֮��

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

	DOWN_MSG_END	// !!!����������Ϣ��������ڴ���֮ǰ
};

////////////////////////////////////////////////////////////////////////////////
//-- ������Ϣ���ݶ���

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
	FS_INT32	media_id;		//ý��ID
	FS_INT32	media_state;	//��Ƶ�㲥״̬ 
	bool		has_video;		//�豸�Ƿ���Ч
	bool		recv_video;		//�Ƿ���ո�·��Ƶ
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
	int     nVerifyMode; //1���û�������֤��2��������������֤��3��������¼
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
	BOOL	bWaterMarkState;				// ˮӡ״̬;

	BYTE	bUserSrvAVSetting;	//�Ƿ����÷�����������Ƶ��������
	BYTE	bUserRight;			//ǰ�÷��ص�ǰ�������û�Ȩ��,�û�������Ȩ��1Ϊ�����ˡ�2Ϊ��ϯ��3Ϊ����

	time_t	tStartTime;			//���鿪ʼʱ��
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
	BOOL		bEnablePhoneInvite; //�绰���� loki 2015-01-20

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
	DWORD	dwPrivateTalkDstUserID;			//˽�ĶԷ��û�ID
	TerminalType terminal_type;
	BYTE    bUserState;						//�Ƿ�����
	BYTE	bUserType;						//�û�����,ע����ע��
	BYTE	bUserRight;						//�û�Ȩ��
	BYTE    bUserLevel;						//�û�����
	BYTE	bSex;
	BYTE    bCallRight;                     //�绰����Ȩ�� 0����Ȩ�ޣ�1������Ȩ��
	DWORD   dwBuyServer;                    //����ķ��� 0 ���κη��� loki 2014-12-12  0x000000000000000
	BYTE	bDataState;
	BYTE	bVNCState;
	BYTE	bPrivateTalkState;				//˽��״̬
	BYTE	bAudioShareID;
	BYTE	bVideoShareID;
	BYTE	bAudioOutMute;					//���ر��������
	BYTE	bGroupState;					//�������״̬
	BOOL	bEnableChat;
	BYTE	bWBMarkState;					//�װ��עȨ��״̬

	BOOL	bEnableWaterMark;				// �Ƿ�߱�ˮӡ����

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
	BOOL			bShowSysTime;		//����Ƶ���Ƿ���ʾϵͳʱ��
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
//-- ������Ϣ���Ͷ���

enum UpMsgType
{
	UP_MSG_BEGIN = 0xFFFF, // !!!����������Ϣ��������ڴ���֮��

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

	UP_MSG_END	// !!!����������Ϣ��������ڴ���֮ǰ
};

////////////////////////////////////////////////////////////////////////////////
//-- ������Ϣ���ݶ���

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
	FS_UINT32	login_time; // ��¼ʱ��
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

	// �����û��б�
	UserDataMap		m_room_user_map;

	// ���������
	RoomInfo		m_room_info;

	// �ͻ�������
	RoomConfig		m_room_config;

	// ��������ķ��񣬱�������Ƶ������Ļ�������ȡ�
	RoomSrvInfo		m_room_srv_info;

	VideoParam		m_video_param;

	// ������Ϣ
	DeptNodeList	m_dept;
	DeptNodeList	m_node;
};



}