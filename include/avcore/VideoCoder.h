#if !defined VIDEO_CODER_H
#define		 VIDEO_CODER_H

#include "VideoDefine.h"

//---------------------
//获取编码器个数
//---------------------
int 	VIDEO_Codec_GetCount();

//---------------------
//获取编码器名称
//---------------------
FS_UINT    VIDEO_Codec_GetInfo( int nIndex,WCHAR *wszName,FS_UINT nSize,int &nCodecID );

//---------------------
//创建压缩器
//EncodeType: 压缩器类型
//lpbiIn:压缩前位图格式
//Return:压缩器句柄
//-------------------
HANDLE	VIDEO_Encode_StartCompress( const Video_Encoder_Param &param,const BITMAPINFOHEADER &biIn );


//---------------------
//压缩数据
//frame：压缩数据包
//Return:返回是否成功
//----------------------
BOOL	VIDEO_Encode_Compress(HANDLE hEncoder,Video_Code_Frame &frame );


//--------------------
//停止压缩器
//hEncoder: 压缩器句柄
//--------------------
VOID	VIDEO_Encode_StopCompress(HANDLE &hEncoder);


//---------------------
//创建解压器
//CodeType:解压器句柄
//biOut:解压之后格式
//Return: 解压器句柄
//---------------------
HANDLE	VIDEO_Decode_StartDecompress( int nCodeID,const BITMAPINFOHEADER &biOut );


//-------------------
//解压图象
//hDecoder:解压器句柄
//frame:解压包
//Return: 是否解压成功
//--------------------
BOOL	VIDEO_Decode_Decompress(HANDLE hDecoder,Video_Code_Frame &frame );

//---------------------
//停止压缩器
//hDecoder:解压器句柄
//--------------------
VOID	VIDEO_Decode_StopDecompress(HANDLE &hDecoder);


#endif