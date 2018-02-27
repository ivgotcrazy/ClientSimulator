#ifndef __CONF_PROTOCOL_H
#define __CONF_PROTOCOL_H

#include "ProtocolCommonDefine.h"

#pragma pack(1)

#define	CONF_PROTOCOL_VERSION		"1.0"			//Э��汾

#define CONF_CMDID_BASE				6500		//Э������ID��ʼֵ

#define STATE_NONE					0X00
#define STATE_WAITING				0X01
#define STATE_DONE					0X02


#define USERTYPE_UNREGISTER			0X00		//��ע���û�
#define	USERTYPE_REGISTER			0X01		//ע���û�

//�Ƿ񷵻������û��б�
#define	GET_ONLINE_USERLIST			0x0			//���������û�
#define	GET_ALL_USERLIST			0x1			//����ȫ���û�

//�豸��������
#define	DEV_OPERATION_ADD			0x1			//�����豸
#define	DEV_OPERATION_MODIFY		0x2			//�޸��豸
#define	DEV_OPERATION_DEL			0x3			//ɾ���豸

//ϵͳ��Ϣ����
#define SYSMSG_TYPE_CHAT			0x01		//������Ϣ
#define SYSMSG_TYPE_WND				0x02		//������Ϣ
#define SYSMSG_TYPE_WEB				0x03		//WEB��Ϣ
#define SYSMSG_TYPE_NAVIGATE		0x04		//�������Ϣ
#define SYSMSG_TYPE_LOGINLOGO		0x05		//��¼LOGO

////////////////////////////////////////////////////////////////////////////////
//  �ն���������֮�������
////////////////////////////////////////////////////////////////////////////////

//�ͻ������������֤�汾��Ϣ
#define	CONF_CMDID_VERSIONREQ		(CONF_CMDID_BASE)

//��������ͻ��˷��ذ汾��Ϣ
#define	CONF_CMDID_VERSIONREP		(CONF_CMDID_BASE+100)

//�ͻ��˵�¼����
#define CONF_CMDID_LOGINREQ			(CONF_CMDID_BASE+1)

//���������ص�¼���
#define CONF_CMDID_LOGINREP			(CONF_CMDID_BASE+101)

//������֪ͨ�����û���Ϣ
#define CONF_CMDID_USERENTER		(CONF_CMDID_BASE+102)

//���������û��б�
#define CONF_CMDID_REQOFFLINES		(CONF_CMDID_BASE+3)

//���������������û��б�
#define CONF_CMDID_OUTLINE			(CONF_CMDID_BASE+103)

//�����˴���������
#define CONF_CMDID_ALLOWKNOCK		(CONF_CMDID_BASE+4)

//������֪ͨ��������������
#define CONF_CMDID_KNOCKNOTIFY		(CONF_CMDID_BASE+104)


//�ͻ����˳�����
#define CONF_CMDID_LOGOUTREQ		(CONF_CMDID_BASE+5)

//������֪ͨ�û��˳�
#define CONF_CMDID_USERLEAVE		(CONF_CMDID_BASE+105)

//�û��߳������û�
#define CONF_CMDID_KICKUSER			(CONF_CMDID_BASE+6)

//������֪ͨ���߳��û��ѱ��߳�
#define CONF_CMDID_USERKICKED		(CONF_CMDID_BASE+106)

//�����˹رշ���
#define CONF_CMDID_CLOSEROOM		(CONF_CMDID_BASE+7)

//�������رշ���
#define CONF_CMDID_ROOMCLOSED		(CONF_CMDID_BASE+107)

//�û����±��ص�����Ƶ�豸��Ϣ
#define CONF_CMDID_AVINFO			(CONF_CMDID_BASE+8)

//������֪ͨ�û�����Ƶ�豸��Ϣ���
#define CONF_CMDID_AVINFONOTIFY		(CONF_CMDID_BASE+108)

//�ı��û�״̬
#define CONF_CMDID_CHANGEUSERSTATE	(CONF_CMDID_BASE+9)

//������֪ͨ�û�״̬�Ѹı�
#define CONF_CMDID_USERSTATECHANGED	(CONF_CMDID_BASE+109)

//�û��ı����״̬
#define CONF_CMDID_CHANGECONFSTATE	(CONF_CMDID_BASE+10)

//������֪ͨ����״̬�Ѹı�
#define CONF_CMDID_CONFSTATECHANGED	(CONF_CMDID_BASE+110)

//�û������Ϊ������
#define CONF_CMDID_REQCHAIRRIGHT	(CONF_CMDID_BASE+11)

//�������������������˽��
#define CONF_CMDID_REQCHAIRRIGHTRET	(CONF_CMDID_BASE+111)

//�û�����������Ϣ
#define CONF_CMDID_CHATMSG			(CONF_CMDID_BASE+12)

//������ת��������Ϣ
#define CONF_CMDID_CHATMSGNOTIFY	(CONF_CMDID_BASE+112)

//�û����ʹ���״̬
#define CONF_CMDID_WNDSTATE			(CONF_CMDID_BASE+13)

//������ת������״̬
#define CONF_CMDID_WNDSTATENOTIFY	(CONF_CMDID_BASE+113)

//�����˷��Ϳ��پ�������
#define CONF_CMDID_SILENT			(CONF_CMDID_BASE+14)

//������ת�����پ�������
#define CONF_CMDID_SILENTNOTIFY		(CONF_CMDID_BASE+114)

//�����˷�����Ļ����
#define CONF_CMDID_MEETINGCHAR		(CONF_CMDID_BASE+15)

//������ת����Ļ��Ϣ
#define CONF_CMDID_MEETINGCHARNOTIFY (CONF_CMDID_BASE+115)

//�û������ļ��������û�
#define CONF_CMDID_SENDFILE			(CONF_CMDID_BASE+16)

//������֪ͨ�����û������ļ�
#define CONF_CMDID_SENDFILENOTIFY	(CONF_CMDID_BASE+116)

//�ͻ��˳�ʼ�����
#define CONF_CMDID_INITCOMPLETE		(CONF_CMDID_BASE+17)

//������֪ͨ���Ŷ����ڵȴ������˿���
#define CONF_CMDID_WAITOPENDOOR		(CONF_CMDID_BASE+117)

//����������֪ͨ��Ϣ,���ڷ�����㲥��Ϣ
#define CONF_CMDID_SYSMSG			(CONF_CMDID_BASE+118)

//���������û᳡����
#define CONF_CMDID_ROOMDATA			(CONF_CMDID_BASE+19)

//������֪ͨ���»᳡���ݣ����û���¼Ҳ�յ���֪ͨ
#define CONF_CMDID_ROOMDATANOTIFY	(CONF_CMDID_BASE+119)

//�����������ȡAV�ϳɲ���
#define CONF_CMDID_MIXCONFIG		(CONF_CMDID_BASE+20)

//���������ص�ǰAV�ϳɲ���
#define CONF_CMDID_MIXCONFIGINFO	(CONF_CMDID_BASE+120)

//����������AV�ϳɲ���
#define CONF_CMDID_SETMIXCONFIG		(CONF_CMDID_BASE+21)

//������������Ƶ��Ļ����
#define CONF_CMDID_SETOSDPARAM		(CONF_CMDID_BASE+22)

//������ת��������������Ƶ��Ļ����
#define CONF_CMDID_OSDPARAMNOTIFY	(CONF_CMDID_BASE+122)

//�����˴����������,����ͬʱ�������
#define CONF_CMDID_CREATEGROUP		(CONF_CMDID_BASE+23)

//�����������½����������Ϣ
#define CONF_CMDID_GROUPINFO		(CONF_CMDID_BASE+123)

//���û�����������
#define CONF_CMDID_ENTERGROUPREQ	(CONF_CMDID_BASE+24)

//֪ͨ�û�����������
#define CONF_CMDID_ENTERGROUPREP	(CONF_CMDID_BASE+124)

//�����˽����������
#define CONF_CMDID_CLOSEGROUP		(CONF_CMDID_BASE+25)

//���������ؽ������������Ϣ
#define CONF_CMDID_CLOSEGROUPNOTIFY	(CONF_CMDID_BASE+125)

//���û�����������
#define CONF_CMDID_ENTERMAINREQ		(CONF_CMDID_BASE+26)

//֪ͨ�û�����������
#define CONF_CMDID_ENTERMAINREP		(CONF_CMDID_BASE+126)

//�ͻ��޸Ļ���������
#define CONF_CMDID_MEETINGRENAMEREQ		(CONF_CMDID_BASE+27)
//֪ͨ�û��Ļ���������
#define CONF_CMDID_MEETINGRENAMEREP		(CONF_CMDID_BASE+127)

//��ת��Ϣ
#define CONF_CMDID_TRANSDATA		(CONF_CMDID_BASE+200)

/************************************************************************/
/*                          �ն���������                              */
/************************************************************************/
//6740-6799
#define CONF_CMDID_TERMINAL_BASE				(CONF_CMDID_BASE+240)

//��������
#define CONF_CMDID_TERMINAL_MAKECALL_REQ		(CONF_CMDID_TERMINAL_BASE+1)
//���з���
#define CONF_CMDID_TERMINAL_MAKECALL_REP		(CONF_CMDID_TERMINAL_BASE+2)

//�һ�����
#define CONF_CMDID_TERMINAL_HANGUP_REQ			(CONF_CMDID_TERMINAL_BASE+3)
//�һ�����
#define CONF_CMDID_TERMINAL_HANGUP_REP			(CONF_CMDID_TERMINAL_BASE+4)

//����״̬֪ͨ
#define CONF_CMDID_TERMINAL_CALLSTATE_NOTIFY	(CONF_CMDID_TERMINAL_BASE+5)

//��ȡ�û������б�
#define CONF_CMDID_TERMINAL_CALL_LIST_REQ		(CONF_CMDID_TERMINAL_BASE+6)

//�����û������б�
#define CONF_CMDID_TERMINAL_CALL_LIST_REP		(CONF_CMDID_TERMINAL_BASE+7)

#pragma pack()

#endif