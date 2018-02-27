#ifndef __VIDEO_MIXER_H
#define __VIDEO_MIXER_H

#include "IPlaySyncTime.h"

typedef struct{
	unsigned int 		nWidth;				//��Ƶ���
	unsigned int 		nHeight;			//��Ƶ�߶�
	unsigned int 		nFrameRate;			//֡����
	unsigned int   		nEncoderID;			//������ID
	unsigned int		nEncoderMode;		//ѹ��ģʽ
	unsigned int		nBitrate;			//����,bps
	unsigned int		nVBRQuality;		//����
	unsigned int 		nKeyFrameInterval;	//�ؼ�֡���
}VideoMixParam;

//
//�ϳɺ����Ƶ���ݻص�����
//lpobj:			�ص����ն���
//pbData:			����ָ��
//dwDataLen:		���ݳ���
//bKeyFrame:		�Ƿ��ǹؼ�֡
//
typedef VOID (*VideoMixCallBack)(LPVOID lpObj, PBYTE pbData, FS_UINT32 dwDataLen,BOOL  bKeyFrame);
//
//������Ƶ���ģ��
//lpObj ��		�ص����ն���
//pMixCallBack��	�ϳ����ݻص�����
// pParam ��		��������
//����ģ����
//
HANDLE VideoMix_Create(LPVOID lpObj, VideoMixCallBack pMixCallBack, VideoMixParam *pParam  );


VOID VideoMix_EnableMix( HANDLE hMix,BOOL bMix  );

//
//���ò���
//hMix:			���
//pParam:			��������
//���ز��������Ƿ�ɹ�
//
BOOL VideoMix_SetParam( HANDLE hMix, VideoMixParam *pParam  );
//
//���һ·��Ƶ����
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//
VOID VideoMix_AddInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID );
//
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//
VOID VideoMix_RemoveInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID);
//
//д��Ƶ����,ע������д��������Ǿ�������ϰ��������
//hMix��			ģ����
//dwUser��		�û�ID
//dwMediaID:		ý��ID
//pbData��		��������
//nLength��		���ݳ���
//
VOID VideoMix_WriteData(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, PBYTE pbData, int nLength);
//
//�ͷ�ģ�飻
//hMix��			ģ����
//
VOID VideoMix_Destory(HANDLE hMix);

VOID VideoMix_SetSyncTime(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, IPlaySyncTime* pSyncTime );

#endif