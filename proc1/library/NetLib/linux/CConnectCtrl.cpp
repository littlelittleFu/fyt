#include "pch.h"
#include "CConnectCtrl.h"
#include "SessionManager.h"
#include "CEpollCtrl.h"
#include "CSocket.h"


CConnectCtrl::CConnectCtrl()
{

}

CConnectCtrl::~CConnectCtrl()
{

}

void CConnectCtrl::AddConnector(const std::string &ip, uint32_t port, int sess_type, int sess_param, bool encrypt)
{
    int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (fd == -1) {
        LOG_ERROR("socket failed with error %d", errno);
        return;
    }

    CSocket::SetSocketNoDelay(fd, 1);

    auto addr = CSocket::GetSockAddr(ip, port);
    auto result = connect(fd, &addr, sizeof(addr));

    if (result == 0) {
        LOG_NORMAL("Connect to %s:%u success directly", ip.c_str(), port);
        SessionManager::GetInstance()->CacheSessionInfo(sess_type, sess_param, encrypt, true, "", 0, ip, port, fd);
        return;
    }

    if (errno != EINPROGRESS) {
        LOG_ERROR("connect failed with error %d", errno);
        close(fd);
        return;
    }

    auto *ctx = AddSockContext(fd, sess_type, sess_param, encrypt, ip, port);
    CEpollCtrl::GetInstance()->StartMonitor(fd, EPOLLOUT | EPOLLET, ctx);
}

sock_context * CConnectCtrl::AddSockContext(int sock_fd, int sess_type, int sess_param,
    bool encrypt, const std::string &conn_ip, uint16_t conn_port)
{
    CLockGuard guard(m_mutex);

    m_sock_ctx_list.emplace_back(sock_fd, sock_type_connect, sess_type, sess_param, encrypt, conn_ip, conn_port, this);

    auto &ctx = m_sock_ctx_list.back();

    return &ctx;
}

void CConnectCtrl::RemoveSockContext(sock_context *ctx)
{
    CLockGuard guard(m_mutex);

    auto it = std::find_if(m_sock_ctx_list.begin(), m_sock_ctx_list.end(), [&](const auto &ctx_) {
        return &ctx_ == ctx;
    });

    if (it != m_sock_ctx_list.end()) m_sock_ctx_list.erase(it);
}

void CConnectCtrl::OnConnect(sock_context *ctx)
{
    if (!ctx) return;

    auto &fd = ctx->sock_fd;
    if (fd == INVALID_SOCKET) return;

    auto addr = CSocket::GetSockAddr(ctx->conn_ip, ctx->conn_port);
    auto result = connect(fd, &addr, sizeof(addr));

    if (result == 0 || errno == EISCONN) {

        LOG_NORMAL("Connect to %s:%u success async", ctx->conn_ip.c_str(), ctx->conn_port);

        CEpollCtrl::GetInstance()->StopMonitor(fd);

        SessionManager::GetInstance()->CacheSessionInfo(ctx->sess_type, ctx->sess_param,
            ctx->encrypt, true, "", 0, ctx->conn_ip, ctx->conn_port, fd);

        ctx->connected = true;
    }
    else if (errno != EINPROGRESS) {

        LOG_ERROR("connect failed with error %d", errno);
        OnError(ctx, errno);
    }
}

void CConnectCtrl::OnLost(sock_context *ctx)
{
    if (!ctx) return;

    auto &fd = ctx->sock_fd;
    if (fd == INVALID_SOCKET) return;

    CEpollCtrl::GetInstance()->StopMonitor(fd);

    RELEASE_SOCKET(fd);
}

void CConnectCtrl::OnError(sock_context *ctx, int error)
{
    OnLost(ctx);
}
