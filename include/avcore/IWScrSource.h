#ifndef __IWSCREEN_SOURCE_H
#define __IWSCREEN_SOURCE_H

#include "wbasetype.h"
#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	// WScrSource Component's GUID
	// {6853EE04-5020-499a-AEEA-5E54FB37180C}
	DEFINE_GUID(CLSID_WScrSource, 
		0x6853ee04, 0x5020, 0x499a, 0xae, 0xea, 0x5e, 0x54, 0xfb, 0x37, 0x18, 0xc);
	
	// IWScrSource Interface's GUID
	// {8C4DC883-6E6C-4fb2-B1AD-C289DD784968}
	DEFINE_GUID(IID_IWScrSource, 
		0x8c4dc883, 0x6e6c, 0x4fb2, 0xb1, 0xad, 0xc2, 0x89, 0xdd, 0x78, 0x49, 0x68);
	
	typedef struct{

		int		nCapLeft;
		int		nCapTop;
		int		nCapWidth;
		int		nCapHeight;
		int		nFrameRate;
	}ScrCapParam;

	typedef struct{

		CHAR	szRemoteIP[32];
		FS_UINT16	wRemotePort;
	}ScrConParam;

#define		WSCRSOURCE_EVENT_CONNECTSUCCESS				0X1001		//连接成功 wParam = Event,lParam = FileID
#define		WSCRSOURCE_EVENT_CONNECTFAILED				0X1002		//连接失败
#define		WSCRSOURCE_EVENT_DISCONNECT					0X1003		//连接断开
#define		WSCRSOURCE_EVENT_EXCEPTION					0X1004		//发生异常错误


	//----------------------------------------------------------------------------
	// IWScrSource
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IWScrSource, IUnknown)
	{
		STDMETHOD( Connect )( THIS_ ScrConParam* pConParam,WBASE_NOTIFY* pNotify ) PURE;

		STDMETHOD( StartCapture )( THIS_ ScrCapParam *pCapParam ) PURE;

		STDMETHOD( StopCapture )( THIS_ ) PURE;

		STDMETHOD( SetParam )( THIS_ ScrCapParam *pCapParam ) PURE;


		STDMETHOD( DisConnect )( THIS_ ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif