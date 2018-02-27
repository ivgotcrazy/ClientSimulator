#ifndef __AUDIO_MIXER_H
#define __AUDIO_MIXER_H

#include "IPlaySyncTime.h"

typedef struct{
	unsigned int		nEncoderID;			//音频编码器ID
	unsigned int		nFecType;			//FEC类型,该参数目前已不用
}AudioMixParam;

//
//合成后的音频数据回调函数
//lpobj:			回调接收对象
//dwUserID:		该音频数据是合成给谁的,如果为0表示给非发言用户的
//pbData:			数据指针
//dwDataLen:		数据长度
//
typedef VOID(*AudioMixCallBack)(LPVOID lpObj, FS_UINT32 dwUserID, PBYTE pbData, FS_UINT32 dwDataLen);

//
//创建音频混合模块
//lpObj ：		回调接收对象
//pMixCallBack：	合成数据回调函数
// pParam ：		参数定义
//返回模块句柄
//
HANDLE AudioMix_Create(LPVOID lpObj, AudioMixCallBack pMixCallBack, AudioMixParam *pParam  );

//
//创建PCM音频混合模块,只合成PCM数据,不进行音频编码.
//PCM音频格式固定为16KHZ,单声道,16BITS
//lpObj ：		            回调接收对象
//pMixCallBack：	        合成数据回调函数
//返回模块句柄
//
HANDLE AudioMix_CreatePCM(LPVOID lpObj, AudioMixCallBack pMixCallBack  );

//
//当前是否允许数据合成.如果不允放,将停止合成数据回调
//hMix:			句柄
//bMix:         是否合成
//
VOID AudioMix_EnableMix( HANDLE hMix,BOOL bMix  );

//
//设置参数
//hMix:			句柄
//pParam:			参数定义
//返回参数设置是否成功
//
BOOL AudioMix_SetParam( HANDLE hMix, AudioMixParam *pParam  );

//
//添加一路音频输入
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//bMix:			是否要针对该用户合成音频
//
VOID AudioMix_AddInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID,BOOL bMix );

//
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//
VOID AudioMix_RemoveInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID);

//
//写音频数据,注意这里写入的数据是经过网络合包后的数据
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//pbData：		输入数据
//nLength：		数据长度
//
VOID AudioMix_WriteData(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, PBYTE pbData, int nLength);

//
//释放模块；
//hMix：			模块句柄
//
VOID AudioMix_Destory(HANDLE hMix);

//
//设置同步时钟,用于音视频数据的同步
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//pSyncTime:        同步时钟接口指针
//
VOID AudioMix_SetSyncTime(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID,IPlaySyncTime* pSyncTime );

#endif