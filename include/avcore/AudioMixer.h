#ifndef __AUDIO_MIXER_H
#define __AUDIO_MIXER_H

#include "IPlaySyncTime.h"

typedef struct{
	unsigned int		nEncoderID;			//��Ƶ������ID
	unsigned int		nFecType;			//FEC����,�ò���Ŀǰ�Ѳ���
}AudioMixParam;

//
//�ϳɺ����Ƶ���ݻص�����
//lpobj:			�ص����ն���
//dwUserID:		����Ƶ�����Ǻϳɸ�˭��,���Ϊ0��ʾ���Ƿ����û���
//pbData:			����ָ��
//dwDataLen:		���ݳ���
//
typedef VOID(*AudioMixCallBack)(LPVOID lpObj, FS_UINT32 dwUserID, PBYTE pbData, FS_UINT32 dwDataLen);

//
//������Ƶ���ģ��
//lpObj ��		�ص����ն���
//pMixCallBack��	�ϳ����ݻص�����
// pParam ��		��������
//����ģ����
//
HANDLE AudioMix_Create(LPVOID lpObj, AudioMixCallBack pMixCallBack, AudioMixParam *pParam  );

//
//����PCM��Ƶ���ģ��,ֻ�ϳ�PCM����,��������Ƶ����.
//PCM��Ƶ��ʽ�̶�Ϊ16KHZ,������,16BITS
//lpObj ��		            �ص����ն���
//pMixCallBack��	        �ϳ����ݻص�����
//����ģ����
//
HANDLE AudioMix_CreatePCM(LPVOID lpObj, AudioMixCallBack pMixCallBack  );

//
//��ǰ�Ƿ��������ݺϳ�.������ʷ�,��ֹͣ�ϳ����ݻص�
//hMix:			���
//bMix:         �Ƿ�ϳ�
//
VOID AudioMix_EnableMix( HANDLE hMix,BOOL bMix  );

//
//���ò���
//hMix:			���
//pParam:			��������
//���ز��������Ƿ�ɹ�
//
BOOL AudioMix_SetParam( HANDLE hMix, AudioMixParam *pParam  );

//
//���һ·��Ƶ����
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//bMix:			�Ƿ�Ҫ��Ը��û��ϳ���Ƶ
//
VOID AudioMix_AddInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID,BOOL bMix );

//
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//
VOID AudioMix_RemoveInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID);

//
//д��Ƶ����,ע������д��������Ǿ�������ϰ��������
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//pbData��		��������
//nLength��		���ݳ���
//
VOID AudioMix_WriteData(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, PBYTE pbData, int nLength);

//
//�ͷ�ģ�飻
//hMix��			ģ����
//
VOID AudioMix_Destory(HANDLE hMix);

//
//����ͬ��ʱ��,��������Ƶ���ݵ�ͬ��
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//pSyncTime:        ͬ��ʱ�ӽӿ�ָ��
//
VOID AudioMix_SetSyncTime(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID,IPlaySyncTime* pSyncTime );

#endif