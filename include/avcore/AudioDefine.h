#ifndef AUDIO_DEFINE_H
#define AUDIO_DEFINE_H

//***********����/��ȡ��Ƶ�豸�ĵĲ���***************

#define		AUDIO_PARAM_AEC				0X1001	//��������(0-1)	0-���� 1-����
#define		AUDIO_PARAM_ANS				0X1002	//����(0-3) 0-���� 1-�� 2-�� 3-ǿ
#define		AUDIO_PARAM_VAD				0X1003	//�������(0-1) 0-���� 1-����
#define		AUDIO_PARAM_AGC				0X1004	//�Զ�����(0-3)0-���� 1-�� 2-�� 3-ǿ
#define		AUDIO_PARAM_ENCODER			0X1006	//�ɼ���ʹ�õı����ʽ
#define		AUDIO_PARAM_CAPAUTOVOLUME	0x1007	//�ɼ��豸�����Զ�����(0-1) 0-���� 1-����
#define		AUDIO_PARAM_CALENERGY		0x1008	//������Ƶ����(0-1) 0-���� 1-����

#define     AUDIO_PARAM_SOUNDTOUCH      0x1009  //��������

#define		AUDIO_PARAM_CAPVOL			0x1010	//��ȡ/����ϵͳ�ɼ��豸�����Ĵ�С(0 - 100)
#define		AUDIO_PARAM_PLAYVOL			0x1011	//��ȡ/����ϵͳ�����豸�����Ĵ�С(0 - 100)
#define		AUDIO_PARAM_CAPSOFTMUTE		0x1012	//��ȡ/���ñ�����ɼ��豸�ľ���״̬(0-1)0-���� 1-����
#define		AUDIO_PARAM_PLAYSOFTMUTE	0x1013	//��ȡ/���ñ���������豸�ľ���״̬(0-1)0-���� 1-����
#define		AUDIO_PARAM_PLAYDEVMUTE		0x1014	//��ȡ/���ò���ϵͳ�����豸�ľ���״̬(0-1)0-���� 1-����
//MIXERLINE_COMPONENTTYPE_SRC_ANALOG:		Mix
//MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE		Modem
//MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:		Video
//MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY:	Aux
//MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE:	Micro
//MIXERLINE_COMPONENTTYPE_SRC_LINE:			LineIn
//MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC:	CompactDisc
#define		AUDIO_PARAM_CAPINPUT		0x1015	//��ȡ/���òɼ�����������

//��Ƶ�����ͷ
typedef struct{
	
	PBYTE pbSrc;		//Դ����ָ��
	UINT  unSrcLen;		//Դ���ݳ���
	UINT  unSrcUsed;	//��ʹ�õ�Դ���ݳ���
	
	PBYTE pbDes;		//Ŀ�껺��ָ��
	UINT  unDesLen;		//Ŀ�껺���С
	UINT  unDesUsed;	//Ŀ�����ݳ���
	
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