#pragma once
#include "afxcmn.h"

// CAddUnRegUserDlg �Ի���

class CAddUnRegUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUnRegUserDlg)

public:
	CAddUnRegUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddUnRegUserDlg();

// �Ի�������
	enum { IDD = IDD_DLG_ADD_UNREG_USER };

	CString GetUserNickName();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CString m_strNickName;
public:
	afx_msg void OnEnKillfocusEditInputUnregUserName();
};
