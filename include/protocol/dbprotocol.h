#ifndef __DB_PROTOCOL_H
#define __DB_PROTOCOL_H

#pragma pack(1)

#define	DB_PROTOCOL_VERSION			0X00		//���ݿ����Э��汾

#define DB_CMDID_BASE				6900		//���ݿ����Э������ID��ʼֵ

//
//�����ֶ���
//���������ֽ���
//

#define	DB_CMDID_CONNECTREQ			(DB_CMDID_BASE)		//�����������ݿ�����
typedef struct{

	WORD	wCmdID;
	WORD	wReserved;
	//User 
	//Password
	//DBName
}DB_CMD_CONNECTREQ;

#define DB_CMDID_CONNECTREP			(DB_CMDID_BASE+10)	//�������ݿ�����Ӧ��
typedef struct{

	WORD	wCmdID;
	WORD	wResult;
}DB_CMD_CONNECTREP;

#define DB_CMDID_DISCONNECTREQ		(DB_CMDID_BASE+1)	//����Ͽ�����
typedef struct{

	WORD	wCmdID;
}DB_CMD_DISCONNECTREQ;

#define DB_CMDID_DISCONNECTREP		(DB_CMDID_BASE+11)	//�Ͽ�����Ӧ��
typedef struct{

	WORD	wCmdID;
}DB_CMD_DISCONNECTREP;

#define DB_CMDID_QUERYREQ			(DB_CMDID_BASE+2)	//���ݿ��ѯ����
typedef struct{

	WORD	wCmdID;
	BYTE	bGetResult;				//�Ƿ���Ҫ��ȡ��ѯ���
	BYTE	bMultiResult;			//�Ƿ񷵻ض�����
	WORD	wSeqNum;				//�������к�
	WORD	wReserved;
	//Query String
}DB_CMD_QUERYREQ;

#define DB_CMDID_QUERYREP			(DB_CMDID_BASE+12)	//���ݿ��ѯ����
typedef struct{

	WORD	wCmdID;
	WORD	wResult;
	WORD	wSeqnum;
	BYTE	bHasMoreData;			//�Ƿ�������Ҫ����
	BYTE	bReserved;
	//Data
}DB_CMD_QUERYREP;

typedef struct{
	WORD	wBlockLen;				//���ݿ鳤��
	WORD	wRecordCount;			//��¼����
	BYTE	bResultSeqnum;			//��ǰ��������,��0��ʼ
	BYTE	bFieldCount;			//��ǰ������ֶ���
	//Record Data
	//ÿһ���ֶ�������\0��β
}ResultHeader;						//���������ͷ

#pragma pack()

#endif
