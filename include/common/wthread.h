// Thread.h

#ifndef	__THREAD_H__
#define __THREAD_H__

#include "wbasetype.h"
#ifndef _FS_OS_WIN
#include <pthread.h>
#include <errno.h>
#include "wbaseobject.h"
#include "wmsgqueue.h"

#endif

namespace WBASELIB
{

#define PRIORITY_HIGHEST_OUR	THREAD_PRIORITY_HIGHEST
#define PRIORITY_HIGH_OUR		THREAD_PRIORITY_ABOVE_NORMAL
#define PRIORITY_NORMAL_OUR		THREAD_PRIORITY_NORMAL
#define PRIORITY_LOW_OUR		THREAD_PRIORITY_BELOW_NORMAL
#define PRIORITY_LOWEST_OUR		THREAD_PRIORITY_LOWEST

#ifndef _FS_OS_WIN
#define PM_REMOVE               1
#endif

class WLog;

class  WThread
{

public:
    WThread();
    virtual ~WThread();

public:

    virtual BOOL	StartThread(BOOL bWaitCreated = TRUE, void* pThreadContext = NULL);

    virtual void	SetAutoDelete(BOOL bAutoDelete) { m_bAutoDelete = bAutoDelete; };

    virtual FS_UINT32	Suspend(void);

    virtual FS_UINT32	Resume(void);

    virtual BOOL	SetPriority(FS_INT32 nPriority);

    virtual BOOL	GetExitCode(FS_UINT32 *pdwExitCode);

    virtual	void	StopThread(void);

    virtual FS_UINT32	ThreadProcEx() { return 0; };

#ifdef _FS_OS_WIN

    virtual FS_UINT32   GetThreadID();

    typedef MSG Thread_MSG;

#else

    virtual FS_UINT		GetThreadID();

    typedef WBASE_MSG Thread_MSG;
    typedef WMsgQueue<Thread_MSG>            ThreadMsgQueue;
    typedef WElementAllocator<Thread_MSG>    ThreadMsgAllocator;

    static BOOL CALLBACK ThreadMsgCallback(FS_UINT32 nMsgID, WPARAM wParam, LPARAM lParam, FS_UINT32 dwReserved, FS_UINT dwUserData);

    void ClearMsgQueue();

    BOOL PeekMessage(
        Thread_MSG * lpMsg,
        HWND hWnd,
        FS_UINT32 wMsgFilterMin,
        FS_UINT32 wMsgFilterMax,
        UINT wRemoveMsg);

#endif

    enum
    {
        WAIT_THREAD_EXIT,
        WAIT_THREAD_MSG,
        WAIT_THREAD_TIMEOUT
    };
    void        GetThreadMsgNotify(WBASE_NOTIFY& notify, FS_UINT32 nMsgID);

    FS_UINT32   WaitForThreadMsg(FS_UINT32 dwMilliSeconds, Thread_MSG *pMsg);

    FS_UINT32   WaitForThreadExit(FS_UINT32 dwMilliSeconds);

    static BOOL PostThreadMessage(WThread *pThread, FS_UINT32 nMsgID, WPARAM wParam, LPARAM lParam);


    virtual	BOOL	IsStarted();
public:
    BOOL                m_bAutoDelete;
    FS_UINT32           m_dwExitCode;
    BOOL                m_bStop;
#ifdef _FS_OS_WIN
    WTHREADID           m_unThreadID;
    HANDLE              m_hThread;
    HANDLE              m_evCreated;
    HANDLE              m_evStop;
#else
    pthread_t	        m_thrd;
    ThreadMsgQueue      m_ThreadMsgQueue;
    ThreadMsgAllocator  m_ThreadMsgAllocator;
#endif		
};
}

#endif
