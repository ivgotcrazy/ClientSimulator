// UserConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "UserConfigDlg.h"
#include "afxdialogex.h"
#include "AddRegUserDlg.h"
#include "AddUnRegUserDlg.h"
#include "global_config_mgr.h"


#define REG_USER_TITLE_INDEX_WIDTH 43
#define REG_USER_TITLE_COLUMN_WIDTH 136

#define UN_REG_USER_TITLE_INDEX_WIDTH 40
#define UN_REG_USER_TITLE_COLUMN_WIDTH (REG_USER_TITLE_COLUMN_WIDTH + 35)

// CUserConfigDlg �Ի���

IMPLEMENT_DYNAMIC(CUserConfigDlg, CDialogEx)

CUserConfigDlg::CUserConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserConfigDlg::IDD, pParent)
	, m_ClientMgr(clientMgr)
	, m_RegisterGrid(1, 4, 1, 1)
	, m_UnRegisterGrid(1, 2, 1, 1)
	, m_nFixedRowHeight(20)
	, m_nRowHeight(20)
	, m_TitleRowColor(RGB(49, 192, 236))
	, m_nRegUserCount(0)
	, m_nUnRegUserCount(0)
{

}

CUserConfigDlg::~CUserConfigDlg()
{
}

void CUserConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_REG_USER, m_RegisterGrid);
	DDX_Control(pDX, IDC_GRID_UNREG_USER, m_UnRegisterGrid);
}


BEGIN_MESSAGE_MAP(CUserConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_REG_USER, &CUserConfigDlg::OnBnClickedBtnAddRegUser)
	ON_BN_CLICKED(IDC_BTN_DEL_REG_USER, &CUserConfigDlg::OnBnClickedBtnDelRegUser)
	ON_BN_CLICKED(IDC_BTN_CLR_REG_USER, &CUserConfigDlg::OnBnClickedBtnClrRegUser)
	ON_BN_CLICKED(IDC_BTN_ADD_UNREG_USER, &CUserConfigDlg::OnBnClickedBtnAddUnregUser)
	ON_BN_CLICKED(IDC_BTN_DEL_UNREG_USER, &CUserConfigDlg::OnBnClickedBtnDelUnregUser)
	ON_BN_CLICKED(IDC_BTN_CLR_UNREG_USER, &CUserConfigDlg::OnBnClickedBtnClrUnregUser)
	ON_BN_CLICKED(IDC_BTN_CLR_BATCH_ADD_INFO, &CUserConfigDlg::OnBnClickedBtnClrBatchAddInfo)
	ON_BN_CLICKED(IDC_BTN_BATCH_ADD, &CUserConfigDlg::OnBnClickedBtnBatchAdd)
	ON_MESSAGE(WM_USER_APPLY_CONFIG, OnApplyConfig)
END_MESSAGE_MAP()


// CUserConfigDlg ��Ϣ�������

BOOL CUserConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitRegisterGrid();

	InitUnRegisterGrid();

	RefreshUserCountStats();

	return TRUE;
}

void CUserConfigDlg::RefreshUserCountStats()
{
	CString str;
	str.Format(_T("%u"), GlobalConfigMgr::GetInstance().GetGlobalConfig().users.size());
	GetDlgItem(IDC_STATIC_CFG_TOTAL_USER_COUNT)->SetWindowTextW(str);

	str.Format(_T("%u"), m_nRegUserCount);
	GetDlgItem(IDC_STATIC_CFG_REG_USER_COUNT)->SetWindowTextW(str);

	str.Format(_T("%u"), m_nUnRegUserCount);
	GetDlgItem(IDC_STATIC_CFG_UNREG_USER_COUNT)->SetWindowTextW(str);
}

void CUserConfigDlg::InitRegisterGrid()
{
	CRect rect;
	GetClientRect(&rect);

	rect.top += 75;
	rect.right *= 0.73;
	rect.bottom = rect.bottom / 2 - 30;
	rect.left += 20;

	m_RegisterGrid.Create(rect, this, IDC_GRID_REG_USER);

	// ��������
	m_RegisterGrid.SetEditable(TRUE);
	m_RegisterGrid.EnableDragAndDrop(TRUE);
	m_RegisterGrid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xFF));
	m_RegisterGrid.SetFixedColumnSelection(TRUE);
	m_RegisterGrid.SetFixedRowSelection(TRUE);
	m_RegisterGrid.EnableColumnHide();
	m_RegisterGrid.AutoSize();

	// ���ñ����е�Ԫ��Ŀ�͸�
	m_RegisterGrid.SetColumnWidth(0, REG_USER_TITLE_INDEX_WIDTH);
	m_RegisterGrid.SetColumnWidth(1, REG_USER_TITLE_COLUMN_WIDTH);
	m_RegisterGrid.SetColumnWidth(2, REG_USER_TITLE_COLUMN_WIDTH);
	m_RegisterGrid.SetColumnWidth(3, REG_USER_TITLE_COLUMN_WIDTH);

	m_RegisterGrid.SetRowHeight(0, m_nFixedRowHeight);

	// ���ñ������ı�
	m_RegisterGrid.GetCell(0, 0)->SetText(_T("���"));
	m_RegisterGrid.GetCell(0, 1)->SetText(_T("�û���"));
	m_RegisterGrid.GetCell(0, 2)->SetText(_T("����"));
	m_RegisterGrid.GetCell(0, 3)->SetText(_T("��Ƶ�豸����"));

	// ���ñ����б���ɫ
	m_RegisterGrid.GetCell(0, 0)->SetBackClr(m_TitleRowColor);
	m_RegisterGrid.GetCell(0, 1)->SetBackClr(m_TitleRowColor);
	m_RegisterGrid.GetCell(0, 2)->SetBackClr(m_TitleRowColor);
	m_RegisterGrid.GetCell(0, 3)->SetBackClr(m_TitleRowColor);

	// ����ע���û�
	for each (UserInfo user in GlobalConfigMgr::GetInstance().GetGlobalConfig().users)
	{
		if (user.user_type == USER_TYPE_REGISTER)
		{
			m_nRegUserCount++;

			CString str;
			str.Format(_T("%d"), m_nRegUserCount);
			m_RegisterGrid.InsertRow(str);

			m_RegisterGrid.GetCell(m_nRegUserCount, 1)->SetText(user.user_name.c_str());

			USES_CONVERSION;
			m_RegisterGrid.GetCell(m_nRegUserCount, 2)->SetText(A2T(user.user_pwd.c_str()));

			str.Format(_T("%d"), user.video_count);
			m_RegisterGrid.GetCell(m_nRegUserCount, 3)->SetText(str);
		}
	}
}

void CUserConfigDlg::InitUnRegisterGrid()
{
	CRect rect;
	GetClientRect(&rect);

	rect.top = rect.bottom / 2 + 10;
	rect.right *= 0.39;
	rect.bottom -= 66;
	rect.left += 20;

	m_UnRegisterGrid.Create(rect, this, IDC_GRID_UNREG_USER);

	// ��������
	m_UnRegisterGrid.EnableDragAndDrop(TRUE);
	m_UnRegisterGrid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xFF));
	m_UnRegisterGrid.SetFixedColumnSelection(TRUE);
	m_UnRegisterGrid.SetFixedRowSelection(TRUE);
	m_UnRegisterGrid.EnableColumnHide();
	m_UnRegisterGrid.AutoSize();

	// ���ñ����е�Ԫ��Ŀ�͸�
	m_UnRegisterGrid.SetColumnWidth(0, UN_REG_USER_TITLE_INDEX_WIDTH);
	m_UnRegisterGrid.SetColumnWidth(1, UN_REG_USER_TITLE_COLUMN_WIDTH);

	m_UnRegisterGrid.SetRowHeight(0, m_nFixedRowHeight);

	// ���ñ������ı�
	m_UnRegisterGrid.GetCell(0, 0)->SetText(_T("���"));
	m_UnRegisterGrid.GetCell(0, 1)->SetText(_T("�û��ǳ�"));

	// ���ñ����б���ɫ
	m_UnRegisterGrid.GetCell(0, 0)->SetBackClr(m_TitleRowColor);
	m_UnRegisterGrid.GetCell(0, 1)->SetBackClr(m_TitleRowColor);

	// ���������û�
	for each (UserInfo user in GlobalConfigMgr::GetInstance().GetGlobalConfig().users)
	{
		if (user.user_type == USER_TYPE_UNREGISTER)
		{
			m_nUnRegUserCount++;

			CString str;
			str.Format(_T("%d"), m_nUnRegUserCount);
			m_UnRegisterGrid.InsertRow(str);

			m_UnRegisterGrid.GetCell(m_nUnRegUserCount, 1)->SetText(user.user_name.c_str());
		}
	}
}

void CUserConfigDlg::OnBnClickedBtnAddRegUser()
{
	CAddRegUserDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{		
		if (dlg.GetInputUserName().IsEmpty())
		{
			MessageBox(_T("�û����Ʋ���Ϊ��!"), _T("����"));
			return;
		}

		int nVideoCount = dlg.GetInputVideoCount();
		if (nVideoCount < -1 || nVideoCount > 6)
		{
			MessageBox(_T("��Ƶ�豸����������[0, 6]��Χ!"), _T("����"));
			return;
		}
		else if (nVideoCount == -1) // ʹ��Ĭ������
		{
			const GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();
			nVideoCount = config.common_info.video_count;
		}

		m_nRegUserCount++;

		CString str;
		str.Format(_T("%u"), m_nRegUserCount);
		m_RegisterGrid.InsertRow(str);

		m_RegisterGrid.GetCell(m_nRegUserCount, 1)->SetText(dlg.GetInputUserName());

		USES_CONVERSION;
		m_RegisterGrid.GetCell(m_nRegUserCount, 2)->SetText(dlg.GetInputUserPwd());

		str.Format(_T("%d"), nVideoCount);
		m_RegisterGrid.GetCell(m_nRegUserCount, 3)->SetText(str);

		m_RegisterGrid.Invalidate();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
}


void CUserConfigDlg::OnBnClickedBtnDelRegUser()
{
	CCellRange range = m_RegisterGrid.GetSelectedCellRange();
	for (int i = range.GetMinRow(); i <= range.GetMaxRow(); i++)
	{
		m_RegisterGrid.DeleteRow(i);
		m_nRegUserCount--;
	}

	m_RegisterGrid.Invalidate();
}


void CUserConfigDlg::OnBnClickedBtnClrRegUser()
{
	m_nRegUserCount = 0;

	m_RegisterGrid.DeleteNonFixedRows();

	m_RegisterGrid.Invalidate();
}


void CUserConfigDlg::OnBnClickedBtnAddUnregUser()
{
	CAddUnRegUserDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// �ǳƲ���Ϊ��
		if (dlg.GetUserNickName().IsEmpty())
		{
			MessageBox(_T("�û����Ʋ���Ϊ��!"), _T("����"));
			return;
		}

		// �ǳƲ����ظ�
		for each (UserInfo user in GlobalConfigMgr::GetInstance().GetGlobalConfig().users)
		{
			if (user.user_type == USER_TYPE_UNREGISTER
				&& user.user_name.c_str() == dlg.GetUserNickName())
			{
				CString str;
				str.Format(_T("�û��ǳ�%s�Ѵ��ڣ�"), dlg.GetUserNickName());
				MessageBox(str, _T("����"));
				return;
			}
		}

		m_nUnRegUserCount++;

		CString str;
		str.Format(_T("%u"), m_nUnRegUserCount);
		m_UnRegisterGrid.InsertRow(str);

		m_UnRegisterGrid.GetCell(m_nUnRegUserCount, 1)->SetText(dlg.GetUserNickName());

		m_UnRegisterGrid.Invalidate();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
}

void CUserConfigDlg::OnBnClickedBtnDelUnregUser()
{
	CCellRange range = m_UnRegisterGrid.GetSelectedCellRange();
	for (int i = range.GetMinRow(); i <= range.GetMaxRow(); i++)
	{
		m_UnRegisterGrid.DeleteRow(i);
		m_nUnRegUserCount--;
	}

	m_UnRegisterGrid.Invalidate();
}


void CUserConfigDlg::OnBnClickedBtnClrUnregUser()
{
	m_nUnRegUserCount = 0;

	m_UnRegisterGrid.DeleteNonFixedRows();

	m_UnRegisterGrid.Invalidate();
}

void CUserConfigDlg::OnBnClickedBtnClrBatchAddInfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_EDIT_BATCH_ADD_NICK_PREFIX)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_BATCH_ADD_NICK_POSTFIX_NUM_BEGIN)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_BATCH_ADD_NICK_POSTFIX_NUM_END)->SetWindowTextW(_T(""));
}

void CUserConfigDlg::OnBnClickedBtnBatchAdd()
{
	CString str;

	GetDlgItemTextW(IDC_EDIT_BATCH_ADD_NICK_POSTFIX_NUM_BEGIN, str);
	int nNumBegin = _ttoi(str);

	GetDlgItemTextW(IDC_EDIT_BATCH_ADD_NICK_POSTFIX_NUM_END, str);
	int nNumEnd = _ttoi(str);

	CString strPrefix;
	GetDlgItemTextW(IDC_EDIT_BATCH_ADD_NICK_PREFIX, strPrefix);

	if (nNumBegin < 0)
	{
		MessageBox(_T("�û��ǳƺ�׺��ʼ��Ų���Ϊ����!"), _T("����"));
		return;
	}
	else if (nNumBegin > nNumEnd)
	{
		MessageBox(_T("�û��ǳƺ�׺��ʼ��Ų��ܴ�����ֹ���!"), _T("����"));
		return;
	}

	for (int i = nNumBegin; i <= nNumEnd; i++)
	{
		m_nUnRegUserCount++;

		CString strNickName;
		strNickName.Format(_T("%s%d"), strPrefix, i);

		CString strUserNum;
		strUserNum.Format(_T("%u"), m_nUnRegUserCount);
		m_UnRegisterGrid.InsertRow(strUserNum);

		m_UnRegisterGrid.GetCell(m_nUnRegUserCount, 1)->SetText(strNickName);
	}

	m_UnRegisterGrid.Invalidate();
}

LRESULT CUserConfigDlg::OnApplyConfig(WPARAM wParam, LPARAM lParam)
{
	USES_CONVERSION;

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	// ����������û�
	config.users.clear();
	
	// ע���û�������������
	for (int i = 1; i < m_RegisterGrid.GetRowCount(); i++)
	{
		UserInfo user;

		user.user_name = m_RegisterGrid.GetCell(i, 1)->GetText();
		user.user_pwd = T2A(m_RegisterGrid.GetCell(i, 2)->GetText());
		user.user_type = USER_TYPE_REGISTER;
		user.video_count = _ttoi(m_RegisterGrid.GetCell(i, 3)->GetText());
		user.if_recv_av = config.common_info.if_recv_av;
		
		config.users.push_back(user);
	}

	// ˢ��ע���û���
	

	// �����û�
	for (int i = 1; i < m_UnRegisterGrid.GetRowCount(); i++)
	{
		UserInfo user;

		user.user_name = m_UnRegisterGrid.GetCell(i, 1)->GetText();
		user.user_pwd = "";
		user.user_type = USER_TYPE_UNREGISTER;
		user.video_count = 0;
		user.if_recv_av = config.common_info.if_recv_av;

		config.users.push_back(user);
	}

	return 0;
}