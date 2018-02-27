/*##############################################################################
 * 文件：fs_types.h 
 * 描述：自定义跨平台类型
 * 作者：Teck
 * 创建：2014年11月24日
 * 版权：Copyright(C) 2014 Fsmeeting.com. All rights reserved.
 #############################################################################*/
#ifndef FASTMEETING_FS_TYPES_H_
#define FASTMEETING_FS_TYPES_H_
 
#if defined _FS_OS_LINUX || defined _FS_OS_IOS || defined _FS_OS_MAC || defined _FS_OS_ANDROID
#include <stdint.h>
#endif

namespace FsMeeting
{
#if defined __arm__ || defined __i386__
    #define  _FS_ARCH_32
#elif defined __arm64__ || defined __x86_64__
    #define  _FS_ARCH_64
#endif
// linux/ios/mac, android also use the linux macro.
#if defined _FS_OS_LINUX || defined _FS_OS_IOS || defined _FS_OS_MAC  || defined _FS_OS_ANDROID
    typedef void        FS_VOID;

    typedef int8_t      FS_INT8;
    typedef uint8_t     FS_UINT8;
    
    typedef int16_t     FS_INT16;
    typedef uint16_t    FS_UINT16;
    
    typedef int32_t     FS_INT32;
    typedef uint32_t    FS_UINT32;
    
    typedef int64_t     FS_INT64;
    typedef uint64_t    FS_UINT64;

    typedef float       FS_FLOAT;
    typedef double      FS_DOUBLE;

    typedef char        FS_CHAR;
    typedef wchar_t     FS_WCHAR;

#if defined  _FS_ARCH_32
    typedef int32_t     FS_INT;
    typedef uint32_t    FS_UINT;
#elif defined _FS_ARCH_64
    typedef int64_t     FS_INT;
    typedef uint64_t    FS_UINT;
#endif

// windows
#elif defined _FS_OS_WIN
    typedef void                FS_VOID;

    typedef __int8              FS_INT8;
    typedef unsigned __int8     FS_UINT8;
    
    typedef __int16             FS_INT16;
    typedef unsigned __int16    FS_UINT16;
    
    typedef __int32             FS_INT32;
    typedef unsigned __int32    FS_UINT32;
    
    typedef __int64             FS_INT64;
    typedef unsigned __int64    FS_UINT64;

    typedef float               FS_FLOAT;
    typedef double              FS_DOUBLE;

    typedef char                FS_CHAR;
    typedef wchar_t             FS_WCHAR;

#ifdef _FS_ARCH_32
    typedef __int32             FS_INT;
    typedef unsigned __int32    FS_UINT;
#elif defined _FS_ARCH_64
    typedef __int64             FS_INT;
    typedef unsigned __int64    FS_UINT;
#endif

#endif

} // namespace FsMeeting

#endif // FASTMEETING_FS_TYPES_H_
