// BigNumber.h: interface for the CBigNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIGNUMBER_H__87A218D7_579F_4D1C_92F2_9AD6B05FB1DB__INCLUDED_)
#define AFX_BIGNUMBER_H__87A218D7_579F_4D1C_92F2_9AD6B05FB1DB__INCLUDED_

#include "stdafx.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define bnExtractBigBytes		bnExtractBigBytes_32
#define bnInsertBigBytes		bnInsertBigBytes_32
#define bnExtractLittleBytes	bnExtractLittleBytes_32
#define bnInsertLittleBytes		bnInsertLittleBytes_32
#define bnCopy					bnCopy_32
#define bnNorm					bnNorm_32
#define bnLSWord				bnLSWord_32
#define bnBits					bnBits_32
#define bnAdd					bnAdd_32
#define bnSub					bnSub_32
#define bnCmpQ					bnCmpQ_32
#define bnSetQ					bnSetQ_32
#define bnAddQ					bnAddQ_32
#define bnSubQ					bnSubQ_32
#define bnCmp					bnCmp_32
#define bnSquare				bnSquare_32
#define bnMul					bnMul_32
#define bnMulQ					bnMulQ_32
#define bnDivMod				bnDivMod_32
#define bnMod					bnMod_32
#define bnModQ					bnModQ_32
#define bnExpMod				bnExpMod_32
#define bnDoubleExpMod			bnDoubleExpMod_32
#define bnTwoExpMod				bnTwoExpMod_32
#define bnGcd					bnGcd_32
#define bnInv					bnInv_32
#define bnLShift				bnLShift_32
#define bnRShift				bnRShift_32
#define bnMakeOdd				bnMakeOdd_32

#define BITS2BYTES(b)	((b + 7) >> 3)

class CBigNumber
{
protected:
    BOOL _ToStringXX(FS_INT32 nType, char* pszString, FS_INT32 nBufferSize) const;
    BOOL _StringXXFrom(FS_INT32 nType, const char* pszString);
    BOOL _GetNumber(FS_INT32& n, FS_INT32& nRunLen, FS_INT32 nType, const char* psz, FS_INT32 len);
public:
    void*		ptr;
    FS_UINT32	size;
    FS_UINT32	allocated;

    CBigNumber();
    virtual ~CBigNumber();

    //bytes array
    BOOL ToBytes(PBYTE pb, FS_INT32 nBufferSize, FS_INT32* pnNeedBufferSize = NULL) const;
    BOOL BytesFrom(const PBYTE pb, FS_INT32 nBufferSize);

    //\x??  ? = 0123456789ABCDEF
    BOOL ToStringC(char* pszString, FS_INT32 nBufferSize) const;
    BOOL StringCFrom(const char* pszString);

    //??	? = 0123456789ABCDEF
    BOOL ToStringHex(char* pszString, FS_INT32 nBufferSize) const;
    BOOL StringHexFrom(const char* pszString);

    //?		? = 0123456789
    BOOL ToStringDec(char* pszString, FS_INT32 nBufferSize) const;
    BOOL StringDecFrom(const char* pszString);

    //friend helper functions
    //default, these functions are 64 bits
    friend void bnExtractBigBytes_32(CBigNumber const *bn, FS_UINT8 *dest, FS_UINT32 lsbyte, FS_UINT32 dlen);
    friend FS_INT32 bnInsertBigBytes_32(CBigNumber *bn, FS_UINT8 const *src, FS_UINT32 lsbyte, FS_UINT32 len);
    friend void bnExtractLittleBytes_32(CBigNumber const *bn, FS_UINT8 *dest, FS_UINT32 lsbyte, FS_UINT32 dlen);
    friend FS_INT32 bnInsertLittleBytes_32(CBigNumber *bn, FS_UINT8 const *src, FS_UINT32 lsbyte, FS_UINT32 len);
    friend FS_INT32 bnCopy_32(CBigNumber *dest, CBigNumber const *src);
    friend void bnNorm_32(CBigNumber *bn);
    friend FS_UINT32 bnLSWord_32(CBigNumber const *src);
    friend FS_UINT32 bnBits_32(CBigNumber const *src);
    friend FS_INT32 bnAdd_32(CBigNumber *dest, CBigNumber const *src);
    friend FS_INT32 bnSub_32(CBigNumber *dest, CBigNumber const *src);
    friend FS_INT32 bnCmpQ_32(CBigNumber const *a, FS_UINT32 b);
    friend FS_INT32 bnSetQ_32(CBigNumber *dest, FS_UINT32 src);
    friend FS_INT32 bnAddQ_32(CBigNumber *dest, FS_UINT32 src);
    friend FS_INT32 bnSubQ_32(CBigNumber *dest, FS_UINT32 src);
    friend FS_INT32 bnCmp_32(CBigNumber const *a, CBigNumber const *b);
    friend FS_INT32 bnSquare_32(CBigNumber *dest, CBigNumber const *src);
    friend FS_INT32 bnMul_32(CBigNumber *dest, CBigNumber const *a, CBigNumber const *b);
    friend FS_INT32 bnMulQ_32(CBigNumber *dest, CBigNumber const *a, FS_UINT32 b);
    friend FS_INT32 bnDivMod_32(CBigNumber *q, CBigNumber *r, CBigNumber const *n, CBigNumber const *d);
    friend FS_INT32 bnMod_32(CBigNumber *dest, CBigNumber const *src, CBigNumber const *d);
    friend FS_UINT32 bnModQ_32(CBigNumber const *src, FS_UINT32 d);
    friend FS_INT32 bnExpMod_32(CBigNumber *dest, CBigNumber const *n, CBigNumber const *exp, CBigNumber const *mod);
    friend FS_INT32 bnDoubleExpMod_32(CBigNumber *dest, CBigNumber const *n1, CBigNumber const *e1, CBigNumber const *n2, CBigNumber const *e2, CBigNumber const *mod);
    friend FS_INT32 bnTwoExpMod_32(CBigNumber *n, CBigNumber const *exp, CBigNumber const *mod);
    friend FS_INT32 bnGcd_32(CBigNumber *dest, CBigNumber const *a, CBigNumber const *b);
    friend FS_INT32 bnInv_32(CBigNumber *dest, CBigNumber const *src, CBigNumber const *mod);
    friend FS_INT32 bnLShift_32(CBigNumber *dest, FS_UINT32 amt);
    friend void bnRShift_32(CBigNumber *dest, FS_UINT32 amt);
    friend FS_UINT32 bnMakeOdd_32(CBigNumber *n);

    //this operators
    inline CBigNumber& operator=(FS_UINT32 n) { bnSetQ(this, n); return *this; }
    inline CBigNumber& operator=(FS_INT32 i) { bnSetQ(this, i); return *this; }
    //inline CBigNumber& operator=(FS_INT64 lg)				{ bnSetQ(this, lg); return *this;	}
    inline CBigNumber& operator=(const CBigNumber& bn) { bnCopy(this, &bn); return *this; }
    inline CBigNumber& operator=(CBigNumber* pbn) { bnCopy(this, pbn); return *this; }

    inline CBigNumber& operator++() { bnAddQ(this, 1); return *this; }
    inline CBigNumber& operator--() { bnSubQ(this, 1); return *this; }

    inline CBigNumber& operator+=(FS_INT32 i) { bnAddQ(this, i); return *this; }
    inline CBigNumber& operator+=(const CBigNumber& b) { bnAdd(this, &b); return *this; }

    inline CBigNumber& operator-=(FS_INT32 i) { bnSubQ(this, i); return *this; }
    inline CBigNumber& operator-=(const CBigNumber& b) { bnSub(this, &b); return *this; }

    inline CBigNumber& operator*=(FS_INT32 i) { CBigNumber b; b = *this; bnMulQ(this, &b, i); return *this; }
    inline CBigNumber& operator*=(const CBigNumber& b) { CBigNumber br; br = *this; bnMul(this, &br, &b); return *this; }

    inline CBigNumber& operator/=(const CBigNumber& b) { CBigNumber q, r; bnDivMod(&q, &r, this, &b); *this = q; return *this; }
    inline CBigNumber& operator/=(FS_INT32 i) { CBigNumber b; b = i; *this /= b; return *this; }

    inline CBigNumber& operator%=(const CBigNumber& b) { CBigNumber q, r; bnDivMod(&q, &r, this, &b); *this = r; return *this; }
    inline CBigNumber& operator%=(FS_INT32 i) { CBigNumber b; b = i; *this %= b; return *this; }

    inline CBigNumber& operator<<=(FS_INT32 i) { bnLShift(this, i); return *this; }
    inline CBigNumber& operator>>=(FS_INT32 i) { bnRShift(this, i); return *this; }

    //friend operators
    friend CBigNumber operator-(const CBigNumber& bn)
    {
        CBigNumber b; b = 0; b -= bn; return b;
    }

    friend CBigNumber operator+(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b += n; return b;
    };
    friend CBigNumber operator+(FS_INT32 n, const CBigNumber& bn)
    {
        CBigNumber b; b = bn; b += n; return b;
    };
    friend CBigNumber operator+(const CBigNumber& bn1, const CBigNumber& bn2)
    {
        CBigNumber b; b = bn1; b += bn2; return b;
    }

    friend CBigNumber operator-(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b -= n; return b;
    }
    friend CBigNumber operator-(FS_INT32 n, const CBigNumber& bn)
    {
        CBigNumber b; b = n; b -= bn; return b;
    }
    friend CBigNumber operator-(const CBigNumber& bn1, const CBigNumber& bn2)
    {
        CBigNumber b; b = bn1; b -= bn2; return b;
    }

    friend CBigNumber operator*(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b *= n; return b;
    }
    friend CBigNumber operator*(FS_INT32 n, const CBigNumber& bn)
    {
        CBigNumber b; b = bn; b *= n; return b;
    }
    friend CBigNumber operator*(const CBigNumber& bn1, const CBigNumber& bn2)
    {
        CBigNumber b; b = bn1; b *= bn2; return b;
    }

    friend CBigNumber operator/(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b /= n; return b;
    }
    friend CBigNumber operator/(const CBigNumber& bn1, const CBigNumber& bn2)
    {
        CBigNumber b; b = bn1; b /= bn2; return b;
    }

    //the return value will be <= n, so bnLSWord is safe
    friend FS_INT32 operator%(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b %= n; return bnLSWord(&b);
    }
    friend CBigNumber operator%(const CBigNumber& bn1, const CBigNumber& bn2)
    {
        CBigNumber b; b = bn1; b %= bn2; return b;
    }

    friend CBigNumber operator<<(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b <<= n; return b;
    }
    friend CBigNumber operator>>(const CBigNumber& bn, FS_INT32 n)
    {
        CBigNumber b; b = bn; b >>= n; return b;
    }

    friend BOOL operator<=(const CBigNumber& b1, const CBigNumber& b2)
    {
        FS_INT32 n = bnCmp(&b1, &b2); return n <= 0;
    }
    friend BOOL operator>=(const CBigNumber& b1, const CBigNumber& b2)
    {
        FS_INT32 n = bnCmp(&b1, &b2); return n >= 0;
    }
    friend BOOL operator==(const CBigNumber& b1, const CBigNumber& b2)
    {
        FS_INT32 n = bnCmp(&b1, &b2); return n == 0;
    }
    friend BOOL operator!=(const CBigNumber& b1, const CBigNumber& b2)
    {
        FS_INT32 n = bnCmp(&b1, &b2); return n != 0;
    }
    friend BOOL operator<(const CBigNumber& b1, const CBigNumber& b2)
    {
        FS_INT32 n = bnCmp(&b1, &b2); return n < 0;
    }
    friend BOOL operator>(const CBigNumber& b1, const CBigNumber& b2)
    {
        FS_INT32 n = bnCmp(&b1, &b2); return n > 0;
    }

    friend BOOL operator<=(const CBigNumber& b1, const FS_INT32 n2)
    {
        FS_INT32 n = bnCmpQ(&b1, n2); return n <= 0;
    }
    friend BOOL operator>=(const CBigNumber& b1, const FS_INT32 n2)
    {
        FS_INT32 n = bnCmpQ(&b1, n2); return n >= 0;
    }
    friend BOOL operator==(const CBigNumber& b1, const FS_INT32 n2)
    {
        FS_INT32 n = bnCmpQ(&b1, n2); return n == 0;
    }
    friend BOOL operator!=(const CBigNumber& b1, const FS_INT32 n2)
    {
        FS_INT32 n = bnCmpQ(&b1, n2); return n != 0;
    }
    friend BOOL operator<(const CBigNumber& b1, const FS_INT32 n2)
    {
        FS_INT32 n = bnCmpQ(&b1, n2); return n < 0;
    }
    friend BOOL operator>(const CBigNumber& b1, const FS_INT32 n2)
    {
        FS_INT32 n = bnCmpQ(&b1, n2); return n > 0;
    }

    FS_INT32 AsInt() { return bnLSWord(this); }
    FS_INT32 GetBits() { return bnBits(this); };

#if !defined(__NO_RSA_HELPER__)
    //RSA helper
    /* Generate a prime >= bn. leaving the result in bn. */
    FS_INT32 __cdecl bnPrimeGen(FS_UINT32(*randnum)(FS_UINT32),
        FS_INT32(*f)(void *arg, FS_INT32 c), void *arg, FS_UINT32 exponent, ...);
    /*
     * Generate a prime of the form bn + k*step.  Step must be even and
     * bn must be odd.
     */
    FS_INT32 bnPrimeGenStrong(CBigNumber const *step, FS_INT32(*f)(void *arg, FS_INT32 c), void *arg);
#endif /*!__NO_RSA_HELPER__*/
};

#endif // !defined(AFX_BIGNUMBER_H__87A218D7_579F_4D1C_92F2_9AD6B05FB1DB__INCLUDED_)
