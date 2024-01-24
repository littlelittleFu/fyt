#include "stdafx.h"
#include "LoginServer.h"


void SignalHandler(int sig)
{
    LoginServer::GetInstance()->Quit();
}

void SetSignalHandler()
{
#ifdef __linux__
    struct sigaction sa;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SignalHandler;
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);
#endif
}

int ServProc(int argc, char *argv[])
{
    SetSignalHandler();

    LogHelper logHelper;
    ILogHelper::SetInstance(&logHelper);

    TimeHelper timeHelper;
    ITimeHelper::SetInstance(&timeHelper);

    FileHelper fileHelper;
    IFileHelper::SetInstance(&fileHelper);

    LOG_INIT("LoginServer");

    LoginServer::GetInstance()->Start();

    LOG_NORMAL("login server stopped");
    LOG_UNINIT();

    return 0;
}

#ifdef _WIN32

DWORD ServiceCtrlHandler(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext)
{
    switch (dwControl) {

    case SERVICE_CONTROL_INTERROGATE: return NO_ERROR;

    case SERVICE_CONTROL_SHUTDOWN:
    case SERVICE_CONTROL_STOP:

        LoginServer::GetInstance()->Quit();

        WinService::GetInstance().SetCurrentState(SERVICE_STOP_PENDING, 2000);

        return NO_ERROR;

    default: return ERROR_CALL_NOT_IMPLEMENTED;
    }
}

void ServiceMain(DWORD argc, LPSTR argv[])
{
    auto result = WinService::GetInstance().RegCtrlHandler("LoginServer", ServiceCtrlHandler, nullptr);
    if (result != ERROR_SUCCESS) return;

    result = WinService::GetInstance().SetCurrentState(SERVICE_START_PENDING, 2000);
    if (result != ERROR_SUCCESS) return;

    ServProc(argc, argv);

    WinService::GetInstance().SetCurrentState(SERVICE_STOPPED);
}

int RunAsService(int argc, char *argv[])
{
    auto result = WinService::GetInstance().SetServiceMain(ServiceMain);

    if (result != ERROR_SUCCESS) return 1;

    return 0;
}

#else

int RunAsDaemon(int argc, char *argv[])
{
    if (daemon(0, 0) == -1) return 1;

    return ServProc(argc, argv);
}

#endif

int RunAsStandAlone(int argc, char *argv[])
{
    return ServProc(argc, argv);
}

int main(int argc, char *argv[])
{
    int result = 0;

    if (argc > 1 && strcmp(argv[1], "-d") == 0) {

#ifdef _WIN32
        result = RunAsService(argc, argv);
#else
        result = RunAsDaemon(argc, argv);
#endif
    }
    else {

        result = RunAsStandAlone(argc, argv);
    }

    return result;
}
