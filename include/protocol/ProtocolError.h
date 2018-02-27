#ifndef __PROTOCOL_ERROR_DEFINE_H
#define __PROTOCOL_ERROR_DEFINE_H

#define		WPROTOCOL_RESULT_SUCCESS			0X0000		//成功

#define		WPROTOCOL_RESULT_UNKNOWN			0x1001		//未知错误
#define		WPROTOCOL_RESULT_EXCEPTION			0x1002		//异常错误
#define		WPROTOCOL_RESULT_SERVERERROR		0X1003		//服务器内部错误
#define		WPROTOCOL_RESULT_INVALIDSESSION		0X1004		//无效的会话
#define		WPROTOCOL_RESULT_USERNOTFOUND		0X1005		//用户未找到
#define		WPROTOCOL_RESULT_VERIFYFAILED		0X1006		//验证失败
#define		WPROTOCOL_RESULT_ACCESSDENIED		0X1007		//用户无权访问
#define		WPROTOCOL_RESULT_INVALIDARG			0x1008		//参数错误
#define		WPROTOCOL_RESULT_NOWMAINTENANCE		0x1009		//系统正在维护，暂停服务
#define		WPROTOCOL_RESULT_TOOACCESS			0x100A		//访问人数过多，暂停服务
#define		WPROTOCOL_RESULT_INVALIDVALUE		0x100B		//数据无效

#define		WPROTOCOL_RESULT_FILENOTFOUND		0X2001		//文件未找到
#define		WPROTOCOL_RESULT_LISTNOTFOUND		0X2002		//文件列表未找到
#define		WPROTOCOL_RESULT_LISTEXISTED		0X2003		//文件列表已存在
#define		WPROTOCOL_RESULT_CHANNELNOTFOUND	0X2004		//文件传输通道不存在
#define		WPROTOCOL_RESULT_FILEUPLOADING		0X2005		//文件正在上传中，不允许同时上传一个文件
#define		WPROTOCOL_RESULT_FILEOVERSIZE		0X2006		//文件大小超过限定值
#define		WPROTOCOL_RESULT_FILENOTUPLOADED	0X2007		//发送者还未上传该文件
#define		WPROTOCOL_RESULT_FILEEXISTED		0X2008		//文件已存在

#define		WPROTOCOL_RESULT_PASSWORDERROR		0x2101		//用户密码错误
#define		WPROTOCOL_RESULT_ROOMNOTFOUND		0x2102		//房间未找到
#define		WPROTOCOL_RESULT_ROOMOVERFLOW		0x2103		//房间已满
#define		WPROTOCOL_RESULT_APPMISMATCH		0x2104		//应用类型不匹配
#define		WPROTOCOL_RESULT_SRVMISMATCH		0X2105		//服务器不匹配
#define		WPROTOCOL_RESULT_SRVNOTFOUND		0x2106		//未找到指定的服务器
#define		WPROTOCOL_RESULT_SRVOVERFLOW		0X2107		//服务器已满员
#define		WPROTOCOL_RESULT_USEREXISTED		0x2108		//用户已存在
#define		WPROTOCOL_RESULT_NEEDROOMPASSWORD	0X2109		//需要输入房间密码
#define		WPROTOCOL_RESULT_ROOMLOCKED			0X210A		//房间已锁定
#define		WPROTOCOL_RESULT_ROOMOVERTIME		0X210B		//房间已过期
#define		WPROTOCOL_RESULT_ROOMOFF			0X210C		//房间已关闭
#define		WPROTOCOL_RESULT_DENYKNOCK			0X210D		//主持人拒绝用户进入锁定房间的请求
#define		WPROTOCOL_RESULT_MULTIDENYKNOCK		0X210E		//用户被列入黑名单，禁止进入锁定房间
#define		WPROTOCOL_RESULT_SERVERCASFAILED	0X210F		//服务器级联失败
#define		WPROTOCOL_RESULT_SRVNOSTART			0x2110		//服务器未启动
#define		WPROTOCOL_RESULT_SRVSTOPED			0x2111		//服务器已停止
#define		WPROTOCOL_RESULT_NEEDPAYMENT		0x2112		//服务已到期或余额不足，请及时续费
#define		WPROTOCOL_RESULT_PRODUCTSRVSTOPED	0x2113		//订购的产品服务被停用

#define		WPROTOCOL_RESULT_CHAIR_PWDERR           0x2114	    //主席密码错误.
#define		WPROTOCOL_RESULT_ROOM_IDERR             0x2115      //该会议室号不存在，请重新输入。
#define		WPROTOCOL_RESULT_LOGIN_NICKNAME      	0x2116		//访问被拒绝，只允许以用户名密码方式登录。。
#define		WPROTOCOL_RESULT_CHAIR_OPEN_OPTION   	0x2117		//当前会议不允许申请主席。
#define		WPROTOCOL_RESULT_CHAIR_NOTOPENROOM 		0x2118		//主席未开启会议

#define		WPROTOCOL_RESULT_INVITECODE_ERROR	 	0x2119		//邀请码错误
#define		WPROTOCOL_RESULT_INVITECODE_EXPIRES 	0x211A		//邀请码过期

#define		WPROTOCOL_RESULT_DISABLE_MOBILE_LOGIN 	0x211B		//不支持手机端登录

/************************************************************************/
/*                            电话接入错误码定义                        */
/************************************************************************/
#define		WPROTOCOL_RESULT_NOT_ENOUGH_CALL_COMPANY	0x3001	// 企业剩余电话呼叫路数不够
#define		WPROTOCOL_RESULT_NOT_ENOUGH_CALL_GATEWAY	0x3002	// 电话网关剩余电话呼叫路数不够
#define		WPROTOCOL_RESULT_REPEATED_PHONE_CALL		0x3003	// 重复电话呼叫
#define     WPROTOCOL_RESULT_NOT_ENOUGH_BNANCE_COMPANY	0x3004	// 企业账户余额不足

/************************************************************************/
/*                            监控系统错误码定义                        */
/************************************************************************/
#define		MONITORPROTOCOL_RESULT_WEB_QUERYADPTER_ERROR	0x9000		//查询适配器地址失败
#define		MONITORPROTOCOL_RESULT_WEB_UNKNOWOPERADDR_ERROR	0x9001		//未知适配器操作类型
#define		MONITORPROTOCOL_RESULT_WEB_ADPTERUPDATE_ERROR	0x9002		//适配器地址更新失败
#define		MONITORPROTOCOL_RESULT_WEB_ADDRMAP_ERROR		0x9003		//网络地址映射操作失败
#define		MONITORPROTOCOL_RESULT_WEB_SRVRESET_ERRROR		0x9004		//服务器重置失败
#define		MONITORPROTOCOL_RESULT_WEB_SERVICERESET_NOFOUND	0x9005		//业务没有找到
#define		MONITORPROTOCOL_RESULT_WEB_SERVICERESET_ERRROR	0x9006		//业务重置失败
#define		MONITORPROTOCOL_RESULT_WEB_QUERYREALTIME_ERRROR	0x9007		//查询服务器运行状态失败
#define		MONITORPROTOCOL_RESULT_WEB_QUERYNETTYPE_ERRROR	0x9009		//查询服务器网络连接类型失败
#define		MONITORPROTOCOL_RESULT_WEB_LICENSEACTIVATED_ERRROR	0x900a	//授权文件激活失败
#define		MONITORPROTOCOL_RESULT_WEB_CREATEREGFILE_ERRROR	0x900b		//生成注册文件失败
#define		MONITORPROTOCOL_RESULT_WEB_SETNETTYPE_ERROR		0x900c		//设置服务器网络连接类型失败

#endif