#ifndef __WTIME_FUNCTION_H
#define __WTIME_FUNCTION_H

#ifndef _FS_OS_WIN
#include <sys/time.h>
#include <unistd.h>
#else
#include <mmsystem.h>
#endif

#include "wbasetype.h"
#include <time.h>

namespace WBASELIB
{

#ifdef _FS_OS_WIN

extern time_t  String2Time(const CHAR* szTime);

extern BOOL  String2SysTime(const CHAR* szTime, SYSTEMTIME &tmSys);

extern void  String2FileTime(const CHAR* szTime, FILETIME &tmFile);

#else

extern FS_UINT32 GetTickCount();

extern FS_UINT32 timeGetTime();

extern void	 Sleep(FS_UINT32 dwMillSecond);

#define _tctime	ctime

#endif

}

#endif
