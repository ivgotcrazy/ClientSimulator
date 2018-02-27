#ifndef __AV_DEVICE_PLUGIN_H
#define __AV_DEVICE_PLUGIN_H

#include "wbasetype.h"
#include "wcombase.h"

//音视频插件类型定义
#define AVPLUGIN_TYPE_FILE		0x0001	//文件流
#define AVPLUGIN_TYPE_RTSP		0x0002	//RTSP流
#define AVPLUGIN_TYPE_RTMP		0x0003	//RTMP流
#define AVPLUGIN_TYPE_MMS		0x0004	//MMS流

#define AVPLUGIN_TYPE_IPC		0x0101	//IP Camara
#define AVPLUGIN_TYPE_DVR		0x0102	//DVR
#define AVPLUGIN_TYPE_NVR		0x0103	//NVR

#define AVPLUGIN_TYPE_SCREEN	0x0201	//屏幕流

#define AVPLUGIN_TYPE_H323		0x0301	//H323对接
#define AVPLUGIN_TYPE_SIP		0x0302	//SIP对接

//插件能力定义
#define AVPLUGIN_CAPA_AUDIOOUT_S		0x0001	//单路音频输出
#define AVPLUGIN_CAPA_VIDEOOUT_S		0x0002	//单路视频输出
#define AVPLUGIN_CAPA_AUDIOIN_S			0x0004	//单路音频输入
#define AVPLUGIN_CAPA_VIDEOIN_S			0x0008	//单路视频输入
#define AVPLUGIN_CAPA_MULTI_OBJ			0x0010	//创建多个插件对象

#define AVPLUGIN_MEDIATYPE_AUDIO		0x0001	//音频
#define AVPLUGIN_MEDIATYPE_VIDEO		0x0002	//视频

typedef struct{
	int		nSize;
	FS_UINT32	dwFourcCC;			//I420必须支持
	int 	nFrameRate;
	int		nWidth;
	int		nHeight;
	int		nBitCount;
	int 	nSizeImage;
}AVPluginVideoFormat;

typedef struct{
	int		nSize;
	int		nFormatTag;			//目前只支持PCM格式
	int 	nSamplePerSecond;
	int		nChannels;
	int		nBitsPerSample;
}AVPluginAudioFormat;

typedef struct{
	FS_UINT32	dwSize;			//结构体大小
	FS_UINT32	dwMediaType;	//媒体类型
	void *	pFormat;		//媒体格式，为空时格式与上一个Sample相同
							//音频为 AVPluginAudioFormat *
							//视频为 AVPluginVideoFormat *
	FS_UINT32	dwFormatSize;	//格式大小
	FS_UINT32	dwTimeStamp;	//样本时间戳
	WORD 	wDuration;		//样本时长
	PBYTE 	pbData;		//数据指针
	long	dwDataLen;		//数据长度
}AVPluginSample;

//数据回调
typedef int	 (CALLBACK *AVPLUGIN_MEDIACALLBACK)( AVPluginSample* pSample, FS_UINT dwUserData);

typedef struct{
	FS_UINT32		dwSize;			//结构体大小
	GUID		guid;			//插件ID,唯一标识
	FS_UINT32		dwVersion;		//插件版本
	FS_UINT32		dwType;			//插件类型
	FS_UINT32		dwCapa;			//插件能力
	WCHAR		wszName[64];	//插件名称
}AVPluginLibInfo;

//插件接口定义
typedef struct{
	AVPluginLibInfo 	info;			//插件信息
	//创建插件
	HANDLE		( STDAPICALLTYPE* Create)( LPUNKNOWN pFactory,WCHAR* wszConfigFilePath );
	//设置语言编码
	void		( STDAPICALLTYPE* SetLanCode )( HANDLE hPlugin ,int nLanCode );
	//配置插件，配置参数将自动保存在设置的配置文件中
	void		( STDAPICALLTYPE* Config )( HANDLE hPlugin ,HWND hWndParent );
	//设置是否允许数据回调
	void		( STDAPICALLTYPE* EnableOutput )(HANDLE hPlugin, FS_UINT32 dwMediaType,BOOL bEnable );
	//设置数据回调函数
	void		( STDAPICALLTYPE* SetOutputCallback )(HANDLE hPlugin, FS_UINT32 dwMediaType,AVPLUGIN_MEDIACALLBACK	lpCallback,FS_UINT dwUserData );
	//设置是否允许输入数据
	void		( STDAPICALLTYPE* EnableInput )(HANDLE hPlugin, FS_UINT32 dwMediaType,BOOL bEnable );
	//向插件输入数据
	void		( STDAPICALLTYPE* InputSample )(HANDLE hPlugin, AVPluginSample* pSample);
	//查询输出格式
	int			( STDAPICALLTYPE* QueryOutputFormat)(HANDLE hPlugin,FS_UINT32 dwMediaType,int nIndex,void* pFormat,FS_UINT32 dwFormatSize );
	//设置输出格式
	int			( STDAPICALLTYPE* SetOutputFormat)(HANDLE hPlugin,FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize );
	//获取当前输出格式
	int			( STDAPICALLTYPE* GetOutputFormat)(HANDLE hPlugin,FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize );
	//销毁插件
	void		( STDAPICALLTYPE* Destroy )( HANDLE hPlugin );
}FMAVPluginLib;

typedef HRESULT	(STDAPICALLTYPE*	GetAVPluginCount )	( int* pCount );
typedef HRESULT	(STDAPICALLTYPE*	GetAVPluginInfo )	( int nIndex, FMAVPluginLib * pPlugin );

#define FMAVPLUGIN_GETCOUNT_FUNNAME		"FMAVPluginGetCount"
#define FMAVPLUGIN_GETINFO_FUNNAME		"FMAVPluginGetInfo"

//获取支持的插件数量
STDAPI	FMAVPluginGetCount( int* pCount );
//获取插件的详细信息
STDAPI	FMAVPluginGetInfo( int nIndex, FMAVPluginLib * pPlugin );

#endif