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
	#define	MULTIAV_MEDIATYPE_AUDIO			0X01	//��Ƶ����
	#define MULTIAV_MEDIATYPE_VIDEO			0X02	//��Ƶ����
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
		//���ݻص�
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
		//��ʼ��
		STDMETHOD( Initialize )( THIS_ LPUNKNOWN pAudioDevice, LPUNKNOWN pRenderManager,LPUNKNOWN pSessionManager) PURE;

		//��¼�����������������ؽ����֪ͨӦ�ò㣬֪ͨ��Ϣ��WPARAM����Ϊ1����ɹ�
		STDMETHOD( Login )( THIS_ const GUID& guidGroup,FS_UINT32 dwUserID,FS_UINT32 dwCheckCode,FS_UINT16 wApplicationID,const CHAR* lpszServerAddrLink,WBASE_NOTIFY *pNotify ) PURE;
		//ע��
		STDMETHOD( Logout )( THIS_ ) PURE;

		//��Ӳɼ��豸Դ
		STDMETHOD( AddSource )( THIS_ BYTE bMediaType,BYTE bMediaID,LPUNKNOWN pSource ) PURE;
		//ɾ���ɼ��豸Դ
		STDMETHOD( RemoveSource )( THIS_ BYTE bMediaType,BYTE bMediaID ) PURE;
		//ɾ�����еĲɼ��豸Դ
		STDMETHOD( RemoveAllSource )( THIS_ ) PURE;
		//�Ƿ������Զ����ڲ���
		STDMETHOD( EnableAutoAdjust )( THIS_ BYTE bMediaType,BYTE bMediaID,BOOL bEnable ) PURE;
		//������Ƶ�����Զ����ڵ����ֵ
		STDMETHOD( SetVideoSourceMaxParam )( THIS_ BYTE bMediaID,const VideoMaxParam* pParam ) PURE;

		//�Ƿ�����������
		STDMETHOD( EnableSend )( THIS_ BYTE bMediaType,BYTE bMediaID,BOOL bEnable ) PURE;

		//�����û�����
		STDMETHOD( StartRecvMedia )( THIS_ FS_UINT32 dwRemoteUserID,BYTE bMediaType,BYTE bMediaID,FS_UINT32 dwRenderID ) PURE;
		//ֹͣ�����û�����
		STDMETHOD( StopRecvMedia )( THIS_ FS_UINT32 dwRemoteUserID,BYTE bMediaType,BYTE bMediaID ) PURE;
		//��ͣ�����û�����
		STDMETHOD( PauseRecvMedia )( THIS_ FS_UINT32 dwRemoteUserID,BYTE bMediaType,BYTE bMediaID,BOOL bPause ) PURE;

		//�ص��û���Ƶ����
		//dwUserID����0ʱ,��ʾ�ص���������
		//��pSinkΪ��ʱ,��ʾֹͣ�ص����û�����
		STDMETHOD( SetDataSink )( THIS_ FS_UINT32 dwUserID,FS_UINT dwUserData,BYTE bMediaType,BYTE bMediaID,IMediaDataSink *pSink ) PURE;

		//��ȡ�ϳ��û�ID
		STDMETHOD( GetMixerUserID )( THIS_ FS_UINT32& dwMixerUserID) PURE;

		STDMETHOD( GetQosState)( THIS_ MULTIAV_QOSSTATE* pState ) PURE;

		STDMETHOD( EnableReuseUdpPort )( THIS_ BOOL bEnable ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif
