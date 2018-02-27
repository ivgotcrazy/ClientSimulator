// Base64.h: interface for the CBase64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__E3797013_2C98_4C20_AE3C_680CF2E2C0AC__INCLUDED_)
#define AFX_BASE64_H__E3797013_2C98_4C20_AE3C_680CF2E2C0AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBase64
{
public:
    CBase64();
    virtual ~CBase64();

public:

    FS_INT32 EncodeBase64(const FS_UINT8* BuffIn, FS_INT32 nInLen, FS_UINT8* BuffOut, FS_INT32 nOutLen);
    FS_INT32 GetEncodeLen(FS_INT32 nOrigLen);


    FS_INT32 DecodeBase64(const FS_UINT8* BuffIn, FS_INT32 nInLen, FS_UINT8* BuffOut, FS_INT32 nOutLen);
};

#endif // !defined(AFX_BASE64_H__E3797013_2C98_4C20_AE3C_680CF2E2C0AC__INCLUDED_)
