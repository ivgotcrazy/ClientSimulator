#if !defined EXPORT_AF_H
#define      EXPORT_AF_H

#include "AudioDefine.h"
#include "IPlaySyncTime.h"
#ifdef _FS_OS_WIN
#include "mmsystem.h"
#endif

//----------------------------
//16λ����
//buf1:��һ·��Ƶ����,ͬʱ��Ŀ�����ݴ�Ż���
//buf2:�ڶ�����Ƶ����
//len:��������
//---------------------------
VOID		 WAudio_Mix16(short* buf1, short* buf2 , FS_INT32 len);
VOID		 WAudio_Mix16_2(short* buf1, short* buf2,short *output, FS_INT32 len);
VOID		 WAudio_Mix32(FS_INT32* buf1, short* buf2,FS_INT32 *output, FS_INT32 len);
VOID		 WAudio_NegMix32(FS_INT32* buf1, short* buf2,FS_INT32 *output, FS_INT32 len);
VOID		 WAudio_NegMix16(short* buf1, short* buf2,short *output, FS_INT32 len);
VOID		 WAudio_Mix32to16(FS_INT32* buf1, short* output, FS_INT32 len, FS_UINT32& factor); 

//--------------------------
//������ƵԴ��
//wfxOut:Ҫ���������Ƶ��ʽ
//������ƵԴ����
//-------------------------
HANDLE      WAudio_SourceGroup_Create( const WAVEFORMATEX &wfxOut );


//-------------------------
//�ж������Ƿ����ָ����ƵԴ
//hGroup:����
//dwSourceID:��ƵԴID
//������ƵԴ�Ƿ����
//-------------------------
BOOL		WAudio_SourceGroup_SourceIsExist( HANDLE hGroup,FS_UINT32 dwSourceID );

//-------------------------
//�����м�����ƵԴ
//hGroup:����
//������ƵԴID
//-------------------------
FS_UINT32		WAudio_SourceGroup_AddSource( HANDLE hGroup );


BOOL		WAudio_SourceGroup_SetSyncTime( HANDLE hGroup,FS_UINT32 dwSourceID,IPlaySyncTime* pSyncTime );

//-------------------------
//������ɾ����ƵԴ
//hGroup:���� 
//dwSourceID:��ƵԴID
//-------------------------
BOOL        WAudio_SourceGroup_RemoveSource( HANDLE hGroup,FS_UINT32 dwSourceID );


//------------------------
//����ƵԴ��д������
//hGroup:����
//dwSourceID:��ƵԴID
//pbData:����ָ��
//unDataLen:���ݳ���
//------------------------
BOOL        WAudio_SourceGroup_WriteSource( HANDLE hGroup,FS_UINT32 dwSourceID,PBYTE pbData,FS_UINT32 dwDataLen );


//------------------------
//����ƵԴ��ȡ����
//hGroup:����
//dwSourceID:��ƵԴID
//pbBuffer:���ݻ���
//nReadLen:Ҫ��������ݳ���
//����ʵ�ʶ�������ݳ���
//------------------------
UINT        WAudio_SourceGroup_ReadSource( HANDLE hGroup,FS_UINT32 dwSourceID,PBYTE pbBuffer,UINT nReadLen );

//-------------------------
//������ƵԴ������С
//hGroup:����
//dwSourceID:��ƵԴID
//nVolume:������С 0-100 
//-------------------------
VOID        WAudio_SourceGroup_SetSourceVolume( HANDLE hGroup,FS_UINT32 dwSourceID,FS_INT32 nVolume );

//-------------------------
//��ȡ��ƵԴ������С
//hGroup:����
//dwSourceID:��ƵԴID
//������ƵԴ������С
//-------------------------
FS_INT32         WAudio_SourceGroup_GetSourceVolume( HANDLE hGroup,FS_UINT32 dwSourceID );


//-------------------------
//������ƵԴ�Ƿ���Ҫ����������ֵ
//hGroup:����
//dwSourceID:��ƵԴID
//bEnable:�Ƿ����
//-------------------------
VOID        WAudio_SourceGroup_EnableSourceCalEnergy( HANDLE hGroup,FS_UINT32 dwSourceID,BOOL bEnable );

//-------------------------
//��ȡ��ƵԴ������ֵ
//hGroup:����
//dwSourceID:��ƵԴID
//����������ֵ��С
//-------------------------
FS_INT32         WAudio_SourceGroup_GetSourceEnergy( HANDLE hGroup,FS_UINT32 dwSourceID );

//------------------------
//�����ж�������
//hGroup:����
//pbBuffer:���ݻ���
//unReadLen:Ҫ��������ݳ���
//����ʵ�ʶ�������ݳ���
//-------------------------
UINT        WAudio_SourceGroup_ReadData( HANDLE hGroup,PBYTE pbBuffer,UINT unReadLen );

//-------------------------
//��ȡ���������ֵ 0-100
//hGroup:����
//������ֵ��С
//-------------------------
INT		  WAudio_SourceGroup_GetEnergy( HANDLE hGroup );

//-------------------------
//�Ƿ����������������ֵ
//hGroup:����
//bEnable:�Ƿ�����
//-------------------------
VOID        WAudio_SourceGroup_EnableCalEnergy( HANDLE hGroup,BOOL bEnable );

//-------------------------
//�ͷ���
//hGroup:����
//-------------------------
VOID        WAudio_SourceGroup_Destroy( HANDLE &hGroup );


//-------------------------
//������Ƶ������
//wfxIn:��Ƶ�������ʽ
//������Ƶ���������
//------------------------
HANDLE      WAudio_Processer_Create(const WAVEFORMATEX &wfxIn );

//���� ��Ƶǰ����Ĳ���
BOOL		WAudio_Processer_SetParam(HANDLE hProcesser,FS_INT32 nParamType, void *pValue,FS_INT32 nValueSize );

//��ȡ ��Ƶǰ����Ĳ���
BOOL		WAudio_Processer_GetParam(HANDLE hProcesser,FS_INT32 nParamType, void *pValue,FS_INT32 nValueSize );

//-------------------------
//��ȡ������ֵ 0-100
//������ֵ��С
//-------------------------
INT			WAudio_Processer_GetEnergy( HANDLE hProcesser );

//------------------------
//������Ƶ����
//hProcesser:���������
//head:��Ƶ�����
//���ش����Ƿ�ɹ�
//�����سɹ�,��head.unDesUsed =0 ʱ,��ʾ��ǰΪ��������
//------------------------
BOOL        WAudio_Processer_Process( HANDLE hProcesser,AudioStreamPacket &head );

//
//��ȡ�������ݿ�Ĵ�С
//hProcesser:���������
//
INT			WAudio_Processer_GetInputBlockSize( HANDLE hProcesser );


//------------------------
//������Ƶ������
//hProcesser:��Ƶ���������
//------------------------
VOID        WAudio_Processer_Destroy( HANDLE &hProcesser );


//------------------------
//��ȡ��Ƶ����������֧�ֵ�ѹ����ʽ����
//bType ������������,Ĭ��Ϊ0x01,������ʹ�õı���������
//------------------------
BYTE		WAudio_GetEncoderCount();

//-----------------------
//��ȡѹ����ʽ������
//bCodeIndex:ѹ����ʽ����: 0 - (����ʽ����-1)
//szName:���ƻ���
//unSize:�����С
//nBitrate:����������
//bType ������������,Ĭ��Ϊ0x01,������ʹ�õı���������
//����д�뻺����ֽ���
//-----------------------
FS_UINT        WAudio_GetEncoderInfo(BYTE bCodeIndex, BYTE& bCodeID,unsigned int &nBitrate,WCHAR *wszName,UINT unSize );

//-----------------------
//��ȡ����������
//bFormatID:ѹ����ʽID
//wfx:��Ƶ��ʽ
//�����Ƿ�ɹ�
//----------------------
BOOL        WAudio_GetEncoderParam( BYTE bCodecID,WAVEFORMATEX &wfx,UINT& nInBlockSize );

#endif
