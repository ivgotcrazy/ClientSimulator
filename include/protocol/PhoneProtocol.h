#ifndef __PHONE_PROTOCOL_H
#define __PHONE_PROTOCOL_H

#pragma pack(1)

#define PHONE_CMDID_BASE				7000		//电话网关协议命令ID起始值

#define	PHONE_PROTOCOL_VERSION			"1.0"		//协议版本

/************************************************************************
说明:
1 范围:7000-7399
2 7XXY:Y为奇数表示请求，为偶数表示应答。
3 分组:
1）会议服务与电话网关：7000-7099                             
************************************************************************/

/************************************************************************/
/*                       电话网关与会议服务                             */
/************************************************************************/
//7000-7099
#define PHONE_CMDID_CONF_BASE				(PHONE_CMDID_BASE)

//会议服务连接请求
#define PHONE_CMDID_CONF_CONNECT_REQ		(PHONE_CMDID_CONF_BASE+1)
//会议服务连接返回
#define PHONE_CMDID_CONF_CONNECT_REP		(PHONE_CMDID_CONF_BASE+2)

//呼叫请求
#define PHONE_CMDID_CONF_MAKECALL_REQ		(PHONE_CMDID_CONF_BASE+3)
//呼叫返回
#define PHONE_CMDID_CONF_MAKECALL_REP		(PHONE_CMDID_CONF_BASE+4)

//挂机请求
#define PHONE_CMDID_CONF_HANGUP_REQ			(PHONE_CMDID_CONF_BASE+5)
//挂机返回
#define PHONE_CMDID_CONF_HANGUP_REP			(PHONE_CMDID_CONF_BASE+6)

//呼叫状态通知
#define PHONE_CMDID_CONF_CALLSTATE_NOTIFY	(PHONE_CMDID_CONF_BASE+7)

#define PHONE_MAX_SERVERADDR 128

#define PHONE_MAX_CALLNUM    22

#define PHONE_MAX_NICKNAME   40

#define PHONE_MAX_PWDLEN     40

#define PHONE_MAX_CLIENTVER  20

#pragma pack()

#endif//__PHONE_PROTOCOL_H
;