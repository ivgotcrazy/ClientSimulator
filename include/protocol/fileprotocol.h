#ifndef __FILE_PROTOCOL_H
#define __FILE_PROTOCOL_H

#pragma warning(disable:4200)

#include "ProtocolError.h"

#define	FILE_PROTOCOL_VERSION		0X00		//�ļ�Э��汾

#define FILE_CMDID_BASE				0x1400		//�ļ�Э������ID��ʼֵ

#pragma pack(1)

//
//����ͨ������
//
#define FILE_CMDID_SENDLOGINREQ		(FILE_CMDID_BASE+0X00)		//�����ļ��ͻ��˵�¼
typedef struct{

	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	DWORD		dwUserID;
	DWORD		dwCheckCode;
	GUID		guidFile;
	DWORD		dwTotalFileSize;
	WORD		wSubFileCount;
	WORD		wMainFileNameLen;
	CHAR		szMainFileName[0];	//����UTF-8����
}FILE_CMD_SENDLOGINREQ;

#define	FILE_CMDID_SENDLOGINREP		(FILE_CMDID_BASE+0X10)		//��¼��Ӧ
typedef struct{
	
	WORD		wCmdID;
	WORD		wResult;
	WORD		wUrlLen;
	CHAR		szUrl[0];			//����UTF-8����
}FILE_CMD_SENDLOGINREP;

#define FILE_CMDID_RECVLOGINREQ		(FILE_CMDID_BASE+0X01)		//�����ļ��ͻ��˵�¼
typedef struct{
	
	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	DWORD		dwUserID;
	DWORD		dwCheckCode;
	GUID		guidFile;
}FILE_CMD_RECVLOGINREQ;

#define	FILE_CMDID_RECVLOGINREP		(FILE_CMDID_BASE+0X11)		//��¼��Ӧ
typedef struct{
	
	WORD		wCmdID;
	WORD		wResult;
	DWORD		dwTotalFileSize;
	WORD		wFileCount;
	WORD		wUrlLen;
	CHAR		szUrl[0];			//����UTF-8����
}FILE_CMD_RECVLOGINREP;

#define FILE_CMDID_BYE				(FILE_CMDID_BASE+0X02)		//�����Ự
typedef struct{
	
	WORD		wCmdID;
	WORD		wReserved;
}FILE_CMD_BYE;

#define	FILE_CMDID_SENDREQ			(FILE_CMDID_BASE+0X04)		//�������ļ�
typedef struct{

	WORD		wCmdID;
	WORD		wFileIndex;
	DWORD		dwFileLength;
	BYTE		bEncryptFlag;		//0:ԭʼ�ļ� 1:ZLIBѹ��
	BYTE		bMainFile;			//�Ƿ�Ϊ���ļ������ļ�ֻ�������һ��
	WORD		wNameLen;
	CHAR		szFileName[0];		//����UTF-8����
}FILE_CMD_SENDREQ;

#define	FILE_CMDID_SENDREP			(FILE_CMDID_BASE+0X14)		//�ļ���������ظ�
typedef struct{

	WORD		wCmdID;
	WORD		wResult;
	WORD		wFileIndex;
	DWORD		dwChannelID;		//�ļ��ϴ�ͨ����
	DWORD		dwCheckCode;
}FILE_CMD_SENDREP;

#define	FILE_CMDID_RECVREQ			(FILE_CMDID_BASE+0x05)		//�ļ���������
typedef struct{

	WORD		wCmdID;
	WORD		wFileIndex;
}FILE_CMD_RECVREQ;

#define FILE_CMDID_RECVREP			(FILE_CMDID_BASE+0X15)		//�����ļ��ظ�
typedef struct{

	WORD		wCmdID;
	WORD		wResult;
	WORD		wFileIndex;
	DWORD		dwChannelID;		//�ļ�����ͨ����
	DWORD		dwCheckCode;		//ͨ����֤��
	DWORD		dwFileLength;
	BYTE		bEncryptFlag;		//0:ԭʼ�ļ� 1:ZLIBѹ��
	BYTE		bMainFile;			//�Ƿ�Ϊ���ļ������ļ�ֻ�������һ��
	WORD		wNameLen;
	CHAR		szFileName[0];		//����UTF-8����
}FILE_CMD_RECVREP;

//
//����ͨ������
//
#define FILE_CMDID_SENDSTART		(FILE_CMDID_BASE+0X20)		//�ͻ��˿�ʼ�����ļ�
typedef	struct{

	WORD		wCmdID;
	BYTE		bKeepAlive;			//ͨ��ʹ����ɺ�, �Ƿ񱣳ֻỰ
	BYTE		bReserved;
	DWORD		dwChannelID;
	DWORD		dwCheckCode;		//ͨ����֤��
}FILE_CMD_SENDSTART;

#define FILE_CMDID_RECVSTART		(FILE_CMDID_BASE+0X21)		//�ͻ��˿�ʼ�����ļ�
typedef	struct{
	
	WORD		wCmdID;
	BYTE		bKeepAlive;			//ͨ��ʹ����ɺ�, �Ƿ񱣳ֻỰ
	BYTE		bReserved;
	DWORD		dwChannelID;
	DWORD		dwCheckCode;		//ͨ����֤��
}FILE_CMD_RECVSTART;

#define FILE_CMDID_SEEK				(FILE_CMDID_BASE+0x22)		//���շ�֪ͨ���ͷ����¶�λ���͵���ʼλ��
typedef struct{

	WORD		wCmdID;
	DWORD		dwChannelID;
	DWORD		dwPos;
}FILE_CMD_SEEK;

#define FILE_CMDID_SENDOK			(FILE_CMDID_BASE+0X23)		//���ͷ�֪ͨ�ѷ������
typedef struct{

	WORD		wCmdID;
	DWORD		dwChannelID;
}FILE_CMD_SENDOK;

#define FILE_CMDID_RECVOK			(FILE_CMDID_BASE+0X24)		//���շ�֪ͨ�ѽ������
typedef struct{
	
	WORD		wCmdID;
	DWORD		dwChannelID;
}FILE_CMD_RECVOK;

#define FILE_CMDID_DATA				(FILE_CMDID_BASE+0X25)		//�ļ�����
typedef struct{

	WORD		wCmdID;
	DWORD		dwChannelID;
	DWORD		dwPos;
	DWORD		dwLength;
	BYTE		pbData[0];
}FILE_CMD_DATA;

#pragma pack()

#endif