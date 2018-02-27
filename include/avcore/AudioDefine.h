#ifndef AUDIO_DEFINE_H
#define AUDIO_DEFINE_H

//***********设置/获取音频设备的的参数***************

#define		AUDIO_PARAM_AEC				0X1001	//回音消除(0-1)	0-禁用 1-启用
#define		AUDIO_PARAM_ANS				0X1002	//降噪(0-3) 0-禁用 1-弱 2-中 3-强
#define		AUDIO_PARAM_VAD				0X1003	//静音检测(0-1) 0-禁用 1-启用
#define		AUDIO_PARAM_AGC				0X1004	//自动增益(0-3)0-禁用 1-弱 2-中 3-强
#define		AUDIO_PARAM_ENCODER			0X1006	//采集后使用的编码格式
#define		AUDIO_PARAM_CAPAUTOVOLUME	0x1007	//采集设备音量自动调节(0-1) 0-禁用 1-启用
#define		AUDIO_PARAM_CALENERGY		0x1008	//计算音频能量(0-1) 0-禁用 1-启用

#define     AUDIO_PARAM_SOUNDTOUCH      0x1009  //变音设置

#define		AUDIO_PARAM_CAPVOL			0x1010	//获取/设置系统采集设备音量的大小(0 - 100)
#define		AUDIO_PARAM_PLAYVOL			0x1011	//获取/设置系统播放设备音量的大小(0 - 100)
#define		AUDIO_PARAM_CAPSOFTMUTE		0x1012	//获取/设置本软件采集设备的静音状态(0-1)0-正常 1-静音
#define		AUDIO_PARAM_PLAYSOFTMUTE	0x1013	//获取/设置本软件播放设备的静音状态(0-1)0-正常 1-静音
#define		AUDIO_PARAM_PLAYDEVMUTE		0x1014	//获取/设置操作系统播放设备的静音状态(0-1)0-正常 1-静音
//MIXERLINE_COMPONENTTYPE_SRC_ANALOG:		Mix
//MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE		Modem
//MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:		Video
//MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY:	Aux
//MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE:	Micro
//MIXERLINE_COMPONENTTYPE_SRC_LINE:			LineIn
//MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC:	CompactDisc
#define		AUDIO_PARAM_CAPINPUT		0x1015	//获取/设置采集的输入类型

//音频处理包头
typedef struct{
	
	PBYTE pbSrc;		//源数据指针
	UINT  unSrcLen;		//源数据长度
	UINT  unSrcUsed;	//所使用的源数据长度
	
	PBYTE pbDes;		//目标缓存指针
	UINT  unDesLen;		//目标缓存大小
	UINT  unDesUsed;	//目标数据长度
	
}AudioStreamPacket;

#pragma pack(1)
typedef struct{
	
	BYTE		bCodecID:4;
	BYTE		bReserved:4;
	BYTE		bDuaration;		//ms
	DWORD		dwTimeStamp;	//ms
	BYTE		pbData[0];
}AudioFrameHeader;
#pragma pack()

#endif//AUDIO_DEFINE_H