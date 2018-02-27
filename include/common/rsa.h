// RSA.h: interface for the CRSA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSA_H__DD5631D5_2064_4DCC_B1C5_88F6B1A4F697__INCLUDED_)
#define AFX_RSA_H__DD5631D5_2064_4DCC_B1C5_88F6B1A4F697__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bignumber.h"
#include "randomgenerator.h"

namespace WBASELIB
{

#define ERSAOK			0
#define ERSA_OUT_OF_MEM (-1)
class CRSA
{
public:
    CBigNumber	p;
    CBigNumber	q;
    CBigNumber	e;
    CBigNumber	u;
    CBigNumber	n;
    CBigNumber	d;

    CRandomGenerator* m_prand;
public:
    CRSA();
    virtual ~CRSA();

    void InitRandGenerator(CRandomGenerator* prand) { m_prand = prand; };

    BOOL RsaPrimesGen(FS_UINT32 bits, FS_UINT32 pe, FS_INT32(*progress)(void *arg, FS_INT32 c), void *arg, FS_INT32 *error);
    BOOL RsaKeyGen(FS_UINT32 pe, FS_INT32(*progress)(void *arg, FS_INT32 c), void *arg, FS_INT32 *error);

    //these are very slowly interface.
    FS_INT32 rsaTestPrivateE(CBigNumber* bn, const PBYTE in, FS_UINT32 len);
    FS_INT32 rsaTestPublicD(const PBYTE in, FS_UINT32 len, const CBigNumber* bn);

    FS_INT32 rsaPublicEncrypt(CBigNumber *bn, const PBYTE in, FS_UINT32 len);
    FS_INT32 rsaPrivateEncrypt(CBigNumber *bn, const PBYTE in, FS_UINT32 len);
    FS_INT32 rsaPublicDecrypt(PBYTE buf, FS_UINT32 len, const CBigNumber *bn);
    FS_INT32 rsaPrivateDecrypt(PBYTE buf, FS_UINT32 len, const CBigNumber *bn);
};

};
#endif // !defined(AFX_RSA_H__DD5631D5_2064_4DCC_B1C5_88F6B1A4F697__INCLUDED_)
