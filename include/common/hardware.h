#ifndef __HARDWARE__H__
#define __HARDWARE__H__

namespace WBASELIB
{

/*
 *	类名:		CHardWare
 *	功能:		用于获取本机硬件信息
 */
#define MAX_HARDDISKIDLEN	128
#define MAX_NETCARDIDLEN	128

class CHardWare
{
public:
    //功能:		返回硬盘ID
    static const char * GetHardDiskID();
    //功能:		返回CPUID
    static const char * GetCPUID();
    //功能:		返回本机IP地址
    static const char * GetIP();
};

}

#endif