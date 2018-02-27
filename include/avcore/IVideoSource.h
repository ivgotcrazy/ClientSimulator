#ifndef __IVIDEO_SOURCE_H
#define __IVIDEO_SOURCE_H

#include "wcombase.h"
#include "VideoDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	//IVideoEncSource Interface's GUID
	// {3B60AB03-3C06-4c97-9D72-E46B0EFEBFA7}
	DEFINE_GUID( IID_IVideoEncSource, 
		0x3b60ab03, 0x3c06, 0x4c97, 0x9d, 0x72, 0xe4, 0x6b, 0xe, 0xfe, 0xbf, 0xa7);

	//
	//IVideoDataSink
	//
	DECLARE_INTERFACE( IVideoDataSink )
	{
		//视频数据回调
		STDMETHOD_( LONG,OnVideoData ) ( THIS_ FS_UINT dwUserDat,PBYTE pbData,FS_UINT32 dwDataLen,BOOL bKeyFrame ) PURE;	
	};

#define VESC_ADJUSTSIZE			0x0001			//可调大小
	typedef struct{

		FS_UINT32			dwFlags;
	}VideoEncSourceCaps;

	//----------------------------------------------------------------------------
	// IVideoEncSource
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IVideoEncSource, IUnknown)
	{
		//设置视频数据回调接口
		STDMETHOD( AddDataSink )( THIS_ IVideoDataSink *pSink,FS_UINT dwUserData ) PURE;

		STDMETHOD( RemoveDataSink )( THIS_ IVideoDataSink *pSink ) PURE;
		//设置参数
		STDMETHOD( SetParam )( THIS_ const Video_CapEnc_Param *pParam ) PURE;
		//获取参数
		STDMETHOD( GetParam )( THIS_ Video_CapEnc_Param *pParam ) PURE;

		STDMETHOD( EnableDataSink )( THIS_ BOOL bEnable ) PURE;

		STDMETHOD( GetCapabilities )( THIS_ VideoEncSourceCaps* pCaps ) PURE;
		//根据远端显示窗口大小，调节视频参数
		STDMETHOD( AdjustVideoParamByWndSize )( THIS_ WORD wWndWidth,WORD wWndHeight ) PURE;
	};
		
#ifdef __cplusplus
}
#endif

#endif