#ifndef __WNETWORK_H
#define	__WNETWORK_H

#include "wbasetype.h"
#include "wnetworkdef.h"
#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
#include "log.h"
#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX

//��ʼ�������
WNETRESULT		WNET_Init( BOOL bUseTcp,BOOL bUseUdp,FS_UINT32 dwMaxTcpCount,FS_UINT32 dwMaxUdpCount, LPCTSTR szLogPath);

//�ͷ������
WNETRESULT		WNET_Release();

//������־����
WNETRESULT		WNET_SetLogLevel(FS_INT32 nLogLevel);
#if defined _FS_OS_WIN_SERVER || defined _FS_OS_LINUX
WNETRESULT		WNET_SetLogLevel(LogLevel nLogLevel);

//������־��������Ϣ
WNETRESULT      WNET_SetLogInfo(ILogMgr *pLogMgr, FS_INT nLoggerID);
#endif // _FS_OS_WIN_SERVER || _FS_OS_LINUX

//���ô���
WNETRESULT		WNET_SetProxy( WNET_PROXY *pProxy );

//��ȡ����
WNETRESULT		WNET_GetProxy( WNET_PROXY *pProxy );


//���Դ��������
WNETRESULT		WNET_TestProxy( WNET_PROXY *pProxy,char *szDestAddr,FS_UINT16 wDestPort );

//
//TCP����ӿ�
//

//�򿪼����˿�
WSOCKET			WNET_TCP_AddListen( FS_UINT32 dwListenIP,FS_UINT16 wListenPort,WBASE_NOTIFY *pMode );

//�رռ����˿�
WNETRESULT		WNET_TCP_RemoveListen( WSOCKET sock );

//���ӷ�����
WSOCKET			WNET_TCP_Connect( FS_UINT32 dwDestIP,FS_UINT16 wDestPort,FS_UINT32 dwWaitTime,WBASE_NOTIFY *pMode,FS_UINT dwUserData );

//������Ϣ֪ͨ��ʽ
WNETRESULT		WNET_TCP_SetNotify( WSOCKET sock,WBASE_NOTIFY *pMode );

//��ͣ���ݽ���
WNETRESULT		WNET_TCP_PauseRead( WSOCKET sock,BOOL bPause );

//��������
WNETRESULT		WNET_TCP_Send( WSOCKET sock,char *pData,FS_INT32 nDataLen );

//��ȡ�¼�
WNET_EVENT*		WNET_TCP_PopupMsg( WSOCKET sock,FS_UINT32 dwWaitTime );

//�ͷ��¼�
WNETRESULT		WNET_TCP_FreeMsg( WSOCKET sock,WNET_EVENT *pEvent );

//���ò���
WNETRESULT		WNET_TCP_SetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//�����û�����
WNETRESULT		WNET_TCP_SetUserData( WSOCKET sock,FS_UINT dwUserData );

//��ȡ����
WNETRESULT		WNET_TCP_GetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//�ر�SOCK
WNETRESULT		WNET_TCP_Close( WSOCKET sock );

WNET_EVENT*		WNET_TCP_AllocMsg( );

//
//UDP����ӿ�
//

//����UDP SOCK
WSOCKET			WNET_UDP_Create( FS_UINT32 dwBindIP,FS_UINT16 wBindPort,WBASE_NOTIFY *pMode,FS_UINT dwUserData );

//������Ϣ֪ͨ��ʽ
WNETRESULT		WNET_UDP_SetNotify( WSOCKET sock,WBASE_NOTIFY *pMode );

//����ಥ��
WNETRESULT		WNET_UDP_JoinGroup( WSOCKET sock,FS_UINT32 dwGroupIP );

//�뿪�ಥ��
WNETRESULT		WNET_UDP_LeaveGroup( WSOCKET sock,FS_UINT32 dwGroupIP );

//��������
WNETRESULT		WNET_UDP_Send( WSOCKET sock,char *pData,FS_INT32 nDataLen,FS_UINT32 dwDestIP,FS_UINT16 wDestPort );

//��ȡ�¼�
WNET_EVENT*		WNET_UDP_PopupMsg( WSOCKET sock,FS_UINT32 dwWaitTime );

//�ͷ��¼�
WNETRESULT		WNET_UDP_FreeMsg( WSOCKET sock,WNET_EVENT *pEvent );

WNET_EVENT*		WNET_UDP_AllocMsg( );

//�����û�����
WNETRESULT		WNET_UDP_SetUserData( WSOCKET sock,FS_UINT dwUserData );

//���ò���
WNETRESULT		WNET_UDP_SetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//��ȡ����
WNETRESULT		WNET_UDP_GetParam( WSOCKET sock,FS_INT32 nType,void *pValue,FS_INT32 *pValueSize );

//�ر�SOCK
WNETRESULT		WNET_UDP_Close( WSOCKET sock );

//PING
WNETRESULT		WNET_Ping( FS_UINT32 dwDestIP,WBASE_NOTIFY *pMode );

//��ȡPING���
WNETRESULT		WNET_GetPingResult( FS_UINT32 dwDestIP,FS_UINT32* pdwMin,FS_UINT32* pdwMax,FS_UINT32* pdwAvg );

WNETRESULT		WNET_RemovePing( FS_UINT32 dwDestIP,WBASE_NOTIFY *pMode );


#endif