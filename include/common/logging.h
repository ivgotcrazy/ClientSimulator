/*##############################################################################
 * �ļ�: logging.h
 * ����: �ṩ��־��ǰ����ص���Ϣ
 * ����: Daniel(yuanlh@fsmeeting.com)
 * ����: 2015��01��04��
 * ��Ȩ: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOGGING_H_
#define FSLOG_LOGGING_H_

#include "fs_types.h"

namespace FsMeeting
{

// ��־����
enum LogLevel
{
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

// ��־��ɫ
enum LogColor
{
    COLOR_DEFAULT,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW
};

const FS_INT32 kLogLevelBase = 1;
const FS_INT32 kLogLevelCnt = 5;

const FS_CHAR* const kLogLevelNames[kLogLevelCnt] =
{
    "INFO",
    "TRACE",
    "WARNING",
    "ERROR",
    "FATAL"
};

const LogColor kLogLevelColor[kLogLevelCnt] =
{
    COLOR_DEFAULT,
    COLOR_DEFAULT,
    COLOR_YELLOW,
    COLOR_RED,
    COLOR_RED
};

// �ж��Ƿ�Ϊ�Ϸ���־����
#define IS_LEGAL_LOG_LEVEL(level)  \
    ((level) >= kLogLevelBase && (level) < kLogLevelBase + kLogLevelCnt)
// ��ȡ��־�����Ӧ������
#define INDEX_OF_LOG_LEVEL(level)   ((level) - kLogLevelBase)
// ��ȡ��־������Ӧ�ļ���
#define MAKE_LOG_LEVEL(index)   (static_cast<LogLevel>((index) + kLogLevelBase))

////////////////////////////////////////////////////////////////////////////////

// ��־��¼��
enum LoggerMode
{
    LOG_TO_FILE = 1,        //�ļ�
    LOG_TO_CONSOLE = 1 << 1,//����̨
    LOG_TO_DEBUG = 1 << 2   //����
};
const FS_INT32 kLoggerModeCnt = 3;

// ��ȡ��־��¼��������Ӧ������
#define MAKE_LOGGER_MODE(index)   (static_cast<LoggerMode>( 1 << (index)))

////////////////////////////////////////////////////////////////////////////////

// ���ĵ�����־�ļ���С
const FS_INT32 kMaxLogFileSize = 10 * 1024 * 1024;

// ������־��Ϣ���ռ�õĿռ��С
const FS_INT32 kMaxLogMessageBufLen = 4096;

////////////////////////////////////////////////////////////////////////////////

struct LoggerParam
{
    FS_CHAR     logger_name[64];        //��־������(ģ��������������ģ����־�ļ�����)
    FS_UINT32   logger_mode;            //��־��ģʽ���ļ�/����̨/���ԣ�
    bool        encrypt;                //��־�����Ƿ����
    LoggerParam():logger_mode(LOG_TO_FILE),encrypt(false){logger_name[0]='\0';}
};

/*==============================================================================
 * ����: ��־�������Ľӿ���
 *============================================================================*/
class ILogMgr
{
public:
    /*--------------------------------------------------------------------------
     * ��  ������Ҫ��ӡ��־��ģ���ڴ�ӡ��־ǰ����Ҫ���ô˽ӿ�����־��������ע�ᡣ
     *         ��־�������Ļ�Ϊÿһ��ע���ģ�鴴��һ����������־�ļ���
     * ��  ����[in] logger_param ��־������
     * ����ֵ��ȫ��Ψһ����־��ID��ģ������־���ļ�¼��־ʱ����Ҫ�ṩ��ID��
     *        ����0,����ע��ʧ�ܡ�
     *------------------------------------------------------------------------*/
    virtual FS_INT RegisterLogger(const LoggerParam& logger_param) = 0;

    /*--------------------------------------------------------------------------
     * ��  ����ģ����ô˽ӿ�֪ͨ��־���Ĳ���ʹ����־���ܡ�
     * ��  ����[in] logger_id ��־��ID
     * ����ֵ����
     *------------------------------------------------------------------------*/
    virtual FS_VOID UnregisterLogger(FS_INT logger_id) = 0;

    /*--------------------------------------------------------------------------
     * ��  �����˽ӿ��ṩ��C++�������־ǰ��ʹ�ã��˽ӿ�ֻ�����¼�Ѿ���ʽ��
     *         �õ���־���ݣ���־ǰ����Ҫ�Լ�������־ǰ׺����־��ʽ����
     * ��  ����[in] logger_id ��־��ID
     *         [in] log_msg ��־����
     *         [in] log_len ��־����
     *         [in] log_level ��־����
     * ����ֵ����
     *------------------------------------------------------------------------*/
    virtual FS_VOID WriteLog(
        FS_INT logger_id,
        const FS_CHAR* log_msg,
        FS_UINT32 log_len,
        LogLevel log_level
        ) = 0;

    /*--------------------------------------------------------------------------
     * ��  �����˽ӿ��ṩ��C�����־ǰ��ʹ�ã���־���ĸ��������־ǰ׺�͸�ʽ����
     *         ־���ݡ�
     * ��  ����[in] logger_id ��־��ID
     *         [in] log_level ��־����
     *         [in] file ��ӡ��־��Դ�ļ���
     *         [in] line ��ӡ��־Դ�ļ����к�
     *         [in] fmt ��־��ʽ���ַ���
     *         [in] ... �ɱ���־����
     * ����ֵ����
     *------------------------------------------------------------------------*/
    virtual FS_VOID WriteLog(
        FS_INT logger_id,
        LogLevel log_level, 
        const FS_CHAR* file,
        FS_UINT32 line,
        const FS_CHAR* fmt,
        ...
        ) = 0;

    /*--------------------------------------------------------------------------
    * ��  �����˽ӿ��ṩ��C�����־ǰ��ʹ�ã���־���ĸ��������־ǰ׺�͸�ʽ����
    *         ־���ݣ����ַ��汾����
    * ��  ����[in] logger_id ��־��ID
    *         [in] log_level ��־����
    *         [in] file ��ӡ��־��Դ�ļ���
    *         [in] line ��ӡ��־Դ�ļ����к�
    *         [in] fmt ��־��ʽ���ַ���
    *         [in] ... �ɱ���־����
    * ����ֵ����
    *------------------------------------------------------------------------*/
    virtual FS_VOID WriteLog(
        FS_INT logger_id,
        LogLevel log_level,
        const FS_CHAR* file,
        FS_UINT32 line,
        const FS_WCHAR* fmt,
        ...
        ) = 0;

    /*--------------------------------------------------------------------------
     * ��  ��: ������־�ı���ʱ��
     * ��  ��: [in] days ���������
     * ����ֵ: ��
     *------------------------------------------------------------------------*/
    virtual FS_VOID SetLogSaveDays(FS_UINT32 days) = 0;

};

} // namespace FsMeeting

#endif // FSLOG_LOGGING_H_
