#ifndef __AVPLUGIN_MANAGER_H
#define __AVPLUGIN_MANAGER_H

#include "wcombase.h"
#include "AVDevPlugin.h"
#include "IAVPlugin.h"

#ifdef __cplusplus
extern "C" {
#endif
	// {F124CF5D-1116-48da-AD33-C6BBB7E1F7D7}
	DEFINE_GUID(CLSID_AVPluginManager, 
		0xf124cf5d, 0x1116, 0x48da, 0xad, 0x33, 0xc6, 0xbb, 0xb7, 0xe1, 0xf7, 0xd7);

	// {C3D8AD42-D6AA-4875-96A8-C171C52C71D5}
	DEFINE_GUID(IID_IAVPluginManager, 
		0xc3d8ad42, 0xd6aa, 0x4875, 0x96, 0xa8, 0xc1, 0x71, 0xc5, 0x2c, 0x71, 0xd5);


	DECLARE_INTERFACE_(IAVPluginManager, IUnknown)
	{
		//寻找并初始化插件
		STDMETHOD( InitPlugins )( THIS_ WCHAR* wszPluginPath ) PURE;
		//获取插件类型数量
		STDMETHOD_(int,GetPluginCount )( THIS_ ) PURE;
		//获取插件信息
		STDMETHOD(GetPluginInfo )( THIS_ int nIndex, AVPluginLibInfo* pInfo ) PURE; 
		//创建插件
		STDMETHOD( CreatePlugin )( THIS_ GUID* pGuid,WCHAR* wszConfigFilePath,IAVPlugin** ppPlugin  ) PURE;
		//销毁插件
		STDMETHOD( DestroyPlugin )( THIS_ IAVPlugin* pPlugin  ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif