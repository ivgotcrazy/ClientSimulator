#ifndef __AVQOS_TRANSFER_CONTROL_H
#define __AVQOS_TRANSFER_CONTROL_H

#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef QOS_MEDIATYPE_AUDIO
#define	QOS_MEDIATYPE_AUDIO			0X01	//音频数据
#define QOS_MEDIATYPE_VIDEO			0X02	//视频数据
#endif

	typedef struct{

		BOOL		bOverload;						
		FS_UINT32		dwBitrate;						//kbps
		FS_UINT32		dwPacketLostRate;				//%
		FS_UINT32		dwMaxPacketLostDuaration;		//packet count	
		FS_UINT32		dwFECPacketLostRate;			//%
		FS_UINT32		dwBackCount;
		FS_UINT32		dwBackOverloadRate;				//%
		FS_UINT32		dwBackPacketAvgLostRate;		//%
		FS_UINT32		dwBackPacketAvgLostDuration;	//packet count
		FS_UINT32		dwBackFECPacketAvgLostRate;		//%

	}AVQosState;

	//
	//IAVQosMsgCallback，以回调接口函数中不应加锁，以免引起死锁
	//
	DECLARE_INTERFACE( IAVQosMsgCallback )
	{
		//dwToID用于指定发送目的地
		STDMETHOD( OnQosData )( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwToID,FS_UINT32 dwToParam ) PURE;

		//dwToID用于指定发送目的地
		STDMETHOD( OnDataUnit )( THIS_ FS_INT32 nMediaType,PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwToID,FS_UINT32 dwToParam ) PURE;
	};

	//
	//IAVQosStateCallback
	//
	DECLARE_INTERFACE( IAVQosStateCallback )
	{
		STDMETHOD( OnQosState )( THIS_ AVQosState* pState,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;

		STDMETHOD( OnVideoWndSize )( THIS_ FS_UINT16 wWndWidth,FS_UINT16 wWndHeight,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;
	};

	//
	//IAVQosSampleCallback
	//
	DECLARE_INTERFACE( IAVQosSampleCallback )
	{
		STDMETHOD( OnAudioSample ) ( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;	
		
		STDMETHOD( OnVideoSample ) ( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;	
	};

	//
	//IAVQosClientS
	//
	DECLARE_INTERFACE( IAVQosClientS )
	{
		STDMETHOD( SetCallback )( THIS_ IAVQosMsgCallback* pMsgCallback,IAVQosStateCallback* pStateCallback ) PURE;

		STDMETHOD( WriteAudioSample ) ( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwDuration ) PURE;	

		STDMETHOD( WriteVideoSample ) ( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,BOOL bKeyFrame ) PURE;	

		STDMETHOD( WriteQosData )( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;

		STDMETHOD( GetQosState )( THIS_ AVQosState *pState ) PURE;

		STDMETHOD( SetFEC )( THIS_ BOOL bAutoR,FS_INT32 nK,FS_INT32 nR ) PURE;
	};

	//
	//IAVQosClientR
	//
	DECLARE_INTERFACE( IAVQosClientR )
	{
		STDMETHOD( SetCallback )( THIS_ IAVQosMsgCallback* pMsgCallback,IAVQosSampleCallback* pSampleCallback ) PURE;

		STDMETHOD( WriteDataUnit )( THIS_ PBYTE pbData,FS_UINT32 dwDataLen ) PURE;

		STDMETHOD( WriteQosData )( THIS_ PBYTE pbData,FS_UINT32 dwDataLen ) PURE;

		STDMETHOD( GetQosState )( THIS_ AVQosState *pState ) PURE;

		STDMETHOD( GetProperty )( THIS_ FS_INT32 *pMediaType,FS_UINT32* pdwFromID,FS_UINT32* pdwFromParam ) PURE;

		STDMETHOD( SetVideoWndSize )( THIS_ FS_UINT16 wWndWidth,FS_UINT16 wWndHeight ) PURE;
	};

	//IAVQosServer
	//
	DECLARE_INTERFACE( IAVQosServer )
	{
		STDMETHOD( SetCallback )( THIS_ IAVQosMsgCallback* pMsgCallback ) PURE;
		
		STDMETHOD( WriteDataUnit )( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;
		
		STDMETHOD( WriteQosData )( THIS_ PBYTE pbData,FS_UINT32 dwDataLen,FS_UINT32 dwFromID,FS_UINT32 dwFromParam ) PURE;		

		STDMETHOD( AddReceiver )( THIS_ FS_UINT32 dwToID,FS_UINT32 dwToParam ) PURE;
 
		STDMETHOD( RemoveReceiver )( THIS_ FS_UINT32 dwToID,FS_UINT32 dwToParam ) PURE;

		STDMETHOD( PauseReceiver )( THIS_ FS_UINT32 dwToID,FS_UINT32 dwToParam,BOOL bPause ) PURE;

        STDMETHOD( GetReceiverQosState )( THIS_ AVQosState *pState,FS_UINT32 dwToID,FS_UINT32 dwToParam ) PURE;

        STDMETHOD( GetSenderQosState )( THIS_ AVQosState *pState ) PURE;
	};
	

#ifdef __cplusplus
}
#endif

BOOL            WINAPI  AVQosInit( LPUNKNOWN pFactory,HMODULE hModule,BOOL bServer );

IAVQosClientS*	WINAPI  AVQosCreateClientS( FS_INT32 nMediaType,FS_UINT32 dwToID,FS_UINT32 dwToParam );

void			WINAPI AVQosDestroyClientS( IAVQosClientS* pQosClientS );

IAVQosClientR*	WINAPI AVQosCreateClientR( FS_INT32 nMediaType,FS_UINT32 dwFromID,FS_UINT32 dwFromParam );

void			WINAPI AVQosDestroyClientR( IAVQosClientR* pQosClientR );

IAVQosServer*	WINAPI AVQosCreateServer( FS_INT32 nMediaType );

void			WINAPI AVQosDestroyServer( IAVQosServer* pQosServer );

void			WINAPI AVQosRelease();

#endif
