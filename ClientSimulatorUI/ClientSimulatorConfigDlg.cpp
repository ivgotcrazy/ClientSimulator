// ClientSimulatorConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "ClientSimulatorConfigDlg.h"
#include "afxdialogex.h"
#include "AvConfigDlg.h"
#include "UserConfigDlg.h"
#include "LoginConfigDlg.h"
#include "GeneralConfigDlg.h"


// CClientSimulatorConfigDlg 对话框

IMPLEMENT_DYNAMIC(CClientSimulatorConfigDlg, CDialogEx)

CClientSimulatorConfigDlg::CClientSimulatorConfigDlg(
	const VirtualClientMgrSP& clientMgr, CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientSimulatorConfigDlg::IDD, pParent)
	, m_ClientMgr(clientMgr)
{
	for each (CDialogEx* dialog in m_aTabItemDlgs)
	{
		dialog = nullptr;
	}
}

CClientSimulatorConfigDlg::~CClientSimulatorConfigDlg()
{
	for each (CDialogEx* dialog in m_aTabItemDlgs)
	{
		if (dialog != nullptr)
			delete dialog;
	}
}

void CClientSimulatorConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CONFIG, m_cTabConfig);
}


BEGIN_MESSAGE_MAP(CClientSimulatorConfigDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONFIG, &CClientSimulatorConfigDlg::OnTcnSelchangeTabConfig)
	ON_BN_CLICKED(ID_BTN_OK, &CClientSimulatorConfigDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CClientSimulatorConfigDlg::OnBnClickedBtnApply)
	ON_BN_CLICKED(ID_BTN_CANCEL, &CClientSimulatorConfigDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CClientSimulatorConfigDlg 消息处理程序
BOOL CClientSimulatorConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cTabConfig.SetParent(this);

	m_cTabConfig.InsertItem(0, _T("通用配置"));
	m_cTabConfig.InsertItem(1, _T("登录配置"));
	m_cTabConfig.InsertItem(2, _T("音视频配置"));
	m_cTabConfig.InsertItem(3, _T("用户配置"));

	m_aTabItemDlgs[0] = new CGeneralConfigDlg(m_ClientMgr);
	m_aTabItemDlgs[0]->Create(IDD_DLG_GENERAL_CONFIG, GetDlgItem(IDC_TAB_CONFIG));

	m_aTabItemDlgs[1] = new CLoginConfigDlg(m_ClientMgr);
	m_aTabItemDlgs[1]->Create(IDD_DLG_LOGIN_CONFIG, GetDlgItem(IDC_TAB_CONFIG));
	
	m_aTabItemDlgs[2] = new CAvConfigDlg(m_ClientMgr);
	m_aTabItemDlgs[2]->Create(IDD_DLG_AV_CONFIG, GetDlgItem(IDC_TAB_CONFIG));
	
	m_aTabItemDlgs[3] = new CUserConfigDlg(m_ClientMgr);
	m_aTabItemDlgs[3]->Create(IDD_DLG_USER_CONFIG, GetDlgItem(IDC_TAB_CONFIG));

	m_cTabConfig.GetClientRect(&m_cTabClientRect);
	m_cTabClientRect.top += 23;
	m_cTabClientRect.bottom -= 4;
	m_cTabClientRect.left += 3;
	m_cTabClientRect.right -= 4;

	m_aTabItemDlgs[0]->MoveWindow(&m_cTabClientRect);
	m_aTabItemDlgs[0]->ShowWindow(SW_SHOW);

	m_nTabCurSel = 0;

	return TRUE;
}

void CClientSimulatorConfigDlg::OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码

	if (m_cTabConfig.GetCurSel() != m_nTabCurSel)
	{
		m_aTabItemDlgs[m_nTabCurSel]->ShowWindow(SW_HIDE);

		m_aTabItemDlgs[m_cTabConfig.GetCurSel()]->MoveWindow(&m_cTabClientRect);
		m_aTabItemDlgs[m_cTabConfig.GetCurSel()]->ShowWindow(SW_SHOW);

		m_nTabCurSel = m_cTabConfig.GetCurSel();
	}

	*pResult = 0;
}

void CClientSimulatorConfigDlg::OnBnClickedBtnOk()
{
	// 向各配置对话框发送配置应用消息
	for each (CDialogEx* dlg in m_aTabItemDlgs)
	{
		::SendMessage(dlg->GetSafeHwnd(), WM_USER_APPLY_CONFIG, 0, 0);
	}

	GlobalConfigMgr::GetInstance().SerializeConfig();

	EndDialog(IDOK);
}

void CClientSimulatorConfigDlg::OnBnClickedBtnApply()
{
	// 向当前配置页对话框发送配置应用消息
	::SendMessage(m_aTabItemDlgs[m_nTabCurSel]->GetSafeHwnd(), WM_USER_APPLY_CONFIG, 0, 0);

	// 配置应用后立即写入配置文件
	GlobalConfigMgr::GetInstance().SerializeConfig();
}

void CClientSimulatorConfigDlg::OnBnClickedBtnCancel()
{
	EndDialog(IDCANCEL);
}
