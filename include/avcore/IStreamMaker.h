#ifndef __IFMSTREAM_MAKER_H
#define __IFMSTREAM_MAKER_H

#include "wbasetype.h"
#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif

	// StreamMaker Component's GUID
	// {B2D7ADB2-C74D-4b84-94BA-36380D60A9CC}
	DEFINE_GUID(CLSID_StreamMaker, 
		0xb2d7adb2, 0xc74d, 0x4b84, 0x94, 0xba, 0x36, 0x38, 0xd, 0x60, 0xa9, 0xcc);
	
	// IStreamMaker Interface's GUID
	// {F5F473D3-5CD8-4d87-BC67-2410F5461CF3}
	DEFINE_GUID( IID_IStreamMaker, 
		0xf5f473d3, 0x5cd8, 0x4d87, 0xbc, 0x67, 0x24, 0x10, 0xf5, 0x46, 0x1c, 0xf3);

	typedef enum
	{
		STREAM_AUDIO = 0,
		STREAM_VIDEO
			
	}STM_STREAM_TYPE;

	typedef enum
	{	
		VIDEO_ENCODER_WMV1 = 0,
		VIDEO_ENCODER_WMV2,
		VIDEO_ENCODER_WMV3,
		VIDEO_ENCODER_MSS1,
		VIDEO_ENCODER_MSS2
			
	}VIDEO_ENCODER_TYPE;

	typedef enum
	{	
		AUDIO_ENCODER_WMAUDIO = 0,
		AUDIO_ENCODER_WMVOICE
			
	}AUDIO_ENCODER_TYPE;

	typedef enum
	{	
		OnePassCBR = 0,
		TwoPassCBR,
		OnePassVBR,
		TwoPassVBR,
		PeakConstrainedTwoPassVBR		
	}VIDEO_ENCODER_MODE;

	typedef struct
	{	
		WORD	wWidth;
		WORD    wHeight;
		WORD	wFrameRate;			//fps
		WORD    wBitCount;			//
		DWORD   dwCompression;		//fourcc
		
		WORD    wEncoderType;
		WORD    wEncoderMode;		//see VIDEO_ENCODER_MODE define
		WORD    wKeyFrameInterval;	//s
		WORD	wQuality;			//0-100
		WORD    wVBRQuality;		//0-100
		DWORD   dwBitrate;			//bps	
		
	}VIDEO_ENCODER_PARAM;

	typedef struct
	{	
		WORD			wEncoderType;
		DWORD			dwBitrate;
		BOOL			bIsVBR;
		DWORD			dwVBRQuality;
		
		WAVEFORMATEX	wfxIn;
		
	}AUDIO_ENCODER_PARAM;

	//pbData为0时,dwDataLen返回状态,0播放完成,1出错
	typedef HRESULT	 (*STREAMCALLBACK)(DWORD dwTimeStamp,WORD wDuration,PBYTE pbData, DWORD dwDataLen, FS_UINT dwUserData);

	typedef struct
	{
		AUDIO_ENCODER_PARAM  AudioParam;
		VIDEO_ENCODER_PARAM  VideoParam;
		
		BOOL				 bHasAudio;
		BOOL				 bHasVideo;
		
	}STREAM_ENCODER_PARAM;

	#ifndef QWORD
#ifdef _FS_OS_MAC
    typedef uint64_t QWORD;
#else
    
	typedef unsigned __int64 QWORD;
#endif
	#endif

	//
	//IStreamCallback
	//
	DECLARE_INTERFACE( IStreamCallback )
	{
		//pbData为0时,dwDataLen返回状态,0播放完成,1出错
		STDMETHOD( OnStreamCallback )(DWORD dwTimeStamp,FS_UINT16 wDuration,PBYTE pbData, DWORD dwDataLen, FS_UINT dwUserData);
	};

	//----------------------------------------------------------------------------
	// IStreamMaker
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IStreamMaker, IUnknown)
	{
		STDMETHOD( OpenURL )( THIS_ WCHAR *wszUrl,IStreamCallback* pCallback,FS_UINT dwUserData ) PURE;

		STDMETHOD( OpenRaw )( THIS_ STREAM_ENCODER_PARAM *pParam,IStreamCallback* pCallback,FS_UINT dwUserData ) PURE;

		STDMETHOD( Close )( THIS_ ) PURE;

		STDMETHOD( SetOutputFileName )( THIS_ WCHAR *wszFileName ) PURE;

		STDMETHOD( SetMediaServer )( THIS_ DWORD dwPort,WCHAR *wszUrl,DWORD dwSize ) PURE;

		STDMETHOD( PushToMediaServer )( THIS_ WCHAR *wszURL,WCHAR* wszUserName,WCHAR* wszPassword ) PURE;

		STDMETHOD( GetStreamHeader )( THIS_ PBYTE pbBuffer,DWORD *pdwSize ) PURE;

		STDMETHOD( WriteStreamSample )( THIS_ BYTE bStreamType,QWORD qwSampleTime,PBYTE pbData,DWORD dwDataLen ) PURE;

		STDMETHOD( GetBitrate )( THIS_ DWORD* pdwMaxBitrate,DWORD* pdwAvgBitrate ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif