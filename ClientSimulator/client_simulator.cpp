#include "stdafx.h"

#include <atlconv.h>

#include <winitguid.h>
#define INITGUID
#include "ibasecomponent.h"
#include "isessionmanager.h"
#include "wtimermanager.h"
#include "framework.h"

#include "tinyxml.h"
#include "tixmlfunction.h"
#include "XMLProtocolParser.h"

#include "client_simulator.h"

using namespace clientcore;

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

}

ClientSimulator::ClientSimulator()
	: m_video_src_type(VIDEO_SRC_SELF_CREATE)
{
	m_base_comps.factory = nullptr;
	m_base_comps.network = nullptr;
	m_base_comps.session_mgr = nullptr;
}

bool ClientSimulator::ParseGlobalConfig(TiXmlElement* root)
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

bool ClientSimulator::ParseUserListConfig(TiXmlElement* root)
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

bool ClientSimulator::ParseNickUserRangeConfig(TiXmlElement* root)
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

bool ClientSimulator::ParseVideoParamConfig(TiXmlElement* root)
{
	char string_value[MAX_CHAR_SIZE];
	int int_value = 0;

	TiXmlElement *video_param = root->FirstChildElement("VideoParam");
	if (video_param)
	{
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
			LOG(_T("Failed to find PostfixNumBegin entry.\n"));
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
	}

	return true;
}

bool ClientSimulator::LoadConfig()
{
	WCHAR* module_path = GetModulePath(NULL);

	USES_CONVERSION;
	std::string config_file = T2A(module_path) + std::string("ClientSimulator.xml");

	TiXmlDocument doc;
	if (!doc.LoadFile(config_file.c_str()))
	{
		LOG(_T("Load Config File %s Failed.\n"), config_file.c_str());
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

	if (!ParseVideoParamConfig(root))
		return false;

	if (!ParseUserListConfig(root))
		return false;

	if (!ParseNickUserRangeConfig(root))
		return false;

	return true;
}

bool ClientSimulator::CreateBaseComponents(IComponentFactory* factory)
{
	m_base_comps.factory = factory;

	HRESULT hr = factory->CreateComponent(CLSID_SessionManager2,
		IID_ISessionManager2, NULL, (void**)&m_base_comps.session_mgr);
	if (FAILED(hr))
	{
		LOG(_T("Failed to create session manager.\n"));
		return false;
	}

	hr = m_base_comps.session_mgr->Start();
	if (FAILED(hr))
	{
		LOG(_T("Failed to start session manager.\n"));
		return false;
	}

	hr = factory->QueryInterface(IID_IWNetwork, (void**)&m_base_comps.network);
	if (FAILED(hr))
	{
		LOG(_T("Failed to query IID_IWNetwork.\n"));
		return false;
	}

	return true;
}

bool ClientSimulator::Init(IComponentFactory* factory)
{
	// 初始化从主线程调用进来，与处理线程不一样
	HRESULT hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		LOG(_T("Failed to call CoInitializeEx.\n"));
		return false;
	}

	if (!LoadConfig())
	{
		LOG(_T("Failed to load config.\n"));
		return false;
	}

	if (!CreateBaseComponents(factory))
	{
		LOG(_T("Failed to create base components.\n"));
		return false;
	}

	if (m_global_cfg.users.empty())
	{
		LOG(_T("None user.\n"));
		return false;
	}

	m_video_source.reset(new VideoSource(m_base_comps.factory, 
		m_global_cfg.video_param));
	if (!m_video_source->Start())
	{
		LOG(_T("Failed to start video source.\n"));
		return false;
	}

	return true;
}

bool ClientSimulator::Run()
{
	LOG(_T("ClientSimulator::Run.\n"));

	for each (UserInfo user_info in m_global_cfg.users)
	{
		ClientConfig client_cfg;
		client_cfg.client_mode		= m_global_cfg.common_info.client_mode;
		client_cfg.client_type		= m_global_cfg.common_info.client_type;
		client_cfg.client_ver		= m_global_cfg.common_info.client_ver;
		client_cfg.front_addr		= m_global_cfg.common_info.front_addr;
		client_cfg.front_app_id		= m_global_cfg.common_info.front_app_id;
		client_cfg.product_id		= m_global_cfg.common_info.product_id;
		client_cfg.room_app_id		= m_global_cfg.common_info.room_app_id;
		client_cfg.terminal_type	= m_global_cfg.common_info.terminal_type;
		client_cfg.room_id			= m_global_cfg.common_info.room_id;
		client_cfg.room_pwd			= m_global_cfg.common_info.room_pwd;
		client_cfg.if_recv_av		= m_global_cfg.common_info.if_recv_av;
		client_cfg.user_name		= user_info.user_name;
		client_cfg.user_pwd			= user_info.user_pwd;
		client_cfg.user_type		= user_info.user_type;
		client_cfg.video_count		= user_info.video_count;
		client_cfg.video_src		= m_video_source->GetVideoDevice();
		
		
		VirtualClientSP vclient(new VirtualClient(client_cfg, m_base_comps));
		if (!vclient->Start())
		{
			LOG(_T("Failed to start virtual client.\n"));
			continue;
		}

		m_virtual_clients.push_back(vclient);
	}

	return true;
}