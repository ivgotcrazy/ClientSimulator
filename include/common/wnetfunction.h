#ifndef __WBASELIB_WNETFUNCTION_H
#define __WBASELIB_WNETFUNCTION_H

#include "stdio.h"
#include "stdlib.h"
#include "wbasetype.h"

#ifdef _FS_OS_WIN

#include <winsock2.h>
#include <ws2tcpip.h>
#define NETERRORNO		WSAGetLastError()
typedef FS_INT32		socklen_t;

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#ifdef _FS_OS_ANDROID
#include <linux/if.h>
#endif
#if defined _FS_OS_IOS || defined _FS_OS_MAC
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#endif

#if defined __linux__
#include <sys/ioctl.h>
#include <net/if.h>
#endif

typedef FS_UINT32   		SOCKET;
typedef struct sockaddr_in	SOCKADDR_IN;

#define ADDR_ANY		INADDR_ANY
#define INVALID_SOCKET		(-1)
#define SOCKET_ERROR		(-1)
#define NETERRORNO		errno
#define	closesocket		close

#define WSAEWOULDBLOCK		EWOULDBLOCK
#define WSAEINPROGRESS		EINPROGRESS
#define WSAEALREADY		EALREADY
#define WSAENOTSOCK		ENOTSOCK
#define WSAEDESTADDRREQ		EDESTADDRREQ
#define WSAEMSGSIZE		EMSGSIZE
#define WSAEPROTOTYPE		EPROTOTYPE
#define WSAENOPROTOOPT		ENOPROTOOPT
#define WSAEPROTONOSUPPORT	EPROTONOSUPPORT
#define WSAESOCKTNOSUPPORT	ESOCKTNOSUPPORT
#define WSAEOPNOTSUPP		EOPNOTSUPP
#define WSAEPFNOSUPPORT		EPFNOSUPPORT
#define WSAEAFNOSUPPORT		EAFNOSUPPORT
#define WSAEADDRINUSE		EADDRINUSE
#define WSAEADDRNOTAVAIL	EADDRNOTAVAIL
#define WSAENETDOWN		ENETDOWN
#define WSAENETUNREACH		ENETUNREACH
#define WSAENETRESET		ENETRESET
#define WSAECONNABORTED		ECONNABORTED
#define WSAECONNRESET		ECONNRESET
#define WSAENOBUFS		ENOBUFS
#define WSAEISCONN		EISCONN
#define WSAENOTCONN		ENOTCONN
#define WSAESHUTDOWN		ESHUTDOWN
#define WSAETOOMANYREFS		ETOOMANYREFS
#define WSAETIMEDOUT		ETIMEDOUT
#define WSAECONNREFUSED		ECONNREFUSED
#define WSAELOOP		ELOOP
#define WSAENAMETOOLONG		ENAMETOOLONG
#define WSAEHOSTDOWN		EHOSTDOWN
#define WSAEHOSTUNREACH		EHOSTUNREACH
#define WSAENOTEMPTY		ENOTEMPTY
#define WSAEPROCLIM		EPROCLIM
#define WSAEUSERS		EUSERS
#define WSAEDQUOT		EDQUOT
#define WSAESTALE		ESTALE
#define WSAEREMOTE		EREMOTE

#define	FD_READ			0x01
#define FD_WRITE		0x02
#define FD_OOB			0x04
#define FD_ACCEPT		0x08
#define FD_CONNECT		0x10
#define FD_CLOSE		0x20

#define SD_BOTH			2

typedef fd_set 			FD_SET;
typedef struct timeval		TIMEVAL;

#endif

namespace WBASELIB
{

extern BOOL IsLanIP(FS_UINT32 dwIP);

extern VOID IPToString(FS_UINT32 dwIP, CHAR *szIP);

extern VOID IPToWString(FS_UINT32 dwIP, WCHAR *szIP);

#ifdef _UNICODE
#define IPToTString		IPToWString
#else
#define IPToTString		IPToString
#endif

extern BOOL SetSockNonBlocking(SOCKET sock, BOOL bNonBlocking);

extern BOOL DNSToIPString(const CHAR* szDNS, CHAR* szIP);

extern BOOL GetPhysicalIPList(FS_UINT32 *pdwIPList, FS_UINT32& dwSize, BOOL bLoopBack = FALSE);

}

#endif