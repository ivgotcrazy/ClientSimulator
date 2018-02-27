#ifndef __RECORD_FILE_DEFINE_H
#define __RECORD_FILE_DEFINE_H

// {3111F6AE-8F0B-4bad-B691-03C717BA9AAF}
DEFINE_GUID(MEDIATYPE_WRECORDRENDERPLUGIN, 
			0x3111f6ae, 0x8f0b, 0x4bad, 0xb6, 0x91, 0x3, 0xc7, 0x17, 0xba, 0x9a, 0xaf);

// {4E2DDA8A-A16D-4555-B363-9495BD56DF5D}
DEFINE_GUID(MEDIASUBTYPE_WRECORDSTREAM, 
			0x4e2dda8a, 0xa16d, 0x4555, 0xb3, 0x63, 0x94, 0x95, 0xbd, 0x56, 0xdf, 0x5d);

#pragma pack(1)

#define DATATYPE_AUDIO			0X01
#define DATATYPE_VIDEO			0X02
#define DATATYPE_SCREEN			0X03
#define DATATYPE_CHAT			0X04
#define DATATYPE_STATUS			0X05
#define DATATYPE_CUSTOM			0x06

typedef struct{

	BYTE	bDataType;
	BYTE	pbData[0];
}RECORD_COMMONDATA;

typedef struct{

	BYTE	bDataType;
	DWORD	dwUserID;
	BYTE	pbData[0];
}RECORD_USERDATA;

typedef struct{

	BYTE	bDataType;
	DWORD	dwUserID;
	BYTE	bMediaID;
	BYTE	pbData[0];
}RECORD_MEDIADATA;

typedef struct{

	BYTE	bDataType;
	DWORD	dwSrcUserID;
	DWORD	dwDstuserID;
	DWORD	dwColor;
	WCHAR	wszMsg[0];
}RECORD_CHATMSG;

#pragma pack()

#endif