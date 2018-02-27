#ifndef __EXPORT_A_H__
#define __EXPORT_A_H__

#ifdef _WIN32
#include <mmsystem.h>
#endif
#include "AudioDefine.h"
//---------------------
//音频数据回调函数
//lpObj:		调用对象指针
//dwUserData:	No use
//pbData:		数据指针
//dwDataLen:	数据长度
//---------------------
typedef FS_INT32  (*AudioDataCallBack)(LPVOID lpObj,FS_UINT dwUserData,PBYTE pbData,FS_UINT32 dwDataLen);

#if (defined UNICODE) || (defined _UNICODE)
	typedef LogPrintW LogPrintT;
#else
	typedef LogPrintA LogPrintT;
#endif

//------------------------------------------
HANDLE		WAudio_Create( const WAVEFORMATEX &wfx );
void		WAudio_Destroy( HANDLE hAudio );

//-------------------------------
INT			WAudio_GetCapDevicesCount( HANDLE hAudio );
FS_INT			WAudio_GetCapDeviceInfo( HANDLE hAudio,UINT unDevID,WCHAR* szName,UINT unSize );

INT			WAudio_GetPlayDevicesCount( HANDLE hAudio );
INT			WAudio_GetPlayDeviceInfo( HANDLE hAudio,UINT unDevID,WCHAR* szName,UINT unSize );

//------------------------------
BOOL		WAudio_StartCapture( HANDLE hAudio,int nDeviceID,LPVOID lpObj,AudioDataCallBack callback);
void		WAudio_StopCapture( HANDLE hAudio );

//----------------------------------
BOOL		WAudio_StartPlay( HANDLE hAudio,int nDeviceID,LPVOID lpObj,AudioDataCallBack callback);
void		WAudio_StopPlay( HANDLE hAudio );

//设置/获取音频设备的的参数
BOOL		WAudio_SetParam( HANDLE hAudio,int nParamType,void *pValue,int nValueSize);
BOOL		WAudio_GetParam( HANDLE hAudio,int nParamType,void *pValue,int nValueSize);

#ifdef _FS_OS_IOS
void		WAudio_SetLogFunc( LogPrintW pLogFun );
#else
void		WAudio_SetLogFunc( LogPrintT pLogFun );
#endif

#endif