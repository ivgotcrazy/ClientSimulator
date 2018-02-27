#pragma once
#include "afxcmn.h"

#include "define.h"
#include "GridCtrl.h"
#include "virtual_client_mgr.h"

using namespace clientmgr;
using namespace gridctrl;

// CClientSimulatorConfigDlg �Ի���

class CClientSimulatorConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientSimulatorConfigDlg)

public:
	CClientSimulatorConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClientSimulatorConfigDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIG };

public:
	afx_msg void OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnEnChangeEditAvDevCount();
	afx_msg void OnEnKillfocusEditAvDevCount();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	VirtualClientMgrSP m_ClientMgr;

	CTabCtrl m_cTabConfig;
	CRect m_cTabClientRect;

	// Tab�ؼ�ҳ���ϵĴ���
	CDialogEx* m_aTabItemDlgs[4];

	// ��ǰѡ���Tabҳ
	unsigned int m_nTabCurSel;
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();
};
