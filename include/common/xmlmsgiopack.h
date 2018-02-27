#ifndef __WXML_PROTOCOL_MSG_IOPACK_H
#define __WXML_PROTOCOL_MSG_IOPACK_H

#include "ibasecomponent.h"
#include "isessionmanager.h"
#include "wlock.h"
#include "zlib.h"
#include "tinyxml.h"
#include "xmlprotocolparser.h"
#include "macros.h"

using namespace WBASELIB;

#define XMLMSG_PACKTYPE_NONE		0x00
#define XMLMSG_PACKTYPE_ZLIB		0x01

#define ZLIB_MINPACKSIZE			256

#define XMLMSG_BUFFERSIZE			(64*1024)

class CXmlMsgIOPack
{
public:
	CXmlMsgIOPack()
	{
		m_pSessionManager = NULL;
		m_pbOutBuffer = NULL;
		m_pbInBuffer = NULL;
		m_nPackType = XMLMSG_PACKTYPE_NONE;
	};
	~CXmlMsgIOPack(){ Release();};
public:
    BOOL	Init(ISessionManager2 *pSessionManager, FS_INT32 nPackType = XMLMSG_PACKTYPE_ZLIB)
	{
		if( NULL == pSessionManager )
			return FALSE;		
		m_pSessionManager = pSessionManager;
		m_StreamOut.reserve( XMLMSG_BUFFERSIZE );
		if( nPackType == XMLMSG_PACKTYPE_ZLIB ){

			if( NULL == m_pbOutBuffer )
				m_pbOutBuffer = new BYTE[XMLMSG_BUFFERSIZE];
			if( NULL == m_pbInBuffer )
				m_pbInBuffer = new BYTE[XMLMSG_BUFFERSIZE];			
			if( NULL == m_pbInBuffer || NULL == m_pbOutBuffer )
				return FALSE;
			ZeroMemory( m_pbInBuffer,XMLMSG_BUFFERSIZE );
			ZeroMemory( m_pbOutBuffer,XMLMSG_BUFFERSIZE );
			m_nPackType = nPackType;
		}
		return TRUE;
	};
	void	Release()
	{
		SAFE_ARRAYDELETE( m_pbInBuffer );
		SAFE_ARRAYDELETE( m_pbOutBuffer );
	};
	ISessionManager2*	GetSessionManager(){ return m_pSessionManager;};

	void	Lock(){ m_lock.Lock();};
	void	UnLock(){ m_lock.UnLock();};

	BOOL	Pack( PBYTE pbIn,FS_UINT32 dwDataLen,PBYTE& pbOut,FS_UINT32& dwOutLen )
	{
		if( dwDataLen >= XMLMSG_BUFFERSIZE )
			return FALSE;

		BOOL bResult = FALSE;

		if( m_nPackType == XMLMSG_PACKTYPE_ZLIB && m_pbOutBuffer && dwDataLen > ZLIB_MINPACKSIZE ){
			uLongf uOutLen = XMLMSG_BUFFERSIZE-1;
			if( compress( m_pbOutBuffer+1,&uOutLen,pbIn,dwDataLen ) == Z_OK ){

				m_pbOutBuffer[0] = XMLMSG_PACKTYPE_ZLIB;
				pbOut = m_pbOutBuffer;
				dwOutLen = uOutLen+1;
				bResult = TRUE;
			}
		}
		
		if( !bResult ){
			CopyMemory( m_pbOutBuffer+1,pbIn,dwDataLen );
			m_pbOutBuffer[0] = XMLMSG_PACKTYPE_NONE;
			pbOut = m_pbOutBuffer;
			dwOutLen = dwDataLen+1;
			bResult = TRUE;
		}
		return bResult;		
	};

	BOOL	Pack( TiXmlElement& element,PBYTE& pbOut,FS_UINT32& dwOutLen )
	{
		BOOL bResult = FALSE;
		m_StreamOut.reset();
		m_StreamOut<<element;
		
		return Pack( (PBYTE)m_StreamOut.c_str(),m_StreamOut.length(),pbOut,dwOutLen );
	};

	BOOL	UnPack( PBYTE pbIn,FS_UINT32 dwDataLen,PBYTE& pbOut,FS_UINT32& dwOutLen )
	{
		if( NULL == pbIn || dwDataLen < 2 )
			return FALSE;
		
		BYTE bPackType = pbIn[0];
		if( bPackType == XMLMSG_PACKTYPE_ZLIB && m_pbInBuffer ){
			uLongf uOutLen = XMLMSG_BUFFERSIZE;
			if( uncompress( m_pbInBuffer,&uOutLen,pbIn+1,dwDataLen-1 ) != Z_OK ){
				return FALSE;
			}
			if( uOutLen < XMLMSG_BUFFERSIZE )
				m_pbInBuffer[uOutLen] = 0;
			pbOut = m_pbInBuffer;
			dwOutLen = uOutLen;
		}else if( bPackType == XMLMSG_PACKTYPE_NONE){

			CopyMemory( m_pbInBuffer,pbIn+1,dwDataLen-1 );
			pbOut = m_pbInBuffer;
			dwOutLen = dwDataLen-1;
			if( dwOutLen < XMLMSG_BUFFERSIZE )
				pbOut[dwOutLen] = 0;
		}else{
			return FALSE;
		}
		return TRUE;
	};
    HRESULT	Output(TiXmlElement& element, FS_UINT16 wSessionID)
	{
		HRESULT hr = E_FAIL;
		PBYTE pbOut = NULL;
		FS_UINT32 dwOutLen = 0;
		m_lock.Lock();
		if( Pack( element,pbOut,dwOutLen )){
			hr = m_pSessionManager->Send( wSessionID,pbOut,dwOutLen );
		}
		m_lock.UnLock();
		return hr;
	};
	BOOL	Input( PBYTE pbIn,FS_UINT32 dwDataLen,TiXmlElement& element )
	{
		BOOL bResult = FALSE;
		PBYTE pbOut = NULL;
		FS_UINT32 dwOutLen = 0;
		m_lock.Lock();
		if( UnPack( pbIn,dwDataLen,pbOut,dwOutLen )){
			bResult = WXmlParser_LoadCommand( element,(CHAR*)pbOut,dwOutLen ) != NULL;
		}
		m_lock.UnLock();
		return bResult;
	};
protected:
	ISessionManager2*	m_pSessionManager;
	WLock			m_lock;
	TIXML_OSTREAM	m_StreamOut; 
	PBYTE			m_pbOutBuffer;
	PBYTE			m_pbInBuffer;
    FS_INT32		m_nPackType;
};

#endif