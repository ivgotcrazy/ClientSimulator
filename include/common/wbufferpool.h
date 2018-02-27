// WBufferPool.h: interface for the WBufferPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WBUFFERPOOL_H__FE59404F_2995_45A3_BC35_24E33702D130__INCLUDED_)
#define AFX_WBUFFERPOOL_H__FE59404F_2995_45A3_BC35_24E33702D130__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wbasetype.h"
#include "wlock.h"
#include "wsemaphore.h"
#include "wtimefunction.h"
#include <list>

namespace WBASELIB
{

class WFlexBuffer
{
public:
    WFlexBuffer(FS_UINT32 unSize = 0) :
        m_unSize(0),
        m_unDataLen(0),
        m_pbBuffer(NULL)
    {
        m_unSize = unSize;
        if (unSize > 0)
            m_pbBuffer = new BYTE[unSize];
    };
    virtual ~WFlexBuffer()
    {
        if (m_pbBuffer)
        {
            delete[] m_pbBuffer;
            m_pbBuffer = NULL;
        }
    };

public:
    virtual PBYTE		GetPtr() { return m_pbBuffer; };
    virtual PBYTE		GetPtr(FS_UINT32 unSize) { CheckSize(unSize); return m_pbBuffer; };
    virtual BOOL		WriteData(PBYTE pbData, FS_UINT32 unDataLen)
    {
        if (unDataLen > m_unSize)
        {
            if (!CheckSize(unDataLen))
                return FALSE;
        }
        memcpy(m_pbBuffer, pbData, unDataLen);
        m_unDataLen = unDataLen;
        return TRUE;
    };

    virtual VOID        SetDataLen(FS_UINT32 unDataLen) { m_unDataLen = unDataLen; };
    virtual FS_UINT32		GetDataLen() { return m_unDataLen; };

    virtual FS_UINT32        GetSize() { return m_unSize; };
protected:
    virtual BOOL		CheckSize(FS_UINT32 unSize)
    {
        BOOL bRet = TRUE;
        if (unSize > m_unSize)
        {

            delete[] m_pbBuffer;
            m_unSize = unSize;
            if (unSize > 0)
            {
                m_pbBuffer = new BYTE[unSize];
                if (!m_pbBuffer)
                {
                    bRet = FALSE;
                    m_unSize = 0;
                }
            }
        }
        return bRet;
    };
    FS_UINT32		m_unSize;
    FS_UINT32		m_unDataLen;
    PBYTE		m_pbBuffer;
};

template<class T>
class WPoolTemplate
{
    typedef std::list< T* > BufferList;
public:

    //buffer clear direction
    enum { BUFFER_CLEAR_DIR_BEGIN = 0, BUFFER_CLEAR_DIR_END };

    WPoolTemplate(FS_UINT32 unCount, FS_UINT32 unSize = 0)
        :m_bStop(FALSE),
        m_unBufferCount(0),
        m_unBufferSize(0),
        m_semBusy(0, unCount),
        m_semFree(unCount, unCount)
    {
        m_unBufferCount = unCount;
        m_unBufferSize = unSize;

        if (unCount > 0)
        {
            for (FS_UINT32 u = 0; u < unCount; u++)
            {
                T *pBuffer = new T(unSize);
                if (pBuffer)
                {
                    m_lsTotal.push_back(pBuffer);
                    m_lsFree.push_back(pBuffer);
                }
            }
        }
#ifdef _FS_OS_WIN
        m_evStop = CreateEvent(NULL, TRUE, FALSE, NULL);
#endif
    };

    ~WPoolTemplate()
    {
        SetStop();

        m_csBusy.Lock();
        m_lsBusy.clear();
        m_csBusy.UnLock();

        m_csFree.Lock();
        m_lsFree.clear();
        m_csFree.UnLock();

        while (m_lsTotal.size() > 0)
        {
            T *pBuffer = m_lsTotal.front();
            if (pBuffer)
                delete pBuffer;
            m_lsTotal.pop_front();
        }
#ifdef _FS_OS_WIN
        CloseHandle(m_evStop);
#endif
    };

    FS_UINT32 GetBufferCount() { return m_unBufferCount; };
    FS_UINT32 GetBufferSize() { return m_unBufferSize; };

    FS_UINT32 GetBufferFreeCount()
    {
        m_csFree.Lock();
        FS_UINT32 unCount = m_lsFree.size();
        m_csFree.UnLock();

        return unCount;
    };
    FS_UINT32 GetBufferBusyCount()
    {
        m_csBusy.Lock();
        FS_UINT32 unCount = m_lsBusy.size();
        m_csBusy.UnLock();

        return unCount;
    };

    FS_UINT32 GetBufferStatus()
    {
        if (m_unBufferCount < 1)
            return 0;

        FS_UINT32 unCount = GetBufferBusyCount();

        return unCount * 100 / m_unBufferCount;
    };

#ifndef _FS_OS_WIN
#define WaitSemphoreOrStop(sem, dwWaitMiniSecond)                               \
{                                                                               \
    const FS_UINT32 kStandardTime = 50;                                         \
    FS_UINT32 dwPassedTime = 0;                                                 \
    bool bWaitInfinite = dwWaitMiniSecond == INFINITE;                          \
    FS_UINT32 dwStartTime = GetTickCount();                                     \
    while (bWaitInfinite || dwPassedTime <= dwWaitMiniSecond)                   \
    {                                                                           \
        if (m_bStop)                                                            \
            return NULL;                                                        \
        FS_UINT32 dwAvailTime = dwWaitMiniSecond - dwPassedTime;                \
        FS_UINT32 dwWaitTime = dwAvailTime < kStandardTime ? dwAvailTime : kStandardTime;\
        dwRet = sem.WaitSemaphore(dwWaitTime);                                  \
        if (dwRet == WAIT_TIMEOUT)                                              \
        {                                                                       \
            dwPassedTime = bWaitInfinite ? 0 : GetTickCount() - dwStartTime;    \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            break;                                                              \
        }                                                                       \
    }                                                                           \
    if (dwPassedTime > dwWaitMiniSecond)                                        \
        return NULL;                                                            \
}
#endif

    T * GetFreeBuffer(FS_UINT32 dwWaitMiniSecond = INFINITE)
    {
        FS_UINT32 dwRet = 0;
#ifdef _FS_OS_WIN
        HANDLE evWait[2] = { m_evStop, m_semFree.GetHandle() };
        dwRet = WaitForMultipleObjects(2, evWait, FALSE, dwWaitMiniSecond);
        if (dwRet != WAIT_OBJECT_0 + 1)
            return NULL;
#else
        WaitSemphoreOrStop(m_semFree, dwWaitMiniSecond);
#endif

        T *pBuffer = NULL;
        m_csFree.Lock();
        pBuffer = m_lsFree.front();
        m_lsFree.pop_front();
        m_csFree.UnLock();

        return pBuffer;
    };

    T * PeekBusyBuffer(FS_UINT32 dwWaitMiniSecond = INFINITE)
    {
        FS_UINT32 dwRet = 0;
#ifdef _FS_OS_WIN
        HANDLE evWait[2] = { m_evStop, m_semBusy.GetHandle() };
        dwRet = WaitForMultipleObjects(2, evWait, FALSE, dwWaitMiniSecond);
        if (dwRet != WAIT_OBJECT_0 + 1)
            return NULL;
#else
        WaitSemphoreOrStop(m_semBusy, dwWaitMiniSecond);
#endif	

        T *pBuffer = NULL;
        m_csBusy.Lock();
        pBuffer = m_lsBusy.front();
        m_csBusy.UnLock();
        return pBuffer;
    };

    T * GetBusyBuffer(FS_UINT32 dwWaitMiniSecond = INFINITE)
    {
        FS_UINT32 dwRet = 0;
#ifdef _FS_OS_WIN
        HANDLE evWait[2] = { m_evStop, m_semBusy.GetHandle() };
        dwRet = WaitForMultipleObjects(2, evWait, FALSE, dwWaitMiniSecond);
        if (dwRet != WAIT_OBJECT_0 + 1)
            return NULL;
#else
        WaitSemphoreOrStop(m_semBusy, dwWaitMiniSecond);
#endif			
        T *pBuffer = NULL;
        m_csBusy.Lock();
        pBuffer = m_lsBusy.front();
        m_lsBusy.pop_front();
        m_csBusy.UnLock();

        return pBuffer;
    };

    VOID AddFreeBuffer(T *pBuffer)
    {
        if (!pBuffer)
            return;

        m_csFree.Lock();
        m_lsFree.push_back(pBuffer);
        m_csFree.UnLock();

        m_semFree.ReleaseSemaphore(1L);
    };

    VOID AddBusyBuffer(T *pBuffer)
    {
        if (!pBuffer)
            return;

        m_csBusy.Lock();
        m_lsBusy.push_back(pBuffer);
        m_csBusy.UnLock();

        m_semBusy.ReleaseSemaphore(1L);
    };

    BOOL InsertBusyBuffer(T *pBuffer)
    {
        FS_UINT32 	unTemp;
        T*	pTempBuffer;
        FS_UINT32   	unSeqNum;
        BOOL	bRet = TRUE;
#ifdef _FS_OS_WIN
        BufferList::iterator  it;
#else
#ifdef _STLP_LIST
        std::priv::_List_iterator<T*, std::_Nonconst_traits<T*> > it;

#else
#if defined _FS_OS_IOS || defined _FS_OS_MAC
        typename BufferList::iterator it;
        //std::iterator<T*, std::allocator<T*>> it;
        //typename std::list<T *>::iterator it;
#else
        std::_List_iterator<T*> it;
#endif
#endif			
#endif

        if (!pBuffer)
            return FALSE;

        unSeqNum = pBuffer->GetSeqNum();

        BOOL  bInvalid = TRUE;

        m_csBusy.Lock();

        for (it = m_lsBusy.begin(); it != m_lsBusy.end(); it++)
        {

            pTempBuffer = *it;
            if (pTempBuffer)
            {

                unTemp = pTempBuffer->GetSeqNum();
                if (unTemp == unSeqNum)
                {
                    bInvalid = FALSE;
                    break;
                }

                if ((unSeqNum < unTemp && unTemp - unSeqNum < m_unBufferCount * 2) ||
                    (unSeqNum > unTemp && unSeqNum - unTemp > m_unBufferCount * 2))
                    break;
            }
        }

        if (bInvalid)
        {
            if (it != m_lsBusy.end())
                m_lsBusy.insert(it, pBuffer);
            else
                m_lsBusy.push_back(pBuffer);
            m_semBusy.ReleaseSemaphore(1L);

            bRet = TRUE;
        }
        else
        {
            m_lsFree.push_back(pBuffer);
            m_semFree.ReleaseSemaphore(1L);

            bRet = FALSE;
        }
        m_csBusy.UnLock();

        return bRet;
    };

    VOID SetStop()
    {
#ifdef _FS_OS_WIN
        SetEvent(m_evStop);
#endif
        m_bStop = TRUE;
    };
    BOOL  IsStoped()
    {
        return m_bStop;
    };
    FS_UINT32 WaitStop(FS_UINT32 dwMilliSeconds)
    {
#ifdef _FS_OS_WIN
        return WaitForSingleObject(m_evStop, dwMilliSeconds);
#else	
        if (m_bStop)
            return WAIT_OBJECT_0;
        const FS_UINT32 kStandardTime = 10;
        FS_UINT32 dwPassedTime = 0;
        bool bWaitInfinite = dwMilliSeconds == INFINITE;
        FS_UINT32 dwStartTime = GetTickCount();
        while (bWaitInfinite || dwPassedTime <= dwMilliSeconds)
        {
            FS_UINT32 dwAvailTime = dwMilliSeconds - dwPassedTime;
            FS_UINT32 dwWaitTime = dwAvailTime < kStandardTime ? dwAvailTime : kStandardTime;
            Sleep(dwWaitTime);
            if (m_bStop)
            {
                return WAIT_OBJECT_0;
            }
            else if (!bWaitInfinite)
            {
                dwPassedTime = GetTickCount() - dwStartTime;
            }
        }
        if (m_bStop)
            return WAIT_OBJECT_0;
        return WAIT_TIMEOUT;
#endif
    };

    VOID ResetStop()
    {
#ifdef _FS_OS_WIN
        ResetEvent(m_evStop);
#endif
        m_bStop = FALSE;
    };

    VOID FreeLock() { m_csFree.Lock(); };
    VOID FreeUnLock() { m_csFree.UnLock(); };
    VOID BusyLock() { m_csBusy.Lock(); };
    VOID BusyUnLock() { m_csBusy.UnLock(); };

    VOID ClearBusyBuffer(FS_UINT32 unCount, BYTE bDir = BUFFER_CLEAR_DIR_BEGIN)
    {
        m_csBusy.Lock();
        m_csFree.Lock();

#ifdef _FS_OS_WIN
        HANDLE evWait[2] = { m_evStop, m_semBusy.GetHandle() };
#endif
        FS_UINT32 dwRet = 0;
        T  *pBuffer;

        if (bDir == BUFFER_CLEAR_DIR_BEGIN)
        {

            do
            {
#ifdef _FS_OS_WIN
                dwRet = WaitForMultipleObjects(2, evWait, FALSE, 0);
                if (dwRet != WAIT_OBJECT_0 + 1)
                    break;
#else
                dwRet = m_semBusy.WaitSemaphore(0);
                if (dwRet != WAIT_OBJECT_0)
                    break;
#endif

                pBuffer = m_lsBusy.front();
                m_lsBusy.pop_front();
                m_lsFree.push_back(pBuffer);

                m_semFree.ReleaseSemaphore(1L);

            } while (--unCount && !m_bStop);
        }

        if (bDir == BUFFER_CLEAR_DIR_END)
        {

            do
            {
#ifdef _FS_OS_WIN
                dwRet = WaitForMultipleObjects(2, evWait, FALSE, 0);
                if (dwRet != WAIT_OBJECT_0 + 1)
                    break;
#else
                dwRet = m_semBusy.WaitSemaphore(0);
                if (dwRet != WAIT_OBJECT_0)
                    break;
#endif

                pBuffer = m_lsBusy.back();
                m_lsBusy.pop_back();
                m_lsFree.push_back(pBuffer);

                m_semFree.ReleaseSemaphore(1L);

            } while (--unCount && !m_bStop);
        }

        m_csFree.UnLock();
        m_csBusy.UnLock();
    };

protected:
#ifdef _FS_OS_WIN
    HANDLE		m_evStop;		//停止事件，当此事件有信号时，拒绝所有读写操作
#endif
    volatile BOOL	m_bStop;

    FS_UINT32		m_unBufferCount;
    FS_UINT32		m_unBufferSize;

    WLock		m_csFree;
    WLock		m_csBusy;

    BufferList	m_lsBusy;
    BufferList	m_lsFree;
    BufferList  m_lsTotal;

    WSemaphore 	m_semBusy;
    WSemaphore	m_semFree;
};

typedef WPoolTemplate<WFlexBuffer> WFlexBufferPool;
}

#endif // !defined(AFX_WBUFFERPOOL_H__FE59404F_2995_45A3_BC35_24E33702D130__INCLUDED_)
