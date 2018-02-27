#ifndef __PROTOCOL_ERROR_DEFINE_H
#define __PROTOCOL_ERROR_DEFINE_H

#define		WPROTOCOL_RESULT_SUCCESS			0X0000		//�ɹ�

#define		WPROTOCOL_RESULT_UNKNOWN			0x1001		//δ֪����
#define		WPROTOCOL_RESULT_EXCEPTION			0x1002		//�쳣����
#define		WPROTOCOL_RESULT_SERVERERROR		0X1003		//�������ڲ�����
#define		WPROTOCOL_RESULT_INVALIDSESSION		0X1004		//��Ч�ĻỰ
#define		WPROTOCOL_RESULT_USERNOTFOUND		0X1005		//�û�δ�ҵ�
#define		WPROTOCOL_RESULT_VERIFYFAILED		0X1006		//��֤ʧ��
#define		WPROTOCOL_RESULT_ACCESSDENIED		0X1007		//�û���Ȩ����
#define		WPROTOCOL_RESULT_INVALIDARG			0x1008		//��������
#define		WPROTOCOL_RESULT_NOWMAINTENANCE		0x1009		//ϵͳ����ά������ͣ����
#define		WPROTOCOL_RESULT_TOOACCESS			0x100A		//�����������࣬��ͣ����
#define		WPROTOCOL_RESULT_INVALIDVALUE		0x100B		//������Ч

#define		WPROTOCOL_RESULT_FILENOTFOUND		0X2001		//�ļ�δ�ҵ�
#define		WPROTOCOL_RESULT_LISTNOTFOUND		0X2002		//�ļ��б�δ�ҵ�
#define		WPROTOCOL_RESULT_LISTEXISTED		0X2003		//�ļ��б��Ѵ���
#define		WPROTOCOL_RESULT_CHANNELNOTFOUND	0X2004		//�ļ�����ͨ��������
#define		WPROTOCOL_RESULT_FILEUPLOADING		0X2005		//�ļ������ϴ��У�������ͬʱ�ϴ�һ���ļ�
#define		WPROTOCOL_RESULT_FILEOVERSIZE		0X2006		//�ļ���С�����޶�ֵ
#define		WPROTOCOL_RESULT_FILENOTUPLOADED	0X2007		//�����߻�δ�ϴ����ļ�
#define		WPROTOCOL_RESULT_FILEEXISTED		0X2008		//�ļ��Ѵ���

#define		WPROTOCOL_RESULT_PASSWORDERROR		0x2101		//�û��������
#define		WPROTOCOL_RESULT_ROOMNOTFOUND		0x2102		//����δ�ҵ�
#define		WPROTOCOL_RESULT_ROOMOVERFLOW		0x2103		//��������
#define		WPROTOCOL_RESULT_APPMISMATCH		0x2104		//Ӧ�����Ͳ�ƥ��
#define		WPROTOCOL_RESULT_SRVMISMATCH		0X2105		//��������ƥ��
#define		WPROTOCOL_RESULT_SRVNOTFOUND		0x2106		//δ�ҵ�ָ���ķ�����
#define		WPROTOCOL_RESULT_SRVOVERFLOW		0X2107		//����������Ա
#define		WPROTOCOL_RESULT_USEREXISTED		0x2108		//�û��Ѵ���
#define		WPROTOCOL_RESULT_NEEDROOMPASSWORD	0X2109		//��Ҫ���뷿������
#define		WPROTOCOL_RESULT_ROOMLOCKED			0X210A		//����������
#define		WPROTOCOL_RESULT_ROOMOVERTIME		0X210B		//�����ѹ���
#define		WPROTOCOL_RESULT_ROOMOFF			0X210C		//�����ѹر�
#define		WPROTOCOL_RESULT_DENYKNOCK			0X210D		//�����˾ܾ��û������������������
#define		WPROTOCOL_RESULT_MULTIDENYKNOCK		0X210E		//�û����������������ֹ������������
#define		WPROTOCOL_RESULT_SERVERCASFAILED	0X210F		//����������ʧ��
#define		WPROTOCOL_RESULT_SRVNOSTART			0x2110		//������δ����
#define		WPROTOCOL_RESULT_SRVSTOPED			0x2111		//��������ֹͣ
#define		WPROTOCOL_RESULT_NEEDPAYMENT		0x2112		//�����ѵ��ڻ����㣬�뼰ʱ����
#define		WPROTOCOL_RESULT_PRODUCTSRVSTOPED	0x2113		//�����Ĳ�Ʒ����ͣ��

#define		WPROTOCOL_RESULT_CHAIR_PWDERR           0x2114	    //��ϯ�������.
#define		WPROTOCOL_RESULT_ROOM_IDERR             0x2115      //�û����ҺŲ����ڣ����������롣
#define		WPROTOCOL_RESULT_LOGIN_NICKNAME      	0x2116		//���ʱ��ܾ���ֻ�������û������뷽ʽ��¼����
#define		WPROTOCOL_RESULT_CHAIR_OPEN_OPTION   	0x2117		//��ǰ���鲻����������ϯ��
#define		WPROTOCOL_RESULT_CHAIR_NOTOPENROOM 		0x2118		//��ϯδ��������

#define		WPROTOCOL_RESULT_INVITECODE_ERROR	 	0x2119		//���������
#define		WPROTOCOL_RESULT_INVITECODE_EXPIRES 	0x211A		//���������

#define		WPROTOCOL_RESULT_DISABLE_MOBILE_LOGIN 	0x211B		//��֧���ֻ��˵�¼

/************************************************************************/
/*                            �绰��������붨��                        */
/************************************************************************/
#define		WPROTOCOL_RESULT_NOT_ENOUGH_CALL_COMPANY	0x3001	// ��ҵʣ��绰����·������
#define		WPROTOCOL_RESULT_NOT_ENOUGH_CALL_GATEWAY	0x3002	// �绰����ʣ��绰����·������
#define		WPROTOCOL_RESULT_REPEATED_PHONE_CALL		0x3003	// �ظ��绰����
#define     WPROTOCOL_RESULT_NOT_ENOUGH_BNANCE_COMPANY	0x3004	// ��ҵ�˻�����

/************************************************************************/
/*                            ���ϵͳ�����붨��                        */
/************************************************************************/
#define		MONITORPROTOCOL_RESULT_WEB_QUERYADPTER_ERROR	0x9000		//��ѯ��������ַʧ��
#define		MONITORPROTOCOL_RESULT_WEB_UNKNOWOPERADDR_ERROR	0x9001		//δ֪��������������
#define		MONITORPROTOCOL_RESULT_WEB_ADPTERUPDATE_ERROR	0x9002		//��������ַ����ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_ADDRMAP_ERROR		0x9003		//�����ַӳ�����ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_SRVRESET_ERRROR		0x9004		//����������ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_SERVICERESET_NOFOUND	0x9005		//ҵ��û���ҵ�
#define		MONITORPROTOCOL_RESULT_WEB_SERVICERESET_ERRROR	0x9006		//ҵ������ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_QUERYREALTIME_ERRROR	0x9007		//��ѯ����������״̬ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_QUERYNETTYPE_ERRROR	0x9009		//��ѯ������������������ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_LICENSEACTIVATED_ERRROR	0x900a	//��Ȩ�ļ�����ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_CREATEREGFILE_ERRROR	0x900b		//����ע���ļ�ʧ��
#define		MONITORPROTOCOL_RESULT_WEB_SETNETTYPE_ERROR		0x900c		//���÷�����������������ʧ��

#endif