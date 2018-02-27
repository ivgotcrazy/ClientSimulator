#ifndef __INC_TIMER_THREAD_H__
#define __INC_TIMER_THREAD_H__

#include "wbaseobject.h"
#include "wbasetype.h"
#include "map"
#include "wthread.h"
#include "wlog.h"
#include "wlock.h"
#include "wsemaphore.h"
#include "wtimefunction.h"
#include "wmsgqueue.h"
#include "wbaseobject.h"

namespace WBASELIB
{

#define		WTIMER_RESULT_SUCCESS		0X00000000
#define		WTIMER_RESULT_REMOVETIMER	0X00000001

typedef LRESULT(*WTIMERCALLBACK)(FS_UINT32 uTimerID, FS_UINT dwUserData);

class NOVTABLE ITimer
{
public:
    virtual ~ITimer() {};

    virtual  LRESULT	OnTimer(FS_UINT32 uTimerID) = 0;
};

class NOVTABLE ITimerManager
{
public:
    virtual ~ITimerManager() {};

    virtual BOOL    StartTimer(BOOL bHighRes = TRUE) = 0;
    virtual VOID	StopTimer() = 0;

    virtual FS_UINT32	AddTimer(ITimer*pTimer, FS_UINT32 uDelay) = 0;
    virtual FS_UINT32	AddTimer(WTIMERCALLBACK pCallback, FS_UINT dwUserData, FS_UINT32 uDelay) = 0;
    virtual VOID	RemoveTimer(FS_UINT32 uTimerID) = 0;
};

class WTimerManager :public WThread, public ITimerManager
{
public:
    //Constructor and Destructor
    WTimerManager(FS_UINT32 nMinRes = 10, FS_UINT32 nMaxRes = 10000, WLog *pLog = NULL);
    virtual ~WTimerManager();

public:

    virtual VOID RemoveTimer(FS_UINT32 uTimerID);
    virtual FS_UINT32 AddTimer(ITimer*pTimer, FS_UINT32 uDelay);
    virtual FS_UINT32 AddTimer(WTIMERCALLBACK pCallback, FS_UINT dwUserData, FS_UINT32 uDelay);

    //public interface
    virtual BOOL    StartTimer(BOOL bHighRes = TRUE);
    virtual VOID	StopTimer();

protected:
    struct TimerNode
    {

        TimerNode() :uTimerID(0) {};

        volatile FS_INT32		lValid;
        FS_UINT32				uTimerID;
        FS_UINT32				uDelay;
        FS_UINT32				nIndex;
        FS_UINT32				dwLastTime;
        ITimer*				pTimer;

        WTIMERCALLBACK		pCallback;
        FS_UINT				dwUserData;

        TimerNode*	pNext;
        TimerNode*  pPrev;
    };
    struct	TimerList
    {

        FS_UINT32		nRes;
        FS_UINT32		nHalfRes;
        TimerNode*	pHead;
        FS_UINT32		dwCount;
        WLock		lock;
    };
    struct TimerMsg
    {

        FS_UINT32		nMsgID;
        FS_UINT32		dwParam1;
        FS_UINT32		dwParam2;
    };

    typedef std::map<FS_UINT32, TimerNode*>			TimerNodeMap;
    typedef WElementAllocator<TimerNode>		TimerNodeAllocator;
    typedef WElementAllocator<TimerMsg>		TimerMsgAllocator;

    VOID		InternalAddTimer(TimerNode *pNode);
    VOID		InternalRemoveTimer(FS_UINT32 uTimerID);
    FS_UINT32		ThreadProcEx();
    TimerNode*	GetFreeTimerNode()
    {
        TimerNode *pNode = m_Allocator.Alloc();
        if (pNode && pNode->uTimerID == 0)
        {
            pNode->uTimerID = m_nTimerIDBase++;
        };
        return pNode;
    }

    void		OnTimeProc(FS_UINT32 uID);
    void		ProcessTimerEvent(FS_UINT32 dwIndex);
    BOOL		PushMsg(FS_UINT32 nMsgID, FS_UINT32 dwParam1 = 0, FS_UINT32 dwParam2 = 0);
#ifdef _FS_OS_WIN
    static void CALLBACK TimeProc(FS_UINT32 uID, FS_UINT32 uMsg, FS_UINT dwUser, FS_UINT32 dw1, FS_UINT32 dw2);
#endif
private:
    TimerNodeAllocator	m_Allocator;
    TimerMsgAllocator	m_msgAllocator;
    WMsgQueue<TimerMsg>	m_msgQueue;

    TimerList*			m_lsTimer;
    FS_UINT32			m_nListCount;
    FS_UINT32			m_nTimerIDBase;

    WLock				m_mapLock;
    TimerNodeMap		m_mapTimer;
    volatile FS_INT32	m_lOnTimer;

    BOOL				m_bHighRes;
    BOOL				m_bStarted;
    FS_UINT32			m_nMinRes;
    FS_UINT32			m_nMaxRes;
    FS_UINT32			m_nTimerID;
    FS_UINT32			m_nTimerRes;

    BOOL				m_bStop;
    WLog*				m_pLog;
};

}

#endif //__INC_TIMER_THREAD_H__
