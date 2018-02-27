// AvConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "AvConfigDlg.h"
#include "afxdialogex.h"
#include "global_config_mgr.h"


// CAvConfigDlg 对话框

IMPLEMENT_DYNAMIC(CAvConfigDlg, CDialogEx)

CAvConfigDlg::CAvConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent /*=NULL*/)
	: CDialogEx(CAvConfigDlg::IDD, pParent)
	, m_ClientMgr(clientMgr)
	, m_nCurSelVideoDev(0)
	, m_nCurVideoResolution(0)
	, m_nCurVideoFrameRate(0)
	, m_nCurVideoBitRate(0)
	, m_nVideoEncodeMode(0)
	, m_nRadioRecvAvGroup(0)
	, m_nCurSelAuidoDev(0)
{

}

CAvConfigDlg::~CAvConfigDlg()
{
}

void CAvConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_VIDEO_DEV, m_ComboSelectVideoDev);
	DDX_Control(pDX, IDC_COMBO_SELECT_VIDEO_RESOLUTION, m_ComboSelectResolution);
	DDX_Control(pDX, IDC_SLIDER_VIDEO_FRAME_RATE, m_SliderFrameRate);
	DDX_Control(pDX, IDC_SLIDER_VIDEO_BIT_RATE, m_SliderBitRate);
	DDX_Radio(pDX, IDC_RADIO_RECV_AV_YES, m_nRadioRecvAvGroup);
	DDX_Control(pDX, IDC_EDIT_AV_DEV_COUNT, m_EditVideoDevCount);
	DDX_Control(pDX, IDC_COMBO_SELECT_VIDEO_ENCODE_MODE, m_ComboEncodeMode);
	DDX_Control(pDX, IDC_COMBO_SELECT_AUDIO_CAP_DEV, m_ComboAudioCapDev);
}


BEGIN_MESSAGE_MAP(CAvConfigDlg, CDialogEx)
	
	ON_EN_KILLFOCUS(IDC_EDIT_AV_DEV_COUNT, &CAvConfigDlg::OnEnKillfocusEditAvDevCount)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_VIDEO_DEV, &CAvConfigDlg::OnCbnSelchangeComboSelectVideoDev)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_VIDEO_RESOLUTION, &CAvConfigDlg::OnCbnSelchangeComboSelectVideoResolution)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VIDEO_FRAME_RATE, &CAvConfigDlg::OnNMReleasedcaptureSliderVideoFrameRate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VIDEO_BIT_RATE, &CAvConfigDlg::OnNMReleasedcaptureSliderVideoBitRate)
	ON_MESSAGE(WM_USER_APPLY_CONFIG, OnApplyConfig)
	ON_BN_CLICKED(IDC_RADIO_RECV_AV_YES, &CAvConfigDlg::OnBnClickedRadioRecvAvGroup)
	ON_BN_CLICKED(IDC_RADIO_RECV_AV_NO, &CAvConfigDlg::OnBnClickedRadioRecvAvGroup)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_VIDEO_ENCODE_MODE, &CAvConfigDlg::OnCbnSelchangeComboSelectVideoEncodeMode)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_AUDIO_CAP_DEV, &CAvConfigDlg::OnCbnSelchangeComboSelectAudioCapDev)
END_MESSAGE_MAP()

typedef struct
{
	int		nWidth;
	int		nHeight;
	TCHAR	szText[32];
	unsigned int nFrameRate;
	unsigned int nBitrate;
}VideoParamItem;

static VideoParamItem g_Params[] = {
	{ 160, 120, _T("160 * 120"), 10, 0 },
	{ 176, 144, _T("176 * 144"), 10, 0 },
	{ 320, 240, _T("320 * 240"), 10, 0 },
	{ 352, 288, _T("352 * 288"), 10, 0 },
	{ 640, 480, _T("640 * 480"), 15, 0 },
	{ 704, 576, _T("704 * 576"), 20, 0 },
	{ 720, 576, _T("720 * 576"), 25, 0 },
	{ 1280, 720, _T("1280 * 720"), 30, 0 },
	{ 1920, 1080, _T("1920 * 1080"), 30, 0 }
};

// CAvConfigDlg 消息处理程序

BOOL CAvConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// message flow: CAvConfigDlg -> VirtualClientMgr
	SetDownMsgProcSuccessor(m_ClientMgr);

	CString str;

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	// 显示视频设备个数
	str.Format(_T("%d"), config.common_info.video_count);
	m_EditVideoDevCount.SetWindowTextW(str);

	// 是否接受音视频
	m_nRadioRecvAvGroup = config.common_info.if_recv_av ? 0 : 1;
	if (config.common_info.if_recv_av)
	{
		((CButton*)GetDlgItem(IDC_RADIO_RECV_AV_YES))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_RECV_AV_NO))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_RECV_AV_YES))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_RECV_AV_NO))->SetCheck(TRUE);
	}

	// 将视频设备列表显示在下拉列表框中
	VideoDevNameVec video_devs = m_ClientMgr->GetVideoDeviceNames();
	for (int i = 0; i < video_devs.size(); i++)
	{
		CString str;
		str.Format(_T("%d-%s"), i, video_devs[i]);
		m_ComboSelectVideoDev.AddString(str);
	}
	m_ComboSelectVideoDev.SetCurSel(config.video_param.video_dev_index);

	// 将视频设备可选分辨率显示在下拉列表框中
	int nResolutionIndex = -1;
	for (int i = 0; i < sizeof(g_Params) / sizeof(VideoParamItem); i++)
	{
		m_ComboSelectResolution.AddString(g_Params[i].szText);
		if (config.video_param.width == g_Params[i].nWidth
			&& config.video_param.height == g_Params[i].nHeight)
		{
			nResolutionIndex = i;
		}
	}
	if (nResolutionIndex == -1)
	{
		MessageBox(_T("不支持的视频分辨率！"), _T("错误"));
		exit(0);
	}
	m_ComboSelectResolution.SetCurSel(nResolutionIndex);

	// 下拉列表显示编码模式
	m_ComboEncodeMode.AddString(_T("动态码率"));
	m_ComboEncodeMode.AddString(_T("平均码率"));
	m_ComboEncodeMode.AddString(_T("恒定码率"));
	m_ComboEncodeMode.SetCurSel(config.video_param.encode_mode);

	// 显示帧率
	m_SliderFrameRate.SetRange(0, 60);
	m_SliderFrameRate.SetPos(config.video_param.frame_rate);

	str.Format(_T("%d f/s"), config.video_param.frame_rate);
	GetDlgItem(IDC_STATIC_VIDEO_FRAME_RATE)->SetWindowTextW(str);

	// 显示码率
	m_SliderBitRate.SetRange(0, 8000000);
	m_SliderBitRate.SetPos(config.video_param.bit_rate);

	str.Format(_T("%d kb/s"), config.video_param.bit_rate / 1000);
	GetDlgItem(IDC_STATIC_VIDEO_BIT_RATE)->SetWindowTextW(str);

	// 下拉列表显示音频采集设备
	AudioDevNameVec audio_devs = m_ClientMgr->GetAudioCapDevNames();
	for (int i = 0; i < audio_devs.size(); i++)
	{
		CString str;
		str.Format(_T("%d-%s"), i, audio_devs[i]);
		m_ComboAudioCapDev.AddString(str);
	}
	m_ComboAudioCapDev.SetCurSel(config.audio_param.audio_dev_index);

	// 获取音视频参数
	m_nCurSelVideoDev		= config.video_param.video_dev_index;
	m_nCurVideoResolution	= nResolutionIndex;
	m_nCurVideoFrameRate	= config.video_param.frame_rate;
	m_nCurVideoBitRate		= config.video_param.bit_rate;
	m_nVideoEncodeMode		= config.video_param.encode_mode;
	m_nCurSelAuidoDev		= config.audio_param.audio_dev_index;

	// 视频设备预览
	PreviewVideoDev();

	return TRUE;
}

void CAvConfigDlg::OnEnKillfocusEditAvDevCount()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_AV_DEV_COUNT)->GetWindowText(str);
	
	int nDevCount = _ttoi(str);

	GlobalConfigMgr::GetInstance().GetGlobalConfig().common_info.video_count = nDevCount;
}


void CAvConfigDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_VIDEO_FRAME_RATE)
	{
		CSliderCtrl* pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VIDEO_FRAME_RATE);
		int pos = pSliderCtrl->GetPos();

		CString str;
		str.Format(_T("%d f/s"), pos);
		GetDlgItem(IDC_STATIC_VIDEO_FRAME_RATE)->SetWindowTextW(str);
	}
	else if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_VIDEO_BIT_RATE)
	{
		CSliderCtrl* pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VIDEO_BIT_RATE);
		int pos = pSliderCtrl->GetPos();

		CString str;
		str.Format(_T("%d kb/s"), pos / 1000); // 转换成kb
		GetDlgItem(IDC_STATIC_VIDEO_BIT_RATE)->SetWindowTextW(str);
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAvConfigDlg::OnCbnSelchangeComboSelectVideoDev()
{
	if (m_ComboSelectVideoDev.GetCurSel() != m_nCurSelVideoDev)
	{
		m_nCurSelVideoDev = m_ComboSelectVideoDev.GetCurSel();

		PreviewVideoDev();
	}
}

void CAvConfigDlg::OnCbnSelchangeComboSelectVideoResolution()
{
	if (m_ComboSelectResolution.GetCurSel() != m_nCurVideoResolution)
	{
		m_nCurVideoResolution = m_ComboSelectResolution.GetCurSel();

		SetVideoDevParam();
	}
}

void CAvConfigDlg::OnNMReleasedcaptureSliderVideoFrameRate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	SetVideoDevParam();
}

void CAvConfigDlg::OnNMReleasedcaptureSliderVideoBitRate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	SetVideoDevParam();
}

void CAvConfigDlg::PreviewVideoDev()
{
	PreviewVideoDevMsgSP preview_msg(new PreviewVideoDevMsg);
	preview_msg->cap_param.dev_index	= m_nCurSelVideoDev;
	preview_msg->cap_param.width		= g_Params[m_nCurVideoResolution].nWidth;
	preview_msg->cap_param.height		= g_Params[m_nCurVideoResolution].nHeight;
	preview_msg->cap_param.frame_rate	= m_nCurVideoFrameRate;
	preview_msg->cap_param.bit_rate		= m_nCurVideoBitRate;
	preview_msg->cap_param.encode_mode	= m_nVideoEncodeMode;
	preview_msg->render_wnd				= GetDlgItem(IDC_STATIC_VIDEO_DISPLAYER)->GetSafeHwnd();
	SendDownMsg(DOWN_MSG_PREVIEW_VIDEO_DEV, preview_msg);
}

void CAvConfigDlg::SetVideoDevParam()
{
	SetVideoParamMsgSP preview_msg(new SetVideoParamMsg);
	preview_msg->cap_param.dev_index	= m_nCurSelVideoDev;
	preview_msg->cap_param.width		= g_Params[m_nCurVideoResolution].nWidth;
	preview_msg->cap_param.height		= g_Params[m_nCurVideoResolution].nHeight;
	preview_msg->cap_param.frame_rate	= m_nCurVideoFrameRate;
	preview_msg->cap_param.bit_rate		= m_nCurVideoBitRate;
	preview_msg->cap_param.encode_mode	= m_nVideoEncodeMode;
	SendDownMsg(DOWN_MSG_SET_VIDEO_PARAM, preview_msg);
}

void CAvConfigDlg::SetAudioDevParam()
{
	SetAudioParamMsgSP audio_param_msg(new SetAudioParamMsg);
	audio_param_msg->cap_param.dev_index = m_nCurSelAuidoDev;

	SendDownMsg(DOWN_MSG_SET_AUDIO_PARAM, audio_param_msg);
}

LRESULT CAvConfigDlg::OnApplyConfig(WPARAM wParam, LPARAM lParam)
{
	CString str;

	GlobalConfig& config = GlobalConfigMgr::GetInstance().GetGlobalConfig();

	m_EditVideoDevCount.GetWindowTextW(str);
	config.common_info.video_count = _ttoi(str);
	config.common_info.if_recv_av = (m_nRadioRecvAvGroup == 0);

	// 视频设备参数
	config.video_param.video_dev_index = m_ComboSelectVideoDev.GetCurSel();
	config.video_param.width = g_Params[m_ComboSelectResolution.GetCurSel()].nWidth;
	config.video_param.height = g_Params[m_ComboSelectResolution.GetCurSel()].nHeight;
	config.video_param.frame_rate = m_SliderFrameRate.GetPos();
	config.video_param.bit_rate = m_SliderBitRate.GetPos();
	config.video_param.encode_mode = m_ComboEncodeMode.GetCurSel();
	
	// 音频设备参数
	config.audio_param.audio_dev_index = m_ComboAudioCapDev.GetCurSel();

	return 0;
}

void CAvConfigDlg::OnBnClickedRadioRecvAvGroup()
{
	UpdateData(TRUE);
}

void CAvConfigDlg::OnCbnSelchangeComboSelectVideoEncodeMode()
{
	if (m_ComboEncodeMode.GetCurSel() != m_nVideoEncodeMode)
	{
		m_nVideoEncodeMode = m_ComboEncodeMode.GetCurSel();
		SetVideoDevParam();
	}
}

void CAvConfigDlg::OnCbnSelchangeComboSelectAudioCapDev()
{
	if (m_ComboAudioCapDev.GetCurSel() != m_nCurSelAuidoDev)
	{
		m_nCurSelAuidoDev = m_ComboAudioCapDev.GetCurSel();
		SetAudioDevParam();
	}
}
