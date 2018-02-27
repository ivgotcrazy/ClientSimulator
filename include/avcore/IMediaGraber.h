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
		Media_Play = 0,	//����
		Media_Pause,	//��ͣ
		Media_Stop		//ֹͣ		
	}WMEDIASTATUS;

	//VTMediaPlay �Ŀ�������
	typedef enum
	{
		MEDIA_SET_STATUS = 0,		//���ò���״̬
		MEDIA_GET_STATUS,			//��ȡ����״̬
		MEDIA_SET_WNDPOS,			//������Ƶ����λ��
		MEDIA_SET_POS,				//���õ�ǰ����ʱ��λ��
		MEDIA_GET_POS,				//��ȡ��ǰ����ʱ��λ��
		MEDIA_SET_VOLUME,			//���õ�ǰ����
		MEDIA_GET_VOLUME,			//��ȡ��ǰ����
		MEDIA_SET_BALANCE,			//������������ƽ��
		MEDIA_GET_BALANCE,			//��ȡ��������ƽ��

	}WMEDIACONTROLTYPE;

	//ý��֪ͨ��Ϣ���ز���,wParam��������,lParam���޶���
	#define	WMEDIA_EC_COMPLETE		0x0001		//ý���ļ��������	

	typedef struct{

		HWND				hMovieWnd;			//[IN] ���Ŵ��ھ��
		RECT                rcMovieWnd;			//[IN] ����λ��
		HWND				hNotifyWnd;			//[IN] ��Ϣ֪ͨ���ھ��
		ULONG               lNotifyMsg;			//[IN] �Զ���ý��֪ͨ��Ϣ

		double				dbTotalTime;		//[OUT]�ļ�������ʱ��,��λ����
		double              dbVideoRate;		//[OUT]��Ƶ��������
		BOOL				bHasVideo;			//[OUT]�Ƿ�����Ƶ
		BOOL				bHasAudio;			//[OUT]�Ƿ�����Ƶ

		WAVEFORMATEX		wfxAudio;			//[OUT]��Ƶ��ʽ
		BITMAPINFOHEADER	bmiVideo;			//[OUT]��Ƶģʽ
		FS_UINT             dwUserData;			//[IN] �û��Զ�������,�������ݻص�
		MEDIACALLBACK       AudioCallback;		//[IN] ��Ƶ���ݻص�����
		MEDIACALLBACK		VideoCallback;		//[IN] ��Ƶ���ݻص�����

		WMEDIASTATUS		MediaStaus;			//[IN][OUT]	����״̬
		double              dbCurTime;			//[IN][OUT] ��ǰ����ʱ��λ��
		LONG                lVolume;			//[IN][OUT] ��������(Full volume is 0, and �C10,000 is silence)
		LONG				lBalance;			//[IN][OUT] ��������ƽ��(The value can range from -10,000 to 10,000. 
												//		    The value -10,000 means the right channel is attenuated by 100 dB and is effectively silent. 
												//			The value 10,000 means the left channel is silent. 
												//			The neutral value is 0, which means that both channels are at full volume.
												//			When one channel is attenuated, the other remains at full volume		

		BOOL				bVideoResize;		//�Ƿ����Ƶ�Զ�����
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