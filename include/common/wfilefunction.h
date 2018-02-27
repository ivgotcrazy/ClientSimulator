#ifndef __WBASELIB_WFILEFUNCTION_H
#define __WBASELIB_WFILEFUNCTION_H

#include <stdlib.h>
#include "wbasetype.h"
#include "wunicode.h"

#ifndef _FS_OS_WIN
#include <limits.h>
#include <wchar.h>
#endif

namespace WBASELIB
{

#ifdef _FS_OS_WIN
#define		DIRSPLITERA	'\\'
#define		DIRSPLITERW	(WCHAR)'\\'
#define		DIRSPLITERSA	"\\"
#define		DIRSPLITERSW	L"\\"
#else
#define		DIRSPLITERA	'/'
#define 	DIRSPLITERW	(WCHAR)'/'
#define		DIRSPLITERSA	"/"
#define		DIRSPLITERSW	L"/"
#endif

#ifndef _FS_OS_WIN

#ifndef ERROR_ALREADY_EXISTS
#define ERROR_ALREADY_EXISTS    EEXIST
#endif

#endif

#ifdef _UNICODE
#define		DIRSPLITER	DIRSPLITERW
#define		DIRSPLITERS	DIRSPLITERSW
#else
#define		DIRSPLITER	DIRSPLITERA
#define		DIRSPLITERS	DIRSPLITERSA
#endif

#ifdef _FS_OS_ANDROID
extern CHAR	  g_szModulePath[256];
#endif

extern BOOL	  GetModuleName(HMODULE hModule, LPTSTR szName, FS_UINT32 dwSize, LPCTSTR lpszDefName);

extern TCHAR* GetModulePath(HMODULE hModule = NULL);

extern BOOL WCreateDirectoryEx(LPCTSTR lpszFilePath);

extern BOOL WRemoveDirectoryEx(LPCTSTR  lpszFilePath);

#ifdef _FS_OS_WIN

extern BOOL DeleteFileEx(LPCTSTR  lpszFilePath, FS_UINT32 nDayBefore);

//	szFilePath - 模块全路径
//	szInfo -   需要获取的信息
//		"ProductName",
//		"ProductVersion",
//		"FileDescription",
//		"LegalCopyright",
//		"FileVersion",
//		"CompanyName",
//		"LegalTradeMarks",
//		"InternalName",
//		"OriginalFileName"
extern TCHAR* GetProductInfo(const TCHAR* szFilePath, TCHAR* szInfo);

extern BOOL FindUDisk(TCHAR *szUPath);

#define IsFileExist(szFilePath)  (GetFileAttributesA(szFilePath) != -1)

#else

#define IsFileExist(szFilePath)  (access(szFilePath, 0) != -1)

#endif

}

#endif