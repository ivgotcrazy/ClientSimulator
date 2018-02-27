/*##############################################################################
 * �ļ�: log_streambuf.h
 * ����: �ṩ��־�����뻺����������֧��
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOG_STREAM_BUF_H_
#define FSLOG_LOG_STREAM_BUF_H_

#include <streambuf>
#include "fs_types.h"

namespace FsMeeting
{

/*==============================================================================
 * ����: ��־��������ʵ��
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