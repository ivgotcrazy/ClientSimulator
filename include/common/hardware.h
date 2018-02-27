#ifndef __HARDWARE__H__
#define __HARDWARE__H__

namespace WBASELIB
{

/*
 *	����:		CHardWare
 *	����:		���ڻ�ȡ����Ӳ����Ϣ
 */
#define MAX_HARDDISKIDLEN	128
#define MAX_NETCARDIDLEN	128

class CHardWare
{
public:
    //����:		����Ӳ��ID
    static const char * GetHardDiskID();
    //����:		����CPUID
    static const char * GetCPUID();
    //����:		���ر���IP��ַ
    static const char * GetIP();
};

}

#endif