/*##############################################################################
 * 文件: log_message.h
 * 描述: 日志信息类声明
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_MESSAGE_H_
#define FSLOG_LOG_MESSAGE_H_

#include "logging.h"
#include "log_stream.h"
#include "null_stream.h"
#include <stdarg.h>

namespace FsMeeting
{

/*==============================================================================
 * 描述: 日志信息记录和处理类
 *============================================================================*/
class LogMessage {
public:
    LogMessage(ILogMgr* log_mgr, FS_INT logger_id, LogLevel level,
        const FS_CHAR* file, FS_UINT32 line);

    ~LogMessage();

    // flush日志信息到日志器
    FS_VOID Flush();

    // 填充日志信息
    FS_VOID Fill(const FS_CHAR* fmt, va_list ap);

    // 填充日志信息（宽字符版本）
    FS_VOID Fill(const FS_WCHAR* fmt, va_list ap);

    // 获取日志信息的流对象
    std::ostream& Stream();

    // 获取某日志级别的日志条数
    static FS_UINT64 NumMessages(LogLevel level);

private:
    // 初始化日志流
    FS_VOID Init(const FS_CHAR* file, FS_INT32 line);

    static FS_UINT64 m_num_messages[kLogLevelCnt];

    LogMessage(const LogMessage&);
    FS_VOID operator=(const LogMessage&);

    FS_INT m_logger_id;         //日志器ID
    LogStream* m_stream;        //日志流指针
    LogLevel m_level;           //日志级别
    FS_CHAR* m_buf;             //日志缓冲区
    FS_INT32 m_prefix_len;      //日志前缀长度
    ILogMgr* m_log_mgr;         //日志管理中心
};

} // namespace FsMeeting

#endif // FSLOG_LOG_MESSAGE_H_