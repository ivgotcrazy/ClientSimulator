#ifndef __VNC_PROTOCOL_H
#define __VNC_PROTOCOL_H

#pragma warning(disable:4200)

#pragma pack(1)

#define	VNC_PROTOCOL_VERSION		0X00		//应用程序共享协议版本

#define VNC_CMDID_BASE				0x1300		//应用程序共享协议命令ID起始值

//
//命令字定义
//
#define	VNC_CMDID_HOSTREQ			(VNC_CMDID_BASE+0x00)	//客户端请求应用程序共享
typedef struct{

	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	GUID		guidGroup;
	DWORD		dwUserID;
	DWORD		dwCheckCode;
}VNC_CMD_HOSTREQ;

#define VNC_CMDID_HOSTREP			(VNC_CMDID_BASE+0X10)	//服务器应答应用程序共享请求
typedef struct{

	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	WORD		wResult;
	GUID		guidGroup;
	DWORD		dwUserID;
}VNC_CMD_HOSTREP;

#define VNC_CMDID_HOSTBYE			(VNC_CMDID_BASE+0X01)	//通知结束会话
typedef struct{
	
	WORD		wCmdID;
	WORD		wReserved;
	GUID		guidGroup;
	DWORD		dwUserID;
	
}VNC_CMD_HOSTBYE;

#define	VNC_CMDID_VIEWREQ			(VNC_CMDID_BASE+0x02)	//客户端请求接收应用程序共享
typedef struct{

	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	GUID		guidGroup;
	DWORD		dwUserID;
	DWORD		dwSrcUserID;
	DWORD		dwCheckCode;
}VNC_CMD_VIEWREQ;

#define VNC_CMDID_VIEWREP			(VNC_CMDID_BASE+0X12)	//服务器响应接收应用程序共享
typedef struct{

	WORD		wCmdID;
	BYTE		bVersion;
	BYTE		bReserved;
	WORD		wResult;
	GUID		guidGroup;
	DWORD		dwUserID;
	DWORD		dwSrcUserID;
}VNC_CMD_VIEWREP;

#define VNC_CMDID_VIEWBYE			(VNC_CMDID_BASE+0X03)	//通知结束会话
typedef struct{
	
	WORD		wCmdID;
	WORD		wReserved;
	GUID		guidGroup;
	DWORD		dwUserID;
	DWORD		dwSrcUserID;
	
}VNC_CMD_VIEWBYE;

#define	VNC_CMDID_DATA			(VNC_CMDID_BASE+0X04)	//应用程序共享数据
typedef struct{

	WORD		wCmdID;
	WORD		wSeqnum;
	BYTE		bSubCount;
	BYTE		bSubSeqnum;
	BYTE		pbData[0];
}VNC_CMD_DATA;

#pragma pack()

#endif
