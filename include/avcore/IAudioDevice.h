#ifndef __IWAUDIO_DEVICE_H
#define __IWAUDIO_DEVICE_H

#include "wcombase.h"
#include "IAudioSource.h"
#include "IPlaySyncTime.h"
#ifdef _WIN32
#include <mmsystem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
	

	// AudioDevice Component's GUID
	// {F0645FDB-A8E3-45bd-8C1A-54237A1F6EBF}
	DEFINE_GUID( CLSID_AudioDevice, 
		0xf0645fdb, 0xa8e3, 0x45bd, 0x8c, 0x1a, 0x54, 0x23, 0x7a, 0x1f, 0x6e, 0xbf);

	// IAudioDevice's GUID
	// {DC26810D-D3CC-48bf-94BB-E56B7FAE58BA}
	DEFINE_GUID(IID_IAudioDevice, 
		0xdc26810d, 0xd3cc, 0x48bf, 0x94, 0xbb, 0xe5, 0x6b, 0x7f, 0xae, 0x58, 0xba);	
	
	//----------------------------------------------------------------------------
	// IAudioDevice
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioDevice, IUnknown)
	{
		//
		//��ȡ��Ƶ�ɼ��豸����
		//
		STDMETHOD_( int,GetCapDevicesCount ) ( THIS_ ) PURE;
		//
		//��ȡ��Ƶ�ɼ��豸��Ϣ
		//
		STDMETHOD( GetCapDeviceInfo ) (THIS_ int nDevIndex,WCHAR *szDevName,UINT nSize ) PURE;
		//
		//��ȡ��Ƶ�����豸����
		//
		STDMETHOD_( int,GetPlayDevicesCount ) ( THIS_ ) PURE;
		//
		//��ȡ��Ƶ�����豸��Ϣ
		//
		STDMETHOD( GetPlayDeviceInfo ) (THIS_ int nDevIndex,WCHAR *szDevName,UINT nSize ) PURE;
		//
		//��ȡ����������
		//
		STDMETHOD_( int,GetEncoderCount ) ( THIS_ ) PURE;
		//
		//��ȡ��������Ϣ
		//
		STDMETHOD( GetEncoderInfo )( int nEncoderIndex,int *pEncoderID,int *pBitrate,WCHAR *szEncoderName,UINT nSize ) PURE;
		//
		//������Ƶ�ɼ�
		//
		STDMETHOD( StartCapture )( THIS_ int nDevIndex ) PURE;
		//
		//ֹͣ��Ƶ�ɼ�
		//
		STDMETHOD( StopCapture )( THIS_ ) PURE;
		//
		//������Ƶ����
		//
		STDMETHOD( StartPlay )( THIS_ int nDevIndex ) PURE;
		//
		//ֹͣ��Ƶ����
		//
		STDMETHOD( StopPlay )( THIS_ ) PURE;
		//
		//��Ƶ�ɼ����ݻص�
		//
		STDMETHOD( AddCapDataSink )( THIS_ IAudioDataSink *pSink,FS_UINT dwUserData  ) PURE;

		STDMETHOD( RemoveCapDataSink )( THIS_ IAudioDataSink *pSink ) PURE;
		//
		//��Ƶ�ɼ����ݻص�
		//
		STDMETHOD( AddPlayDataSink )( THIS_ IAudioDataSink *pSink,FS_UINT dwUserData  ) PURE;
		 
		STDMETHOD( RemovePlayDataSink )( THIS_ IAudioDataSink *pSink ) PURE;
		//
		//��ȡ��Ƶ�������ݸ�ʽ
		//
		STDMETHOD( GetPlayDataFormat)( THIS_ WAVEFORMATEX *pWfx ) PURE;
		//
		//���ò���
		//
		STDMETHOD( SetParam )( THIS_ int nParamType,void *pValue,int nValueSize ) PURE;
		//
		//��ȡ����
		//
		STDMETHOD( GetParam )( THIS_ int nParamType,void *pValue,int nValueSize ) PURE;
		//
		//������ƵԴ
		//
		STDMETHOD_( FS_UINT32,AddSource )( THIS_ ) PURE;

		STDMETHOD( SetSyncTime )( THIS_ FS_UINT32 dwSourceID,IPlaySyncTime* pSyncTime ) PURE;
		//
		//ɾ����ƵԴ
		//
		STDMETHOD( RemoveSource )( THIS_ FS_UINT32 dwSourceID ) PURE;
		//
		//������ƵԴ�Ƿ����
		//
		STDMETHOD_( BOOL,SourceIsExist )( THIS_ FS_UINT32 dwSourceID ) PURE;
		//
		//����ƵԴд������
		//
		STDMETHOD( WriteSource )( THIS_ FS_UINT32 dwSourceID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;
		//
		//������ƵԴ����
		//
		STDMETHOD( SetSourceVolume )( THIS_ FS_UINT32 dwSourceID,int nVolume ) PURE;
		//
		//��ȡ��ƵԴ����
		//
		STDMETHOD( GetSourceVolume )( THIS_ FS_UINT32 dwSourceID,int *pVolume,int *pMaxVolume,int *pMinVolume ) PURE;
		//
		//��ȡ��ƵԴ������ֵ
		//
		STDMETHOD( GetSourceEnergy )( THIS_ FS_UINT32 dwSourceID,int *pEnergy,int *pMaxEnergy,int *pMinEnergy ) PURE;
		//
		//��ȡ�ɼ�������ֵ
		//
		STDMETHOD( GetCapEnergy )( THIS_ int *pEnergy,int *pMaxEnergy,int *pMinEnergy ) PURE;
		//
		//��ȡ����������ֵ
		//
		STDMETHOD( GetPlayEnergy )( THIS_ int *pEnergy,int *pMaxEnergy,int *pMinEnergy ) PURE;
		//
		//���òɼ�����
		//
		STDMETHOD( SetCapVolume )( THIS_ int nVolume ) PURE;
		//
		//��ȡ�ɼ�����
		//
		STDMETHOD( GetCapVolume )( THIS_ int *pVolume,int *pMaxVolume,int *pMinVolume ) PURE;
		//
		//���ò�������
		//
		STDMETHOD( SetPlayVolume )( THIS_ int nVolume ) PURE;
		//
		//��ȡ��������
		//
		STDMETHOD( GetPlayVolume )( THIS_ int *pVolume,int *pMaxVolume,int *pMinVolume ) PURE;
		//
		//���òɼ�����
		//
		STDMETHOD( SetCapMute )( THIS_ BOOL bMute ) PURE;
		//
		//��ȡ�ɼ�����
		//
		STDMETHOD( GetCapMute )( THIS_ BOOL *pMute ) PURE;
		//
		//���ò��ž���
		//
		STDMETHOD( SetPlayMute )( THIS_ BOOL bMute ) PURE;
		//
		//��ȡ���ž���
		//
		STDMETHOD( GetPlayMute )( THIS_ BOOL *pMute ) PURE;
		//
		//���òɼ���������
		// 
		STDMETHOD( SetCapInputType )( THIS_ FS_UINT32 dwInputType ) PURE;
		//
		//��ȡ�ɼ���������
		//
		STDMETHOD( GetCapInputType )( THIS_ FS_UINT32 *pdwInputType ) PURE;
		//
		//�����Ƿ񲥷ű�����Ƶ
		//
		STDMETHOD( SetPlayLocal )( THIS_ BOOL bPlay ) PURE;
		//
		//��ȡ�Ƿ񲥷ű�����Ƶ
		//
		STDMETHOD( GetPlayLocal )( THIS_ BOOL *pPlay ) PURE;
		//
		//���ò�������
		//
		STDMETHOD( SetPlaySoftMute )( THIS_ BOOL bMute ) PURE;
		//
		//��ȡ��������
		//
		STDMETHOD( GetPlaySoftMute )( THIS_ BOOL *pMute ) PURE;

		STDMETHOD( SetAudioEngine )( THIS_ int nEngineIndex ) PURE;

		STDMETHOD( StartAudioDevice )( THIS_ int nCapDev,int nPlayDev ) PURE;

		STDMETHOD( StopAudioDevice )( THIS_ ) PURE;
	};

	// AudioProcessor Component's GUID
	// {A18A0F2B-0503-4da0-9595-0261144A72EA}
	DEFINE_GUID(CLSID_AudioProcessor, 
		0xa18a0f2b, 0x503, 0x4da0, 0x95, 0x95, 0x2, 0x61, 0x14, 0x4a, 0x72, 0xea);

	// IAudioProcessor's GUID
	// {49DC2814-76DD-47ff-A382-2A4A7C6CC3EA}
	DEFINE_GUID(IID_IAudioProcessor, 
		0x49dc2814, 0x76dd, 0x47ff, 0xa3, 0x82, 0x2a, 0x4a, 0x7c, 0x6c, 0xc3, 0xea);
	
	//----------------------------------------------------------------------------
	// IAudioProcessor
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioProcessor, IUnknown)
	{
		//������Ƶ������
		//pwfxIn:��Ƶ�������ʽ
		STDMETHOD( Create ) ( THIS_ WAVEFORMATEX* pwfxIn ) PURE;
	
		//������Ƶ������
		STDMETHOD( Destroy ) ( THIS_ ) PURE;
		
		//���� ��Ƶǰ����Ĳ���
		STDMETHOD( SetParam ) ( THIS_ int nParamType, void *pValue,int nValueSize ) PURE;
		
		//��ȡ������ֵ
		//������ֵ��С 0-100
		STDMETHOD_( int,GetEnergy ) ( THIS_ ) PURE;
		
		//������Ƶ����
		//pPack:��Ƶ�����
		//���ش����Ƿ�ɹ�
		//�����سɹ�,��head.unDesUsed =0 ʱ,��ʾ��ǰΪ��������
		STDMETHOD( Process ) ( THIS_ AudioStreamPacket* pPack) PURE;
		
		//��ȡ�������ݿ�Ĵ�С
		STDMETHOD_( int,GetInputBlockSize ) ( THIS_ ) PURE;

        //��ȡ��Ƶǰ����Ĳ���
        STDMETHOD( GetParam ) ( THIS_ int nParamType, void *pValue,int nValueSize ) PURE;
	};


	// AudioGroup Component's GUID
	// {A1557819-07D6-4392-A9DB-F3D58A8C0F9A}
	DEFINE_GUID(CLSID_AudioGroup, 
		0xa1557819, 0x7d6, 0x4392, 0xa9, 0xdb, 0xf3, 0xd5, 0x8a, 0x8c, 0xf, 0x9a);
	
	// IAudioGroup's GUID
	// {20259CFC-C0AB-458e-A7CF-EA7018C9E14B}
	DEFINE_GUID(IID_IAudioGroup, 
		0x20259cfc, 0xc0ab, 0x458e, 0xa7, 0xcf, 0xea, 0x70, 0x18, 0xc9, 0xe1, 0x4b);
	
	//----------------------------------------------------------------------------
	// IAudioGroup
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioGroup, IUnknown)
	{
		//16λ����
		//buf1:��һ·��Ƶ����,ͬʱ��Ŀ�����ݴ�Ż���
		//buf2:�ڶ�����Ƶ����
		//nSamples:��������
		//---------------------------
		STDMETHOD( Mix16 )(short* buf1, short* buf2 , int nSamples) PURE;
		
		//16λ����
		//buf1:��һ·��Ƶ����
		//buf2:�ڶ�����Ƶ����
		//output:Ŀ�����ݴ�Ż���
		//nSamples:��������
		STDMETHOD( Mix16_2)(short* buf1, short* buf2,short *output, int nSamples) PURE;

		//������ƵԴ��
		//pwfxOut:Ҫ���������Ƶ��ʽ
		STDMETHOD( Create ) ( THIS_ WAVEFORMATEX* pwfxOut ) PURE;

		//������ƵԴ��
		STDMETHOD( Destroy ) ( THIS_ ) PURE;

		//�ж������Ƿ����ָ����ƵԴ
		//dwSourceID:��ƵԴID
		//������ƵԴ�Ƿ����
		STDMETHOD_(BOOL,SourceIsExist)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//�����м�����ƵԴ
		//������ƵԴID
		STDMETHOD_(FS_UINT32,AddSource)( THIS_ ) PURE;

		//������ƵԴͬ��ʱ��
		STDMETHOD(SetSyncTime)( THIS_ FS_UINT32 dwSourceID,IPlaySyncTime* pSyncTime ) PURE;

		//������ɾ����ƵԴ
		//dwSourceID:��ƵԴID
		STDMETHOD(RemoveSource)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//����ƵԴ��д������
		//dwSourceID:��ƵԴID
		//pbData:����ָ��
		//unDataLen:���ݳ���
		STDMETHOD(WriteSource)( THIS_ FS_UINT32 dwSourceID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;

		//����ƵԴ��ȡ����
		//dwSourceID:��ƵԴID
		//pbBuffer:���ݻ���
		//nReadLen:Ҫ��������ݳ���
		//����ʵ�ʶ�������ݳ���
		STDMETHOD_(UINT,ReadSource)( THIS_ FS_UINT32 dwSourceID,PBYTE pbBuffer,UINT nReadLen ) PURE;

		//������ƵԴ������С
		//dwSourceID:��ƵԴID
		//nVolume:������С 0-100 
		STDMETHOD(SetSourceVolume)( THIS_ FS_UINT32 dwSourceID,int nVolume ) PURE;

		//��ȡ��ƵԴ������С
		//dwSourceID:��ƵԴID
		//������ƵԴ������С
		STDMETHOD_(int,GetSourceVolume)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//������ƵԴ�Ƿ���Ҫ����������ֵ
		//dwSourceID:��ƵԴID
		//bEnable:�Ƿ����
		STDMETHOD(EnableSourceCalEnergy)( THIS_ FS_UINT32 dwSourceID,BOOL bEnable ) PURE;

		//��ȡ��ƵԴ������ֵ
		//dwSourceID:��ƵԴID
		//����������ֵ��С
		STDMETHOD_(int,GetSourceEnergy)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//�����ж�������
		//pbBuffer:���ݻ���
		//unReadLen:Ҫ��������ݳ���
		//����ʵ�ʶ�������ݳ���
		STDMETHOD_(UINT,ReadData)( THIS_ PBYTE pbBuffer,UINT unReadLen ) PURE;

		//��ȡ���������ֵ 0-100
		//������ֵ��С
		STDMETHOD_(int,GetEnergy)( THIS_ ) PURE;

		//�Ƿ����������������ֵ
		//bEnable:�Ƿ�����
		STDMETHOD(EnableCalEnergy)( THIS_ BOOL bEnable ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif