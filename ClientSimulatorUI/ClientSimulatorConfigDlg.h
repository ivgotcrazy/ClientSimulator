#pragma once
#include "afxcmn.h"

#include "define.h"
#include "GridCtrl.h"
#include "virtual_client_mgr.h"

using namespace clientmgr;
using namespace gridctrl;

// CClientSimulatorConfigDlg 对话框

class CClientSimulatorConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientSimulatorConfigDlg)

public:
	CClientSimulatorConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientSimulatorConfigDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONFIG };

public:
	afx_msg void OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnEnChangeEditAvDevCount();
	afx_msg void OnEnKillfocusEditAvDevCount();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	VirtualClientMgrSP m_ClientMgr;

	CTabCtrl m_cTabConfig;
	CRect m_cTabClientRect;

	// Tab控件页面上的窗口
	CDialogEx* m_aTabItemDlgs[4];

	// 当前选择的Tab页
	unsigned int m_nTabCurSel;
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();
};
