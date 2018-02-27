#pragma once
#include "afxcmn.h"

#include "virtual_client_mgr.h"
#include "GridCtrl.h"

using namespace clientmgr;
using namespace gridctrl;

// CUserConfigDlg �Ի���

class CUserConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserConfigDlg)

public:
	CUserConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserConfigDlg();

// �Ի�������
	enum { IDD = IDD_DLG_USER_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	void InitRegisterGrid();
	void InitUnRegisterGrid();
	void RefreshUserCountStats();
	LRESULT OnApplyConfig(WPARAM wParam, LPARAM lParam);

private:
	VirtualClientMgrSP m_ClientMgr;

	CGridCtrl m_RegisterGrid;
	CGridCtrl m_UnRegisterGrid;

	FS_UINT32 m_nFixedRowHeight;
	FS_UINT32 m_nRowHeight;
	COLORREF  m_TitleRowColor;

	FS_UINT32 m_nRegUserCount;
	FS_UINT32 m_nUnRegUserCount;
	
public:
	afx_msg void OnBnClickedBtnAddRegUser();
	afx_msg void OnBnClickedBtnDelRegUser();
	afx_msg void OnBnClickedBtnClrRegUser();
	afx_msg void OnBnClickedBtnAddUnregUser();
	afx_msg void OnBnClickedBtnDelUnregUser();
	afx_msg void OnBnClickedBtnClrUnregUser();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBtnClrBatchAddInfo();
	afx_msg void OnBnClickedBtnBatchAdd();
};
