/*##############################################################################
 * �ļ���common_msg_processor.h
 * ������CommonMsgProcessor����
 * ���ߣ�Teck
 * ʱ�䣺2016��12��04��
 * ��Ȩ��Copyright(C) 2016 Fsmeeting.com. All rights reserved.
##############################################################################*/
#pragma once

#include "msg_processor.h"

namespace clientcore
{

/*==============================================================================
 * ��������ͨ��Ϣ��������װ����Ϣ�ַ����ᷢ���߳��л�
==============================================================================*/
class CommonMsgProcessor : public MsgProcessor
{
public:
	virtual void OnDownMsg(DownMsgType msg_type, const MsgData& msg_data) override
	{
		OnDefaultDownMsg(msg_type, msg_data);
	}

	virtual void OnUpMsg(UpMsgType msg_type, const MsgData& msg_data) override
	{
		OnDefaultUpMsg(msg_type, msg_data);
	}
};

}