// FrameUnknown.h: interface for the CFrameUnknown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEUNKNOWN_H__7D45F349_0406_416F_8028_6D58BD166C80__INCLUDED_)
#define AFX_FRAMEUNKNOWN_H__7D45F349_0406_416F_8028_6D58BD166C80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "framebaseobject.h"
#include "wlock.h"

using namespace WBASELIB;

namespace FRAMEWORKSDK
{

#ifndef INONDELEGATINGUNKNOWN_DEFINED
DECLARE_INTERFACE(INonDelegatingUnknown)
{
    STDMETHOD(NonDelegatingQueryInterface) (THIS_ REFIID, LPVOID *) PURE;
    STDMETHOD_(ULONG, NonDelegatingAddRef)(THIS)PURE;
    STDMETHOD_(ULONG, NonDelegatingRelease)(THIS)PURE;
};
#define INONDELEGATINGUNKNOWN_DEFINED
typedef INonDelegatingUnknown *PNDUNKNOWN;
#endif


class CFrameUnknown : public INonDelegatingUnknown, public  CFrameBaseObject
{
private:
    const LPUNKNOWN m_pUnknown; /* Owner of this object */

protected:                      /* So we can override NonDelegatingRelease() */
    volatile FS_INT32	m_cRef;       /* Number of reference counts */
#ifndef _FS_OS_WIN
    WLock			m_reflock;
#endif
    IComponentFactory*		m_pComponentFactory;
public:
    CFrameUnknown(const TCHAR *pName, LPUNKNOWN pUnk, IComponentFactory *pFrameWork);
    virtual ~CFrameUnknown();

    /* Return the owner of this object */

    LPUNKNOWN GetOwner() const
    {
        return m_pUnknown;
    };

    /* static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *) */

    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void **);
    STDMETHODIMP_(ULONG) NonDelegatingAddRef();
    STDMETHODIMP_(ULONG) NonDelegatingRelease();
};

}

#endif // !defined(AFX_FRAMEUNKNOWN_H__7D45F349_0406_416F_8028_6D58BD166C80__INCLUDED_)
