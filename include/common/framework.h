#ifndef __FRAME_WORK_H
#define	__FRAME_WORK_H

#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif

    //Framework object GUID
    // {AB7DA4AA-3107-4347-A257-A4DCEFB66580}
    DEFINE_GUID(CLSID_FrameWork,
        0xab7da4aa, 0x3107, 0x4347, 0xa2, 0x57, 0xa4, 0xdc, 0xef, 0xb6, 0x65, 0x80);

    // IComponentFactory's GUID
    // {F9C9B576-DE20-47f0-AEC1-2217F2483A25}
    DEFINE_GUID(IID_IComponentFactory,
        0xf9c9b576, 0xde20, 0x47f0, 0xae, 0xc1, 0x22, 0x17, 0xf2, 0x48, 0x3a, 0x25);

    //
    //组件分类枚举回调接口
    //返回值不等于S_OK时,将停止枚举
    typedef HRESULT(CALLBACK *CategoryCallback)(REFGUID rCategory, REFCLSID rClsID, FS_UINT dwUserData);

    //----------------------------------------------------------------------------
    // IComponentFactory
    //----------------------------------------------------------------------------
    DECLARE_INTERFACE_(IComponentFactory, IUnknown)
    {
        //
        //创建组件及接口
        //
        STDMETHOD(CreateComponent) (THIS_
            REFCLSID rClsID,
            REFIID riid,
            LPUNKNOWN pUnkOuter,
            void **pv
            ) PURE;

        //
        //枚举指定分类的所有组件
        //
        STDMETHOD(EnumCategory) (THIS_
            REFGUID rCategory,
            CategoryCallback callback,
            FS_UINT	dwUserData
            ) PURE;

    };

#ifdef __cplusplus
}
#endif

#endif
