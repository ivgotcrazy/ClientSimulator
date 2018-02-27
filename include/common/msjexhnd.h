#ifndef __MSJEXHND_H__
#define __MSJEXHND_H__

#ifdef _FS_OS_WIN

#include <windows.h>

class MSJExceptionHandler
{
public:

    MSJExceptionHandler();
    ~MSJExceptionHandler();

    static void Init();
    static void Release();
    static void SetLogFileName(PTSTR pszLogFileName);
    static void SetLogFilePath(PTSTR pszLogFilePath);
    static void SetAutoReportCmd(PSTR pszReportCmd);
    static void ReportException(PSTR pszReportCmd, PEXCEPTION_POINTERS pExceptionInfo);

private:

    static BOOL restorePrivilege(HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    static BOOL enablePrivilege(LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    static bool getImpersonationToken(HANDLE* phToken);

    // entry point where control comes on an unhandled exception
    static LONG WINAPI MSJUnhandledExceptionFilter(
        PEXCEPTION_POINTERS pExceptionInfo);

    // where report info is extracted and generated 
    static void GenerateExceptionReport(PEXCEPTION_POINTERS pExceptionInfo);

    // Helper functions
    static LPTSTR GetExceptionString(FS_UINT32 dwCode);
    static BOOL GetLogicalAddress(PVOID addr, PTSTR szModule, FS_UINT32 len,
        FS_UINT32& section, FS_UINT& offset);
    static void IntelStackWalk(PCONTEXT pContext);
    static FS_INT32 __cdecl _tprintf(const TCHAR * format, ...);

    static void GenerateExceptionDump(PEXCEPTION_POINTERS pExceptionPointers, LPCTSTR lpszDumpFileName);

    // Variables used by the class
    static TCHAR m_szLogFileName[MAX_PATH];
    static TCHAR m_szLogFilePath[MAX_PATH];
    static CHAR m_szAutoReportCmd[MAX_PATH];
    static LPTOP_LEVEL_EXCEPTION_FILTER m_previousFilter;
    static HANDLE m_hReportFile;
    static FS_INT32	  m_lRef;
};

extern MSJExceptionHandler g_MSJExceptionHandler;   //  global instance of class

#endif

#endif
