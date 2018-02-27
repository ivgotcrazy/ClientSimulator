#ifndef __IAUDIO_SOURCE_H
#define __IAUDIO_SOURCE_H

#include "wcombase.h"
#include "AudioDefine.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	//IAudioEncSource Interface's GUID
	// {557CA888-1602-4ccb-B737-1AFE31E66FA9}
	DEFINE_GUID( IID_IAudioEncSource, 
		0x557ca888, 0x1602, 0x4ccb, 0xb7, 0x37, 0x1a, 0xfe, 0x31, 0xe6, 0x6f, 0xa9);
	
	//
	//IAudioDataSink
	//
	DECLARE_INTERFACE( IAudioDataSink )
	{
		//音频数据回调
		STDMETHOD_( LONG,OnAudioData ) ( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT dwUserData ) PURE;	
	};

	
	//----------------------------------------------------------------------------
	// IAudioEncSource
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioEncSource, IUnknown)
	{
		//
		//添加数据回调接口
		//
		STDMETHOD( AddDataSink )( THIS_ IAudioDataSink *pSink,FS_UINT dwUserData ) PURE;
		//
		//删除数据回调接口
		//
		STDMETHOD( RemoveDataSink )( THIS_ IAudioDataSink *pSink ) PURE;
		//
		//设置参数
		//
		STDMETHOD( SetParam )( THIS_ int nParamType,void *pValue,int nValueSize ) PURE;
		//
		//获取参数
		//
		STDMETHOD( GetParam )( THIS_ int nParamType,void *pValue,int nValueSize ) PURE;

		STDMETHOD( EnableDataSink )( THIS_ BOOL bEnable ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif