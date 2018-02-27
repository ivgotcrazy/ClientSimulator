#ifndef __CONFMAIN_INTERFACE_H
#define __CONFMAIN_INTERFACE_H

#include "list"
#include "vector"
#include "string"
#include "map"
#include "set"
#if defined(_FS_OS_ANDROID)
#include <unordered_map>
#elif defined(_FS_OS_WIN)
#include "hash_map"
#elif defined(_FS_OS_IOS) || defined(_FS_OS_MAC)
#include <ext/hash_map>
using namespace __gnu_cxx;
#endif

#include "wunicode.h"
#include "wbasetype.h"
#include "wbaseobject.h"
#include "wmsgqueue.h"
#include "wnetworkdef.h"
#include "ibasecomponent.h"
#include "frameworksdk.h"
#include "isessionmanager.h"
#include "IAudioDevice.h"
#include "IMultiAVMP.h"
#include "IVideoDevice.h"
#include "IVncMP.h"
#include "IFileManager.h"
#include "IWMultiWhiteBoard.h"
//#include "IWExplorer.h"
#ifdef _FS_OS_WIN
#include "ICameraControl.h"
#include "ConfCallDefine.h"
#include "RecordDataDefine.h"
#endif
#include "IMediaGraber.h"
#include "IAVPluginManager.h"
#include "IAVDevManager.h"

#include "ClientErrorDefine.h"
#include "ConfStructDefine.h"

#include "IViewInterface.h"

#include "VoteInfo.h"

#ifdef _WIN32_WCE
#include "Connection.h"
#endif

#include "VideoChannelManager.h"

interface CConfDataContainer;
class CallUserInfo;


typedef std::map<DWORD,CallUserInfo>       CallUserMap;
typedef std::map<tstring,CallUserMap>      CallPhoneMap;
typedef std::set<DWORD>                    CallIDSet;
typedef std::multimap<tstring,DWORD>       PhoneNumberWithCallIDMap;


struct RoomUserInfo
{
	DWORD	dwUserID;
	int     nSeatList;
	DWORD	dwPrivateTalkDstUserID;			//私聊对方用户ID
	TERMINALTYPE TerminalType;
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

	CVideoChannelManager vclMgr;
	AudioChannel audioChannel;

	std::string strUserIP;
	tstring	strDeptID;
	tstring strNodeID;
	tstring strUserName;
	tstring strNickName;
	tstring	strTel;    //
	tstring strMobile; //
	tstring strEMail;
};

struct DeptNodeInfo{

	int		nNodeType;						// 1 node 2 dept
	tstring	strNodeID;
	tstring	strNodeName;
	tstring	strParentID;
	int		nLevel;							// TOP Level = 1
};

typedef std::list<DeptNodeInfo>					DeptNodeList;
typedef std::vector<RoomUserInfo>				RoomUserList;
typedef std::map<DWORD,RoomUserInfo>			UserMap;

interface IConfMsgReadCallback
{
	virtual void    OnFrontUserLoginRep(int nResult,LocalDoMainInfo& info ){};
	virtual void    OnFrontRoomListRep(int nResult,RoomInfoList& lsRoomInfo){};
	virtual void    OnFrontRoomLoginRep(int nResult, RoomInfo& info){};
	virtual void    OnFrontRoomLoginOutRep(){};
	virtual void    OnFrontUserLoginOutRep(){};

	virtual void    OnSilentNotify(){};
	virtual void    OnMeetingCharNotify(tstring strContent,int nRoolTime,COLORREF colorFont){};
	virtual void	OnLoginRep( int nResult,DeptNodeList& lsNode,DeptNodeList& lsDept,RoomInfo& roomInfo,RoomConfig& config,RoomUserInfo& userInfo,VideoParam& param,RoomSrvInfo& srvInfo ){};
	virtual void	OnRoomLockedWaiting(){};
	virtual void	OnUserEnter( RoomUserList& lsRoomUser ){};
	virtual void	OnUserLeave( DWORD dwUserID ){};
	virtual void	OnUserKicked( DWORD dwKickUserID,DWORD dwUserID ){};
	virtual void	OnCloseRoom( int nReason ){};
	virtual void	OnUserAVInfoState( DWORD dwStateUserID,BOOL bHasAudioInfo,BOOL bHasVideoInfo,AudioChannel& audioChannel,VideoChannelMap& lsVideoChannle){};
	virtual void	OnUserAudioState( DWORD dwStateUserID,BYTE bMediaID,BYTE bAudioState ){};
	virtual void	OnUserDataState( DWORD dwStateUserID,BYTE bDataState ){};
	virtual void	OnUserVideoState( DWORD dwStateUserID,VideoChannelMap& lsVideoChannle ){};
	virtual void	OnUserVNCState( DWORD dwStateUserID,BYTE bVNCState ) {};
	virtual void	OnUserMediaShare( DWORD dwStateUserID,BYTE bAudioShareID,BYTE bVideoShareID ) {};
	virtual void	OnUserAudioOutMute( DWORD dwStateUserID,BYTE bAudioOutMute ){};
	virtual void	OnUserPrivateTalkState( DWORD dwOptUserID, DWORD dwStateUserID,DWORD dwDstUserID,BYTE bPrivateTalkState ) {};
	virtual void	OnUserUpdateInfo( const RoomUserInfo& info ){};
	virtual void	OnUserWBMarkState( DWORD dwStateUserID,BYTE bWBMarkState ) {};

	virtual void	OnSetRoomMode( BYTE bMode ){};
	virtual void	OnSetRoomLock( BYTE bLock ){};
	virtual void	OnSetRoomRecord( BYTE bRecord ){};
	virtual void	OnChatMsg( DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,const TCHAR* szText,LOGFONT* pLogFont ){};
	virtual void	OnWndState( RoomWndState& state,const VideoItemPosList& lsVideoPos,BOOL bValidFullMode ){};

	virtual void	OnVNCControlState( DWORD dwSrcUserID,DWORD dwDstUserID,BYTE bState ){};
	virtual void	OnControlCamera( DWORD dwSrcUserID,DWORD dwDstUserID,BYTE bCtrol,BYTE bMediaID ){};

	virtual void	OnAudioParamReq( DWORD dwSrcUserID,DWORD dwDstUserID ){};
	virtual void	OnAudioParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteAudioParam& param ){};
	virtual void	OnSetAudioParam( DWORD dwSrcUserID,DWORD dwDstUserID,AudioParam& param ){};
	virtual void	OnSetVVDev( DWORD dwSrcUserID,DWORD dwDstUserID,int nVVDev ){};

	virtual void	OnVideoParamReq( DWORD dwSrcUserID,DWORD dwDstUserID ){};
	virtual void	OnVideoParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteVideoParam& param ){};
	virtual void	OnSetVideoParam( DWORD dwSrcUserID,DWORD dwDstUserID,BOOL bEnableQos,VideoParam& param ){};
	
	virtual void	OnCameraParamReq( DWORD dwSrcUserID,DWORD dwDstUserID ){};
	virtual void	OnCameraParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,std::list<RemoteCameraParam>& lsParam ){};
	virtual void	OnSetCameraParam( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteCameraParam& param ){};

	virtual void	OnKnockUserNotify(DWORD dwUserID, const TCHAR *szDisplayName, BOOL bInLine){};
	virtual void    OnAllowKnockUserNotify(DWORD dwUserID, BOOL bAllow){} ;
	virtual void    OnSendFileNotify(DWORD dwSrcUserID,GUID& guid,tstring& strName,DWORD dwSize,
		                            DWORD dwCheckCode,WORD wSrvAppID,std::string& strSrvAddrLink){};
	virtual void    OnTransDataFileStatus(DWORD dwSrcUserID, DWORD dwDstUserID, GUID& guid, BYTE bValue){};

	virtual void	OnAVMixParamRep( const AudioMixParam& AudioParam,const VideoMixParam& VideoParam ){};
	virtual void	OnOSDParamNoitfy( const VideoOSDParam& param ){};
	virtual void	OnSysMsg( int nMsgType,const TCHAR* szMsg ){};

	virtual void	OnStartQuickRollCall( DWORD dwSrcUserID,const GUID& guidRollCall,DWORD dwDuration ){};
	virtual void	OnStopQuickRollCall( DWORD dwSrcUserID,const GUID& guidRollCall ){};
	virtual void	OnAckQuickRollCall( DWORD dwSrcUserID,DWORD dwDstUserID,const GUID& guidRollCall ){};

	virtual void	OnUserRight( DWORD dwUserID,BYTE bUserRight ){};
	virtual void	OnReqChairRightRet( BYTE bChairRight,int nResult ){};
	virtual void	OnRoomEnableChat( BOOL bEnableChat ){};
	virtual void	OnRoomEnableP2PChat( BOOL bEnableP2PChat ){};
	virtual void	OnRoomEnablePubChat( BOOL bEnablePubChat ){};
	virtual void	OnRoomEnableSendFile( BOOL bEnableSendFile ){};
	virtual void	OnRoomEnableSaveWB( BOOL bEnableSaveWB ){};
	virtual void	OnRoomReservePresenterVideo( BOOL bReservePresenterVideo ){};
	virtual void	OnUserEnableChat( DWORD dwUserID,BOOL bEnableChat ){};
	virtual void	OnVideoPollPreNotify( DWORD dwSrcUserID,DWORD dwVideoUserID,BYTE bID,DWORD dwRemainTime ){};

	virtual void	OnStartVote( DWORD dwSrcUserID,const CVoteInfo& info ){};
	virtual void	OnStopVote( DWORD dwSrcUserID,DWORD dwVoteID ){};
	virtual void	OnCloseVote( DWORD dwSrcUserID,DWORD dwVoteID ){};
	virtual void	OnBrdVoteResult( DWORD dwSrcUserID,const CVoteInfo& info ){};
	virtual void	OnVoteResult( DWORD dwSrcUserID,DWORD dwVoteID,BOOL bGiveup,const VoteResultList& result ){};

	virtual void	OnCreateGroupRoomMsg( const GroupRoomList& lsRoom ){};
	virtual void	OnUserGroupStateMsg( DWORD dwUserID,BYTE bState ){};
	virtual void	OnUserEnterGroupRoomRep( DWORD dwSrcUserID,const GroupRoomInfo& info,BYTE bRight ){};
	virtual void	OnUserEnterMainRoomRep( DWORD dwSrcUserID ){};
	virtual void	OnCloseGroupRoomMsg( DwordList& lsRooomID ){};

	virtual void	OnSendWaterMark(DWORD dwUserID) {};
	virtual void	OnRetWaterMark(DWORD dwUserID) {};
	virtual void	OnSetWaterMark(bool bWaterMark, int nTime) {};
	
#ifdef _FS_OS_WIN
	virtual void    OnCallInvitationReq(DWORD dwOprResult,CallUserInfoList &lsCallInfo){};
	virtual void    OnHangupReq(DWORD dwOprResult,CallUserInfo &callUserInfo){};
	virtual void    OnCallStateReq(DWORD dwoOperResult,const tstring &strCallNum){};
	virtual void    OnCallListReq(DWORD dwoOperResult,CallUserInfoList &lsCallInfo){};
#endif

};

interface IConfMsgWriter
{
	virtual void	WriteFrontUserLoginReq( ClientConfig& cfg,LoginParam& param ) = 0;
	virtual void	WriteFrontUserLogoutReq() = 0;
	virtual void	WriteFrontRoomListReq( MCUROOMLISTTYPE nMCURoomListType ) = 0;
	virtual void	WriteFrontRoomLoginReq( const CHAR* szRoomNodeID,DWORD dwRoomID,int nRoomAppID) = 0;
	virtual void	WriteFrontRoomLoginOutReq( const CHAR* szRoomNodeID,DWORD dwRoomID ) = 0;

	virtual void	WriteSendFileInfo( std::list<DWORD>& lsUserID,const GUID& guidFile,const TCHAR* szFileName,DWORD dwFileSize,DWORD dwCheckCode,WORD wAppID,const CHAR* lpszSrvLink ) = 0;
	virtual void    WriteTransDataReceiveInfo( DWORD dwSrcUserID,DWORD dwDstUserID,const GUID& guidFile,BYTE bStatus ) = 0;
	virtual void    WriteCmdMeetingChar(DWORD dwDuration,const TCHAR* szContent,int nRollTime,COLORREF colorFont) = 0;
	virtual void    WriteCmdSilent() = 0;
	virtual void    WriteAllowKnockNotify(DWORD dwUserID,BOOL bAllow) = 0;
	
	virtual void	WriteVNCControlState( DWORD dwSrcUserID,DWORD dwDstUserID,BYTE bState ) = 0;
	virtual void	WriteControlCamera( DWORD dwSrcUserID,DWORD dwDstUserID,BYTE bCtrol,BYTE bMediaID ) = 0;

	virtual void	WriteAudioParamReq( DWORD dwSrcUserID,DWORD dwDstUserID ) = 0;
	virtual void	WriteAudioParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteAudioParam& param ) = 0;
	virtual void	WriteSetAudioParam( DWORD dwSrcUserID,DWORD dwDstUserID,AudioParam& param ) = 0;

	virtual void	WriteVideoParamReq( DWORD dwSrcUserID,DWORD dwDstUserID ) = 0;
	virtual void	WriteVideoParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteVideoParam& param ) = 0;
	virtual void	WriteSetVideoParam( DWORD dwSrcUserID,DWORD dwDstUserID,VideoParam& param,BOOL bEnableQos ) = 0;
	virtual void	WriteSetVVDev( DWORD dwSrcUserID,DWORD dwDstUserID,int nVDevIndex ) = 0;

	virtual void	WriteCameraParamReq( DWORD dwSrcUserID,DWORD dwDstUserID ) = 0;
	virtual void	WriteCameraParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,std::list<RemoteCameraParam>& lsParam ) = 0;
	virtual void	WriteSetCameraParam( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteCameraParam& param ) = 0;
	
	virtual void	WriteWndState( const RoomWndState& state,const VideoItemPosList& lsVideoPos,BOOL bValidFullMode  ) = 0;
	virtual void	WriteWndStateEx( const RoomWndState& state,const RoomWndState& forOldClient,const VideoItemPosList& lsVideoPos,BOOL bValidFullMode  ) = 0;
	virtual void	WriteChatMsg( DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,const TCHAR* szText,const LOGFONT& logFont ) = 0;
	virtual void	WriteRoomLock( BYTE bLock ) = 0;
	virtual void	WriteRoomMode( BYTE bMode ) = 0;
	virtual void	WriteRoomRecord( BYTE bRecord ) = 0;
	virtual void	WriteUserDataState( DWORD dwUserID,BYTE bDataState) = 0;
	virtual void	WriteUserVNCState( DWORD dwUserID,BYTE bVNCState ) = 0;
	virtual void	WriteUserMediaShare( DWORD dwUserID,BYTE bAudioShareID,BYTE bVideoShareID ) = 0;
	virtual void	WriteUserAudioOutMute( DWORD dwStateUserID,BYTE bAudioOutMute ) = 0;
	virtual void	WriteUserPrivateTalkState( DWORD dwUserID,DWORD dwDstUserID, BYTE bState )=0;
	virtual void	WriteUserVideoState( DWORD dwUserID,BYTE bID,BYTE bState ) = 0;
	virtual void	WriteUserAudioState( DWORD dwUserID,BYTE bID,BYTE bState ) = 0;
	virtual void    WriteUserAvInfo( DWORD dwUserID,AudioChannel& audioChannel,const VideoChannelMap& lsVideoChannel ) = 0;
	virtual void	WriteUserUpdateInfo( const RoomUserInfo& info ) = 0;
	virtual void	WriteUserWBMarkState( DWORD dwUserID,BYTE bWBMarkState ) = 0;

	virtual void	WriteKickUser( DWORD dwUserID,DWORD dwKickedUserID ) = 0;
	virtual void	WriteReqOfflines() = 0;
	virtual void	WriteLoginReq(CLIENTTYPE nClientType,TERMINALTYPE nTerminalType,
									const CHAR* szRoomSrvNodeID,DWORD dwRoomID,
									DWORD dwUserID,const TCHAR *szUserName,
									BYTE bUserType,const CHAR *szToken,							  
									int nVerifyMode,std::string strRoomPassword,
									ClientCapability& capa,int nLanCode ) = 0;
	virtual void    WriteLogoutReq(DWORD dwUserID, DWORD dwRoomID, const CHAR* szRoomSrvNodeID ) = 0;
	virtual void    WriteInitComplete() = 0;
	virtual void	WriteAVMixParamReq() = 0;
	virtual void	WriteSetAVMixParam( BOOL bEnableDefault,const AudioMixParam& AudioParam,const VideoMixParam& VideoParam ) = 0;
	virtual void	WriteSetOSDParam( const VideoOSDParam& param ) = 0;
	virtual void	WriteCloseRoom( int nReason,const CHAR* szDesc ) = 0;

	virtual void	WriteStartQuickRollCall( DWORD dwSrcUserID,const std::list<DWORD>& lsDstUserID,const GUID& guidRollCall,DWORD dwDuration ) = 0;
	virtual void	WriteStopQuickRollCall( DWORD dwSrcUserID,const std::list<DWORD>& lsDstUserID,const GUID& guidRollCall ) = 0;
	virtual void	WriteAckQuickRollCall( DWORD dwSrcUserID,DWORD dwDstUserID,const GUID& guidRollCall ) = 0;

	virtual void	WriteReqChairRight( BYTE bChairRight,const TCHAR* szChairPwd ) = 0;
	virtual void	WriteRoomEnableChat( BYTE bEnableChat ) = 0;
	virtual void	WriteRoomEnableP2PChat( BYTE bEnableP2PChat ) = 0;
	virtual void	WriteRoomEnablePubChat( BYTE bEnablePubChat ) = 0;
	virtual void	WriteRoomEnableSendFile( BYTE bEnableSendFile ) = 0;
	virtual void	WriteRoomEnableSaveWB( BYTE bEnableSaveWB ) = 0;
	virtual void	WriteRoomReservePresenterVideo( BYTE bReservePresenterVideo ) = 0;
	virtual void	WriteUserEnableChat( DWORD dwUserID,BYTE bEnableChat ) = 0;
	virtual void	WriteVideoPollPreNotify( DWORD dwLocalUserID,DWORD dwVideoUserID,BYTE bID,DWORD dwRemainTime ) = 0;

	virtual void	WriteStartVote( DWORD dwSrcUserID,std::list<DWORD>& lsDstUser,const CVoteInfo& info ) = 0;
	virtual void	WriteStopVote( DWORD dwSrcUserID,DWORD dwVoteID ) = 0;
	virtual void	WriteCloseVote( DWORD dwSrcUserID,DWORD dwVoteID ) = 0;
	virtual void	WriteBrdVoteResult( DWORD dwSrcUserID,std::list<DWORD>& lsDstUser,const CVoteInfo& info ) = 0;
	virtual void	WriteVoteResult( DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwVoteID,BOOL bGiveup,const VoteResultList& result ) = 0;

	virtual void	WriteCreateGroupRoom( GroupRoomList& lsRoom ) = 0;
	virtual void	WriteEnterGroupRoomReq( DWORD dwRoomID,const GroupRoomUserMap& mapUser ) = 0;
	virtual void	WriteEnterMainRoomReq( const DwordList& lsUserID ) = 0;
	virtual void	WriteUserGroupState( DWORD dwStateUserID,BYTE bState) = 0;
	virtual void	WriteCloseGroupRoom( DwordList& lsRooomID,WORD wSessionID ) = 0;

	//水印相关
	virtual void	WriteClientWaterMark(DWORD dwUserID) = 0;
	virtual void	WriteClientWaterMarkRet( DWORD dwSrcID, DWORD dwUserID ) = 0;
	virtual void	WriteWaterMarkStat(bool bEnable, int nTime) = 0;
    
#ifdef _FS_OS_WIN
	//电话要求相关
	virtual void    WriteCallInvitation(const CallUserInfo &callInfo) = 0;         //拨号 
	virtual void    WriteCallInvitation(const CallUserInfoList &listCallUserInfo) = 0; //拨号 
	virtual void    WriteHangup(const CallUserInfo &callInfo) = 0;                 //挂机
	virtual void    WriteHangup(const CallUserInfoList &listCallUserInfo) = 0;         //挂机
	virtual void    WriteCallList(DWORD dwUserID,DWORD dwRoomID) = 0;         //呼叫列表请求
#endif
	virtual void	SetSessionID( WORD wSessionID ) = 0;
	virtual BOOL	ProcessMsg( PBYTE pbData,DWORD dwDataLen,IConfMsgReadCallback *pReadCallback ) = 0;
};

interface IPicutreAttrib
{
	virtual BOOL    GetImageSize( DWORD dwWidth,DWORD dwHeight ) = 0;
};


interface INotifyWndMsg
{
    virtual BOOL	OnMessage( UINT message, WPARAM wParam, LPARAM lParam
                               #if defined(_FS_OS_ANDROID)
                               , DWORD dwReserved
                               #endif
                             )=0;
};

interface IConfEventCallback: public IConfMsgReadCallback, public IPicutreAttrib
{
	virtual void	OnSessionReconnecting( WORD wSessionID ){};
	virtual void	OnSessionReconnected( WORD wSessionID ){};
	virtual void	OnSessionCreateFailed( WORD wSessionID ){};
	virtual void	OnSessionClosed( WORD wSessionID ){};
	virtual void	OnSessionCreated( WORD wSessionID ){};
	
	virtual void	OnTimer( UINT nTimerID ){};
	virtual void	OnAVMPLoginResult( int nResult ){};
	virtual void	OnCMNotify( WPARAM wParam,LPARAM lParam ){};
	virtual void	OnFileServerLoginResult( int nResult ){};
	virtual void	OnAddFile( const WFILELISTITEM* pFileItem ){};
	virtual void	OnDelFile( const GUID* guidFile ){};
	virtual void	OnAddDir( const WFILELISTITEM* pFileItem ){};
	virtual void	OnDelDir( const GUID* guiFile ){};
	virtual void	OnRenameRep( const GUID& guidFile,const WCHAR* wszFileDisaplayName,WORD wResult ){};
	virtual void    OnMoveFileRep( const GUID& guidFile,const GUID& guidParent,WORD wResult ){};
	virtual void	OnUpdateResult( int nResult ){};
	virtual void    OnUploadNotify( DWORD wParam,DWORD lParam ){};
	virtual void    OnDownLoadNotify( DWORD wParam,DWORD lParam ){};
    virtual void    OnVNCViewChangeNotify( DWORD wParam,DWORD lParam ){};

	virtual BOOL    GetImageSize( DWORD dwWidth,DWORD dwHeight ){return TRUE;};

	virtual void	OnRegResult( int nResult ){};
	virtual void	OnLoginResult( int nResult ){};
	virtual void	OnAddMeetingResult( int nResult ){};
	virtual void	OnMeetingLstResult( int nResult ){};
	virtual void	OnDelMeestingResult( int nResult ){};

};

interface IWBEventCallBack
{
	virtual void    OnWBCallBack( DWORD wParam,DWORD lParam ) = 0;
	virtual void    OnAddWB( DWORD dwWBID,LPCTSTR lpszName,int nDocType ) = 0;
	virtual void    OnCloseWB( DWORD dwWBID ) = 0;
	virtual void    OnSelectWB( DWORD dwWBID ) = 0;
	virtual void	SetTotalPage( DWORD dwWBID,int nTotalPage ) = 0;
	virtual void	SetCurPage( DWORD dwWBID,int nPage ) = 0;
	virtual void    UpdateRect(DWORD dwWBID, const RECT &rcUpdate, BOOL bEraseBk) = 0;
	virtual void    SwitchViewState(DWORD dwWBID) = 0;
#ifdef _FS_OS_ANDROID
	virtual void	StartLoadNotify(DWORD dwWBID) = 0;
	virtual void	FinishLoadNotify(DWORD dwWBID,TCHAR* szResul) = 0;
	virtual void    FileRecvError(DWORD dwWBID,DWORD dwCode) = 0;
#endif
};

interface IActionNotify
{
	virtual void	OnActionResult( int nResult ) = 0;
};

interface IAction
{
	virtual void	Cancel() = 0;
	virtual void	Done() = 0;
	virtual BOOL	Excute() = 0;
};

interface ILoginActionNotify:public IActionNotify
{
	virtual void	OnSessionClosed() = 0;
    virtual void	OnSessionCreateFailed() = 0;
    virtual BOOL    OnNotNeedUpdate() = 0;
    virtual BOOL	OnNeedUpdate( BOOL bMustUpdate,std::string strUpgradeVersion,std::list<tstring>& lsDownloadUrl ) = 0;
};

interface ILoginFrontServerActionNotify : public IActionNotify
{
    virtual void	OnSessionClosed() = 0;
    virtual void	OnSessionCreateFailed() = 0;
    virtual BOOL    OnNotNeedUpdate() = 0;
    virtual BOOL	OnNeedUpdate( BOOL bMustUpdate,std::string strUpgradeVersion,std::list<tstring>& lsDownloadUrl ) = 0;
    virtual void	OnLoadRoomList( RoomInfoList& lsRoomInfo ) = 0;
};

interface ISelectRoomNotify:public IActionNotify
{
	virtual void	OnSessionClosed( ) = 0;
	virtual void	LoadRoomList( RoomInfoList& lsRoomInfo ) = 0;
	virtual void	ResetRoomList() = 0;
};

interface IStartupRoomNotify:public IActionNotify
{
	//add by ron2012-07-06 用户取消输入密码登陆
	virtual void    OnUserCancel(){};
	virtual void	OnSessionClosed( ) = 0;
	virtual void	OnSessionCreateFailed( ) = 0;
	virtual void	OnState( int nState ) = 0;
	virtual BOOL	InputRoomPassword(const std::string& strPassword) = 0;
	virtual BOOL	OnNeedUpdate( BOOL bMustUpdate,std::string strUpgradeVersion,std::list<tstring>& lsDownloadUrl ) = 0;
};

interface IConfMainNotify:public IActionNotify
{
	virtual void	OnUserOnline( RoomUserInfo &userInfo ) = 0;
	virtual void	OnUserEnter( RoomUserInfo &userInfo ) = 0;
	virtual void    OnUserEnter(RoomUserList& lsRoomUser) = 0;
	virtual void	OnUserLeave( DWORD dwUserID ) = 0;
	virtual void    OnSyncOver(BOOL bSync) = 0;
	virtual void	OnUserAVInfoState( DWORD dwStateUserID) = 0;
	virtual void	OnUserAudioState( DWORD dwStateUserID,BYTE bMediaID,BYTE bAudioState ) = 0;
	virtual void	OnUserDataState( DWORD dwStateUserID,BYTE bDataState ) = 0;
	virtual void	OnUserVideoState( DWORD dwStateUserID,BYTE bState,BYTE bID ) = 0;
	virtual void	OnUserVNCState( DWORD dwStateUserID,BYTE bVNCState )  = 0;
	virtual void	OnUserMediaShare( DWORD dwStateUserID,BYTE bAudioShareID,BYTE bVideoShareID ) = 0;
	virtual void	OnUserAudioOutMute( DWORD dwStateUserID,BYTE bAudioOutMute ) = 0;
	virtual void	OnUserPrivateTalkState( DWORD dwOptUserID, DWORD dwStateUserID,DWORD dwDstUserID,BYTE bPrivateTalkState,BYTE bOldState )  = 0;
	virtual void	OnProprcessUserPrivateTalkState(PRIVATETALKINFO TalkInfo) = 0;
	virtual void	OnUserUpdateInfo( const RoomUserInfo& info ) = 0;
	virtual void	OnUserWBMarkState( DWORD dwStateUserID,BYTE bWBMarkState ) = 0;

	virtual void	OnSetRoomMode( BYTE bMode ) = 0;
	virtual void	OnSetRoomLock( BYTE bLock ) = 0;
	virtual void	OnSetRoomRecord( BYTE bRecord ) = 0;
	virtual void	OnChatMsg( DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,const TCHAR* szText,LOGFONT* pLogFont ) = 0;
	virtual void    OnMeetingCharNotify(tstring strContent,int nRoolTime,COLORREF colorFont) = 0;
	
	virtual void	OnWndState( RoomWndState& state,const VideoItemPosList& lsVideoPos,BOOL bValidFullMode  ) = 0;	
	virtual void	OnVNCControlState( DWORD dwSrcUserID,DWORD dwDstUserID,BYTE bState ) = 0;
	virtual void	OnAudioParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteAudioParam& param ) = 0;
    virtual void	OnVideoParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,RemoteVideoParam& param ) = 0;

    virtual void	OnSetAudioParamByRemote( AudioParam& param ) = 0;
    virtual void	OnSetVideoParamByRemote( VideoParam& param ) = 0;

	virtual void	OnCameraParamRep( DWORD dwSrcUserID,DWORD dwDstUserID,std::list<RemoteCameraParam>& lsParam ) = 0;
	
	virtual void	OnKnockUserNotify(DWORD dwUserID, const TCHAR *szDisplayName, BOOL bInLine) = 0;
	virtual void    OnSendFileNotify(DWORD dwSrcUserID,GUID& guid,tstring& strName,DWORD dwSize,
		DWORD dwCheckCode,WORD wSrvAppID,std::string& strSrvAddrLink) = 0;
	virtual void    OnTransDataFileStatus(DWORD dwSrcUserID, DWORD dwDstUserID, GUID& guid, BYTE bValue) = 0;
	virtual void	OnAVMixParamRep( const AudioMixParam& AudioParam,const VideoMixParam& VideoParam ) = 0;
	virtual void	OnSysMsg( int nMsgType,const TCHAR* szMsg ) = 0;
	
	virtual void	OnStartQuickRollCall( DWORD dwSrcUserID,const GUID& guidRollCall,DWORD dwDuration ) = 0;
	virtual void	OnStopQuickRollCall( DWORD dwSrcUserID,const GUID& guidRollCall ) = 0;
	virtual void	OnAckQuickRollCall( DWORD dwSrcUserID,DWORD dwDstUserID,const GUID& guidRollCall ) = 0;

	virtual void	OnUserRight( DWORD dwUserID,BYTE bUserRight ) = 0;
	virtual void	OnReqChairRightRet( BYTE bChairRight,int nResult ) = 0;
	virtual void	OnRoomEnableChat( BOOL bEnableChat ) = 0;
	virtual void	OnRoomEnableP2PChat( BOOL bEnableP2PChat ) = 0;
	virtual void	OnRoomEnablePubChat( BOOL bEnablePubChat ) = 0;
	virtual void	OnRoomEnableSendFile( BOOL bEnableSendFile ) = 0;
	virtual void	OnRoomEnableSaveWB( BOOL bEnableSaveWB ) = 0;
	virtual void	OnRoomReservePresenterVideo( BOOL bReservePresenterVideo ) = 0;
	virtual void	OnUserEnableChat( DWORD dwUserID,BOOL bEnableChat ) = 0;
	virtual void	OnVideoPollPreNotify( DWORD dwSrcUserID,DWORD dwVideoUserID,BYTE bID,DWORD dwRemainTime ) = 0;

	virtual void	OnOSDParamNoitfy( const VideoOSDParam& param ) = 0;

	virtual void	OnSilentNotify() = 0;
	virtual void	OnUserKicked( DWORD dwKickUserID ) = 0;
	virtual void	OnCloseRoom( int nReason ) = 0;
	
	virtual void	OnStartVote( DWORD dwSrcUserID,const CVoteInfo& info ) = 0;
	virtual void	OnStopVote( DWORD dwSrcUserID,DWORD dwVoteID ) = 0;
	virtual void	OnCloseVote( DWORD dwSrcUserID,DWORD dwVoteID ) = 0;
	virtual void	OnBrdVoteResult( DWORD dwSrcUserID,const CVoteInfo& info ) = 0;
	virtual void	OnVoteResult( DWORD dwSrcUserID,DWORD dwVoteID,BOOL bGiveup,const VoteResultList& result ) = 0;

	virtual void	OnAddFile( const WFILELISTITEM* pFileItem ) = 0;
	virtual void	OnDelFile( const GUID* guidFile ) = 0;
	virtual void	OnAddDir( const WFILELISTITEM* pFileItem ) = 0;
	virtual void	OnDelDir( const GUID* guiFile ) = 0;	
	virtual void	OnRenameRep( const GUID& guidFile,const WCHAR* wszFileDisaplayName,WORD wResult ) = 0;
	virtual void    OnMoveFileRep( const GUID& guidFile,const GUID& guidParent,WORD wResult ) = 0;

	virtual void	OnCreateGroupRoomMsg( const GroupRoomList& lsRoom ) = 0;
	virtual void	OnUserGroupStateMsg( DWORD dwUserID,BYTE bState ) = 0;
	virtual void	OnUserEnterGroupRoomRep( DWORD dwSrcUserID,const GroupRoomInfo& info,BYTE bRight ) = 0;
	virtual void	OnUserEnterMainRoomRep( DWORD dwSrcUserID ) = 0;
	virtual void	OnCloseGroupRoomMsg( DwordList& lsRooomID ) = 0;

	virtual void	OnSessionReconnecting( WORD wSessionID ) = 0;
	virtual void	OnSessionReconnected( WORD wSessionID ) = 0;
	virtual void	OnSessionClosed( WORD wSessionID ) = 0;

	//主会议信息
	virtual void	OnMainRoomUserOnline( RoomUserInfo &userInfo ) = 0;
	virtual void	OnMainRoomUserEnter( RoomUserInfo &userInfo ) = 0;
	virtual void	OnMainRoomUserLeave( DWORD dwUserID ) = 0;
	virtual void	OnMainRoomUserAVInfoState( DWORD dwStateUserID) = 0;
	virtual void	OnMainRoomUserAudioState( DWORD dwStateUserID,BYTE bMediaID,BYTE bAudioState ) = 0;
	virtual void	OnMainRoomUserDataState( DWORD dwStateUserID,BYTE bDataState ) = 0;
	virtual void	OnMainRoomUserVideoState( DWORD dwStateUserID,BYTE bState,BYTE bID ) = 0;
	virtual void	OnMainRoomUserAudioOutMute( DWORD dwStateUserID,BYTE bAudioOutMute ) = 0;
	virtual void	OnMainRoomUserPrivateTalkState( DWORD dwOptUserID, DWORD dwStateUserID,DWORD dwDstUserID,BYTE bPrivateTalkState,BYTE bOldState )  = 0;
	virtual void	OnMainRoomUserRight( DWORD dwUserID,BYTE bUserRight ) = 0;
	virtual void	OnMainRoomUserEnableChat( DWORD dwUserID,BOOL bEnableChat ) = 0;
	virtual void	OnMainRoomUserGroupStateMsg( DWORD dwUserID,BYTE bState ) = 0;	
	virtual void	OnMainRoomUserUpdateInfo( const RoomUserInfo& info ) = 0;	

	virtual void	OnMainRoomUserKicked( DWORD dwKickUserID ) = 0;
	virtual void	OnMainRoomCloseRoom( int nReason ) = 0;		
	virtual void	OnMainRoomChatMsg( DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,const TCHAR* szText,LOGFONT* pLogFont ) = 0;
	virtual void	OnMainRoomSysMsg( int nMsgType,const TCHAR* szMsg ) = 0;
	
#ifdef _FS_OS_WIN
	// 界面加水印
	virtual void	OnSetWaterMark( bool bWaterMark, int nTime) = 0;
	
	virtual void    OnCallInvitationMsg(CallUserInfoList &lsCallInfo) = 0;  //呼叫返回
	virtual void    OnHangupMsg(CallUserInfo &callUserInfo) = 0;            //挂断电话
	virtual void    OnStateMsg(CallUserInfo &callUserInfo) = 0;             //状态返回
	virtual void    OnCallListMsg(CallUserInfo &callUserInfo) = 0;        
#endif
};

interface IMediaControlNotify
{
	virtual void	OnPlay() = 0;
	virtual void	OnPause() = 0;
	virtual void	OnStop() = 0;
	virtual void	OnMute() = 0;
	virtual void	OnOpen() = 0;
	virtual void	OnSetting() = 0;
	virtual void	OnSetProgress( int nProgress ) = 0;
	virtual void	OnSetVolume( int nVolume ) = 0;
};

interface IReconnectNotify
{
	virtual void	OnReconnectCancel() = 0;
};

interface IConfConfig
{
	virtual VOID    SetConfigInfo(LPCTSTR lpszdefaultConfigInfo,LPCTSTR lpszconfigDataPath) = 0;
	virtual BOOL	IsHardwareClient() = 0;
	virtual	BOOL	InitConfig() = 0;	
	virtual BOOL	LoadConfig( HMODULE hModule = NULL ) = 0;
	virtual BOOL	SaveConfig() = 0;
	virtual VOID	GetDefaultAudioParam( AudioParam& param ) = 0;
	virtual VOID	GetDefaultVideoParam( VideoParam& param ) = 0;
	virtual BOOL	ReadClientConfig( ClientConfig& config ) = 0;
	virtual	VOID	AdjustByRoomConfig( RoomConfig& config ) = 0;
	virtual BOOL    ResetClientRoomConfig() = 0;
	virtual BOOL	WriteClientConfig( const ClientConfig& config ) = 0;
	virtual BOOL	ReadLoginParam( LoginParam& param ) = 0;
	virtual BOOL	WriteLoginParam( const LoginParam& param ) = 0;
	virtual BOOL	MakeLoginAddrLink( LoginParam& param,NetworkParam& NetParam ) = 0;
	virtual BOOL	ReadSysParam( SysParam& param ) = 0;
	virtual BOOL	WriteSysParam( const SysParam& param ) = 0;
	virtual BOOL	ReadNetParam( NetworkParam& param ) = 0;
	virtual BOOL	WriteNetParam( const NetworkParam& param ) = 0;
	virtual VOID	GetDefaultNetParam( NetworkParam& param ) = 0;
	virtual BOOL	ReadAVParam( AVParam& AVParam ) = 0;
	virtual BOOL	WriteAVParam( const AVParam& AVParam ) = 0;
	virtual BOOL	ReadVideoParam( VideoParam& param , BYTE bMediaID) = 0;
	virtual BOOL	WriteVideoParam( const VideoParam& param,  BYTE bMediaID  ) = 0;
	virtual BOOL	ReadAudioParam( AudioParam& param ) = 0;
	virtual BOOL	WriteAudioParam( const AudioParam& param ) = 0;
	virtual BOOL	ReadCameraParam( CameraParam& param,BYTE bMediaID   ) = 0;
	virtual BOOL	WriteCameraParam( const CameraParam& param,BYTE bMediaID   ) = 0;
	virtual BOOL	ReadFileParam( FileParam& param ) = 0;
	virtual BOOL	WriteFileParam( const FileParam& param ) = 0;
	virtual BOOL	ReadRecordParam( RecordParam& param ) = 0;
	virtual BOOL	WriteRecordParam( const RecordParam& param ) = 0;
	virtual	BOOL	WriteCaptionParam(const CaptionParam& param) = 0;
	virtual	BOOL	ReadCaptionParam(CaptionParam& param) = 0;
	virtual BOOL	WriteLocalRecordParam( const LocalRecordParam& param ) = 0;
	virtual BOOL	ReadLocalRecordParam( LocalRecordParam& param ) = 0;
	virtual BOOL	WriteMediaShareParam( const MediaShareParam& param ) = 0;
	virtual BOOL	ReadMediaShareParam( MediaShareParam& param ) = 0;
	virtual VOID	GetDefaultMsgNotifyParam( MsgNotifyParam& param ) = 0;;
	virtual BOOL	WriteMsgNotifyParam( const MsgNotifyParam& param ) = 0;
	virtual BOOL	ReadMsgNotifyParam( MsgNotifyParam& param ) = 0;
	virtual VOID	GetDefaultOSDParam( VideoOSDParam& param ) = 0;
	virtual BOOL	WriteOSDParam( const VideoOSDParam& param ) = 0;
	virtual BOOL	ReadOSDParam( VideoOSDParam& param ) = 0;
	virtual BOOL	SearchP2PSoftware( std::map<DWORD,tstring>& mapSoftware ) = 0;
	virtual BOOL	WriteDocShareParam( const DocShareParam& param ) = 0;
	virtual BOOL	ReadDocShareParam( DocShareParam& param ) = 0;
	virtual BOOL	GetDefaultHotKeyDefParam( HotKeyDef& param ) = 0;
	virtual BOOL	WriteHotKeyDefParam( const HotKeyDef& param ) = 0;
	virtual BOOL	ReadHotKeyDefParam( HotKeyDef& param ) = 0;
	virtual BOOL	ReadAppCustomParam( CHAR* szName,std::string& strValue ) = 0;

	virtual BOOL	WriteWaterMarkParam(int nTimer) = 0;
	virtual BOOL	ReadWaterMarkParam(int& nTime) = 0;	
	
	virtual BOOL	ReadOEMInfoParam( tagOEMInfo& param ) = 0;
    virtual BOOL    WriteOEMInfoParam(const tagOEMInfo &param) = 0;
    virtual BOOL    IsEqualOEMInfo(const tagOEMInfo oemInfo) = 0;
	
	virtual BOOL	ReadUpdateParam(struct_UpdateParam &UpdateParam)= 0;

	virtual BOOL    WriteUserLastConfigInfo(const tagUserLastConfigInfo &param) = 0;
	virtual BOOL    ReadUserLastConfigInfo(tagUserLastConfigInfo &param) = 0;
};

#define USERLIST_FLAG_ALL			0xFFFFFFFF
#define USERLIST_FLAG_OFFLINE		0x00000001
#define USERLIST_FLAG_GROUPROOM		0x00000002
#define USERLIST_FLAG_LOCALUSER		0x00000004
#define USERLIST_FLAG_DEFAULT		(USERLIST_FLAG_LOCALUSER)

interface IUserManager
{
	virtual int		CompareUser( DWORD dwUserID1,DWORD dwUserID2) = 0;
	virtual int		CompareUser( const RoomUserInfo& user1,const RoomUserInfo& user2 ) = 0;
	virtual void	SortUserList( RoomUserList& lsUserInfo ) = 0;

	virtual void	SetNodeList( const DeptNodeList& lsNode ) = 0;
	virtual void	SetDeptList( const DeptNodeList& lsDept ) = 0;
	virtual BOOL	GetNodeList( DeptNodeList& lsNode ) = 0;
	virtual BOOL	GetDeptList( DeptNodeList& lsDept ) = 0;
	
	virtual void	SetShowUserTree( BOOL bShow ) = 0;
	virtual BOOL	GetShowUserTree() = 0;
	virtual BOOL	GetUserTreeNodeList( DeptNodeList& lsNode ) = 0;
	virtual tstring GetUserTreeParentNodeID( const RoomUserInfo& info ) = 0;
	
	virtual BOOL	GetLocalUser( RoomUserInfo& info ) = 0;
	virtual BOOL	GetUserByUserName( LPCTSTR lpszUserName,RoomUserInfo& info ) = 0;
	virtual BOOL	GetUser( DWORD dwUserID,RoomUserInfo& info ) = 0;
	virtual BOOL	ModifyUser( DWORD dwUserID, RoomUserInfo& info ) = 0;
	virtual VOID	RemoveUser( DWORD dwUserID ) = 0;
	virtual VOID	AddUser( RoomUserInfo& info ) = 0;
	virtual VOID	UserOffline( DWORD dwUserID ) = 0;
	
	virtual DWORD	GetLocalUserID() = 0;
	virtual VOID	SetLocalUserID( DWORD dwUserID ) = 0;
	virtual DWORD	GetUserCount() = 0;
	virtual DWORD	GetOnlineUserCount() = 0;
	virtual VOID	GetUserList( RoomUserList& lsUserInfo,DWORD dwFlag = USERLIST_FLAG_DEFAULT ) = 0;
	virtual VOID	GetUserRightList( RoomUserList& lsUserInfo,int nUserRight,DWORD dwFlag = USERLIST_FLAG_DEFAULT ) = 0;
	virtual void	SearchUser( LPCTSTR lpszFindName,RoomUserList& lsUserInfo ) = 0;
	virtual BOOL	GetDataUser( RoomUserInfo& info ) = 0;
	virtual BOOL	HasDataUser() = 0;
	virtual void	Clear() = 0;
};

#ifdef _FS_OS_WIN

interface ICallUserManager
{
	virtual VOID    Init() = 0;  //初始化
	virtual void	Clear() = 0;
	
	virtual void    SetLocalUserID(DWORD dwLocalUserId) = 0;

	virtual BOOL    AddCallUser(const CallUserInfo& info) = 0;   //添加一个拨号
	virtual BOOL    DelCallUser(const CallUserInfo &info) = 0;   //删除
	virtual BOOL    CoverCallUser(const CallUserInfo& info) = 0; //覆盖
	virtual BOOL    IsHaveCallPhone() = 0;                       //判断是否有电话在通话中...
	virtual BOOL    CheckIsCalling(const tstring &strPhonenumber) = 0;    //判断是否正在拨号
	virtual BOOL	ModifyCallUserStatus(DWORD dwID,CallUserInfo::CallUserStatus status ) = 0;         //修改状态
	virtual BOOL	ModifyCallUserStatus(CallUserInfo &user,CallUserInfo::CallUserStatus status ) = 0; //修改状态
	virtual BOOL	ModifyCallUserOperateStatus(CallUserInfo &user,BYTE bOp_ ) = 0; //修改
	virtual BOOL    ModifyCallUserInfo(DWORD dwId,const tstring &strNickName,BYTE bSex) = 0;
	virtual BOOL    MergeCallUser(CallUserInfo& info) = 0;        //合并
public:
	//未参会人 管理 只有从OnUserEnter 和 OnuserOnline 进入
	virtual BOOL    AddNotInMeetingUser(DWORD dwId) = 0;
	virtual BOOL    TestInNotInMeetingUserList(CallUserInfoList& infoList) = 0;
		
	//最近联系人 管理
	virtual VOID    SetMaxHistoryUser(const UINT nMax) = 0;     //设置最近联系人显示数量
	virtual UINT    GetMaxHistoryUser() = 0;
	virtual BOOL    AddCallHistoryUser(DWORD dwId) = 0;
	virtual BOOL    TestInHistoryUserList(CallUserInfoList& infoList) = 0;

	// 拨号列表 管理 
	virtual BOOL    AddCallingUser(DWORD dwId) = 0;
	virtual BOOL    TestInCallingUserList(CallUserInfoList& infoList) = 0;
	
public:
	virtual BOOL    GetAllCallPhone(CallUserMap& mapInfo) = 0;
	virtual BOOL    GetCallUserByCallID(DWORD dwId ,CallUserInfo& info) = 0;
	virtual BOOL    GetCallUserByVirtualUserID(DWORD dwUserId,CallUserInfo& info) = 0;
	virtual BOOL    GetCallUserByPhone (const tstring &strPhone,CallUserInfo& info) = 0;	
	
	virtual BOOL    WriteCallList(DwordList dwIdList) = 0;
	virtual BOOL    ReadCallList(DWORD &dwCallId) = 0;
		
	virtual BOOL    WriteHangupList(DwordList dwIdList) = 0;
	virtual BOOL    ReadHangupList(DWORD &dwCallId) = 0;

	virtual BOOL    TestCallUserSatus(CallUserInfo &info,CallUserInfo::CallUserStatus status) = 0;
	virtual BOOL    TestCallUserSatus(CallUserInfoList &infoList,CallUserInfo::CallUserStatus status) = 0;

public:
	virtual BOOL    AddRestoreCallList(CallUserInfoList &lsCallInfo) = 0;
	virtual BOOL    GetRestoreCallList(CallUserInfoList &lsCallInfo) = 0;
	virtual VOID    ClearRestoreCallList() = 0;
};

interface ICallUserDBManager
{
	virtual BOOL InitDB() = 0;
	virtual BOOL IsInit() = 0;

	virtual BOOL UpdateCallUserInfo(CallUserInfo &rCallUserInfo) = 0;                     //更新用户信息
	virtual BOOL UpdateCallInfo(CallUserInfo &rCallUserInfo,UINT nOp) = 0;                //更新拨号信息
	virtual BOOL UpdateCallInfoUserID(DWORD dwOldUserId,CallUserInfo &rCallUserInfo) = 0; //更新用户ID
	virtual BOOL AddCallInfo(CallUserInfo &rCallUserInfo) = 0;                //添加拨号信息
	virtual BOOL GetCallInfo(DWORD dwCallId,CallUserInfo &rCallUserInfo) = 0; //获取拨号信息
	virtual BOOL GetCallInfoByRUserID(DWORD dwUserId,CallUserInfoList &callUserInfoList) = 0; //获取拨号信息
	virtual BOOL GetCallInfoByVUserID(DWORD dwUserId,CallUserInfo &info) = 0;				  //获取拨号信息
	virtual BOOL DelCallInfo(DWORD dwID) = 0;			  // 删除最近联系人
	virtual BOOL GetLocalCallHistory(CallUserInfoList &callUserInfoList,UINT nMaxCount) = 0;  //获取拨号记录 nMaxCount条
	virtual UINT GetMaxHistoryRecord() = 0;

	virtual BOOL MergerRealUserCallInfo(CallUserInfoList &oldCallInfoList,RoomUserInfo &newRoomUserInfo) = 0; //合并用户
	virtual void  SetLocalID(DWORD dwLocalRoomId,DWORD dwLocalUserId) = 0;
	virtual DWORD GetLocalUserID() = 0;
	virtual DWORD GetLocalRoomID() = 0;
};
#endif

interface IConfRecorder
{
	virtual BOOL	StartRecord() = 0;
	virtual void	StopRecord() = 0;
	virtual void	PauseRecord() = 0;
	virtual void	RestoreRecord() = 0;
	virtual int		GetRecordState() = 0;
	virtual void	OnWndStateChanged() = 0;
	virtual void	OnChatMsg( DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,LPCTSTR lpszMsg ) = 0;
	virtual void    OnRecvMedia(DWORD dwUserID,BYTE bMediaType,BYTE bMediaID,BOOL bRecv,DWORD dwUserData) = 0;
	virtual LPCTSTR	GetRecordFilePath() = 0;
	virtual DWORD	GetRecordSeconds() = 0;
};

interface ILocalRecorder
{
	virtual BOOL	StartRecord() = 0;
	virtual void	StopRecord() = 0;
	virtual int		GetRecordState() = 0;
};

interface IVirtualVideoDevConfig 
{
	virtual BOOL	ParseVirualDevName( const WCHAR *wszText,int& nCount ) = 0;
	virtual void	GetVirtualDevName( WCHAR* wszText,UINT nSize ) = 0;
	virtual int		GetCurrentVirtualDev() = 0;
	virtual BOOL	SetCurrentVirtualDev( int nDev ) = 0;
	virtual int		GetVirtualDevCount() = 0;
};

interface IADManager
{
	virtual void	StopUpdate() = 0;
	virtual void	StartUpdate() = 0;
	virtual BOOL	GetLogoFileInfo( WCHAR* wszFilePath,DWORD dwSize1,WCHAR* wszHyperlink,DWORD dwSize2 ) = 0;
	virtual void	SetEventCallback( IConfEventCallback *pEventCallback) = 0;
};

struct AVPluginItem{
	
	GUID		guidPlugin;
	TCHAR		szPluginName[64];
	BOOL		bEnableAudioDev;
	TCHAR		szAudioDevName[64];
	BOOL		bEnableVideoDev;
	TCHAR		szVideoDevName[64];
	TCHAR		szConfigFile[MAX_PATH];
	IAVPlugin*	pPlugin;
};

typedef std::vector<AVPluginItem>		AVPluginVector;

interface IAVPluginConfig  
{
	virtual BOOL Get( int nIndex,AVPluginItem& item ) = 0;
	virtual BOOL Set( int nIndex,AVPluginItem& item) = 0;
	virtual BOOL Add( AVPluginItem& item ) = 0;
	virtual BOOL Remove( int nIndex ) = 0;
	virtual int  GetCount() = 0;
	virtual void Save() = 0;
};


interface IAppControler
{
	virtual void			OnQuit() = 0;
	virtual void			OnDisconnect() = 0;
	//virtual IConfDataContainer* GetContainer() = 0;
	virtual void			SwitchRoom( int nRoomIndex ) = 0;
	virtual void			EnterGroupRoom( DWORD dwGroupRoomID ) = 0;
	virtual void			EnterMainRoom() = 0;
};

#endif
