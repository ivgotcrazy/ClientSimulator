#ifndef __WBASETYPE_H
#define __WBASETYPE_H

#include "fs_types.h"
using namespace FsMeeting;

#if !defined(_FS_OS_WIN)
#include "wwindef.h"
#else
#include "windows.h"
#ifndef QWORD
typedef FS_UINT64	QWORD;
#endif

typedef unsigned short CHARU16;

#define NOVTABLE	__declspec(novtable)
#endif	//_FS_OS_WIN

#define MSGBASEID		WM_USER

//
//WBASE_NOTIFY DEFINE
//
#define			WBASE_NOTIFYMODE_NONE				0X0000	//无通知
#define			WBASE_NOTIFYMODE_EVENT				0x0001	//事件方式
#define			WBASE_NOTIFYMODE_THREADMSG			0x0002	//线程消息方式
#define			WBASE_NOTIFYMODE_HWNDMSG			0x0003	//窗口消息方式
#define			WBASE_NOTIFYMODE_INTERFACE			0x0004	//接口指针方式
#define			WBASE_NOTIFYMODE_CALLBACK			0x0005	//回调方式

#define			WBASE_NOTIFYMODE_MSGQUEUE			0x0006

typedef struct
{

    UINT        message;
    WPARAM     	wParam;
    LPARAM     	lParam;

}WBASE_MSG;

typedef BOOL(CALLBACK* WBASECALLBACK)(UINT nMsgID, WPARAM wParam, LPARAM lParam, FS_UINT32 dwReserved, FS_UINT dwUserData);

//消息通知方式定义
typedef struct
{

    int						nNotifyMode;
    union
    {
        struct
        {
            HANDLE			event;
        }EventMode;
        struct
        {
            FS_UINT32		nThreadID;
            FS_UINT32		nNotifyMsg;
        }ThreadMsgMode;
        struct
        {
            HWND			hWnd;
            FS_UINT32		nNotifyMsg;
        }HwndMsgMode;
        struct
        {
            void*			pInterface;
        }InterfaceMode;
        struct
        {
            void*			pCallback;
            FS_UINT32		nMsgID;
            FS_UINT			dwUserData;
        }CallbackMode;
        struct
        {
            FS_INT32 		nMsgQueueID;
            FS_UINT32		nMsgID;
        }MsgQueueMode;
    };
}WBASE_NOTIFY;

typedef		FS_UINT32		WTHREADID;

typedef void (WINAPI *LogPrintA)(LPCSTR format, ...);
typedef void (WINAPI *LogPrintW)(LPCWSTR format, ...);

#endif