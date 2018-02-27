// WLock.h: interface for the WLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WLOCK_H__215ADB87_70CF_4950_B1FB_04855FB7981B__INCLUDED_)
#define AFX_WLOCK_H__215ADB87_70CF_4950_B1FB_04855FB7981B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wbasetype.h"

#ifndef _FS_OS_WIN
#include <pthread.h>
#include <errno.h>
#endif

namespace WBASELIB
{

class WLock
{
public:
    WLock();
    virtual ~WLock();
public:
    VOID UnLock();
    VOID Lock();
    BOOL TryLock();
private:
#ifdef _FS_OS_WIN
    mutable CRITICAL_SECTION	m_Lock;
#else
    pthread_mutexattr_t         m_attr;
    mutable pthread_mutex_t		m_Lock;
#endif
};

class WAutoLock
{
public:
    WAutoLock(WLock* pLock);
    virtual ~WAutoLock();

private:
    WLock*  m_pLock;
};
}
#endif // !defined(AFX_WLOCK_H__215ADB87_70CF_4950_B1FB_04855FB7981B__INCLUDED_)
