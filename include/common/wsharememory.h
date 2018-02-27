#ifndef __SHARE_MEMORY_H
#define __SHARE_MEMORY_H

#ifdef _FS_OS_WIN
#include "tchar.h"
#else
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

#include "wbasetype.h"
#include "wunicode.h"
#include "wcharfunction.h"

namespace WBASELIB
{

#ifdef _FS_OS_WIN

#define SHAREMEM_DEFAULTNAME	_T("SharedMemory")

class WSharedMemory
{
public:
    WSharedMemory() { _tcscpy(m_csName, SHAREMEM_DEFAULTNAME); m_bInit = FALSE; m_bAlreadyExist = FALSE; _stprintf(m_csMutexName, _T("%s%s"), m_csName, _T("Mutex")); }
    WSharedMemory(LPCTSTR cs) { _tcscpy(m_csName, cs); m_bInit = FALSE; m_bAlreadyExist = FALSE; _stprintf(m_csMutexName, _T("%s%s"), m_csName, _T("Mutex")); }
    WSharedMemory(FS_INT32 size, LPSECURITY_ATTRIBUTES lpFileMappingAttributes = NULL) { _tcscpy(m_csName, SHAREMEM_DEFAULTNAME); m_bAlreadyExist = FALSE; _stprintf(m_csMutexName, _T("%s%s"), m_csName, _T("Mutex")); Init(size, lpFileMappingAttributes); }
    WSharedMemory(LPCTSTR cs, FS_INT32 size, LPSECURITY_ATTRIBUTES lpFileMappingAttributes = NULL) { _tcscpy(m_csName, cs); m_bAlreadyExist = FALSE; _stprintf(m_csMutexName, _T("%s%s"), m_csName, _T("Mutex")); Init(size, lpFileMappingAttributes); }

    ~WSharedMemory()
    {
        Release();
    }
    BOOL Init(LPCTSTR cs, FS_INT32 size, LPSECURITY_ATTRIBUTES lpFileMappingAttributes = NULL) { _tcscpy(m_csName, cs); m_bAlreadyExist = FALSE; _stprintf(m_csMutexName, _T("%s%s"), m_csName, _T("Mutex")); return Init(size, lpFileMappingAttributes); }
    BOOL Init(FS_INT32 size, LPCTSTR cs, LPSECURITY_ATTRIBUTES lpFileMappingAttributes = NULL) { _tcscpy(m_csName, cs); m_bAlreadyExist = FALSE; _stprintf(m_csMutexName, _T("%s%s"), m_csName, _T("Mutex")); return Init(size, lpFileMappingAttributes); }
    BOOL Init(FS_INT32 size, LPSECURITY_ATTRIBUTES lpFileMappingAttributes = NULL)
    {
        m_hMutex = CreateMutex(NULL, FALSE, m_csMutexName);
        m_dwNumberOfBytesToMap = size;
        m_hSharedMemoryFile = CreateFileMapping(INVALID_HANDLE_VALUE,
            lpFileMappingAttributes,
            PAGE_READWRITE,
            0/*dwMaximumSizeHigh*/,
            m_dwNumberOfBytesToMap/*dwMaximumSizeLow*/,
            m_csName);
        if (m_hSharedMemoryFile == NULL)
        {
            m_bAlreadyExist = FALSE;
            m_bInit = FALSE;
            return FALSE;
        }
        else
        {
            if (GetLastError() == ERROR_ALREADY_EXISTS)
                m_bAlreadyExist = TRUE;
        }
        m_pwData = MapViewOfFile(m_hSharedMemoryFile,
            FILE_MAP_WRITE,
            0/*dwFileOffsetHigh*/,
            0/*dwFileOffsetLow*/,
            m_dwNumberOfBytesToMap);
        if (m_pwData == NULL)
        {
            m_bInit = FALSE;
            CloseHandle(m_hSharedMemoryFile);
            return FALSE;
        }
        else
            m_bInit = TRUE;
        return TRUE;
    }
    void  Release()
    {
        if (m_bInit)
        {
            UnmapViewOfFile(m_pwData);
            m_pwData = NULL;
            CloseHandle(m_hSharedMemoryFile);
            m_hSharedMemoryFile = NULL;
            CloseHandle(m_hMutex);
            m_hMutex = NULL;
        }
        m_bInit = FALSE;
    }
    void* GetData()
    {
        if (m_bInit)
            return m_pwData;
        else
            return NULL;
    }
    BOOL AlreadyExist()
    {
        return m_bAlreadyExist;
    }

    struct Locker
    {
        Locker(WSharedMemory* sm)
        {
            m_sm = sm;
            m_sm->Lock();
        }
        Locker(WSharedMemory& sm)
        {
            m_sm = &sm;
            m_sm->Lock();
        }
        ~Locker()
        {
            m_sm->Unlock();
        }
        WSharedMemory* m_sm;
    };
    BOOL Lock(FS_UINT32 dwMilliSec = INFINITE)
    {
        if (WaitForSingleObject(m_hMutex, dwMilliSec) == WAIT_OBJECT_0)
            return TRUE;
        return FALSE;
    }
    BOOL Unlock()
    {
        return ReleaseMutex(m_hMutex);
    }
protected:
    void *	m_pwData;
    TCHAR	m_csName[256];
    HANDLE	m_hSharedMemoryFile;
    FS_UINT32	m_dwMaximumSizeHigh;
    FS_UINT32	m_dwMaximumSizeLow;
    FS_UINT32	m_dwNumberOfBytesToMap;
    BOOL	m_bInit;
    BOOL	m_bAlreadyExist;
    TCHAR	m_csMutexName[256];
    HANDLE	m_hMutex;
};
#endif

}

#endif