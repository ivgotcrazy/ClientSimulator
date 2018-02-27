// MemoryAllocator.h: interface for the WMemoryAllocator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYALLOCATOR_H__BC423488_4AB5_4CEF_806E_5249E2160436__INCLUDED_)
#define AFX_MEMORYALLOCATOR_H__BC423488_4AB5_4CEF_806E_5249E2160436__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "list"
#include "wbasetype.h"
#include "wbaseobject.h"
#include "wlog.h"
#include "math.h"

namespace WBASELIB{

	class WBuffer;
	
	typedef std::list< PBYTE >						MemoryList;
	typedef std::list<WBuffer *>					SSBufferList;
	
	class WMemoryAllocator  
	{
		friend class WBuffer;
	public:
		WMemoryAllocator( );
		virtual ~WMemoryAllocator();
		
	public:
		VOID		Clear();
		WBuffer *	Alloc( FS_UINT32 dwSize );
		BOOL		Init( FS_UINT32 dwCount,FS_UINT32 dwSize,FS_UINT32 cbAlign = 256,FS_UINT32 dwMaxSize = 256*1024,FS_UINT32 dwIncreCount = 10 );
		BOOL		Init2(FS_UINT32 cbAlign = 256,FS_UINT32 dwMaxSize = 256*1024,FS_UINT32 dwIncreCount = 10 );
		BOOL		BatchAlloc( FS_UINT32 dwSize,FS_UINT32 dwCount );
		
	protected:
		VOID		Free( WBuffer *pBuffer );
		
		inline FS_UINT32 SIZE2INDEX( FS_UINT32 dwSize)
		{
			FS_UINT32 dwIndex = (FS_UINT32)(log((double)((dwSize+(m_cbAlign-1))>>m_dwShift))/m_dbLog2);
			if( m_pBufferList[dwIndex].dwSize < dwSize ) ++ dwIndex;
			return dwIndex;
		};
		
		FS_UINT32               m_cbAlign;
		FS_UINT32               m_dwShift;
		FS_UINT32				m_dwMaxSize;
		FS_UINT32				m_dwIncreCount;
		double				m_dbLog2;
		
		struct BufferItem{
			WLock				lock;
			WBuffer*			pBuffer;
			FS_UINT32				dwSize;
		};
		BufferItem*			m_pBufferList;
		FS_UINT32				m_dwArraySize;
		
		FS_UINT32				m_dwBatchAllocCount;
		FS_UINT32				m_dwTotalAllocMemorySize;
		FS_UINT32				m_dwTotalBufferObjectCount;
		FS_UINT32				m_nFreeMemorySize;
		FS_UINT32				m_nFreeBufferObjectCount;
		
		WLock		m_TotalLock;
		MemoryList	m_lsTotalMemory;
		SSBufferList	m_lsTotalBuffer;	
	};
	
	class WBuffer:public WBaseObject  
	{
		friend class WMemoryAllocator;
	public:
		WBuffer( ):
		  m_pNext( NULL ),
		  m_pPrev( NULL ),
		  m_pbBuffer( NULL ),
		  m_dwSize( 0 ),
		  m_dwLength( 0 ),
		  m_dwUserData( 0 ),
		  m_pInternalNext( NULL ),
		  m_pInternalPrev( NULL ),
		  m_pAlloctor( NULL )
		  {};
		  virtual ~WBuffer(){};
		  
	public:
        FS_UINT GetUserData() { return m_dwUserData; };
        VOID  SetUserData(FS_UINT dwUserData) { m_dwUserData = dwUserData; };
		
		VOID  SetLength( FS_UINT32 dwLength ){ m_dwLength = dwLength;};
		FS_UINT32 GetLength(){ return m_dwLength;};
		
		FS_UINT32 GetBufferSize(){ return m_dwSize;};
		PBYTE GetBuffer(){ return m_pbBuffer;};
		
		BOOL  WriteData( PBYTE pbData,FS_UINT32 dwLength )
		{
			if( m_pbBuffer && m_dwSize >= dwLength ){
				memcpy( m_pbBuffer,pbData,dwLength );
				m_dwLength = dwLength;
				return TRUE;
			}
			return FALSE;
		};
		BOOL Append( PBYTE pbData,FS_UINT32 dwLength )
		{
			if( m_pbBuffer && dwLength+m_dwLength <= m_dwSize ){
				memcpy( m_pbBuffer+m_dwLength,pbData,dwLength );
				m_dwLength += dwLength;
				return TRUE;
			}
			return FALSE;
		}
		virtual FS_INT32 Release()
		{
#ifdef _FS_OS_WIN
			FS_UINT32 lRef = (FS_UINT32)InterlockedDecrement( (LONG*)&m_lRef );
#else
			m_lockRef.Lock();
			FS_INT32 lRef = --m_lRef;
			m_lockRef.UnLock();
#endif
			if( 0 == lRef ){
				m_dwLength = 0;
				m_dwUserData = 0;
				m_pAlloctor->Free( this );
			}
			return (FS_INT32)(lRef);
		}
		WBuffer*	m_pNext;
		WBuffer*  m_pPrev;
		
	private:
		PBYTE		m_pbBuffer;
		FS_UINT32       m_dwSize;
		FS_UINT32	    m_dwLength;
        FS_UINT       m_dwUserData;
		
		WBuffer*	m_pInternalNext;
		WBuffer*  m_pInternalPrev;
		WMemoryAllocator *m_pAlloctor;
	};
}

#endif // !defined(AFX_MEMORYALLOCATOR_H__BC423488_4AB5_4CEF_806E_5249E2160436__INCLUDED_)
