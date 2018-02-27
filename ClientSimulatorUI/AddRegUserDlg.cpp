/*##############################################################################
* 文件：AddRegUserDlg.cpp
* 描述：CAddRegUserDlg实现文件
* 作者：Teck
* 时间：2016年12月04日
* 版权：Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "AddRegUserDlg.h"
#include "afxdialogex.h"
#include "global_config_mgr.h"

using namespace clientmgr;

// CAddRegUserDlg 对话框

IMPLEMENT_DYNAMIC(CAddRegUserDlg, CDialogEx)

CAddRegUserDlg::CAddRegUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddRegUserDlg::IDD, pParent)
	, m_nVideoCount(-1)
{

}

CAddRegUserDlg::~CAddRegUserDlg()
{
}

CString CAddRegUserDlg::GetInputUserName()
{
	return m_strUserName;
}

CString CAddRegUserDlg::GetInputUserPwd()
{
	return m_strUserPwd;
}

int CAddRegUserDlg::GetInputVideoCount()
{
	return m_nVideoCount;
}

void CAddRegUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_USE_DEFAULT_VIDEO_COUNT, m_CheckUseDefaultVideoCount);
}


BEGIN_MESSAGE_MAP(CAddRegUserDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT_INPUT_USER_NAME, &CAddRegUserDlg::OnEnKillfocusEditInputUserName)
	ON_EN_KILLFOCUS(IDC_EDIT_INPUT_USER_PWD, &CAddRegUserDlg::OnEnKillfocusEditInputUserPwd)
	ON_EN_KILLFOCUS(IDC_EDIT_INPUT_VIDEO_COUNT, &CAddRegUserDlg::OnEnKillfocusEditInputVideoCount)
	ON_BN_CLICKED(IDC_CHECK_USE_DEFAULT_VIDEO_COUNT, &CAddRegUserDlg::OnBnClickedCheckUseDefaultVideoCount)
END_MESSAGE_MAP()


// CAddRegUserDlg 消息处理程序

BOOL CAddRegUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 默认不选中
	m_CheckUseDefaultVideoCount.SetCheck(0);

	// 使用默认视频个数
	GetDlgItem(IDC_EDIT_INPUT_VIDEO_COUNT)->EnableWindow(FALSE);

	// 显示默认视频个数
	const GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	CString str;
	str.Format(_T("%u"), config.common_info.video_count);
	GetDlgItem(IDC_EDIT_INPUT_VIDEO_COUNT)->SetWindowTextW(str);

	return TRUE;
}

void CAddRegUserDlg::OnEnKillfocusEditInputUserName()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_EDIT_INPUT_USER_NAME)->GetWindowTextW(m_strUserName);
}


void CAddRegUserDlg::OnEnKillfocusEditInputUserPwd()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_EDIT_INPUT_USER_PWD)->GetWindowTextW(m_strUserPwd);
}


void CAddRegUserDlg::OnEnKillfocusEditInputVideoCount()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_INPUT_VIDEO_COUNT)->GetWindowTextW(str);

	if (!str.IsEmpty())
		m_nVideoCount = _ttoi(str);
}


void CAddRegUserDlg::OnBnClickedCheckUseDefaultVideoCount()
{
	if (m_CheckUseDefaultVideoCount.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT_INPUT_VIDEO_COUNT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_INPUT_VIDEO_COUNT)->EnableWindow(FALSE);
	}
}
