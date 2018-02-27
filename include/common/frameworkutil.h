#ifndef __FRAMEWORK_UTIL_H
#define __FRAMEWORK_UTIL_H

namespace FRAMEWORKSDK
{

#ifndef DECLARE_IUNKNOWN
#define DECLARE_IUNKNOWN                                        \
			STDMETHODIMP QueryInterface(REFIID riid, void **ppv) {      \
			return CFrameUnknown::GetOwner()->QueryInterface(riid,ppv);            \
		};                                                          \
			STDMETHODIMP_(ULONG) AddRef() {                             \
			return CFrameUnknown::GetOwner()->AddRef();                            \
		};                                                          \
			STDMETHODIMP_(ULONG) Release() {                            \
			return CFrameUnknown::GetOwner()->Release();                           \
		};
#endif
template<class T> inline static T ourmax(const T & a, const T & b)
{
    return a > b ? a : b;
};
template<class T> inline static T ourmin(const T & a, const T & b)
{
    return a < b ? a : b;
};

#define CheckPointer(p,ret) {if((p)==NULL) return (ret);}
#define HresultFromWin32(x) (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, x))

STDAPI GetComponentInterface(LPUNKNOWN pUnk, void **ppv);
}

#endif
