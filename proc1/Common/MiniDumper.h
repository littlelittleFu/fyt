#ifndef MINIDUMPER_H
#define MINIDUMPER_H

#ifdef _WIN32

#include <windows.h>

class CMiniDumper
{
public:

	static CMiniDumper* GetInstance();
    CMiniDumper(BOOL bPromptUserForMiniDump);
    ~CMiniDumper(void);

public:
	static LONG MiniDumpFile(_EXCEPTION_POINTERS *pExceptionInfo);
	void ResetExceptionHandler();
	static BOOL WriteMemory(BYTE* pTarget, const BYTE* pSource, DWORD dwSize);
	BOOL EnforceFilter(BOOL _Enforce);
	VOID NoDumpFile();

private:

    static LONG WINAPI unhandledExceptionHandler(struct _EXCEPTION_POINTERS *pExceptionInfo);
    void setMiniDumpFileName(void);
    BOOL getImpersonationToken(HANDLE* phToken);
    BOOL enablePrivilege(LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    BOOL restorePrivilege(HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    LONG writeMiniDump(_EXCEPTION_POINTERS *pExceptionInfo);

    _EXCEPTION_POINTERS *m_pExceptionInfo;
    TCHAR m_szMiniDumpPath[MAX_PATH];
    TCHAR m_szAppPath[MAX_PATH];
    TCHAR m_szAppBaseName[MAX_PATH];
    BOOL m_bPromptUserForMiniDump;

    static CMiniDumper* s_pMiniDumper;
    static LPCRITICAL_SECTION s_pCriticalSection;
	BOOL m_WriteDumpFile;
};

#else

class CMiniDumper
{
public:
    CMiniDumper(bool bPromptUserForMiniDump) {}
    ~CMiniDumper(void) {}
};

#endif

#endif // MINIDUMPER_H
