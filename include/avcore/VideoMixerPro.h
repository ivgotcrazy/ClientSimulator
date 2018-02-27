#ifndef AVCORE_VC12_VIDEOMIXER_VIDEOMIXERPRO_H_
#define AVCORE_VC12_VIDEOMIXER_VIDEOMIXERPRO_H_
/*##############################################################################
**File Name   : VideoMixerPro.h
**Description : ��Ƶ�ϳɿ���ǿ��Ľӿ��ļ�����ǿ����Ƶ�ϳɿ�֧��������ƵΪδ��������
���ѱ������ݣ�ͬʱ֧������ÿһ·������Ƶ�ںϳɻ����е�λ�ã�����ϳɺ��ԭʼ��Ƶ���ݡ�
**Author	  : Gerald
**Create Time : 2015.12.08
**Copyright   : Copyright 2015 Fsmeeting.com.All Rights Reserved.
##############################################################################*/
#include "IPlaySyncTime.h"

typedef struct{
	unsigned int 		nWidth;				//��Ƶ���
	unsigned int 		nHeight;			//��Ƶ�߶�
	unsigned int 		nFrameRate;			//֡����
	unsigned int   		nEncoderID;			//������ID
	unsigned int		nEncoderMode;		//ѹ��ģʽ
	unsigned int		nBitrate;			//����,bps
	unsigned int		nVBRQuality;		//����
	unsigned int 		nKeyFrameInterval;	//�ؼ�֡���
}VideoEncParam;

typedef struct{
	DWORD nGroupID;
	DWORD nStreamID;
}InputVideoID;

typedef struct{
	BOOL				bEncoded;//�Ƿ����
	union 
	{
		BITMAPINFOHEADER bmInfo;//���δ���룬ԭʼ��Ƶ������Ϣ
		VideoEncParam    encParam;//������룬������Ƶ������Ϣ
	};
	DWORD				nFrameRate;//֡��
}VideoStreamInfo;

typedef struct  
{
	DWORD	nWidth;//��Ƶ֡�Ŀ�
	DWORD	nHeight;//��Ƶ֡�ĸ�
	DWORD	nTimeStamp;//��Ƶ֡��ʱ���
	BOOL	bIsKeyFrame;//�Ƿ��ǹؼ�֡
}VideoFrameInfo;

typedef struct
{
	DWORD nLeftCoor;//���Ͻ�x����
	DWORD nTopCoor;//���Ͻ�y����
	DWORD nWidth;//���������
	DWORD nHeight;//���������
}RenderRect;

/*------------------------------------------------------------------------------
 *Description���ϳɺ����Ƶ���ݻص�����
 *lpobj      ���ص����ն���
 *pbData     ������ָ��
 *dwDataLen  �����ݳ���
 *bKeyFrame  ���Ƿ��ǹؼ�֡
------------------------------------------------------------------------------*/
typedef VOID(*VideoMixedCallBack)(LPVOID lpObj, PBYTE pbData, DWORD dwDataLen, BOOL  bKeyFrame);

//**********************************************************************
// Method:    	 VideoMixPro_Create
// Parameter: 	 [IN] pMixCallBack			�ϳ����ݻص�����
//               [IN] lpObj					�û��Զ�������	
//				 [IN] pOutputStreamInfo		����ϳɺ�ԭʼ��Ƶ���ݵĸ�ʽ
// Returns:   	 HANDLE ���ɹ������ش��������ںϳɵĶ����handle�����򷵻�
//				 NULL
//									
// Description:  ����������Ƶ�ϳɵĶ���ָ���ϳ���Ƶ�Ĳ������ϳɺ���Ƶ��
//			     �ݻص�����������ϳ���Ƶ��֡�ʡ�
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
HANDLE VideoMixPro_Create(LPVOID lpObj, VideoMixedCallBack pMixCallBack, 
					      const VideoStreamInfo *pOutputStreamInfo);

//**********************************************************************
// Method:    	 VideoMixPro_Destroy
// Parameter: 	 [IN] hMixPro �����ٵĺϳɶ����handle.
// Returns:   	 
// Description:  ����һ���Ѿ������ĺϳɶ���
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_Destroy(HANDLE hMixPro);

//**********************************************************************
// Method:    	 VideoMixPro_EnableMix
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] bMix    �Ƿ���кϳ�
// Returns:   	 
// Description:  ָʾ�Ƿ������Ƶ�ϳɹ���.
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_EnableMix(HANDLE hMixPro, BOOL bMix);

//**********************************************************************
// Method:    	 VideoMixPro_SetParam
// Parameter: 	 [IN] hMixPro			�ϳɶ����handle
//               [IN] pOutputStreamInfo  ��������ĺϳ���Ƶ�Ĳ���
// Returns:   	 ���óɹ�����TRUE�����򷵻�FALSE
// Description:  ���������Ƶ�ĸ�ʽ,��������Ƶ�ϳ��ڼ��ڵ����Ըı�����ϳ�
//				 ��Ƶ�ĸ�ʽ��
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_SetParam(HANDLE hMixPro, const VideoStreamInfo *pOutputStreamInfo);

//**********************************************************************
// Method:    	 VideoMixPro_AddCodedInput
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] pInputVideoID ����Ψһ��ʶһ·���ϳɵ�������Ƶ���ɵ�
//				 �÷�ָ��
//				 [IN] nCodecID ������Ƶ�ı�����ID
//				 [IN] dstRect �����Ĵ�·��Ƶ�ںϳɺ���Ƶ�����е�λ��
// Returns:   	 �ɹ�����TRUE��ʧ�ܷ���FALSE.
// Description:  ���һ·�ѱ�����Ƶ����ϳɡ�
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_AddCodedInput(HANDLE hMixPro, const InputVideoID *pInputVideoID,
							   int nCodecID, RenderRect dstRect);

//**********************************************************************
// Method:    	 VideoMixPro_AddRawInput
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] pInputVideoID ����Ψһ��ʶһ·���ϳɵ�������Ƶ���ɵ�
//				 �÷�ָ��
//				 [IN] pBIH   ������Ƶ��Ϣ
//				 [IN] dstRect �����Ĵ�·��Ƶ�ںϳɺ���Ƶ�����е�λ��
// Returns:   	 �ɹ�����TRUE��ʧ�ܷ���FALSE.
// Description:  ���һ·ԭʼ��Ƶ���ݲ���ϳɡ�
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_AddRawInput(HANDLE hMixPro, const InputVideoID *pInputVideoID,
						     const BITMAPINFOHEADER *pbmih, RenderRect dstRect);

//**********************************************************************
// Method:    	 VideoMixPro_RemoveInput
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] pInputVideoID ��ʶ���Ƴ���һ·��Ƶ
// Returns:   	 
// Description:  �Ƴ�һ·��Ƶ�����ٶ�����кϳɡ�
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_RemoveInput(HANDLE hMixPro, const InputVideoID *pInputVideoID);

//**********************************************************************
// Method:    	 VideoMixPro_ResetVideoRect
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] pInputVideoID ��ʶһ·������Ƶ
//				 [IN] pRect	�������ú���pInputVideoIDָ����һ·��Ƶ�ںϳ�
//				 ��Ƶ�����е�λ����Ϣ
// Returns:   	 �ɹ�����TRUE,���򷵻�FALSE
// Description:  ��������һ·��Ƶ�ںϳɺ���Ƶ�е�λ��.
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
BOOL VideoMixPro_ResetVideoRect(HANDLE hMixPro, const InputVideoID *pInputVideoID, const RenderRect *pRect);

//**********************************************************************
// Method:    	 VideoMixPro_WriteData
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] pInputVideoID ��ʶ����������������һ·��Ƶ
//				 [IN] pbData �������Ƶ����
//				 [IN] dwLength ������Ƶ���ݵĳ���
//				 [IN] pFrameInfo д����Ƶ֡����Ϣ��ע������������Ƶ��ԭʼ
//               ��Ƶ���ݣ���pFrameInfo->bIsKeyFrame��������
// Returns:   	 
// Description:  ����һ·��Ƶ�����ݲ���ϳ�
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_WriteData(HANDLE hMixPro, InputVideoID *pInputVideoID, 
						   PBYTE pbData, DWORD dwLength, VideoFrameInfo *pFrameInfo);
//**********************************************************************
// Method:    	 VideoMixPro_SetSyncTime
// Parameter: 	 [IN] hMixPro ָ��һ���Ѵ����ϳɶ����handle
//				 [IN] pInputVideoID ��ʶһ·����ϳɵ���Ƶ
//				 [IN] pSyncTime ��һ·��Ƶ��������Ƶͬ��
// Returns:   	 
// Description:  
// Time:    	 15.12.08
// Author: 	     Gerald
//**********************************************************************
VOID VideoMixPro_SetSyncTime(HANDLE hMixPro, InputVideoID *pInputVideoID, IPlaySyncTime* pSyncTime);

#endif





