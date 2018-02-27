#ifndef __IAVPLUGIN_H
#define __IAVPLUGIN_H

#include "wcombase.h"
#include "AVDevPlugin.h"

#ifdef __cplusplus
extern "C" {
#endif

	// {A0EE6ACD-D15B-4829-B03F-7749ACBF0245}
	DEFINE_GUID(IID_IAVPlugin, 
		0xa0ee6acd, 0xd15b, 0x4829, 0xb0, 0x3f, 0x77, 0x49, 0xac, 0xbf, 0x2, 0x45);

	DECLARE_INTERFACE(IAVPlugin)
	{
		//��ȡ�������
		STDMETHOD_(FS_UINT32,GetType)( THIS_ ) PURE;
		//��ȡ�������
		STDMETHOD_( FS_UINT32,GetCapa )( THIS_ ) PURE;
		//�������Ա���
		STDMETHOD(SetLanCode)( THIS_ int nLanCode ) PURE;
		//���ò�������ò������Զ����������õ������ļ���
		STDMETHOD(Config )( THIS_ HWND hWndParent ) PURE;
		//�����Ƿ��������ݻص�
		STDMETHOD(EnableOutput )( THIS_ FS_UINT32 dwMediaType,BOOL bEnable ) PURE;
		//�������ݻص�����
		STDMETHOD(SetOutputCallback )( THIS_ FS_UINT32 dwMediaType,AVPLUGIN_MEDIACALLBACK	lpCallback,FS_UINT dwUserData ) PURE;
		//�����Ƿ�������������
		STDMETHOD(EnableInput )( THIS_ FS_UINT32 dwMediaType,BOOL bEnable )PURE;
		//������������
		STDMETHOD(InputSample )( THIS_ AVPluginSample* pSample)PURE;
		//��ѯ�����ʽ
		STDMETHOD(QueryOutputFormat)( THIS_ FS_UINT32 dwMediaType,int nIndex,void* pFormat,FS_UINT32 dwFormatSize ) PURE;
		//���������ʽ
		STDMETHOD(SetOutputFormat)( THIS_ FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize ) PURE;
		//��ȡ��ǰ�����ʽ
		STDMETHOD(GetOutputFormat)( THIS_ FS_UINT32 dwMediaType,void* pFormat,FS_UINT32 dwFormatSize ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif