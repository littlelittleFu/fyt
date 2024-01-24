#pragma once

#include "Type.h"
#include "ISession.h"
#include "sock_context.h"
#include "CMutex.h"
#include "AES.h"

#include <websocketpp/config/core.hpp>
#include <websocketpp/processors/processor.hpp>

enum CLIENT_PROTO
{
    CLIENT_PROTO_DEF,
    CLIENT_PROTO_WS,
    SERVER_PROTO_WS
};

enum DATA_TYPE
{
    DATA_TYPE_DEF,
    DATA_TYPE_HTTP,
    DATA_TYPE_WS,
    DATA_TYPE_CL_HTTP,
    DATA_TYPE_CL_WS,
};

class CSocket
{
    using ws_config = websocketpp::config::core;
    using ws_processor = websocketpp::processor::processor<ws_config>;
    using ws_processor_ptr = websocketpp::lib::shared_ptr<ws_processor>;
    using msg_manager = ws_config::con_msg_manager_type;
    using msg_manager_ptr = msg_manager::ptr;
    using rng_type = ws_config::rng_type;
    using cache_info_type = std::map<uint32_t, DEBUG_DATA::cache_value>;

    enum send_data_result {
        send_data_success       = 0,
        send_data_invalid_fd    = 1,
        send_data_would_block   = 2,
        send_data_lost_conn     = 3,
    };

    enum read_data_result {
        read_data_success       = 0,
        read_data_invalid_fd    = 1,
        read_data_would_block   = 2,
        read_data_lost_conn     = 3,
        read_data_sock_error    = 4,
        read_data_weird         = 5,
        read_data_invalid_data  = 6,
    };

    static const size_t HDRLEN  = 4;

public:
    CSocket();
    ~CSocket();

    uint32_t GetID() { return m_sock_id; }

    bool IsConnected() { return m_connected; }

    void OnUpdate(int delta);

    void OnEstablish(int fd);
    void OnLost();
    void OnError(uint32_t errcode);

    void DoClose();
    void DoSend(const void *data, uint32_t len, bool candrop = false);
    void SendDirectly(const void *data, uint32_t len, uint32_t msgid = 0, bool candrop = false);
    void OnSend();
    void OnRecv();
    void LogDebugInfo(DEBUG_DATA &data);

    void SetSession(ISession *session) { m_session = session; }
    void SetEncrypt(bool encrypt) { m_sock_ctx.encrypt = encrypt; }

    void SetLocalIpPort(const std::string &ip, uint32_t port);
    std::string GetLocalIp() { return m_local_ip; };
    uint32_t GetLocalPort() { return m_local_port; };

    void SetRemoteIpPort(const std::string &ip, uint32_t port);
    std::string GetRemoteIp() { return m_remote_ip; };
    uint32_t GetRemotePort() { return m_remote_port; };

    void SetDataType(DATA_TYPE type) { m_data_type = type; }
    DATA_TYPE GetDataType() { return m_data_type; }

    static bool SetSocketReuseAddr(int sockfd, int enable);
    static bool SetSocketNoDelay(int sockfd, int enable);
    static int GetSocketError(int sockfd);
    static sockaddr GetSockAddr(const std::string &ip, uint32_t port);

private:
    send_data_result SendData(data_cache &cache);
    read_data_result RecvData(uint8_t *buff, uint32_t need_read, uint32_t &num_read);

    read_data_result ReadOnePack();

    void HandleRecvData();

    void ClearSendCache();
    void ClearRecvCache();

    void OnRecv_Default();
    void OnRecv_WebSocket();

    bool IsWSSession();
    bool IsWSServSession();

    void ParsePacks_HTTP();
    void ParsePacks_WebSocket();
    void ParsePacks_CL_HTTP();
    void ParsePacks_CL_WS();

    void InitWSProcessor(int version);
    void InitCLWSProcessor(int version);

    void DoSend_Default(const void *data, uint32_t len, bool candrop);
    void DoSend_WebSocket(const void *data, uint32_t len, bool candrop);
    void DoSend_CL_WebSocket_Request();
    void DoSend_CL_WebSocket(const void* data, uint32_t len, bool candrop);

    uint32_t GetMsgID(const void *data, uint32_t len);
    void RecordMsgID(data_cache &cache, const void *data, uint32_t len);
private:
    sock_context        m_sock_ctx;
    DATA_TYPE           m_data_type                 = DATA_TYPE_DEF;

    uint32_t            m_sock_id                   = 0;

    std::atomic<bool>   m_connected{false};
    std::atomic<bool>   m_notify_session_on_lost{false};
    std::atomic<bool>   m_sending{false};

    std::string         m_local_ip;
    uint32_t            m_local_port                = 0;

    std::string         m_remote_ip;
    uint32_t            m_remote_port               = 0;

    ISession           *m_session                   = nullptr;

    AES                 m_aes;

    CMutex              m_send_mutex;
    data_cache_list     m_send_caches;
    uint32_t            m_send_peak                 = 0;
    uint32_t            m_send_peak_MAX             = 0;

    CMutex              m_recv_mutex;
    uint8_t             m_header[HDRLEN]            = {0};
    size_t              m_header_read               = 0;
    data_cache          m_recv_cache;

    CMutex              m_recv_caches_mutex;
    data_cache_list     m_recv_caches;
    uint32_t            m_recv_peak                 = 0;
    uint32_t            m_recv_peak_MAX             = 0;

    ws_processor_ptr    m_processor;
    msg_manager_ptr     m_msg_manager;
    static rng_type     m_rng;
};
