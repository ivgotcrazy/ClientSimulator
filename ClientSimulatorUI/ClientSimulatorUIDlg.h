
// ClientSimulatorUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "virtual_client_mgr.h"

using namespace clientmgr;

// CClientSimulatorUIDlg �Ի���
class CClientSimulatorUIDlg 
	: public CDialogEx
	, public CommonMsgProcessor
	, public std::enable_shared_from_this<CClientSimulatorUIDlg>
{
// ����
public:
	CClientSimulatorUIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CClientSimulatorUIDlg();

// �Ի�������
	enum { IDD = IDD_CLIENTSIMULATORUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedBtnStart();

// ʵ��
protected:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnConfig();
	afx_msg void OnBnClickedBtnQuit();
	DECLARE_MESSAGE_MAP()

private:
	bool InitClientMgr();
	bool OnStateStart(const MsgData& msg_data);
	bool OnHasNoVideoDev(const MsgData& msg_data);
	bool OnLoginResultMsg(const MsgData& msg_data);
	bool OnAppRunErrMsg(const MsgData& msg_data);
	void InitGeneralConfig();
	void InitVideoParam();
	void InitRuntimeInfo();
	void StatLoginTime();
	void RestartSelf();

private:
	HICON m_hIcon;
	CBrush m_cDisplayBrush;
	
	VirtualClientMgrSP m_cClientMgr;
	
	std::wstring m_strDisplay;
	std::mutex m_mtxDisplay;

	// ��Ҫ������Ϣ
	CStatic m_cStaticFrontAddr;
	CStatic m_cStaticTotalUserCount;
	CStatic m_cStaticAnonymousUserCount;
	CStatic m_cStaticRegisterUserCount;
	CStatic m_cStaticIfRecvAv;
	CStatic m_cStaticVideoDevCount;

	// ��Ƶ������Ϣ
	CStatic m_cStaticVideoWidth;
	CStatic m_cStaticVideoHeight;
	CStatic m_cStaticVideoFrameRate;
	CStatic m_cStaticVideoBitRate;

	// ����ͳ����Ϣ
	CStatic m_cLoginSuccessCount;
	CStatic m_cStaticUnloginUserCount;
	CStatic m_cStaticLoginingUserCount;
	CStatic m_cStaticLoginFailUserCount;
	CStatic m_cStaticAverLoginTime;
	CStatic m_cStaticLoginLongest;
	CStatic m_cStaticStartLoginTime;
	CStatic m_cStaticLoginTotalTime;

	FS_UINT32 m_nUnLoginUserCount;
	FS_UINT32 m_nLoginingUserCount;
	FS_UINT32 m_nLoginSuccessUserCount;
	FS_UINT32 m_nLoginFailUserCount;
	FS_UINT32 m_nAverLoginTime;
	FS_UINT32 m_nLoginLongestTime;
	FS_UINT32 m_nStartLoginTime;
	FS_UINT32 m_nTotalLoginTime;

	bool m_bStatOK;

	// ��¼��Ϣ��ʾ��
	CEdit m_cEditDisplayer;

	std::mutex m_mtxLoginResult;
	std::vector<UserLoginResultMsgSP> m_vecLoginResult;

	enum StartBtnState
	{
		START_BTN_STATE_START,
		START_BTN_STATE_STOP,
		START_BTN_STATE_RESTART
	};

	StartBtnState m_eStartBtnState;
};
