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
//��Ƶ�ɼ��ص�����
//lpobj:		�ϲ����ָ��
//pbData:		����ָ��
//dwDataLen:	���ݳ���
//bKeyFrame:	�Ƿ�Ϊ�ؼ�֡
//---------------------------------
typedef LONG (*VideoCapCallBack)(LPVOID lpObj,PBYTE pbData,FS_UINT32 dwDataLen,BOOL bKeyFrame );

//---------------------------------
//��Ƶԭʼ���ݻص�����
//lpobj:		�ϲ����ָ��
//pbmih:		ͼ���ʽ
//pbData:		����ָ��
//dwDataLen:	���ݳ���
//---------------------------------
typedef LONG (*VideoRawDataCallBack)(LPVOID lpObj,BITMAPINFOHEADER* pbmih,PBYTE pbData,FS_UINT32 dwDataLen );
	
//
//��Ƶѹ��ģʽ����
//
#define VIDEO_ENCODER_MODE_VBR		0
#define VIDEO_ENCODER_MODE_CBR		1
#define VIDEO_ENCODER_MODE_ABR		2

//
//��Ƶѹ����ID����
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
//��Ƶ����������Ͷ���
//
#define VIDEO_INPUT_TUNER			1       //��г��Ƶ����
#define VIDEO_INPUT_COMPOSITE		2		//������Ƶ����
#define VIDEO_INPUT_SVIDEO          3		//s��Ƶ���� 

//
//��Ƶ�ɼ���ʽ����
//
#define VIDEO_STANDAND_PAL			1
#define VIDEO_STANDAND_NTSC			2
#define VIDEO_STANDAND_SECAM		3

//
//��Ƶɫ�ʿռ��������ƶ���
//Value: 0 - 100
//
#define VIDEO_COLOR_BRIGHTNESS		1		//����
#define VIDEO_COLOR_HUE				2		//ɫ�� 
#define VIDEO_COLOR_CONTRAST		3		//�Աȶ�  
#define VIDEO_COLOR_SATUATION		4		//���Ͷ�
#define VIDEO_COLOR_GAMMA			5		//�Ҷ�

//
//��Ƶ��ʾģʽ
//
#define VIDEO_DISPLAY_TILED			1		//��Ƶ�ڴ�����ƽ����ʾ
#define VIDEO_DISPLAY_RATIOTILED	2		//��Ƶ�ڴ����еȱ�ƽ����ʾ����Ƶ���ᱻ�ü�
#define VIDEO_DISPLAY_RATIO			3		//��Ƶ�ڴ����еȱ���ʾ����Χ���ܻ��кڱ�

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
//��ƵRENDER�¼�����
//
#define VIDEORENDER_EVENT_STATE		0X1001	//RENDER״̬����¼�,�ϲ�Ӧ�ô�ʱ���Ի�ȡRENDER״̬

typedef  enum
{
    Rotate0 = 0,  // No rotation.
    Rotate90 = 90,  // ˳ʱ����ת90��
    Rotate180 = 180,  // ˳ʱ����ת180��
    Rotate270 = 270,  // ˳ʱ����ת270��
}RotationAngle;

//��Ƶ�ɼ��豸��Ϣ
typedef struct
{
#define MAX_DEVICE_STR_LENGTH 256
    WCHAR   wszDeviceIdentifier[MAX_DEVICE_STR_LENGTH];//��Ψһ��ʶһ����Ƶ�豸
    WCHAR   wszDeviceName[MAX_DEVICE_STR_LENGTH];//�豸����
    WCHAR   wszDeviceDescription[MAX_DEVICE_STR_LENGTH];//�豸����
}VideoCapDeviceInfo;

typedef struct{

	int		nFrameRate;		//nfps
	int		nBitrate;		//bps
	int		nEncoderID;		//������ID
	FS_UINT32	dwWidth;		//��Ƶ���
	FS_UINT32	dwHeight;		//��Ƶ�߶�
}VideoRender_State;

typedef struct{
	
	int		nEncoderID;		//��������
	int		nEncoderMode;	//ѹ��ģʽ 0-VBR 1-CBR
	int		nFrameRate;		//֡����
	int		nVBRQuality;	//ͼ��ѹ������ 0-100 ,VBRģʽ��Ч
	int		nQuality;
	int		nBitRate;		//����bps
	int		nKeyFrameInterval;//�ؼ�֡���	

#if USE_VIDEO_RORATE
    RotationAngle   rotationAngle;//��Ƶ˳ʱ����ת�Ƕ�,Ŀǰ����׿�д���Ҫ
#endif
}Video_Encoder_Param;

typedef struct{

	int		nCapDevIndex;	//�ɼ��豸��
	int		nWidth;			//��Ƶ���
	int		nHeight;		//��Ƶ�߶�
	int     nFrameRate;
	int		nVideoInputIndex; //��Ƶ�����������
	int		nVideoStandand;	//��Ƶ��ʽ	
	BOOL	bVideoDenoise;	//�Ƿ���Ƶ����
	BOOL	bVFlip;			//�Ƿ����·�תͼ��
#if USE_EXTERNALVIDEOINPUT
	int		nVideoCsp;		//��Ƶ��ɫ�ռ�,����԰�׿
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
