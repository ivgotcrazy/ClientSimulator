#ifndef __WCHARFUNCTION_H__
#define __WCHARFUNCTION_H__

#ifndef _FS_OS_WIN
#ifndef _FS_OS_ANDROID
#include <iconv.h>
#endif
#include <errno.h>
#endif

#include "wbasetype.h"
#include <string.h>
#include <wchar.h>
#include <ctype.h>

namespace WBASELIB
{

extern FS_INT32		StringFromGUID2(REFGUID rguid, CHAR *szGuid, FS_INT32 ccMax);

#ifndef _FS_OS_WIN

extern FS_INT32  StringConvert( const char* szFromCharset,const char* szToCharset,char *szIn,FS_INT32 nInLen,char* szOut,FS_INT32 nOutLen );

extern char* _strupr( char *string);
extern char* _strlwr( char *string);
extern WCHAR* _wcsupr( WCHAR *string);
extern WCHAR* _wcslwr( WCHAR *string);

#define strupr		_strupr
#define strlwr		_strlwr

#define wcsupr		_wcsupr
#define wcslwr		_wcslwr

#define _strnicmp	strncasecmp
#define _stricmp	strcasecmp

#define _snwprintf	swprintf

#ifdef _FS_OS_ANDROID
#define wcsicmp		wcscmp
#define stricmp		strcasecmp
#else
#define wcsicmp		wcscasecmp
#endif

extern FS_INT32		StringFromGUID2( REFGUID rguid,WCHAR *wszGuid,FS_INT32 ccMax );
extern HRESULT	GUIDFromString( WCHAR *wszGuid,GUID* lpGuid );

#define CLSIDFromString 	GUIDFromString
#define StringFromCLSID2	StringFromGUID2

#else

#define snprintf	_snprintf

#endif

extern HRESULT	GUIDFromString(const CHAR *szGuid, GUID* lpGuid);

extern char*  strreplace(char* string, char srch, char tgch);
extern WCHAR* wcsreplace(WCHAR* string, WCHAR srch, WCHAR tgch);

extern FS_INT32 ConvertUtf8ToUnicode(const CHAR * szIn, WCHAR *wszOut, FS_INT32 nSize);

extern  FS_INT32 ConvertUnicodeToUtf8(const WCHAR * wszIn, CHAR *szOut, FS_INT32 nSize);

extern FS_INT32 ConvertUtf8ToAnsi(const CHAR * szIn, CHAR *szOut, FS_INT32 nSize);

extern FS_INT32 ConvertAnsiToUtf8(const CHAR * szIn, CHAR *szOut, FS_INT32 nSize);

extern FS_INT32 ConvertAnsiToUnicode(const CHAR * szIn, WCHAR *wszOut, FS_INT32 nSize);

extern  FS_INT32 ConvertUnicodeToAnsi(const WCHAR * wszIn, CHAR *szOut, FS_INT32 nSize);

extern FS_INT32 ConvertAnsiToUnicode16(const CHAR * szIn, CHARU16 *szOut, FS_INT32 nSize);

extern  FS_INT32 ConvertUnicode16ToAnsi(const CHARU16 * szIn, CHAR *szOut, FS_INT32 nSize);

extern FS_INT32 ConvertUtf8ToUnicode16(const CHAR * szIn, CHARU16 *szOut, FS_INT32 nSize);

extern  FS_INT32 ConvertUnicode16ToUtf8(const CHARU16 * szIn, CHAR *szOut, FS_INT32 nSize);

#ifdef _FS_OS_WIN

extern void OutPutDebugStringEx(const TCHAR * format, ...);

#else
extern FS_INT32 ConvertUnicodeToUnicode16(const WCHAR * wszIn,CHARU16 *szOut,FS_INT32 nSize );

extern  FS_INT32 ConvertUnicode16ToUnicode(const CHARU16 * szIn,WCHAR *wszOut,FS_INT32 nSize );
#endif

extern  FS_INT32 u16strlen(const FS_UINT16 * string);
extern FS_INT32 utf8strlen(char *str);
}

#endif
