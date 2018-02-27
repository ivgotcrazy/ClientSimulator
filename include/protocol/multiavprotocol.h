#ifndef __MULTIAV_PROTOCOL_H
#define __MULTIAV_PROTOCOL_H

#pragma warning(disable:4200)

#define MULTIAV_CMDID_BASE				8700		//��·����ƵЭ������ID��ʼֵ

#pragma pack(1)

#define	MULTIAV_MEDIATYPE_AUDIO			0X01	//��Ƶ����
#define MULTIAV_MEDIATYPE_VIDEO			0X02	//��Ƶ����

////////////////////////////////////////////////////////////////////////////////
//  �ն���ý�����֮��������
////////////////////////////////////////////////////////////////////////////////

#define MULTIAV_CMDID_LOGINREQ			(MULTIAV_CMDID_BASE+1)	//�ͻ��˵�¼����
#define MULTIAV_CMDID_LOGINREP			(MULTIAV_CMDID_BASE+2)	//������Ӧ���¼����
#define MULTIAV_CMDID_RECVREQ			(MULTIAV_CMDID_BASE+3)	//�ͻ���������ջ�ֹͣ��������Ƶ
#define MULTIAV_CMDID_RECVREP			(MULTIAV_CMDID_BASE+4)	//������Ӧ���������Ƶ����
#define MULTIAV_CMDID_SENDENABLE		(MULTIAV_CMDID_BASE+5)	//������֪ͨ���Ͷ˷��ͻ�ֹͣ��������
#define MULTIAV_CMDID_SENDENABLEREP		(MULTIAV_CMDID_BASE+6)	//�ͻ���Ӧ����������ݷ���֪ͨ
#define MULTIAV_CMDID_PAUSERECVREQ		(MULTIAV_CMDID_BASE+7)	//�ͻ���������ͣ��ָ������û�����Ƶ
#define MULTIAV_CMDID_PAUSERECVREP		(MULTIAV_CMDID_BASE+8)	//������Ӧ��ͻ�����ͣ�����û�����Ƶ����
#define MULTIAV_CMDID_BYE				(MULTIAV_CMDID_BASE+9)	//�ر�����ͨ��

////////////////////////////////////////////////////////////////////////////////
//  ���ݴ���ͨ�������ֶ���(�ն���ý�����ý�������ý�����)
////////////////////////////////////////////////////////////////////////////////

#define MULTIAV_CMDID_SENDLOGINREQ		0x01		//�ͻ��˵�¼��������ͨ��
#define MULTIAV_CMDID_RECVLOGINREQ		0x02		//�ͻ��˵�¼��������ͨ��
typedef struct {
	
	BYTE		bCmd;
	BYTE		bReserved;
	DWORD		dwChannelID;
	DWORD		dwChannelCheckCode;
}MULTIAV_CMD_SENDLOGINREQ,
 MULTIAV_CMD_RECVLOGINREQ;

#define MULTIAV_CMDID_SENDLOGINREP		0x11		//������Ӧ��ͻ��˵�¼��������ͨ��
#define MULTIAV_CMDID_RECVLOGINREP		0x12		//������Ӧ��ͻ��˵�¼��������ͨ��
typedef struct{

	BYTE		bCmd;	
	BYTE		bResult;
	DWORD		dwChannelID;
}MULTIAV_CMD_SENDLOGINREP,
 MULTIAV_CMD_RECVLOGINREP;

#define MULTIAV_CMDID_SENDBYE			0x03		//�رշ�������ͨ��
#define MULTIAV_CMDID_RECVBYE			0x04		//�رս�������ͨ��
typedef struct{

	BYTE		bCmd;
	BYTE		bReserved;
}MULTIAV_CMD_SENDBYE,
 MULTIAV_CMD_RECVBYE;

#define	MULTIAV_CMDID_AVDATA			0x05	//��������Ƶ����
typedef struct{
	
	BYTE		bCmd;	
	BYTE		pbData[0];
}MULTIAV_CMD_AVDATA;

#define	MULTIAV_CMDID_QOSDATA			0x06	//����QOS����
typedef struct{
	
	BYTE		bCmd;
	BYTE		pbData[0];
}MULTIAV_CMD_QOSDATA;

#pragma pack()

#endif