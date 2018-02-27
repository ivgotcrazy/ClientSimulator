#ifndef __IWAUDIO_DEVICE_H
#define __IWAUDIO_DEVICE_H

#include "wcombase.h"
#include "IAudioSource.h"
#include "IPlaySyncTime.h"
#ifdef _WIN32
#include <mmsystem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
	

	// AudioDevice Component's GUID
	// {F0645FDB-A8E3-45bd-8C1A-54237A1F6EBF}
	DEFINE_GUID( CLSID_AudioDevice, 
		0xf0645fdb, 0xa8e3, 0x45bd, 0x8c, 0x1a, 0x54, 0x23, 0x7a, 0x1f, 0x6e, 0xbf);

	// IAudioDevice's GUID
	// {DC26810D-D3CC-48bf-94BB-E56B7FAE58BA}
	DEFINE_GUID(IID_IAudioDevice, 
		0xdc26810d, 0xd3cc, 0x48bf, 0x94, 0xbb, 0xe5, 0x6b, 0x7f, 0xae, 0x58, 0xba);	
	
	//----------------------------------------------------------------------------
	// IAudioDevice
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioDevice, IUnknown)
	{
		//
		//获取音频采集设备个数
		//
		STDMETHOD_( int,GetCapDevicesCount ) ( THIS_ ) PURE;
		//
		//获取音频采集设备信息
		//
		STDMETHOD( GetCapDeviceInfo ) (THIS_ int nDevIndex,WCHAR *szDevName,UINT nSize ) PURE;
		//
		//获取音频播放设备个数
		//
		STDMETHOD_( int,GetPlayDevicesCount ) ( THIS_ ) PURE;
		//
		//获取音频播放设备信息
		//
		STDMETHOD( GetPlayDeviceInfo ) (THIS_ int nDevIndex,WCHAR *szDevName,UINT nSize ) PURE;
		//
		//获取编码器个数
		//
		STDMETHOD_( int,GetEncoderCount ) ( THIS_ ) PURE;
		//
		//获取编码器信息
		//
		STDMETHOD( GetEncoderInfo )( int nEncoderIndex,int *pEncoderID,int *pBitrate,WCHAR *szEncoderName,UINT nSize ) PURE;
		//
		//启动音频采集
		//
		STDMETHOD( StartCapture )( THIS_ int nDevIndex ) PURE;
		//
		//停止音频采集
		//
		STDMETHOD( StopCapture )( THIS_ ) PURE;
		//
		//启动音频播放
		//
		STDMETHOD( StartPlay )( THIS_ int nDevIndex ) PURE;
		//
		//停止音频播放
		//
		STDMETHOD( StopPlay )( THIS_ ) PURE;
		//
		//音频采集数据回调
		//
		STDMETHOD( AddCapDataSink )( THIS_ IAudioDataSink *pSink,FS_UINT dwUserData  ) PURE;

		STDMETHOD( RemoveCapDataSink )( THIS_ IAudioDataSink *pSink ) PURE;
		//
		//音频采集数据回调
		//
		STDMETHOD( AddPlayDataSink )( THIS_ IAudioDataSink *pSink,FS_UINT dwUserData  ) PURE;
		 
		STDMETHOD( RemovePlayDataSink )( THIS_ IAudioDataSink *pSink ) PURE;
		//
		//获取音频播放数据格式
		//
		STDMETHOD( GetPlayDataFormat)( THIS_ WAVEFORMATEX *pWfx ) PURE;
		//
		//设置参数
		//
		STDMETHOD( SetParam )( THIS_ int nParamType,void *pValue,int nValueSize ) PURE;
		//
		//获取参数
		//
		STDMETHOD( GetParam )( THIS_ int nParamType,void *pValue,int nValueSize ) PURE;
		//
		//增加音频源
		//
		STDMETHOD_( FS_UINT32,AddSource )( THIS_ ) PURE;

		STDMETHOD( SetSyncTime )( THIS_ FS_UINT32 dwSourceID,IPlaySyncTime* pSyncTime ) PURE;
		//
		//删除音频源
		//
		STDMETHOD( RemoveSource )( THIS_ FS_UINT32 dwSourceID ) PURE;
		//
		//测试音频源是否存在
		//
		STDMETHOD_( BOOL,SourceIsExist )( THIS_ FS_UINT32 dwSourceID ) PURE;
		//
		//向音频源写入数据
		//
		STDMETHOD( WriteSource )( THIS_ FS_UINT32 dwSourceID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;
		//
		//设置音频源音量
		//
		STDMETHOD( SetSourceVolume )( THIS_ FS_UINT32 dwSourceID,int nVolume ) PURE;
		//
		//获取音频源音量
		//
		STDMETHOD( GetSourceVolume )( THIS_ FS_UINT32 dwSourceID,int *pVolume,int *pMaxVolume,int *pMinVolume ) PURE;
		//
		//获取音频源声音能值
		//
		STDMETHOD( GetSourceEnergy )( THIS_ FS_UINT32 dwSourceID,int *pEnergy,int *pMaxEnergy,int *pMinEnergy ) PURE;
		//
		//获取采集声音能值
		//
		STDMETHOD( GetCapEnergy )( THIS_ int *pEnergy,int *pMaxEnergy,int *pMinEnergy ) PURE;
		//
		//获取播放声音能值
		//
		STDMETHOD( GetPlayEnergy )( THIS_ int *pEnergy,int *pMaxEnergy,int *pMinEnergy ) PURE;
		//
		//设置采集音量
		//
		STDMETHOD( SetCapVolume )( THIS_ int nVolume ) PURE;
		//
		//获取采集音量
		//
		STDMETHOD( GetCapVolume )( THIS_ int *pVolume,int *pMaxVolume,int *pMinVolume ) PURE;
		//
		//设置播放音量
		//
		STDMETHOD( SetPlayVolume )( THIS_ int nVolume ) PURE;
		//
		//获取播放音量
		//
		STDMETHOD( GetPlayVolume )( THIS_ int *pVolume,int *pMaxVolume,int *pMinVolume ) PURE;
		//
		//设置采集静音
		//
		STDMETHOD( SetCapMute )( THIS_ BOOL bMute ) PURE;
		//
		//获取采集静音
		//
		STDMETHOD( GetCapMute )( THIS_ BOOL *pMute ) PURE;
		//
		//设置播放静音
		//
		STDMETHOD( SetPlayMute )( THIS_ BOOL bMute ) PURE;
		//
		//获取播放静音
		//
		STDMETHOD( GetPlayMute )( THIS_ BOOL *pMute ) PURE;
		//
		//设置采集输入类型
		// 
		STDMETHOD( SetCapInputType )( THIS_ FS_UINT32 dwInputType ) PURE;
		//
		//获取采集输入类型
		//
		STDMETHOD( GetCapInputType )( THIS_ FS_UINT32 *pdwInputType ) PURE;
		//
		//设置是否播放本地音频
		//
		STDMETHOD( SetPlayLocal )( THIS_ BOOL bPlay ) PURE;
		//
		//获取是否播放本地音频
		//
		STDMETHOD( GetPlayLocal )( THIS_ BOOL *pPlay ) PURE;
		//
		//设置播放软静音
		//
		STDMETHOD( SetPlaySoftMute )( THIS_ BOOL bMute ) PURE;
		//
		//获取播放软静音
		//
		STDMETHOD( GetPlaySoftMute )( THIS_ BOOL *pMute ) PURE;

		STDMETHOD( SetAudioEngine )( THIS_ int nEngineIndex ) PURE;

		STDMETHOD( StartAudioDevice )( THIS_ int nCapDev,int nPlayDev ) PURE;

		STDMETHOD( StopAudioDevice )( THIS_ ) PURE;
	};

	// AudioProcessor Component's GUID
	// {A18A0F2B-0503-4da0-9595-0261144A72EA}
	DEFINE_GUID(CLSID_AudioProcessor, 
		0xa18a0f2b, 0x503, 0x4da0, 0x95, 0x95, 0x2, 0x61, 0x14, 0x4a, 0x72, 0xea);

	// IAudioProcessor's GUID
	// {49DC2814-76DD-47ff-A382-2A4A7C6CC3EA}
	DEFINE_GUID(IID_IAudioProcessor, 
		0x49dc2814, 0x76dd, 0x47ff, 0xa3, 0x82, 0x2a, 0x4a, 0x7c, 0x6c, 0xc3, 0xea);
	
	//----------------------------------------------------------------------------
	// IAudioProcessor
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioProcessor, IUnknown)
	{
		//创建音频处理器
		//pwfxIn:音频的输入格式
		STDMETHOD( Create ) ( THIS_ WAVEFORMATEX* pwfxIn ) PURE;
	
		//释入音频处理器
		STDMETHOD( Destroy ) ( THIS_ ) PURE;
		
		//设置 音频前处理的参数
		STDMETHOD( SetParam ) ( THIS_ int nParamType, void *pValue,int nValueSize ) PURE;
		
		//获取声音能值
		//返回能值大小 0-100
		STDMETHOD_( int,GetEnergy ) ( THIS_ ) PURE;
		
		//处理音频数据
		//pPack:音频处理包
		//返回处理是否成功
		//当返回成功,且head.unDesUsed =0 时,表示当前为静音数据
		STDMETHOD( Process ) ( THIS_ AudioStreamPacket* pPack) PURE;
		
		//获取输入数据块的大小
		STDMETHOD_( int,GetInputBlockSize ) ( THIS_ ) PURE;

        //获取音频前处理的参数
        STDMETHOD( GetParam ) ( THIS_ int nParamType, void *pValue,int nValueSize ) PURE;
	};


	// AudioGroup Component's GUID
	// {A1557819-07D6-4392-A9DB-F3D58A8C0F9A}
	DEFINE_GUID(CLSID_AudioGroup, 
		0xa1557819, 0x7d6, 0x4392, 0xa9, 0xdb, 0xf3, 0xd5, 0x8a, 0x8c, 0xf, 0x9a);
	
	// IAudioGroup's GUID
	// {20259CFC-C0AB-458e-A7CF-EA7018C9E14B}
	DEFINE_GUID(IID_IAudioGroup, 
		0x20259cfc, 0xc0ab, 0x458e, 0xa7, 0xcf, 0xea, 0x70, 0x18, 0xc9, 0xe1, 0x4b);
	
	//----------------------------------------------------------------------------
	// IAudioGroup
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IAudioGroup, IUnknown)
	{
		//16位混音
		//buf1:第一路音频数据,同时是目标数据存放缓存
		//buf2:第二咱音频数据
		//nSamples:样本个数
		//---------------------------
		STDMETHOD( Mix16 )(short* buf1, short* buf2 , int nSamples) PURE;
		
		//16位混音
		//buf1:第一路音频数据
		//buf2:第二咱音频数据
		//output:目标数据存放缓存
		//nSamples:样本个数
		STDMETHOD( Mix16_2)(short* buf1, short* buf2,short *output, int nSamples) PURE;

		//创建音频源组
		//pwfxOut:要求输出的音频格式
		STDMETHOD( Create ) ( THIS_ WAVEFORMATEX* pwfxOut ) PURE;

		//释入音频源组
		STDMETHOD( Destroy ) ( THIS_ ) PURE;

		//判断组中是否存在指定音频源
		//dwSourceID:音频源ID
		//返回音频源是否存在
		STDMETHOD_(BOOL,SourceIsExist)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//向组中加入音频源
		//返回音频源ID
		STDMETHOD_(FS_UINT32,AddSource)( THIS_ ) PURE;

		//设置音频源同步时钟
		STDMETHOD(SetSyncTime)( THIS_ FS_UINT32 dwSourceID,IPlaySyncTime* pSyncTime ) PURE;

		//从组中删除音频源
		//dwSourceID:音频源ID
		STDMETHOD(RemoveSource)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//向音频源中写入数据
		//dwSourceID:音频源ID
		//pbData:数据指针
		//unDataLen:数据长度
		STDMETHOD(WriteSource)( THIS_ FS_UINT32 dwSourceID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;

		//向音频源读取数据
		//dwSourceID:音频源ID
		//pbBuffer:数据缓存
		//nReadLen:要读入的数据长度
		//返回实际读入的数据长度
		STDMETHOD_(UINT,ReadSource)( THIS_ FS_UINT32 dwSourceID,PBYTE pbBuffer,UINT nReadLen ) PURE;

		//设置音频源音量大小
		//dwSourceID:音频源ID
		//nVolume:音量大小 0-100 
		STDMETHOD(SetSourceVolume)( THIS_ FS_UINT32 dwSourceID,int nVolume ) PURE;

		//获取音频源音量大小
		//dwSourceID:音频源ID
		//返回音频源音量大小
		STDMETHOD_(int,GetSourceVolume)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//设置音频源是否需要计算声音能值
		//dwSourceID:音频源ID
		//bEnable:是否计算
		STDMETHOD(EnableSourceCalEnergy)( THIS_ FS_UINT32 dwSourceID,BOOL bEnable ) PURE;

		//获取音频源声音能值
		//dwSourceID:音频源ID
		//返回声音能值大小
		STDMETHOD_(int,GetSourceEnergy)( THIS_ FS_UINT32 dwSourceID ) PURE;

		//从组中读入数据
		//pbBuffer:数据缓存
		//unReadLen:要读入的数据长度
		//返回实际读入的数据长度
		STDMETHOD_(UINT,ReadData)( THIS_ PBYTE pbBuffer,UINT unReadLen ) PURE;

		//获取组的声音能值 0-100
		//返回能值大小
		STDMETHOD_(int,GetEnergy)( THIS_ ) PURE;

		//是否允许组计算声音能值
		//bEnable:是否允许
		STDMETHOD(EnableCalEnergy)( THIS_ BOOL bEnable ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif