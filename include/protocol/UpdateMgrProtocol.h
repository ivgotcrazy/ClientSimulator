#ifndef __UPDATEMGR_PROTOCOL_H
#define __UPDATEMGR_PROTOCOL_H

#include "ProtocolCommonDefine.h"

#ifdef _WIN32
#include <mmsystem.h>
#endif

#pragma pack(1)

#define UPDATE_PROTOCOL_TAG			mmioFOURCC('U','P','D','T')

#define	UPDATE_PROTOCOL_VERSION		"0"			//协议版本

#define UPDATE_CMDID_BASE			10000		//协议命令ID起始值

//客户端向服务器验证版本信息
#define	UPDATE_CMDID_VERSIONREQ		(UPDATE_CMDID_BASE)

//服务器向客户端返回版本信息
#define	UPDATE_CMDID_VERSIONREP		(UPDATE_CMDID_BASE+10)

//升级协议头
typedef struct
{
	DWORD 	dwHeadTag;			//值为UPDATE_PROTOCOL_TAG
	DWORD	dwLen;				//整个包长度
}UPDATE_CMD_HEADER;

#pragma pack()

#endif
