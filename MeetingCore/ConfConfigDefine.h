#ifndef __CONF_CONFIG_DEFINE_H
#define __CONF_CONFIG_DEFINE_H

#ifndef _FS_OS_WIN
#include "wwindef.h"
#include "wunicode.h"
#if defined(_FS_OS_ANDROID)
#include "VideoDefine.h"
#endif
#endif

#include "ConfCommonDefine.h"
#include "ConfBaseDefine.h"
#include "wnetworkdef.h"

struct RoomConfig{
	
	BYTE		bEnableWB;
	BYTE		bEnableWEB;
	BYTE		bEnableApp;
	BYTE		bEnableMedia;
	BYTE		bEnableChat;
	BYTE		bEnableFile;
	BYTE		bEnableVote;
	BYTE		bEnablePhoneInvite; //电话邀请 loki 2015-01-20
	
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

struct ClientCapability{
	
	int		nDownloadBitrate;		//下行码流
	int		nClientMode;
};

typedef struct{	

	tstring			strClientVersion;
	tstring			strGroupName;
	tstring			strProductName;
	tstring			strProductID;
	WORD			wFrontSrvAppID;
	WORD			wRoomAppID;

	PRODUCTSERIES   Series;
	CLIENTTYPE		ClientType;
	TERMINALTYPE	TerminalType;
	ClientCapability ClientCapa;


    BOOL            bCameraVerticalMode;    //摄像头垂直采集
	BOOL			bUseVirtualChannel;		//是否使用视频设备通道模拟视频设备,固定为单压模式
	BOOL			bSupportScreenDevice;
	BOOL			bShowUserListTree;		//是否显示用户树状列表
	BOOL			bOverlayNameOnLocal;	//视频是否在发送端叠加用户名
	BOOL			bOverlayNameOnRemote;	//视频是否在接收端叠加用户名
	int				nInitWndMode;			//初始化窗口模式
	int				nInitWndVideoRelayID;	//初始化视频布局
	int				nInitWndDataActive;		//初始化数据激活窗口
	int				nMaxVideoSplitCount;	//最大视频分屏数
	BOOL			bDataFullMode;			//全屏时数据窗口是否用全屏模式

	//BOOL            bEnableRegister;        //是否可以注册 用edition版本信息判断
	//tstring         strDataDirName;         //本地目录名称 放在mapAppCustomParam中，不用单独使用配置 使用Key  "UserDataDirName"查找
	CLIENTEDITION   edition;                //客户端版本

	tstring			strAdConfigLink;	     	//广告消息配置链接地址
	std::list<std::string>		lsDefServer;	//运营版默认服务器列表
	std::map<std::string,std::string>	mapAppCustomParam;	//应用层自定义参数

	RoomConfig		config;

}ClientConfig;

typedef struct{

	BOOL					bSetServerAddr;
	std::list<tstring>		lsServerAddr;
	tstring					strLastServerAddr;
	
	std::list<tstring>		lsUserName;
	tstring					strLastUserName;

    std::list<tstring>      lsNickName;         
    tstring                 strLastNickName;  

    DWORD                   dwMeetingModel;//loki 2015-10-31 for ios 会议模式 ：0 正常模式 1 语音模式
    BOOL                    bExitNormalOnMeetingRoom;//for ios 会议室内正常退出
    BOOL                    bMainSpeakerWhenException;
    tstring                 strLastLoginRoomName;

	std::string				strUserPassword;
	std::string				strRoomPassword;

	BOOL					bLoginWithUnRegister;
	BOOL					bSaveUserPassword;

	int						nUserLoginType;		//1为用户帐号 2为用户邮箱 3为用户电话
	std::string				strLoginAddrLink;	//用于命令行方式登录
	DWORD					dwLoginRoomID;
	BOOL					bAutoLogin;

	BOOL					bRunFromCmdLine;	//是否是通过命令行方式启动客户端的
	std::string				strRunSeq;			//登录后自动运行的工作序列
}LoginParam;

typedef struct{
	
	BOOL					bSetServerPort;
	DWORD					dwServerPort;
	BOOL					bUserProxy;
	WNET_PROXY				Proxy;	
	std::string				strProxyAddr;
	BOOL					bEnableQos;
	BOOL					bPreferLoginIP;
	BOOL					bReuseUdpPort;
	DWORD					dwMTU;
#ifdef _WIN32_WCE	
	GUID					guidNetwork;
#endif
}NetworkParam;

typedef struct{
	
	int		nScrollStep;
	DWORD	dwColor;
	DWORD	dwRollTime;
	DWORD	dwDuration;
	std::vector<tstring> lsTitles;
	
}CaptionParam;

typedef struct{
    WORD			wLanguage;
    BOOL			bNotifyP2PSoftware;
	std::string		strUpgradeSilentVersion;	//不再提示升级的版本,如果提示非强制性升级至该版本，客户端直接跳过
	BOOL			bAutoRun;
	BOOL			bShowDept;				//是否显示组织架构
}SysParam;

typedef struct{

	int				wVideoPollTime;			//视频轮循时间
	int				nVideoDispMode;			//视频显示模式
	BOOL			bOpenScreenDevice;		//是否启动屏幕流设备
	BOOL			bVNCShareStopVideoBrd;	//屏幕广播时是否停止视频广播
	BOOL			bMediaShareStopVideoBrd;//媒体共享时是否停止视频广播
	int				nLastAudioCapDevCount;	//上一次启动时音频采集设备个数
	int				nLastAudioPlayDevCount;	//上一次启动时音频播放设备个数
	tstring			strPhotoPath;
	tstring			strTestSoundAudioPath;		//音频测试文件
}AVParam;

#define DEFAULT_KEYFRAMEINTERVAL_TIME		2	//second

#if defined(_FS_OS_ANDROID)
#ifndef _FS_ANDROID_AVCORE_3_9_

#define RotationAngle int

#endif
#endif

typedef struct{
	
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
#if defined(_FS_OS_ANDROID) || defined(_FS_OS_IOS)
	int				nVideoCsp;       //翻转

#if defined(_FS_OS_ANDROID)
	RotationAngle   rotationAngle;   //旋转参数 
#endif
#endif

}VideoParam;

typedef struct{
	
	int				nCapDevIndex;
	int				nPlayDevIndex;
	int				nCapInput;
	int				nCapVolume;
	int				nPlayVolume;
	BOOL			bCapVolumeAutoAdjust;
	int				nEncoderID;
	int				nAEC;
	int				nANS;
	int				nFEC;
	int				nAGC;
	int				nVAD;
	BOOL			bAutoAdjust;
	int				bAudioEngine;
	tstring			strLastCapDevName;
	tstring			strLastPlayDevName;
}AudioParam;

typedef struct{
	int				nDevIndex;
	int				nCameraType;
	int				nControlPort;
	int				nBaudRate;
	int				nAddrCode;
}CameraParam;

#define		RECORDTYPE_PRIVATEASF		0x01
#define		RECORDTYPE_STANDARDWMV		0x02
#define		RECORDTYPE_WMA				0x03

#define		RECORDQUALITY_LOW			0x01
#define		RECORDQUALITY_MEDIAM		0x02
#define		RECORDQUALITY_HIGH			0x03

#define		RECORDRECT_FULL				0x01
#define		RECORDRECT_SELF				0x02
#define		RECORDRECT_SPEC				0x03

typedef struct{
	
	int				nRecordType;
	int				nRecordQuality;
	int				nRecordProfile;
	int				nRecordRect;
	int				nRecordLeft;
	int				nRecordTop;
	int				nRecordWidth;
	int				nRecordHeight;
	BOOL			bClipUponWnd;
	BOOL			bRecordAudio;
	BOOL			bRecordVideo;
	BOOL			bRecordChat;
	BOOL			bRecordWB;
	BOOL			bRecordWE;
	BOOL			bRecordVNC;
	DWORD			dwMaxFileSize;
	tstring			strRecordPath;
}RecordParam;

typedef struct{

	tstring			strDownloadFilePath;
	tstring			strFileFixedFolder;
}FileParam;

typedef struct{

	BOOL		bEnableLocalRecord;
	BOOL		bRecordAudio;
	BOOL		bRecordVideo;
	tstring		strRecordPath;
	DWORD		dwSaveDays;
	DWORD		dwMaxFileSize;
}LocalRecordParam;

typedef struct{

	int		nAudioEncoderID;
	int		nAudioFEC;
	int		nVideoEncoderID;
	int		nVideoFrameRate;
	int		nVideoBitrate;
	BOOL	bShareAudio;
	BOOL	bShareVideo;
	BOOL	bUserRawVideSize;
	BOOL	bAutoAdjust;
	BOOL	bShowPlayList;
	std::vector<tstring>	lsPlayList;
}MediaShareParam;

typedef struct{

	BOOL	bMsgFlashWindow;
	BOOL	bMsgAudioNotify;
	BOOL	bMsgPopupWindow;
	BOOL	bMsgHotShow;
	tstring strMsgNotifyAudioPath;

	BOOL	bKnockWndNotify;
	BOOL	bKnockAudioNotify;
	tstring strKnockNotifyAudioPath;

	BOOL	bShowUserTips;
	BOOL	bSaveChatMsg;
	tstring strChatmsgSavePath;
}MsgNotifyParam;


#define		OSDPOS_LT			1
#define		OSDPOS_RT			2
#define		OSDPOS_LB			3
#define		OSDPOS_RB			4

typedef struct{

	int		nPos;
	int		nSize;
	DWORD	dwColor;
}OSDSetting;

typedef struct{

	OSDSetting	DateTime;
	OSDSetting	UserName;
}VideoOSDParam;

#if !(defined(_FS_OS_IOS) || defined(_FS_OS_MAC))
static void		GetOsdPos( int nPos, POINT& pt )
{
	switch ( nPos )
	{
	case 1:
		pt.x = 0;
		pt.y = 0;
		break;
	case 2:
		pt.x = -1;
		pt.y = 0;
		break;
	case 3:
		pt.x = 0;
		pt.y = -1;
		break;
	case 4:
		pt.x = -1;
		pt.y = -1;
		break;
	default:
		pt.x = 0;
		pt.y = 0;
		break;		
	}
}
#endif

#define DOCSHARE_OUTTYPE_AUTO		0
#define DOCSHARE_OUTTYPE_EMF		1
#define DOCSHARE_OUTTYPE_BMP		2

typedef struct{

	int		nOutType;	
	BOOL	bSaveNotify;
	BOOL	bSaveInServer;
}DocShareParam;

typedef struct{

	BOOL	bEnableHotKey;
	DWORD	dwKeyMicMute;
	DWORD	dwKeySoundMute;
	DWORD	dwKeyFullWnd;
	DWORD	dwKeyCycleVideoLayout;
	DWORD	dwKeyIncVolume;
	DWORD	dwKeyDecVolume;
	DWORD	dwKeySpeak;
	DWORD	dwKeyDataControl;
	DWORD	dwKeyRecord;
	DWORD	dwKeyQuit;
}HotKeyDef;

//add by ron-2013_06_28
//OEM struct
typedef struct tagOEMInfo{
	tstring   sProductName;
	tstring   sCopyRight;
	tstring   sCopyRightURL;
	tstring   sMsgBoxTitle;
	tstring   sMainTitle;
	tstring   sHotLine;
	tstring   sServiceLink;
	tstring   sManualFile;
	tstring   sTutorialLink;
	tstring   sFAQLink;
	tstring   sErrSrvAddr;
	tstring   sErrUserName;
	tstring   sErrUserPwd;
	tstring   sErrSrvPath;
	tstring   sErrReportExe;
	tstring   sVersion;
	tstring   sAboutInfo;
	tagOEMInfo()
	{
		sProductName      = _T("");
		sCopyRight        = _T("");
		sCopyRightURL     = _T("");
		sMsgBoxTitle      = _T("");
		sMainTitle        = _T("");
		sHotLine          = _T("");
		sServiceLink      = _T("");
		sManualFile       = _T("");
		sTutorialLink     = _T("");
		sFAQLink          = _T("");
		sErrSrvAddr       = _T("");
		sErrUserName      = _T("");
		sErrUserPwd       = _T("");
		sErrSrvPath       = _T("");
		sErrReportExe     = _T("");
		sVersion          = _T("");
		sAboutInfo        = _T("");
	}
}tagOEMInfo;
//end

typedef struct UpdateParam
{
	DWORD ActiveTime;				// 设置不检查更新的有效时间
	DWORD LastTimeCheckUpdate;		// 最后一次检查更新的时间
	UpdateParam()
	{
		ActiveTime=0;
		LastTimeCheckUpdate = 0;
	}
} struct_UpdateParam;

struct tagUserLastConfigInfo
{
	DWORD dwUserID;       //用户ID
	DWORD dwRoomID;       //会议室ID
	tstring strLastTime;  //最后设置的时间

};

#endif	//	__CONF_CONFIG_DEFINE_H