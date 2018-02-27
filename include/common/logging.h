/*##############################################################################
 * 文件: logging.h
 * 描述: 提供日志库前端相关的信息
 * 作者: Daniel(yuanlh@fsmeeting.com)
 * 创建: 2015年01月04日
 * 版权: Copyright(C) 2015 Fsmeeting.com. All rights reserved.
 *############################################################################*/
#ifndef FSLOG_LOGGING_H_
#define FSLOG_LOGGING_H_

#include "fs_types.h"

namespace FsMeeting
{

// 日志级别
enum LogLevel
{
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

// 日志颜色
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

// 判断是否为合法日志级别
#define IS_LEGAL_LOG_LEVEL(level)  \
    ((level) >= kLogLevelBase && (level) < kLogLevelBase + kLogLevelCnt)
// 获取日志级别对应的索引
#define INDEX_OF_LOG_LEVEL(level)   ((level) - kLogLevelBase)
// 获取日志索引对应的级别
#define MAKE_LOG_LEVEL(index)   (static_cast<LogLevel>((index) + kLogLevelBase))

////////////////////////////////////////////////////////////////////////////////

// 日志记录器
enum LoggerMode
{
    LOG_TO_FILE = 1,        //文件
    LOG_TO_CONSOLE = 1 << 1,//控制台
    LOG_TO_DEBUG = 1 << 2   //调试
};
const FS_INT32 kLoggerModeCnt = 3;

// 获取日志记录器索引对应的类型
#define MAKE_LOGGER_MODE(index)   (static_cast<LoggerMode>( 1 << (index)))

////////////////////////////////////////////////////////////////////////////////

// 最大的单个日志文件大小
const FS_INT32 kMaxLogFileSize = 10 * 1024 * 1024;

// 单条日志信息最大占用的空间大小
const FS_INT32 kMaxLogMessageBufLen = 4096;

////////////////////////////////////////////////////////////////////////////////

struct LoggerParam
{
    FS_CHAR     logger_name[64];        //日志器名称(模块名，会体现在模块日志文件名中)
    FS_UINT32   logger_mode;            //日志器模式（文件/控制台/调试）
    bool        encrypt;                //日志数据是否加密
    LoggerParam():logger_mode(LOG_TO_FILE),encrypt(false){logger_name[0]='\0';}
};

/*==============================================================================
 * 描述: 日志管理中心接口类
 *============================================================================*/
class ILogMgr
{
public:
    /*--------------------------------------------------------------------------
     * 描  述：需要打印日志的模块在打印日志前，需要调用此接口向日志管理中心注册。
     *         日志管理中心会为每一个注册的模块创建一个独立的日志文件。
     * 参  数：[in] logger_param 日志器参数
     * 返回值：全局唯一的日志器ID，模块向日志中心记录日志时，需要提供此ID。
     *        返回0,代表注册失败。
     *------------------------------------------------------------------------*/
    virtual FS_INT RegisterLogger(const LoggerParam& logger_param) = 0;

    /*--------------------------------------------------------------------------
     * 描  述：模块调用此接口通知日志中心不再使用日志功能。
     * 参  数：[in] logger_id 日志器ID
     * 返回值：无
     *------------------------------------------------------------------------*/
    virtual FS_VOID UnregisterLogger(FS_INT logger_id) = 0;

    /*--------------------------------------------------------------------------
     * 描  述：此接口提供给C++流风格日志前端使用，此接口只负责记录已经格式化
     *         好的日志内容，日志前端需要自己处理日志前缀和日志格式化。
     * 参  数：[in] logger_id 日志器ID
     *         [in] log_msg 日志内容
     *         [in] log_len 日志长度
     *         [in] log_level 日志级别
     * 返回值：无
     *------------------------------------------------------------------------*/
    virtual FS_VOID WriteLog(
        FS_INT logger_id,
        const FS_CHAR* log_msg,
        FS_UINT32 log_len,
        LogLevel log_level
        ) = 0;

    /*--------------------------------------------------------------------------
     * 描  述：此接口提供给C风格日志前端使用，日志中心负责添加日志前缀和格式化日
     *         志内容。
     * 参  数：[in] logger_id 日志器ID
     *         [in] log_level 日志级别
     *         [in] file 打印日志的源文件名
     *         [in] line 打印日志源文件的行号
     *         [in] fmt 日志格式化字符串
     *         [in] ... 可变日志参数
     * 返回值：无
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
    * 描  述：此接口提供给C风格日志前端使用，日志中心负责添加日志前缀和格式化日
    *         志内容（宽字符版本）。
    * 参  数：[in] logger_id 日志器ID
    *         [in] log_level 日志级别
    *         [in] file 打印日志的源文件名
    *         [in] line 打印日志源文件的行号
    *         [in] fmt 日志格式化字符串
    *         [in] ... 可变日志参数
    * 返回值：无
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
     * 描  述: 设置日志的保存时间
     * 参  数: [in] days 保存的天数
     * 返回值: 无
     *------------------------------------------------------------------------*/
    virtual FS_VOID SetLogSaveDays(FS_UINT32 days) = 0;

};

} // namespace FsMeeting

#endif // FSLOG_LOGGING_H_
