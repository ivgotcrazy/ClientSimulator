// FileEncrypt.h: interface for the CFileEncrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEENCRYPT_H__400C44A2_31A9_449A_9DE4_0E7D92EA0414__INCLUDED_)
#define AFX_FILEENCRYPT_H__400C44A2_31A9_449A_9DE4_0E7D92EA0414__INCLUDED_
#include "stdafx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
 *	类名:		CFileEncrypt
 *	功能:		对文件进行加解密,以及计算加密后的文件大小
 */
#include "rsa.h"

namespace WBASELIB
{

class CFileEncrypt
{
public:
    CFileEncrypt();
    virtual ~CFileEncrypt();

    //功能:		计算加密后的文件大小,但对文件不进行加密
    //参数:		lpszInFilePath		需要加密的文件名
    //			lpszOutFilePath		加密后的文件名
    //			dwPrivateDataLen	加密私有数据大小
    //返回值:	返回加密后的文件大小
    FS_UINT32	DetectEncryptFileSize(LPCTSTR lpszInFilePath, LPCTSTR lpszOutFilePath, FS_UINT32 dwPrivateDataLen = 0);

    //功能:		解密文件
    //参数:		lpszInFilePath		需要解密的文件名
    //			lpszOutFilePath		解密后的文件名
    //			lpszPrivateData		解密私有数据
    //			dwPrivateDataLen	解密私有数据大小
    //返回值:	TRUE				解密成功
    //			FALSE				解密失败
    BOOL	DecryptFile(LPCTSTR lpszInFilePath, LPCTSTR lpszOutFilePath = NULL, LPCTSTR lpszPrivateData = NULL, FS_UINT32 dwPrivateDatalen = 0);

    //功能:		解密文件
    //参数:		lpszInFilePath		需要解密的文件名
    //			lpszPrivateData		解密私有数据
    //			dwPrivateDataLen	解密私有数据大小
    //返回值:	解密后的数据缓存区长度,采用New 分配
    FS_UINT32	DecryptFileToBuffer(LPCTSTR lpszInFilePath, BYTE** ppOutBuffer, LPCTSTR lpszPrivateData = NULL, FS_UINT32 dwPrivateDatalen = 0);

    //功能:		加密文件
    //参数:		lpszInFilePath		需要加密的文件名
    //			lpszOutFilePath		加密后的文件名
    //			lpszPrivateData		加密私有数据
    //			dwPrivateDataLen	加密私有数据大小
    //返回值:	TRUE				加密成功
    //			FALSE				加密失败	
    BOOL	EncryptFile(LPCTSTR lpszInFilePath, LPCTSTR lpszOutFilePath = NULL, LPCTSTR lpszPrivateData = NULL, FS_UINT32 dwPrivateDatalen = 0);
protected:
    //功能:		解密字符串密钥
    //参数:		szKey				字符串密钥
    //返回值:	解密后的字符串密钥
    char*	DecryptKeyString(char* szKey);
    //功能:		产生随机字符串密钥
    //返回值:	生成的字符串密钥
    char*	GenerateKeyString();
    //功能:		加密字符串密钥
    //参数:		szKey				字符串密钥
    //返回值:	加密后的字符串密钥
    char*	EncryptKeyString(const char* szKey);

    CRandomGenerator	m_rand;		//随机数生成种子
    CRSA				m_rsa;		//RSA加密器		
};
};

#endif // !defined(AFX_FILEENCRYPT_H__400C44A2_31A9_449A_9DE4_0E7D92EA0414__INCLUDED_)
