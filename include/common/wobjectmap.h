#ifndef __WOBJECT_MAP_H
#define __WOBJECT_MAP_H

#pragma   warning(disable:4786)

#include "unordered_map"
#include "wlock.h"
#include "wbaseobject.h"

using namespace WBASELIB;

template<class TYPE,class KEY = FS_UINT32>
class WObjectMap
{
public:

	typedef WElementAllocator<TYPE>		MultiObjectAllocator;
	typedef std::unordered_map<KEY,TYPE*>	MultiObjectMap;
	typedef typename MultiObjectMap::iterator	MultiObjectItor;

public:	
	WObjectMap(){}	
	virtual ~WObjectMap(){}	
public:
	
	TYPE*	NewMultiObj(KEY dwObjID,FS_UINT32 dwParam = 0)
	{
		TYPE* obj = NULL;
		
		m_lock.Lock();
		
		obj = m_ObjAllocator.Alloc();	
		if(obj != NULL)
		{
			m_mapObject.insert(typename MultiObjectMap::value_type(dwObjID, obj));
		}
		m_lock.UnLock();
		
		return obj;
	}
	
	TYPE*	FindMultiObjByID(KEY dwObjID)
	{
		TYPE* obj = NULL;
		MultiObjectItor itor;
		
		m_lock.Lock();		
		itor = m_mapObject.find(dwObjID);
		if (itor != m_mapObject.end())
		{
			obj= (*itor).second;
		}
		m_lock.UnLock();
		
		return obj;
	}
	
	void	DestroyMultiObj(KEY dwObjID)
	{
		m_lock.Lock();
		
		MultiObjectItor itor = m_mapObject.find(dwObjID);
		
		if(itor != m_mapObject.end())
		{
			TYPE* obj = (*itor).second;
			if(obj)
			{
				m_ObjAllocator.Free(obj);		
				obj = NULL;
			}
			m_mapObject.erase(itor);
		}
		m_lock.UnLock();
	}
	
	void	DestroyAllMultiObj()
	{
		MultiObjectItor itor;		
		m_lock.Lock();		
		for (itor = m_mapObject.begin() ; itor != m_mapObject.end() ; itor++)
		{
			TYPE* obj = (*itor).second;
			if (obj)
			{
				m_ObjAllocator.Free(obj);		
				obj = NULL;
			}
		}
		m_mapObject.clear();
		m_lock.UnLock();	
	}
	
	FS_UINT32	GetMultiObjCount()
	{
		FS_UINT32 tmp;
		m_lock.Lock();
		tmp = m_mapObject.size();
		m_lock.UnLock();
		return tmp;
	}

public:	
	//µü´ú²éÑ¯
	void TryLock()
	{
		m_lock.Lock();
	}
	
	void UnTryLock()
	{
		m_lock.UnLock();
	}
	
	void GetFirstPosData(MultiObjectItor& itor,TYPE*& obj)
	{
		itor = m_mapObject.begin();
		if (itor == m_mapObject.end())
			obj = NULL;
		else
			obj = (*itor).second;
	}
	
	void GetNextPosData(MultiObjectItor& itor,TYPE*& obj)
	{
		if (itor == m_mapObject.end())
		{
			obj = NULL;
			return;
		}		
		itor++;
		if (itor == m_mapObject.end())
			obj = NULL;
		else
			obj = (*itor).second;
	}	
protected:
	
	MultiObjectMap			m_mapObject;
	WLock					m_lock;
	MultiObjectAllocator	m_ObjAllocator;	
};

#endif //__WOBJECT_MAP_H