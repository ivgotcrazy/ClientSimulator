#ifndef __IMEDIA_GRABER_H
#define __IMEDIA_GRABER_H

#include "wcombase.h"
#include "IAudioSource.h"
#include "IVideoSource.h"
#ifdef _WIN32
#include "mmsystem.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	typedef  VOID ( *MEDIACALLBACK) (
		FS_UINT dwUserData,
		double dbSampleTime,
		PBYTE	pbBuffer,
		LONG	lDataLen );

	typedef enum
	{	
		Media_Play = 0,	//播放
		Media_Pause,	//暂停
		Media_Stop		//停止		
	}WMEDIASTATUS;

	//VTMediaPlay 的控制类型
	typedef enum
	{
		MEDIA_SET_STATUS = 0,		//设置播放状态
		MEDIA_GET_STATUS,			//获取播放状态
		MEDIA_SET_WNDPOS,			//设置视频播放位置
		MEDIA_SET_POS,				//设置当前播放时间位置
		MEDIA_GET_POS,				//获取当前播放时间位置
		MEDIA_SET_VOLUME,			//设置当前音量
		MEDIA_GET_VOLUME,			//获取当前音量
		MEDIA_SET_BALANCE,			//设置左右音量平衡
		MEDIA_GET_BALANCE,			//获取左右音量平衡

	}WMEDIACONTROLTYPE;

	//媒体通知消息返回参数,wParam定义如下,lParam暂无定义
	#define	WMEDIA_EC_COMPLETE		0x0001		//媒体文件播放完成	

	typedef struct{

		HWND				hMovieWnd;			//[IN] 播放窗口句柄
		RECT                rcMovieWnd;			//[IN] 播放位置
		HWND				hNotifyWnd;			//[IN] 消息通知窗口句柄
		ULONG               lNotifyMsg;			//[IN] 自定义媒体通知消息

		double				dbTotalTime;		//[OUT]文件播放总时间,单位称秒
		double              dbVideoRate;		//[OUT]视频播放速率
		BOOL				bHasVideo;			//[OUT]是否有视频
		BOOL				bHasAudio;			//[OUT]是否有音频

		WAVEFORMATEX		wfxAudio;			//[OUT]音频格式
		BITMAPINFOHEADER	bmiVideo;			//[OUT]视频模式
		FS_UINT             dwUserData;			//[IN] 用户自定义数据,用于数据回调
		MEDIACALLBACK       AudioCallback;		//[IN] 音频数据回调函数
		MEDIACALLBACK		VideoCallback;		//[IN] 视频数据回调函数

		WMEDIASTATUS		MediaStaus;			//[IN][OUT]	播放状态
		double              dbCurTime;			//[IN][OUT] 当前播放时间位置
		LONG                lVolume;			//[IN][OUT] 声音音量(Full volume is 0, and –10,000 is silence)
		LONG				lBalance;			//[IN][OUT] 左右音量平衡(The value can range from -10,000 to 10,000. 
												//		    The value -10,000 means the right channel is attenuated by 100 dB and is effectively silent. 
												//			The value 10,000 means the left channel is silent. 
												//			The neutral value is 0, which means that both channels are at full volume.
												//			When one channel is attenuated, the other remains at full volume		

		BOOL				bVideoResize;		//是否对视频自动缩放
	}WMEDIAINFO;

	// MediaGraber Component's GUID
	// {987C257D-0157-4923-9B68-3C7C1864AB5F}
	DEFINE_GUID( CLSID_MediaGraber, 
		0x987c257d, 0x157, 0x4923, 0x9b, 0x68, 0x3c, 0x7c, 0x18, 0x64, 0xab, 0x5f);

	// IMediaGraber Interface's GUID
	// {00839B82-9115-4b9d-987C-1408F7AECEC8}
	DEFINE_GUID( IID_IMediaGraber, 
		0x839b82, 0x9115, 0x4b9d, 0x98, 0x7c, 0x14, 0x8, 0xf7, 0xae, 0xce, 0xc8);
	
	//----------------------------------------------------------------------------
	// IMediaGraber
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IMediaGraber, IUnknown)
	{
		STDMETHOD( MediaOpen )( THIS_ WCHAR* wszFilePath,WMEDIAINFO* pMediaInfo ) PURE;

		STDMETHOD( MediaControl )( THIS_ WMEDIAINFO* pMediaInfo,WMEDIACONTROLTYPE ControlType ) PURE;

		STDMETHOD( MediaClose )( THIS_ ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif