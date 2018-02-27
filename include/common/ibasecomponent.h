#ifndef __FRAMEWORD_IBASE_COMPONENT_H
#define __FRAMEWORD_IBASE_COMPONENT_H

#include "wbasetype.h"
#include "wcombase.h"
#include "stdarg.h"
#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
#include "log.h"
#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX
using namespace FsMeeting;

#ifdef __cplusplus
extern "C" {
#endif

	DECLARE_INTERFACE( IWTimer )
	{
		//
		//定时器事件，如果返回值不等于S_OK，系统将关闭该定时器
		//
		STDMETHOD(OnTimer) (THIS_
			FS_UINT32	nTimerID
			) PURE;		
	};

	//
	//定时器事件回调接口
	typedef HRESULT	( CALLBACK* TIMERCALLBACK)( FS_UINT32 uTimerID,FS_UINT dwUserData );

	// ITimerAllocator's GUID
	// {270A386D-8E0B-4815-815A-ABDFCFE7368F}
	DEFINE_GUID(IID_ITimerAllocator, 
	0x270a386d, 0x8e0b, 0x4815, 0x81, 0x5a, 0xab, 0xdf, 0xcf, 0xe7, 0x36, 0x8f);
	
	
	//----------------------------------------------------------------------------
	// ITimerAllocator
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(ITimerAllocator, IUnknown)
	{
		//
		//增加定时器
		//
		STDMETHOD_( FS_UINT32,AddTimer) (THIS_
			FS_UINT32		uDelay,
			WBASE_NOTIFY*	pNotify
			) PURE;
		//
		//删除定时器
		//
		STDMETHOD(RemoveTimer) (THIS_
			FS_UINT32 uTimer
			) PURE;		
		
	};

	// IWBuffer's GUID
	// {BE715D07-A80A-45ab-84E5-BEC729223813}
	DEFINE_GUID( IID_IWBuffer, 
		0xbe715d07, 0xa80a, 0x45ab, 0x84, 0xe5, 0xbe, 0xc7, 0x29, 0x22, 0x38, 0x13);
	
	//----------------------------------------------------------------------------
	// IWBuffer
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IWBuffer, IUnknown)
	{
        STDMETHOD(GetUserData)(THIS_ FS_UINT *pdwUserData) PURE;
        STDMETHOD(SetUserData)(THIS_ FS_UINT dwUserData) PURE;

		STDMETHOD (GetLength)( THIS_ FS_UINT32 *pdwLength ) PURE;
		STDMETHOD (SetLength)( THIS_ FS_UINT32 dwLength ) PURE;

		STDMETHOD (GetBufferSize)( THIS_ FS_UINT32 *pdwSize )  PURE;

		STDMETHOD (GetBuffer)( THIS_ BYTE** ppBuffer ) PURE;
		
		STDMETHOD (WriteData)( THIS_ PBYTE pbData,FS_UINT32 dwLength ) PURE;

		STDMETHOD (Append)( THIS_ PBYTE pbData,FS_UINT32 dwLength ) PURE;		
	};

	// IMemoryAllocator's GUID
	// {122CF2D6-086D-4e0a-AB0A-C5DDBADB40B9}
	DEFINE_GUID(IID_IMemoryAllocator, 
		0x122cf2d6, 0x86d, 0x4e0a, 0xab, 0xa, 0xc5, 0xdd, 0xba, 0xdb, 0x40, 0xb9);
	

	//----------------------------------------------------------------------------
	// IMemoryAllocator
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IMemoryAllocator, IUnknown)
	{
		STDMETHOD (Alloc)( THIS_ FS_UINT32 dwSize,IWBuffer** pBuffer ) PURE;
	};
		
	// IWNetwork's GUID
	// {ECAE2E31-47F3-4365-9552-158C0C727CFB}
	DEFINE_GUID(IID_IWNetwork, 
		0xecae2e31, 0x47f3, 0x4365, 0x95, 0x52, 0x15, 0x8c, 0xc, 0x72, 0x7c, 0xfb);
	
#include "wnetworkdef.h"
	//----------------------------------------------------------------------------
	// IWNetwork
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IWNetwork, IUnknown)
	{
		//设置代理
		STDMETHOD_(WNETRESULT,SetProxy)( THIS_ WNET_PROXY *pProxy ) PURE;
		
		//测试代理服务器
		STDMETHOD_(WNETRESULT,TestProxy)( THIS_ WNET_PROXY *pProxy,char *szDestAddr,FS_UINT16 wDestPort ) PURE;
		
		//
		//TCP网络接口
		//
		
		//打开监听端口
		STDMETHOD_( WSOCKET,TCP_AddListen)( THIS_ FS_UINT32 dwListenIP,FS_UINT16 wListenPort,WBASE_NOTIFY *pMode ) PURE;
		
		//关闭监听端口
		STDMETHOD_( WNETRESULT,TCP_RemoveListen )( THIS_ WSOCKET sock ) PURE;
		
		//连接服务器
		STDMETHOD_( WSOCKET,TCP_Connect)( THIS_ FS_UINT32 dwDestIP,FS_UINT16 wDestPort,FS_UINT32 dwWaitTime,WBASE_NOTIFY *pMode,FS_UINT dwUserData ) PURE;
		
		//设置消息通知方式
		STDMETHOD_( WNETRESULT,TCP_SetNotify)( THIS_ WSOCKET sock,WBASE_NOTIFY *pMode ) PURE;
		
		//设置是否暂停接收数据
		STDMETHOD_( WNETRESULT,TCP_PauseRead)( THIS_ WSOCKET sock,BOOL bPause ) PURE;

		STDMETHOD_( WNETRESULT,TCP_SetUserData)( THIS_ WSOCKET sock,FS_UINT dwUserData ) PURE;

		//发送数据
		STDMETHOD_( WNETRESULT,TCP_Send)( THIS_ WSOCKET sock,char *pData,FS_INT32 nDataLen ) PURE;
		
		//获取事件
		STDMETHOD_( WNET_EVENT*,TCP_PopupMsg)( THIS_ WSOCKET sock,FS_UINT32 dwWaitTime ) PURE;
		
		//释放事件
		STDMETHOD_( WNETRESULT,TCP_FreeMsg)( THIS_ WSOCKET sock,WNET_EVENT *pEvent ) PURE;
		
		//设置参数
		STDMETHOD_( WNETRESULT,TCP_SetParam)( THIS_ WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize ) PURE;
		
		//获取参数
		STDMETHOD_( WNETRESULT,TCP_GetParam)( THIS_ WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize ) PURE;
		
		//关闭SOCK
		STDMETHOD_( WNETRESULT,TCP_Close)( THIS_ WSOCKET sock ) PURE;
		
		//
		//UDP网络接口
		//
		
		//创建UDP SOCK
		STDMETHOD_( WSOCKET,UDP_Create)( THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort,WBASE_NOTIFY *pMode,FS_UINT dwUserData ) PURE;
		
		//设置消息通知方式
		STDMETHOD_( WNETRESULT,UDP_SetNotify)( THIS_ WSOCKET sock,WBASE_NOTIFY *pMode ) PURE;
		
		STDMETHOD_( WNETRESULT,UDP_SetUserData)( THIS_ WSOCKET sock,FS_UINT dwUserData ) PURE;

		//加入多播组
		STDMETHOD_( WNETRESULT,UDP_JoinGroup)( THIS_ WSOCKET sock,FS_UINT32 dwGroupIP ) PURE;
		
		//离开多播组
		STDMETHOD_( WNETRESULT,UDP_LeaveGroup)( THIS_ WSOCKET sock,FS_UINT32 dwGroupIP ) PURE;
		
		//发送数据
		STDMETHOD_( WNETRESULT,UDP_Send)( THIS_ WSOCKET sock,char *pData,FS_INT32 nDataLen,FS_UINT32 dwDestIP,FS_UINT16 wDestPort ) PURE;
		
		//获取事件
		STDMETHOD_( WNET_EVENT*,UDP_PopupMsg)( THIS_ WSOCKET sock,FS_UINT32 dwWaitTime ) PURE;
		
		//释放事件
		STDMETHOD_( WNETRESULT,UDP_FreeMsg)( THIS_ WSOCKET sock,WNET_EVENT *pEvent ) PURE;
		
		//设置参数
		STDMETHOD_( WNETRESULT,UDP_SetParam)( THIS_ WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize ) PURE;
		
		//获取参数
		STDMETHOD_( WNETRESULT,UDP_GetParam)( THIS_ WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize ) PURE;
		
		//关闭SOCK
		STDMETHOD_( WNETRESULT,UDP_Close)( THIS_ WSOCKET sock ) PURE;
		
		//PING
		STDMETHOD_( WNETRESULT,Ping)( THIS_ FS_UINT32 dwDestIP,WBASE_NOTIFY *pMode ) PURE;
		
		//获取PING结果
		STDMETHOD_( WNETRESULT,GetPingResult)( THIS_ FS_UINT32 dwDestIP,FS_UINT32* pdwMin,FS_UINT32* pdwMax,FS_UINT32* pdwAvg ) PURE;
	
		STDMETHOD_( WNETRESULT,RemovePing )( THIS_ FS_UINT32 dwDestIP,WBASE_NOTIFY *pMode) PURE;

		STDMETHOD_( WNET_EVENT*,TCP_AllocMsg)( THIS_ ) PURE;

		STDMETHOD_( WNET_EVENT*,UDP_AllocMsg)( THIS_ ) PURE;

		//获取代理
		STDMETHOD_(WNETRESULT,GetProxy)( THIS_ WNET_PROXY *pProxy ) PURE;
	};

	
#define WLOGMODE_TODEBUG			1
#define WLOGMODE_TOFILE				2
#define WLOGMODE_TOCONSOLE			4

	//IWLog
	// {EC7A7194-3073-4c0b-B57E-DBB4852E2D67}
	DEFINE_GUID( IID_IWLog, 
		0xec7a7194, 0x3073, 0x4c0b, 0xb5, 0x7e, 0xdb, 0xb4, 0x85, 0x2e, 0x2d, 0x67);
	
	//----------------------------------------------------------------------------
	// IWLog
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IWLog, IUnknown)
	{
		STDMETHOD (SetLevel)( THIS_ FS_INT32 nLevel ) PURE;
		STDMETHOD (SetMode)( THIS_ FS_INT32 nMode ) PURE;
		STDMETHOD_(FS_INT32,GetLevel)( THIS_ ) PURE;
		STDMETHOD_(FS_INT32,GetMode)( THIS_ ) PURE;
		STDMETHOD_( const WCHAR*,GetName)( THIS_ ) PURE;
		STDMETHOD (PrintW)( FS_INT32 nLevel,const WCHAR* wszFormat,... ) PURE;
		STDMETHOD (PrintA)( FS_INT32 nLevel,const CHAR* szFormat,... ) PURE;
		STDMETHOD (PrintW2)( FS_INT32 nLevel,const WCHAR* wszFormat,va_list ap ) PURE;
		STDMETHOD (PrintA2)( FS_INT32 nLevel,const CHAR* szFormat,va_list ap ) PURE;
		STDMETHOD (RealPrintW)( const WCHAR* wszFormat,... ) PURE;
		STDMETHOD (RealPrintA)( const CHAR* szFormat,... ) PURE;
		STDMETHOD (RealPrintW2)( const WCHAR* wszFormat,va_list ap ) PURE;
		STDMETHOD (RealPrintA2)( const CHAR* szFormat,va_list ap ) PURE;
	};

	// IWLogAllocator's GUID
	// {19B9932D-1068-4add-A642-0B95EBF338A9}
	DEFINE_GUID( IID_IWLogAllocator, 
		0x19b9932d, 0x1068, 0x4add, 0xa6, 0x42, 0xb, 0x95, 0xeb, 0xf3, 0x38, 0xa9);	

#define FILESAVE_MODE_
	//----------------------------------------------------------------------------
	// IWLogAllocator
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IWLogAllocator, IUnknown)
	{
		STDMETHOD (Alloc)( THIS_ const WCHAR* wszName,FS_INT32 nLevel,FS_INT32 nMode,IWLog** pLog ) PURE;
		STDMETHOD (Alloc2)( THIS_ const WCHAR* wszName,FS_INT32 nLevel,FS_INT32 nMode,BOOL bEncrypt,IWLog** pLog ) PURE;
		STDMETHOD (SetLogSaveDays)( THIS_ FS_INT32 nDays ) PURE;
#ifdef _FS_OS_WIN
		STDMETHOD (SetLogLevelByName)(THIS_ const WCHAR* wszName,FS_INT32 nLevel) PURE;
#endif
	};


    // ILogCenter's GUID
    // {E67F5F27-CB02-D0B6-62E2-500AB0C5B0D6}
    DEFINE_GUID(IID_ILogCenter,
        0xE67F5F27, 0xCB02, 0xD0B6, 0x62, 0xE2, 0x50, 0x0A, 0xB0, 0xC5, 0xB0, 0xD6);

#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
    // 配置文件中日志配置发生变化时的回调函数
    struct LogCfg
    {
        FS_INT nLoggerID;
        LogLevel nLogLevel;
    };
    typedef void(CALLBACK* LogLevelCfgChange)(LogCfg logCfg);

    DECLARE_INTERFACE_(ILogCenter, IUnknown)
    {
        STDMETHOD_(ILogMgr*, GetLogMgr)(THIS_) PURE;
        STDMETHOD_(FS_INT, RegisterLogger)(THIS_ const FS_CHAR* szLogName, FS_INT32 nMode, 
            LogLevel nInitLevel, LogLevelCfgChange callback) PURE;
        STDMETHOD(UnregisterLogger)(THIS_ FS_INT nLoggerID) PURE;
    };
#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX

	// IIPConfig's GUID
	// {BD2ADAB4-34E7-4ebb-B4EA-5AD2CF4129AA}
	DEFINE_GUID( IID_IIPConfig, 
		0xbd2adab4, 0x34e7, 0x4ebb, 0xb4, 0xea, 0x5a, 0xd2, 0xcf, 0x41, 0x29, 0xaa);

#define  SETIPMODE_ADD		1
#define  SETIPMODE_DEL		2
#define  SETIPMODE_RESET	3
	//----------------------------------------------------------------------------
	// IIPConfig
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IIPConfig, IUnknown)
	{
		//
		//配置本地IP地址列表,系统初始默认取本地网卡的地址列表
		//szIPList:		IP地址列表,地址间以分号分隔,例如:192.168.0.106;192.168.0.3;
		//nMode:		1	增加地址列表
		//				2	删除地址列表
		//				3   重置地址列表,用szIPList替代现有的地址列表信息
		//
		STDMETHOD ( SetIPList )( THIS_ const CHAR* szIPList,FS_INT32 nMode ) PURE;
		
		//
		//获取本地IP地址列表
		//
		STDMETHOD ( GetIPList )( THIS_ CHAR* szIPList,FS_UINT32 dwSize ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif