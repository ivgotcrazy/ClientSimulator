#ifndef __VIDEO_MIXER_H
#define __VIDEO_MIXER_H

#include "IPlaySyncTime.h"

typedef struct{
	unsigned int 		nWidth;				//视频宽度
	unsigned int 		nHeight;			//视频高度
	unsigned int 		nFrameRate;			//帧速率
	unsigned int   		nEncoderID;			//编码器ID
	unsigned int		nEncoderMode;		//压缩模式
	unsigned int		nBitrate;			//码率,bps
	unsigned int		nVBRQuality;		//质量
	unsigned int 		nKeyFrameInterval;	//关键帧间隔
}VideoMixParam;

//
//合成后的视频数据回调函数
//lpobj:			回调接收对象
//pbData:			数据指针
//dwDataLen:		数据长度
//bKeyFrame:		是否是关键帧
//
typedef VOID (*VideoMixCallBack)(LPVOID lpObj, PBYTE pbData, FS_UINT32 dwDataLen,BOOL  bKeyFrame);
//
//创建视频混合模块
//lpObj ：		回调接收对象
//pMixCallBack：	合成数据回调函数
// pParam ：		参数定义
//返回模块句柄
//
HANDLE VideoMix_Create(LPVOID lpObj, VideoMixCallBack pMixCallBack, VideoMixParam *pParam  );


VOID VideoMix_EnableMix( HANDLE hMix,BOOL bMix  );

//
//设置参数
//hMix:			句柄
//pParam:			参数定义
//返回参数设置是否成功
//
BOOL VideoMix_SetParam( HANDLE hMix, VideoMixParam *pParam  );
//
//添加一路视频输入
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//
VOID VideoMix_AddInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID );
//
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//
VOID VideoMix_RemoveInput(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID);
//
//写视频数据,注意这里写入的数据是经过网络合包后的数据
//hMix：			模块句柄
//dwUser：		用户ID
//dwMediaID:		媒体ID
//pbData：		输入数据
//nLength：		数据长度
//
VOID VideoMix_WriteData(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, PBYTE pbData, int nLength);
//
//释放模块；
//hMix：			模块句柄
//
VOID VideoMix_Destory(HANDLE hMix);

VOID VideoMix_SetSyncTime(HANDLE hMix, FS_UINT32 dwUser,FS_UINT32 dwMediaID, IPlaySyncTime* pSyncTime );

#endif