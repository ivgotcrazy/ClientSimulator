#ifndef __PROTOCOL_COMMON_DEFINE_H
#define __PROTOCOL_COMMON_DEFINE_H

//用户类型
#define     USER_TYPE_UNREGISTER			0
#define     USER_TYPE_REGISTER				1

//
//用户登录的用户名类型定义
//
#define		LOGINNAME_TYPE_ANONYMOUS	0X00	//匿名用户
#define		LOGINNAME_TYPE_USERNAME		0x01	//用户名
#define		LOGINNAME_TYPE_EMAIL		0X02	//E-MAIL
#define		LOGINNAME_TYPE_TELPHONE		0X03	//电话号码

//
//用户权限定义
//
#define		USERRIGHT_CHAIR				0X03	//主持人
#define		USERRIGHT_ATTENDER			0X02	//参与者
#define		USERRIGHT_LISTENER			0X01	//旁听者

#define     USERRIGHT_COUNT             0X04    //权限个数(包括0x00未初始化)

//
//会议模式定义
//
#define		ROOMMODE_FREE				0X00	//自由模式
#define		ROOMMODE_CONTROL			0x01	//主控模式

//
//会议室验证模式定义
//
#define		ROOMVERIFY_MODE_USERPASSWORD	0X01	//用户名密码验证
#define		ROOMVERIFY_MODE_ROOMPASSWORD	0X02	//会议室密码验证
#define		ROOMVERIFY_MODE_ANONYMOUS		0X03	//允许匿名登陆

//
//终端类型
//
#define		TERMINAL_DESKTOP				0X01	//桌面终端
#define		TERMINAL_HARD					0X02	//硬件终端
#define		TERMINAL_MOBILE					0X03	//移动终端
#define     TERMINAL_TEL                    0x04    //电话终端
#define     TERMINAL_RECORD                 0x05    //录制终端

typedef enum
{
	IMUSER_STATE_OFFLINE,
	IMUSER_STATE_FREE,
	IMUSER_STATE_BUSY,
	IMUSER_STATE_INVITE,
	IMUSER_STATE_CONF,
	IMUSER_STATE_LOGINCONF
}IMUSER_STATE;


#endif