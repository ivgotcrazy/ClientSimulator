#ifndef __CONF_PROTOCOL_H
#define __CONF_PROTOCOL_H

#include "ProtocolCommonDefine.h"

#pragma pack(1)

#define	CONF_PROTOCOL_VERSION		"1.0"			//协议版本

#define CONF_CMDID_BASE				6500		//协议命令ID起始值

#define STATE_NONE					0X00
#define STATE_WAITING				0X01
#define STATE_DONE					0X02


#define USERTYPE_UNREGISTER			0X00		//非注册用户
#define	USERTYPE_REGISTER			0X01		//注册用户

//是否返回离线用户列表
#define	GET_ONLINE_USERLIST			0x0			//返回在线用户
#define	GET_ALL_USERLIST			0x1			//返回全部用户

//设备操作类型
#define	DEV_OPERATION_ADD			0x1			//增加设备
#define	DEV_OPERATION_MODIFY		0x2			//修改设备
#define	DEV_OPERATION_DEL			0x3			//删除设备

//系统消息定义
#define SYSMSG_TYPE_CHAT			0x01		//文字消息
#define SYSMSG_TYPE_WND				0x02		//窗口消息
#define SYSMSG_TYPE_WEB				0x03		//WEB消息
#define SYSMSG_TYPE_NAVIGATE		0x04		//浏览器消息
#define SYSMSG_TYPE_LOGINLOGO		0x05		//登录LOGO

////////////////////////////////////////////////////////////////////////////////
//  终端与会议服务之间的信令
////////////////////////////////////////////////////////////////////////////////

//客户端向服务器验证版本信息
#define	CONF_CMDID_VERSIONREQ		(CONF_CMDID_BASE)

//服务器向客户端返回版本信息
#define	CONF_CMDID_VERSIONREP		(CONF_CMDID_BASE+100)

//客户端登录请求
#define CONF_CMDID_LOGINREQ			(CONF_CMDID_BASE+1)

//服务器返回登录结果
#define CONF_CMDID_LOGINREP			(CONF_CMDID_BASE+101)

//服务器通知新增用户信息
#define CONF_CMDID_USERENTER		(CONF_CMDID_BASE+102)

//请求离线用户列表
#define CONF_CMDID_REQOFFLINES		(CONF_CMDID_BASE+3)

//服务器返回离线用户列表
#define CONF_CMDID_OUTLINE			(CONF_CMDID_BASE+103)

//主持人答复敲门请求
#define CONF_CMDID_ALLOWKNOCK		(CONF_CMDID_BASE+4)

//服务器通知主持人有人敲门
#define CONF_CMDID_KNOCKNOTIFY		(CONF_CMDID_BASE+104)


//客户端退出请求
#define CONF_CMDID_LOGOUTREQ		(CONF_CMDID_BASE+5)

//服务器通知用户退出
#define CONF_CMDID_USERLEAVE		(CONF_CMDID_BASE+105)

//用户踢出其他用户
#define CONF_CMDID_KICKUSER			(CONF_CMDID_BASE+6)

//服务器通知被踢出用户已被踢出
#define CONF_CMDID_USERKICKED		(CONF_CMDID_BASE+106)

//主持人关闭房间
#define CONF_CMDID_CLOSEROOM		(CONF_CMDID_BASE+7)

//服务器关闭房间
#define CONF_CMDID_ROOMCLOSED		(CONF_CMDID_BASE+107)

//用户更新本地的音视频设备信息
#define CONF_CMDID_AVINFO			(CONF_CMDID_BASE+8)

//服务器通知用户音视频设备信息变更
#define CONF_CMDID_AVINFONOTIFY		(CONF_CMDID_BASE+108)

//改变用户状态
#define CONF_CMDID_CHANGEUSERSTATE	(CONF_CMDID_BASE+9)

//服务器通知用户状态已改变
#define CONF_CMDID_USERSTATECHANGED	(CONF_CMDID_BASE+109)

//用户改变会议状态
#define CONF_CMDID_CHANGECONFSTATE	(CONF_CMDID_BASE+10)

//服务器通知会议状态已改变
#define CONF_CMDID_CONFSTATECHANGED	(CONF_CMDID_BASE+110)

//用户申请成为主持人
#define CONF_CMDID_REQCHAIRRIGHT	(CONF_CMDID_BASE+11)

//服务器返回申请主持人结果
#define CONF_CMDID_REQCHAIRRIGHTRET	(CONF_CMDID_BASE+111)

//用户发送文字消息
#define CONF_CMDID_CHATMSG			(CONF_CMDID_BASE+12)

//服务器转发文字消息
#define CONF_CMDID_CHATMSGNOTIFY	(CONF_CMDID_BASE+112)

//用户发送窗口状态
#define CONF_CMDID_WNDSTATE			(CONF_CMDID_BASE+13)

//服务器转发窗口状态
#define CONF_CMDID_WNDSTATENOTIFY	(CONF_CMDID_BASE+113)

//主持人发送快速静场命令
#define CONF_CMDID_SILENT			(CONF_CMDID_BASE+14)

//服务器转发快速静场命令
#define CONF_CMDID_SILENTNOTIFY		(CONF_CMDID_BASE+114)

//主持人发送字幕命令
#define CONF_CMDID_MEETINGCHAR		(CONF_CMDID_BASE+15)

//服务器转发字幕消息
#define CONF_CMDID_MEETINGCHARNOTIFY (CONF_CMDID_BASE+115)

//用户发送文件给其他用户
#define CONF_CMDID_SENDFILE			(CONF_CMDID_BASE+16)

//服务器通知其他用户接收文件
#define CONF_CMDID_SENDFILENOTIFY	(CONF_CMDID_BASE+116)

//客户端初始化完成
#define CONF_CMDID_INITCOMPLETE		(CONF_CMDID_BASE+17)

//服务器通知敲门端正在等待主持人开门
#define CONF_CMDID_WAITOPENDOOR		(CONF_CMDID_BASE+117)

//服务器发送通知消息,用于发布或广播消息
#define CONF_CMDID_SYSMSG			(CONF_CMDID_BASE+118)

//主持人设置会场数据
#define CONF_CMDID_ROOMDATA			(CONF_CMDID_BASE+19)

//服务器通知更新会场数据，新用户登录也收到该通知
#define CONF_CMDID_ROOMDATANOTIFY	(CONF_CMDID_BASE+119)

//主持人申请获取AV合成参数
#define CONF_CMDID_MIXCONFIG		(CONF_CMDID_BASE+20)

//服务器返回当前AV合成参数
#define CONF_CMDID_MIXCONFIGINFO	(CONF_CMDID_BASE+120)

//主持人设置AV合成参数
#define CONF_CMDID_SETMIXCONFIG		(CONF_CMDID_BASE+21)

//主持人设置视频字幕参数
#define CONF_CMDID_SETOSDPARAM		(CONF_CMDID_BASE+22)

//服务器转发主持人设置视频字幕参数
#define CONF_CMDID_OSDPARAMNOTIFY	(CONF_CMDID_BASE+122)

//主持人创建分组会议,可以同时创建多个
#define CONF_CMDID_CREATEGROUP		(CONF_CMDID_BASE+23)

//服务器返回新建分组会议信息
#define CONF_CMDID_GROUPINFO		(CONF_CMDID_BASE+123)

//将用户加入分组会议
#define CONF_CMDID_ENTERGROUPREQ	(CONF_CMDID_BASE+24)

//通知用户进入分组会议
#define CONF_CMDID_ENTERGROUPREP	(CONF_CMDID_BASE+124)

//主持人结束分组会议
#define CONF_CMDID_CLOSEGROUP		(CONF_CMDID_BASE+25)

//服务器返回结束分组会议消息
#define CONF_CMDID_CLOSEGROUPNOTIFY	(CONF_CMDID_BASE+125)

//将用户加入主会议
#define CONF_CMDID_ENTERMAINREQ		(CONF_CMDID_BASE+26)

//通知用户进入主会议
#define CONF_CMDID_ENTERMAINREP		(CONF_CMDID_BASE+126)

//客户修改会议室名称
#define CONF_CMDID_MEETINGRENAMEREQ		(CONF_CMDID_BASE+27)
//通知用户改会议室名称
#define CONF_CMDID_MEETINGRENAMEREP		(CONF_CMDID_BASE+127)

//中转消息
#define CONF_CMDID_TRANSDATA		(CONF_CMDID_BASE+200)

/************************************************************************/
/*                          终端与会议服务                              */
/************************************************************************/
//6740-6799
#define CONF_CMDID_TERMINAL_BASE				(CONF_CMDID_BASE+240)

//呼叫请求
#define CONF_CMDID_TERMINAL_MAKECALL_REQ		(CONF_CMDID_TERMINAL_BASE+1)
//呼叫返回
#define CONF_CMDID_TERMINAL_MAKECALL_REP		(CONF_CMDID_TERMINAL_BASE+2)

//挂机请求
#define CONF_CMDID_TERMINAL_HANGUP_REQ			(CONF_CMDID_TERMINAL_BASE+3)
//挂机返回
#define CONF_CMDID_TERMINAL_HANGUP_REP			(CONF_CMDID_TERMINAL_BASE+4)

//呼叫状态通知
#define CONF_CMDID_TERMINAL_CALLSTATE_NOTIFY	(CONF_CMDID_TERMINAL_BASE+5)

//获取用户拨号列表
#define CONF_CMDID_TERMINAL_CALL_LIST_REQ		(CONF_CMDID_TERMINAL_BASE+6)

//返回用户拨号列表
#define CONF_CMDID_TERMINAL_CALL_LIST_REP		(CONF_CMDID_TERMINAL_BASE+7)

#pragma pack()

#endif