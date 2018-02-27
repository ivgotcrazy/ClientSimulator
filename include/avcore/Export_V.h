#ifndef __EXPORT_WVIDEO_H__
#define __EXPORT_WVIDEO_H__
 
#include "VideoDefine.h"
#include "wbasetype.h"
#include "IPlaySyncTime.h"

#if (defined UNICODE) || (defined _UNICODE)
	typedef LogPrintW LogPrintT;
#else
	typedef LogPrintA LogPrintT;
#endif

//
//视频库初始化,在调用所有方法之前调用
//
#if defined(_FS_OS_IOS)
BOOL		WVideo_Initialize( HMODULE hModule,LogPrintW pLogFun );
#else
BOOL		WVideo_Initialize( HMODULE hModule,LogPrintT pLogFun );
#endif

//
//释放视频库
//
VOID		WVideo_Release();

//
//视频编码处理器接口
//
HANDLE		WVideo_EncProcessor_Create();

VOID		WVideo_EncProcessor_Destroy( HANDLE hProcessor );

BOOL		WVideo_EncProcessor_SetParam( HANDLE hProcessor,const BITMAPINFOHEADER& bmiIn,const Video_Encoder_Param& param );

BOOL		WVideo_EncProcessor_Process( HANDLE hProcessor,Video_Code_Frame& frame );

/////////////////////////////////////////////////////////////////////
// Video Capture function
////////////////////////////////////////////////////////////////////
//DirectShow Capture

//---------------------
//获取系统可支持的压缩器个数
//--------------------
int			WVideo_CapDS_GetEncoderCount();

//--------------------
//获取压缩器的名称
//--------------------
FS_UINT		WVideo_CapDS_GetEncoderInfo( int nEncoderIndex,WCHAR *wszName,UINT unSize,int& nEncoderID );

//--------------------
//获取系统视频采集设备的个数
//--------------------
UINT		WVideo_CapDS_GetDevicesCount();

//---------------------
//获取视频采集设备的名称
//----------------------
UINT		WVideo_CapDS_GetDeviceInfo( UINT unID,WCHAR *wszName,UINT unSize );
//---------------------
//获取视频采集设备的完整信息
//----------------------
UINT		WVideo_CapDS_GetDeviceInfo(VideoCapDeviceInfo *pCapDevInfo, UINT uSize);
//-----------------------
//启动视频设备
//-----------------------
HANDLE		WVideo_CapDS_Create(const Video_CapEnc_Param &param,LPVOID lpObj,VideoCapCallBack compDataCallBack);


//------------------------
//设置是否回调视频数据,默认不回调数据
//-----------------------
VOID		WVideo_CapDS_EnableDataCallback( HANDLE hCapture,BOOL bEnable );

//------------------------
//设置参数
//----------------------------
BOOL		WVideo_CapDS_SetParam( HANDLE hCapture,const Video_CapEnc_Param &param );

//获取参数
BOOL		WVideo_CapDS_GetParam( HANDLE hCapture,Video_CapEnc_Param &param );

//------------------------
//显示设备属性对话框
//-----------------------
VOID		WVideo_CapDS_ShowPropertyPage( HANDLE  hCapture,HWND hWndOwner );

//------------------------
//显示设备格式对话框
//-------------------------
VOID		WVideo_CapDS_ShowConfigPage( HANDLE hCapture,HWND hWndOwner );

//------------------------
//显示设备视频输入对话框
//-------------------------
VOID		WVideo_CapDS_ShowCrossbar( HANDLE hCapture,HWND hWndOwner );


//-----------------------
//获取当前视频设备的输入源个数
//------------------------
UINT		WVideo_CapDS_GetInputCount( HANDLE  hCapture );

//------------------------
//获取当前设备的视频源名称
//------------------------
UINT		WVideo_CapDS_GetInputInfo( HANDLE hCapture,UINT unIndex,WCHAR *wszName,UINT  unSize,LONG& nInputType);

//
//设置视频的输入端子
//
BOOL		WVideo_CapDS_SetVideoInput( HANDLE hCapture,UINT nIndex,LONG lType,BOOL bInputByIndex );

//获得图象的色彩空间
BOOL		WVideo_CapDS_GetVideoColor(HANDLE hCapture, int nColorType, long &lValue);

//设置图象的色彩
BOOL		WVideo_CapDS_SetVideoColor(HANDLE hCapture, int nColorType, long lValue);

//将本地Render管理器与视频采集设备句柄绑定
//传空的hRenderManager参数,将解除绑定
BOOL		WVideo_CapDS_Attach( HANDLE hCapture,HANDLE hRenderManager );

//采用默认参数叠加字幕
VOID		WVideo_CapDS_SetText( HANDLE hCapture,const WCHAR *wszText );

//在本地视频上又叠加字幕
//dwColor		文字颜色
//nNum			字体大小与图象高度比例分子
//nDen			字体大小与图象高度比例分母
//xPos			文字位置X坐标,为正时表示文字左边与图象左边的像素距离,为负时表示文字右边与图象右边的像素距离
//yPos			文字位置Y坐标,为正时表示文字上边与图象上边的像素距离,为负时表示文字下边与图像下边的像素距离
VOID		WVideo_CapDS_SetText2( HANDLE hCapture,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

//nTextIndex	文字索引
VOID		WVideo_CapDS_SetText3( HANDLE hCapture,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

//--------------------
//写入外部视频数据
//--------------------
VOID		WVideo_CapDS_WriteVideoSample( HANDLE hCapture,double dblSampleTime, PBYTE pbBuffer, long lBufferSize );


BOOL		WVideo_CapDS_AdjustVideoParamByWndSize( HANDLE hCapture,WORD wWndWidth,WORD wWndHeight );

//-----------------------
//关闭设备采集对象
//------------------------
VOID		WVideo_CapDS_Destroy(HANDLE& hCapture);

//创建本地Render管理器
HANDLE		WVideo_CapRender_CreateManager();

//关闭本地Render管理器
VOID		WVideo_CapRender_DestroyManager( HANDLE hRenderManager );

//------------------------
//创建本地Render
//------------------------
DWORD		WVideo_CapRender_AddRender(HANDLE hRenderManager, HWND hWnd,const WBASE_NOTIFY& Notify );

//-----------------------
//关闭本地Render
//-----------------------
VOID		WVideo_CapRender_RemoveRender(HANDLE hRenderManager,DWORD dwRenderID );

//-----------------------
//是否显示图象
//-----------------------
BOOL		WVideo_CapRender_Show( HANDLE hRenderManager,DWORD dwRenderID,BOOL bShow );

//-----------------------
//设置本地图象窗口显示区域
//-----------------------
BOOL		WVideo_CapRender_SetRenderPos( HANDLE hRenderManager,DWORD dwRenderID,const RECT &rect );

//-----------------------
//设置图象上显示的文字
//------------------------
BOOL		WVideo_CapRender_ShowText( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText );

BOOL		WVideo_CapRender_ShowText2( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

BOOL		WVideo_CapRender_ShowText3( HANDLE hRenderManager,DWORD dwRenderID,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );
//------------------------
//抓取本地图象
//-------------------------
BOOL		WVideo_CapRender_SavePicture( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *lpszFilePath );

//获取Render状态
BOOL		WVideo_CapRender_GetState( HANDLE hRenderManager,DWORD dwRenderID,VideoRender_State& state );

//当背景擦除时调用
BOOL   		WVideo_CapRender_OnDraw( HANDLE hRenderManager,DWORD dwRenderID );

BOOL		WVideo_CapRender_SetDisplayMode( HANDLE hRenderManager,DWORD dwRenderID,int nMode );

VOID		WVideo_CapRender_Clear( HANDLE hRenderManager );

VOID		WVideo_CapRender_SetFormat( HANDLE hRenderManager,const BITMAPINFOHEADER &biIn );

VOID		WVideo_CapRender_WriteData( HANDLE hRenderManager,PBYTE pbData,UINT unDataLen );

INT			WVideo_CapRender_GetCount( HANDLE hRenderManager );

VOID		WVideo_CapRender_SetRawDataCallback( HANDLE hRenderManager,DWORD dwRenderID,LPVOID lpObj,VideoRawDataCallBack callback );

VOID		WVideo_CapRender_SetRenderWnd( HANDLE hRenderManager,DWORD dwRenderID,HWND hWnd );

BOOL		WVideo_CapRender_GetRenderPos( HANDLE hRenderManager,DWORD dwRenderID,RECT &rect );

/////////////////////////////////////////////////////////////////////
// Video Render function
////////////////////////////////////////////////////////////////////

HANDLE		WVideo_Render_CreateManager();

VOID		WVideo_Render_DestroyManager( HANDLE hRenderManager );
//-------------------------
//创建Render
//-------------------------
DWORD 		WVideo_Render_AddRender( HANDLE hRenderManager,HWND    hWnd,const WBASE_NOTIFY& Notify );

BOOL 		WVideo_Render_SetSyncTime( HANDLE hRenderManager,DWORD dwRenderID,IPlaySyncTime* pSyncTime );

//-----------------------
//向Render 写入数据
//------------------------
BOOL		WVideo_Render_Write( HANDLE hRenderManager,DWORD dwRenderID,PBYTE pbData,DWORD dwDataLen );

//
//读取Reader最后一帧数据
//
BOOL		WVideo_Render_ReadLastFrame( HANDLE hRenderManager,DWORD dwRenderID,PBYTE pbBuffer,FS_UINT32& dwSize );

//------------------------
//设置视频在窗口中的显示位置
//------------------------
BOOL		WVideo_Render_SetRenderPos( HANDLE hRenderManager,DWORD dwRenderID,const RECT &rcDraw);

//-------------------------
//设置是否显示视频,默认是显示的
//-------------------------
BOOL		WVideo_Render_Show( HANDLE hRenderManager,DWORD dwRenderID,BOOL bEnable );

//-------------------------
//设置在视频上是否显示文字
//-------------------------
BOOL   		WVideo_Render_ShowText( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText );

BOOL		WVideo_Render_ShowText2( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

BOOL		WVideo_Render_ShowText3( HANDLE hRenderManager,DWORD dwRenderID,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

//-------------------------
//当背景擦除时调用
//-------------------------
BOOL   		WVideo_Render_OnDraw( HANDLE hRenderManager,DWORD dwRenderID );

//获取Render状态
BOOL		WVideo_Render_GetState( HANDLE hRenderManager,DWORD dwRenderID,VideoRender_State& state );

//------------------------
//抓取图象
//-------------------------
BOOL		WVideo_Render_SavePicture( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *lpszFilePath );

BOOL		WVideo_Render_SetDisplayMode( HANDLE hRenderManager,DWORD dwRenderID,int nMode );

//-------------------------
//关闭Render 句柄
//-------------------------
BOOL		WVideo_Render_RemoveRender( HANDLE hRenderManager,DWORD dwRenderID );

VOID		WVideo_Render_Clear( HANDLE hRenderManager );

#if defined _FS_OS_IOS || defined _FS_OS_ANDROID
VOID        WVideo_Render_Pause( HANDLE hRenderManager, FS_UINT32 dwRenderID, BOOL bPause );
#endif

INT			WVideo_Render_GetCount( HANDLE hRenderManager );

VOID		WVideo_Render_SetRawDataCallback( HANDLE hRenderManager,DWORD dwRenderID,LPVOID lpObj,VideoRawDataCallBack callback );

VOID		WVideo_Render_SetRenderWnd( HANDLE hRenderManager,DWORD dwRenderID,HWND hWnd );

BOOL		WVideo_Render_GetRenderPos( HANDLE hRenderManager,DWORD dwRenderID,RECT &rcDraw);

BOOL		WVideo_Render_GetRenderWinPos( HANDLE hRenderManager,DWORD dwRenderID,RECT &rcDraw);

//
//视频文字叠加管理器
//
HANDLE		WVideo_TextWriter_CreateManager();

void		WVideo_TextWriter_DestroyManager( HANDLE hTextManager );

FS_INT			WVideo_TextWriter_GetTextCount( HANDLE hTextManager );

void		WVideo_TextWriter_WriteText( HANDLE hTextManager,PBYTE pbData,int nStride );

void		WVideo_TextWriter_SetVideoFormat( HANDLE hTextManager,const BITMAPINFOHEADER& bmiIn );

void		WVideo_TextWriter_SetText3( HANDLE hTextManager,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

void		WVideo_TextWriter_SetText2( HANDLE hTextManager,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

void		WVideo_TextWriter_SetText( HANDLE hTextManager,const WCHAR *wszText );

void		WVideo_TextWriter_ClearText( HANDLE hTextManager );

BOOL		WVideo_TextWriter_IsSupportFormat( const BITMAPINFOHEADER& bmpIn,BITMAPINFOHEADER *pbiOut = NULL );

//视频处理器
HANDLE		WVideo_Processor_Create( LPVOID lpObj,VideoCapCallBack compDataCallBack);

VOID		WVideo_Processor_EnableDataCallback( HANDLE hProcessor,BOOL bEnable );

BOOL		WVideo_Processor_SetParam( HANDLE hProcessor,const BITMAPINFOHEADER& bmiIn,int nFrameRate,BOOL bDenoise,BOOL bDeinterface,BOOL bVFlip,const Video_Encoder_Param& param );

BOOL		WVideo_Processor_Attach( HANDLE hProcessor,HANDLE hRenderManager );

VOID		WVideo_Processor_SetText( HANDLE hProcessor,const WCHAR *wszText );

VOID		WVideo_Processor_SetText2( HANDLE hProcessor,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

VOID		WVideo_Processor_SetText3( HANDLE hProcessor,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

VOID		WVideo_Processor_WriteVideoSample( HANDLE hProcessor,double dblSampleTime, PBYTE pbBuffer, long lBufferSize );

BOOL		WVideo_Processor_AdjustVideoParamByWndSize( HANDLE hProcessor,WORD wWndWidth,WORD wWndHeight );

VOID		WVideo_Processor_Destroy(HANDLE& hProcessor);

//帧速率控制器
HANDLE		WVideo_FrameRateCtl_Create();

VOID		WVideo_FrameRateCtl_SetFrameRate( HANDLE hCtl,int nFrameRate );

BOOL		WVideo_FrameRateCtl_RateControl( HANDLE hCtl );

VOID		WVideo_FrameRateCtl_Destroy( HANDLE hCtl );

//精确帧速率控制器
HANDLE		WVideo_PreciseFrameRateCtl_Create();

VOID		WVideo_PreciseFrameRateCtl_SetFrameRate( HANDLE hCtl,int nFrameRate );

BOOL		WVideo_PreciseFrameRateCtl_RateControl( HANDLE hCtl );

VOID		WVideo_PreciseFrameRateCtl_Destroy( HANDLE hCtl );

#endif