#pragma once

#include "Type.h"


enum socket_type
{
    sock_type_invalid   = 0,
    sock_type_connect   = 1,
    sock_type_listen    = 2,
    sock_type_io        = 3
};

struct sock_context
{
    int             sock_fd         = INVALID_SOCKET;
    socket_type     sock_type       = sock_type_invalid;

    int             sess_type       = SESSION_TYPE_INVALID;
    int             sess_param      = 0;
    bool            encrypt         = false;

    std::string     conn_ip;
    uint16_t        conn_port       = 0;
    bool            connected       = false;

    void           *event_handler   = nullptr;

    sock_context() = default;

    sock_context(int sock_fd_, socket_type sock_type_, int sess_type_, int sess_param_,
                 bool encrypt_, const std::string &conn_ip_, uint16_t conn_port_, void *event_handler_)
        : sock_fd(sock_fd_)
        , sock_type(sock_type_)
        , sess_type(sess_type_)
        , sess_param(sess_param_)
        , encrypt(encrypt_)
        , conn_ip(conn_ip_)
        , conn_port(conn_port_)
        , event_handler(event_handler_)
    {}
};

using sock_context_list = std::list<sock_context>;


struct data_cache
{
    char           *buff            = nullptr;
    uint32_t        buff_size       = 0;
    int32_t         data_len        = 0;
    uint32_t        user_data       = 0;
    bool            candrop         = false;

    void reset() {
        buff        = nullptr;
        buff_size   = 0;
        data_len    = 0;
        user_data   = 0;
        candrop     = false;
    }

    bool empty() {
        return (buff == nullptr) || (buff_size == 0);
    }
};

using data_cache_list = std::list<data_cache>;
