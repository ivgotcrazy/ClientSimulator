#ifndef __XML_DOC_PROTOCOL_H
#define __XML_DOC_PROTOCOL_H

#pragma warning(disable:4200)

#define	XMLDOC_PROTOCOL_VERSION		0X00		//协议版本

#define XMLDOC_CMDID_BASE			0x1500		//协议命令ID起始值

#pragma pack(1)

#define XMLDOC_CMDID_LOGINREQ		(XMLDOC_CMDID_BASE+0X00)		//登录请求
typedef struct{
	
	WORD		wCommand;
	BYTE		bVersion;
	BYTE		bReserved;
	DWORD		dwUserID;
	DWORD		dwCheckCode;
	GUID		guidDoc;
}XMLDOC_CMD_LOGINREQ;

#define XMLDOC_CMDID_LOGINREP		(XMLDOC_CMDID_BASE+0x10)		//登录响应
typedef struct{

	WORD		wCommand;
	WORD		wResult;
	WORD		wReserved;
}XMLDOC_CMD_LOGINREP;

#define XMLDOC_CMDID_BYE			(XMLDOC_CMDID_BASE+0X01)		//结束会话
typedef struct{
	
	WORD		wCmdID;
	WORD		wReserved;
}XMLDOC_CMD_BYE;

#define XMLDOC_CMDID_SENDFILEREQ	(XMLDOC_CMDID_BASE+0X02)		//请求上传文件
typedef struct{

	WORD		wCmdID;
	WORD		wReserved;
	GUID		guidFile;
}XMLDOC_CMD_SENDFILEREQ;

#define XMLDOC_CMDID_SENDFILEREP	(XMLDOC_CMDID_BASE+0X12)		//上传文件回复
typedef struct{

	WORD		wCmdID;
	WORD		wResult;
	GUID		guidFile;
	DWORD		dwCheckCode;
	WORD		wSrvAppID;
	WORD		wSrvAddrLinkLen;
	CHAR		szFileSrvAddrLink[0];
}XMLDOC_CMD_SENDFILEREP;

#define XMLDOC_CMDID_GETDOCREQ		(XMLDOC_CMDID_BASE+0X03)		//请求下载文档
typedef struct{

	WORD		wCmdID;
	WORD		wReserved;
}XMLDOC_CMD_GETDOCREQ;

#define XMLDOC_CMDID_GETDOCREP		(XMLDOC_CMDID_BASE+0X13)		//文档回复
typedef struct{

	WORD		wCmdID;
	DWORD		dwDocSize;
	WORD		wSubSeqnum;
	WORD		wSubLength;
	CHAR		szDocData[0];
}XMLDOC_CMD_GETDOCREP;

#define XMLDOC_CMDID_CLEARDOC		(XMLDOC_CMDID_BASE+0X04)		//清空文档内容
typedef struct{
	
	WORD		wCmdID;
	WORD		wReserved;
}XMLDOC_CMD_CLEARDOC;

#define XMLDOC_INSERT_AFTER			0x00		//插入指定结点之前
#define XMLDOC_INSERT_BEFORE		0X01		//插入指定结点之后
#define XMLDOC_INSERT_END			0X02		//插入结尾
			
#define XMLDOC_CMDID_INSERTDOCNODE	(XMLDOC_CMDID_BASE+0X05)		//插入文档结点
typedef struct{

	WORD		wCmdID;
	BYTE		bInsertType;
	BYTE		bOnlyOne;			//该结点是否只允许存在一个
	WORD		wParentPathLen;
	CHAR		szParentPath[0];	//语法: Page Index=1/Obj ID=1000
//	WORD		wInsertPosPathLen;
//	CHAR		szInsertPosPath[0];
//	WORD		wNodeLen;
//	CHAR		szNodeData[0];
	
}XMLDOC_CMD_INSERTDOCNODE;

#define XMLDOC_CMDID_MODIFYDOCNODE	(XMLDOC_CMDID_BASE+0X06)		//修改文档结点
typedef struct{

	WORD		wCmdID;
	WORD		wNodePathLen;
	CHAR		szNodePath[0];		//语法: Page Index=1/Obj ID=1000
//	WORD		wNodeDataLen;
//	CHAR		szNodeData[0];
}XMLDOC_CMD_MODIFYDOCNODE;

#define XMLDOC_CMDID_DELDOCNODE		(XMLDOC_CMDID_BASE+0X07)		//删除文档结点
typedef struct{

	WORD		wCmdID;
	WORD		wNodePathLen;
	CHAR		szNodePath[0];		
}XMLDOC_CMD_DELDOCNODE;

#pragma pack()

#endif