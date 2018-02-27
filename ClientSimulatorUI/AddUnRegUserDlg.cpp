// AddUnRegUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "AddUnRegUserDlg.h"
#include "afxdialogex.h"


// CAddUnRegUserDlg 对话框

IMPLEMENT_DYNAMIC(CAddUnRegUserDlg, CDialogEx)

CAddUnRegUserDlg::CAddUnRegUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddUnRegUserDlg::IDD, pParent)
{

}

CAddUnRegUserDlg::~CAddUnRegUserDlg()
{
}

void CAddUnRegUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

CString CAddUnRegUserDlg::GetUserNickName()
{
	return m_strNickName;
}

BEGIN_MESSAGE_MAP(CAddUnRegUserDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT_INPUT_UNREG_USER_NAME, &CAddUnRegUserDlg::OnEnKillfocusEditInputUnregUserName)
END_MESSAGE_MAP()


// CAddUnRegUserDlg 消息处理程序


void CAddUnRegUserDlg::OnEnKillfocusEditInputUnregUserName()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_EDIT_INPUT_UNREG_USER_NAME)->GetWindowTextW(m_strNickName);
}
