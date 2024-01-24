#pragma once

#include "Type.h"
#include "sock_context.h"


class CEpollCtrl
{
    DECLARE_INSTANCE(CEpollCtrl);

public:
    bool Init(uint32_t thread_num);
    void UnInit();

    bool StartMonitor(int fd, uint32_t events, sock_context *ctx);
    bool ModifyMonitor(int fd, uint32_t events, sock_context *ctx);
    bool StopMonitor(int fd);

private:
    CEpollCtrl();
    ~CEpollCtrl();

    void WorkerThread();

    void HandleEvents(epoll_event *pevents, int num);
    void HandleEvents_HUP(sock_context *ctx);
    void HandleEvents_ERR(sock_context *ctx);
    void HandleEvents_IN(sock_context *ctx);
    void HandleEvents_Listen(sock_context *ctx);
    void HandleEvents_Recv(sock_context *ctx);
    void HandleEvents_OUT(sock_context *ctx);
    void HandleEvents_Connect(sock_context *ctx);
    void HandleEvents_Send(sock_context *ctx);

    void AfterHandled(sock_context *ctx);

    void OnLost(sock_context *ctx, int error);
    void OnError(sock_context *ctx, int error);

private:
    int m_epoll_fd = -1;

    std::vector<std::thread> m_threads;

    std::atomic<bool> m_term{false};
};
