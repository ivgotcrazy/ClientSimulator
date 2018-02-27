#ifndef __AV_DEVICE_PLUGIN_H
#define __AV_DEVICE_PLUGIN_H

#include "wbasetype.h"
#include "wcombase.h"

//����Ƶ������Ͷ���
#define AVPLUGIN_TYPE_FILE		0x0001	//�ļ���
#define AVPLUGIN_TYPE_RTSP		0x0002	//RTSP��
#define AVPLUGIN_TYPE_RTMP		0x0003	//RTMP��
#define AVPLUGIN_TYPE_MMS		0x0004	//MMS��

#define AVPLUGIN_TYPE_IPC		0x0101	//IP Camara
#define AVPLUGIN_TYPE_DVR		0x0102	//DVR
#define AVPLUGIN_TYPE_NVR		0x0103	//NVR

#define AVPLUGIN_TYPE_SCREEN	0x0201	//��Ļ��

#define AVPLUGIN_TYPE_H323		0x0301	//H323�Խ�
#define AVPLUGIN_TYPE_SIP		0x0302	//SIP�Խ�

//�����������
#define AVPLUGIN_CAPA_AUDIOOUT_S		0x0001	//��·��Ƶ���
#define AVPLUGIN_CAPA_VIDEOOUT_S		0x0002	//��·��Ƶ���
#define AVPLUGIN_CAPA_AUDIOIN_S			0x0004	//��·��Ƶ����
#define AVPLUGIN_CAPA_VIDEOIN_S			0x0008	//��·��Ƶ����
#define AVPLUGIN_CAPA_MULTI_OBJ			0x0010	//��������������

#define AVPLUGIN_MEDIATYPE_AUDIO		0x0001	//��Ƶ
#define AVPLUGIN_MEDIATYPE_VIDEO		0x0002	//��Ƶ

typedef struct{
	int		nSize;
	FS_UINT32	dwFourcCC;			//I420����֧��
	int 	nFrameRate;
	int		nWidth;
	int		nHeight;
	int		nBitCount;
	int 	nSizeImage;
}AVPluginVideoFormat;

typedef struct{
	int		nSize;
	int		nFormatTag;			//Ŀǰֻ֧��PCM��ʽ
	int 	nSamplePerSecond;
	int		nChannels;
	int		nBitsPerSample;
}AVPluginAudioFormat;

typedef struct{
	FS_UINT32	dwSize;			//�ṹ���С
	FS_UINT32	dwMediaType;	//ý������
	void *	pFormat;		//ý���ʽ��Ϊ��ʱ��ʽ����һ��Sample��ͬ
							//��ƵΪ AVPluginAudioFormat *
							//��ƵΪ AVPluginVideoFormat *
	FS_UINT32	dwFormatSize;	//��ʽ��С
	FS_UINT32	dwTimeStamp;	//����ʱ���
	WORD 	wDuration;		//����ʱ��
	PBYTE 	pbData;		//����ָ��
	long	dwDataLen;		//���ݳ���
}AVPluginSample;

//���ݻص�
typedef int	 (CALLBACK *AVPLUGIN_MEDIACALLBACK)( AVPluginSample* pSample, FS_UINT dwUserData);

typedef struct{
	FS_UINT32		dwSize;			//�ṹ���С
	GUID		guid;			//���ID,Ψһ��ʶ
	FS_UINT32		dwVersion;		//����汾
	FS_UINT32		dwType;			//�������
	FS_UINT32		dwCapa;			//�������
	WCHAR		wszName[64];	//�������
}AVPluginLibInfo;

//����ӿڶ���
typedef struct{
	AVPluginLibInfo 	info;			//�����Ϣ
	//�������
	HANDLE		( STDAPICALLTYPE* Create)( LPUNKNOWN pFactory,WCHAR* wszConfigFilePath );
	//�������Ա���
	void		( STDAPICALLTYPE* SetLanCode )( HANDLE hPlugin ,int nLanCode );
	//���ò�������ò������Զ����������õ������ļ���
	void		( STDAPICALLTYPE* Config )( HANDLE hPlugin ,HWND hWndParent );
	//�����Ƿ��������ݻص�
	void		( STDAPICALLTYPE* EnableOutput )(HANDLE hPlugin, FS_UINT32 dwMediaType,BOOL bEnable );
	//�������ݻص�����
	void		( STDAPICALLTYPE* SetOutputCallback )(HANDLE hPlugin, FS_UINT32 dwMediaType,AVPLUGIN_MEDIACALLBACK	lpCallback,FS_UINT dwUserData );
	//�����Ƿ�������������
	void		( STDAPICALLTYPE* EnableInput )(HANDLE hPlugin, FS_UINT32 dwMediaType,BOOL bEnable );
	//������������
	void		( STDAPICALLTYPE* InputSample )(HANDLE hPlugin, AVPluginSample* pSample);
	//��ѯ�����ʽ
	int			( STDAPICALLTYPE* QueryOutputFormat)(HANDLE hPlugin,FS_UINT32 dwMediaType,int nIndex,void* pFormat,FS_UINT32 dwFormatSize );
	//���������ʽ
	int			( STDAPICALLTYPE* SetOutputFormat)(HANDLE hPlugin,FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize );
	//��ȡ��ǰ�����ʽ
	int			( STDAPICALLTYPE* GetOutputFormat)(HANDLE hPlugin,FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize );
	//���ٲ��
	void		( STDAPICALLTYPE* Destroy )( HANDLE hPlugin );
}FMAVPluginLib;

typedef HRESULT	(STDAPICALLTYPE*	GetAVPluginCount )	( int* pCount );
typedef HRESULT	(STDAPICALLTYPE*	GetAVPluginInfo )	( int nIndex, FMAVPluginLib * pPlugin );

#define FMAVPLUGIN_GETCOUNT_FUNNAME		"FMAVPluginGetCount"
#define FMAVPLUGIN_GETINFO_FUNNAME		"FMAVPluginGetInfo"

//��ȡ֧�ֵĲ������
STDAPI	FMAVPluginGetCount( int* pCount );
//��ȡ�������ϸ��Ϣ
STDAPI	FMAVPluginGetInfo( int nIndex, FMAVPluginLib * pPlugin );

#endif