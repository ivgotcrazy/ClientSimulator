/*##############################################################################
 * �ļ�: log_util.h
 * ����: �ṩ�����ʹ��fslog��־��Ľӿ�(���ܲ�����ʱ,��ֱ�ӷ�Ч���ļ�ʹ��log.h)
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_UTIL_H_
#define FSLOG_LOG_UTIL_H_

#include "log.h"

#ifdef _FS_OS_WIN
#pragma comment(lib, "fslog.lib")
#endif

namespace FSLogUtil
{

// ��־��������
FsMeeting::ILogMgr * g_xxx_log_mgr = NULL;
#define FS_LOG_MGR FSLogUtil::g_xxx_log_mgr

// ��־��ID
FsMeeting::FS_INT g_xxx_logger_id = 0;
#define FS_LOGGER_ID FSLogUtil::g_xxx_logger_id

// ��־����������
FsMeeting::LogLevel g_xxx_log_level = FsMeeting::LOG_LEVEL_INFO;
#define FS_LOG_LEVEL FSLogUtil::g_xxx_log_level


/*------------------------------------------------------------------------------
 * ��  ��: ��ʼ��fslog��־��
 * ��  ��: [in] module_name ģ������
 * ����ֵ: ��
 * ʱ  ��: 2015��01��04��
 * ��  ��: Daniel
 *----------------------------------------------------------------------------*/
FsMeeting::FS_VOID InitFSLogLibrary(const FsMeeting::FS_CHAR* module_name)
{
    FS_LOG_MGR = InitFSLog();
    FsMeeting::LoggerParam logger_param;
    strncpy(logger_param.logger_name, module_name, sizeof(logger_param.logger_name));
    logger_param.logger_mode = FsMeeting::LOG_TO_FILE;
#ifdef _DEBUG
    logger_param.logger_mode |= FsMeeting::LOG_TO_CONSOLE | FsMeeting::LOG_TO_DEBUG;
#endif
    logger_param.encrypt = false;
    FS_LOGGER_ID = FS_LOG_MGR->RegisterLogger(logger_param);
}

/*------------------------------------------------------------------------------
 * ��  ��: ����ʼ��fslog��־��
 * ����ֵ: ��
 * ʱ  ��: 2015��01��04��
 * ��  ��: Daniel
 *----------------------------------------------------------------------------*/
FsMeeting::FS_VOID UninitFSLogLibrary()
{
    FS_LOG_MGR->UnregisterLogger(FS_LOGGER_ID);
    FS_LOGGER_ID = 0;
}

} // namespace FSLogUtil


#endif // FSLOG_LOG_UTIL_H_