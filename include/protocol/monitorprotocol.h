#ifndef __MONITOR_PROTOCOL_H
#define __MONITOR_PROTOCOL_H

#pragma pack(1)

/************************************************************************/
/*                        WEB��̨��������                             */
/************************************************************************/

#define MONITOR_CMDID_BASE				40000		//���Э������ID��ʼֵ

//WEB��̨��½����
#define MONITOR_CMDID_WEB_ACCOUNTLOGIN_REQ		 (MONITOR_CMDID_BASE)

//WEB��̨��½�ظ�
#define MONITOR_CMDID_WEB_ACCOUNTLOGIN_REP		 (MONITOR_CMDID_BASE + 1)

//��ѯMCU��������ַ����
#define MONITOR_CMDID_WEB_QUERYSRVADDR_REQ		 (MONITOR_CMDID_BASE + 2)

//��ѯMCU��������ַ�ظ�
#define MONITOR_CMDID_WEB_QUERYSRVADDR_REP		 (MONITOR_CMDID_BASE + 3)

//����MCU��������ַ����
#define MONITOR_CMDID_WEB_OPERATIONSRVADDR_REQ	 (MONITOR_CMDID_BASE + 4)

//����MCU��������ַ�ظ�
#define MONITOR_CMDID_WEB_OPERATIONSRVADDR_REP	 (MONITOR_CMDID_BASE + 5)

//ҵ����������
#define MONITOR_CMDID_WEB_SERVICERESET_REQ		 (MONITOR_CMDID_BASE + 6)

//ҵ�����ûظ�
#define MONITOR_CMDID_WEB_SERVICERESET_REP		 (MONITOR_CMDID_BASE + 7)

//���������÷���
#define MONITOR_CMDID_WEB_SRVRESET_REQ			(MONITOR_CMDID_BASE + 8)

//���������ûظ�
#define MONITOR_CMDID_WEB_SRVRESET_REP			(MONITOR_CMDID_BASE + 9)

//MCU����״̬����
#define MONITOR_CMDID_WEB_REALTIMEDATA_REQ		(MONITOR_CMDID_BASE + 10)

//MCU����״̬�ظ�
#define MONITOR_CMDID_WEB_REALTIMEDATA_REP		(MONITOR_CMDID_BASE + 11)

//MCUҵ������б�����
#define MONITOR_CMDID_WEB_SERVICELIST_REQ		(MONITOR_CMDID_BASE + 12)

//MCUҵ������б�ظ�
#define MONITOR_CMDID_WEB_SERVICELIST_REP		(MONITOR_CMDID_BASE + 13)

//MCU��Ȩ��������
#define MONITOR_CMDID_WEB_LICENSEACTIVATED_REQ	(MONITOR_CMDID_BASE + 16)

//MCU��Ȩ����ظ�
#define MONITOR_CMDID_WEB_LICENSEACTIVATED_REP	(MONITOR_CMDID_BASE + 17)

//��/�رն�̬��ַע�Ṧ��
#define MONITOR_CMDID_WEB_ARQS_REQ				(MONITOR_CMDID_BASE + 18)

//��̬��ַע�Ṧ�ܷ���
#define MONITOR_CMDID_WEB_ARQS_REP				(MONITOR_CMDID_BASE + 19)

//��ѯ����������������������
#define MONITOR_CMDID_WEB_QUERY_NETCONNTYPE_REQ	(MONITOR_CMDID_BASE + 20)

//��ѯ�����������������ͻظ�
#define MONITOR_CMDID_WEB_QUERY_NETCONNTYPE_REP	(MONITOR_CMDID_BASE + 21)

//���÷���������������������
#define MONITOR_CMDID_WEB_SET_NETCONNTYPE_REQ	(MONITOR_CMDID_BASE + 22)

//���÷����������������ͻظ�
#define MONITOR_CMDID_WEB_SET_NETCONNTYPE_REP	(MONITOR_CMDID_BASE + 23)

//����ע���ļ�����
#define MONITOR_CMDID_WEB_CREATEREGFILE_REQ		(MONITOR_CMDID_BASE + 24)

//MCU����ע���ļ��ظ�
#define MONITOR_CMDID_WEB_CREATEREGFILE_REP		(MONITOR_CMDID_BASE + 25)

//�����豸ID����
#define MONITOR_CMDID_WEB_UPDATEDEVID_REQ		(MONITOR_CMDID_BASE + 26)

//�����豸ID�ظ�
#define MONITOR_CMDID_WEB_UPDATEDEVID_REP		(MONITOR_CMDID_BASE + 27)

#pragma pack()

#endif//__MONITOR_PROTOCOL_H
;