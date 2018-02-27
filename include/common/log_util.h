/*##############################################################################
 * 文件: log_util.h
 * 描述: 提供方便的使用fslog日志库的接口(功能不满足时,可直接仿效本文件使用log.h)
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_UTIL_H_
#define FSLOG_LOG_UTIL_H_

#include "log.h"

#ifdef _FS_OS_WIN
#pragma comment(lib, "fslog.lib")
#endif

namespace FSLogUtil
{

// 日志管理中心
FsMeeting::ILogMgr * g_xxx_log_mgr = NULL;
#define FS_LOG_MGR FSLogUtil::g_xxx_log_mgr

// 日志器ID
FsMeeting::FS_INT g_xxx_logger_id = 0;
#define FS_LOGGER_ID FSLogUtil::g_xxx_logger_id

// 日志最低输出级别
FsMeeting::LogLevel g_xxx_log_level = FsMeeting::LOG_LEVEL_INFO;
#define FS_LOG_LEVEL FSLogUtil::g_xxx_log_level


/*------------------------------------------------------------------------------
 * 描  述: 初始化fslog日志库
 * 参  数: [in] module_name 模块名称
 * 返回值: 无
 * 时  间: 2015年01月04日
 * 作  者: Daniel
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
 * 描  述: 反初始化fslog日志库
 * 返回值: 无
 * 时  间: 2015年01月04日
 * 作  者: Daniel
 *----------------------------------------------------------------------------*/
FsMeeting::FS_VOID UninitFSLogLibrary()
{
    FS_LOG_MGR->UnregisterLogger(FS_LOGGER_ID);
    FS_LOGGER_ID = 0;
}

} // namespace FSLogUtil


#endif // FSLOG_LOG_UTIL_H_