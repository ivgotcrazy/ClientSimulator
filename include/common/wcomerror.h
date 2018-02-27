#ifndef __WCOM_ERROR_H
#define __WCOM_ERROR_H

#include "wbasetype.h"

#ifndef _FS_OS_WIN

#define _HRESULT_TYPEDEF_(_sc) 	((HRESULT)_sc )

#define NOERROR			0
#define S_OK			((HRESULT)0x00000000L)
#define S_FALSE			((HRESULT)0x00000001L)

#define	E_UNEXPECTED		_HRESULT_TYPEDEF_( 0x8000FFFFL )
#define E_NOTIMPL		_HRESULT_TYPEDEF_( 0x80004001L )
#define E_OUTOFMEMORY		_HRESULT_TYPEDEF_( 0x8007000EL )
#define E_INVALIDARG		_HRESULT_TYPEDEF_( 0x80070057L )
#define E_NOINTERFACE		_HRESULT_TYPEDEF_( 0x80004002L )
#define E_POINTER		_HRESULT_TYPEDEF_( 0x80004003L )
#define E_HANDLE		_HRESULT_TYPEDEF_( 0x80070006L )
#define E_ABORT			_HRESULT_TYPEDEF_( ox80004004L )
#define E_FAIL			_HRESULT_TYPEDEF_( 0x80004005L )
#define E_ACCESSDENIED		_HRESULT_TYPEDEF_( 0x80070005L )
#define E_PENDING		_HRESULT_TYPEDEF_( 0x8000000AL )

#define SEVERITY_SUCCESS	0
#define SEVERITY_ERROR		1

#define SUCCEEDED(Status)	((HRESULT)(Status) >= 0 )
#define FAILED(Status)		((HRESULT)(Status) < 0 )

#define FACILITY_WIN32		7

#define MAKE_HRESULT( sev,fac,code ) \
	((HRESULT) (((FS_UINT32)(sev)<<31) | ((FS_UINT32)(fac)<<16) | ((FS_UINT32 )(code))))

#define GetLastError()		errno
#endif

#endif
