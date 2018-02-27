// RandomGenerator.h: interface for the CRandomGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANDOMGENERATOR_H__4A4F00B0_DB64_4B3C_9DD8_7B8D6AC704FB__INCLUDED_)
#define AFX_RANDOMGENERATOR_H__4A4F00B0_DB64_4B3C_9DD8_7B8D6AC704FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "bignumber.h"

namespace WBASELIB
{

class CRandomGenerator
{
protected:
    BOOL	m_bSetFileName;
    FS_INT32		m_nUpdateCounter;
    BYTE	m_bySeed[1024];
    std::string m_strFileName;
    void _RandomGetBytesEntropy(FS_UINT8* buf, FS_UINT32 l, FS_UINT32 effective);
public:
    CRandomGenerator();
    virtual ~CRandomGenerator();

    BOOL LoadSeedFromFile(const char* szFileName);
    BOOL SaveSeedIntoFile();

    void Update(FS_INT32 n);
    FS_INT32 GetUpdateCounter() { return m_nUpdateCounter; };

    FS_INT32 GenRand(CBigNumber *bn, FS_UINT32 bits, BYTE high, BYTE low, FS_UINT32 effective);
};

};

#endif // !defined(AFX_RANDOMGENERATOR_H__4A4F00B0_DB64_4B3C_9DD8_7B8D6AC704FB__INCLUDED_)
