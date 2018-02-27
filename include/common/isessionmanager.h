#ifndef __ISESSION_MANAGER_H
#define __ISESSION_MANAGER_H

#include "wbasetype.h"
#include "wcombase.h"
#include "wnetworkdef.h"
#include "ibasecomponent.h"

#ifdef __cplusplus
extern "C" {
#endif

#define			SESSION_EVENT_ACCEPT					0x1000	//���յ��µĻỰ
#define			SESSION_EVENT_CREATED					0X1001	//�Ự�ѽ���
#define			SESSION_EVENT_CREATEFAIL				0X1002	//�Ự����ʧ��
#define			SESSION_EVENT_CLOSED					0x1003	//�Ự�ѹر�
#define			SESSION_EVENT_DATA						0x1004	//���յ��Ự����
#define			SESSION_EVENT_RECONNECTING				0x1005	//�Ự��������
#define			SESSION_EVENT_RECONNECTED				0x1006	//�Ự�����ɹ�
#define			SESSION_EVENT_SEND						0x1007	//���绺��������,����֪ͨ�����ٴη�������,���ڿɿ��Ự

	typedef struct{
		FS_INT32	nEventType;
		FS_UINT16	nSessionID;
		PBYTE	    pbData;
		FS_UINT32	dwDataLen;
		FS_UINT	    dwUserData1;
		FS_UINT	    dwUserData2;

	}SESSION_EVENT;

	typedef enum{
		SESSIONTYPE_RELIABLE,
		SESSIONTYPE_UNRELIABLE
	}SESSIONTYPE;

	typedef enum{
		SESSION_CREATING,	//���ڴ����Ự
		SESSION_CREATED,	//�Ự�ѽ���
		SESSION_DISCONNECT,	//�Ự�ѶϿ�
		SESSION_RECONNECTING,//���������Ự
		SESSION_CLOSED		//�Ự�ѹر�
	}SessionState;

	typedef struct{

		SESSIONTYPE		Type;
		FS_INT32		bTcp;
		FS_UINT32		dwLocalIP;
		FS_UINT16		wLocalPort;
		FS_UINT32		dwRemoteIP;
		FS_UINT16		wRemotePort;
		SessionState	state;
	}SESSIONINFO;

#define		SESSION_SRVADDRTYPE_TCP		0x01		//TCP
#define		SESSION_SRVADDRTYPE_UDP		0x02		//UDP
#define		SESSION_SRVADDRTYPE_HTTP	0x04		//HTTP
	typedef struct{
		FS_UINT32	dwIP;
		FS_UINT16	wPort;
		FS_UINT16	wAddrType;
	}SESSIONSRVADDRITEM;


#define WSESSION_SECURITY_NONE			0x00		//Э���޼���
#define WSESSION_SECURITY_XOR			0x01		//������

	//SessionManager2 object GUID
	// {33B5D98E-E3AD-4407-8311-960DE9591D2A}
	DEFINE_GUID( CLSID_SessionManager2, 
		0x33b5d98e, 0xe3ad, 0x4407, 0x83, 0x11, 0x96, 0xd, 0xe9, 0x59, 0x1d, 0x2a);

	//ISessionManager's GUID
	// {0290FEBF-B376-4ebd-8B23-664D03E4DD6B}
	DEFINE_GUID(IID_ISessionManager, 
	0x290febf, 0xb376, 0x4ebd, 0x8b, 0x23, 0x66, 0x4d, 0x3, 0xe4, 0xdd, 0x6b);

	//----------------------------------------------------------------------------
	// ISessionManager
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(ISessionManager,IUnknown )
	{		
		STDMETHOD(Start) (THIS_) PURE;
		STDMETHOD(Stop)( THIS_ ) PURE;

		//��������������˿�
		STDMETHOD_(FS_UINT32,AddUdpListen) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort ) PURE;		
		
		STDMETHOD(RemoveUdpListen) (THIS_ FS_UINT32	uListern ) PURE;		

		STDMETHOD_(FS_UINT32,AddTcpListen) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort ) PURE;		
		
		STDMETHOD(RemoveTcpListen) (THIS_ FS_UINT32 uListern ) PURE;

		STDMETHOD(GetAddrLink)( THIS_ CHAR*	lpszLink,FS_UINT32 *pdwSize,BOOL bTcp,BOOL bUdp ) PURE;

		//ע��Ӧ��
		STDMETHOD(RegisterApplication)( THIS_ FS_UINT16 wApplicationID,WBASE_NOTIFY* pNotify,BYTE bSecurityType ) PURE;

		STDMETHOD(UnRegisterApplication)( THIS_ FS_UINT16 wApplicationID ) PURE;

		//�����Ự
		STDMETHOD_( FS_UINT16,CreateSession )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD(Send)( THIS_ FS_UINT16 nSessionID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;

		STDMETHOD(GetSessionInfo)( THIS_ FS_UINT16 nSessionID,SESSIONINFO *pInfo ) PURE;

		STDMETHOD(SetSessionNotify)( THIS_ FS_UINT16 nSessionID,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD(SetUserData)( THIS_ FS_UINT16 nSessionID,FS_UINT dwUserData1,FS_UINT dwUserData2 ) PURE;

		STDMETHOD_(SESSION_EVENT*,GetEvent)( THIS_ FS_UINT16 nSessionID) PURE;

		STDMETHOD( FreeEvent )( THIS_ FS_UINT16 nSessionID,SESSION_EVENT *pEvent ) PURE;

		STDMETHOD( SetSessionTimeout )( THIS_ FS_UINT16 nSessionID,FS_UINT32 dwTimeout ) PURE;

		STDMETHOD( CloseSession )( THIS_ FS_UINT16 nSessionID ) PURE;
	};

	//�������Ͷ���
#define			WSESSION_PARAM_SOSENDBUFSIZE		0X1000	//����SOCKET�ײ㷢�ͻ�������С
#define			WSESSION_PARAM_SENDBUFSIZE			0X1001	//����SOCKET���ͻ�������С,TCPĬ��Ϊ32K,UDPĬ��Ϊ16K
#define			WSESSION_PARAM_ACKSENDBUFSIZE		0X1002	//����ȷ�Ϸ��ͻ�������С,���ڿɿ��Ự

#define			WSESSION_PARAM_SORECVBUFSIZE		0x1005	//����SOCKET�ײ���ջ�������С
#define			WSESSION_PARAM_RECVBUFSIZE			0x1006	//����SOCKET���ջ�������С,TCPĬ��Ϊ16K,UDPĬ��Ϊ64K

#define			WSESSION_PARAM_CHECKTIMEOUT			0x1010	//���õ�SESSION�೤ʱ��û�н��յ�����,����Ϊ�Ự�Ѿ��Ͽ�,����ʼ����,Ĭ��Ϊ16��

	//ԭʼӦ�ò�������
	typedef struct{
		
		CHAR		pbFlagData[32];		//��ʶ����,���ܳ���32���ֽ�
		FS_UINT32		dwFlagLen;			//��ʶ���ݳ���
		BOOL		bCaseSensitive;		//��ʶ�����Ƿ��Сд����
		BOOL		bSupportTCP;		//�Ƿ�֧��TCP
		BOOL		bSupportUDP;		//�Ƿ�֧��UDP
		
	}SESSIONRAWAPP;

	//ISessionManager2's GUID
	// {A413E359-E79F-4804-B166-34B77ED20D2F}
	DEFINE_GUID( IID_ISessionManager2, 
		0xa413e359, 0xe79f, 0x4804, 0xb1, 0x66, 0x34, 0xb7, 0x7e, 0xd2, 0xd, 0x2f);

	DECLARE_INTERFACE_(ISessionManager2,IUnknown )
	{		
		STDMETHOD(Start) (THIS_) PURE;
		STDMETHOD(Stop)( THIS_ ) PURE;
		
		//��������˿�
		STDMETHOD_(FS_UINT32,AddUdpListen2) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort,BOOL bServer ) PURE;
		
		STDMETHOD(RemoveUdpListen) (THIS_ FS_UINT32	uListern ) PURE;		
		
		STDMETHOD_(FS_UINT32,AddTcpListen2) (THIS_ FS_UINT32 dwBindIP,FS_UINT16 wBindPort,BOOL bServer ) PURE;
		
		STDMETHOD(RemoveTcpListen) (THIS_ FS_UINT32 uListern ) PURE;
		
		STDMETHOD(GetAddrLink)( THIS_ CHAR*	lpszLink,FS_UINT32 *pdwSize,BOOL bTcp,BOOL bUdp ) PURE;
		
		//ע��Ӧ��
		STDMETHOD(RegisterApplication)( THIS_ FS_UINT16 wApplicationID,WBASE_NOTIFY* pNotify,BYTE bSecurityType ) PURE;
		
		STDMETHOD(UnRegisterApplication)( THIS_ FS_UINT16 wApplicationID ) PURE;
		
		//
		//ע��ԭʼӦ��,����Ӧ��,ֻ��Ϊ�˹���˿�,�Ự�㲻�Ը���Ӧ�õ����ݰ����κδ���.
		//����TCP��Ӧ��,�����ݿͻ��˷��͵ĵ�һ������ǰ�漸���ֽڵ������ж�Ӧ������
		//����UDP��Ӧ��,������ÿ������ǰ�漸���ֽڵ������������ж�Ӧ������
		//����ϵͳ�����Ӧ��ID
		//
		STDMETHOD_(FS_UINT32,RegisterRawApplication)( THIS_ SESSIONRAWAPP *pApplication,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD(UnRegisterRawApplication)( THIS_ FS_UINT32 dwRawAppID ) PURE;

		//
		//��ȡԭʼӦ�õ���Ϣ��ֱ�ӷ��������¼�������ֱ�ӵ��������ӿ��ͷ��¼�
		//
		STDMETHOD_( WNET_EVENT*,GetRawEvent )( THIS_ FS_UINT32 dwRawAppID ) PURE;

			
		STDMETHOD( FreeRawEvent )( THIS_ FS_UINT32 dwRawAppID,WNET_EVENT* pEvent ) PURE;

		//�����Ự
		STDMETHOD_( FS_UINT16,CreateSession )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify ) PURE;
		
		STDMETHOD(Send)( THIS_ FS_UINT16 nSessionID,PBYTE pbData,FS_UINT32 dwDataLen ) PURE;
		
		STDMETHOD(GetSessionInfo)( THIS_ FS_UINT16 nSessionID,SESSIONINFO *pInfo ) PURE;
		
		STDMETHOD(SetSessionNotify)( THIS_ FS_UINT16 nSessionID,WBASE_NOTIFY* pNotify ) PURE;
		
		STDMETHOD(SetUserData)( THIS_ FS_UINT16 nSessionID,FS_UINT dwUserData1,FS_UINT dwUserData2 ) PURE;
		
		STDMETHOD_(SESSION_EVENT*,GetEvent)( THIS_ FS_UINT16 nSessionID) PURE;
		
		STDMETHOD( FreeEvent )( THIS_ FS_UINT16 nSessionID,SESSION_EVENT *pEvent ) PURE;
		
		STDMETHOD( SetSessionTimeout )( THIS_ FS_UINT16 nSessionID,FS_UINT32 dwTimeout ) PURE;
		
		//����Session����
		STDMETHOD( SetSessionParam )( THIS_ FS_UINT16 uSessionID,FS_INT32 nParamType,const CHAR* pValue,FS_INT32 nValueSize ) PURE;
		
		//��ȡSession����
		STDMETHOD( GetSessionParam )( THIS_ FS_UINT16 uSessionID,FS_INT32 nParamType,CHAR* pValue,FS_INT32* pValueSize ) PURE;

		STDMETHOD( CloseSession )( THIS_ FS_UINT16 nSessionID ) PURE;

		//������ѡ�����ӵ�ַ
		STDMETHOD( SetPreferAddr )( THIS_ FS_UINT32 dwPreferAddr ) PURE;

		//�����Ự,ʹ�ñ��ؼ�����UDP�˿�
		STDMETHOD_( FS_UINT16,CreateSession2 )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify,FS_UINT32 uUdpListen ) PURE;

		//�����Ự,ʹ�ù���TCP����
		STDMETHOD_( FS_UINT16,CreateSession3 )( THIS_ const CHAR* szServerAddrLink,SESSIONTYPE Type,FS_UINT16 wDstApplicationID,WBASE_NOTIFY* pNotify,FS_UINT32 uUdpListen,BOOL bShareTCP ) PURE;

		//�����Ự,ʹ�ù���TCP����
		STDMETHOD_( FS_UINT32,ParseAndSortAddrLink )( THIS_ const CHAR* szServerAddrLink,FS_UINT32 dwAddrTypeMask,FS_UINT32 dwPreferAddrType,HANDLE hStopEvent,SESSIONSRVADDRITEM **ppSrvAddrItem ) PURE;

		//�ͷŵ�ַ���ڴ�
		STDMETHOD( FreeSrvAddrItem )( THIS_ SESSIONSRVADDRITEM *pSrvAddrItem ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif