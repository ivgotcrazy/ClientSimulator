#ifndef __UPDATEMGR_PROTOCOL_H
#define __UPDATEMGR_PROTOCOL_H

#include "ProtocolCommonDefine.h"

#ifdef _WIN32
#include <mmsystem.h>
#endif

#pragma pack(1)

#define UPDATE_PROTOCOL_TAG			mmioFOURCC('U','P','D','T')

#define	UPDATE_PROTOCOL_VERSION		"0"			//Э��汾

#define UPDATE_CMDID_BASE			10000		//Э������ID��ʼֵ

//�ͻ������������֤�汾��Ϣ
#define	UPDATE_CMDID_VERSIONREQ		(UPDATE_CMDID_BASE)

//��������ͻ��˷��ذ汾��Ϣ
#define	UPDATE_CMDID_VERSIONREP		(UPDATE_CMDID_BASE+10)

//����Э��ͷ
typedef struct
{
	DWORD 	dwHeadTag;			//ֵΪUPDATE_PROTOCOL_TAG
	DWORD	dwLen;				//����������
}UPDATE_CMD_HEADER;

#pragma pack()

#endif
