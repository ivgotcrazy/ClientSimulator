#ifndef __WCOMBASE_H
#define __WCOMBASE_H

#include "wbasetype.h"
#include "wcomerror.h"

#ifdef _FS_OS_WIN

#include <objbase.h>

#else

DEFINE_GUID(IID_IUnknown,
    0x00000000, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#undef INTERFACE
#define INTERFACE IUnknown

DECLARE_INTERFACE(IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void ** ppvObject) PURE;
    STDMETHOD_(FS_UINT32, AddRef)(THIS)PURE;
    STDMETHOD_(FS_UINT32, Release)(THIS)PURE;
};

typedef IUnknown*	LPUNKNOWN;

#ifdef __cplusplus
namespace WBASELIB
{

extern HRESULT CoCreateGuid(GUID *pguid);

}
#endif

#endif //_FS_OS_WIN

#endif //_COMBASE_H
