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
 *	����:		CFileEncrypt
 *	����:		���ļ����мӽ���,�Լ�������ܺ���ļ���С
 */
#include "rsa.h"

namespace WBASELIB
{

class CFileEncrypt
{
public:
    CFileEncrypt();
    virtual ~CFileEncrypt();

    //����:		������ܺ���ļ���С,�����ļ������м���
    //����:		lpszInFilePath		��Ҫ���ܵ��ļ���
    //			lpszOutFilePath		���ܺ���ļ���
    //			dwPrivateDataLen	����˽�����ݴ�С
    //����ֵ:	���ؼ��ܺ���ļ���С
    FS_UINT32	DetectEncryptFileSize(LPCTSTR lpszInFilePath, LPCTSTR lpszOutFilePath, FS_UINT32 dwPrivateDataLen = 0);

    //����:		�����ļ�
    //����:		lpszInFilePath		��Ҫ���ܵ��ļ���
    //			lpszOutFilePath		���ܺ���ļ���
    //			lpszPrivateData		����˽������
    //			dwPrivateDataLen	����˽�����ݴ�С
    //����ֵ:	TRUE				���ܳɹ�
    //			FALSE				����ʧ��
    BOOL	DecryptFile(LPCTSTR lpszInFilePath, LPCTSTR lpszOutFilePath = NULL, LPCTSTR lpszPrivateData = NULL, FS_UINT32 dwPrivateDatalen = 0);

    //����:		�����ļ�
    //����:		lpszInFilePath		��Ҫ���ܵ��ļ���
    //			lpszPrivateData		����˽������
    //			dwPrivateDataLen	����˽�����ݴ�С
    //����ֵ:	���ܺ�����ݻ���������,����New ����
    FS_UINT32	DecryptFileToBuffer(LPCTSTR lpszInFilePath, BYTE** ppOutBuffer, LPCTSTR lpszPrivateData = NULL, FS_UINT32 dwPrivateDatalen = 0);

    //����:		�����ļ�
    //����:		lpszInFilePath		��Ҫ���ܵ��ļ���
    //			lpszOutFilePath		���ܺ���ļ���
    //			lpszPrivateData		����˽������
    //			dwPrivateDataLen	����˽�����ݴ�С
    //����ֵ:	TRUE				���ܳɹ�
    //			FALSE				����ʧ��	
    BOOL	EncryptFile(LPCTSTR lpszInFilePath, LPCTSTR lpszOutFilePath = NULL, LPCTSTR lpszPrivateData = NULL, FS_UINT32 dwPrivateDatalen = 0);
protected:
    //����:		�����ַ�����Կ
    //����:		szKey				�ַ�����Կ
    //����ֵ:	���ܺ���ַ�����Կ
    char*	DecryptKeyString(char* szKey);
    //����:		��������ַ�����Կ
    //����ֵ:	���ɵ��ַ�����Կ
    char*	GenerateKeyString();
    //����:		�����ַ�����Կ
    //����:		szKey				�ַ�����Կ
    //����ֵ:	���ܺ���ַ�����Կ
    char*	EncryptKeyString(const char* szKey);

    CRandomGenerator	m_rand;		//�������������
    CRSA				m_rsa;		//RSA������		
};
};

#endif // !defined(AFX_FILEENCRYPT_H__400C44A2_31A9_449A_9DE4_0E7D92EA0414__INCLUDED_)
