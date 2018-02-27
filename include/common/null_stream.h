/*##############################################################################
 * 文件: null_stream.h
 * 描述: 提供空流对象的实现
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_NULL_STREAM_H_
#define FSLOG_NULL_STREAM_H_

#include "log_stream.h"

namespace FsMeeting
{

/*==============================================================================
 * 描述: 空流对象类(用于日志级别小于日志最低输出级别时候的处理)
 *============================================================================*/
class NullStream : public LogStream
{
public:
    NullStream() : LogStream(m_message_buffer, 0) {}
    // 获取流对象
    NullStream &Stream() { return *this; }
private:
    FS_CHAR m_message_buffer[2];
};

template<class T>
inline NullStream& operator<<(NullStream &stream, const T &) 
{
    return stream;
}

} // namespace FsMeeting

#endif // FSLOG_NULL_STREAM_H_
