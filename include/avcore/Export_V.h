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
//��Ƶ���ʼ��,�ڵ������з���֮ǰ����
//
#if defined(_FS_OS_IOS)
BOOL		WVideo_Initialize( HMODULE hModule,LogPrintW pLogFun );
#else
BOOL		WVideo_Initialize( HMODULE hModule,LogPrintT pLogFun );
#endif

//
//�ͷ���Ƶ��
//
VOID		WVideo_Release();

//
//��Ƶ���봦�����ӿ�
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
//��ȡϵͳ��֧�ֵ�ѹ��������
//--------------------
int			WVideo_CapDS_GetEncoderCount();

//--------------------
//��ȡѹ����������
//--------------------
FS_UINT		WVideo_CapDS_GetEncoderInfo( int nEncoderIndex,WCHAR *wszName,UINT unSize,int& nEncoderID );

//--------------------
//��ȡϵͳ��Ƶ�ɼ��豸�ĸ���
//--------------------
UINT		WVideo_CapDS_GetDevicesCount();

//---------------------
//��ȡ��Ƶ�ɼ��豸������
//----------------------
UINT		WVideo_CapDS_GetDeviceInfo( UINT unID,WCHAR *wszName,UINT unSize );
//---------------------
//��ȡ��Ƶ�ɼ��豸��������Ϣ
//----------------------
UINT		WVideo_CapDS_GetDeviceInfo(VideoCapDeviceInfo *pCapDevInfo, UINT uSize);
//-----------------------
//������Ƶ�豸
//-----------------------
HANDLE		WVideo_CapDS_Create(const Video_CapEnc_Param &param,LPVOID lpObj,VideoCapCallBack compDataCallBack);


//------------------------
//�����Ƿ�ص���Ƶ����,Ĭ�ϲ��ص�����
//-----------------------
VOID		WVideo_CapDS_EnableDataCallback( HANDLE hCapture,BOOL bEnable );

//------------------------
//���ò���
//----------------------------
BOOL		WVideo_CapDS_SetParam( HANDLE hCapture,const Video_CapEnc_Param &param );

//��ȡ����
BOOL		WVideo_CapDS_GetParam( HANDLE hCapture,Video_CapEnc_Param &param );

//------------------------
//��ʾ�豸���ԶԻ���
//-----------------------
VOID		WVideo_CapDS_ShowPropertyPage( HANDLE  hCapture,HWND hWndOwner );

//------------------------
//��ʾ�豸��ʽ�Ի���
//-------------------------
VOID		WVideo_CapDS_ShowConfigPage( HANDLE hCapture,HWND hWndOwner );

//------------------------
//��ʾ�豸��Ƶ����Ի���
//-------------------------
VOID		WVideo_CapDS_ShowCrossbar( HANDLE hCapture,HWND hWndOwner );


//-----------------------
//��ȡ��ǰ��Ƶ�豸������Դ����
//------------------------
UINT		WVideo_CapDS_GetInputCount( HANDLE  hCapture );

//------------------------
//��ȡ��ǰ�豸����ƵԴ����
//------------------------
UINT		WVideo_CapDS_GetInputInfo( HANDLE hCapture,UINT unIndex,WCHAR *wszName,UINT  unSize,LONG& nInputType);

//
//������Ƶ���������
//
BOOL		WVideo_CapDS_SetVideoInput( HANDLE hCapture,UINT nIndex,LONG lType,BOOL bInputByIndex );

//���ͼ���ɫ�ʿռ�
BOOL		WVideo_CapDS_GetVideoColor(HANDLE hCapture, int nColorType, long &lValue);

//����ͼ���ɫ��
BOOL		WVideo_CapDS_SetVideoColor(HANDLE hCapture, int nColorType, long lValue);

//������Render����������Ƶ�ɼ��豸�����
//���յ�hRenderManager����,�������
BOOL		WVideo_CapDS_Attach( HANDLE hCapture,HANDLE hRenderManager );

//����Ĭ�ϲ���������Ļ
VOID		WVideo_CapDS_SetText( HANDLE hCapture,const WCHAR *wszText );

//�ڱ�����Ƶ���ֵ�����Ļ
//dwColor		������ɫ
//nNum			�����С��ͼ��߶ȱ�������
//nDen			�����С��ͼ��߶ȱ�����ĸ
//xPos			����λ��X����,Ϊ��ʱ��ʾ���������ͼ����ߵ����ؾ���,Ϊ��ʱ��ʾ�����ұ���ͼ���ұߵ����ؾ���
//yPos			����λ��Y����,Ϊ��ʱ��ʾ�����ϱ���ͼ���ϱߵ����ؾ���,Ϊ��ʱ��ʾ�����±���ͼ���±ߵ����ؾ���
VOID		WVideo_CapDS_SetText2( HANDLE hCapture,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

//nTextIndex	��������
VOID		WVideo_CapDS_SetText3( HANDLE hCapture,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

//--------------------
//д���ⲿ��Ƶ����
//--------------------
VOID		WVideo_CapDS_WriteVideoSample( HANDLE hCapture,double dblSampleTime, PBYTE pbBuffer, long lBufferSize );


BOOL		WVideo_CapDS_AdjustVideoParamByWndSize( HANDLE hCapture,WORD wWndWidth,WORD wWndHeight );

//-----------------------
//�ر��豸�ɼ�����
//------------------------
VOID		WVideo_CapDS_Destroy(HANDLE& hCapture);

//��������Render������
HANDLE		WVideo_CapRender_CreateManager();

//�رձ���Render������
VOID		WVideo_CapRender_DestroyManager( HANDLE hRenderManager );

//------------------------
//��������Render
//------------------------
DWORD		WVideo_CapRender_AddRender(HANDLE hRenderManager, HWND hWnd,const WBASE_NOTIFY& Notify );

//-----------------------
//�رձ���Render
//-----------------------
VOID		WVideo_CapRender_RemoveRender(HANDLE hRenderManager,DWORD dwRenderID );

//-----------------------
//�Ƿ���ʾͼ��
//-----------------------
BOOL		WVideo_CapRender_Show( HANDLE hRenderManager,DWORD dwRenderID,BOOL bShow );

//-----------------------
//���ñ���ͼ�󴰿���ʾ����
//-----------------------
BOOL		WVideo_CapRender_SetRenderPos( HANDLE hRenderManager,DWORD dwRenderID,const RECT &rect );

//-----------------------
//����ͼ������ʾ������
//------------------------
BOOL		WVideo_CapRender_ShowText( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText );

BOOL		WVideo_CapRender_ShowText2( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

BOOL		WVideo_CapRender_ShowText3( HANDLE hRenderManager,DWORD dwRenderID,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );
//------------------------
//ץȡ����ͼ��
//-------------------------
BOOL		WVideo_CapRender_SavePicture( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *lpszFilePath );

//��ȡRender״̬
BOOL		WVideo_CapRender_GetState( HANDLE hRenderManager,DWORD dwRenderID,VideoRender_State& state );

//����������ʱ����
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
//����Render
//-------------------------
DWORD 		WVideo_Render_AddRender( HANDLE hRenderManager,HWND    hWnd,const WBASE_NOTIFY& Notify );

BOOL 		WVideo_Render_SetSyncTime( HANDLE hRenderManager,DWORD dwRenderID,IPlaySyncTime* pSyncTime );

//-----------------------
//��Render д������
//------------------------
BOOL		WVideo_Render_Write( HANDLE hRenderManager,DWORD dwRenderID,PBYTE pbData,DWORD dwDataLen );

//
//��ȡReader���һ֡����
//
BOOL		WVideo_Render_ReadLastFrame( HANDLE hRenderManager,DWORD dwRenderID,PBYTE pbBuffer,FS_UINT32& dwSize );

//------------------------
//������Ƶ�ڴ����е���ʾλ��
//------------------------
BOOL		WVideo_Render_SetRenderPos( HANDLE hRenderManager,DWORD dwRenderID,const RECT &rcDraw);

//-------------------------
//�����Ƿ���ʾ��Ƶ,Ĭ������ʾ��
//-------------------------
BOOL		WVideo_Render_Show( HANDLE hRenderManager,DWORD dwRenderID,BOOL bEnable );

//-------------------------
//��������Ƶ���Ƿ���ʾ����
//-------------------------
BOOL   		WVideo_Render_ShowText( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText );

BOOL		WVideo_Render_ShowText2( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

BOOL		WVideo_Render_ShowText3( HANDLE hRenderManager,DWORD dwRenderID,int nTextIndex,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );

//-------------------------
//����������ʱ����
//-------------------------
BOOL   		WVideo_Render_OnDraw( HANDLE hRenderManager,DWORD dwRenderID );

//��ȡRender״̬
BOOL		WVideo_Render_GetState( HANDLE hRenderManager,DWORD dwRenderID,VideoRender_State& state );

//------------------------
//ץȡͼ��
//-------------------------
BOOL		WVideo_Render_SavePicture( HANDLE hRenderManager,DWORD dwRenderID,const WCHAR *lpszFilePath );

BOOL		WVideo_Render_SetDisplayMode( HANDLE hRenderManager,DWORD dwRenderID,int nMode );

//-------------------------
//�ر�Render ���
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
//��Ƶ���ֵ��ӹ�����
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

//��Ƶ������
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

//֡���ʿ�����
HANDLE		WVideo_FrameRateCtl_Create();

VOID		WVideo_FrameRateCtl_SetFrameRate( HANDLE hCtl,int nFrameRate );

BOOL		WVideo_FrameRateCtl_RateControl( HANDLE hCtl );

VOID		WVideo_FrameRateCtl_Destroy( HANDLE hCtl );

//��ȷ֡���ʿ�����
HANDLE		WVideo_PreciseFrameRateCtl_Create();

VOID		WVideo_PreciseFrameRateCtl_SetFrameRate( HANDLE hCtl,int nFrameRate );

BOOL		WVideo_PreciseFrameRateCtl_RateControl( HANDLE hCtl );

VOID		WVideo_PreciseFrameRateCtl_Destroy( HANDLE hCtl );

#endif