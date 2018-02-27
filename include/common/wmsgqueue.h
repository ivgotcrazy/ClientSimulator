// WMsgQueue.h: interface for the WMsgQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WMSGQUEUE_H__25DFC653_6CF3_439C_8D86_3E42800C1CB6__INCLUDED_)
#define AFX_WMSGQUEUE_H__25DFC653_6CF3_439C_8D86_3E42800C1CB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <assert.h>
#include "wlock.h"
#include "wbasetype.h"
#include "wsemaphore.h"
#include "wbaseobject.h"

namespace WBASELIB
{

template <class T>
class WMsgQueue
{
public:
    WMsgQueue(FS_UINT32 dwMaxMsgCount = 1000) :
        m_bStop(FALSE),
        m_dwMaxMsgCount(dwMaxMsgCount),
        m_dwUserData(0),
        m_dwFlag(0),
        m_dwMsgCount(0),
        m_nHead(0),
        m_nTail(0),
        m_sem(0, dwMaxMsgCount),
        m_pAllocator(NULL)
    {
        m_pMsg = new T*[dwMaxMsgCount + 1];
#ifdef _FS_OS_WIN
        m_evStop = CreateEvent(NULL, TRUE, FALSE, NULL);
#endif
    };
    virtual ~WMsgQueue()
    {
        SetStop();

        m_Lock.Lock();
        delete[] m_pMsg;
        m_dwMsgCount = 0;
        m_nHead = m_nTail = 0;
        m_Lock.UnLock();
#ifdef _FS_OS_WIN
        CloseHandle(m_evStop);
#endif
    };
    typedef WElementAllocator<T>	Alloctor;
public:
    BOOL	PushMsg(T *pMsg, FS_UINT32 *pdwMsgCount = NULL)
    {
#ifdef _FS_OS_WIN
        if (WaitForSingleObject(m_evStop, 0) == WAIT_OBJECT_0)
            return FALSE;
#else
        if (m_bStop)
            return FALSE;
#endif
        m_Lock.Lock();

        assert(m_dwMsgCount < m_dwMaxMsgCount);
        if (m_dwMsgCount >= m_dwMaxMsgCount)
        {
            m_Lock.UnLock();
            return FALSE;
        }
        m_pMsg[m_nTail++] = pMsg;
        m_nTail = (FS_UINT32)m_nTail > m_dwMaxMsgCount ? 0 : m_nTail;
        ++m_dwMsgCount;
        if (pdwMsgCount)
            *pdwMsgCount = m_dwMsgCount;

        m_Lock.UnLock();

        m_sem.ReleaseSemaphore(1);

        return TRUE;
    }
    T*	PopMsg(FS_UINT32 dwWaitTime = INFINITE, FS_UINT32 *pdwMsgCount = NULL)
    {
        FS_UINT32 dwRet = 0;
#ifdef _FS_OS_WIN
        HANDLE pHandle[] = { m_sem.GetHandle(), m_evStop };
        dwRet = WaitForMultipleObjects(2, pHandle, FALSE, dwWaitTime);
#else
        if (m_bStop)
            return NULL;
        dwRet = m_sem.WaitSemaphore(dwWaitTime);
#endif
        if (dwRet != WAIT_OBJECT_0 || m_bStop)
            return NULL;
        m_Lock.Lock();

        T* pMsg = m_pMsg[m_nHead++];
        m_nHead = (FS_UINT32)m_nHead > m_dwMaxMsgCount ? 0 : m_nHead;
        --m_dwMsgCount;
        if (pdwMsgCount)
            *pdwMsgCount = m_dwMsgCount;

        m_Lock.UnLock();

        return pMsg;
    };
    VOID	SetStop()
    {
#ifdef _FS_OS_WIN
        SetEvent(m_evStop);
#endif
        m_bStop = TRUE;
    };
    VOID	ResetStop()
    {
#ifdef _FS_OS_WIN
        ResetEvent(m_evStop);
#endif
        m_bStop = FALSE;
    };
    FS_UINT32	GetMsgCount() { return m_dwMsgCount; };
    FS_UINT32	GetMaxMsgCount() { return m_dwMaxMsgCount; };
    VOID		SetMaxMsgCount(FS_UINT32 dwMaxMsgCount) { m_dwMaxMsgCount = dwMaxMsgCount; };
    BOOL		IsFull() { return m_dwMsgCount >= m_dwMaxMsgCount; };
    VOID		SetFlag(FS_UINT32 dwFlag) { m_dwFlag = dwFlag; };
    FS_UINT32	GetFlag() { return m_dwFlag; };
    VOID		SetUserData(FS_UINT dwUserData) { m_dwUserData = dwUserData; };
    FS_UINT		GetUserData() { return m_dwUserData; };
    T*			Alloc() { return m_pAllocator ? m_pAllocator->Alloc() : NULL; };
    void		Free(T* pMsg) { if (m_pAllocator) m_pAllocator->Free(pMsg); }
    void		SetAllocator(WElementAllocator<T> *pAllocator) { m_pAllocator = pAllocator; };

protected:
    BOOL	m_bStop;
#ifdef _FS_OS_WIN
    HANDLE	m_evStop;
#endif
    FS_UINT32	m_dwMaxMsgCount;
    FS_UINT		m_dwUserData;
    FS_UINT32	m_dwFlag;
    FS_UINT32	m_dwMsgCount;

    T**	m_pMsg;
    FS_INT32	m_nHead;
    FS_INT32	m_nTail;

    WSemaphore m_sem;
    WLock	m_Lock;
    Alloctor*	m_pAllocator;
};
template <class T>

class SimpleMsgQueue
{
public:
    SimpleMsgQueue(FS_UINT32 dwMaxMsgCount = 1000) :
        m_dwMaxMsgCount(dwMaxMsgCount),
        m_dwUserData(0),
        m_dwFlag(0),
        m_lMsgCount(0),
        m_bStop(FALSE),
        m_nHead(0),
        m_nTail(0),
        m_pAllocator(NULL)
    {
        m_pMsg = new T*[dwMaxMsgCount + 1];
    };
    virtual ~SimpleMsgQueue()
    {
        m_bStop = TRUE;
        delete[] m_pMsg;
        m_lMsgCount = 0;
        m_nHead = m_nTail = 0;
    };
    typedef WElementAllocator<T>	Alloctor;
public:
    BOOL	PushMsg(T *pMsg, FS_UINT32 *pdwMsgCount = NULL)
    {
        if (m_bStop)
        {
            return FALSE;
        }
        m_Lock.Lock();
        assert(m_lMsgCount < (FS_INT32)m_dwMaxMsgCount);
        if (m_lMsgCount >= (FS_INT32)m_dwMaxMsgCount)
        {
            m_Lock.UnLock();
            return FALSE;
        }
        m_pMsg[m_nTail++] = pMsg;
        m_nTail = m_nTail > (FS_INT32)m_dwMaxMsgCount ? 0 : m_nTail;
#ifdef _FS_OS_WIN
        InterlockedIncrement((LONG*)&m_lMsgCount);
#else
        ++m_lMsgCount;
#endif
        if (pdwMsgCount)
            *pdwMsgCount = m_lMsgCount;
        m_Lock.UnLock();

        return TRUE;
    }
    T*		PopMsg(FS_UINT32 dwWaitTime = INFINITE, FS_UINT32 *pdwMsgCount = NULL)
    {
        if (m_bStop)
            return NULL;
        m_Lock.Lock();
        if (m_lMsgCount <= 0)
        {
            m_Lock.UnLock();
            return NULL;
        }
        T* pMsg = m_pMsg[m_nHead++];
        m_nHead = m_nHead > (FS_INT32)m_dwMaxMsgCount ? 0 : m_nHead;
#ifdef _FS_OS_WIN
        InterlockedDecrement((LONG*)&m_lMsgCount);
#else
        --m_lMsgCount;
#endif
        if (pdwMsgCount)
            *pdwMsgCount = m_lMsgCount;
        m_Lock.UnLock();
        return pMsg;
    };
    FS_UINT32	GetMsgCount() { return m_lMsgCount; };
    FS_UINT32	GetMaxMsgCount() { return m_dwMaxMsgCount; };
    VOID		SetMaxMsgCount(FS_UINT32 dwMaxMsgCount) { m_dwMaxMsgCount = dwMaxMsgCount; };
    BOOL		IsFull() { return m_lMsgCount >= (FS_INT32)m_dwMaxMsgCount; };
    VOID		SetStop() { m_bStop = TRUE; };
    VOID		ResetStop() { m_bStop = FALSE; };
    VOID		SetFlag(FS_UINT32 dwFlag) { m_dwFlag = dwFlag; };
    FS_UINT32	GetFlag() { return m_dwFlag; };
    VOID		SetUserData(FS_UINT dwUserData) { m_dwUserData = dwUserData; };
    FS_UINT		GetUserData() { return m_dwUserData; };
    T*			Alloc() { return m_pAllocator ? m_pAllocator->Alloc() : NULL; };
    void		Free(T* pMsg) { if (m_pAllocator) m_pAllocator->Free(pMsg); }
    void		SetAllocator(WElementAllocator<T> *pAllocator) { m_pAllocator = pAllocator; };

protected:
    FS_UINT32	m_dwMaxMsgCount;
    FS_UINT		m_dwUserData;
    FS_UINT32	m_dwFlag;
    FS_INT32	m_lMsgCount;
    BOOL	m_bStop;

    WLock	m_Lock;
    T**		m_pMsg;
    FS_INT32		m_nHead;
    FS_INT32		m_nTail;
    Alloctor*	m_pAllocator;
};
}

#endif // !defined(AFX_WMSGQUEUE_H__25DFC653_6CF3_439C_8D86_3E42800C1CB6__INCLUDED_)
