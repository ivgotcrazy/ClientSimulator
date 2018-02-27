#ifndef AVCORE_VC12_VIDEOMIXER_VIDEOMIXERPRO_H_
#define AVCORE_VC12_VIDEOMIXER_VIDEOMIXERPRO_H_
/*##############################################################################
**File Name   : VideoMixerPro.h
**Description : 视频合成库增强版的接口文件，增强版视频合成库支持输入视频为未编码数据
或已编码数据，同时支持设置每一路输入视频在合成画面中的位置，输出合成后的原始视频数据。
**Author	  : Gerald
**Create Time : 2015.12.08
**Copyright   : Copyright 2015 Fsmeeting.com.All Rights Reserved.
##############################################################################*/
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
}VideoEncParam;

typedef struct{
	DWORD nGroupID;
	DWORD nStreamID;
}InputVideoID;

typedef struct{
	BOOL				bEncoded;//是否编码
	union 
	{
		BITMAPINFOHEADER bmInfo;//如果未编码，原始视频数据信息
		VideoEncParam    encParam;//如果编码，编码视频数据信息
	};
	DWORD				nFrameRate;//帧率
}VideoStreamInfo;

typedef struct  
{
	DWORD	nWidth;//视频帧的宽
	DWORD	nHeight;//视频帧的高
	DWORD	nTimeStamp;//视频帧的时间戳
	BOOL	bIsKeyFrame;//是否是关键帧
}VideoFrameInfo;

typedef struct
{
	DWORD nLeftCoor;//左上角x坐标
	DWORD nTopCoor;//左上角y坐标
	DWORD nWidth;//矩形区域宽
	DWORD nHeight;//矩形区域高
}RenderRect;

/*------------------------------------------------------------------------------
 *Description：合成后的视频数据回调函数
 *lpobj      ：回调接收对象
 *pbData     ：数据指针
 *dwDataLen  ：数据长度
 *bKeyFrame  ：是否是关键帧
------------------------------------------------------------------------------*/
typedef VOID(*VideoMixedCallBack)(LPVOID lpObj, PBYTE pbData, DWORD dwDataLen, BOOL  bKeyFrame);

//**********************************************************************
// Method:    	 VideoMixPro_Create
// Parameter: 	 [IN] pMixCallBack			合成数据回调函数
//               [IN] lpObj					用户自定义数据	
//				 [IN] pOutputStreamInfo		输出合成后原始视频数据的格式
// Returns:   	 HANDLE 若成功，返回创建的用于合成的对象的handle，否则返回
//				 NULL
//									
// Description:  创建用于视频合成的对象，指定合成视频的参数、合成后视频数
//			     据回调函数、输出合成视频的帧率。
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
HANDLE VideoMixPro_Create(LPVOID lpObj, VideoMixedCallBack pMixCallBack, 
					      const VideoStreamInfo *pOutputStreamInfo);

//**********************************************************************
// Method:    	 VideoMixPro_Destroy
// Parameter: 	 [IN] hMixPro 欲销毁的合成对象的handle.
// Returns:   	 
// Description:  销毁一个已经创建的合成对象。
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_Destroy(HANDLE hMixPro);

//**********************************************************************
// Method:    	 VideoMixPro_EnableMix
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] bMix    是否进行合成
// Returns:   	 
// Description:  指示是否进行视频合成工作.
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_EnableMix(HANDLE hMixPro, BOOL bMix);

//**********************************************************************
// Method:    	 VideoMixPro_SetParam
// Parameter: 	 [IN] hMixPro			合成对象的handle
//               [IN] pOutputStreamInfo  期望输出的合成视频的参数
// Returns:   	 设置成功返回TRUE，否则返回FALSE
// Description:  设置输出视频的格式,可以在视频合成期间内调用以改变输出合成
//				 视频的格式。
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_SetParam(HANDLE hMixPro, const VideoStreamInfo *pOutputStreamInfo);

//**********************************************************************
// Method:    	 VideoMixPro_AddCodedInput
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] pInputVideoID 用于唯一标识一路待合成的输入视频，由调
//				 用方指定
//				 [IN] nCodecID 输入视频的编码器ID
//				 [IN] dstRect 期望的此路视频在合成后视频画面中的位置
// Returns:   	 成功返回TRUE，失败返回FALSE.
// Description:  添加一路已编码视频参与合成。
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_AddCodedInput(HANDLE hMixPro, const InputVideoID *pInputVideoID,
							   int nCodecID, RenderRect dstRect);

//**********************************************************************
// Method:    	 VideoMixPro_AddRawInput
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] pInputVideoID 用于唯一标识一路待合成的输入视频，由调
//				 用方指定
//				 [IN] pBIH   输入视频信息
//				 [IN] dstRect 期望的此路视频在合成后视频画面中的位置
// Returns:   	 成功返回TRUE，失败返回FALSE.
// Description:  添加一路原始视频数据参与合成。
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_AddRawInput(HANDLE hMixPro, const InputVideoID *pInputVideoID,
						     const BITMAPINFOHEADER *pbmih, RenderRect dstRect);

//**********************************************************************
// Method:    	 VideoMixPro_RemoveInput
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] pInputVideoID 标识欲移除的一路视频
// Returns:   	 
// Description:  移除一路视频，不再对其进行合成。
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_RemoveInput(HANDLE hMixPro, const InputVideoID *pInputVideoID);

//**********************************************************************
// Method:    	 VideoMixPro_ResetVideoRect
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] pInputVideoID 标识一路输入视频
//				 [IN] pRect	重新设置后由pInputVideoID指定的一路视频在合成
//				 视频画面中的位置信息
// Returns:   	 成功返回TRUE,否则返回FALSE
// Description:  重新设置一路视频在合成后视频中的位置.
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_ResetVideoRect(HANDLE hMixPro, const InputVideoID *pInputVideoID, const RenderRect *pRect);

//**********************************************************************
// Method:    	 VideoMixPro_WriteData
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] pInputVideoID 标识输入数据所属的那一路视频
//				 [IN] pbData 输入的视频数据
//				 [IN] dwLength 输入视频数据的长度
//				 [IN] pFrameInfo 写入视频帧的信息，注意如果输入的视频是原始
//               视频数据，则pFrameInfo->bIsKeyFrame将被忽略
// Returns:   	 
// Description:  输入一路视频的数据参与合成
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_WriteData(HANDLE hMixPro, InputVideoID *pInputVideoID, 
						   PBYTE pbData, DWORD dwLength, VideoFrameInfo *pFrameInfo);
//**********************************************************************
// Method:    	 VideoMixPro_SetSyncTime
// Parameter: 	 [IN] hMixPro 指定一个已创建合成对象的handle
//				 [IN] pInputVideoID 标识一路参与合成的视频
//				 [IN] pSyncTime 对一路视频进行音视频同步
// Returns:   	 
// Description:  
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_SetSyncTime(HANDLE hMixPro, InputVideoID *pInputVideoID, IPlaySyncTime* pSyncTime);

#endif





