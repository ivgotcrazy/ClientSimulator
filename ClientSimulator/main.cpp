// ClientSimulator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "frameworksdk.h"
#include "virtual_client_mgr.h"

using namespace clientmgr;

int _tmain(int argc, _TCHAR* argv[])
{
	// ��ʼ�������̵߳��ý������봦���̲߳�һ��
	HRESULT hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		printf("Failed to call CoInitializeEx.\n");
		return -1;
	}

	IComponentFactory* factory = NULL;
	hr = FWInitFrameWorkFromPath(true, _T("./"), NULL, &factory);
	if (FAILED(hr))
	{
		printf("Failed to init framework.\n");
		return -1;
	}

	hr = FWInitLogger(factory, _T("ClientSimulator"), 3, WLOGMODE_TOCONSOLE | WLOGMODE_TOFILE);
	if (FAILED(hr))
	{
		printf("Failed to init logger.\n");
		return -1;
	}

	VirtualClientMgr client_mgr;
	if (!client_mgr.Init(factory))
	{
		LOG(_T("Failed to init simulator.\n"));
		return -1;
	}

	if (!client_mgr.Start())
	{
		LOG(_T("Failed to run simulator.\n"));
		return -1;
	}

	while (true)
	{
		Sleep(1000);
	}

	return 0;
}

