#ifndef __WUNICODE_H
#define __WUNICODE_H

#include "wbasetype.h"
#include "wcharfunction.h"

using namespace WBASELIB;

#if !defined(_FS_OS_WIN)

#if defined _UNICODE || defined UNICODE

typedef WCHAR		TCHAR;

#define	_tcslen		wcslen
#define	_tcscat		wcscat
#define _tcsncat	wcsncat
#define	_tcscpy		wcscpy
#define _tcsncpy	wcsncpy
#define _tcsstr		wcsstr
#define _tcschr		wcschr
#define _tcsrchr	wcsrchr
#define _vsntprintf	vswprintf
#define _tprintf	wprintf
#define _stprintf	swprintf
#define _tcscmp		wcscmp

#define __T(x)		L ## x

#else

typedef CHAR		TCHAR;

#define _tcslen		strlen
#define _tcscat		strcat
#define _tcsncat    strncat
#define _tcscpy		strcpy
#define _tcsncpy	strncpy
#define _tcsstr		strstr
#define _tcschr		strchr
#define _tcsrchr	strrchr
#define _vsntprintf	vsnprintf
#define _tprintf	printf
#define _stprintf	sprintf
#define _tcscmp		strcmp

#define __T(x)		x

#endif

typedef const TCHAR*	LPCTSTR;
typedef TCHAR*		LPTSTR;

#define _T(x)		__T(x)
#define _TEXT(x)	__T(x)

#endif

#endif
