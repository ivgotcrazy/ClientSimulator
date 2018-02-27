#ifndef __IC2CTRANSFER_H
#define __IC2CTRANSFER_H

#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    #define C2C_RESOURCE_AUDIO          0x01    //音频
    #define C2C_RESOURCE_VIDEO          0x02    //视频

	// C2CTransfer Component's GUID
    // {3FD5A3C1-BC50-421b-815E-62E42172C324}
    DEFINE_GUID(CLSID_C2CTransfer, 
        0x3fd5a3c1, 0xbc50, 0x421b, 0x81, 0x5e, 0x62, 0xe4, 0x21, 0x72, 0xc3, 0x24);

	// IC2CTransfer Interface's GUID
    // {82B7928F-D1B3-4ed1-B423-EC9DACB9DB93}
    DEFINE_GUID(IID_IC2CTransfer, 
        0x82b7928f, 0xd1b3, 0x4ed1, 0xb4, 0x23, 0xec, 0x9d, 0xac, 0xb9, 0xdb, 0x93);

	//
	//IC2CTransferNotify
	//
	DECLARE_INTERFACE( IC2CTransferNotify )
	{
        //通知是否从C2C网络接收数据
        STDMETHOD( OnRecvFromC2C ) ( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,BOOL bRecvFromC2C ) PURE;	
        //通知是否向C2C网络发送数据
        STDMETHOD( OnSendToC2C ) ( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,BOOL bSendToC2C ) PURE;	       
		//C2C网络接收的数据回调
		STDMETHOD( OnResData ) ( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,PBYTE pbData,FS_UINT16 wDataLen ) PURE;	
	};

	//----------------------------------------------------------------------------
	// IC2CTransfer
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IC2CTransfer, IUnknown)
	{
		//加入C2C组播网络
		STDMETHOD( JoinC2C )( THIS_ const GUID& guidGroup,FS_UINT32 dwUserID,const CHAR* szMCIP,FS_UINT16 wMCPort,IC2CTransferNotify *pNotify ) PURE;
		//离开
		STDMETHOD( LeaveC2C )( THIS_ ) PURE;
		//添加资源
		STDMETHOD( AddResource )( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID ) PURE;
		//删除资源
		STDMETHOD( RemoveResource)( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID ) PURE;
        //向C2C网络发送数据
		STDMETHOD( WriteResData )( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,PBYTE pbData,FS_UINT16 wDataLen ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif