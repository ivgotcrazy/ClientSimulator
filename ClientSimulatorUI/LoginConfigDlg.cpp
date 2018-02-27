// LoginConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "LoginConfigDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>

// CLoginConfigDlg 对话框

IMPLEMENT_DYNAMIC(CLoginConfigDlg, CDialogEx)

CLoginConfigDlg::CLoginConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginConfigDlg::IDD, pParent)
	, m_ClientMgr(clientMgr)
{

}

CLoginConfigDlg::~CLoginConfigDlg()
{
}

void CLoginConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FRONT_ADDR, m_EditFrontAddr);
	DDX_Control(pDX, IDC_EDIT_ROOM_ID, m_EditRoomId);
	DDX_Control(pDX, IDC_EDIT_ROOM_PWD, m_EditRoomPwd);
	DDX_Control(pDX, IDC_EDIT_CONCURRENT_LOGIN_USER_COUNT, m_EditConcurrentLoginCount);
	DDX_Control(pDX, IDC_EDIT_LOGIN_USER_COUNT_PER_SECOND, m_EditLoginCountPerSecond);
}


BEGIN_MESSAGE_MAP(CLoginConfigDlg, CDialogEx)
	ON_MESSAGE(WM_USER_APPLY_CONFIG, OnApplyConfig)
END_MESSAGE_MAP()


// CLoginConfigDlg 消息处理程序
BOOL CLoginConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	CString str;
	USES_CONVERSION;

	str.Format(_T("%s"), A2T(config.common_info.front_addr.c_str()));
	m_EditFrontAddr.SetWindowTextW(str);

	str.Format(_T("%d"), config.common_info.room_id);
	m_EditRoomId.SetWindowTextW(str);

	str.Format(_T("%s"), A2T(config.common_info.room_pwd.c_str()));
	m_EditRoomPwd.SetWindowTextW(str);

	str.Format(_T("%d"), config.login_param.concurrent_login_count);
	m_EditConcurrentLoginCount.SetWindowTextW(str);

	str.Format(_T("%d"), config.login_param.login_count_per_second);
	m_EditLoginCountPerSecond.SetWindowTextW(str);

	return TRUE;
}

LRESULT CLoginConfigDlg::OnApplyConfig(WPARAM wParam, LPARAM lParam)
{
	USES_CONVERSION;

	CString str;

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	m_EditFrontAddr.GetWindowTextW(str);
	config.common_info.front_addr = T2A(str);

	m_EditRoomId.GetWindowTextW(str);
	config.common_info.room_id = _ttoi(str);

	m_EditRoomPwd.GetWindowTextW(str);
	config.common_info.room_pwd = T2A(str);

	m_EditConcurrentLoginCount.GetWindowTextW(str);
	config.login_param.concurrent_login_count = _ttoi(str);

	m_EditLoginCountPerSecond.GetWindowTextW(str);
	config.login_param.login_count_per_second = _ttoi(str);

	return 0;
}