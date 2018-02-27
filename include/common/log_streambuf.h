/*##############################################################################
 * 文件: log_streambuf.h
 * 描述: 提供日志流输入缓冲区的类型支持
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_STREAM_BUF_H_
#define FSLOG_LOG_STREAM_BUF_H_

#include <streambuf>
#include "fs_types.h"

namespace FsMeeting
{

/*==============================================================================
 * 描述: 日志流缓冲类实现
 *============================================================================*/
class LogStreamBuf : public std::streambuf
{
public:
    LogStreamBuf(FS_CHAR* buf, FS_INT32 len)
    {
        setp(buf, buf + len);
    }

    virtual int_type overflow(int_type ch)
    {
        return ch;
    }

    FS_INT32 Length() const
    {
        return pptr() - pbase();
    }
};

} // namespace FsMeeting

#endif // FSLOG_LOG_STREAM_BUF_H_