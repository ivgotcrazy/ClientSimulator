#pragma once

#include "tinyxml.h"
#include "define.h"

namespace clientmgr
{

class GlobalConfigMgr
{
public:
	static GlobalConfigMgr& GetInstance();

	bool Init();
	bool SerializeConfig();

	GlobalConfig& GetGlobalConfig();

private:
	bool ParseGlobalConfig(TiXmlElement* root);
	bool ParseAudioParamConfig(TiXmlElement* root);
	bool ParseVideoParamConfig(TiXmlElement* root);
	bool ParseUserListConfig(TiXmlElement* root);
	bool ParseNickUserRangeConfig(TiXmlElement* root);
	bool ParseLoginParamConfig(TiXmlElement* root);

	// 不允许拷贝和赋值
	GlobalConfigMgr() {}
	GlobalConfigMgr(const GlobalConfigMgr&) {}
	GlobalConfigMgr& operator=(const GlobalConfigMgr&) {}

private:
	std::string	m_config_file;
	GlobalConfig m_global_cfg;
};

}