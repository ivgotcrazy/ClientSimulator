#ifndef __IAVDEV_MANAGER_H
#define __IAVDEV_MANAGER_H

#include "wcombase.h"
#include "AVDevPlugin.h"
#include "IAVPlugin.h"
#include "VideoDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	// {02C99EAE-F379-4236-A677-82F040851A47}
	DEFINE_GUID(CLSID_AVDevManager, 
		0x2c99eae, 0xf379, 0x4236, 0xa6, 0x77, 0x82, 0xf0, 0x40, 0x85, 0x1a, 0x47);

	// {B250B92C-992E-4a1e-9125-3863B452330B}
	DEFINE_GUID(IID_IAVDevManager, 
		0xb250b92c, 0x992e, 0x4a1e, 0x91, 0x25, 0x38, 0x63, 0xb4, 0x52, 0x33, 0xb);

	DECLARE_INTERFACE_(IAVDevManager, IUnknown)
	{
		//添加音频插件设备
		STDMETHOD( AddAudioPlugin )( THIS_ IAVPlugin *pPlugin,WCHAR* wszName ) PURE;
		//添加视频插件设备
		STDMETHOD( AddVideoPlugin )( THIS_ IAVPlugin *pPlugin,WCHAR* wszName ) PURE;
		//删除音视频插件设备
		STDMETHOD( RemoveAudioPlugin )( THIS_ IAVPlugin *pPlugin ) PURE;
		STDMETHOD( RemoveVideoPlugin )( THIS_ IAVPlugin *pPlugin ) PURE;
		//获取音频采集设备数量
		STDMETHOD_(int,GetAudioCapDevCount)( THIS_ ) PURE;
		//获取音频采集设备名称
		STDMETHOD( GetAudioCapDevInfo )( THIS_ int nDevIndex,WCHAR *wszName,UINT nSize ) PURE;
		//获取视频采集设备数量
		STDMETHOD_(int,GetVideoCapDevCount)( THIS_ ) PURE;
		//获取视频采集设备名称
		STDMETHOD( GetVideoCapDevInfo )( THIS_ int nDevIndex,WCHAR *wszName,UINT nSize ) PURE;
        STDMETHOD_(unsigned, GetVideoCapDevInfo)(VideoCapDeviceInfo *pCapDevInfo, UINT uSize) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif