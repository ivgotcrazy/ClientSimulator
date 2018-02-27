#ifndef __WNETWORK_H
#define	__WNETWORK_H

#include "wbasetype.h"
#include "wnetworkdef.h"
#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
#include "log.h"
#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX

//初始化网络库
WNETRESULT		WNET_Init( BOOL bUseTcp,BOOL bUseUdp,FS_UINT32 dwMaxTcpCount,FS_UINT32 dwMaxUdpCount, LPCTSTR szLogPath);

//释放网络库
WNETRESULT		WNET_Release();

//设置日志级别
WNETRESULT		WNET_SetLogLevel(FS_INT32 nLogLevel);
#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
WNETRESULT		WNET_SetLogLevel(LogLevel nLogLevel);

//设置日志管理器信息
WNETRESULT      WNET_SetLogInfo(ILogMgr *pLogMgr, FS_INT nLoggerID);
#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX

//设置代理
WNETRESULT		WNET_SetProxy( WNET_PROXY *pProxy );

//获取代理
WNETRESULT		WNET_GetProxy( WNET_PROXY *pProxy );


//测试代理服务器
WNETRESULT		WNET_TestProxy( WNET_PROXY *pProxy,char *szDestAddr,FS_UINT16 wDestPort );

//
//TCP网络接口
//

//打开监听端口
WSOCKET			WNET_TCP_AddListen( FS_UINT32 dwListenIP,FS_UINT16 wListenPort,WBASE_NOTIFY *pMode );

//关闭监听端口
WNETRESULT		WNET_TCP_RemoveListen( WSOCKET sock );

//连接服务器
WSOCKET			WNET_TCP_Connect( FS_UINT32 dwDestIP,FS_UINT16 wDestPort,FS_UINT32 dwWaitTime,WBASE_NOTIFY *pMode,FS_UINT dwUserData );

//设置消息通知方式
WNETRESULT		WNET_TCP_SetNotify( WSOCKET sock,WBASE_NOTIFY *pMode );

//暂停数据接收
WNETRESULT		WNET_TCP_PauseRead( WSOCKET sock,BOOL bPause );

//发送数据
WNETRESULT		WNET_TCP_Send( WSOCKET sock,char *pData,FS_INT32 nDataLen );

//获取事件
WNET_EVENT*		WNET_TCP_PopupMsg( WSOCKET sock,FS_UINT32 dwWaitTime );

//释放事件
WNETRESULT		WNET_TCP_FreeMsg( WSOCKET sock,WNET_EVENT *pEvent );

//设置参数
WNETRESULT		WNET_TCP_SetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//设置用户数据
WNETRESULT		WNET_TCP_SetUserData( WSOCKET sock,FS_UINT dwUserData );

//获取参数
WNETRESULT		WNET_TCP_GetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//关闭SOCK
WNETRESULT		WNET_TCP_Close( WSOCKET sock );

WNET_EVENT*		WNET_TCP_AllocMsg( );

//
//UDP网络接口
//

//创建UDP SOCK
WSOCKET			WNET_UDP_Create( FS_UINT32 dwBindIP,FS_UINT16 wBindPort,WBASE_NOTIFY *pMode,FS_UINT dwUserData );

//设置消息通知方式
WNETRESULT		WNET_UDP_SetNotify( WSOCKET sock,WBASE_NOTIFY *pMode );

//加入多播组
WNETRESULT		WNET_UDP_JoinGroup( WSOCKET sock,FS_UINT32 dwGroupIP );

//离开多播组
WNETRESULT		WNET_UDP_LeaveGroup( WSOCKET sock,FS_UINT32 dwGroupIP );

//发送数据
WNETRESULT		WNET_UDP_Send( WSOCKET sock,char *pData,FS_INT32 nDataLen,FS_UINT32 dwDestIP,FS_UINT16 wDestPort );

//获取事件
WNET_EVENT*		WNET_UDP_PopupMsg( WSOCKET sock,FS_UINT32 dwWaitTime );

//释放事件
WNETRESULT		WNET_UDP_FreeMsg( WSOCKET sock,WNET_EVENT *pEvent );

WNET_EVENT*		WNET_UDP_AllocMsg( );

//设置用户数据
WNETRESULT		WNET_UDP_SetUserData( WSOCKET sock,FS_UINT dwUserData );

//设置参数
WNETRESULT		WNET_UDP_SetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//获取参数
WNETRESULT		WNET_UDP_GetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//关闭SOCK
WNETRESULT		WNET_UDP_Close( WSOCKET sock );

//PING
WNETRESULT		WNET_Ping( FS_UINT32 dwDestIP,WBASE_NOTIFY *pMode );

//获取PING结果
WNETRESULT		WNET_GetPingResult( FS_UINT32 dwDestIP,FS_UINT32* pdwMin,FS_UINT32* pdwMax,FS_UINT32* pdwAvg );

WNETRESULT		WNET_RemovePing( FS_UINT32 dwDestIP,WBASE_NOTIFY *pMode );


#endif