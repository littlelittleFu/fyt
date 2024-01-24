#include "stdafx.h"
#include "miniDumper.h"

#ifdef _WIN32

#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include <dbghelp.h>
#include <stdlib.h>
#include "ITimeHelper.h"
#include <chrono>
#ifdef UNICODE
    #define _tcssprintf wsprintf
    #define tcsplitpath _wsplitpath
#else
    #define _tcssprintf sprintf
    #define tcsplitpath _splitpath
#endif

const int USER_DATA_BUFFER_SIZE = 4096;
const BYTE PatchBytes[5] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };
BYTE OriginalBytes[5] = { 0 };

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
CMiniDumper* CMiniDumper::s_pMiniDumper = NULL;
LPCRITICAL_SECTION CMiniDumper::s_pCriticalSection = NULL;

// Based on dbghelp.h
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess,
                                         DWORD dwPid,
                                         HANDLE hFile,
                                         MINIDUMP_TYPE DumpType,
                                         CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                         CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                         CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

CMiniDumper* CMiniDumper::GetInstance()
{
	return s_pMiniDumper;
}

//-----------------------------------------------------------------------------
// Name: CMiniDumper()
// Desc: Constructor
//-----------------------------------------------------------------------------
CMiniDumper::CMiniDumper(BOOL bPromptUserForMiniDump)
{
	// Our CMiniDumper should act alone as a singleton.
	assert(!s_pMiniDumper);

    s_pMiniDumper = this;
    m_bPromptUserForMiniDump = bPromptUserForMiniDump;
	m_WriteDumpFile = TRUE;

    // The SetUnhandledExceptionFilter function enables an application to
    // supersede the top-level exception handler of each thread and process.
    // After calling this function, if an exception occurs in a process
    // that is not being debugged, and the exception makes it to the
    // unhandled exception filter, that filter will call the exception
    // filter function specified by the lpTopLevelExceptionFilter parameter.
	::SetUnhandledExceptionFilter(unhandledExceptionHandler);
	EnforceFilter(TRUE);

    // Since DBGHELP.dll is not inherently thread-safe, making calls into it
    // from more than one thread simultaneously may yield undefined behavior.
    // This means that if your application has multiple threads, or is
    // called by multiple threads in a non-synchronized manner, you need to 
    // make sure that all calls into DBGHELP.dll are isolated via a global
    // critical section.
    s_pCriticalSection = new CRITICAL_SECTION;

    if(s_pCriticalSection)
        InitializeCriticalSection(s_pCriticalSection);
}

//-----------------------------------------------------------------------------
// Name: ~CMiniDumper()
// Desc: Destructor
//-----------------------------------------------------------------------------
CMiniDumper::~CMiniDumper(void)
{
    if(s_pCriticalSection)
    {
        DeleteCriticalSection(s_pCriticalSection);
        delete s_pCriticalSection;
    }
}

void CMiniDumper::ResetExceptionHandler()
{
	::SetUnhandledExceptionFilter(unhandledExceptionHandler);
	EnforceFilter(TRUE);
}

BOOL CMiniDumper::WriteMemory(BYTE* pTarget, const BYTE* pSource, DWORD dwSize)
{
	/*DWORD dwOldProtect;
	DWORD dwTempProtect;
	if (pTarget && pSource &&
		!IsBadReadPtr(pSource,dwSize) &&
		VirtualProtect(pTarget,dwSize,PAGE_READWRITE,&dwOldProtect))
	{
		memcpy(pTarget,pSource,dwSize);
		return VirtualProtect(pTarget,dwSize,dwOldProtect,&dwTempProtect);
	}
	return FALSE;*/
	return TRUE;
}

BOOL CMiniDumper::EnforceFilter(BOOL _Enforce)
{
	HMODULE hLib = NULL;
	BYTE* pTarget = NULL;
	const BYTE* pSrcBytes = NULL;

	if ((hLib = GetModuleHandle(_T("kernel32.dll"))) &&
		(pTarget = (BYTE*)GetProcAddress(hLib,"SetUnhandledExceptionFilter")) &&
		!IsBadReadPtr(pTarget,sizeof(OriginalBytes)))
	{
		if (_Enforce) {
			memcpy(OriginalBytes,pTarget,sizeof(OriginalBytes));
			pSrcBytes = &PatchBytes[0];
		}
		else {
			pSrcBytes = &OriginalBytes[0];
		}
		return WriteMemory(pTarget,pSrcBytes,sizeof(OriginalBytes));
	}
	return FALSE;
}

VOID CMiniDumper::NoDumpFile()
{
	m_WriteDumpFile = FALSE;
}

//-----------------------------------------------------------------------------
// Name: unhandledExceptionHandler()
// Desc: Call-back filter function for unhandled exceptions
//-----------------------------------------------------------------------------
LONG CMiniDumper::unhandledExceptionHandler(_EXCEPTION_POINTERS *pExceptionInfo)
{
	if(!s_pMiniDumper)
		return EXCEPTION_CONTINUE_SEARCH;

	if (!s_pMiniDumper->m_WriteDumpFile) {
		return EXCEPTION_EXECUTE_HANDLER;
	}

	return s_pMiniDumper->writeMiniDump(pExceptionInfo);
}

//-----------------------------------------------------------------------------
// Name: MiniDumpFile()
// Desc: Call-back filter function for unhandled exceptions
//-----------------------------------------------------------------------------
LONG CMiniDumper::MiniDumpFile(_EXCEPTION_POINTERS *pExceptionInfo)
{
	if(!s_pMiniDumper)
		return EXCEPTION_CONTINUE_SEARCH;

	return s_pMiniDumper->writeMiniDump(pExceptionInfo);
}

//-----------------------------------------------------------------------------
// Name: setMiniDumpFileName()
// Desc:
//-----------------------------------------------------------------------------
void CMiniDumper::setMiniDumpFileName(void)
{
    auto curTime = ITimeHelper::GetInstance()->ConvertTimeToString(time(nullptr), DTFMTA3);

	_tcssprintf(m_szMiniDumpPath,
		_T("%s%s.%s.dmp"),
		m_szAppPath,
		m_szAppBaseName,
        curTime.c_str()
         );
}

//-----------------------------------------------------------------------------
// Name: getImpersonationToken()
// Desc: The method acts as a potential workaround for the fact that the
//       current thread may not have a token assigned to it, and if not, the
//       process token is received.
//-----------------------------------------------------------------------------
BOOL CMiniDumper::getImpersonationToken(HANDLE* phToken)
{
    *phToken = NULL;

    if(!OpenThreadToken(GetCurrentThread(),
                          TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
                          TRUE,
                          phToken))
    {
        if(GetLastError() == ERROR_NO_TOKEN)
        {
            // No impersonation token for the current thread is available.
            // Let's go for the process token instead.
            if(!OpenProcessToken(GetCurrentProcess(),
                                   TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
                                   phToken))
                return FALSE;
        }
        else
            return FALSE;
    }

    return TRUE;
}

//-----------------------------------------------------------------------------
// Name: enablePrivilege()
// Desc: Since a MiniDump contains a lot of meta-data about the OS and
//       application state at the time of the dump, it is a rather privileged
//       operation. This means we need to set the SeDebugPrivilege to be able
//       to call MiniDumpWriteDump.
//-----------------------------------------------------------------------------
BOOL CMiniDumper::enablePrivilege(LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld)
{
    BOOL _Ret = FALSE;

    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    _Ret = LookupPrivilegeValue(0, pszPriv, &tp.Privileges[0].Luid);

    if(_Ret)
    {
        DWORD cbOld = sizeof(*ptpOld);
        _Ret = AdjustTokenPrivileges(hToken, FALSE, &tp, cbOld, ptpOld, &cbOld);
    }

    return (_Ret && (ERROR_NOT_ALL_ASSIGNED != GetLastError()));
}

//-----------------------------------------------------------------------------
// Name: restorePrivilege()
// Desc:
//-----------------------------------------------------------------------------
BOOL CMiniDumper::restorePrivilege(HANDLE hToken, TOKEN_PRIVILEGES* ptpOld)
{
    BOOL bOk = AdjustTokenPrivileges(hToken, FALSE, ptpOld, 0, NULL, NULL);
    return (bOk && (ERROR_NOT_ALL_ASSIGNED != GetLastError()));
}

//-----------------------------------------------------------------------------
// Name: writeMiniDump()
// Desc:
//-----------------------------------------------------------------------------
LONG CMiniDumper::writeMiniDump(_EXCEPTION_POINTERS *pExceptionInfo)
{
	LONG retval = EXCEPTION_CONTINUE_SEARCH;
	m_pExceptionInfo = pExceptionInfo;

    HANDLE hImpersonationToken = NULL;
    if(!getImpersonationToken(&hImpersonationToken))
        return FALSE;

	// You have to find the right dbghelp.dll.
	// Look next to the EXE first since the one in System32 might be old (Win2k)
	
	HMODULE hDll = NULL;
	TCHAR szDbgHelpPath[MAX_PATH];

	if(GetModuleFileName(NULL, m_szAppPath, _MAX_PATH))
	{
		TCHAR *pSlash = _tcsrchr(m_szAppPath, '\\');
	
		if(pSlash)
		{
			_tcscpy(m_szAppBaseName, pSlash + 1);
			TCHAR tempname[MAX_PATH];
			(int)_stscanf(m_szAppBaseName,"%[^_]",tempname);
			memset(m_szAppBaseName,0,sizeof(m_szAppBaseName));
			_tcscpy(m_szAppBaseName, tempname);
			*(m_szAppBaseName + strlen(m_szAppBaseName)) = 0;
			*(pSlash+1) = 0;
		}

		_tcscpy(szDbgHelpPath, m_szAppPath);
        _tcscat(szDbgHelpPath, _T("DBGHELP.DLL"));
		hDll = ::LoadLibrary(szDbgHelpPath);
	
	}

	if(hDll == NULL)
	{
		// If we haven't found it yet - try one more time.
		hDll = ::LoadLibrary(_T("DBGHELP.DLL"));
	}

	LPCTSTR szResult = NULL;

	if(hDll)
	{
        // Get the address of the MiniDumpWriteDump function, which writes
        // user-mode mini-dump information to a specified file.
		MINIDUMPWRITEDUMP MiniDumpWriteDump =
            (MINIDUMPWRITEDUMP)::GetProcAddress(hDll, "MiniDumpWriteDump");

		if(MiniDumpWriteDump != NULL)
        {
			TCHAR szScratch[USER_DATA_BUFFER_SIZE];

			setMiniDumpFileName();

			// Ask the user if he or she wants to save a mini-dump file...
			_tcssprintf(szScratch,
                         _T("There was an unexpected error:\r\n\r\nWould you ")
                         _T("like to create a mini-dump file?\r\n\r\n%s "),
                         m_szMiniDumpPath);

			// Create the mini-dump file...
			HANDLE hFile = ::CreateFile(m_szMiniDumpPath,
                                            GENERIC_WRITE,
                                            FILE_SHARE_WRITE,
                                            NULL,
                                            CREATE_ALWAYS,
                                            FILE_ATTRIBUTE_NORMAL,
                                            NULL);

			if(hFile != INVALID_HANDLE_VALUE)
			{
				_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
				ExInfo.ThreadId          = ::GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers    = NULL;

                // We need the SeDebugPrivilege to be able to run MiniDumpWriteDump
                TOKEN_PRIVILEGES tp;
                BOOL bPrivilegeEnabled = enablePrivilege(SE_DEBUG_NAME, hImpersonationToken, &tp);

                BOOL bOk;

                // DBGHELP.dll is not thread-safe, so we need to restrict access...
                EnterCriticalSection(s_pCriticalSection);
                {
					// Write out the mini-dump data to the file...
                    bOk = MiniDumpWriteDump(GetCurrentProcess(),
                                                GetCurrentProcessId(),
                                                hFile,
                                                MiniDumpNormal,
                                                &ExInfo,
                                                NULL,
                                                NULL);
                }
                LeaveCriticalSection(s_pCriticalSection);

                // Restore the privileges when done
                if(bPrivilegeEnabled)
	                restorePrivilege(hImpersonationToken, &tp);

                if(bOk)
				{
					szResult = NULL;
					retval = EXCEPTION_EXECUTE_HANDLER;
				}
				else
				{
					_tcssprintf(szScratch,
                                    _T("Failed to save the mini-dump file to '%s' (error %d)"),
                                    m_szMiniDumpPath,
                                    GetLastError());

					szResult = szScratch;
				}

				::CloseHandle(hFile);
			}
			else
			{
				_tcssprintf(szScratch,
                                _T("Failed to create the mini-dump file '%s' (error %d)"),
                                m_szMiniDumpPath,
                                GetLastError());

				szResult = szScratch;
			}
		}
		else
		{
			szResult = _T("Call to GetProcAddress failed to find MiniDumpWriteDump. ")
                       _T("The DBGHELP.DLL is possibly outdated.");
		}
	}
	else
	{
		szResult = _T("Call to LoadLibrary failed to find DBGHELP.DLL.");
	}

	if(szResult && m_bPromptUserForMiniDump)
		::MessageBox(NULL, szResult, NULL, MB_OK);

	TerminateProcess(GetCurrentProcess(), 0);

	return retval;
}

#endif
