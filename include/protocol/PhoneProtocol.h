#ifndef __PHONE_PROTOCOL_H
#define __PHONE_PROTOCOL_H

#pragma pack(1)

#define PHONE_CMDID_BASE				7000		//�绰����Э������ID��ʼֵ

#define	PHONE_PROTOCOL_VERSION			"1.0"		//Э��汾

/************************************************************************
˵��:
1 ��Χ:7000-7399
2 7XXY:YΪ������ʾ����Ϊż����ʾӦ��
3 ����:
1�����������绰���أ�7000-7099                             
************************************************************************/

/************************************************************************/
/*                       �绰������������                             */
/************************************************************************/
//7000-7099
#define PHONE_CMDID_CONF_BASE				(PHONE_CMDID_BASE)

//���������������
#define PHONE_CMDID_CONF_CONNECT_REQ		(PHONE_CMDID_CONF_BASE+1)
//����������ӷ���
#define PHONE_CMDID_CONF_CONNECT_REP		(PHONE_CMDID_CONF_BASE+2)

//��������
#define PHONE_CMDID_CONF_MAKECALL_REQ		(PHONE_CMDID_CONF_BASE+3)
//���з���
#define PHONE_CMDID_CONF_MAKECALL_REP		(PHONE_CMDID_CONF_BASE+4)

//�һ�����
#define PHONE_CMDID_CONF_HANGUP_REQ			(PHONE_CMDID_CONF_BASE+5)
//�һ�����
#define PHONE_CMDID_CONF_HANGUP_REP			(PHONE_CMDID_CONF_BASE+6)

//����״̬֪ͨ
#define PHONE_CMDID_CONF_CALLSTATE_NOTIFY	(PHONE_CMDID_CONF_BASE+7)

#define PHONE_MAX_SERVERADDR 128

#define PHONE_MAX_CALLNUM    22

#define PHONE_MAX_NICKNAME   40

#define PHONE_MAX_PWDLEN     40

#define PHONE_MAX_CLIENTVER  20

#pragma pack()

#endif//__PHONE_PROTOCOL_H
;