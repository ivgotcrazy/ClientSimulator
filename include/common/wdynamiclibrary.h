// WDynamicLibrary.h: interface for the WDynamicLibrary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDYNAMICLIBRARY_H__1DA9EF26_C9E9_443E_8E6A_A2C8A41E0188__INCLUDED_)
#define AFX_WDYNAMICLIBRARY_H__1DA9EF26_C9E9_443E_8E6A_A2C8A41E0188__INCLUDED_

#include "wbasetype.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace WBASELIB
{

class WDynamicLibrary
{
public:
    WDynamicLibrary();
    virtual ~WDynamicLibrary();
public:
    void*	GetFunction(const CHAR* szFuncName);
    void	FreeLibrary();
    BOOL	LoadLibrary(TCHAR* szPathName);
public:
    HMODULE		m_hModule;
};

}
#endif // !defined(AFX_WDYNAMICLIBRARY_H__1DA9EF26_C9E9_443E_8E6A_A2C8A41E0188__INCLUDED_)
