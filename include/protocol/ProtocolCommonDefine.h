#ifndef __PROTOCOL_COMMON_DEFINE_H
#define __PROTOCOL_COMMON_DEFINE_H

//�û�����
#define     USER_TYPE_UNREGISTER			0
#define     USER_TYPE_REGISTER				1

//
//�û���¼���û������Ͷ���
//
#define		LOGINNAME_TYPE_ANONYMOUS	0X00	//�����û�
#define		LOGINNAME_TYPE_USERNAME		0x01	//�û���
#define		LOGINNAME_TYPE_EMAIL		0X02	//E-MAIL
#define		LOGINNAME_TYPE_TELPHONE		0X03	//�绰����

//
//�û�Ȩ�޶���
//
#define		USERRIGHT_CHAIR				0X03	//������
#define		USERRIGHT_ATTENDER			0X02	//������
#define		USERRIGHT_LISTENER			0X01	//������

#define     USERRIGHT_COUNT             0X04    //Ȩ�޸���(����0x00δ��ʼ��)

//
//����ģʽ����
//
#define		ROOMMODE_FREE				0X00	//����ģʽ
#define		ROOMMODE_CONTROL			0x01	//����ģʽ

//
//��������֤ģʽ����
//
#define		ROOMVERIFY_MODE_USERPASSWORD	0X01	//�û���������֤
#define		ROOMVERIFY_MODE_ROOMPASSWORD	0X02	//������������֤
#define		ROOMVERIFY_MODE_ANONYMOUS		0X03	//����������½

//
//�ն�����
//
#define		TERMINAL_DESKTOP				0X01	//�����ն�
#define		TERMINAL_HARD					0X02	//Ӳ���ն�
#define		TERMINAL_MOBILE					0X03	//�ƶ��ն�
#define     TERMINAL_TEL                    0x04    //�绰�ն�
#define     TERMINAL_RECORD                 0x05    //¼���ն�

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