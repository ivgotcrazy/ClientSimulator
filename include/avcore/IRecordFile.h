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

		DWORD				dwSize;			//总的大小
		DWORD				dwVersion;		//版本
		DWORD				dwRoomID;		//会议ID
		WCHAR				wszRoomName[128];//会议名称
		BYTE				bHasAudio;		//是否有音频
		BYTE				bHasVideo;		//是否有视频
		BYTE				bHasChatMsg;	//是否有聊天信息
		BYTE				bHasScreen;		//是否有抓屏数据
		DWORD				dwReserved;		//保留
		DWORD				cbExtendData;	//扩展数据大小,扩展数据必须跟在结构体的后面
		DWORD				dwColorTableSize;//ColorTable大小
		BITMAPINFOHEADER	bmiScreen;		//抓屏图象的格式
		//后跟Color Table
		//后跟Extend Data
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
		//设置输出文件名
		STDMETHOD( SetOutputFileName )( THIS_ WCHAR *wszFileName ) PURE;
		//设置文件属性
		STDMETHOD( SetProperty )( THIS_ RecordFileProperty *pProperty ) PURE;
		//设置属性
		STDMETHOD( SetAttribute )( THIS_ DWORD dwAttributeType,WCHAR* wszValue ) PURE;
		//开始写文件
		STDMETHOD( BeginWriting )( THIS_ ) PURE;
		//停止写文件
		STDMETHOD( EndWriting )( THIS_ ) PURE;
		//写入音频数据
		//qwTime:		以100ns为单位
		STDMETHOD( WriteAudioData )( THIS_ ULONGLONG qwTime,DWORD dwUserID,BYTE bMediaID,PBYTE pbData,DWORD dwDataLen ) PURE;
		//写入视频数据
		STDMETHOD( WriteVideoData )( THIS_ ULONGLONG qwTime,DWORD dwUserID,BYTE bMediaID,PBYTE pbData,DWORD dwDataLen ) PURE;
		//写入抓屏数据
		STDMETHOD( WriteScreenData )( THIS_ ULONGLONG qwTime,PBYTE pbData,DWORD dwDataLen ) PURE;
		//写入聊天消息
		STDMETHOD( WriteChatMsg )( THIS_ ULONGLONG qwTime,DWORD dwSrcUserID,DWORD dwDstUserID,DWORD dwColor,WCHAR *wszMessage ) PURE;
		//写入状态数据
		STDMETHOD( WriteStatusData )( THIS_ ULONGLONG qwTime,PBYTE pbData,DWORD dwDataLen ) PURE;
		//写入自定义数据
		STDMETHOD( WriteCustomData )( THIS_ ULONGLONG qwTime,PBYTE pbData,DWORD dwDataLen ) PURE;	
		//设置媒体类型，与播放插件GUID相对应
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