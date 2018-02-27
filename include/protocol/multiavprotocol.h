#ifndef __MULTIAV_PROTOCOL_H
#define __MULTIAV_PROTOCOL_H

#pragma warning(disable:4200)

#define MULTIAV_CMDID_BASE				8700		//多路音视频协议命令ID起始值

#pragma pack(1)

#define	MULTIAV_MEDIATYPE_AUDIO			0X01	//音频数据
#define MULTIAV_MEDIATYPE_VIDEO			0X02	//视频数据

////////////////////////////////////////////////////////////////////////////////
//  终端与媒体服务之间的信令定义
////////////////////////////////////////////////////////////////////////////////

#define MULTIAV_CMDID_LOGINREQ			(MULTIAV_CMDID_BASE+1)	//客户端登录请求
#define MULTIAV_CMDID_LOGINREP			(MULTIAV_CMDID_BASE+2)	//服务器应答登录请求
#define MULTIAV_CMDID_RECVREQ			(MULTIAV_CMDID_BASE+3)	//客户端请求接收或停止接收音视频
#define MULTIAV_CMDID_RECVREP			(MULTIAV_CMDID_BASE+4)	//服务器应答接收音视频请求
#define MULTIAV_CMDID_SENDENABLE		(MULTIAV_CMDID_BASE+5)	//服务器通知发送端发送或停止发送数据
#define MULTIAV_CMDID_SENDENABLEREP		(MULTIAV_CMDID_BASE+6)	//客户端应答服务器数据发送通知
#define MULTIAV_CMDID_PAUSERECVREQ		(MULTIAV_CMDID_BASE+7)	//客户端请求暂停或恢复接收用户音视频
#define MULTIAV_CMDID_PAUSERECVREP		(MULTIAV_CMDID_BASE+8)	//服务器应答客户端暂停接收用户音视频请求
#define MULTIAV_CMDID_BYE				(MULTIAV_CMDID_BASE+9)	//关闭信令通道

////////////////////////////////////////////////////////////////////////////////
//  数据传输通道命令字定义(终端与媒体服务、媒体服务与媒体服务)
////////////////////////////////////////////////////////////////////////////////

#define MULTIAV_CMDID_SENDLOGINREQ		0x01		//客户端登录发送数据通道
#define MULTIAV_CMDID_RECVLOGINREQ		0x02		//客户端登录接收数据通道
typedef struct {
	
	BYTE		bCmd;
	BYTE		bReserved;
	DWORD		dwChannelID;
	DWORD		dwChannelCheckCode;
}MULTIAV_CMD_SENDLOGINREQ,
 MULTIAV_CMD_RECVLOGINREQ;

#define MULTIAV_CMDID_SENDLOGINREP		0x11		//服务器应答客户端登录发送数据通道
#define MULTIAV_CMDID_RECVLOGINREP		0x12		//服务器应答客户端登录接收数据通道
typedef struct{

	BYTE		bCmd;	
	BYTE		bResult;
	DWORD		dwChannelID;
}MULTIAV_CMD_SENDLOGINREP,
 MULTIAV_CMD_RECVLOGINREP;

#define MULTIAV_CMDID_SENDBYE			0x03		//关闭发送数据通道
#define MULTIAV_CMDID_RECVBYE			0x04		//关闭接收数据通道
typedef struct{

	BYTE		bCmd;
	BYTE		bReserved;
}MULTIAV_CMD_SENDBYE,
 MULTIAV_CMD_RECVBYE;

#define	MULTIAV_CMDID_AVDATA			0x05	//传输音视频数据
typedef struct{
	
	BYTE		bCmd;	
	BYTE		pbData[0];
}MULTIAV_CMD_AVDATA;

#define	MULTIAV_CMDID_QOSDATA			0x06	//传输QOS数据
typedef struct{
	
	BYTE		bCmd;
	BYTE		pbData[0];
}MULTIAV_CMD_QOSDATA;

#pragma pack()

#endif