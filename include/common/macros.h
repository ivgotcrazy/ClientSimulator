//*****************************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// FileName:            Macros.h
//
// Abstract:            Contains macros used to perform operations safely on
//                      pointers or handles
//
//*****************************************************************************

#ifndef _MACROS_H_
#define _MACROS_H_

namespace WBASELIB
{

#ifndef SAFE_RELEASE
#define SAFE_RELEASE( x )   \
    if ( x )                \
        {                       \
	(x)->Release();       \
	(x) = NULL;           \
    }
#endif

#ifndef SAFE_ADDREF
#define SAFE_ADDREF( x )    \
    if ( x )                \
        {                       \
	(x)->AddRef();        \
    }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE( x )    \
    if ( x )                \
        {                       \
	delete x;           \
	x = NULL;           \
    }
#endif

#ifndef SAFE_ARRAYDELETE
#define SAFE_ARRAYDELETE( x )   \
    if ( x )                    \
        {                           \
	delete[] x;             \
	x = NULL;               \
    }
#endif

#ifdef _FS_OS_WIN	

#ifndef SAFE_SYSFREESTRING
#define SAFE_SYSFREESTRING( x ) \
    if ( x )                    \
        {                           \
	SysFreeString( x );     \
	x = NULL;               \
    }
#endif

#ifndef SAFE_CLOSEHANDLE
#define SAFE_CLOSEHANDLE( x )               \
    if ( x && INVALID_HANDLE_VALUE != x )   \
        {                                       \
	CloseHandle( x );                   \
	x = INVALID_HANDLE_VALUE;                           \
    }
#endif

#endif

#ifndef _countof
#define _countof(a) (sizeof(a)/sizeof(a[0]))
#endif

#ifndef OUT
#define OUT
#endif 

#ifndef IN
#define IN
#endif


}

#endif // _MACROS_H_
