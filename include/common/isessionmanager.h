#ifndef __ISESSION_MANAGER_H
#define __ISESSION_MANAGER_H

#include "wbasetype.h"
#include "wcombase.h"
#include "wnetworkdef.h"
#include "ibasecomponent.h"

#ifdef __cplusplus
extern "C" {
#endif

#define			SESSION_EVENT_ACCEPT					0x1000	//接收到新的会话
#define			SESSION_EVENT_CREATED					0X1001	//会话已建立
#define			SESSION_EVENT_CREATEFAIL				0X1002	//会话建立失败
#define			SESSION_EVENT_CLOSED					0x1003	//会话已关闭
#define			SESSION_EVENT_DATA						0x1004	//接收到会话数据
#define			SESSION_EVENT_RECONNECTING				0x1005	//会话正在重连
#define			SESSION_EVENT_RECONNECTED				0x1006	//会话重连成功
#define			SESSION_EVENT_SEND						0x1007	//网络缓存区满后,用于通知可以再次发送数据,用于可靠会话

	typedef struct{
		FS_INT32	nEventType;
		FS_UINT16	nSessionID;
		PBYTE	    pbData;
		FS_UINT32	dwDataLen;
		FS_UINT	    dwUserData1;
		FS_UINT	    dwUserData2;

	}SESSION_EVENT;

	typedef enum{
		SESSIONTYPE_RELIABLE,
		SESSIONTYPE_UNRELIABLE
	}SESSIONTYPE;

	typedef enum{
		SESSION_CREATING,	//正在创建会话
		SESSION_CREATED,	//会话已建立
		SESSION_DISCONNECT,	//会话已断开
		SESSION_RECONNECTING,//正在重连会话
		SESSION_CLOSED		//会话已关闭
	}SessionState;

	typedef struct{

		SESSIONTYPE		Type;
		FS_INT32		bTcp;
		FS_UINT32		dwLocalIP;
		FS_UINT16		wLocalPort;
		FS_UINT32		dwRemoteIP;
		FS_UINT16		wRemotePort;
		SessionState	state;
	}SESSIONINFO;

#define		SESSION_SRVADDRTYPE_TCP		0x01		//TCP
#define		SESSION_SRVADDRTYPE_UDP		0x02		//UDP
#define		SESSION_SRVADDRTYPE_HTTP	0x04		//HTTP
	typedef struct{
		FS_UINT32	dwIP;
		FS_UINT16	wPort;
		FS_UINT16	wAddrType;
	}SESSIONSRVADDRITEM;


#define WSESSION_SECURITY_NONE			0x00		//协议无加密
#define WSESSION_SECURITY_XOR			0x01		//异或加密

	//SessionManager2 object GUID
	// {33B5D98E-E3AD-4407-8311-960DE9591D2A}
	DEFINE_GUID( CLSID_SessionManager2, 
		0x33b5d98e, 0xe3ad, 0x4407, 0x83, 0x11, 0x96, 0xd, 0xe9, 0x59, 0x1d, 0x2a);

	//ISessionManager's GUID
	// {0290FEBF-B376-4ebd-8B23-664D03E4DD6B}
	DEFINE_GUID(IID_ISessionManager, 
	0x290febf, 0xb376, 0x4ebd, 0x8b, 0x23, 0x66, 0x4d, 0x3, 0xe4, 0xdd, 0x6b);

	//----------------------------------------------------------------------------
	// ISessionManager
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(ISessionManager,IUnknown )
	{		
		STDMETHOD(Start) (THIS_) PURE;
		STDMETHOD(Stop)( THIS_ ) PURE;

		//监听网络服务器端口
		STDMETHOD_(FS_UINT32,AddUdpListen) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort ) PURE;		
		
		STDMETHOD(RemoveUdpListen) (THIS_ FS_UINT32	uListern ) PURE;		

		STDMETHOD_(FS_UINT32,AddTcpListen) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort ) PURE;		
		
		STDMETHOD(RemoveTcpListen) (THIS_ FS_UINT32 uListern ) PURE;

		STDMETHOD(GetAddrLink)( THIS_ CHAR*	lpszLink,FS_UINT32 *pdwSize,BOOL bTcp,BOOL bUdp ) PURE;

		//注册应用
		STDMETHOD(RegisterApplication)( THIS_ FS_UINT16 wApplicationID,WBASE_NOTIFY* pNotify,BYTE bSecurityType ) PURE;

		STDMETHOD(UnRegisterApplication)( THIS_ FS_UINT16 wApplicationID ) PURE;

		//创建会话
		STDMETHOD_( FS_UINT16,CreateSession )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD(Send)( THIS_ FS_UINT16 nSessionID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;

		STDMETHOD(GetSessionInfo)( THIS_ FS_UINT16 nSessionID,SESSIONINFO *pInfo ) PURE;

		STDMETHOD(SetSessionNotify)( THIS_ FS_UINT16 nSessionID,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD(SetUserData)( THIS_ FS_UINT16 nSessionID,FS_UINT dwUserData1,FS_UINT dwUserData2 ) PURE;

		STDMETHOD_(SESSION_EVENT*,GetEvent)( THIS_ FS_UINT16 nSessionID) PURE;

		STDMETHOD( FreeEvent )( THIS_ FS_UINT16 nSessionID,SESSION_EVENT *pEvent ) PURE;

		STDMETHOD( SetSessionTimeout )( THIS_ FS_UINT16 nSessionID,FS_UINT32 dwTimeout ) PURE;

		STDMETHOD( CloseSession )( THIS_ FS_UINT16 nSessionID ) PURE;
	};

	//参数类型定义
#define			WSESSION_PARAM_SOSENDBUFSIZE		0X1000	//设置SOCKET底层发送缓存区大小
#define			WSESSION_PARAM_SENDBUFSIZE			0X1001	//设置SOCKET发送缓存区大小,TCP默认为32K,UDP默认为16K
#define			WSESSION_PARAM_ACKSENDBUFSIZE		0X1002	//设置确认发送缓存区大小,用于可靠会话

#define			WSESSION_PARAM_SORECVBUFSIZE		0x1005	//设置SOCKET底层接收缓存区大小
#define			WSESSION_PARAM_RECVBUFSIZE			0x1006	//设置SOCKET接收缓存区大小,TCP默认为16K,UDP默认为64K

#define			WSESSION_PARAM_CHECKTIMEOUT			0x1010	//设置当SESSION多长时间没有接收到数据,即认为会话已经断开,并开始重连,默认为16秒

	//原始应用参数定义
	typedef struct{
		
		CHAR		pbFlagData[32];		//标识数据,不能超过32个字节
		FS_UINT32		dwFlagLen;			//标识数据长度
		BOOL		bCaseSensitive;		//标识数据是否大小写敏感
		BOOL		bSupportTCP;		//是否支持TCP
		BOOL		bSupportUDP;		//是否支持UDP
		
	}SESSIONRAWAPP;

	//ISessionManager2's GUID
	// {A413E359-E79F-4804-B166-34B77ED20D2F}
	DEFINE_GUID( IID_ISessionManager2, 
		0xa413e359, 0xe79f, 0x4804, 0xb1, 0x66, 0x34, 0xb7, 0x7e, 0xd2, 0xd, 0x2f);

	DECLARE_INTERFACE_(ISessionManager2,IUnknown )
	{		
		STDMETHOD(Start) (THIS_) PURE;
		STDMETHOD(Stop)( THIS_ ) PURE;
		
		//监听网络端口
		STDMETHOD_(FS_UINT32,AddUdpListen2) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort,BOOL bServer ) PURE;
		
		STDMETHOD(RemoveUdpListen) (THIS_ FS_UINT32	uListern ) PURE;		
		
		STDMETHOD_(FS_UINT32,AddTcpListen2) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort,BOOL bServer ) PURE;
		
		STDMETHOD(RemoveTcpListen) (THIS_ FS_UINT32 uListern ) PURE;
		
		STDMETHOD(GetAddrLink)( THIS_ CHAR*	lpszLink,FS_UINT32 *pdwSize,BOOL bTcp,BOOL bUdp ) PURE;
		
		//注册应用
		STDMETHOD(RegisterApplication)( THIS_ FS_UINT16 wApplicationID,WBASE_NOTIFY* pNotify,BYTE bSecurityType ) PURE;
		
		STDMETHOD(UnRegisterApplication)( THIS_ FS_UINT16 wApplicationID ) PURE;
		
		//
		//注册原始应用,该种应用,只是为了共享端口,会话层不对该种应用的数据包做任何处理.
		//对于TCP的应用,将根据客户端发送的第一个包的前面几个字节的数据判断应用类型
		//对于UDP的应用,将根据每个包的前面几个字节的数据类型来判断应用类型
		//返回系统分配的应用ID
		//
		STDMETHOD_(FS_UINT32,RegisterRawApplication)( THIS_ SESSIONRAWAPP *pApplication,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD(UnRegisterRawApplication)( THIS_ FS_UINT32 dwRawAppID ) PURE;

		//
		//获取原始应用的消息，直接返回网络事件，可以直接调用网络层接口释放事件
		//
		STDMETHOD_( WNET_EVENT*,GetRawEvent )( THIS_ FS_UINT32 dwRawAppID ) PURE;

			
		STDMETHOD( FreeRawEvent )( THIS_ FS_UINT32 dwRawAppID,WNET_EVENT* pEvent ) PURE;

		//创建会话
		STDMETHOD_( FS_UINT16,CreateSession )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify ) PURE;
		
		STDMETHOD(Send)( THIS_ FS_UINT16 nSessionID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;
		
		STDMETHOD(GetSessionInfo)( THIS_ FS_UINT16 nSessionID,SESSIONINFO *pInfo ) PURE;
		
		STDMETHOD(SetSessionNotify)( THIS_ FS_UINT16 nSessionID,WBASE_NOTIFY* pNotify ) PURE;
		
		STDMETHOD(SetUserData)( THIS_ FS_UINT16 nSessionID,FS_UINT dwUserData1,FS_UINT dwUserData2 ) PURE;
		
		STDMETHOD_(SESSION_EVENT*,GetEvent)( THIS_ FS_UINT16 nSessionID) PURE;
		
		STDMETHOD( FreeEvent )( THIS_ FS_UINT16 nSessionID,SESSION_EVENT *pEvent ) PURE;
		
		STDMETHOD( SetSessionTimeout )( THIS_ FS_UINT16 nSessionID,FS_UINT32 dwTimeout ) PURE;
		
		//设置Session参数
		STDMETHOD( SetSessionParam )( THIS_ FS_UINT16 uSessionID,FS_INT32 nParamType,const CHAR* pValue,FS_INT32 nValueSize ) PURE;
		
		//获取Session参数
		STDMETHOD( GetSessionParam )( THIS_ FS_UINT16 uSessionID,FS_INT32 nParamType,CHAR* pValue,FS_INT32* pValueSize ) PURE;

		STDMETHOD( CloseSession )( THIS_ FS_UINT16 nSessionID ) PURE;

		//设置首选的连接地址
		STDMETHOD( SetPreferAddr )( THIS_ FS_UINT32 dwPreferAddr ) PURE;

		//创建会话,使用本地监听的UDP端口
		STDMETHOD_( FS_UINT16,CreateSession2 )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify,FS_UINT32 uUdpListen ) PURE;

		//创建会话,使用共享TCP连接
		STDMETHOD_( FS_UINT16,CreateSession3 )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify,FS_UINT32 uUdpListen,BOOL bShareTCP ) PURE;

		//创建会话,使用共享TCP连接
		STDMETHOD_( FS_UINT32,ParseAndSortAddrLink )( THIS_ const CHAR* szServerAddrLink,FS_UINT32 dwAddrTypeMask,FS_UINT32 dwPreferAddrType,HANDLE hStopEvent,SESSIONSRVADDRITEM **ppSrvAddrItem ) PURE;

		//释放地址项内存
		STDMETHOD( FreeSrvAddrItem )( THIS_ SESSIONSRVADDRITEM *pSrvAddrItem ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif