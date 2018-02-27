#ifndef __VMIX_H_
#define __VMIX_H_

#include "IPlaySyncTime.h"
//回调函数
//lpobj:		上层对象指针
//pbData:		数据指针
//dwDataLen:	数据长度
//iWidth:		合成后视频的widht;
//iHeight:      合成后视频的height;
//---------------------------------
typedef LONG(*MixCallBack)(LPVOID lpObj, PBYTE pbData, FS_UINT32 dwDataLen, int iWidth, int iHeight);

//创建视频混合模块
//lpObj ：主设备回调接收对象
//pMixCallBack：合成数据回调函数
//nWidth ：混合视频的width
//nHeight：混合视频的height
//nFrameRate:输出的帧速率
//返回：返回模块句柄
HANDLE VMix_Create(LPVOID lpObj, MixCallBack pMixCallBack,BITMAPINFOHEADER* pbmiOut,int nFrameRate );

//添加一路视频输入
//hMix：模块句柄
//dwUser：用户输入的唯一视频标志；
//返回：成功1 否则0
int VMix_AddInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID );

//删除一路视频输入
//hMix：模块句柄
//dwUser：用户输入的唯一视频标志；
//返回：成功true 否则false
BOOL VMix_RemoveInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID);

//写视频数据
//hMix ：模块句柄
//dwUser：用户输入的唯一视频标志
//pbData：输入数据
//nLength：数据长度
//返回：成功true 否则false
BOOL VMix_WriteData(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, PBYTE pbData, int nLength);

//释放模块；
//hMix：模块句柄
VOID VMix_Destory(HANDLE hMix);

BOOL VMix_SetSyncTime( HANDLE hMix,FS_UINT32 dwUser,FS_UINT32 dwMediaID, IPlaySyncTime* pSyncTime );

#endif  //__VMIX_H_