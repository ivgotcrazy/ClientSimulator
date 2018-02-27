#ifndef __CASCADE_PROTOCOL_H
#define __CASCADE_PROTOCOL_H

#define CASCADE_CMDID_BASE				6800		//级联协议命令ID起始值

#pragma pack(1)

//向上级服务器申请建立级联通道
#define CASCADE_CMDID_SERVERCASREQ				(CASCADE_CMDID_BASE)

//服务器对下级申请建立级联通道的回应
#define CASCADE_CMDID_SERVERCASREP			    (CASCADE_CMDID_BASE+1)

//向上级服务器报告路由信息
#define CASCADE_CMDID_SERVERCASROUTEREPORT		(CASCADE_CMDID_BASE+2)

//服务器之间用级联通道转发数据
#define CASCADE_CMDID_SERVERCASDATA		        (CASCADE_CMDID_BASE+3)

#pragma pack()

#endif