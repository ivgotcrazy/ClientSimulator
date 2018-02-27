#pragma once
#include "afxcmn.h"

#include "virtual_client_mgr.h"
#include "afxwin.h"

using namespace clientmgr;

// CGeneralConfigDlg 对话框

class CGeneralConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGeneralConfigDlg)

public:
	CGeneralConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGeneralConfigDlg();

// 对话框数据
	enum { IDD = IDD_DLG_GENERAL_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	LRESULT OnApplyConfig(WPARAM wParam, LPARAM lParam);

private:
	VirtualClientMgrSP m_ClientMgr;

	CEdit m_EditFrontAppId;
	CEdit m_EditProductId;
	CEdit m_EditClientMode;
	CEdit m_EditTerminalType;
	CEdit m_EditRoomAppId;
	CEdit m_EditClientVersion;
	CEdit m_EditClientType;
};
