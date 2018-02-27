#ifndef __IWRECORD_FILE_H
#define __IWRECORD_FILE_H

#include "wcombase.h"
#ifdef _WIN32
#include <mmsystem.h>
#endif
#include "RecordFileDefine.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	// RecordFileWriter Component's GUID
	// {561EA257-2FC0-4b6e-84D9-5BB7703F314A}
	DEFINE_GUID( CLSID_RecordFileWriter, 
		0x561ea257, 0x2fc0, 0x4b6e, 0x84, 0xd9, 0x5b, 0xb7, 0x70, 0x3f, 0x31, 0x4a);

	// IRecordFileWriter Interface's GUID
	// {B8675B8B-0797-4c24-985F-5B0EAE7A3743}
	DEFINE_GUID( IID_IRecordFileWriter, 
		0xb8675b8b, 0x797, 0x4c24, 0x98, 0x5f, 0x5b, 0xe, 0xae, 0x7a, 0x37, 0x43);
	
#define RECORDFILE_VERSION			0

	typedef struct{

		DWORD				dwSize;			//�ܵĴ�С
		DWORD				dwVersion;		//�汾
		DWORD				dwRoomID;		//����ID
		WCHAR				wszRoomName[128];//��������
		BYTE				bHasAudio;		//�Ƿ�����Ƶ
		BYTE				bHasVideo;		//�Ƿ�����Ƶ
		BYTE				bHasChatMsg;	//�Ƿ���������Ϣ
		BYTE				bHasScreen;		//�Ƿ���ץ������
		DWORD				dwReserved;		//����
		DWORD				cbExtendData;	//��չ���ݴ�С,��չ���ݱ�����ڽṹ��ĺ���
		DWORD				dwColorTableSize;//ColorTable��С
		BITMAPINFOHEADER	bmiScreen;		//ץ��ͼ��ĸ�ʽ
		//���Color Table
		//���Extend Data
	}RecordFileProperty;

#define RECORDFILE_ATTRIBUTE_TITLE				0x00
#define RECORDFILE_ATTRIBUTE_COPYRIGHT			0x01
#define RECORDFILE_ATTRIBUTE_COPYRIGHTURL		0x02
#define RECORDFILE_ATTRIBUTE_DESCRIPTION		0x03
#define RECORDFILE_ATTRIBUTE_AUTHOR				0x04
#define RECORDFILE_ATTRIBUTE_PROVIDER			0x05
#define RECORDFILE_ATTRIBUTE_PUBLISHER			0x06
#define RECORDFILE_ATTRIBUTE_PROTECTIONTYPE		0x07
#define RECORDFILE_ATTRIBUTE_YEAR				0x08
	//----------------------------------------------------------------------------
	// IRecordFileWriter
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IRecordFileWriter, IUnknown)
	{
		//��������ļ���
		STDMETHOD( SetOutputFileName )( THIS_ WCHAR *wszFileName ) PURE;
		//�����ļ�����
		STDMETHOD( SetProperty )( THIS_ RecordFileProperty *pProperty ) PURE;
		//��������
		STDMETHOD( SetAttribute )( THIS_ DWORD dwAttributeType,WCHAR* wszValue ) PURE;
		//��ʼд�ļ�
		STDMETHOD( BeginWriting )( THIS_ ) PURE;
		//ֹͣд�ļ�
		STDMETHOD( EndWriting )( THIS_ ) PURE;
		//д����Ƶ����
		//qwTime:		��100nsΪ��λ
		STDMETHOD( WriteAudioData )( THIS_ ULONGLONG qwTime,DWORD dwUserID,BYTE bMediaID,PBYTE pbData,DWORD dwDataLen ) PURE;
		//д����Ƶ����
		STDMETHOD( WriteVideoData )( THIS_ ULONGLONG qwTime,DWORD dwUserID,BYTE bMediaID,PBYTE pbData,DWORD dwDataLen ) PURE;
		//д��ץ������
		STDMETHOD( WriteScreenData )( THIS_ ULONGLONG qwTime,PBYTE pbData,DWORD dwDataLen ) PURE;
		//д��������Ϣ
		STDMETHOD( WriteChatMsg )( THIS_ ULONGLONG qwTime,DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,WCHAR *wszMessage ) PURE;
		//д��״̬����
		STDMETHOD( WriteStatusData )( THIS_ ULONGLONG qwTime,PBYTE pbData,DWORD dwDataLen ) PURE;
		//д���Զ�������
		STDMETHOD( WriteCustomData )( THIS_ ULONGLONG qwTime,PBYTE pbData,DWORD dwDataLen ) PURE;	
		//����ý�����ͣ��벥�Ų��GUID���Ӧ
		STDMETHOD( SetMediaType )( THIS_ GUID* pFormatType,GUID* pSubType ) PURE;
	};
	
	// RecordFileReader Component's GUID
	// {0185B4F4-FE41-47c4-8C91-40748D67600D}
	DEFINE_GUID( CLSID_RecordFileReader, 
		0x185b4f4, 0xfe41, 0x47c4, 0x8c, 0x91, 0x40, 0x74, 0x8d, 0x67, 0x60, 0xd);
	
	// IRecordFileReader Interface's GUID
	// {29050D88-00AA-4de2-A4EF-387E7AA6DADC}
	DEFINE_GUID( IID_IRecordFileReader, 
		0x29050d88, 0xaa, 0x4de2, 0xa4, 0xef, 0x38, 0x7e, 0x7a, 0xa6, 0xda, 0xdc);
		
	//----------------------------------------------------------------------------
	// IRecordFileReader
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IRecordFileReader, IUnknown)
	{
	};
	
	// ScreenRecorder Component's GUID
	// {16FA842A-CE2E-42a5-B581-AC71B4DD65FE}
	DEFINE_GUID( CLSID_ScreenRecorder, 
		0x16fa842a, 0xce2e, 0x42a5, 0xb5, 0x81, 0xac, 0x71, 0xb4, 0xdd, 0x65, 0xfe);
	
	// IScreenRecorder Interface's GUID
	// {15CCDE4A-9EBA-47eb-BA1B-F4FD5099C928}
	DEFINE_GUID( IID_IScreenRecorder, 
		0x15ccde4a, 0x9eba, 0x47eb, 0xba, 0x1b, 0xf4, 0xfd, 0x50, 0x99, 0xc9, 0x28);

#define SCREENRECORD_PROFILE_SCREEN			0x01
#define SCREENRECORD_PROFILE_VIDEO			0x02

	typedef struct{

		int				nProfile;

		BOOL			bClipUponWnd;
		HWND			hCapWnd;
		int				nCapLeft;
		int				nCapTop;
		int				nCapWidth;
		int				nCapHeight;
		int				nVideoFrameRate;
		int				nVideoBitrate;

		BOOL			bHasAudio;
		int				nAudioSampleRate;
		int				nAudioChannels;
		int				nBitsPerSample;
		int				nAudioBitrate;
	}ScreenRecordParam;

	typedef struct{
		
		int				nSize;
		
		BOOL			bHasVideo;
		int				nProfile;
		BOOL			bClipUponWnd;
		HWND			hCapWnd;
		int				nCapLeft;
		int				nCapTop;
		int				nCapWidth;
		int				nCapHeight;
		int				nVideoFrameRate;
		int				nVideoBitrate;
		
		BOOL			bHasAudio;
		int				nAudioSampleRate;
		int				nAudioChannels;
		int				nBitsPerSample;
		int				nAudioBitrate;
	}ScreenRecordParam2;
	//----------------------------------------------------------------------------
	// IScreenRecorder
	//----------------------------------------------------------------------------
	DECLARE_INTERFACE_(IScreenRecorder, IUnknown)
	{
		STDMETHOD( StartRecord )( THIS_ ScreenRecordParam* pParam,WCHAR* wszFileName ) PURE;
		STDMETHOD( PauseRecord )( THIS_ BOOL bPause ) PURE;
		STDMETHOD( StopRecord )( THIS_ ) PURE;
		STDMETHOD( WriteAudioData )( THIS_ PBYTE pbData,DWORD dwDataLen ) PURE;
		STDMETHOD_( DWORD,GetRecordSeconds)( THIS_ ) PURE;
		STDMETHOD( StartRecord2 )( THIS_ ScreenRecordParam2* pParam,WCHAR* wszFileName ) PURE;
	};

#ifdef __cplusplus
}
#endif

#endif