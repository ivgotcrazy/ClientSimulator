#ifndef __WWINDEEF_H
#define __WWINDEEF_H
#include "fs_types.h"
using namespace FsMeeting;

#ifdef _FS_OS_LINUX
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>
#endif

#if !defined(_FS_OS_WIN)

typedef char CHAR;
typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;
typedef unsigned char UCHAR;

typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR;
typedef const WCHAR *LPCWSTR;

typedef unsigned short CHARU16;

typedef unsigned char BYTE;
typedef FS_UINT32 UINT;
typedef FS_INT32 INT;

#if defined _FS_OS_IOS

#if !defined(OBJC_HIDE_64)  &&__LP64__
typedef bool BOOL;
#else//arm64
typedef signed char BOOL;
#endif//arm64

#elif defined _FS_OS_MAC
typedef signed char BOOL;

#else//_IOS
typedef FS_INT32 BOOL;

#endif//_IOS

typedef FS_INT32 LONG;
typedef FS_UINT32 DWORD;
typedef FS_INT16 SHORT;
typedef FS_UINT16 WORD;
typedef FS_UINT16 USHORT;
typedef FS_INT64 LONGLONG;
typedef FS_UINT64 ULONGLONG;

typedef DWORD   COLORREF;
typedef DWORD   *LPCOLORREF;

typedef DWORD ULONG;
typedef LONG LRESULT;
typedef LONG HRESULT;
typedef WORD *LPWORD;
typedef DWORD *LPDWORD;
typedef LONG* LPLONG;
typedef BYTE* PBYTE;
typedef BYTE* LPBYTE;
typedef double DOUBLE;

typedef void VOID;
typedef VOID* LPVOID;

#if defined _FS_OS_IOS || defined _FS_OS_MAC
typedef long long int LONGLONG;
typedef unsigned long long int ULONGLONG;
typedef ULONGLONG QWORD;
#else
typedef FS_INT64 LONGLONG;
typedef FS_UINT64 ULONGLONG;
typedef FS_UINT64	QWORD;
#endif

typedef union _LARGE_INTEGER
{
    struct
    {
        FS_UINT32 LowPart;
        LONG HighPart;
    };
    struct
    {
        FS_UINT32 LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef struct _GUID
{

    FS_UINT32		Data1;
    FS_UINT16		Data2;
    FS_UINT16		Data3;
    FS_UINT8 	Data4[8];
}GUID;
typedef GUID 	IID;
typedef GUID	CLSID;

typedef FS_UINT WPARAM;
typedef FS_INT  LPARAM;

typedef void* HANDLE;
typedef void* HWND;
typedef void* HMODULE;
typedef void* HBITMAP;

typedef DWORD COLORREF;

#ifndef FALSE
#define FALSE  0
#define TRUE   1
#endif

#ifndef MAX_PATH
#define MAX_PATH	256
#endif

#define INFINITE		((DWORD)0xffffffff)
#define WAIT_OBJECT_0	((DWORD)0x00000000)
#define WAIT_TIMEOUT	((DWORD)0x00000102)

#define NOVTABLE
#define CALLBACK
#define WINAPI
#define STDAPICALLTYPE
#define STDMETHODCALLTYPE
#define __cdecl

#define NEAR
#define FAR

#define 	WM_USER			100
#define		WM_TIMER		WM_USER+98
#define 	WM_QUIT			WM_USER+99

#ifdef __cplusplus

#define EXTERN_C	extern "C"
#define REFIID 		const IID &
#define REFCLSID	const IID &

#define interface	struct
#define STDMETHOD(method) virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
#define PURE		= 0
#define THIS_		
#define THIS		void
#define DECLARE_INTERFACE(iface) interface iface
#define DECLARE_INTERFACE_(iface,baseiface) interface iface: public baseiface

#else

#define EXTERN_C	extern
#define REFIID 		const IID *
#define REFCLSID	const IID *

#define interface 	struct NOVTABLE
#define STDMETHOD(method) HRESULT (STDMETHODCALLTYPE* method)
#define STDMETHOD_(type,method) type (STDMETHODCALLTYPE* method)
#define PURE
#define THIS_		INTERFACE* This,
#define THIS		INTERFACE* This
#define DECLARE_INTERFACE( iface ) typedef interface iface{ \
							struct iface##Vtbl * lpVtbl; \
						} iface;\
						typedef struct iface##Vtbl iface##Vtbl; \
						struct iface##Vtbl
#define DECLARE_INTERFACE_(iface,baseiface ) DECLARE_INTERFACE( iface )

#endif //_cplusplus

#define REFGUID		REFIID

#ifdef __cplusplus

__inline int InlineIsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
    return (
        ((FS_UINT32*)&rguid1)[0] == ((FS_UINT32*)&rguid2)[0] &&
        ((FS_UINT32*)&rguid1)[1] == ((FS_UINT32*)&rguid2)[1] &&
        ((FS_UINT32*)&rguid1)[2] == ((FS_UINT32*)&rguid2)[2] &&
        ((FS_UINT32*)&rguid1)[3] == ((FS_UINT32*)&rguid2)[3]);
}

#include <memory.h>
#include "string"

__inline int IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
    return !memcmp(&rguid1, &rguid2, sizeof(GUID));
}

__inline int operator==(REFGUID guidOne, REFGUID guidOther)
{
    return IsEqualGUID(guidOne, guidOther);
}

__inline FS_INT32 operator!=(REFGUID guidOne, REFGUID guidOther)
{
    return !(guidOne == guidOther);
}

#define IsEqualCLSID	IsEqualGUID

#endif //_cplusplus

#define STDAPI		EXTERN_C HRESULT STDAPICALLTYPE
#define STDAPI_(type)	EXTERN_C type STDAPICALLTYPE

#define STDMETHODIMP	HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type) type STDMETHODCALLTYPE

#ifdef INITGUID
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8 ) \
			EXTERN_C const GUID name \
				= { l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8 }}
#else
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8 ) \
			EXTERN_C const GUID name
#endif // INITGUID

#define MoveMemory( d,s,l )	memmove( (d),(s),(l))
#define CopyMemory( d,s,l )	memcpy( (d),(s),(l))
#define FillMemory( d,l,f )	memset( (d),(f),(l))
#define ZeroMemory( d,l )	memset( (d),0,(l))

#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
		((FS_UINT32)(BYTE)(ch0) | ((FS_UINT32)(BYTE)(ch1) << 8) |   \
	((FS_UINT32)(BYTE)(ch2) << 16) | ((FS_UINT32)(BYTE)(ch3) << 24 ))

/* MMIO macros */
#define mmioFOURCC(ch0, ch1, ch2, ch3)  MAKEFOURCC(ch0, ch1, ch2, ch3)

#define BI_RGB		0
#define BI_BITFIELDS    3

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((FS_UINT16)((BYTE)(g))<<8))|(((FS_UINT32)(BYTE)(b))<<16)))
#define GetRValue(rgb)      ((BYTE)(rgb))
#define GetGValue(rgb)      ((BYTE)(((FS_UINT16)(rgb)) >> 8))
#define GetBValue(rgb)      ((BYTE)((rgb)>>16))

typedef struct tagBITMAPINFOHEADER
{
    FS_UINT32		biSize;
    LONG			biWidth;
    LONG			biHeight;
    FS_UINT16			biPlanes;
    FS_UINT16			biBitCount;
    FS_UINT32		biCompression;
    FS_UINT32		biSizeImage;
    LONG			biXPelsPerMeter;
    LONG			biYPelsPerMeter;
    FS_UINT32		biClrUsed;
    FS_UINT32		biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} BITMAPINFO;

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT;

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT, *LPRECT;
typedef const RECT* LPCRECT;

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

#ifndef _WAVEFORMATEX_

#define WAVE_FORMAT_PCM     1

#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
    FS_UINT16		wFormatTag;        /* format type */
    FS_UINT16		nChannels;         /* number of channels (i.e. mono, stereo...) */
    FS_UINT32		nSamplesPerSec;    /* sample rate */
    FS_UINT32		nAvgBytesPerSec;   /* for buffer estimation */
    FS_UINT16		nBlockAlign;       /* block size of data */
    FS_UINT16		wBitsPerSample;    /* Number of bits per sample of mono data */
    FS_UINT16		cbSize;            /* The count in bytes of the size of
                                    extra information (after cbSize) */
} WAVEFORMATEX;
#endif /* _WAVEFORMATEX_ */

/* Logical Font */
#define LF_FACESIZE         32

typedef struct tagLOGFONTA
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    BYTE      lfItalic;
    BYTE      lfUnderline;
    BYTE      lfStrikeOut;
    BYTE      lfCharSet;
    BYTE      lfOutPrecision;
    BYTE      lfClipPrecision;
    BYTE      lfQuality;
    BYTE      lfPitchAndFamily;
    CHAR      lfFaceName[LF_FACESIZE];
} LOGFONTA, *PLOGFONTA, NEAR *NPLOGFONTA, FAR *LPLOGFONTA;
typedef struct tagLOGFONTW
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    BYTE      lfItalic;
    BYTE      lfUnderline;
    BYTE      lfStrikeOut;
    BYTE      lfCharSet;
    BYTE      lfOutPrecision;
    BYTE      lfClipPrecision;
    BYTE      lfQuality;
    BYTE      lfPitchAndFamily;
    WCHAR     lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;
#ifdef UNICODE
typedef LOGFONTW LOGFONT;
typedef PLOGFONTW PLOGFONT;
typedef NPLOGFONTW NPLOGFONT;
typedef LPLOGFONTW LPLOGFONT;
#else
typedef LOGFONTA LOGFONT;
typedef PLOGFONTA PLOGFONT;
typedef NPLOGFONTA NPLOGFONT;
typedef LPLOGFONTA LPLOGFONT;
#endif // UNICODE

#endif	//_FS_OS_WIN

#endif
