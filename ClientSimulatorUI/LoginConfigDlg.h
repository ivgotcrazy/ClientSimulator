#pragma once
#include "afxcmn.h"

#include "virtual_client_mgr.h"
#include "afxwin.h"

using namespace clientmgr;

// CLoginConfigDlg 对话框

class CLoginConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginConfigDlg)

public:
	CLoginConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginConfigDlg();

// 对话框数据
	enum { IDD = IDD_DLG_LOGIN_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	LRESULT OnApplyConfig(WPARAM wParam, LPARAM lParam);

private:
	VirtualClientMgrSP m_ClientMgr;

	CEdit m_EditFrontAddr;
	CEdit m_EditRoomId;
	CEdit m_EditRoomPwd;
public:
	CEdit m_EditConcurrentLoginCount;
	CEdit m_EditLoginCountPerSecond;
};
