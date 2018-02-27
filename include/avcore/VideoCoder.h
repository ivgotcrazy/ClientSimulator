#if !defined VIDEO_CODER_H
#define		 VIDEO_CODER_H

#include "VideoDefine.h"

//---------------------
//��ȡ����������
//---------------------
int 	VIDEO_Codec_GetCount();

//---------------------
//��ȡ����������
//---------------------
FS_UINT    VIDEO_Codec_GetInfo( int nIndex,WCHAR *wszName,FS_UINT nSize,int &nCodecID );

//---------------------
//����ѹ����
//EncodeType: ѹ��������
//lpbiIn:ѹ��ǰλͼ��ʽ
//Return:ѹ�������
//-------------------
HANDLE	VIDEO_Encode_StartCompress( const Video_Encoder_Param &param,const BITMAPINFOHEADER &biIn );


//---------------------
//ѹ������
//frame��ѹ�����ݰ�
//Return:�����Ƿ�ɹ�
//----------------------
BOOL	VIDEO_Encode_Compress(HANDLE hEncoder,Video_Code_Frame &frame );


//--------------------
//ֹͣѹ����
//hEncoder: ѹ�������
//--------------------
VOID	VIDEO_Encode_StopCompress(HANDLE &hEncoder);


//---------------------
//������ѹ��
//CodeType:��ѹ�����
//biOut:��ѹ֮���ʽ
//Return: ��ѹ�����
//---------------------
HANDLE	VIDEO_Decode_StartDecompress( int nCodeID,const BITMAPINFOHEADER &biOut );


//-------------------
//��ѹͼ��
//hDecoder:��ѹ�����
//frame:��ѹ��
//Return: �Ƿ��ѹ�ɹ�
//--------------------
BOOL	VIDEO_Decode_Decompress(HANDLE hDecoder,Video_Code_Frame &frame );

//---------------------
//ֹͣѹ����
//hDecoder:��ѹ�����
//--------------------
VOID	VIDEO_Decode_StopDecompress(HANDLE &hDecoder);


#endif