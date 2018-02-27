// FrameBaseObject.h: interface for the CFrameBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEBASEOBJECT_H__8911E8E0_B697_493B_8BC4_98741BB8778F__INCLUDED_)
#define AFX_FRAMEBASEOBJECT_H__8911E8E0_B697_493B_8BC4_98741BB8778F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wbasetype.h"
#include "wunicode.h"

namespace FRAMEWORKSDK
{

class CFrameBaseObject
{
private:
    static FS_INT32 m_cObjects;     /* Total number of objects active */

public:
    /* These increment and decrement the number of active objects */

    CFrameBaseObject(const TCHAR *pName);
    ~CFrameBaseObject();

    /* Call this to find if there are any CUnknown derived objects active */

    static FS_INT32 ObjectsActive()
    {
        return m_cObjects;
    };
};

}

#endif // !defined(AFX_FRAMEBASEOBJECT_H__8911E8E0_B697_493B_8BC4_98741BB8778F__INCLUDED_)
