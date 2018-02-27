#ifndef __IC2CTRANSFER_H
#define __IC2CTRANSFER_H

#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    #define C2C_RESOURCE_AUDIO          0x01    //��Ƶ
    #define C2C_RESOURCE_VIDEO          0x02    //��Ƶ

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
        //֪ͨ�Ƿ��C2C�����������
        STDMETHOD( OnRecvFromC2C ) ( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,BOOL bRecvFromC2C ) PURE;	
        //֪ͨ�Ƿ���C2C���緢������
        STDMETHOD( OnSendToC2C ) ( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,BOOL bSendToC2C ) PURE;	       
		//C2C������յ����ݻص�
		STDMETHOD( OnResData ) ( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,PBYTE pbData,FS_UINT16 wDataLen ) PURE;	
	};

	//----------------------------------------------------------------------------
	// IC2CTransfer
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IC2CTransfer, IUnknown)
	{
		//����C2C�鲥����
		STDMETHOD( JoinC2C )( THIS_ const GUID& guidGroup,FS_UINT32 dwUserID,const CHAR* szMCIP,FS_UINT16 wMCPort,IC2CTransferNotify *pNotify ) PURE;
		//�뿪
		STDMETHOD( LeaveC2C )( THIS_ ) PURE;
		//�����Դ
		STDMETHOD( AddResource )( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID ) PURE;
		//ɾ����Դ
		STDMETHOD( RemoveResource)( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID ) PURE;
        //��C2C���緢������
		STDMETHOD( WriteResData )( THIS_ FS_UINT32 dwResUserID,BYTE bResType,BYTE bResID,PBYTE pbData,FS_UINT16 wDataLen ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif