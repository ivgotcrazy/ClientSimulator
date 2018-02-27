#pragma once
#include "afxcmn.h"

// CAddUnRegUserDlg 对话框

class CAddUnRegUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUnRegUserDlg)

public:
	CAddUnRegUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUnRegUserDlg();

// 对话框数据
	enum { IDD = IDD_DLG_ADD_UNREG_USER };

	CString GetUserNickName();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CString m_strNickName;
public:
	afx_msg void OnEnKillfocusEditInputUnregUserName();
};
