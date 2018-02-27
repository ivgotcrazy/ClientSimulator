#pragma once

#include <memory>
#include "tinyxml.h"
#include "client_public.h"
#include "client_core_mgr.h"
#include "common_msg_processor.h"
#include "virtual_client.h"
#include "define.h"
#include "video_source.h"

using namespace clientcore;

class IComponentFactory;

class ClientSimulator : public clientcore::CommonMsgProcessor
{
public:
	ClientSimulator();

	bool Init(IComponentFactory* factory);
	bool Run();

private:
	bool LoadConfig();
	bool ParseGlobalConfig(TiXmlElement* root);
	bool ParseVideoParamConfig(TiXmlElement* root);
	bool ParseUserListConfig(TiXmlElement* root);
	bool ParseNickUserRangeConfig(TiXmlElement* root);

	bool CreateBaseComponents(IComponentFactory* factory);

private:
	ClientBaseComponents	m_base_comps;
	GlobalConfig			m_global_cfg;

	typedef std::shared_ptr<VirtualClient> VirtualClientSP;
	typedef std::vector<VirtualClientSP> VirtualClientSPVec;

	VirtualClientSPVec		m_virtual_clients;

	VideoSrcType			m_video_src_type;

	typedef std::shared_ptr<VideoSource> VideoSourceSP;
	VideoSourceSP			m_video_source;
};