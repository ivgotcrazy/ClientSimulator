// ClientSimulatorUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "ClientSimulatorUIDlg.h"
#include "afxdialogex.h"
#include "frameworksdk.h"
#include "ClientSimulatorConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_USER_NOTIFY_MSG	(WM_USER + 1)


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientSimulatorUIDlg 对话框



CClientSimulatorUIDlg::CClientSimulatorUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientSimulatorUIDlg::IDD, pParent)
	, m_nUnLoginUserCount(0)
	, m_nLoginingUserCount(0)
	, m_nLoginSuccessUserCount(0)
	, m_nLoginFailUserCount(0)
	, m_nAverLoginTime(0)
	, m_nLoginLongestTime(0)
	, m_nStartLoginTime(0)
	, m_nTotalLoginTime(0)
	, m_bStatOK(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClientSimulatorUIDlg::~CClientSimulatorUIDlg()
{
	m_cClientMgr->Stop();

	//m_cClientMgr.reset();
	FWReleaseFrameWork();
}

void CClientSimulatorUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LOGIN_SUCCESS, m_cLoginSuccessCount);
	DDX_Control(pDX, IDC_STATIC_FRONT_ADDR, m_cStaticFrontAddr);
	DDX_Control(pDX, IDC_STATIC_TOTAL_USER_COUNT, m_cStaticTotalUserCount);
	DDX_Control(pDX, IDC_STATIC_ANONYMOUS_USER_COUNT, m_cStaticAnonymousUserCount);
	DDX_Control(pDX, IDC_STATIC_REGISTER_USER_COUNT, m_cStaticRegisterUserCount);
	DDX_Control(pDX, IDC_STATIC_IF_RECV_AV, m_cStaticIfRecvAv);
	DDX_Control(pDX, IDC_STATIC_VIDEO_DEV_COUNT, m_cStaticVideoDevCount);
	DDX_Control(pDX, IDC_STATIC_VIDEO_WIDTH, m_cStaticVideoWidth);
	DDX_Control(pDX, IDC_STATIC_VIDEO_HEIGHT, m_cStaticVideoHeight);
	DDX_Control(pDX, IDC_STATIC_VIDEO_FRAME_RATE, m_cStaticVideoFrameRate);
	DDX_Control(pDX, IDC_STATIC_VIDEO_BIT_RATE, m_cStaticVideoBitRate);
	DDX_Control(pDX, IDC_STATIC_UNLOGIN_USER_COUNT, m_cStaticUnloginUserCount);
	DDX_Control(pDX, IDC_STATIC_LOGINING_USER_COUNT, m_cStaticLoginingUserCount);
	DDX_Control(pDX, IDC_STATIC_LOGIN_FAIL_USER_COUNT, m_cStaticLoginFailUserCount);
	DDX_Control(pDX, IDC_STATIC_AVER_LOGIN_TIME, m_cStaticAverLoginTime);
	DDX_Control(pDX, IDC_STATIC_LOGIN_LONGEST, m_cStaticLoginLongest);
	DDX_Control(pDX, IDC_STATIC_START_LOGIN_TIME, m_cStaticStartLoginTime);
	DDX_Control(pDX, IDC_STATIC_LOGIN_TOTAL_TIME, m_cStaticLoginTotalTime);
	DDX_Control(pDX, IDC_EDIT_DISPLAYER, m_cEditDisplayer);
}

BEGIN_MESSAGE_MAP(CClientSimulatorUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_START, &CClientSimulatorUIDlg::OnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CONFIG, &CClientSimulatorUIDlg::OnBnClickedBtnConfig)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CClientSimulatorUIDlg::OnBnClickedBtnQuit)
	ON_MESSAGE(WM_USER_NOTIFY_MSG, &CClientSimulatorUIDlg::OnNotifyMsg)
END_MESSAGE_MAP()


// CClientSimulatorUIDlg 消息处理程序

BOOL CClientSimulatorUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	SkinH_Attach();

	// 必须先调用InitClientMgr，后面的初始化依赖于InitClientMgr
	if (!InitClientMgr())
	{
		MessageBox(_T("Call InitClientMgr failed!"), _T("错误"));
		exit(1);
	}

	InitGeneralConfig();
	InitVideoParam();
	InitRuntimeInfo();

	// 设置显示背景
	m_cDisplayBrush.CreateSolidBrush(0x0);

	// 设置文本框不限制内容长度
	m_cEditDisplayer.LimitText(-1);

	m_eStartBtnState = START_BTN_STATE_START;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientSimulatorUIDlg::InitRuntimeInfo()
{
	const GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	WCHAR szTmp[32];

	// 尚未登录用户数
	wsprintf(szTmp, _T("%u"), config.users.size());
	m_cStaticUnloginUserCount.SetWindowTextW(szTmp);

	m_nUnLoginUserCount = config.users.size();

	// 正在登录用户数
	wsprintf(szTmp, _T("%u"), 0);
	m_cStaticLoginingUserCount.SetWindowTextW(szTmp);

	// 登录成功用户数
	wsprintf(szTmp, _T("%u"), 0);
	m_cLoginSuccessCount.SetWindowTextW(szTmp);

	// 登录失败用户数
	wsprintf(szTmp, _T("%u"), 0);
	m_cStaticLoginFailUserCount.SetWindowTextW(szTmp);

	// 平均登录时长
	wsprintf(szTmp, _T("%u"), 0);
	m_cStaticAverLoginTime.SetWindowTextW(szTmp);

	// 最慢登录时长
	wsprintf(szTmp, _T("%u"), 0);
	m_cStaticLoginLongest.SetWindowTextW(szTmp);
	
	// 开始登录时间
	wsprintf(szTmp, _T("%u"), 0);
	m_cStaticStartLoginTime.SetWindowTextW(szTmp);

	// 总登录时长
	wsprintf(szTmp, _T("%u"), 0);
	m_cStaticLoginTotalTime.SetWindowTextW(szTmp);
}

void CClientSimulatorUIDlg::InitVideoParam()
{
	const GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	WCHAR szTmp[32];

	// 视频宽度
	wsprintf(szTmp, _T("%u"), config.video_param.width);
	m_cStaticVideoWidth.SetWindowTextW(szTmp);

	// 视频高度
	wsprintf(szTmp, _T("%u"), config.video_param.height);
	m_cStaticVideoHeight.SetWindowTextW(szTmp);

	// 视频帧率
	wsprintf(szTmp, _T("%u f/s"), config.video_param.frame_rate);
	m_cStaticVideoFrameRate.SetWindowTextW(szTmp);

	// 视频码流
	wsprintf(szTmp, _T("%u kb/s"), config.video_param.bit_rate / 1000);
	m_cStaticVideoBitRate.SetWindowTextW(szTmp);
}

void CClientSimulatorUIDlg::InitGeneralConfig()
{
	const GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	// 前置服务地址
	USES_CONVERSION;
	m_cStaticFrontAddr.SetWindowTextW(A2T(config.common_info.front_addr.c_str()));

	WCHAR szTmp[32];

	// 总用户数
	wsprintf(szTmp, _T("%u"), config.users.size());
	m_cStaticTotalUserCount.SetWindowTextW(szTmp);

	// 匿名用户个数
	FS_UINT32 nAnonymousUserCount = 0;
	FS_UINT32 nRegisterUserCount = 0;

	for each (UserInfo info in config.users)
	{
		if (info.user_type == USER_TYPE_REGISTER)
		{
			nRegisterUserCount++;
		}
		else
		{
			nAnonymousUserCount++;
		}
	}

	// 注册用户个数
	wsprintf(szTmp, _T("%u"), nRegisterUserCount);
	m_cStaticRegisterUserCount.SetWindowTextW(szTmp);
	
	// 匿名用户个数
	wsprintf(szTmp, _T("%u"), nAnonymousUserCount);
	m_cStaticAnonymousUserCount.SetWindowTextW(szTmp);

	// 是否接收音视频
	wsprintf(szTmp, _T("%s"), config.common_info.if_recv_av ? _T("是") : _T("否"));
	m_cStaticIfRecvAv.SetWindowTextW(szTmp);

	// 视频设备个数
	wsprintf(szTmp, _T("%u"), config.common_info.video_count);
	m_cStaticVideoDevCount.SetWindowTextW(szTmp);
}

bool CClientSimulatorUIDlg::InitClientMgr()
{
	IComponentFactory* factory = NULL;
	HRESULT hr = FWInitFrameWorkFromPath(true, _T("./"), NULL, &factory);
	if (FAILED(hr))
	{
		printf("Failed to init framework.\n");
		return false;
	}

	hr = FWInitLogger(factory, _T("ClientSimulatorUI"), 3, WLOGMODE_TOFILE);
	if (FAILED(hr))
	{
		printf("Failed to init logger.\n");
		return false;
	}

	m_cClientMgr.reset(new VirtualClientMgr());
	if (!m_cClientMgr->Init(factory))
	{
		MessageBox(_T("初始化VirtualClientMgr失败!"), _T("错误"));
		return false;
	}

	// CClientSimulatorUIDlg->VirtualClientMgr
	SetDownMsgProcSuccessor(m_cClientMgr);

	// !!!m_cClientMgr->SetUpMsgProcSuccessor(shared_from_this());
	// 使用shared_from_this()会导致崩溃，暂未搞清楚是什么原因!!!
	// CClientSimulatorUIDlg<-VirtualClientMgr
	m_cClientMgr->SetUpMsgProcSuccessor(this);

	// 上行消息映射
	UP_MSG_PRE_MAP(UP_MSG_STATE_START, CClientSimulatorUIDlg::OnStateStart);
	UP_MSG_PRE_MAP(UP_MSG_HAS_NO_VIDEO_DEV, CClientSimulatorUIDlg::OnHasNoVideoDev);
	UP_MSG_PRE_MAP(UP_MSG_USER_LOGIN_RESULT, CClientSimulatorUIDlg::OnLoginResultMsg);
	UP_MSG_PRE_MAP(UP_MSG_APP_RUN_ERROR, CClientSimulatorUIDlg::OnAppRunErrMsg);

	return true;
}

bool CClientSimulatorUIDlg::OnStateStart(const MsgData& msg_data)
{
	std::unique_lock<std::mutex> lock(m_mtxDisplay);

	StateStartMsgSP start_msg =
		std::static_pointer_cast<StateStartMsg>(msg_data);

	WCHAR szTmp[128];
	ZeroMemory(szTmp, sizeof(szTmp));

	m_strDisplay.clear();

	CTime tm = CTime::GetCurrentTime();
	std::wstring strTime = tm.Format(_T("%X"));

	switch (start_msg->state_type)
	{
	case CLIENT_STATE_TYPE_INIT:
		// 更新正登录用户数
		m_nLoginingUserCount++;
		wsprintf(szTmp, _T("%u"), m_nLoginingUserCount);
		m_cStaticLoginingUserCount.SetWindowTextW(szTmp);
		m_cStaticLoginingUserCount.Invalidate();

		// 更新未登录用户数
		m_nUnLoginUserCount--;
		wsprintf(szTmp, _T("%u"), m_nUnLoginUserCount);
		m_cStaticUnloginUserCount.SetWindowTextW(szTmp);
		m_cStaticUnloginUserCount.Invalidate();

		wsprintf(szTmp, _T("[%s] User %s start logining...\r\n"),
			strTime.c_str(), start_msg->user_name.c_str());
		m_strDisplay += szTmp;
		break;
		
	case CLIENT_STATE_TYPE_UPDATE:
		wsprintf(szTmp, _T("[%s] User %s enter update-version state.\r\n"),
			strTime.c_str(), start_msg->user_name.c_str());
		m_strDisplay += szTmp;
		break;

	case CLIENT_STATE_TYPE_LOGIN:
		wsprintf(szTmp, _T("[%s] User %s enter login-front state.\r\n"),
			strTime.c_str(), start_msg->user_name.c_str());
		m_strDisplay += szTmp;
		break;

	case CLIENT_STATE_TYPE_SELECT_ROOM:
		wsprintf(szTmp, _T("[%s] User %s enter select-room state.\r\n"),
			strTime.c_str(), start_msg->user_name.c_str());
		m_strDisplay += szTmp;
		break;

	case CLIENT_STATE_TYPE_STARTUP_ROOM:
		wsprintf(szTmp, _T("[%s] User %s enter startup-room state.\r\n"),
			strTime.c_str(), start_msg->user_name.c_str());
		m_strDisplay += szTmp;
		break;

	case CLIENT_STATE_TYPE_MAIN_ROOM:
		wsprintf(szTmp, _T("[%s] User %s enter main-room state.\r\n"),
			strTime.c_str(), start_msg->user_name.c_str());
		m_strDisplay += szTmp;
		break;

	default:
		break;
	}

	// 在此线程调用SendMessage会引发死锁，原因未知，只能先Post到窗口线程处理
	PostMessage(WM_USER_NOTIFY_MSG, 0, (LPARAM)(new CString(m_strDisplay.c_str())));

	return false;
}

bool CClientSimulatorUIDlg::OnHasNoVideoDev(const MsgData& msg_data)
{
	MessageBox(_T("未找到本地视频设备!"), _T("警告"));

	return false;
}

void CClientSimulatorUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientSimulatorUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientSimulatorUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientSimulatorUIDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

HBRUSH CClientSimulatorUIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_DISPLAYER)
	{	
		// 黑底白字
		pDC->SetTextColor(RGB(255, 255, 255));

		// 文字背景透明
		pDC->SetBkMode(0);

		return m_cDisplayBrush;
	}

	return hbr;
}

void CClientSimulatorUIDlg::OnClickedBtnStart()
{
	if (m_eStartBtnState == START_BTN_STATE_STOP)
	{
		if (!m_cClientMgr->Stop())
		{
			MessageBox(_T("退出登录失败!"), _T("错误"));
		}

		m_cEditDisplayer.SetWindowTextW(_T(""));
		m_cEditDisplayer.Invalidate();

		InitGeneralConfig();
		InitRuntimeInfo();
		InitVideoParam();

		// 停止后可配置
		GetDlgItem(IDC_BTN_CONFIG)->EnableWindow(TRUE);

		// 开始按钮变重新启动
		GetDlgItem(IDC_BTN_START)->SetWindowTextW(_T("重新启动"));

		m_eStartBtnState = START_BTN_STATE_RESTART;
	}
	else if (m_eStartBtnState == START_BTN_STATE_START)
	{
		m_nStartLoginTime = timeGetTime();

		if (m_cClientMgr->Start())
		{
			CTime tm = CTime::GetCurrentTime();
			std::wstring str = tm.Format(_T("%Y/%m/%d/%X"));
			m_cStaticStartLoginTime.SetWindowTextW(str.c_str());
			m_cStaticStartLoginTime.Invalidate();

			// 运行中不可配置
			GetDlgItem(IDC_BTN_CONFIG)->EnableWindow(FALSE);

			// 开始按钮变停止按钮
			GetDlgItem(IDC_BTN_START)->SetWindowTextW(_T("停止"));

			m_eStartBtnState = START_BTN_STATE_STOP;
		}
		else
		{
			::MessageBoxA(GetSafeHwnd(), "启动失败", "错误", MB_ICONEXCLAMATION | MB_OKCANCEL);
			EndDialog(IDCANCEL);
		}
	}
	else if (m_eStartBtnState == START_BTN_STATE_RESTART)
	{
		RestartSelf();
		EndDialog(IDCANCEL);
	}
}

void CClientSimulatorUIDlg::RestartSelf()
{
	//获取exe程序当前路径  
	TCHAR szAppName[MAX_PATH];
	::GetModuleFileName(theApp.m_hInstance, szAppName, MAX_PATH);

	CString strAppFullName;
	strAppFullName.Format(_T("%s"), szAppName);

	//重启程序  
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION procStruct;
	memset(&StartInfo, 0, sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);
	::CreateProcess(
		(LPCTSTR)strAppFullName,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&StartInfo,
		&procStruct);
}

void CClientSimulatorUIDlg::OnBnClickedBtnConfig()
{
	CClientSimulatorConfigDlg dlg(m_cClientMgr);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		InitGeneralConfig();
		InitVideoParam();
		InitRuntimeInfo();
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
}

void CClientSimulatorUIDlg::OnBnClickedBtnQuit()
{
	EndDialog(IDCANCEL);
}

void CClientSimulatorUIDlg::StatLoginTime()
{
	if (m_nUnLoginUserCount == 0 && m_nLoginingUserCount == 0 && !m_bStatOK)
	{	
		WCHAR szTmp[16];

		FS_UINT32 nNowTime = timeGetTime();

		// 总登录时间
		wsprintf(szTmp, _T("%u ms"), nNowTime - m_nStartLoginTime);
		m_cStaticLoginTotalTime.SetWindowTextW(szTmp);
		m_cStaticLoginTotalTime.Invalidate();
		
		FS_UINT32 nTotalLoginTime = 0;
		FS_UINT32 nMaxLoginTime = 0;
		FS_UINT32 nLoginSuccessCount = 0;
		for each (UserLoginResultMsgSP result in m_vecLoginResult)
		{
			if (result->login_result == ERR_CODE_SUCCESS)
			{
				nLoginSuccessCount++;
				nTotalLoginTime += result->login_time;

				if (result->login_time > nMaxLoginTime)
					nMaxLoginTime = result->login_time;
			}
		}

		if (nLoginSuccessCount != 0)
		{
			// 平均登录时长
			wsprintf(szTmp, _T("%u ms"), nTotalLoginTime / nLoginSuccessCount);
			m_cStaticAverLoginTime.SetWindowTextW(szTmp);
			m_cStaticAverLoginTime.Invalidate();

			// 最慢登录时长
			wsprintf(szTmp, _T("%u ms"), nMaxLoginTime);
			m_cStaticLoginLongest.SetWindowTextW(szTmp);
			m_cStaticLoginLongest.Invalidate();
		}

		m_bStatOK = true;
	}
}

LRESULT CClientSimulatorUIDlg::OnNotifyMsg(WPARAM wParam, LPARAM lParam)
{
	// 直接试用SetWindowTextW刷新文本框内容，闪烁比较厉害，这里采用增量刷新的方式
	CString* pStr = reinterpret_cast<CString*>(lParam);

	::SendMessage(m_cEditDisplayer.GetSafeHwnd(), EM_SETSEL, -1, 0);
	::SendMessage(m_cEditDisplayer.GetSafeHwnd(), EM_REPLACESEL, NULL, LPARAM(pStr->GetString()));

	delete pStr;

	return 0;
}

bool CClientSimulatorUIDlg::OnAppRunErrMsg(const MsgData& msg_data)
{
	AppRunErrMsgSP err_msg =
		std::static_pointer_cast<AppRunErrMsg>(msg_data);

	switch (err_msg->run_err)
	{
	case ERR_CODE_START_AUDIO_FAILED:
		MessageBox(_T("启动音频设备失败!"), _T("错误"));
		break;

	case ERR_CODE_START_VIDEO_FAILED:
		MessageBox(_T("启动视频设备失败!"), _T("错误"));
		break;

	default:
		break;
	}

	return false;
}

bool CClientSimulatorUIDlg::OnLoginResultMsg(const MsgData& msg_data)
{
	std::lock_guard<std::mutex> lock(m_mtxLoginResult);

	UserLoginResultMsgSP result_msg =
		std::static_pointer_cast<UserLoginResultMsg>(msg_data);

	m_vecLoginResult.push_back(result_msg);

	WCHAR szTmp[128];
	ZeroMemory(szTmp, sizeof(szTmp));

	if (result_msg->login_result == ERR_CODE_SUCCESS)
	{
		// 更新登录成功用户数
		m_nLoginSuccessUserCount++;
		wsprintf(szTmp, _T("%u"), m_nLoginSuccessUserCount);
		m_cLoginSuccessCount.SetWindowTextW(szTmp);
		m_cLoginSuccessCount.Invalidate();
	}
	else // 登录失败
	{
		// 更新登录失败用户数
		m_nLoginFailUserCount++;
		wsprintf(szTmp, _T("%u"), m_nLoginFailUserCount);
		m_cStaticLoginFailUserCount.SetWindowTextW(szTmp);
		m_cStaticLoginFailUserCount.Invalidate();
	}

	// 更新正在登录用户数
	m_nLoginingUserCount--;
	wsprintf(szTmp, _T("%u"), m_nLoginingUserCount);
	m_cStaticLoginingUserCount.SetWindowTextW(szTmp);
	m_cStaticLoginingUserCount.Invalidate();

	// 登录时间统计
	StatLoginTime();

	// 显示用户登录结果
	CTime tm = CTime::GetCurrentTime();
	std::wstring strTime = tm.Format(_T("%X"));

	if (result_msg->login_result == 0)
		wsprintf(szTmp, _T("[%s] User %s login sucess.\r\n"),
			strTime.c_str(), result_msg->user_name.c_str());
	else
		wsprintf(szTmp, _T("[%s] User %s login failed.\r\n"),
			strTime.c_str(), result_msg->user_name.c_str());

	m_strDisplay.clear();
	m_strDisplay += szTmp;

	// 在此线程调用SendMessage会引发死锁，原因未知，只能先Post到窗口线程处理
	PostMessage(WM_USER_NOTIFY_MSG, 0, (LPARAM)(new CString(m_strDisplay.c_str())));

	return false;
}