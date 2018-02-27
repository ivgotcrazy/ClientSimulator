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
		//��ȡ��Ƶ�ɼ��豸����
		STDMETHOD_(int,GetCapDevicesCount)( THIS_ ) PURE;
		//��ȡ��Ƶ�ɼ��豸����
		STDMETHOD( GetCapDeviceInfo )( THIS_ int nDevIndex,WCHAR *wszName,UINT nSize ) PURE;
		//��ȡ��Ƶ�ɼ��豸��Ϣ,uSizeΪ�����VideoCapDeviceInfo����ĳ��ȣ�����ʵ�ʲ�ѯ�����豸
        //���������ڼ��Ϳ����Դ˷���ֵ��GetCapDevicesCount()�Ĳ�ͬ����ʱ������Ҫ���µ��ô˷���
        //�Ա��������©
        STDMETHOD_(int,GetCapDeviceInfo)(VideoCapDeviceInfo *pCapDevInfo, UINT uSize) PURE;
		//�����ɼ�
		STDMETHOD( StartCapture )( THIS_ Video_CapEnc_Param *pParam ) PURE;
		//ֹͣ�ɼ�
		STDMETHOD( StopCapture )( THIS_ ) PURE;
		//������Ƶ���ݻص��ӿ�
		STDMETHOD( AddDataSink )( THIS_ IVideoDataSink *pSink,FS_UINT dwUserData ) PURE;

		STDMETHOD( RemoveDataSink )( THIS_ IVideoDataSink *pSink ) PURE;
		//���ò���
		STDMETHOD( SetParam )( THIS_ const Video_CapEnc_Param *pParam ) PURE;
		//��ȡ����
		STDMETHOD( GetParam )( THIS_ Video_CapEnc_Param *pParam ) PURE;
		//��ʾ���ԶԻ���
		STDMETHOD( ShowPropertyPage )( THIS_ HWND hWndOwner ) PURE;
		//��ʾ�豸��ʽ�Ի���
		STDMETHOD( ShowConfigPage )( THIS_ HWND hWndOwner ) PURE;
		//��ʾ��Ƶ����Ի���
		STDMETHOD( ShowCrossbar )( THIS_ HWND hWndOwner ) PURE;
		//��ȡ��Ƶ������Ӹ���
		STDMETHOD_( int,GetVideoInputCount )( THIS_ ) PURE;
		//��ȡ��Ƶ���������Ϣ
		STDMETHOD( GetVideoInputInfo )( THIS_ int nInputIndex,WCHAR *wszInputName,UINT nSize,LONG *pInputType ) PURE;
		//��ȡͼ��ɫ��ֵ
		STDMETHOD( GetVideoColor )( THIS_ int nColorType,long *pValue ) PURE;
		//����ͼ��ɫ��ֵ
		STDMETHOD( SetVideoColor )( THIS_ int nColorType,LONG lValue ) PURE;
		//������Ƶ�������
		STDMETHOD( SetVideoInput )( THIS_ UINT nIndex,LONG lType,BOOL bInputByIndex ) PURE;
		//����Ĭ�ϲ���������Ļ
		STDMETHOD( SetText )( THIS_ const WCHAR *wszText ) PURE;		
		//�ڱ�����Ƶ���ֵ�����Ļ
		//dwColor		������ɫ
		//nNum			�����С��ͼ��߶ȱ�������
		//nDen			�����С��ͼ��߶ȱ�����ĸ
		//xPos			����λ��X����,Ϊ��ʱ��ʾ���������ͼ����ߵ����ؾ���,Ϊ��ʱ��ʾ�����ұ���ͼ���ұߵ����ؾ���
		//yPos			����λ��Y����,Ϊ��ʱ��ʾ�����ϱ���ͼ���ϱߵ����ؾ���,Ϊ��ʱ��ʾ�����±���ͼ���±ߵ����ؾ���
		STDMETHOD( SetText2 )( THIS_ const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;
		//nTextIndex	����������������ʾ�������
		STDMETHOD( SetText3 )( THIS_ int nTextIndex,const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;

		STDMETHOD( Enable )( THIS_ BOOL bEnable ) PURE;
		//д����Ƶ����
		STDMETHOD( WriteVideoSample )( THIS_ double dblSampleTime, PBYTE pbBuffer, long lBufferSize ) PURE;
		//����Զ����ʾ���ڴ�С��������Ƶ����
		STDMETHOD( AdjustVideoParamByWndSize )( THIS_ WORD wWndWidth,WORD wWndHeight ) PURE;
	};

	//----------------------------------------------------------------------------
	// IVideoRenderManager
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IVideoRenderManager, IUnknown)
	{
		//����Render
		STDMETHOD_( FS_UINT32,AddRender)( THIS_ HWND hWnd,WBASE_NOTIFY *pNotify ) PURE;

		STDMETHOD( SetSyncTime )( THIS_ FS_UINT32 dwRenderID,IPlaySyncTime* pSyncTime ) PURE;
		//�ر�Render
		STDMETHOD( RemoveRender )( THIS_ FS_UINT32 dwRenderID ) PURE;
		//��Renderд����Ƶ����
		STDMETHOD( Write )( THIS_ FS_UINT32 dwRenderID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;
		//����Render�ڴ����е���ʾλ��
		STDMETHOD( SetRenderPos )( THIS_ FS_UINT32 dwRenderID,RECT *pRect ) PURE;
		//�Ƿ���ʾ��Ƶ
		STDMETHOD( Show )( THIS_ FS_UINT32 dwRenderID,BOOL bShow ) PURE;
		//����Ƶ����ʾ����
		STDMETHOD( ShowText )( THIS_ FS_UINT32 dwRenderID,const WCHAR *wszText ) PURE;
		//�ػ���Ƶ
		STDMETHOD( OnDraw )( THIS_ FS_UINT32 dwRenderID ) PURE;
		//������Ƶ��ָ���ļ�
		STDMETHOD( SavePicture )( THIS_ FS_UINT32 dwRenderID,const WCHAR *wszFilePath ) PURE;
		//��ȡ��Ƶ��С
		STDMETHOD( GetState )( THIS_ FS_UINT32 dwRenderID,VideoRender_State *pState ) PURE;
		//����Ƶ����ʾ����
		//dwColor		������ɫ
		//nNum			�����С��ͼ��߶ȱ�������
		//nDen			�����С��ͼ��߶ȱ�����ĸ
		//xPos			����λ��X����,Ϊ��ʱ��ʾ���������ͼ����ߵ����ؾ���,Ϊ��ʱ��ʾ�����ұ���ͼ���ұߵ����ؾ���
		//yPos			����λ��Y����,Ϊ��ʱ��ʾ�����ϱ���ͼ���ϱߵ����ؾ���,Ϊ��ʱ��ʾ�����±���ͼ���±ߵ����ؾ���
		STDMETHOD( ShowText2 )( THIS_ FS_UINT32 dwRenderID,const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;

		STDMETHOD( ShowText3 )( THIS_ FS_UINT32 dwRenderID,int nTextIndex,const WCHAR *wszText,FS_UINT32 dwColor,int nNum,int nDen,int xPos,int yPos ) PURE;

		STDMETHOD( SetDisplayMode )( THIS_ FS_UINT32 dwRenderID,int nMode ) PURE;

		STDMETHOD( ReadLastFrame )( THIS_ FS_UINT32 dwRenderID,PBYTE pbBuffer,FS_UINT32* pdwSize ) PURE;
		//����ԭʼ��Ƶ���ݻص�
		STDMETHOD( SetRawDataCallback )( THIS_ FS_UINT32 dwRenderID,LPVOID lpObj,VideoRawDataCallBack callback ) PURE;		
		//����Render�Ĵ��ھ��
		STDMETHOD( SetRenderWnd )( THIS_ FS_UINT32 dwRenderID,HWND hWnd ) PURE;		
		//��ȡRender�ڴ����е���ʾλ��
		STDMETHOD( GetRenderPos )( THIS_ FS_UINT32 dwRenderID,RECT *pRect ) PURE;
        
#if defined _FS_OS_IOS || defined _FS_OS_ANDROID
        STDMETHOD( PauseRender )( THIS_ FS_UINT32 dwRenderID, BOOL bPause ) PURE;
#endif
		//��ȡRender�������ڵ�����
		STDMETHOD( GetRenderWinPos )( THIS_ FS_UINT32 dwRenderID,RECT *pRect ) PURE;
	};
		
#ifdef __cplusplus
}
#endif

#endif
