#pragma once

#include "Type.h"
#include "sock_context.h"

class CListener
{
public:
    CListener();
    ~CListener();

    bool Start(const std::string &ip, uint32_t port);
    void Stop();

    void SetType(int type) { m_sock_ctx.sess_type = type; }
    void SetParam(int param) { m_sock_ctx.sess_param = param; }
    void SetEncrypt(bool encrypt) { m_sock_ctx.encrypt = encrypt; }

    void OnAccept();
    void OnError(int error);

private:
    sock_context m_sock_ctx;
};
