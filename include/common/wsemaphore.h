#ifndef __WSEMAPHORE_H 
#define __WSEMAPHORE_H

#ifdef _FS_OS_WIN

#else

#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif

#ifndef __USE_POSIX199309
#define __USE_POSIX199309
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>

#endif

#include "wbasetype.h"

namespace WBASELIB
{

class WSemaphore
{
public:
    WSemaphore(FS_INT32 nInitialCount, FS_INT32 nMaxCount);
    virtual ~WSemaphore();
public:
    FS_UINT32 	WaitSemaphore(FS_UINT32 dwWaitTime);
    BOOL 	ReleaseSemaphore(FS_INT32 lCount);
#ifdef _FS_OS_WIN
    HANDLE	GetHandle() { return m_hSemaphore; };
#endif
private:
#ifdef _FS_OS_WIN
    HANDLE	m_hSemaphore;
#else
#if defined _FS_OS_IOS || defined _FS_OS_MAC
    volatile FS_INT32    m_nCount;
    FS_INT32             m_nMax;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
    //        char    m_szName[32];
    FS_INT32             Lock();
    void            UnLock();
#else
    sem_t* 	m_sem;
#endif
#endif
};

}
#endif
