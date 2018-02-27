#ifndef __AVPLAY_SYNCTIME_H__
#define __AVPLAY_SYNCTIME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wtimefunction.h"
#include "wlock.h"
#include "IPlaySyncTime.h"

using namespace WBASELIB;

#define SYNC_TIMEOUT_VALUE			2000

class CAVPlaySyncTime:public IPlaySyncTime
{
public:
	CAVPlaySyncTime()
	{
		ResetTimeStamp();
	};
	~CAVPlaySyncTime()
	{
	}
public:
	STDMETHODIMP SetTimeStamp( DWORD dwTimeStamp )
	{
		m_lock.Lock();
		m_dwSyncTimeStamp = dwTimeStamp;
		m_dwSyncLocalTime = timeGetTime();
		m_lock.UnLock();
		return S_OK;
	};
	STDMETHODIMP_(DWORD) GetTimeStamp( )
	{
		DWORD dwCurTime = timeGetTime();
		m_lock.Lock();
		DWORD dwTimeStamp = (dwCurTime-m_dwSyncLocalTime)*m_dbRate+m_dwSyncTimeStamp;
		m_lock.UnLock();
		return dwTimeStamp;
	};
	STDMETHODIMP SetPlayRate( double dbRate ){ if( dbRate != m_dbRate ){ SetTimeStamp( GetTimeStamp());m_dbRate = dbRate;} return S_OK;};
	STDMETHODIMP_( double )GetPlayRate( ){ return m_dbRate;};
	STDMETHODIMP_( DWORD ) GetLastSyncTime(){ return m_dwSyncLocalTime;};
	STDMETHODIMP ResetTimeStamp()
	{ 	
		m_dwSyncTimeStamp = 0;
		m_dwSyncLocalTime = 0;
		m_dbRate = 1.0;
		return S_OK;
	};

protected:
	DWORD	m_dwSyncTimeStamp;
	DWORD	m_dwSyncLocalTime;
	double  m_dbRate;
	WLock	m_lock;
};

#endif