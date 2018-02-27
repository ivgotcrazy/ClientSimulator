#ifndef __VMIX_H_
#define __VMIX_H_

#include "IPlaySyncTime.h"
//�ص�����
//lpobj:		�ϲ����ָ��
//pbData:		����ָ��
//dwDataLen:	���ݳ���
//iWidth:		�ϳɺ���Ƶ��widht;
//iHeight:      �ϳɺ���Ƶ��height;
//---------------------------------
typedef LONG(*MixCallBack)(LPVOID lpObj, PBYTE pbData, FS_UINT32 dwDataLen, int iWidth, int iHeight);

//������Ƶ���ģ��
//lpObj �����豸�ص����ն���
//pMixCallBack���ϳ����ݻص�����
//nWidth �������Ƶ��width
//nHeight�������Ƶ��height
//nFrameRate:�����֡����
//���أ�����ģ����
HANDLE VMix_Create(LPVOID lpObj, MixCallBack pMixCallBack,BITMAPINFOHEADER* pbmiOut,int nFrameRate );

//���һ·��Ƶ����
//hMix��ģ����
//dwUser���û������Ψһ��Ƶ��־��
//���أ��ɹ�1 ����0
int VMix_AddInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID );

//ɾ��һ·��Ƶ����
//hMix��ģ����
//dwUser���û������Ψһ��Ƶ��־��
//���أ��ɹ�true ����false
BOOL VMix_RemoveInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID);

//д��Ƶ����
//hMix ��ģ����
//dwUser���û������Ψһ��Ƶ��־
//pbData����������
//nLength�����ݳ���
//���أ��ɹ�true ����false
BOOL VMix_WriteData(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, PBYTE pbData, int nLength);

//�ͷ�ģ�飻
//hMix��ģ����
VOID VMix_Destory(HANDLE hMix);

BOOL VMix_SetSyncTime( HANDLE hMix,FS_UINT32 dwUser,FS_UINT32 dwMediaID, IPlaySyncTime* pSyncTime );

#endif  //__VMIX_H_