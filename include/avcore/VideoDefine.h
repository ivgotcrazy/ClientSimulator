#if !defined VIDEO_DEFINE_H
#define		 VIDEO_DEFINE_H

#include "wbasetype.h"
#include "AVConfig.h"

#pragma pack(1)

typedef struct{

	BYTE		bCodecID:4;
	BYTE		bKeyFrame:1;
	BYTE		bReserved:3;
	BYTE		bWidth;
	BYTE		bHeight;
	FS_UINT32		dwTimeStamp;	//ms
	BYTE		pbData[0];

}VideoFrameHeader;

#pragma pack()

//---------------------------------
//视频采集回调函数
//lpobj:		上层对象指针
//pbData:		数据指针
//dwDataLen:	数据长度
//bKeyFrame:	是否为关键帧
//---------------------------------
typedef LONG (*VideoCapCallBack)(LPVOID lpObj,PBYTE pbData,FS_UINT32 dwDataLen,BOOL bKeyFrame );

//---------------------------------
//视频原始数据回调函数
//lpobj:		上层对象指针
//pbmih:		图像格式
//pbData:		数据指针
//dwDataLen:	数据长度
//---------------------------------
typedef LONG (*VideoRawDataCallBack)(LPVOID lpObj,BITMAPINFOHEADER* pbmih,PBYTE pbData,FS_UINT32 dwDataLen );
	
//
//视频压缩模式定义
//
#define VIDEO_ENCODER_MODE_VBR		0
#define VIDEO_ENCODER_MODE_CBR		1
#define VIDEO_ENCODER_MODE_ABR		2

//
//视频压缩器ID定义
//
#define VIDEO_CODEC_RAW				0
#define VIDEO_CODEC_DIVX			1
#define VIDEO_CODEC_WMV9			2
#define VIDEO_CODEC_H264			3
#define VIDEO_CODEC_H264PLUS		4
#define VIDEO_CODEC_XVID			5
#define VIDEO_CODEC_VP8				6
#define VIDEO_CODEC_VP9				7


//
//视频输入端子类型定义
//
#define VIDEO_INPUT_TUNER			1       //调谐视频端子
#define VIDEO_INPUT_COMPOSITE		2		//复合视频端子
#define VIDEO_INPUT_SVIDEO          3		//s视频端子 

//
//视频采集制式定义
//
#define VIDEO_STANDAND_PAL			1
#define VIDEO_STANDAND_NTSC			2
#define VIDEO_STANDAND_SECAM		3

//
//视频色彩空间属性名称定义
//Value: 0 - 100
//
#define VIDEO_COLOR_BRIGHTNESS		1		//亮度
#define VIDEO_COLOR_HUE				2		//色度 
#define VIDEO_COLOR_CONTRAST		3		//对比度  
#define VIDEO_COLOR_SATUATION		4		//饱和度
#define VIDEO_COLOR_GAMMA			5		//灰度

//
//视频显示模式
//
#define VIDEO_DISPLAY_TILED			1		//视频在窗口中平铺显示
#define VIDEO_DISPLAY_RATIOTILED	2		//视频在窗口中等比平铺显示，视频将会被裁减
#define VIDEO_DISPLAY_RATIO			3		//视频在窗口中等比显示，周围可能会有黑边

#ifndef 	TIF_CSP_I420
#define		TIF_CSP_I420            0x0001
#define		TIF_CSP_YV12            0x0002
#define		TIF_CSP_YUYV            0x0003
#define		TIF_CSP_UYVY            0x0004
#define		TIF_CSP_RGB555          0x0005
#define		TIF_CSP_RGB565          0x0006
#define		TIF_CSP_RGB24           0x0007
#define		TIF_CSP_RGB32           0x0008
#define		TIF_CSP_NV21			0x0009
#define		TIF_CSP_NV12			0x000a
#define		TIF_CSP_RGBA			0x000b  //TODO
#define		TIF_CSP_BGRA			0x000c
#endif
//
//视频RENDER事件定义
//
#define VIDEORENDER_EVENT_STATE		0X1001	//RENDER状态变更事件,上层应用此时可以获取RENDER状态

typedef  enum
{
    Rotate0 = 0,  // No rotation.
    Rotate90 = 90,  // 顺时针旋转90度
    Rotate180 = 180,  // 顺时针旋转180度
    Rotate270 = 270,  // 顺时针旋转270度
}RotationAngle;

//视频采集设备信息
typedef struct
{
#define MAX_DEVICE_STR_LENGTH 256
    WCHAR   wszDeviceIdentifier[MAX_DEVICE_STR_LENGTH];//可唯一标识一个视频设备
    WCHAR   wszDeviceName[MAX_DEVICE_STR_LENGTH];//设备名称
    WCHAR   wszDeviceDescription[MAX_DEVICE_STR_LENGTH];//设备描述
}VideoCapDeviceInfo;

typedef struct{

	int		nFrameRate;		//nfps
	int		nBitrate;		//bps
	int		nEncoderID;		//编码器ID
	FS_UINT32	dwWidth;		//视频宽度
	FS_UINT32	dwHeight;		//视频高度
}VideoRender_State;

typedef struct{
	
	int		nEncoderID;		//编码器号
	int		nEncoderMode;	//压缩模式 0-VBR 1-CBR
	int		nFrameRate;		//帧速率
	int		nVBRQuality;	//图象压缩质量 0-100 ,VBR模式有效
	int		nQuality;
	int		nBitRate;		//码流bps
	int		nKeyFrameInterval;//关键帧间隔	

#if USE_VIDEO_RORATE
    RotationAngle   rotationAngle;//视频顺时针旋转角度,目前仅安卓有此需要
#endif
}Video_Encoder_Param;

typedef struct{

	int		nCapDevIndex;	//采集设备号
	int		nWidth;			//视频宽度
	int		nHeight;		//视频高度
	int     nFrameRate;
	int		nVideoInputIndex; //视频输入端子类型
	int		nVideoStandand;	//视频制式	
	BOOL	bVideoDenoise;	//是否视频降噪
	BOOL	bVFlip;			//是否上下翻转图像
#if USE_EXTERNALVIDEOINPUT
	int		nVideoCsp;		//视频颜色空间,仅针对安卓
#endif
}Video_Capture_Param;

typedef struct{
	
	Video_Capture_Param CapParam;
	Video_Encoder_Param	EncParam;

}Video_CapEnc_Param;

typedef struct{
	
	PBYTE   pbIn;
	UINT    unInLen;
	PBYTE   pbOut;
	UINT    unOutLen;
	BYTE    bKeyFrame;
}Video_Code_Frame;

#endif
