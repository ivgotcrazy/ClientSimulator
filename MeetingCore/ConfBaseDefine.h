#ifndef __CONF_BASE_DEFINE_H
#define __CONF_BASE_DEFINE_H

#include "list"
#include "map"
#include "vector"

#if defined(_FS_OS_IOS) || defined(_FS_OS_MAC) || defined(_FS_OS_LINUX)
#include <ext/hash_map>
using namespace __gnu_cxx;
#else
#include "hash_map"
#endif

#include "string"

#if !(defined(_FS_OS_IOS) || defined(_FS_OS_MAC) || defined(_FS_OS_ANDROID)) || defined(_FS_OS_LINUX)
#include "wlog.h"
using namespace WBASELIB;
#endif



#ifdef _UNICODE
typedef std::wstring			tstring;
#else
typedef std::string				tstring;
#endif

#ifdef _WIN32_WCE
typedef stdext::hash_map<tstring,tstring> StringMap;
#elif defined(_FS_OS_ANDROID)
typedef std::hash_map<tstring,tstring> StringMap;
#elif defined(_FS_OS_LINUX)
typedef std::map<tstring,tstring> StringMap;
#elif defined(_FS_OS_WIN)
//modify by ron2012-10-15

#if _MSC_VER < 1400 
typedef std::hash_map<tstring,tstring> StringMap;  //vc6 
#else
	typedef stdext::hash_map<tstring,tstring> StringMap; //vc2008
#endif

#elif defined(_FS_OS_IOS) || defined(_FS_OS_MAC)
using namespace __gnu_cxx;
typedef __gnu_cxx::hash_map<tstring, tstring> StringMap;
#endif

#endif
