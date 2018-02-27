#ifndef __FRONT_PROTOCOL_H
#define __FRONT_PROTOCOL_H

#pragma pack(1)

#define FRONT_CMDID_BASE				30000		//前置协议命令ID起始值

#define	FRONT_PROTOCOL_VERSION			"1.2"			//协议版本

/************************************************************************/
/*                              终端与业务前置                          */
/************************************************************************/

//用户登陆请求
#define FRONT_CMDID_TERMINAL_USERLOGIN_REQ		 (FRONT_CMDID_BASE)

//用户登陆回复
#define FRONT_CMDID_TERMINAL_USERLOGIN_REP		 (FRONT_CMDID_BASE + 1)

//获取会议室列表请求
#define FRONT_CMDID_TERMINAL_ROOMLIST_REQ		 (FRONT_CMDID_BASE + 2)

//获取会议室列表回复
#define FRONT_CMDID_TERMINAL_ROOMLIST_REP		 (FRONT_CMDID_BASE + 3)

//用户进入会议室请求
#define FRONT_CMDID_TERMINAL_LOGINROOM_REQ       (FRONT_CMDID_BASE + 4)

//用户进入会议室回复
#define FRONT_CMDID_TERMINAL_LOGINROOM_REP       (FRONT_CMDID_BASE + 5)

//用户退出会议室请求
#define FRONT_CMDID_TERMINAL_EXITROOM_REQ        (FRONT_CMDID_BASE + 8)

//用户退出会议室回复
#define FRONT_CMDID_TERMINAL_EXITROOM_REP        (FRONT_CMDID_BASE + 9)

//用户注销请求
#define FRONT_CMDID_TERMINAL_USERLOGOUT_REQ		 (FRONT_CMDID_BASE + 10)

//用户注销回复
#define FRONT_CMDID_TERMINAL_USERLOGOUT_REP		 (FRONT_CMDID_BASE + 11)

//用户通过登入会议室ID请求获取会议室ID
#define FRONT_CMDID_TERMINAL_GETROOMID_REQ       (FRONT_CMDID_BASE + 12)

//用户通过登入会议室ID请求获取会议室ID
#define FRONT_CMDID_TERMINAL_GETROOMID_REP       (FRONT_CMDID_BASE + 13)



/************************************************************************/
/*							业务前置与业务组件                          */
/************************************************************************/

//业务组件注册请求
#define FRONT_CMDID_DEV_REGISTER_REQ	(FRONT_CMDID_BASE + 100)

//业务组件注册回复
#define FRONT_CMDID_DEV_REGISTER_REP	(FRONT_CMDID_BASE + 101)

//业务组件退出请求
#define FRONT_CMDID_DEV_EXIT_REQ		(FRONT_CMDID_BASE + 102)

//业务组件退出回复
#define FRONT_CMDID_DEV_EXIT_REP		(FRONT_CMDID_BASE + 103)

//业务组件状态报告请求
#define FRONT_CMDID_DEV_UPDATE_TOKEN	(FRONT_CMDID_BASE + 104)

//会议服务身份验证请求
#define FRONT_CMDID_CONFSRV_VERIFY_REQ	(FRONT_CMDID_BASE + 105)

//会议服务身份验证回复
#define FRONT_CMDID_CONFSRV_VERIFY_REP	(FRONT_CMDID_BASE + 106)

//查询电话网关请求
#define FRONT_CMDID_CONFSRV_QUERY_PHONEGW_REQ	(FRONT_CMDID_BASE+107)

//查询电话网关回复
#define FRONT_CMDID_CONFSRV_QUERY_PHONEGW_REP	(FRONT_CMDID_BASE+108)


/************************************************************************/
/*                   下级业务前置与上级业务前置                         */
/************************************************************************/

//业务前置注册请求
#define FRONT_CMDID_FRONTSRV_REGISTER_REQ		(FRONT_CMDID_BASE + 200)

//业务前置注册回复
#define FRONT_CMDID_FRONTSRV_REGISTER_REP		(FRONT_CMDID_BASE + 201)

//业务前置会议室列表请求
#define FRONT_CMDID_FRONTSRV_ROOMLIST_REQ		(FRONT_CMDID_BASE + 202)

//业务前置会议室列表回复
#define FRONT_CMDID_FRONTSRV_ROOMLIST_REP		(FRONT_CMDID_BASE + 203)

//转发用户请求进入会议室
#define FRONT_CMDID_FRONTSRV_LOGINROOM_REQ		(FRONT_CMDID_BASE + 204)

//转发用户请求进入会议室返回
#define FRONT_CMDID_FRONTSRV_LOGINROOM_REP		(FRONT_CMDID_BASE + 205)

//业务前置注册请求
#define FRONT_CMDID_FRONTSRV_EXIT_REQ			(FRONT_CMDID_BASE + 206)

//业务前置注册回复
#define FRONT_CMDID_FRONTSRV_EXIT_REP			(FRONT_CMDID_BASE + 207)


#pragma pack()

#endif//__FRONT_PROTOCOL_H
;