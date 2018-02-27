#ifndef __RTXPLUGIN_PROTOCOL_H
#define __RTXPLUGIN_PROTOCOL_H

#define RTXPLUGIN_CMDID_BASE					0x00		//Э������ID��ʼֵ

#define RTXPLUGIN_APPGUID						_T("{05AFC099-6915-4a8f-ACEE-D1A12E4A8A1B}")
#define RTXPLUGIN_IDENTIFIER					_T("Tencent.RTX.FMRTXPlugin")

#define	RTXPLUGIN_DATAKEY						_T("cmd")

#pragma pack(1)

//���������������ʱ����
#define RTXPLUGIN_CMDID_CREATEROOMREQ			(RTXPLUGIN_CMDID_BASE+1)

//���������ؽ�����ʱ������
#define RTXPLUGIN_CMDID_CREATEROOMREP			(RTXPLUGIN_CMDID_BASE+11)

//�����������������ʱ����
#define RTXPLUGIN_CMDID_REMOVEROOMREQ			(RTXPLUGIN_CMDID_BASE+2)

//����������������ʱ������
#define RTXPLUGIN_CMDID_REMOVEROOMREP			(RTXPLUGIN_CMDID_BASE+12)

//���������û��������
#define RTXPLUGIN_CMDID_INVITEJOINROOM			(RTXPLUGIN_CMDID_BASE+3)

//Ӧ�������û�����
#define RTXPLUGIN_CMDID_REPJOINROOM				(RTXPLUGIN_CMDID_BASE+4)

#define	REPJOINROOM_RESULT_ACCEPT				0x00			//����
#define REPJOINROOM_RESULT_REJECT				0x01			//�ܾ�
#define REPJOINROOM_RESULT_BUSY					0x03			//��æ

#pragma pack()

#endif