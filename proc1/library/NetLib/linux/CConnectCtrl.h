#pragma once

#include "sock_context.h"
#include "CMutex.h"

class CConnectCtrl
{
public:
    CConnectCtrl();
    ~CConnectCtrl();

    void AddConnector(const std::string &ip, uint32_t port, int sess_type, int sess_param = 0, bool encrypt = false);

    void OnConnect(sock_context *ctx);
    void OnLost(sock_context *ctx);
    void OnError(sock_context *ctx, int error);

    void RemoveSockContext(sock_context *ctx);

private:
    sock_context * AddSockContext(int sock_fd, int sess_type, int sess_param,
        bool encrypt, const std::string &conn_ip, uint16_t conn_port);

private:
    CMutex m_mutex;
    sock_context_list m_sock_ctx_list;
};
