#pragma once

#include "client_public.h"
#include "common_msg_processor.h"
#include "client_core_mgr.h"
#include "define.h"

using namespace clientcore;

namespace clientmgr
{

class VirtualClient
	: public CommonMsgProcessor
	, public std::enable_shared_from_this < VirtualClient >
{
public:
	VirtualClient(const ClientConfig& client_cfg,
		const ClientBaseComponents& base_comps);

	bool Init();
	bool Start();
	bool Stop();
	void OnTimer();

private:
	bool OnStateStart(const MsgData& msg_data);
	bool OnUpdateCheckResult(const MsgData& msg_data);
	bool OnLoginRep(const MsgData& msg_data);
	bool OnGetRoomListRep(const MsgData& msg_data);
	bool OnLoginFrontRoomRep(const MsgData& msg_data);
	bool OnLoginRoomRep(const MsgData& msg_data);

	void SendAvConfigMsg();
	void SendLoginFrontRoomMsg();
	void SendLoginMsg();
	void SendStartUpdateCheckMsg();
	void TryToSendLoginFrontRoomMsg();

	void NotifyLoginFail();

private:
	ClientBaseComponents m_base_comps;
	ClientConfig m_client_cfg;

	typedef std::shared_ptr<ClientCoreMgr> ClientCoreMgrSP;
	ClientCoreMgrSP	m_client_mgr;

	typedef std::vector<FrontRoomInfo> FrontRoomInfoVec;
	FrontRoomInfoVec m_room_list;

	// 统计登录时长
	FS_UINT32	m_login_start_time;
	FS_UINT32	m_login_end_time;

	FS_UINT32	m_local_user_id;
	std::string m_node_id;

	bool m_login_success;
};

typedef std::shared_ptr<VirtualClient> VirtualClientSP;

}