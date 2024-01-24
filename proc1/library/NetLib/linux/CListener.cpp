#include "pch.h"
#include "CListener.h"
#include "CEpollCtrl.h"
#include "SessionManager.h"
#include "CSocket.h"


CListener::CListener()
{
    m_sock_ctx.sock_type = sock_type_listen;
    m_sock_ctx.event_handler = this;
}

CListener::~CListener()
{

}

bool CListener::Start(const std::string &ip, uint32_t port)
{
    auto &fd = m_sock_ctx.sock_fd;

    fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (fd == INVALID_SOCKET) {
        LOG_ERROR("socket failed with error %d", errno);
        return false;
    }

    CSocket::SetSocketReuseAddr(fd, 1);

    auto addr = CSocket::GetSockAddr(ip, port);

    if (bind(fd, &addr, sizeof(addr)) == -1) {
        LOG_ERROR("bind failed with error %d", errno);
        RELEASE_SOCKET(fd);
        return false;
    }

    const int MAX_LISTEN_NUM = 128;

    if (listen(fd, MAX_LISTEN_NUM) == -1) {
        LOG_ERROR("listen failed with error %d", errno);
        RELEASE_SOCKET(fd);
        return false;
    }

    CEpollCtrl::GetInstance()->StartMonitor(fd, EPOLLIN | EPOLLET, &m_sock_ctx);

    LOG_NORMAL("Start listening on %s:%u", ip.empty() ? "0.0.0.0" : ip.c_str(), port);

    return true;
}

void CListener::Stop()
{
    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) return;

    CEpollCtrl::GetInstance()->StopMonitor(fd);
    RELEASE_SOCKET(fd);
}

void CListener::OnError(int error)
{
    Stop();
}

void CListener::OnAccept()
{
    auto &server_sock = m_sock_ctx.sock_fd;
    sockaddr_in client_addr;

    while (true) {

        socklen_t addr_len = sizeof(client_addr);
        auto client_sock = accept4(server_sock, (sockaddr *)&client_addr, &addr_len, SOCK_NONBLOCK);

        if (client_sock == -1) {

            if (errno == EINTR) continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EMFILE) break;

            LOG_ERROR("accept4 failed with error %d", errno);
            OnError(errno);
            break;
        }

        CSocket::SetSocketNoDelay(client_sock, 1);

        std::string client_ip = inet_ntoa(client_addr.sin_addr);
        uint16_t client_port = ntohs(client_addr.sin_port);

        LOG_NORMAL("New connection from %s:%u", client_ip.c_str(), client_port);

        SessionManager::GetInstance()->CacheSessionInfo(m_sock_ctx.sess_type,
            m_sock_ctx.sess_param, m_sock_ctx.encrypt, false,
            "", 0, client_ip, client_port, client_sock);
    }
}
