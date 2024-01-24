#include "pch.h"
#include "CEpollCtrl.h"
#include "SessionManager.h"
#include "CConnectCtrl.h"
#include "CListener.h"
#include "CSocket.h"


IMPLEMENT_INSTANCE(CEpollCtrl);


CEpollCtrl::CEpollCtrl()
{
}

CEpollCtrl::~CEpollCtrl()
{
}

bool CEpollCtrl::Init(uint32_t thread_num)
{
    m_term = false;

    m_epoll_fd = epoll_create(2000);
    if (m_epoll_fd == -1) {
        LOG_ERROR("epoll_create failed with error %d", errno);
        return false;
    }

    for (unsigned i = 0; i < thread_num; ++i) {
        m_threads.emplace_back(&CEpollCtrl::WorkerThread, this);
    }

    return true;
}

void CEpollCtrl::UnInit()
{
    m_term = true;

    for (auto &t : m_threads) t.join();

    m_threads.clear();

    close(m_epoll_fd);
    m_epoll_fd = -1;
}

bool CEpollCtrl::StartMonitor(int fd, uint32_t events, sock_context *ctx)
{
    if (m_epoll_fd == -1) return false;

    epoll_event event;
    event.events = events;
    event.data.ptr = ctx;

    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1) {
        LOG_ERROR("epoll_ctl failed with error %d", errno);
        return false;
    }

    return true;
}

bool CEpollCtrl::ModifyMonitor(int fd, uint32_t events, sock_context *ctx)
{
    if (m_epoll_fd == -1) return false;

    epoll_event event;
    event.events = events;
    event.data.ptr = ctx;

    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &event) == -1) {
        LOG_ERROR("epoll_ctl failed with error %d", errno);
        return false;
    }

    return true;
}

bool CEpollCtrl::StopMonitor(int fd)
{
    if (m_epoll_fd == -1) return false;

    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
        LOG_ERROR("epoll_ctl failed with error %d", errno);
        return false;
    }

    return true;
}

void CEpollCtrl::WorkerThread()
{
    const int MAX_WAIT_EVENTS = 2000;
    const int WAIT_TIME_MS = 1000;

    epoll_event events[MAX_WAIT_EVENTS];

    while (!m_term) {

        auto num = epoll_wait(m_epoll_fd, events, _countof(events), WAIT_TIME_MS);

        if (num == -1) {
            if (errno == EINTR) continue;
            LOG_ERROR("epoll_wait failed with error %d", errno);
            break;
        }

        if (num == 0) continue;     // timeout

        HandleEvents(events, num);
    }
}

void CEpollCtrl::HandleEvents(epoll_event *pevents, int num)
{
    for (int i = 0; i < num; ++i) {

        auto &event = pevents[i];
        auto events = event.events;
        auto context = event.data.ptr;

        auto *ctx = static_cast<sock_context *>(context);
        if (!ctx) continue;

        if (events & EPOLLHUP) {
            HandleEvents_HUP(ctx);
        }

        if (events & EPOLLERR) {
            HandleEvents_ERR(ctx);
        }

        if (events & EPOLLIN) {
            HandleEvents_IN(ctx);
        }

        if (events & EPOLLOUT) {
            HandleEvents_OUT(ctx);
        }

        AfterHandled(ctx);
    }
}

void CEpollCtrl::HandleEvents_HUP(sock_context *ctx)
{
    LOG_NORMAL("HandleEvents_HUP, fd: %d", ctx->sock_fd);

    auto &fd = ctx->sock_fd;
    if (fd == INVALID_SOCKET) return;

    auto error = CSocket::GetSocketError(fd);

    switch (error) {

    case ECONNREFUSED:
        LOG_WARN("Connection refused");
        break;

    case ECONNRESET:
        LOG_WARN("Connection reset by peer");
        break;

    default:
        LOG_WARN("socket error %d", error);
        break;
    }

    // read left data

    OnLost(ctx, error);
}

void CEpollCtrl::HandleEvents_ERR(sock_context *ctx)
{
    LOG_NORMAL("HandleEvents_ERR, fd: %d", ctx->sock_fd);

    auto &fd = ctx->sock_fd;
    if (fd == INVALID_SOCKET) return;

    auto error = CSocket::GetSocketError(fd);

    switch (error) {

    case ETIMEDOUT:
        LOG_WARN("Connection timed out");
        break;

    default:
        LOG_WARN("socket error %d", error);
        break;
    }

    OnError(ctx, error);
}

void CEpollCtrl::HandleEvents_IN(sock_context *ctx)
{
    switch (ctx->sock_type) {

    case sock_type_listen:
        HandleEvents_Listen(ctx);
        break;

    case sock_type_io:
        HandleEvents_Recv(ctx);
        break;

    default:
        break;
    }
}

void CEpollCtrl::HandleEvents_Listen(sock_context *ctx)
{
    LOG_NORMAL("HandleEvents_Listen, fd: %d", ctx->sock_fd);

    if (ctx->sock_fd == INVALID_SOCKET) return;

    auto *handler = static_cast<CListener *>(ctx->event_handler);
    if (!handler) return;

    handler->OnAccept();
}

void CEpollCtrl::HandleEvents_Recv(sock_context *ctx)
{
    if (ctx->sock_fd == INVALID_SOCKET) return;

    auto *handler = static_cast<CSocket *>(ctx->event_handler);
    if (!handler) return;

    handler->OnRecv();
}

void CEpollCtrl::HandleEvents_OUT(sock_context *ctx)
{
    switch (ctx->sock_type) {

    case sock_type_connect:
        HandleEvents_Connect(ctx);
        break;

    case sock_type_io:
        HandleEvents_Send(ctx);
        break;

    default:
        break;
    }
}

void CEpollCtrl::HandleEvents_Connect(sock_context *ctx)
{
    LOG_NORMAL("HandleEvents_Connect, fd: %d", ctx->sock_fd);

    if (ctx->sock_fd == INVALID_SOCKET) return;

    auto *handler = static_cast<CConnectCtrl *>(ctx->event_handler);
    if (!handler) return;

    handler->OnConnect(ctx);
}

void CEpollCtrl::HandleEvents_Send(sock_context *ctx)
{
    if (ctx->sock_fd == INVALID_SOCKET) return;

    auto *handler = static_cast<CSocket *>(ctx->event_handler);
    if (!handler) return;

    handler->OnSend();
}

void CEpollCtrl::AfterHandled(sock_context *ctx)
{
    if (ctx->sock_type == sock_type_connect) {
        if (ctx->sock_fd == INVALID_SOCKET || ctx->connected) {
            static_cast<CConnectCtrl *>(ctx->event_handler)->RemoveSockContext(ctx);
        }
    }
}

void CEpollCtrl::OnLost(sock_context *ctx, int error)
{
    if (!ctx) return;

    switch (ctx->sock_type) {

    case sock_type_connect:
        static_cast<CConnectCtrl *>(ctx->event_handler)->OnLost(ctx);
        break;

    case sock_type_io:
        static_cast<CSocket *>(ctx->event_handler)->OnLost();
        break;

    default:
        break;
    }
}

void CEpollCtrl::OnError(sock_context *ctx, int error)
{
    if (!ctx) return;

    switch (ctx->sock_type) {

    case sock_type_connect:
        static_cast<CConnectCtrl *>(ctx->event_handler)->OnError(ctx, error);
        break;

    case sock_type_listen:
        static_cast<CListener *>(ctx->event_handler)->OnError(error);
        break;

    case sock_type_io:
        static_cast<CSocket *>(ctx->event_handler)->OnError(error);
        break;

    default:
        break;
    }
}
