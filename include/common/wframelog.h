#ifndef __WFRAME_LOG_H
#define __WFRAME_LOG_H
#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
#include "log.h"

using namespace FsMeeting;

interface		IComponentFactory;

extern ILogMgr*     g_fs_log_mgr;
extern FS_INT       g_fs_logger_id;
extern LogLevel     g_fs_log_level;

#ifndef FS_LOG_MGR
#define FS_LOG_MGR g_fs_log_mgr
#endif // !FS_LOG_MGR

#ifndef FS_LOGGER_ID
#define FS_LOGGER_ID g_fs_logger_id
#endif // !FS_LOGGER_ID

#ifndef FS_LOG_LEVEL
#define FS_LOG_LEVEL g_fs_log_level
#endif // !FS_LOG_LEVEL

#define FSLOG(...)   FS_LOG_TRACE(__VA_ARGS__)


STDAPI			FWInitFSLogger(IComponentFactory *pFactory, const FS_CHAR* szLogName, FS_INT32 nMode);
STDAPI			FWReleaseFSLogger();
STDAPI			FWInitFSLoggerEx(IComponentFactory *pFactory, const FS_CHAR* szLogName, FS_INT32 nMode,
    LogLevel nInitLogLevel, ILogMgr *& pLogMgr, FS_INT & nLoggerID);
STDAPI			FWReleaseFSLoggerEx(FS_INT nLoggerID);

#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX

interface		IWLog;
interface		IComponentFactory;
extern IWLog*	g_pFrameLog;

#define			FWLOGW			if( g_pFrameLog ) g_pFrameLog->RealPrintW
#define			FWLOGA			if( g_pFrameLog ) g_pFrameLog->RealPrintA
#define			FWLOGW2			if( g_pFrameLog ) g_pFrameLog->RealPrintW2
#define			FWLOGA2			if( g_pFrameLog ) g_pFrameLog->RealPrintA2

#define			FWLEVELLOGW		if( g_pFrameLog ) g_pFrameLog->PrintW
#define			FWLEVELLOGA		if( g_pFrameLog ) g_pFrameLog->PrintA


#ifdef _UNICODE
#define			FWLOG			FWLOGW
#define			FWLOG2			FWLOGW2

#define			FWLEVELLOG			FWLEVELLOGW
#else
#define			FWLOG			FWLOGA
#define			FWLOG2			FWLOGA2
#endif

STDAPI			FWInitLogger(IComponentFactory *pFactory, const WCHAR* wszLogName, FS_INT32 nLevel, FS_INT32 nMode);
STDAPI			FWInitLogger2(IComponentFactory *pFactory, const WCHAR* wszLogName, FS_INT32 nLevel, FS_INT32 nMode, BOOL bEncrypt);
STDAPI			FWReleaseLogger();

STDAPI			FWInitExLogger(IComponentFactory *pFactory, const WCHAR* wszLogName, FS_INT32 nLevel, FS_INT32 nMode, IWLog** pFrameLog);
STDAPI			FWInitExLogger2(IComponentFactory *pFactory, const WCHAR* wszLogName, FS_INT32 nLevel, FS_INT32 nMode, BOOL bEncrypt, IWLog** pFrameLog);
STDAPI			FWReleaseExLogger(IWLog* pFrameLog);


#endif
