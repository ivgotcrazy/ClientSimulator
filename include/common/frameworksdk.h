#ifndef __FRAMEWORK_SDK_H
#define __FRAMEWORK_SDK_H

#include "wbasetype.h"
#include "framework.h"
#include "component.h"
#include "frameworkutil.h"
#include "framebaseobject.h"
#include "frameunknown.h"
#include "wframelog.h"

#if defined _FS_OS_WIN

#ifdef _FS_ARCH_32
#ifdef _DEBUG
#pragma comment(lib,"frameworksdkd32.lib")
#else
#pragma comment(lib,"frameworksdk32.lib")
#endif
#elif defined _FS_ARCH_64
#ifdef _DEBUG
#pragma comment(lib,"frameworksdkd64.lib") 
#else
#pragma comment(lib,"frameworksdk64.lib")
#endif
#endif

#elif defined _FS_OS_LINUX || defined _FS_OS_IOS || defined _FS_OS_MAC || defined _FS_OS_ANDROID

#ifdef _FS_ARCH_32
#ifdef _DEBUG
#pragma comment(lib,"libframeworksdkd32.a")
#else
#pragma comment(lib,"libframeworksdk32.a")
#endif
#elif defined _FS_ARCH_64
#ifdef _DEBUG
#pragma comment(lib,"libframeworksdkd64.a") 
#else
#pragma comment(lib,"libframeworksdk64.a")
#endif
#endif

#endif
using namespace FRAMEWORKSDK;

STDAPI		CPDllCanUnloadNow();

#if !(defined _FS_OS_IOS || defined _FS_OS_MAC)
STDAPI		CPDllCreateComponent(REFCLSID rClsID, REFIID riid, LPUNKNOWN pUnkOuter, IComponentFactory *pFactory, void **pv);
#endif

STDAPI		CPDllCreateComponent2(REFCLSID rClsID, REFIID riid, LPUNKNOWN pUnkOuter, IComponentFactory *pFactory, void **pv, ComponentObject* pObjs, FS_INT32 nObjCount);

STDAPI		FWInitFrameWorkFromPath(BOOL bRunServer, const WCHAR *wszComponentPath, const WCHAR *wszLogPath, IComponentFactory**pFrameWork);

STDAPI		FWInitFrameWorkFromEnv(BOOL bRunServer, const WCHAR *wszEnvName, const WCHAR *wszLogPath, IComponentFactory**pFrameWork);

STDAPI		FWReleaseFrameWork();

#endif
