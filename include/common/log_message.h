/*##############################################################################
 * �ļ�: log_message.h
 * ����: ��־��Ϣ������
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
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
 * ����: ��־��Ϣ��¼�ʹ�����
 *============================================================================*/
class LogMessage {
public:
    LogMessage(ILogMgr* log_mgr, FS_INT logger_id, LogLevel level,
        const FS_CHAR* file, FS_UINT32 line);

    ~LogMessage();

    // flush��־��Ϣ����־��
    FS_VOID Flush();

    // �����־��Ϣ
    FS_VOID Fill(const FS_CHAR* fmt, va_list ap);

    // �����־��Ϣ�����ַ��汾��
    FS_VOID Fill(const FS_WCHAR* fmt, va_list ap);

    // ��ȡ��־��Ϣ��������
    std::ostream& Stream();

    // ��ȡĳ��־�������־����
    static FS_UINT64 NumMessages(LogLevel level);

private:
    // ��ʼ����־��
    FS_VOID Init(const FS_CHAR* file, FS_INT32 line);

    static FS_UINT64 m_num_messages[kLogLevelCnt];

    LogMessage(const LogMessage&);
    FS_VOID operator=(const LogMessage&);

    FS_INT m_logger_id;         //��־��ID
    LogStream* m_stream;        //��־��ָ��
    LogLevel m_level;           //��־����
    FS_CHAR* m_buf;             //��־������
    FS_INT32 m_prefix_len;      //��־ǰ׺����
    ILogMgr* m_log_mgr;         //��־��������
};

} // namespace FsMeeting

#endif // FSLOG_LOG_MESSAGE_H_