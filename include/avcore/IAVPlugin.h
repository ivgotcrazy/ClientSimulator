#ifndef __IAVPLUGIN_H
#define __IAVPLUGIN_H

#include "wcombase.h"
#include "AVDevPlugin.h"

#ifdef __cplusplus
extern "C" {
#endif

	// {A0EE6ACD-D15B-4829-B03F-7749ACBF0245}
	DEFINE_GUID(IID_IAVPlugin, 
		0xa0ee6acd, 0xd15b, 0x4829, 0xb0, 0x3f, 0x77, 0x49, 0xac, 0xbf, 0x2, 0x45);

	DECLARE_INTERFACE(IAVPlugin)
	{
		//获取插件类型
		STDMETHOD_(FS_UINT32,GetType)( THIS_ ) PURE;
		//获取插件能力
		STDMETHOD_( FS_UINT32,GetCapa )( THIS_ ) PURE;
		//设置语言编码
		STDMETHOD(SetLanCode)( THIS_ int nLanCode ) PURE;
		//配置插件，配置参数将自动保存在设置的配置文件中
		STDMETHOD(Config )( THIS_ HWND hWndParent ) PURE;
		//设置是否允许数据回调
		STDMETHOD(EnableOutput )( THIS_ FS_UINT32 dwMediaType,BOOL bEnable ) PURE;
		//设置数据回调函数
		STDMETHOD(SetOutputCallback )( THIS_ FS_UINT32 dwMediaType,AVPLUGIN_MEDIACALLBACK	lpCallback,FS_UINT dwUserData ) PURE;
		//设置是否允许输入数据
		STDMETHOD(EnableInput )( THIS_ FS_UINT32 dwMediaType,BOOL bEnable )PURE;
		//向插件输入数据
		STDMETHOD(InputSample )( THIS_ AVPluginSample* pSample)PURE;
		//查询输出格式
		STDMETHOD(QueryOutputFormat)( THIS_ FS_UINT32 dwMediaType,int nIndex,void* pFormat,FS_UINT32 dwFormatSize ) PURE;
		//设置输出格式
		STDMETHOD(SetOutputFormat)( THIS_ FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize ) PURE;
		//获取当前输出格式
		STDMETHOD(GetOutputFormat)( THIS_ FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif