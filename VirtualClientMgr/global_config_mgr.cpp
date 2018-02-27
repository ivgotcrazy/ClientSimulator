#include "stdafx.h"

#include <atlconv.h>
#include <sstream>
#include <fstream>

#include "global_config_mgr.h"
#include "tixmlfunction.h"
#include "XMLProtocolParser.h"

using namespace clientmgr;

#define MAX_CHAR_SIZE	256


namespace
{

TCHAR* GetModulePath(HMODULE hModule)
{
	TCHAR  szPath[MAX_PATH];
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szDir[_MAX_DIR];

	GetModuleFileName(hModule, szPath, MAX_PATH);

	_tsplitpath(szPath, szDrive, szDir, NULL, NULL);

	_stprintf(szPath, _T("%s%s"), szDrive, szDir);

	static TCHAR  szModuelPath[MAX_PATH];

	return _tcscpy(szModuelPath, szPath);
}

void InsertUtf8BomHeader(const std::string& file)
{
	std::ifstream ifs(file.c_str(), std::ios_base::in);
	std::stringstream file_stream;
	file_stream << ifs.rdbuf();

	char utf8_bom[3] = {0xEF, 0xBB, 0xBF};

	std::ofstream ofs(file.c_str(), std::ios_base::out);
	ofs.write(utf8_bom, 3);
	ofs << file_stream.str();
}

}

GlobalConfigMgr& GlobalConfigMgr::GetInstance()
{
	static GlobalConfigMgr config_mgr;
	return config_mgr;
}

bool GlobalConfigMgr::Init()
{
	// 构造配置文件路径，后续还需要将配置序列化，所以将配置文件路径保存
	WCHAR* module_path = GetModulePath(NULL);

	USES_CONVERSION;
	m_config_file = T2A(module_path) + std::string("ClientSimulator.xml");

	TiXmlDocument doc;
	if (!doc.LoadFile(m_config_file.c_str()))
	{
		LOG(_T("Load Config File %s Failed.\n"), m_config_file.c_str());
		return false;
	}

	TiXmlElement *root = doc.FirstChildElement("root");
	if (NULL == root)
	{
		LOG(_T("Failed to find root entry.\n"));
		return false;
	}

	if (!ParseGlobalConfig(root))
		return false;

	if (!ParseAudioParamConfig(root))
		return false;

	if (!ParseVideoParamConfig(root))
		return false;

	if (!ParseUserListConfig(root))
		return false;

	if (!ParseNickUserRangeConfig(root))
		return false;

	if (!ParseLoginParamConfig(root))
		return false;

	return true;
}

bool GlobalConfigMgr::SerializeConfig()
{
	TiXmlDocument doc;
	std::string tmp;
	std::stringstream ss(tmp);
	USES_CONVERSION;

	char utf8_buf[512];

	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);

	TiXmlElement* root = new TiXmlElement("root");
	doc.LinkEndChild(root);

	// 前置服务器地址
	TiXmlComment* front_addr_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("前置服务器地址")), utf8_buf, 512);
	front_addr_comment->SetValue(utf8_buf);
	root->LinkEndChild(front_addr_comment);

	TiXmlElement* front_addr = new TiXmlElement("FrontAddr");
	front_addr->LinkEndChild(new TiXmlText(m_global_cfg.common_info.front_addr.c_str()));
	root->LinkEndChild(front_addr);

	// 会议服务AppID
	TiXmlComment* room_app_id_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("会议服务AppID")), utf8_buf, 512);
	room_app_id_comment->SetValue(utf8_buf);
	root->LinkEndChild(room_app_id_comment);

	TiXmlElement* room_app_id = new TiXmlElement("RoomAppID");
	ss << m_global_cfg.common_info.room_app_id;
	room_app_id->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(room_app_id);

	// 前置服务AppID
	TiXmlComment* front_app_id_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("前置服务AppID")), utf8_buf, 512);
	front_app_id_comment->SetValue(utf8_buf);
	root->LinkEndChild(front_app_id_comment);

	TiXmlElement* front_app_id = new TiXmlElement("FrontAppID");
	ss.str("");
	ss << m_global_cfg.common_info.front_app_id;
	front_app_id->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(front_app_id);

	// 产品ID
	TiXmlComment* product_id_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("产品ID")), utf8_buf, 512);
	product_id_comment->SetValue(utf8_buf);
	root->LinkEndChild(product_id_comment);

	TiXmlElement* product_id = new TiXmlElement("ProductID");
	product_id->LinkEndChild(new TiXmlText(m_global_cfg.common_info.product_id.c_str()));
	root->LinkEndChild(product_id);

	// 客户端版本
	TiXmlComment* client_version_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("客户端版本")), utf8_buf, 512);
	client_version_comment->SetValue(utf8_buf);
	root->LinkEndChild(client_version_comment);

	TiXmlElement* client_version = new TiXmlElement("ClientVersion");
	client_version->LinkEndChild(new TiXmlText(m_global_cfg.common_info.client_ver.c_str()));
	root->LinkEndChild(client_version);

	// 客户端模式
	TiXmlComment* client_mode_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("1:全功能，2:桌面合成，3:手机最小模式")), utf8_buf, 512);
	client_mode_comment->SetValue(utf8_buf);
	root->LinkEndChild(client_mode_comment);

	TiXmlElement* client_mode = new TiXmlElement("ClientMode");
	ss.str("");
	ss << m_global_cfg.common_info.client_mode;
	client_mode->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(client_mode);

	// 客户端类型
	TiXmlComment* client_type_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("1:视频会议，2:IM，3:G3")), utf8_buf, 512);
	client_type_comment->SetValue(utf8_buf);
	root->LinkEndChild(client_type_comment);

	TiXmlElement* client_type = new TiXmlElement("ClientType");
	ss.str("");
	ss << m_global_cfg.common_info.client_type;
	client_type->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(client_type);

	// 终端类型
	TiXmlComment* terminal_type_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("1:桌面端，2:硬件端，3:移动端，4:电话，5:录制")), utf8_buf, 512);
	terminal_type_comment->SetValue(utf8_buf);
	root->LinkEndChild(terminal_type_comment);

	TiXmlElement* terminal_type = new TiXmlElement("TerminalType");
	ss.str("");
	ss << m_global_cfg.common_info.terminal_type;
	terminal_type->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(terminal_type);

	// 会议室ID
	TiXmlComment* room_id_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("要登录的会议室，一次只能登录一个会议室")), utf8_buf, 512);
	room_id_comment->SetValue(utf8_buf);
	root->LinkEndChild(room_id_comment);

	TiXmlElement* room_id = new TiXmlElement("RoomID");
	ss.str("");
	ss << m_global_cfg.common_info.room_id;
	room_id->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(room_id);

	// 会议室密码
	TiXmlComment* room_pwd_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("会议室密码，没有密码则置空")), utf8_buf, 512);
	room_pwd_comment->SetValue(utf8_buf);
	root->LinkEndChild(room_pwd_comment);

	TiXmlElement* room_pwd = new TiXmlElement("RoomPwd");
	room_pwd->LinkEndChild(new TiXmlText(m_global_cfg.common_info.room_pwd.c_str()));
	root->LinkEndChild(room_pwd);

	// 用户视频设备个数
	TiXmlComment* video_count_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("用户视频设备个数，最大为6，User中配置优先级更高")), utf8_buf, 512);
	video_count_comment->SetValue(utf8_buf);
	root->LinkEndChild(video_count_comment);

	TiXmlElement* video_dev_count = new TiXmlElement("VideoDevCount");
	ss.str("");
	ss << m_global_cfg.common_info.video_count;
	video_dev_count->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(video_dev_count);

	// 是否接收音视频数据
	TiXmlComment* if_recv_av_data_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("是否接收远端音视频数据")), utf8_buf, 512);
	if_recv_av_data_comment->SetValue(utf8_buf);
	root->LinkEndChild(if_recv_av_data_comment);

	TiXmlElement* if_recv_av_data = new TiXmlElement("IfRecvAvData");
	ss.str("");
	ss << m_global_cfg.common_info.if_recv_av;
	if_recv_av_data->LinkEndChild(new TiXmlText(ss.str().c_str()));
	root->LinkEndChild(if_recv_av_data);

	// 登录参数
	TiXmlComment* login_param_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("用户登录速率控制")), utf8_buf, 512);
	login_param_comment->SetValue(utf8_buf);
	root->LinkEndChild(login_param_comment);

	TiXmlElement* login_param = new TiXmlElement("LoginParam");
	root->LinkEndChild(login_param);

	TiXmlElement* concurrent_login_count = new TiXmlElement("ConcurrentLoginCount");
	ss.str("");
	ss << m_global_cfg.login_param.concurrent_login_count;
	concurrent_login_count->LinkEndChild(new TiXmlText(ss.str().c_str()));
	login_param->LinkEndChild(concurrent_login_count);

	TiXmlElement* login_count_per_second = new TiXmlElement("LoginCountPerSecond");
	ss.str("");
	ss << m_global_cfg.login_param.login_count_per_second;
	login_count_per_second->LinkEndChild(new TiXmlText(ss.str().c_str()));
	login_param->LinkEndChild(login_count_per_second);

	// 音频参数
	TiXmlComment* audio_param_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("音频参数")), utf8_buf, 512);
	audio_param_comment->SetValue(utf8_buf);
	root->LinkEndChild(audio_param_comment);

	TiXmlElement* audio_param = new TiXmlElement("AudioParam");
	root->LinkEndChild(audio_param);

	TiXmlElement* audio_dev_index = new TiXmlElement("AudioDevIndex");
	ss.str("");
	ss << m_global_cfg.audio_param.audio_dev_index;
	audio_dev_index->LinkEndChild(new TiXmlText(ss.str().c_str()));
	audio_param->LinkEndChild(audio_dev_index);

	// 视频参数
	TiXmlComment* video_param_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("视频参数")), utf8_buf, 512);
	video_param_comment->SetValue(utf8_buf);
	root->LinkEndChild(video_param_comment);

	TiXmlElement* video_param = new TiXmlElement("VideoParam");
	root->LinkEndChild(video_param);

	TiXmlElement* video_dev_index = new TiXmlElement("VideoDevIndex");
	ss.str("");
	ss << m_global_cfg.video_param.video_dev_index;
	video_dev_index->LinkEndChild(new TiXmlText(ss.str().c_str()));
	video_param->LinkEndChild(video_dev_index);

	TiXmlElement* video_width = new TiXmlElement("Width");
	ss.str("");
	ss << m_global_cfg.video_param.width;
	video_width->LinkEndChild(new TiXmlText(ss.str().c_str()));
	video_param->LinkEndChild(video_width);

	TiXmlElement* height_height = new TiXmlElement("Height");
	ss.str("");
	ss << m_global_cfg.video_param.height;
	height_height->LinkEndChild(new TiXmlText(ss.str().c_str()));
	video_param->LinkEndChild(height_height);

	TiXmlElement* frame_rate = new TiXmlElement("FrameRate");
	ss.str("");
	ss << m_global_cfg.video_param.frame_rate;
	frame_rate->LinkEndChild(new TiXmlText(ss.str().c_str()));
	video_param->LinkEndChild(frame_rate);

	TiXmlElement* bit_rate = new TiXmlElement("BitRate");
	ss.str("");
	ss << m_global_cfg.video_param.bit_rate;
	bit_rate->LinkEndChild(new TiXmlText(ss.str().c_str()));
	video_param->LinkEndChild(bit_rate);

	TiXmlElement* encode_mode = new TiXmlElement("EncodeMode");
	ss.str("");
	ss << m_global_cfg.video_param.encode_mode;
	encode_mode->LinkEndChild(new TiXmlText(ss.str().c_str()));
	video_param->LinkEndChild(encode_mode);

	// 用户列表
	TiXmlComment* user_list_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("UserName配置的是注册用户，NickName配置的是匿名用户")), utf8_buf, 512);
	user_list_comment->SetValue(utf8_buf);
	root->LinkEndChild(user_list_comment);

	TiXmlElement* user_list = new TiXmlElement("UserList");
	root->LinkEndChild(user_list);

	for each (UserInfo user_info in m_global_cfg.users)
	{
		TiXmlElement* user = new TiXmlElement("User");
		user_list->LinkEndChild(user);

		if (user_info.user_type == USER_TYPE_REGISTER)
		{
			TiXmlElement* user_name = new TiXmlElement("UserName");
			user->LinkEndChild(user_name);
			USES_CONVERSION;
			user_name->LinkEndChild(new TiXmlText(T2A(user_info.user_name.c_str())));

			TiXmlElement* user_pwd = new TiXmlElement("UserPwd");
			user->LinkEndChild(user_pwd);
			user_pwd->LinkEndChild(new TiXmlText(user_info.user_pwd.c_str()));

			TiXmlElement* video_count = new TiXmlElement("VideoDevCount");
			user->LinkEndChild(video_count);
			ss.str("");
			ss << user_info.video_count;
			video_count->LinkEndChild(new TiXmlText(ss.str().c_str()));
		}
		else if (user_info.user_type == USER_TYPE_UNREGISTER)
		{
			TiXmlElement* nick_name = new TiXmlElement("NickName");
			user->LinkEndChild(nick_name);
			USES_CONVERSION;
			nick_name->LinkEndChild(new TiXmlText(T2A(user_info.user_name.c_str())));
		}
		else
		{
			LOG(_T("Invaid user type = %u.\n"), user_info.user_type);
		}	
	}

	TiXmlComment* batch_anonymous_comment = new TiXmlComment();
	ConvertAnsiToUtf8(T2A(_T("批量配置匿名用户")), utf8_buf, 512);
	batch_anonymous_comment->SetValue(utf8_buf);
	root->LinkEndChild(batch_anonymous_comment);

	TiXmlComment* batch_example_comment = new TiXmlComment();
	batch_example_comment->SetValue(
		"<NickUserRange>\n \
			<BaseNickName>fs_</BaseNickName>\n \
			<PostfixNumBegin>1</PostfixNumBegin>\n \
			<PostfixNumEnd>300</PostfixNumEnd>\n \
		</NickUserRange>");
	root->LinkEndChild(batch_example_comment);
	
	if (!doc.SaveFile(m_config_file.c_str()))
		return false;

	// TinyXML写入文件时，默认不会写入BOM，这里手动写入BOM
	InsertUtf8BomHeader(m_config_file);

	return true;
}

GlobalConfig& GlobalConfigMgr::GetGlobalConfig()
{
	return m_global_cfg;
}

bool GlobalConfigMgr::ParseGlobalConfig(TiXmlElement* root)
{
	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	if (!TiXmlGetElementValue(root, "FrontAddr", string_value, MAX_CHAR_SIZE))
	{
		LOG(_T("Failed to find FrontAddr entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.front_addr = string_value;
	}

	// RoomAppID
	if (!TiXmlGetElementValue(root, "RoomAppID", int_value))
	{
		LOG(_T("Failed to find RoomAppID entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.room_app_id = int_value;
	}

	if (!TiXmlGetElementValue(root, "FrontAppID", int_value))
	{
		LOG(_T("Failed to find FrontAppID entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.front_app_id = int_value;
	}

	// ProductID
	if (!TiXmlGetElementValue(root, "ProductID", string_value, MAX_CHAR_SIZE))
	{
		LOG(_T("Failed to find ProductID entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.product_id = string_value;
	}

	// ClientVersion
	if (!TiXmlGetElementValue(root, "ClientVersion", string_value, MAX_CHAR_SIZE))
	{
		LOG(_T("Failed to find ClientVersion entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.client_ver = string_value;
	}

	// ClientMode
	if (!TiXmlGetElementValue(root, "ClientMode", int_value))
	{
		LOG(_T("Failed to find ClientMode entry.\n"));
		return false;
	}
	else
	{
		if (int_value <= 0 || int_value > 3)
		{
			LOG(_T("Invalid ClientMode = %d.\n"), int_value);
			return false;
		}
		else
		{
			m_global_cfg.common_info.client_mode = static_cast<ClientMode>(int_value);
		}
	}

	// ClientType
	if (!TiXmlGetElementValue(root, "ClientType", int_value))
	{
		LOG(_T("Failed to find ClientType entry.\n"));
		return false;
	}
	else
	{
		if (int_value <= 0 || int_value > 3)
		{
			LOG(_T("Invalid ClientType = %d.\n"), int_value);
			return false;
		}
		else
		{
			m_global_cfg.common_info.client_type = static_cast<ClientType>(int_value);
		}
	}

	// TerminalType
	if (!TiXmlGetElementValue(root, "TerminalType", int_value))
	{
		LOG(_T("Failed to find TerminalType entry.\n"));
		return false;
	}
	else
	{
		if (int_value <= 0 || int_value > 5)
		{
			LOG(_T("Invalid TerminalType = %d.\n"), int_value);
			return false;
		}
		else
		{
			m_global_cfg.common_info.terminal_type = static_cast<TerminalType>(int_value);
		}
	}

	// RoomID
	if (!TiXmlGetElementValue(root, "RoomID", int_value))
	{
		LOG(_T("Failed to find RoomID entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.room_id = int_value;
	}

	// RoomPwd
	if (!TiXmlGetElementValue(root, "RoomPwd", string_value, MAX_CHAR_SIZE))
	{
		LOG(_T("Failed to find RoomPwd entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.room_pwd = string_value;
	}

	// VideoDevCount
	if (!TiXmlGetElementValue(root, "VideoDevCount", int_value))
	{
		LOG(_T("Failed to find VideoDevCount entry.\n"));
		return false;
	}
	else
	{
		if (int_value < 0 || int_value > 6)
		{
			LOG(_T("Invalid VideoDevCount = %d.\n"), int_value);
			return false;
		}
		else
		{
			m_global_cfg.common_info.video_count = int_value;
		}
	}

	// IfRecvAvData
	if (!TiXmlGetElementValue(root, "IfRecvAvData", int_value))
	{
		LOG(_T("Failed to find IfRecvAvData entry.\n"));
		return false;
	}
	else
	{
		m_global_cfg.common_info.if_recv_av = int_value == 0 ? false : true;
	}

	return true;
}

bool GlobalConfigMgr::ParseUserListConfig(TiXmlElement* root)
{
	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	TiXmlElement *user_list = root->FirstChildElement("UserList");
	while (user_list)
	{
		TiXmlElement *user_entry = user_list->FirstChildElement("User");
		while (user_entry)
		{
			UserInfo user_info;

			// 默认使用全局配置的视频设备个数
			user_info.video_count = m_global_cfg.common_info.video_count;

			if (TiXmlGetElementValue(user_entry, "UserName", string_value, MAX_CHAR_SIZE))
			{
				user_info.user_type = USER_TYPE_REGISTER;

				WCHAR wuser_name[MAX_CHAR_SIZE];
				ConvertUtf8ToUnicode(string_value, wuser_name, MAX_CHAR_SIZE);
				user_info.user_name = wuser_name;

				if (!TiXmlGetElementValue(user_entry, "UserPwd", string_value, MAX_CHAR_SIZE))
				{
					LOG(_T("Failed to find UserPwd entry.\n"));
					return false;
				}
				else
				{
					user_info.user_pwd = string_value;
				}

				if (TiXmlGetElementValue(user_entry, "VideoDevCount", int_value))
				{
					if (int_value < 0 || int_value > 6)
					{
						LOG(_T("Invalid user video device count = %d.\n"), int_value);
						return false;
					}
					else
					{
						user_info.video_count = int_value;
					}
				}
			}
			else
			{
				if (TiXmlGetElementValue(user_entry, "NickName", string_value, MAX_CHAR_SIZE))
				{
					user_info.user_type = USER_TYPE_UNREGISTER;

					WCHAR wuser_name[MAX_CHAR_SIZE];
					ConvertUtf8ToUnicode(string_value, wuser_name, MAX_CHAR_SIZE);
					user_info.user_name = wuser_name;
				}
				else
				{
					LOG(_T("Failed to find NickName entry.\n"));
					return false;
				}

				if (TiXmlGetElementValue(user_entry, "VideoDevCount", int_value))
				{
					if (int_value < 0 || int_value > 6)
					{
						LOG(_T("Invalid user video device count = %d.\n"), int_value);
						return false;
					}
					else
					{
						user_info.video_count = int_value;
					}
				}
			}

			m_global_cfg.users.push_back(user_info);
			user_entry = user_entry->NextSiblingElement("User");
		}
		user_list = user_list->NextSiblingElement("UserList");
	}

	return true;
}

bool GlobalConfigMgr::ParseNickUserRangeConfig(TiXmlElement* root)
{
	// TODO: NickUserRange

	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	TiXmlElement *user_range = root->FirstChildElement("NickUserRange");
	while (user_range)
	{
		std::string base_nick_name;
		FS_UINT32	postfix_begin = 0;
		FS_UINT32	postfix_end = 0;

		if (!TiXmlGetElementValue(user_range, "BaseNickName", string_value, MAX_CHAR_SIZE))
		{
			LOG(_T("Failed to find UserPwd entry.\n"));
			return false;
		}
		else
		{
			base_nick_name = string_value;
		}

		if (TiXmlGetElementValue(user_range, "PostfixNumBegin", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid PostfixNumBegin = %d.\n"), int_value);
				return false;
			}
			else
			{
				postfix_begin = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find PostfixNumBegin entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(user_range, "PostfixNumEnd", int_value))
		{
			if (int_value < postfix_begin)
			{
				LOG(_T("Invalid PostfixNumEnd = %d.\n"), int_value);
				return false;
			}
			else
			{
				postfix_end = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find PostfixNumEnd entry.\n"));
			return false;
		}

		for (int i = postfix_begin; i <= postfix_end; i++)
		{
			UserInfo user_info;

			char tmp[16];
			itoa(i, tmp, 10);

			USES_CONVERSION;
			user_info.user_name = A2T((base_nick_name + tmp).c_str());
			user_info.if_recv_av = m_global_cfg.common_info.if_recv_av;
			user_info.user_type = USER_TYPE_UNREGISTER;
			user_info.video_count = m_global_cfg.common_info.video_count;

			m_global_cfg.users.push_back(user_info);
		} // for

		user_range = user_range->NextSiblingElement("NickUserRange");
	} // while

	return true;
}

bool GlobalConfigMgr::ParseLoginParamConfig(TiXmlElement* root)
{
	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	TiXmlElement *login_param = root->FirstChildElement("LoginParam");
	if (login_param)
	{
		if (TiXmlGetElementValue(login_param, "ConcurrentLoginCount", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid VideoDevIndex = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.login_param.concurrent_login_count = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find ConcurrentLoginCount entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(login_param, "LoginCountPerSecond", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid Width = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.login_param.login_count_per_second = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find LoginCountPerSecond entry.\n"));
			return false;
		}
	}

	return true;
}

bool GlobalConfigMgr::ParseAudioParamConfig(TiXmlElement* root)
{
	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	TiXmlElement *audio_param = root->FirstChildElement("AudioParam");
	if (audio_param)
	{
		if (TiXmlGetElementValue(audio_param, "AudioDevIndex", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid AudioDevIndex = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.audio_param.audio_dev_index = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find AudioDevIndex entry.\n"));
			return false;
		}
	}

	return true;
}

bool GlobalConfigMgr::ParseVideoParamConfig(TiXmlElement* root)
{
	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	TiXmlElement *video_param = root->FirstChildElement("VideoParam");
	if (video_param)
	{
		if (TiXmlGetElementValue(video_param, "VideoDevIndex", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid VideoDevIndex = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.video_param.video_dev_index = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find VideoDevIndex entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(video_param, "Width", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid Width = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.video_param.width = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find Width entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(video_param, "Height", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid Height = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.video_param.height = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find Height entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(video_param, "FrameRate", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid FrameRate = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.video_param.frame_rate = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find FrameRate entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(video_param, "BitRate", int_value))
		{
			if (int_value < 0)
			{
				LOG(_T("Invalid BitRate = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.video_param.bit_rate = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find BitRate entry.\n"));
			return false;
		}

		if (TiXmlGetElementValue(video_param, "EncodeMode", int_value))
		{
			if (int_value < 0 || int_value >= 3)
			{
				LOG(_T("Invalid EncodeMode = %d.\n"), int_value);
				return false;
			}
			else
			{
				m_global_cfg.video_param.encode_mode = int_value;
			}
		}
		else
		{
			LOG(_T("Failed to find EncodeMode entry.\n"));
			return false;
		}
	}

	return true;
}