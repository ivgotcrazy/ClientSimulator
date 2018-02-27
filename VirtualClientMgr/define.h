#pragma once

#include <memory>
#include <vector>
#include "client_public.h"

using namespace clientcore;

namespace clientmgr
{

struct UserInfo
{
	UserType		user_type;
	tstring			user_name;
	std::string		user_pwd;

	FS_UINT32		video_count;
	bool			if_recv_av;
};

struct CommonInfo
{
	std::string		client_ver;
	std::string		product_id;

	std::string		front_addr;
	FS_UINT32		front_app_id;
	FS_UINT32		room_app_id;

	ClientType		client_type;
	TerminalType	terminal_type;
	ClientMode		client_mode;

	FS_UINT32		room_id;
	std::string		room_pwd;

	FS_UINT32		video_count;
	bool			if_recv_av;
};

struct VideoParamInfo
{
	FS_UINT32	video_dev_index;
	FS_UINT32	width;
	FS_UINT32	height;
	FS_UINT32	frame_rate;
	FS_UINT32	bit_rate;
	FS_UINT32	encode_mode;
};

struct AudioParamInfo
{
	FS_UINT32	audio_dev_index;
};

struct LoginParamInfo
{
	FS_UINT32	concurrent_login_count;
	FS_UINT32	login_count_per_second;
};

struct GlobalConfig
{
	CommonInfo		common_info;
	VideoParamInfo	video_param;
	AudioParamInfo	audio_param;
	LoginParamInfo	login_param;
	std::vector<UserInfo> users;
};

typedef std::vector<std::wstring> VideoDevNameVec;
typedef std::vector<std::wstring> AudioDevNameVec;

}
