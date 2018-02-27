#ifndef __WNET_NETWORK_DEF_H
#define __WNET_NETWORK_DEF_H

typedef FS_UINT32		WNETRESULT;
typedef FS_UINT32		WSOCKET;

#define			WNET_PROXYTYPE_NONE					0x4000	//�޴���
#define			WNET_PROXYTYPE_HTTP					0x4001	//HTTP ����
#define			WNET_PROXYTYPE_SOCK4				0x4002	//SOCK4 ����
#define			WNET_PROXYTYPE_SOCK5				0x4003	//SOCK5 ����
//����ṹ����
typedef struct{
	
	FS_INT32		nProxyType;
	char			szProxyIP[32];
	FS_UINT16		wProxyPort;
	char			szUserName[64];
	char			szPassword[64];
}WNET_PROXY;

//��Ϣ�ṹ����
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

//����ֵ����
#define			WNET_RESULT_SUCCESS					0X0000	//�ɹ�
#define			WNET_RESULT_E_FAIL					0X0001	//����
#define			WNET_RESULT_E_INVALIDHANDLE			0X0002	//��Ч�ľ��
#define			WNET_RESULT_E_INVALIDSOCK			0X0003	//��Ч��SOCK
#define			WNET_RESULT_E_INVALIDPOINTER		0X0004	//��Ч��ָ��
#define			WNET_RESULT_E_INVALIDARG			0X0005	//��Ч�Ĳ���
#define			WNET_RESULT_E_OUTOFMEMORY			0X0006	//�ڴ����ʧ��
#define			WNET_RESULT_E_NOTIMPL				0X0007	//�ù���δʵ��
#define			WNET_RESULT_E_BUFOVERFLOW			0X0008	//���Ͷ�������
#define			WNET_RESULT_E_SOCKET_ERROR			0x0009	//SOCKET����
#define			WNET_RESULT_E_NOTCONNECTED			0x0010	//��δ����
#define			WNET_RESULT_E_NOTINIT				0x0011	//��δ��ʼ��


//
//�����¼�����
//
#define			WNET_EVENT_TCP_CONNECT_SUCCESS		0X1000	//���ӳɹ�
#define			WNET_EVENT_TCP_CONNECT_FAIL			0X1001	//����ʧ��
#define			WNET_EVENT_TCP_SEND_COMPLETE		0X1002	//�������ݳɹ�
#define			WNET_EVENT_TCP_RECV_COMPLETE		0X1003	//���յ���������
#define			WNET_EVENT_TCP_CLOSE				0X1005	//���ӹر�
#define			WNET_EVENT_TCP_ACCEPT				0X1006	//���յ��ͻ�������
#define			WNET_EVENT_TCP_LISTEN_FAIL			0X1007	//�����������

#define			WNET_EVENT_UDP_CLOSE				0X1100	//SOCK���ر�
#define			WNET_EVENT_UDP_RECV_COMPLETE		0X1101	//���յ���������

#define			WNET_EVENT_PING_RESULT				0x1200	//PING���ؽ��,���ͨ���̻߳򴰿���Ϣ֪ͨ,��wParam = nEventType,lParam=dwDestIP

//�������Ͷ���
#define			WNET_PARAM_SOCK_SENDBUFSIZE			0X2000	//���÷��ͻ�������С,Ĭ��Ϊ64K
#define			WNET_PARAM_SOCK_RECVBUFSIZE			0x2001	//���ý��ջ�������С,Ĭ��Ϊ64K
#define			WNET_PARAM_SOCK_CHECKTIMEOUT		0x2002	//���õ����Ӷ೤ʱ��û�н��յ�����,����Ϊ�����Ѿ��Ͽ�,Ĭ��Ϊ���޳�ʱ��,��-1
#define			WNET_PARAM_SOCK_MULTICASTTTL		0x2003	//���öಥ���ݰ�TTL,Ĭ��Ϊ64
#define			WNET_PARAM_SOCK_MULTICASTLOOP		0x2004	//���öಥ�Ƿ������·,Ĭ��Ϊ��
#define			WNET_PARAM_SOCK_BROADCAST			0X2005	//�Ƿ������͹㲥����,Ĭ��Ϊ��
#define			WNET_PARAM_SOCK_ACCEPTTIMEOUT		0X2006	//���ÿͻ������Ӻ�,���յ�һ�����ĳ�ʱʱ��,Ĭ��Ϊ15000����
#define			WNET_PARAM_SOCK_SOSENDBUFSIZE		0X2007	//����SOCKET�ײ㷢�ͻ�������С
#define			WNET_PARAM_SOCK_SORECVBUFSIZE		0x2008	//����SOCKET�ײ���ջ�������С


#endif