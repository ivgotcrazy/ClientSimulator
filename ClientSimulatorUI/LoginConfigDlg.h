#pragma once
#include "afxcmn.h"

#include "virtual_client_mgr.h"
#include "afxwin.h"

using namespace clientmgr;

// CLoginConfigDlg �Ի���

class CLoginConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginConfigDlg)

public:
	CLoginConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginConfigDlg();

// �Ի�������
	enum { IDD = IDD_DLG_LOGIN_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
