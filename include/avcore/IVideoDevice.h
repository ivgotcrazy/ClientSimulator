#ifndef __IVIDEO_DEVICE_H
#define __IVIDEO_DEVICE_H

#include "wcombase.h"
#include "VideoDefine.h"
#include "IVideoSource.h"
#include "IPlaySyncTime.h"

#ifdef __cplusplus
extern "C" {
#endif

	//VideoDevice Component's GUID
	// {01E61E19-F77F-40c3-9C03-0A4FBAAB6A6A}
	DEFINE_GUID( CLSID_VideoDevice, 
		0x1e61e19, 0xf77f, 0x40c3, 0x9c, 0x3, 0xa, 0x4f, 0xba, 0xab, 0x6a, 0x6a);

	//Video Render Manager Component's GUID
	// {03663AB5-FBFA-43d8-B16A-0FDF52BB9BB7}
	DEFINE_GUID( CLSID_VideoRenderManager, 
		0x3663ab5, 0xfbfa, 0x43d8, 0xb1, 0x6a, 0xf, 0xdf, 0x52, 0xbb, 0x9b, 0xb7);

	//IVideoDevice Interface's GUID
	// {180E0C5C-5987-4ee0-94CC-B7921044EFDC}
	DEFINE_GUID( IID_IVideoDevice, 
		0x180e0c5c, 0x5987, 0x4ee0, 0x94, 0xcc, 0xb7, 0x92, 0x10, 0x44, 0xef, 0xdc);
	
	//IVideoRenderManager Interface's GUID
	// {0BD30380-54BF-4c48-849B-DD410C63C9F1}
	DEFINE_GUID( IID_IVideoRenderManager, 
		0xbd30380, 0x54bf, 0x4c48, 0x84, 0x9b, 0xdd, 0x41, 0xc, 0x63, 0xc9, 0xf1);


	//----------------------------------------------------------------------------
	// IVideoDevice
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IVideoDevice, IUnknown)
	{
		//获取视频采集设备个数
		STDMETHOD_(int,GetCapDevicesCount)( THIS_ ) PURE;
		//获取视频采集设备名称
		STDMETHOD( GetCapDeviceInfo )( THIS_ int nDevIndex,WCHAR *wszName,UINT nSize ) PURE;
		//获取视频采集设备信息,uSize为传入的VideoCapDeviceInfo数组的长度，返回实际查询到的设备
        //数量，存在极低可能性此返回值与GetCapDevicesCount()的不同，此时可能需要重新调用此方法
        //以避免存在遗漏
        STDMETHOD_(int,GetCapDeviceInfo)(VideoCapDeviceInfo *pCapDevInfo, UINT uSize) PURE;
		//启动采集
		STDMETHOD( StartCapture )( THIS_ Video_CapEnc_Param *pParam ) PURE;
		//停止采集
		STDMETHOD( StopCapture )( THIS_ ) PURE;
		//设置视频数据回调接口
		STDMETHOD( AddDataSink )( THIS_ IVideoDataSink *pSink,FS_UINT dwUserData ) PURE;

		STDMETHOD( RemoveDataSink )( THIS_ IVideoDataSink *pSink ) PURE;
		//设置参数
		STDMETHOD( SetParam )( THIS_ const Video_CapEnc_Param *pParam ) PURE;
		//获取参数
		STDMETHOD( GetParam )( THIS_ Video_CapEnc_Param *pParam ) PURE;
		//显示属性对话框
		STDMETHOD( ShowPropertyPage )( THIS_ HWND hWndOwner ) PURE;
		//显示设备格式对话框
		STDMETHOD( ShowConfigPage )( THIS_ HWND hWndOwner ) PURE;
		//显示视频输入对话框
		STDMETHOD( ShowCrossbar )( THIS_ HWND hWndOwner ) PURE;
		//获取视频输入端子个数
		STDMETHOD_( int,GetVideoInputCount )( THIS_ ) PURE;
		//获取视频输入端子信息
		STDMETHOD( GetVideoInputInfo )( THIS_ int nInputIndex,WCHAR *wszInputName,UINT nSize,LONG *pInputType ) PURE;
		//获取图象色彩值
		STDMETHOD( GetVideoColor )( THIS_ int nColorType,long *pValue ) PURE;
		//设置图象色彩值
		STDMETHOD( SetVideoColor )( THIS_ int nColorType,LONG lValue ) PURE;
		//设置视频输入端子
		STDMETHOD( SetVideoInput )( THIS_ UINT nIndex,LONG lType,BOOL bInputByIndex ) PURE;
		//采用默认参数叠加字幕
		STDMETHOD( SetText )( THIS_ const WCHAR *wszText ) PURE;		
		//在本地视频上又叠加字幕
		//dwColor		文字颜色
		//nNum			字体大小与图象高度比例分子
		//nDen			字体大小与图象高度比例分母
		//xPos			文字位置X坐标,为正时表示文字左边与图象左边的像素距离,为负时表示文字右边与图象右边的像素距离
		//yPos			文字位置Y坐标,为正时表示文字上边与图象上边的像素距离,为负时表示文字下边与图像下边的像素距离
		STDMETHOD( SetText2 )( THIS_ const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;
		//nTextIndex	文字索引，可以显示多个文字
		STDMETHOD( SetText3 )( THIS_ int nTextIndex,const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;

		STDMETHOD( Enable )( THIS_ BOOL bEnable ) PURE;
		//写入视频数据
		STDMETHOD( WriteVideoSample )( THIS_ double dblSampleTime, PBYTE pbBuffer, long lBufferSize ) PURE;
		//根据远端显示窗口大小，调节视频参数
		STDMETHOD( AdjustVideoParamByWndSize )( THIS_ WORD wWndWidth,WORD wWndHeight ) PURE;
	};

	//----------------------------------------------------------------------------
	// IVideoRenderManager
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IVideoRenderManager, IUnknown)
	{
		//创建Render
		STDMETHOD_( FS_UINT32,AddRender)( THIS_ HWND hWnd,WBASE_NOTIFY *pNotify ) PURE;

		STDMETHOD( SetSyncTime )( THIS_ FS_UINT32 dwRenderID,IPlaySyncTime* pSyncTime ) PURE;
		//关闭Render
		STDMETHOD( RemoveRender )( THIS_ FS_UINT32 dwRenderID ) PURE;
		//向Render写入视频数据
		STDMETHOD( Write )( THIS_ FS_UINT32 dwRenderID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;
		//设置Render在窗口中的显示位置
		STDMETHOD( SetRenderPos )( THIS_ FS_UINT32 dwRenderID,RECT *pRect ) PURE;
		//是否显示视频
		STDMETHOD( Show )( THIS_ FS_UINT32 dwRenderID,BOOL bShow ) PURE;
		//在视频上显示文字
		STDMETHOD( ShowText )( THIS_ FS_UINT32 dwRenderID,const WCHAR *wszText ) PURE;
		//重绘视频
		STDMETHOD( OnDraw )( THIS_ FS_UINT32 dwRenderID ) PURE;
		//保存视频到指定文件
		STDMETHOD( SavePicture )( THIS_ FS_UINT32 dwRenderID,const WCHAR *wszFilePath ) PURE;
		//获取视频大小
		STDMETHOD( GetState )( THIS_ FS_UINT32 dwRenderID,VideoRender_State *pState ) PURE;
		//在视频上显示文字
		//dwColor		文字颜色
		//nNum			字体大小与图象高度比例分子
		//nDen			字体大小与图象高度比例分母
		//xPos			文字位置X坐标,为正时表示文字左边与图象左边的像素距离,为负时表示文字右边与图象右边的像素距离
		//yPos			文字位置Y坐标,为正时表示文字上边与图象上边的像素距离,为负时表示文字下边与图像下边的像素距离
		STDMETHOD( ShowText2 )( THIS_ FS_UINT32 dwRenderID,const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;

		STDMETHOD( ShowText3 )( THIS_ FS_UINT32 dwRenderID,int nTextIndex,const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;

		STDMETHOD( SetDisplayMode )( THIS_ FS_UINT32 dwRenderID,int nMode ) PURE;

		STDMETHOD( ReadLastFrame )( THIS_ FS_UINT32 dwRenderID,PBYTE pbBuffer,FS_UINT32* pdwSize ) PURE;
		//设置原始视频数据回调
		STDMETHOD( SetRawDataCallback )( THIS_ FS_UINT32 dwRenderID,LPVOID lpObj,VideoRawDataCallBack callback ) PURE;		
		//设置Render的窗口句柄
		STDMETHOD( SetRenderWnd )( THIS_ FS_UINT32 dwRenderID,HWND hWnd ) PURE;		
		//获取Render在窗口中的显示位置
		STDMETHOD( GetRenderPos )( THIS_ FS_UINT32 dwRenderID,RECT *pRect ) PURE;
        
#if defined _FS_OS_IOS || defined _FS_OS_ANDROID
        STDMETHOD( PauseRender )( THIS_ FS_UINT32 dwRenderID, BOOL bPause ) PURE;
#endif
		//获取Render所属窗口的区域
		STDMETHOD( GetRenderWinPos )( THIS_ FS_UINT32 dwRenderID,RECT *pRect ) PURE;
	};
		
#ifdef __cplusplus
}
#endif

#endif
