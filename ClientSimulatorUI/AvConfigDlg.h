#pragma once
#include "afxcmn.h"

#include "virtual_client_mgr.h"
#include "afxwin.h"

using namespace clientmgr;

// CAvConfigDlg 对话框

class CAvConfigDlg 
	: public CDialogEx
	, public CommonMsgProcessor
	, public std::enable_shared_from_this<CAvConfigDlg>
{
	DECLARE_DYNAMIC(CAvConfigDlg)

public:
	CAvConfigDlg(const VirtualClientMgrSP& clientMgr, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAvConfigDlg();

// 对话框数据
	enum { IDD = IDD_DLG_AV_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnKillfocusEditAvDevCount();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCbnSelchangeComboSelectVideoDev();
	afx_msg void OnCbnSelchangeComboSelectVideoResolution();
	afx_msg void OnNMReleasedcaptureSliderVideoFrameRate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderVideoBitRate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioRecvAvGroup();
	afx_msg void OnCbnSelchangeComboSelectVideoEncodeMode();
	afx_msg void OnCbnSelchangeComboSelectAudioCapDev();

private:
	void PreviewVideoDev();
	void SetVideoDevParam();
	void SetAudioDevParam();
	LRESULT OnApplyConfig(WPARAM wParam, LPARAM lParam);

private:
	VirtualClientMgrSP m_ClientMgr;

	CEdit m_EditVideoDevCount;
	CComboBox m_ComboSelectVideoDev;
	CComboBox m_ComboSelectResolution;
	CComboBox m_ComboEncodeMode;
	CSliderCtrl m_SliderFrameRate;
	CSliderCtrl m_SliderBitRate;
	CComboBox m_ComboAudioCapDev;

	FS_UINT32 m_nCurSelVideoDev;
	FS_UINT32 m_nCurVideoResolution;
	FS_UINT32 m_nCurVideoFrameRate;
	FS_UINT32 m_nCurVideoBitRate;

	// #define VIDEO_ENCODER_MODE_VBR		0
	// #define VIDEO_ENCODER_MODE_CBR		1
	// #define VIDEO_ENCODER_MODE_ABR		2
	FS_UINT32 m_nVideoEncodeMode;

	FS_UINT32 m_nCurSelAuidoDev;

	int m_nRadioRecvAvGroup;					
};
