#ifndef __VIDEO_CODEC_PLUGIN_H
#define __VIDEO_CODEC_PLUGIN_H

#include "wbasetype.h"
#include "wcombase.h"
#include "VideoDefine.h"

typedef struct{

	DWORD	dwVersion;
	int		nCodecID;
	BOOL	bSupportEnc;
	BOOL	bSupportDec;
	WCHAR	wszName[64];

}VideoCodecPluginInfo;

//视频编码器动态库接口定义
typedef struct{
		
	void    ( STDAPICALLTYPE* DllGetInfo)		( VideoCodecPluginInfo *pInfo );
	
	HANDLE	( STDAPICALLTYPE* DllEncOpen )		( const Video_Encoder_Param* pParam,const BITMAPINFOHEADER *pbiIn );
		
	BOOL	( STDAPICALLTYPE* DllEncode )		( HANDLE hEncoder,Video_Code_Frame *pFrame );
		
	BOOL	( STDAPICALLTYPE* DllEncConfig )	( HANDLE hEncoder,const Video_Encoder_Param* pParam );

	VOID	( STDAPICALLTYPE* DllEncClose )		(HANDLE hEncoder);	
	
	HANDLE	( STDAPICALLTYPE* DllDecOpen )		( const BITMAPINFOHEADER *pbiOut );
	
	BOOL	( STDAPICALLTYPE* DllDecode )		(HANDLE hDecoder,Video_Code_Frame *pFrame );
	
	VOID	( STDAPICALLTYPE* DllDecClose )		(HANDLE hDecoder);	

}VideoCodecDll;

typedef HRESULT	(STDAPICALLTYPE*	LoadVideoCodec )		( VideoCodecDll *pDll );
typedef HRESULT	(STDAPICALLTYPE*	GetVideoCodecCount )	( int* pCount );
typedef HRESULT	(STDAPICALLTYPE*	GetVideoCodecInfo )		( int nIndex,VideoCodecDll* pDll );

#define FMVCODEC_FUNNAME			"FMVCodec"
#define FMVCODECGETCOUNT_FUNNAME	"FMVCodecGetCount"
#define FMVCODECGETINFO_FUNNAME		"FMVCodecGetInfo"

STDAPI	FMVCodec( VideoCodecDll *pDll );
STDAPI	FMVCodecGetCount( int* pCount );
STDAPI	FMVCodecGetInfo( int nIndex,VideoCodecDll* pDll );

#endif
