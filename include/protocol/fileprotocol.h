#ifndef __FILE_PROTOCOL_H
#define __FILE_PROTOCOL_H

#pragma warning(disable:4200)

#include "ProtocolError.h"

#define	FILE_PROTOCOL_VERSION		0X00		//文件协议版本

#define FILE_CMDID_BASE				0x1400		//文件协议命令ID起始值

#pragma pack(1)

//
//控制通道命令
//
#define FILE_CMDID_SENDLOGINREQ		(FILE_CMDID_BASE+0X00)		//发送文件客户端登录
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
	CHAR		szMainFileName[0];	//采用UTF-8编码
}FILE_CMD_SENDLOGINREQ;

#define	FILE_CMDID_SENDLOGINREP		(FILE_CMDID_BASE+0X10)		//登录响应
typedef struct{
	
	WORD		wCmdID;
	WORD		wResult;
	WORD		wUrlLen;
	CHAR		szUrl[0];			//采用UTF-8编码
}FILE_CMD_SENDLOGINREP;

#define FILE_CMDID_RECVLOGINREQ		(FILE_CMDID_BASE+0X01)		//接收文件客户端登录
typedef struct{
	
	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	DWORD		dwUserID;
	DWORD		dwCheckCode;
	GUID		guidFile;
}FILE_CMD_RECVLOGINREQ;

#define	FILE_CMDID_RECVLOGINREP		(FILE_CMDID_BASE+0X11)		//登录响应
typedef struct{
	
	WORD		wCmdID;
	WORD		wResult;
	DWORD		dwTotalFileSize;
	WORD		wFileCount;
	WORD		wUrlLen;
	CHAR		szUrl[0];			//采用UTF-8编码
}FILE_CMD_RECVLOGINREP;

#define FILE_CMDID_BYE				(FILE_CMDID_BASE+0X02)		//结束会话
typedef struct{
	
	WORD		wCmdID;
	WORD		wReserved;
}FILE_CMD_BYE;

#define	FILE_CMDID_SENDREQ			(FILE_CMDID_BASE+0X04)		//请求发送文件
typedef struct{

	WORD		wCmdID;
	WORD		wFileIndex;
	DWORD		dwFileLength;
	BYTE		bEncryptFlag;		//0:原始文件 1:ZLIB压缩
	BYTE		bMainFile;			//是否为主文件，主文件只允许存在一个
	WORD		wNameLen;
	CHAR		szFileName[0];		//采用UTF-8编码
}FILE_CMD_SENDREQ;

#define	FILE_CMDID_SENDREP			(FILE_CMDID_BASE+0X14)		//文件发送请求回复
typedef struct{

	WORD		wCmdID;
	WORD		wResult;
	WORD		wFileIndex;
	DWORD		dwChannelID;		//文件上传通道号
	DWORD		dwCheckCode;
}FILE_CMD_SENDREP;

#define	FILE_CMDID_RECVREQ			(FILE_CMDID_BASE+0x05)		//文件接收请求
typedef struct{

	WORD		wCmdID;
	WORD		wFileIndex;
}FILE_CMD_RECVREQ;

#define FILE_CMDID_RECVREP			(FILE_CMDID_BASE+0X15)		//接收文件回复
typedef struct{

	WORD		wCmdID;
	WORD		wResult;
	WORD		wFileIndex;
	DWORD		dwChannelID;		//文件接收通道号
	DWORD		dwCheckCode;		//通道验证码
	DWORD		dwFileLength;
	BYTE		bEncryptFlag;		//0:原始文件 1:ZLIB压缩
	BYTE		bMainFile;			//是否为主文件，主文件只允许存在一个
	WORD		wNameLen;
	CHAR		szFileName[0];		//采用UTF-8编码
}FILE_CMD_RECVREP;

//
//数据通道命令
//
#define FILE_CMDID_SENDSTART		(FILE_CMDID_BASE+0X20)		//客户端开始发送文件
typedef	struct{

	WORD		wCmdID;
	BYTE		bKeepAlive;			//通道使用完成后, 是否保持会话
	BYTE		bReserved;
	DWORD		dwChannelID;
	DWORD		dwCheckCode;		//通道验证码
}FILE_CMD_SENDSTART;

#define FILE_CMDID_RECVSTART		(FILE_CMDID_BASE+0X21)		//客户端开始接收文件
typedef	struct{
	
	WORD		wCmdID;
	BYTE		bKeepAlive;			//通道使用完成后, 是否保持会话
	BYTE		bReserved;
	DWORD		dwChannelID;
	DWORD		dwCheckCode;		//通道验证码
}FILE_CMD_RECVSTART;

#define FILE_CMDID_SEEK				(FILE_CMDID_BASE+0x22)		//接收方通知发送方重新定位发送的起始位置
typedef struct{

	WORD		wCmdID;
	DWORD		dwChannelID;
	DWORD		dwPos;
}FILE_CMD_SEEK;

#define FILE_CMDID_SENDOK			(FILE_CMDID_BASE+0X23)		//发送方通知已发送完毕
typedef struct{

	WORD		wCmdID;
	DWORD		dwChannelID;
}FILE_CMD_SENDOK;

#define FILE_CMDID_RECVOK			(FILE_CMDID_BASE+0X24)		//接收方通知已接收完毕
typedef struct{
	
	WORD		wCmdID;
	DWORD		dwChannelID;
}FILE_CMD_RECVOK;

#define FILE_CMDID_DATA				(FILE_CMDID_BASE+0X25)		//文件数据
typedef struct{

	WORD		wCmdID;
	DWORD		dwChannelID;
	DWORD		dwPos;
	DWORD		dwLength;
	BYTE		pbData[0];
}FILE_CMD_DATA;

#pragma pack()

#endif