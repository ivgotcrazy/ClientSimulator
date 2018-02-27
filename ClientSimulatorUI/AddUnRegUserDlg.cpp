// AddUnRegUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "AddUnRegUserDlg.h"
#include "afxdialogex.h"


// CAddUnRegUserDlg �Ի���

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


// CAddUnRegUserDlg ��Ϣ�������


void CAddUnRegUserDlg::OnEnKillfocusEditInputUnregUserName()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_EDIT_INPUT_UNREG_USER_NAME)->GetWindowTextW(m_strNickName);
}
