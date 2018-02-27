#ifndef __CASCADE_PROTOCOL_H
#define __CASCADE_PROTOCOL_H

#define CASCADE_CMDID_BASE				6800		//����Э������ID��ʼֵ

#pragma pack(1)

//���ϼ����������뽨������ͨ��
#define CASCADE_CMDID_SERVERCASREQ				(CASCADE_CMDID_BASE)

//���������¼����뽨������ͨ���Ļ�Ӧ
#define CASCADE_CMDID_SERVERCASREP			    (CASCADE_CMDID_BASE+1)

//���ϼ�����������·����Ϣ
#define CASCADE_CMDID_SERVERCASROUTEREPORT		(CASCADE_CMDID_BASE+2)

//������֮���ü���ͨ��ת������
#define CASCADE_CMDID_SERVERCASDATA		        (CASCADE_CMDID_BASE+3)

#pragma pack()

#endif