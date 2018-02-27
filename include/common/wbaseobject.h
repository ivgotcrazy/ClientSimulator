// BaseObject.h: interface for the CBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEOBJECT_H__0F7BC688_9860_4803_BF6F_28B148B9EE2B__INCLUDED_)
#define AFX_BASEOBJECT_H__0F7BC688_9860_4803_BF6F_28B148B9EE2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "list"
#include "wlock.h"

namespace WBASELIB
{

class WBaseObject
{
public:
    WBaseObject() { m_lRef = 1; };
    virtual ~WBaseObject() {};

    virtual FS_INT32 Release()
    {
#ifdef _FS_OS_WIN
        FS_UINT32 lRef = (FS_UINT32)InterlockedDecrement((LONG*)&m_lRef);
#else
        m_lockRef.Lock();
        FS_INT32 lRef = --m_lRef;
        m_lockRef.UnLock();
#endif
        if (0 == lRef)
        {
            delete this;
        }
        return (FS_INT32)(lRef);
    }

    virtual FS_INT32 AddRef()
    {
#ifdef _FS_OS_WIN
        FS_UINT32 lRef = (FS_UINT32)InterlockedIncrement((LONG*)&m_lRef);
#else
        m_lockRef.Lock();
        FS_UINT32 lRef = ++m_lRef;
        m_lockRef.UnLock();
#endif
        return (FS_INT32)(lRef);
    }
protected:
    volatile FS_UINT32	m_lRef;
#ifndef _FS_OS_WIN
    WLock		m_lockRef;
#endif
};

#define INSERT_TAIL

template <class T>

class WElementAllocator
{
    struct it
    {
        T		Element;
        it*		pNext;
    };
    typedef std::list<it*> ElementList;
public:
    WElementAllocator(FS_UINT32 dwIncreCount = 10) :
        m_dwIncreCount(dwIncreCount),
        m_lTotalCount(0),
        m_pHead(NULL),
        m_pTail(NULL)
    {
    };
    virtual ~WElementAllocator()
    {
        Clear();
    };
public:
    FS_INT32		GetTotalAllocCount() { return m_lTotalCount; };
    BOOL	BatchAlloc(FS_UINT32 dwCount)
    {
        it*	pElement = new  it[dwCount];
        if (NULL == pElement)
            return FALSE;

        m_lock.Lock();

        m_pTail = m_pTail ? m_pTail : pElement;
        for (FS_UINT32 dwIndex = 0; dwIndex < dwCount; dwIndex++)
        {
            pElement[dwIndex].pNext = m_pHead;
            m_pHead = pElement + dwIndex;
        }
        m_lsTotal.push_back(pElement);
        m_lTotalCount += dwCount;

        //				FS_UINT32 dwTotalSize = sizeof(T)*m_lTotalCount;
        m_lock.UnLock();

        return TRUE;
    };
    T*		Alloc()
    {
        T *pElement = NULL;
        m_lock.Lock();

        if (m_pHead)
        {
            pElement = &(m_pHead->Element);
            m_pHead = m_pHead->pNext;
        }
        else
        {
            if (BatchAlloc(m_dwIncreCount))
            {
                pElement = &(m_pHead->Element);
                m_pHead = m_pHead->pNext;
            }
        }
        m_pTail = m_pHead ? m_pTail : NULL;
        m_lock.UnLock();

        return pElement;
    };
    VOID	Free(T* pElement)
    {
        m_lock.Lock();
        it* i = (it*)pElement;
#ifdef INSERT_TAIL
        i->pNext = NULL;
        if (m_pHead)
        {
            m_pTail->pNext = i;
            m_pTail = i;
        }
        else
        {
            m_pHead = m_pTail = i;
        }
#else
        i->pNext = m_pHead;
        m_pHead = i;
        if (NULL == m_pTail)
            m_pTail = m_pHead;
#endif
        m_lock.UnLock();
    };
    VOID	Clear()
    {
        while (m_lsTotal.size() > 0)
        {
            it *pElement = m_lsTotal.front();
            delete[] pElement;
            m_lsTotal.pop_front();
        }

        m_pHead = NULL;
        m_pTail = NULL;
    };
protected:


    ElementList		m_lsTotal;
    FS_UINT32			m_dwIncreCount;
    volatile FS_INT32		m_lTotalCount;

    WLock			m_lock;
    it*			m_pHead;
    it*			m_pTail;
};

}
#endif // !defined(AFX_BASEOBJECT_H__0F7BC688_9860_4803_BF6F_28B148B9EE2B__INCLUDED_)
