/*##############################################################################
 * �ļ�: log.h
 * ����: fslog��־��ĳ�ʼ���ӿں�ʹ�ú�
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_H_
#define FSLOG_LOG_H_

#include "logging.h"
#include "log_message.h"
#include "null_stream.h"

// ��ʼ����־��ӿ�
FsMeeting::ILogMgr* InitFSLog();

////////////////////////////////////////////////////////////////////////////////
//
// ģ����ʹ�ô˴��������־ǰ��ʱ�����붨�����¼����꣺
// 1) FS_LOG_MGR    ��־���Ķ���ָ��
// 2) FS_LOGGER_ID  ��־��ID
// 3) FS_LOG_LEVEL  ��־��ӡ���𣬴��ڵ��ڴ���־����Ŵ�ӡ
// 
// �����ṩһ���ο����ӣ�����xxx����ģ����: 
// ILogMgr* g_xxx_log_mgr;
// #define FS_LOG_MGR g_xxx_log_mgr
//
// FS_INT g_xxx_logger_id;
// #define FS_LOGGER_ID g_xxx_logger_id
//
// LogLevel g_xxx_log_level;
// #define FS_LOG_LEVEL g_xxx_log_level

// ���Ҫʹ����C++�������־ǰ�ˣ���Ҫ��ʾ����_CPLUSPLUS_STREAM_LOG
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

#else // C�����־ǰ��

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