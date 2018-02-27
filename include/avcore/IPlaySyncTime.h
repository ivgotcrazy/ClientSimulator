#ifndef __IPLAY_SYNCTIME_H
#define __IPLAY_SYNCTIME_H

#include "wcombase.h"

#ifdef __cplusplus
extern "C" {
#endif
		
	// {96BEFA63-F721-465a-AD48-32A46391BE69}
	DEFINE_GUID( IID_IPlaySyncTime, 
		0x96befa63, 0xf721, 0x465a, 0xad, 0x48, 0x32, 0xa4, 0x63, 0x91, 0xbe, 0x69);
	
	//----------------------------------------------------------------------------
	// IPlaySyncTime
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE(IPlaySyncTime )
	{
		STDMETHOD( SetTimeStamp )( THIS_ DWORD dwTimeStamp ) PURE;
		STDMETHOD_( DWORD,GetTimeStamp )( THIS_ ) PURE;
		STDMETHOD( SetPlayRate )( THIS_ double dbRate ) PURE;
		STDMETHOD_(double,GetPlayRate)( THIS_ ) PURE;
		STDMETHOD_( DWORD,GetLastSyncTime )( THIS_ ) PURE;
		STDMETHOD( ResetTimeStamp )( THIS_ ) PURE;
	};
	
#ifdef __cplusplus
}
#endif

#endif