/*##############################################################################
 * �ļ�: log_stream.h
 * ����: �ṩ����־��ʽ���������֧��
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_STREAM_H_
#define FSLOG_LOG_STREAM_H_

#include <ostream>
#include "fs_types.h"
#include "log_streambuf.h"

namespace FsMeeting
{

/*==============================================================================
 * ����: ��־����ʵ��
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