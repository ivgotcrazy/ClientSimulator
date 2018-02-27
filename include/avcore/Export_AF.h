#if !defined EXPORT_AF_H
#define      EXPORT_AF_H

#include "AudioDefine.h"
#include "IPlaySyncTime.h"
#ifdef _FS_OS_WIN
#include "mmsystem.h"
#endif

//----------------------------
//16位混音
//buf1:第一路音频数据,同时是目标数据存放缓存
//buf2:第二咱音频数据
//len:样本个数
//---------------------------
VOID		 WAudio_Mix16(short* buf1, short* buf2 , FS_INT32 len);
VOID		 WAudio_Mix16_2(short* buf1, short* buf2,short *output, FS_INT32 len);
VOID		 WAudio_Mix32(FS_INT32* buf1, short* buf2,FS_INT32 *output, FS_INT32 len);
VOID		 WAudio_NegMix32(FS_INT32* buf1, short* buf2,FS_INT32 *output, FS_INT32 len);
VOID		 WAudio_NegMix16(short* buf1, short* buf2,short *output, FS_INT32 len);
VOID		 WAudio_Mix32to16(FS_INT32* buf1, short* output, FS_INT32 len, FS_UINT32& factor); 

//--------------------------
//创建音频源组
//wfxOut:要求输出的音频格式
//返回音频源组句柄
//-------------------------
HANDLE      WAudio_SourceGroup_Create( const WAVEFORMATEX &wfxOut );


//-------------------------
//判断组中是否存在指定音频源
//hGroup:组句柄
//dwSourceID:音频源ID
//返回音频源是否存在
//-------------------------
BOOL		WAudio_SourceGroup_SourceIsExist( HANDLE hGroup,FS_UINT32 dwSourceID );

//-------------------------
//向组中加入音频源
//hGroup:组句柄
//返回音频源ID
//-------------------------
FS_UINT32		WAudio_SourceGroup_AddSource( HANDLE hGroup );


BOOL		WAudio_SourceGroup_SetSyncTime( HANDLE hGroup,FS_UINT32 dwSourceID,IPlaySyncTime* pSyncTime );

//-------------------------
//从组中删除音频源
//hGroup:组句柄 
//dwSourceID:音频源ID
//-------------------------
BOOL        WAudio_SourceGroup_RemoveSource( HANDLE hGroup,FS_UINT32 dwSourceID );


//------------------------
//向音频源中写入数据
//hGroup:组句柄
//dwSourceID:音频源ID
//pbData:数据指针
//unDataLen:数据长度
//------------------------
BOOL        WAudio_SourceGroup_WriteSource( HANDLE hGroup,FS_UINT32 dwSourceID,PBYTE pbData,FS_UINT32 dwDataLen );


//------------------------
//向音频源读取数据
//hGroup:组句柄
//dwSourceID:音频源ID
//pbBuffer:数据缓存
//nReadLen:要读入的数据长度
//返回实际读入的数据长度
//------------------------
UINT        WAudio_SourceGroup_ReadSource( HANDLE hGroup,FS_UINT32 dwSourceID,PBYTE pbBuffer,UINT nReadLen );

//-------------------------
//设置音频源音量大小
//hGroup:组句柄
//dwSourceID:音频源ID
//nVolume:音量大小 0-100 
//-------------------------
VOID        WAudio_SourceGroup_SetSourceVolume( HANDLE hGroup,FS_UINT32 dwSourceID,FS_INT32 nVolume );

//-------------------------
//获取音频源音量大小
//hGroup:组句柄
//dwSourceID:音频源ID
//返回音频源音量大小
//-------------------------
FS_INT32         WAudio_SourceGroup_GetSourceVolume( HANDLE hGroup,FS_UINT32 dwSourceID );


//-------------------------
//设置音频源是否需要计算声音能值
//hGroup:组句柄
//dwSourceID:音频源ID
//bEnable:是否计算
//-------------------------
VOID        WAudio_SourceGroup_EnableSourceCalEnergy( HANDLE hGroup,FS_UINT32 dwSourceID,BOOL bEnable );

//-------------------------
//获取音频源声音能值
//hGroup:组句柄
//dwSourceID:音频源ID
//返回声音能值大小
//-------------------------
FS_INT32         WAudio_SourceGroup_GetSourceEnergy( HANDLE hGroup,FS_UINT32 dwSourceID );

//------------------------
//从组中读入数据
//hGroup:组句柄
//pbBuffer:数据缓存
//unReadLen:要读入的数据长度
//返回实际读入的数据长度
//-------------------------
UINT        WAudio_SourceGroup_ReadData( HANDLE hGroup,PBYTE pbBuffer,UINT unReadLen );

//-------------------------
//获取组的声音能值 0-100
//hGroup:组句柄
//返回能值大小
//-------------------------
INT		  WAudio_SourceGroup_GetEnergy( HANDLE hGroup );

//-------------------------
//是否允许组计算声音能值
//hGroup:组句柄
//bEnable:是否允许
//-------------------------
VOID        WAudio_SourceGroup_EnableCalEnergy( HANDLE hGroup,BOOL bEnable );

//-------------------------
//释放组
//hGroup:组句柄
//-------------------------
VOID        WAudio_SourceGroup_Destroy( HANDLE &hGroup );


//-------------------------
//创建音频处理器
//wfxIn:音频的输入格式
//返回音频处理器句柄
//------------------------
HANDLE      WAudio_Processer_Create(const WAVEFORMATEX &wfxIn );

//设置 音频前处理的参数
BOOL		WAudio_Processer_SetParam(HANDLE hProcesser,FS_INT32 nParamType, void *pValue,FS_INT32 nValueSize );

//获取 音频前处理的参数
BOOL		WAudio_Processer_GetParam(HANDLE hProcesser,FS_INT32 nParamType, void *pValue,FS_INT32 nValueSize );

//-------------------------
//获取声音能值 0-100
//返回能值大小
//-------------------------
INT			WAudio_Processer_GetEnergy( HANDLE hProcesser );

//------------------------
//处理音频数据
//hProcesser:处理器句柄
//head:音频处理包
//返回处理是否成功
//当返回成功,且head.unDesUsed =0 时,表示当前为静音数据
//------------------------
BOOL        WAudio_Processer_Process( HANDLE hProcesser,AudioStreamPacket &head );

//
//获取输入数据块的大小
//hProcesser:处理器句柄
//
INT			WAudio_Processer_GetInputBlockSize( HANDLE hProcesser );


//------------------------
//释入音频处理器
//hProcesser:音频处理器句柄
//------------------------
VOID        WAudio_Processer_Destroy( HANDLE &hProcesser );


//------------------------
//获取音频处理器所能支持的压缩格式个数
//bType 编码器的类型,默认为0x01,会议室使用的编码器类型
//------------------------
BYTE		WAudio_GetEncoderCount();

//-----------------------
//获取压缩格式的名称
//bCodeIndex:压缩格式索引: 0 - (最大格式个数-1)
//szName:名称缓存
//unSize:缓存大小
//nBitrate:编码后的码流
//bType 编码器的类型,默认为0x01,会议室使用的编码器类型
//返回写入缓存的字节数
//-----------------------
FS_UINT        WAudio_GetEncoderInfo(BYTE bCodeIndex, BYTE& bCodeID,unsigned int &nBitrate,WCHAR *wszName,UINT unSize );

//-----------------------
//获取编码器参数
//bFormatID:压缩格式ID
//wfx:音频格式
//返回是否成功
//----------------------
BOOL        WAudio_GetEncoderParam( BYTE bCodecID,WAVEFORMATEX &wfx,UINT& nInBlockSize );

#endif
