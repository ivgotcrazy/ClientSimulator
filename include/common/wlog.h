#ifndef VNCLOGGING
#define VNCLOGGING

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "wbasetype.h"
#include "wlock.h"
#include "wunicode.h"
#include "string"


namespace WBASELIB
{

class WLog
{
public:
    // Logging mode flags:
    static const FS_INT32 ToDebug;
    static const FS_INT32 ToFile;
    static const FS_INT32 ToConsole;

    // Create a new log object.
    // Parameters as follows:
    //    mode     - specifies where output should go, using combination
    //               of flags above.
    //    level    - the default level
    //    filename - if flag WLog::ToFile is specified in the type,
    //               a filename must be specified here.
    //    append   - if logging to a file, whether or not to append to any
    //               existing log.
    WLog(FS_INT32 mode = ToDebug, FS_INT32 level = 1, LPCTSTR filename = NULL, BOOL bEncrypt = TRUE, const WCHAR* szLogPath = NULL);

    inline void Print2(FS_INT32 level, LPCTSTR format, ...)
    {
        if (level > m_level) return;

        va_list ap;
        va_start(ap, format);
        ReallyPrint(format, ap);
        va_end(ap);
    }

    inline void Print(LPCTSTR format, ...)
    {

        va_list ap;
        va_start(ap, format);
        ReallyPrint(format, ap);
        va_end(ap);
    }
    void ReallyPrint(LPCTSTR format, va_list ap);

    // Change the log level
    void SetLogFileMaxSize(FS_UINT32 dwMaxSize);
    void SetLevel(FS_INT32 level);
    FS_INT32  GetLevel();

    // Change the logging mode
    void SetMode(FS_INT32 mode);
    void SetLogPath(const WCHAR* szLogPath);

    // Change or set the logging filename.  This enables ToFile mode if
    // not already enabled.
    void SetFile(LPCTSTR filename);

    virtual ~WLog();

private:
    void ReallyPrintLine(LPCTSTR line);
    void OpenFile();
    void CloseFile();

    BOOL   m_bSaveDays;
    BOOL   m_bEncrypt;
    bool   m_tofile, m_todebug, m_toconsole;
    FS_INT32    m_level;
#ifdef _FS_OS_WIN
    HANDLE 	hlogfile;
#else
    FILE*	m_pLogFile;
#endif
    TCHAR  m_szLogFileName[MAX_PATH];

    WLock	m_lock;
    time_t 			m_lastLogTime;
    FS_UINT32	m_dwFileTotalSize;
    FS_UINT32   m_dwLogFileMaxSize;
    std::wstring m_strLogPath;
};
}
#endif // VNCLOGGING
