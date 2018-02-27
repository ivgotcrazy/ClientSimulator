
// ClientSimulatorUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ClientSimulatorUI.h"
#include "ClientSimulatorUIDlg.h"
#include "global_config_mgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientSimulatorUIApp

BEGIN_MESSAGE_MAP(CClientSimulatorUIApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClientSimulatorUIApp ����

CClientSimulatorUIApp::CClientSimulatorUIApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CClientSimulatorUIApp ����

CClientSimulatorUIApp theApp;


// CClientSimulatorUIApp ��ʼ��

BOOL CClientSimulatorUIApp::InitInstance()
{
	// ��ʼ�������̵߳��ý������봦���̲߳�һ��
	//HRESULT hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//if (FAILED(hr))
	//{
	//	TRACE(traceAppMsg, 0, "Failed to call CoInitializeEx.\n");
	//	return FALSE;
	//}

//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��ʼ�������̵߳��ý������봦���̲߳�һ��
	/*HRESULT hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
	printf("Failed to call CoInitializeEx.\n");
	return FALSE;
	}*/

	AfxOleInit();

	GlobalConfigMgr& config_mgr = GlobalConfigMgr::GetInstance();
	if (!config_mgr.Init())
	{
		MessageBox(NULL, _T("��ʼ�����ù�����ʧ�ܣ����������ļ��Ƿ���ȷ�������˳���"), _T("����"), 0);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CClientSimulatorUIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������˳������ǽ����ں�̨���У���ʱûʱ���о��������
	// ����ʹ��һ�ִ�³�ķ�ʽ��ֱ�Ӱѽ���ɱ��������
	TerminateProcess(GetCurrentProcess(), 0);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

