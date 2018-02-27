/*##############################################################################
 * �ļ�: null_stream.h
 * ����: �ṩ���������ʵ��
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_NULL_STREAM_H_
#define FSLOG_NULL_STREAM_H_

#include "log_stream.h"

namespace FsMeeting
{

/*==============================================================================
 * ����: ����������(������־����С����־����������ʱ��Ĵ���)
 *============================================================================*/
class NullStream : public LogStream
{
public:
    NullStream() : LogStream(m_message_buffer, 0) {}
    // ��ȡ������
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
