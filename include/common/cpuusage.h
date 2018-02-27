// CPUUsage.h: interface for the CCPUUsage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPUUSAGE_H__0CAE092C_D8D3_423B_8F33_4A6056EA615D__INCLUDED_)
#define AFX_CPUUSAGE_H__0CAE092C_D8D3_423B_8F33_4A6056EA615D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace WBASELIB
{

class CCPUUsage
{
public:
    CCPUUsage();
    virtual ~CCPUUsage();
public:
    FS_UINT32 GetCPUUsage();
protected:
    LARGE_INTEGER						m_liOldIdleTime;
    LARGE_INTEGER						m_liOldSystemTime;
};

};

#endif // !defined(AFX_CPUUSAGE_H__0CAE092C_D8D3_423B_8F33_4A6056EA615D__INCLUDED_)
