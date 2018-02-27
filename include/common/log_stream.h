/*##############################################################################
 * 文件: log_stream.h
 * 描述: 提供对日志流式输入的类型支持
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_STREAM_H_
#define FSLOG_LOG_STREAM_H_

#include <ostream>
#include "fs_types.h"
#include "log_streambuf.h"

namespace FsMeeting
{

/*==============================================================================
 * 描述: 日志流类实现
 *============================================================================*/
class LogStream : public std::ostream
{
public:
    LogStream(FS_CHAR* buf, FS_INT32 len)
        : std::ostream(NULL)
        , m_streambuf(buf, len)
    {
        rdbuf(&m_streambuf);
    }
    FS_INT32 Length() const
    {
        return m_streambuf.Length();
    }

private:
    LogStreamBuf m_streambuf;
};

} // namespace FsMeeting

#endif // FSLOG_LOG_STREAM_H_