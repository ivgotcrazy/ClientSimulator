#pragma once

#include <initguid.h>
#include "wwindef.h"
#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif

DEFINE_GUID(CLSID_VirtualVideoDevice,
	0xcfa241ea, 0x9fa5, 0x49eb, 0xb9, 0x3f, 0x3a, 0x81, 0x5a, 0x7c, 0x5, 0x22);

// 70a86844-0160-46d5-b5ee-e53a47866313
//DEFINE_GUID(IID_IVirutalVideoDevice,
//	0x70a86844, 0x0160, 0x46d5, 0xb5, 0xee, 0xe5, 0x3a, 0x47, 0x86, 0x63, 0x13);

// bcd40f54-a03e-4a41-92fd-403a8614740b
DEFINE_GUID(IID_IVirtualVideoDataSink,
	0xbcd40f54, 0xa03e, 0x4a41, 0x92, 0xfd, 0x40, 0x3a, 0x86, 0x14, 0x74, 0x0b);

DECLARE_INTERFACE_(IVirtualVideoDataSink, IUnknown)
{
	//视频数据回调
	STDMETHOD_(LONG, OnVideoData) (THIS_ FS_UINT dwUserDat, PBYTE pbData, FS_UINT32 dwDataLen, BOOL bKeyFrame) PURE;
};


#ifdef __cplusplus
}
#endif

