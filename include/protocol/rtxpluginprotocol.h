#ifndef __RTXPLUGIN_PROTOCOL_H
#define __RTXPLUGIN_PROTOCOL_H

#define RTXPLUGIN_CMDID_BASE					0x00		//协议命令ID起始值

#define RTXPLUGIN_APPGUID						_T("{05AFC099-6915-4a8f-ACEE-D1A12E4A8A1B}")
#define RTXPLUGIN_IDENTIFIER					_T("Tencent.RTX.FMRTXPlugin")

#define	RTXPLUGIN_DATAKEY						_T("cmd")

#pragma pack(1)

//向服务器请求建立临时房间
#define RTXPLUGIN_CMDID_CREATEROOMREQ			(RTXPLUGIN_CMDID_BASE+1)

//服务器返回建立临时房间结果
#define RTXPLUGIN_CMDID_CREATEROOMREP			(RTXPLUGIN_CMDID_BASE+11)

//向服务器请求销毁临时房间
#define RTXPLUGIN_CMDID_REMOVEROOMREQ			(RTXPLUGIN_CMDID_BASE+2)

//服务器返回销毁临时房间结果
#define RTXPLUGIN_CMDID_REMOVEROOMREP			(RTXPLUGIN_CMDID_BASE+12)

//邀请其它用户参与会议
#define RTXPLUGIN_CMDID_INVITEJOINROOM			(RTXPLUGIN_CMDID_BASE+3)

//应答其它用户邀请
#define RTXPLUGIN_CMDID_REPJOINROOM				(RTXPLUGIN_CMDID_BASE+4)

#define	REPJOINROOM_RESULT_ACCEPT				0x00			//接受
#define REPJOINROOM_RESULT_REJECT				0x01			//拒绝
#define REPJOINROOM_RESULT_BUSY					0x03			//正忙

#pragma pack()

#endif