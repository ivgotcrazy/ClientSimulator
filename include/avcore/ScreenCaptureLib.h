#ifndef __SCREEN_CAPTURE_LIBRARY_H
#define __SCREEN_CAPTURE_LIBRARY_H

#include "fs_types.h"

using namespace FsMeeting;

typedef struct{
	
	BOOL	bClipUponWnd;
	HWND	hCapWnd;
	int		nCapLeft;
	int		nCapTop;
	int		nCapWidth;
	int		nCapHeight;

	int		nFrameRate;
}ScreenCapParam;

typedef void (*ScreenCapCallBack)( PBYTE pbData,DWORD dwDataLen,FS_UINT dwUserData );

HANDLE		SC_Create( );
BOOL		SC_SetParam( HANDLE hSC,const ScreenCapParam& param  );
BOOL		SC_Start( HANDLE hSC,ScreenCapCallBack callback,FS_UINT dwUserData );
VOID		SC_Stop( HANDLE hSC );
LPBITMAPINFO SC_GetFormat( HANDLE hSC );
VOID		SC_Destroy( HANDLE hSC );
VOID		SC_SetLogger( LogPrintW logger );

#endif