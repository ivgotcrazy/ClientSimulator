/*##############################################################################
 * 文件: log.h
 * 描述: fslog日志库的初始化接口和使用宏
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_H_
#define FSLOG_LOG_H_

#include "logging.h"
#include "log_message.h"
#include "null_stream.h"

// 初始化日志库接口
FsMeeting::ILogMgr* InitFSLog();

////////////////////////////////////////////////////////////////////////////////
//
// 模块在使用此处定义的日志前端时，必须定义以下几个宏：
// 1) FS_LOG_MGR    日志中心对象指针
// 2) FS_LOGGER_ID  日志器ID
// 3) FS_LOG_LEVEL  日志打印级别，大于等于此日志级别才打印
// 
// 这里提供一个参考例子，其中xxx代码模块名: 
// ILogMgr* g_xxx_log_mgr;
// #define FS_LOG_MGR g_xxx_log_mgr
//
// FS_INT g_xxx_logger_id;
// #define FS_LOGGER_ID g_xxx_logger_id
//
// LogLevel g_xxx_log_level;
// #define FS_LOG_LEVEL g_xxx_log_level

// 如果要使用用C++流风格日志前端，需要显示定义_CPLUSPLUS_STREAM_LOG
#ifdef _CPLUSPLUS_STREAM_LOG

#define FS_LOG(level) COMPACT_FS_LOG_ ## level

#define COMPACT_FS_LOG_INFO \
    (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_INFO \
        ? FsMeeting::LogMessage(FS_LOG_MGR, FS_LOGGER_ID, FsMeeting::LOG_LEVEL_INFO, __FILE__, __LINE__).Stream()\
        : FsMeeting::NullStream().Stream())

#define COMPACT_FS_LOG_TRACE \
    (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_TRACE \
        ? FsMeeting::LogMessage(FS_LOG_MGR, FS_LOGGER_ID, FsMeeting::LOG_LEVEL_TRACE, __FILE__, __LINE__).Stream()\
        : FsMeeting::NullStream().Stream())

#define COMPACT_FS_LOG_WARNING \
    (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_WARNING \
        ? FsMeeting::LogMessage(FS_LOG_MGR, FS_LOGGER_ID, FsMeeting::LOG_LEVEL_WARNING, __FILE__, __LINE__).Stream()\
        : FsMeeting::NullStream().Stream())

#define COMPACT_FS_LOG_ERROR \
    (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_ERROR \
        ? FsMeeting::LogMessage(FS_LOG_MGR, FS_LOGGER_ID, FsMeeting::LOG_LEVEL_ERROR, __FILE__, __LINE__).Stream()\
        : FsMeeting::NullStream().Stream())

#define COMPACT_FS_LOG_FATAL \
    (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_FATAL \
        ? FsMeeting::LogMessage(FS_LOG_MGR, FS_LOGGER_ID, FsMeeting::LOG_LEVEL_FATAL, __FILE__, __LINE__).Stream()\
        : FsMeeting::NullStream().Stream())

#else // C风格日志前端

#define FS_LOG_INFO(fmt, ...) \
    if (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_INFO) \
        FS_LOG_MGR->WriteLog(FS_LOGGER_ID, FsMeeting::LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ## __VA_ARGS__)

#define FS_LOG_TRACE(fmt, ...) \
    if (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_TRACE) \
        FS_LOG_MGR->WriteLog(FS_LOGGER_ID, FsMeeting::LOG_LEVEL_TRACE, __FILE__, __LINE__, fmt, ## __VA_ARGS__)

#define FS_LOG_WARNING(fmt, ...) \
    if (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_WARNING) \
        FS_LOG_MGR->WriteLog(FS_LOGGER_ID, FsMeeting::LOG_LEVEL_WARNING, __FILE__, __LINE__, fmt, ## __VA_ARGS__)

#define FS_LOG_ERROR(fmt, ...) \
    if (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_ERROR) \
        FS_LOG_MGR->WriteLog(FS_LOGGER_ID, FsMeeting::LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ## __VA_ARGS__)

#define FS_LOG_FATAL(fmt, ...) \
    if (FS_LOG_MGR != NULL && FS_LOGGER_ID != 0 && FS_LOG_LEVEL <= FsMeeting::LOG_LEVEL_FATAL) \
        FS_LOG_MGR->WriteLog(FS_LOGGER_ID, FsMeeting::LOG_LEVEL_FATAL, __FILE__, __LINE__, fmt, ## __VA_ARGS__)


#endif // _CPLUSPLUS_STREAM_LOG


#endif // FSLOG_LOG_MACRO_H_