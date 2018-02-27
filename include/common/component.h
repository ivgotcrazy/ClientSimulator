#ifndef _WCOMPONENT_H
#define _WCOMPONENT_H

#include "wbasetype.h"
#include "frameunknown.h"

using namespace FRAMEWORKSDK;

typedef CFrameUnknown *(WINAPI *LPFNNewComponent)(LPUNKNOWN pUnkOuter, IComponentFactory *pFactory, HRESULT *phr);

typedef struct
{
    const TCHAR *				m_Name;
    const CLSID *				m_ClsID;
    const GUID *				m_CategoryID;
    LPFNNewComponent			m_lpfnNew;

}ComponentObject;

#define		FRAMEVERSION			0x01000001

//组件动态库接口定义
typedef struct
{

    FS_UINT32													dwSize;
    HRESULT(STDAPICALLTYPE*	DllGetInfo)					(FS_UINT32 *pdwFrameVersion, FS_UINT32* pdwDllVersion, FS_UINT32 *pdwDllType);
    HRESULT(STDAPICALLTYPE*	DllGetComponentObject)		(ComponentObject** ppObject, FS_UINT32* pdwCount);
    HRESULT(STDAPICALLTYPE*	DllCanUnloadNow)			();
    HRESULT(STDAPICALLTYPE*	DllCreateComponent)		(REFCLSID rClsID, REFIID riid, LPUNKNOWN pUnkOuter, IComponentFactory *pFramework, void **pv);

}ComponentDll;

//组件动态库接口定义
typedef struct
{

    FS_UINT32													dwSize;
    HRESULT(STDAPICALLTYPE*	DllGetInfo)					(FS_UINT32 *pdwFrameVersion, FS_UINT32* pdwDllVersion, FS_UINT32 *pdwDllType);
    HRESULT(STDAPICALLTYPE*	DllGetComponentObject)		(ComponentObject** ppObject, FS_UINT32* pdwCount);
    HRESULT(STDAPICALLTYPE*	DllCanUnloadNow)			();
    HRESULT(STDAPICALLTYPE*	DllCreateComponent)		(REFCLSID rClsID, REFIID riid, LPUNKNOWN pUnkOuter, IComponentFactory *pFramework, void **pv);
    HRESULT(STDAPICALLTYPE*	DllInitFrameWork)			(BOOL bRunServer, const WCHAR* szComponentPath, const WCHAR* szLogPath);
    HRESULT(STDAPICALLTYPE*	DllReleaseFrameWork)		();
    HRESULT(STDAPICALLTYPE*	DllGetInterface)			(REFIID riid, void **pv);

}ComponentCoreDll;

typedef HRESULT(STDAPICALLTYPE*	LoadComponentDll)		(ComponentDll *pDll);

#define WDLL_FUNNAME			"FMDll"
STDAPI	FMDll(ComponentDll *pDll);

#endif
