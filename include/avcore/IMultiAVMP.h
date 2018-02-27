#ifndef __IMULTIAVMP_H
#define __IMULTIAVMP_H

#include "wcombase.h"
#include "IAudioSource.h"
#include "IVideoSource.h"
#include "IVideoDevice.h"
#include "IAudioDevice.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#ifndef MULTIAV_MEDIATYPE_AUDIO
	#define	MULTIAV_MEDIATYPE_AUDIO			0X01	//音频数据
	#define MULTIAV_MEDIATYPE_VIDEO			0X02	//视频数据
#endif

	typedef struct{

		int		nUpMaxLostRate;
		int		nUpMinLostRate;
		int		nUpAvgLostRate;
		int		nDownMaxLostRate;
		int		nDownMinLostRate;
		int		nDownAvgLostRate;
	}MULTIAV_QOSSTATE;

	// MultiAVMP Component's GUID
	// {314525EE-6D98-4565-9252-6B69B12A992C}
	DEFINE_GUID(CLSID_MultiAVMP, 
		0x314525ee, 0x6d98, 0x4565, 0x92, 0x52, 0x6b, 0x69, 0xb1, 0x2a, 0x99, 0x2c);

	// IMultiAVMP Interface's GUID
	// {ABC48877-A366-4fb7-80BB-5DAA30939C77}
	DEFINE_GUID( IID_IMultiAVMP, 
		0xabc48877, 0xa366, 0x4fb7, 0x80, 0xbb, 0x5d, 0xaa, 0x30, 0x93, 0x9c, 0x77);

	//
	//IAudioDataSink
	//
	DECLARE_INTERFACE( IMediaDataSink )
	{
		//数据回调
		STDMETHOD_( LONG,OnMediaData ) ( THIS_ BYTE bMediaType,BYTE bMediaID, PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwUserID,FS_UINT dwUserData ) PURE;	

	};

	typedef struct{

		int		nMaxWidth;
		int		nMaxHeight;
		int		nMaxFrameRate;
		int		nMaxBitrate;
	}VideoMaxParam;

	//----------------------------------------------------------------------------
	// IMultiAVMP
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IMultiAVMP, IUnknown)
	{
		//初始化
		STDMETHOD( Initialize )( THIS_ LPUNKNOWN pAudioDevice, LPUNKNOWN pRenderManager,LPUNKNOWN pSessionManager) PURE;

		//登录服务器，服务器返回结果后通知应用层，通知消息的WPARAM参数为1代表成功
		STDMETHOD( Login )( THIS_ const GUID& guidGroup,FS_UINT32 dwUserID,FS_UINT32 dwCheckCode,FS_UINT16 wApplicationID,const CHAR* lpszServerAddrLink,WBASE_NOTIFY *pNotify ) PURE;
		//注销
		STDMETHOD( Logout )( THIS_ ) PURE;

		//添加采集设备源
		STDMETHOD( AddSource )( THIS_ BYTE bMediaType,BYTE bMediaID,LPUNKNOWN pSource ) PURE;
		//删除采集设备源
		STDMETHOD( RemoveSource )( THIS_ BYTE bMediaType,BYTE bMediaID ) PURE;
		//删除所有的采集设备源
		STDMETHOD( RemoveAllSource )( THIS_ ) PURE;
		//是否允许自动调节参数
		STDMETHOD( EnableAutoAdjust )( THIS_ BYTE bMediaType,BYTE bMediaID,BOOL bEnable ) PURE;
		//设置视频参数自动调节的最大值
		STDMETHOD( SetVideoSourceMaxParam )( THIS_ BYTE bMediaID,const VideoMaxParam* pParam ) PURE;

		//是否允许发送数据
		STDMETHOD( EnableSend )( THIS_ BYTE bMediaType,BYTE bMediaID,BOOL bEnable ) PURE;

		//接收用户数据
		STDMETHOD( StartRecvMedia )( THIS_ FS_UINT32 dwRemoteUserID,BYTE bMediaType,BYTE bMediaID,FS_UINT32 dwRenderID ) PURE;
		//停止接收用户数据
		STDMETHOD( StopRecvMedia )( THIS_ FS_UINT32 dwRemoteUserID,BYTE bMediaType,BYTE bMediaID ) PURE;
		//暂停接收用户数据
		STDMETHOD( PauseRecvMedia )( THIS_ FS_UINT32 dwRemoteUserID,BYTE bMediaType,BYTE bMediaID,BOOL bPause ) PURE;

		//回调用户视频数据
		//dwUserID等于0时,表示回调所有数据
		//当pSink为空时,表示停止回调该用户数据
		STDMETHOD( SetDataSink )( THIS_ FS_UINT32 dwUserID,FS_UINT dwUserData,BYTE bMediaType,BYTE bMediaID,IMediaDataSink *pSink ) PURE;

		//获取合成用户ID
		STDMETHOD( GetMixerUserID )( THIS_ FS_UINT32& dwMixerUserID) PURE;

		STDMETHOD( GetQosState)( THIS_ MULTIAV_QOSSTATE* pState ) PURE;

		STDMETHOD( EnableReuseUdpPort )( THIS_ BOOL bEnable ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif
