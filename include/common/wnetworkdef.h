#ifndef __WNET_NETWORK_DEF_H
#define __WNET_NETWORK_DEF_H

typedef FS_UINT32		WNETRESULT;
typedef FS_UINT32		WSOCKET;

#define			WNET_PROXYTYPE_NONE					0x4000	//无代理
#define			WNET_PROXYTYPE_HTTP					0x4001	//HTTP 代理
#define			WNET_PROXYTYPE_SOCK4				0x4002	//SOCK4 代理
#define			WNET_PROXYTYPE_SOCK5				0x4003	//SOCK5 代理
//代理结构定义
typedef struct{
	
	FS_INT32		nProxyType;
	char			szProxyIP[32];
	FS_UINT16		wProxyPort;
	char			szUserName[64];
	char			szPassword[64];
}WNET_PROXY;

//消息结构定义
typedef struct{
	
	FS_INT32		nEventType;
	WSOCKET			sock;
	char*			pData;
	FS_INT32		nDataLen;
	FS_UINT32		dwDestIP;
	FS_UINT32		dwLocalIP;
	FS_UINT16		wDestPort;
	FS_UINT16		wLocalPort;
	FS_UINT			dwUserData;
	FS_UINT32		dwReserved1;
	FS_UINT32		dwReserved2;
	
}WNET_EVENT;

//返回值定义
#define			WNET_RESULT_SUCCESS					0X0000	//成功
#define			WNET_RESULT_E_FAIL					0X0001	//错误
#define			WNET_RESULT_E_INVALIDHANDLE			0X0002	//无效的句柄
#define			WNET_RESULT_E_INVALIDSOCK			0X0003	//无效的SOCK
#define			WNET_RESULT_E_INVALIDPOINTER		0X0004	//无效的指针
#define			WNET_RESULT_E_INVALIDARG			0X0005	//无效的参数
#define			WNET_RESULT_E_OUTOFMEMORY			0X0006	//内存分配失败
#define			WNET_RESULT_E_NOTIMPL				0X0007	//该功能未实现
#define			WNET_RESULT_E_BUFOVERFLOW			0X0008	//发送队列已满
#define			WNET_RESULT_E_SOCKET_ERROR			0x0009	//SOCKET错误
#define			WNET_RESULT_E_NOTCONNECTED			0x0010	//还未连接
#define			WNET_RESULT_E_NOTINIT				0x0011	//还未初始化


//
//网络事件定义
//
#define			WNET_EVENT_TCP_CONNECT_SUCCESS		0X1000	//连接成功
#define			WNET_EVENT_TCP_CONNECT_FAIL			0X1001	//连接失败
#define			WNET_EVENT_TCP_SEND_COMPLETE		0X1002	//发送数据成功
#define			WNET_EVENT_TCP_RECV_COMPLETE		0X1003	//接收到网络数据
#define			WNET_EVENT_TCP_CLOSE				0X1005	//连接关闭
#define			WNET_EVENT_TCP_ACCEPT				0X1006	//接收到客户端连接
#define			WNET_EVENT_TCP_LISTEN_FAIL			0X1007	//网络监听出错

#define			WNET_EVENT_UDP_CLOSE				0X1100	//SOCK被关闭
#define			WNET_EVENT_UDP_RECV_COMPLETE		0X1101	//接收到网络数据

#define			WNET_EVENT_PING_RESULT				0x1200	//PING返回结果,如果通过线程或窗口消息通知,则wParam = nEventType,lParam=dwDestIP

//参数类型定义
#define			WNET_PARAM_SOCK_SENDBUFSIZE			0X2000	//设置发送缓存区大小,默认为64K
#define			WNET_PARAM_SOCK_RECVBUFSIZE			0x2001	//设置接收缓存区大小,默认为64K
#define			WNET_PARAM_SOCK_CHECKTIMEOUT		0x2002	//设置当连接多长时间没有接收到数据,即认为连接已经断开,默认为无限长时间,即-1
#define			WNET_PARAM_SOCK_MULTICASTTTL		0x2003	//设置多播数据包TTL,默认为64
#define			WNET_PARAM_SOCK_MULTICASTLOOP		0x2004	//设置多播是否允许回路,默认为否
#define			WNET_PARAM_SOCK_BROADCAST			0X2005	//是否允许发送广播数据,默认为否
#define			WNET_PARAM_SOCK_ACCEPTTIMEOUT		0X2006	//设置客户端连接后,接收第一个包的超时时间,默认为15000毫秒
#define			WNET_PARAM_SOCK_SOSENDBUFSIZE		0X2007	//设置SOCKET底层发送缓存区大小
#define			WNET_PARAM_SOCK_SORECVBUFSIZE		0x2008	//设置SOCKET底层接收缓存区大小


#endif