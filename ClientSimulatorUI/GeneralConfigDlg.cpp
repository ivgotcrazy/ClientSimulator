// GeneralConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "GeneralConfigDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>


// CGeneralConfigDlg 对话框

IMPLEMENT_DYNAMIC(CGeneralConfigDlg, CDialogEx)

CGeneralConfigDlg::CGeneralConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent /*=NULL*/)
	: CDialogEx(CGeneralConfigDlg::IDD, pParent)
	, m_ClientMgr(clientMgr)
{

}

CGeneralConfigDlg::~CGeneralConfigDlg()
{
}

void CGeneralConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FRONT_APP_ID, m_EditFrontAppId);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_ID, m_EditProductId);
	DDX_Control(pDX, IDC_EDIT_CLIENT_MODE, m_EditClientMode);
	DDX_Control(pDX, IDC_EDIT_TERMINAL_TYPE, m_EditTerminalType);
	DDX_Control(pDX, IDC_EDIT_ROOM_APP_ID, m_EditRoomAppId);
	DDX_Control(pDX, IDC_EDIT_CLIENT_VERSION, m_EditClientVersion);
	DDX_Control(pDX, IDC_EDIT_CLIENT_TYPE, m_EditClientType);
}


BEGIN_MESSAGE_MAP(CGeneralConfigDlg, CDialogEx)
	ON_MESSAGE(WM_USER_APPLY_CONFIG, OnApplyConfig)
END_MESSAGE_MAP()


// CGeneralConfigDlg 消息处理程序

BOOL CGeneralConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	CString str;
	USES_CONVERSION;

	str.Format(_T("%d"), config.common_info.front_app_id);
	m_EditFrontAppId.SetWindowTextW(str);

	str.Format(_T("%s"), A2T(config.common_info.product_id.c_str()));
	m_EditProductId.SetWindowTextW(str);

	str.Format(_T("%d"), config.common_info.client_mode);
	m_EditClientMode.SetWindowTextW(str);

	str.Format(_T("%d"), config.common_info.terminal_type);
	m_EditTerminalType.SetWindowTextW(str);

	str.Format(_T("%d"), config.common_info.room_app_id);
	m_EditRoomAppId.SetWindowTextW(str);

	str.Format(_T("%s"), A2T(config.common_info.client_ver.c_str()));
	m_EditClientVersion.SetWindowTextW(str);

	str.Format(_T("%d"), config.common_info.client_type);
	m_EditClientType.SetWindowTextW(str);

	return TRUE;
}

LRESULT CGeneralConfigDlg::OnApplyConfig(WPARAM wParam, LPARAM lParam)
{
	CString str;
	USES_CONVERSION;

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	m_EditFrontAppId.GetWindowTextW(str);
	config.common_info.front_app_id = _ttoi(str);
	
	m_EditProductId.GetWindowTextW(str);
	config.common_info.product_id = T2A(str.GetString());

	m_EditClientMode.GetWindowTextW(str);
	config.common_info.client_mode = static_cast<ClientMode>(_ttoi(str));

	m_EditTerminalType.GetWindowTextW(str);
	config.common_info.terminal_type = static_cast<TerminalType>(_ttoi(str));

	m_EditRoomAppId.GetWindowTextW(str);
	config.common_info.room_app_id = _ttoi(str);

	m_EditClientVersion.GetWindowTextW(str);
	config.common_info.client_ver = T2A(str.GetString());

	m_EditClientType.GetWindowTextW(str);
	config.common_info.client_type = static_cast<ClientType>(_ttoi(str));

	return 0;
}