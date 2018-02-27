#ifndef __DB_PROTOCOL_H
#define __DB_PROTOCOL_H

#pragma pack(1)

#define	DB_PROTOCOL_VERSION			0X00		//数据库访问协议版本

#define DB_CMDID_BASE				6900		//数据库访问协议命令ID起始值

//
//命令字定义
//采用网络字节序
//

#define	DB_CMDID_CONNECTREQ			(DB_CMDID_BASE)		//请求连接数据库网关
typedef struct{

	WORD	wCmdID;
	WORD	wReserved;
	//User 
	//Password
	//DBName
}DB_CMD_CONNECTREQ;

#define DB_CMDID_CONNECTREP			(DB_CMDID_BASE+10)	//连接数据库网关应答
typedef struct{

	WORD	wCmdID;
	WORD	wResult;
}DB_CMD_CONNECTREP;

#define DB_CMDID_DISCONNECTREQ		(DB_CMDID_BASE+1)	//请求断开连接
typedef struct{

	WORD	wCmdID;
}DB_CMD_DISCONNECTREQ;

#define DB_CMDID_DISCONNECTREP		(DB_CMDID_BASE+11)	//断开连接应答
typedef struct{

	WORD	wCmdID;
}DB_CMD_DISCONNECTREP;

#define DB_CMDID_QUERYREQ			(DB_CMDID_BASE+2)	//数据库查询请求
typedef struct{

	WORD	wCmdID;
	BYTE	bGetResult;				//是否需要获取查询结果
	BYTE	bMultiResult;			//是否返回多结果集
	WORD	wSeqNum;				//请求序列号
	WORD	wReserved;
	//Query String
}DB_CMD_QUERYREQ;

#define DB_CMDID_QUERYREP			(DB_CMDID_BASE+12)	//数据库查询返回
typedef struct{

	WORD	wCmdID;
	WORD	wResult;
	WORD	wSeqnum;
	BYTE	bHasMoreData;			//是否还有数据要返回
	BYTE	bReserved;
	//Data
}DB_CMD_QUERYREP;

typedef struct{
	WORD	wBlockLen;				//数据块长度
	WORD	wRecordCount;			//记录个数
	BYTE	bResultSeqnum;			//当前结果集编号,从0开始
	BYTE	bFieldCount;			//当前结果集字段数
	//Record Data
	//每一个字段数据以\0结尾
}ResultHeader;						//结果集数据头

#pragma pack()

#endif
