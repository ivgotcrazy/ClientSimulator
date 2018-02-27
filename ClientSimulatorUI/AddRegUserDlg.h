#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CAddRegUserDlg 对话框

class CAddRegUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddRegUserDlg)

public:
	CAddRegUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddRegUserDlg();

	CString GetInputUserName();
	CString GetInputUserPwd();
	int GetInputVideoCount();

// 对话框数据
	enum { IDD = IDD_DLG_ADD_REG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CString m_strUserName;
	CString m_strUserPwd;
	int m_nVideoCount;

public:
	afx_msg void OnEnKillfocusEditInputUserName();
	afx_msg void OnEnKillfocusEditInputUserPwd();
	afx_msg void OnEnKillfocusEditInputVideoCount();
	CButton m_CheckUseDefaultVideoCount;
	afx_msg void OnBnClickedCheckUseDefaultVideoCount();
};
