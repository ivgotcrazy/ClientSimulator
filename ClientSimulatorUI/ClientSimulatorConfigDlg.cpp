// ClientSimulatorConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "ClientSimulatorConfigDlg.h"
#include "afxdialogex.h"
#include "AvConfigDlg.h"
#include "UserConfigDlg.h"
#include "LoginConfigDlg.h"
#include "GeneralConfigDlg.h"


// CClientSimulatorConfigDlg �Ի���

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


// CClientSimulatorConfigDlg ��Ϣ�������
BOOL CClientSimulatorConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cTabConfig.SetParent(this);

	m_cTabConfig.InsertItem(0, _T("ͨ������"));
	m_cTabConfig.InsertItem(1, _T("��¼����"));
	m_cTabConfig.InsertItem(2, _T("����Ƶ����"));
	m_cTabConfig.InsertItem(3, _T("�û�����"));

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
	// ������öԻ���������Ӧ����Ϣ
	for each (CDialogEx* dlg in m_aTabItemDlgs)
	{
		::SendMessage(dlg->GetSafeHwnd(), WM_USER_APPLY_CONFIG, 0, 0);
	}

	GlobalConfigMgr::GetInstance().SerializeConfig();

	EndDialog(IDOK);
}

void CClientSimulatorConfigDlg::OnBnClickedBtnApply()
{
	// ��ǰ����ҳ�Ի���������Ӧ����Ϣ
	::SendMessage(m_aTabItemDlgs[m_nTabCurSel]->GetSafeHwnd(), WM_USER_APPLY_CONFIG, 0, 0);

	// ����Ӧ�ú�����д�������ļ�
	GlobalConfigMgr::GetInstance().SerializeConfig();
}

void CClientSimulatorConfigDlg::OnBnClickedBtnCancel()
{
	EndDialog(IDCANCEL);
}
