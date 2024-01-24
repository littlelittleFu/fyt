#include "pch.h"
#include "CSocket.h"
#include "CEpollCtrl.h"
#include "CBufManager.h"
#include "Config.h"

#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/processors/hybi07.hpp>
#include <websocketpp/processors/hybi08.hpp>
#include <websocketpp/processors/hybi13.hpp>

CSocket::rng_type CSocket::m_rng;

CSocket::CSocket()
{
    static uint32_t sockid = 0;
    m_sock_id = ++sockid;

    m_sock_ctx.sock_type     = sock_type_io;
    m_sock_ctx.event_handler = this;

    unsigned char aes_key[32] = {
        0x4E, 0xD9, 0x83, 0x4F, 0x20, 0x59, 0x9E, 0x47, 0x6C, 0xFF, 0x0C, 0x74, 0x59, 0x29, 0x4E, 0x0B,
        0x00, 0x5B, 0x7E, 0xA2, 0x33, 0x58, 0xC4, 0x4E, 0x2C, 0x6C, 0xFD, 0x4E, 0x07, 0x38, 0x59, 0x7B };

    unsigned char aes_iv[32] = {
        0x21, 0x80, 0xA0, 0xCF, 0xB1, 0xA4, 0x40, 0x99, 0x2C, 0x50, 0x0F, 0x8E, 0xD1, 0x4F, 0xEE, 0xD7,
        0xC1, 0x7D, 0x22, 0x30, 0x7C, 0x36, 0x6A, 0xF7, 0xD0, 0x0D, 0xB7, 0x05, 0xAE, 0xE0, 0x97, 0x4D };

    m_aes.SetParam("cfb", 128, aes_key, _countof(aes_key), nullptr, 0);
}

CSocket::~CSocket()
{
    auto &fd = m_sock_ctx.sock_fd;
    if (fd != INVALID_SOCKET) {
        CEpollCtrl::GetInstance()->StopMonitor(fd);
        RELEASE_SOCKET(fd);
    }

    ClearSendCache();
    ClearRecvCache();
}

void CSocket::OnUpdate(int delta)
{
    if (m_notify_session_on_lost) {

        if (m_session && !m_session->IsInvalid()) {
            m_session->OnLost();
            m_session->SetInvalid(true);
        }

        m_notify_session_on_lost = false;
    }

    if (!m_connected) return;

    HandleRecvData();
}

void CSocket::HandleRecvData()
{
    if (!m_session) return;

    data_cache_list caches;
    {
        CLockGuard guard(m_recv_caches_mutex);
        if (m_recv_caches.empty()) return;
        caches.swap(m_recv_caches);
        m_recv_peak = 0;
    }

    for (auto &cache : caches) {

        if (!cache.buff || cache.data_len == 0) continue;

        switch (m_data_type) {

        case DATA_TYPE_DEF:
            if (m_sock_ctx.encrypt) {
                m_session->HandleMessage(cache.buff + cache.data_len, cache.data_len);      // 后半部分是解密数据
            }
            else {
                m_session->HandleMessage(cache.buff, cache.data_len);
            }
            break;

        case DATA_TYPE_WS:
            m_session->HandleMessage(cache.buff, cache.data_len);
            break;

        default:
            break;
        }

        CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
    }
}

void CSocket::OnEstablish(int fd)
{
    m_sock_ctx.sock_fd = fd;

    CEpollCtrl::GetInstance()->StartMonitor(fd, EPOLLIN | EPOLLET, &m_sock_ctx);

    m_connected = true;

    if (IsWSSession()) {
        LOG_TRACE("New ws client: %d", fd);
        SetDataType(DATA_TYPE_HTTP);
        m_recv_cache.buff_size = g_RecvBufSize;
        CBufManager::GetInstance()->GetSendOrRecvBuffer(m_recv_cache.buff, m_recv_cache.buff_size, false);
    }

    if (IsWSServSession()) {
        LOG_TRACE("New ws serve: %d", fd);
        DoSend_CL_WebSocket_Request();
        SetDataType(DATA_TYPE_CL_HTTP);
    }
}

bool CSocket::IsWSSession()
{
    return (m_session && m_session->GetParam() == CLIENT_PROTO_WS);
}

bool CSocket::IsWSServSession()
{
    return (m_session && m_session->GetParam() == SERVER_PROTO_WS);
}

void CSocket::OnLost()
{
    LOG_WARN("Lost connection with peer %s:%u", m_remote_ip.c_str(), m_remote_port);

    auto &fd = m_sock_ctx.sock_fd;
    if (IsWSSession()) {
        LOG_TRACE("Lost ws client: %d", fd);
    }
    if (fd == INVALID_SOCKET) return;

    CEpollCtrl::GetInstance()->StopMonitor(fd);
    RELEASE_SOCKET(fd);

    ClearSendCache();
    ClearRecvCache();

    m_connected = false;
    m_notify_session_on_lost = true;
}

void CSocket::OnError(uint32_t errcode)
{
    OnLost();
}

void CSocket::DoClose()
{
    auto &fd = m_sock_ctx.sock_fd;
    if (IsWSSession()) {
        LOG_TRACE("Lost ws client: %d", fd);
    }
    if (fd == INVALID_SOCKET) return;

    CEpollCtrl::GetInstance()->StopMonitor(fd);
    RELEASE_SOCKET(fd);

    ClearSendCache();
    ClearRecvCache();

    m_connected = false;
    m_notify_session_on_lost = true;
}

void CSocket::DoSend(const void *data, uint32_t len, bool candrop)
{
    switch (m_data_type) {

    case DATA_TYPE_DEF:
        DoSend_Default(data, len, candrop);
        break;

    case DATA_TYPE_WS:
        DoSend_WebSocket(data, len, candrop);
        break;

    case DATA_TYPE_CL_WS:
        DoSend_CL_WebSocket(_Data, _Len);
        break;

    default:
        LOG_ERROR("Unhandled data type: %d", m_data_type);
        break;
    }
}

uint32_t CSocket::GetMsgID(const void *data, uint32_t len)
{
    if (!data || len < 4) return 0;
    const auto *p = static_cast<const uint16_t *>(data);
    auto moduleid = *p;
    auto protoid = *(p + 1);
    auto msgid = moduleid * 10000 + protoid;
    return msgid;
}

void CSocket::RecordMsgID(data_cache &cache, const void *data, uint32_t len)
{
    cache.user_data = GetMsgID(data, len);
}

void CSocket::DoSend_Default(const void *data, uint32_t len, bool candrop)
{
    if (GetDataType() != DATA_TYPE_DEF) return;

    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) return;

    data_cache cache;
    cache.buff_size = cache.data_len = len + 4;
    CBufManager::GetInstance()->GetBuffer(cache.buff, cache.buff_size, true);

    if (!cache.buff) {
        LOG_ERROR("cache.buff is NULL");
        return;
    }

    RecordMsgID(cache, data, len);
    cache.candrop = candrop;

    auto *p = (uint8_t *)cache.buff;
    *(uint32_t *)p = cache.data_len;

    if (m_sock_ctx.encrypt) {
        auto rc = m_aes.Encrypt((uint8_t *)data, len, p + 4);
        if (rc < 0) {
            LOG_ERROR("Encrypt failed with error %d", rc);
            CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
            return;
        }
    }
    else {
        memcpy(p + 4, data, len);
    }

    m_send_mutex.Lock();
    m_send_caches.emplace_back(cache);
    m_send_peak ++;
    m_send_mutex.Unlock();
    if (m_send_peak_MAX < m_send_peak) m_send_peak_MAX = m_send_peak;

    CEpollCtrl::GetInstance()->ModifyMonitor(fd, EPOLLIN | EPOLLOUT | EPOLLET, &m_sock_ctx);
}

void CSocket::DoSend_WebSocket(const void *data, uint32_t len, bool candrop)
{
    if (GetDataType() != DATA_TYPE_WS) return;

    if (!m_processor) {
        LOG_ERROR("m_processor is nullptr");
        return;
    }

    if (!m_msg_manager) {
        LOG_ERROR("m_msg_manager is nullptr");
        return;
    }

    auto in = m_msg_manager->get_message();
    in->set_opcode(websocketpp::frame::opcode::BINARY);

    auto totalLen = len + sizeof(uint32_t);
    auto &in_payload = in->get_raw_payload();
    in_payload.resize(totalLen);

    auto *raw = const_cast<char *>(in_payload.data());
    memcpy(raw, &totalLen, sizeof(uint32_t));

    auto rc = m_aes.Encrypt(reinterpret_cast<const uint8_t *>(data), len,
        reinterpret_cast<uint8_t *>(raw) + sizeof(uint32_t));
    if (rc <= 0) {
        LOG_ERROR("Encrypt failed");
        return;
    }

    auto out = m_msg_manager->get_message();
    auto ec = m_processor->prepare_data_frame(in, out);
    if (ec) {
        LOG_ERROR("prepare_data_frame failed with error %d", ec.value());
        return;
    }

    auto sendData = out->get_header();
    sendData += out->get_payload();

    auto msgid = GetMsgID(data, len);
    SendDirectly(sendData.data(), sendData.size(), msgid, candrop);
}

void CSocket::DoSend_CL_WebSocket_Request()
{
    namespace wspp = websocketpp;
    wspp::http::parser::request req;

    InitCLWSProcessor(13);

    char uri[200] = { 0 };
    sprintf_s(uri, sizeof(uri), "ws://%s:%d", GetRemoteIp().c_str(), GetRemotePort());

    wspp::uri_ptr uriPtr = std::make_shared<wspp::uri>(uri);

    std::vector<std::string>subProtol;
    m_processor->client_handshake_request(req, uriPtr, subProtol);

    auto ans = req.raw();
    auto msgid = GetMsgID(data, len);
    SendDirectly(ans.c_str(), ans.length(), msgid, candrop);
}

void CSocket::DoSend_CL_WebSocket(const void* data, uint32_t len, bool candrop)
{
    if (GetDataType() != DATA_TYPE_CL_WS) return;

    if (!m_processor) {
        LOG_ERROR("m_processor is nullptr");
        return;
    }

    if (!m_msg_manager) {
        LOG_ERROR("m_msg_manager is nullptr");
        return;
    }

    auto in = m_msg_manager->get_message();
    in->set_opcode(websocketpp::frame::opcode::BINARY);

    auto totalLen = len /* + sizeof(uint32_t) */;
    auto& in_payload = in->get_raw_payload();
    in_payload.resize(totalLen);

    auto* raw = const_cast<char*>(in_payload.data());
    //memcpy(raw, &totalLen, sizeof(uint32_t));

    //auto rc = m_aes.Encrypt(reinterpret_cast<const uint8_t*>(data), len,
    //    reinterpret_cast<uint8_t*>(raw) + sizeof(uint32_t));
    //if (rc <= 0) {
    //    LOG_ERROR("Encrypt failed");
    //    return;
    //}

    auto out = m_msg_manager->get_message();
    auto ec = m_processor->prepare_data_frame(in, out);
    if (ec) {
        LOG_ERROR("prepare_data_frame failed with error %d", ec.value());
        return;
    }

    auto sendData = out->get_header();
    sendData += out->get_payload();

    auto msgid = GetMsgID(data, len);
    SendDirectly(sendData.data(), sendData.size(), msgid, candrop);
}

void CSocket::SendDirectly(const void *data, uint32_t len, uint32_t msgid, bool candrop)
{
    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) return;

    data_cache cache;
    cache.buff_size = cache.data_len = len;
    CBufManager::GetInstance()->GetBuffer(cache.buff, cache.buff_size, true);

    if (!cache.buff) {
        LOG_ERROR("GetBuffer failed");
        return;
    }

    memcpy_s(cache.buff, cache.data_len, data, len);
    cache.user_data = msgid;
    cache.candrop = candrop;

    m_send_mutex.Lock();
    m_send_caches.emplace_back(cache);
    m_send_peak ++;
    m_send_mutex.Unlock();
    if (m_send_peak_MAX < m_send_peak) m_send_peak_MAX = m_send_peak;

    CEpollCtrl::GetInstance()->ModifyMonitor(fd, EPOLLIN | EPOLLOUT | EPOLLET, &m_sock_ctx);
}

void CSocket::OnSend()
{
    auto sending = m_sending.exchange(true);
    if (sending) return;        // 保证一个SESSION的数据只有一个线程在发

    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) {
        m_sending = false;
        return;
    }

    data_cache_list send_caches;
    m_send_mutex.Lock();
    send_caches.swap(m_send_caches);
    uint32_t   temp_send_peak = m_send_peak;
    m_send_peak = 0;
    m_send_mutex.Unlock();

    if (send_caches.empty()) {
        CEpollCtrl::GetInstance()->ModifyMonitor(fd, EPOLLIN | EPOLLET, &m_sock_ctx);
        m_sending = false;
        return;
    }

    bool drop = false;
    if (temp_send_peak > 10000) drop = true;

    while (!send_caches.empty()) {

        auto &cache = send_caches.front();

        if (drop && cache.candrop) {
            //LOG_WARN("drop: %d", cache.user_data);
            CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
            send_caches.pop_front();
            temp_send_peak -= 1;
            continue;
        }

        auto result = SendData(cache);

        if (result == send_data_success) {
            CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
            send_caches.pop_front();
            temp_send_peak -= 1;
            continue;
        }

        m_send_mutex.Lock();
        m_send_caches.splice(m_send_caches.begin(), send_caches);
        m_send_peak += temp_send_peak;
        m_send_mutex.Unlock();

        if (result == send_data_lost_conn) {
            //OnLost();
        }

        break;
    }

    m_sending = false;
    CEpollCtrl::GetInstance()->ModifyMonitor(fd, EPOLLIN | EPOLLOUT | EPOLLET, &m_sock_ctx);
}

CSocket::send_data_result CSocket::SendData(data_cache &cache)
{
    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) return send_data_invalid_fd;

    auto *p = cache.buff;
    auto &left = cache.data_len;
    size_t n = 0;

    while (true) {

        auto num = send(fd, p + n, left, MSG_NOSIGNAL);

        if (num == left) return send_data_success;

        if (num > 0) {
            n += num;
            left -= num;
            continue;
        }

        if (errno == EINTR) continue;

        if (errno == EAGAIN || errno == EWOULDBLOCK) {

            if (n > 0) memmove(p, p + n, left);

            return send_data_would_block;
        }
        else {

            if (errno == ECONNRESET) {
                LOG_WARN("Connection reset by peer");
            }
            else if (errno == EPIPE) {
                LOG_WARN("Connection has been shut down");
            }
            else {
                LOG_WARN("write failed with error %d", errno);
            }

            return send_data_lost_conn;
        }
    }
}

void CSocket::ClearSendCache()
{
    CLockGuard guard(m_send_mutex);
    for (auto &cache : m_send_caches)
        CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
    m_send_caches.clear();
    m_send_peak = 0;
}

void CSocket::ClearRecvCache()
{
    data_cache_list caches;
    {
        CLockGuard guard(m_recv_caches_mutex);
        caches.swap(m_recv_caches);
        m_recv_peak = 0;
    }

    for (auto &cache : caches)
        CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);

    CLockGuard guard(m_recv_mutex);

    if (IsWSSession()) {
        CBufManager::GetInstance()->ReleaseSendOrRecvBuffer(m_recv_cache.buff, m_recv_cache.buff_size, false);
        m_recv_cache.reset();
    }
    else {
        CBufManager::GetInstance()->ReleaseBuffer(m_recv_cache.buff, m_recv_cache.buff_size);
        m_recv_cache.reset();
        m_header_read = 0;
    }
}

void CSocket::OnRecv()
{
    switch (m_data_type) {

    case DATA_TYPE_DEF:
        OnRecv_Default();
        break;

    case DATA_TYPE_HTTP:
    case DATA_TYPE_WS:
        OnRecv_WebSocket();
        break;

    case DATA_TYPE_CL_HTTP:
        ParsePacks_CL_HTTP();
        break;

    case DATA_TYPE_CL_WS:
        ParsePacks_CL_WS();
        break;

    default:
        LOG_ERROR("Unhandled data type: %d", m_data_type);
        break;
    }
}

void CSocket::OnRecv_Default()
{
    while (true) {

        auto result = ReadOnePack();

        if (result == read_data_invalid_fd ||
            result == read_data_would_block) break;

        if (result == read_data_lost_conn || result == read_data_sock_error) {
            //OnLost();
            break;
        }
    }
}

void CSocket::OnRecv_WebSocket()
{
    if (m_recv_cache.empty()) {
        LOG_ERROR("m_recv_cache is empty. sock: %d", m_sock_ctx.sock_fd);
        return;
    }

    uint8_t *p = reinterpret_cast<uint8_t *>(m_recv_cache.buff) + m_recv_cache.data_len;
    uint32_t need_read = m_recv_cache.buff_size - m_recv_cache.data_len;
    uint32_t num_read = 0;

    auto result = RecvData(p, need_read, num_read);
    if (result == read_data_lost_conn || result == read_data_sock_error) {
        //OnLost();
        return;
    }

    if (num_read == 0) return;
    m_recv_cache.data_len += num_read;

    switch (m_data_type) {

    case DATA_TYPE_HTTP:
        ParsePacks_HTTP();
        break;

    case DATA_TYPE_WS:
        ParsePacks_WebSocket();
        break;

    case DATA_TYPE_CL_HTTP:
        ParsePacks_CL_HTTP();
        break;

    case DATA_TYPE_CL_WS:
        ParsePacks_CL_WS();
        break;

    default:
        LOG_ERROR("Unhandled date type: %d", m_data_type);
        break;
    }
}

void CSocket::ParsePacks_HTTP()
{
    LOG_TRACE("ParsePacks_HTTP, data type: %d, sock: %d", GetDataType(), m_sock_ctx.sock_fd);
    if (GetDataType() != DATA_TYPE_HTTP) return;

    auto *recv_buf = m_recv_cache.buff;
    auto &data_len = m_recv_cache.data_len;
    if (!recv_buf || data_len == 0) return;

    namespace wspp = websocketpp;
    wspp::http::parser::request req;
    size_t processed = 0;

    try {
        processed = req.consume(recv_buf, data_len);
    }
    catch (wspp::http::exception &e) {
        LOG_ERROR("parse exception: %s", e.what());
        data_len = 0;
        return;
    }

    if (!req.ready()) {
        if (data_len > 1024) data_len = 0;
        return;
    }

    if (wspp::processor::is_websocket_handshake(req)) {

        auto version = wspp::processor::get_websocket_version(req);
        InitWSProcessor(version);

        if (m_processor) {
            auto ec = m_processor->validate_handshake(req);

            if (ec) {
                LOG_WARN("validate_handshake failed with error %d", ec.value());
            }
            else {
                wspp::http::parser::response rsp;
                ec = m_processor->process_handshake(req, "", rsp);
                if (ec) {
                    LOG_WARN("process_handshake failed with error %d", ec.value());
                }
                else {
                    rsp.set_version("HTTP/1.1");
                    rsp.set_status(wspp::http::status_code::switching_protocols);
                    rsp.append_header("Sec-WebSocket-Protocol", "binary");
                    auto ans = rsp.raw();
                    SendDirectly(ans.c_str(), ans.length());
                    LOG_TRACE("Send websocket handshake, sock: %d", m_sock_ctx.sock_fd);
                    SetDataType(DATA_TYPE_WS);
                }
            }
        }
        else {
            LOG_ERROR("InitWSProcessor failed, version: %d", version);
        }
    }

    data_len -= processed;
    if (data_len < 0) data_len = 0;
    if (data_len > 0) {
        memmove(recv_buf, recv_buf + processed, data_len);
        ParsePacks_WebSocket();
    }
}

void CSocket::ParsePacks_WebSocket()
{
    LOG_TRACE("ParsePacks_WebSocket, data type: %d", GetDataType());
    if (GetDataType() != DATA_TYPE_WS) return;

    auto *recv_buf = reinterpret_cast<uint8_t *>(m_recv_cache.buff);
    auto &data_len = m_recv_cache.data_len;
    if (!recv_buf || data_len == 0) return;

    if (!m_processor) {
        LOG_ERROR("m_processor is nullptr");
        data_len = 0;
        return;
    }

    size_t processed = 0;

    while (processed < data_len) {

        websocketpp::lib::error_code ec;
        auto num = m_processor->consume(recv_buf + processed, data_len - processed, ec);
        if (ec) {
            LOG_ERROR("consume failed with error code %d", ec.value());
            m_processor->reset_headers();
            if (num == 0) {
                data_len = 0;
                break;
            }
            else {
                processed += num;
                continue;
            }
        }

        processed += num;
        if (!m_processor->ready()) break;

        auto msg = m_processor->get_message();
        if (!msg) {
            LOG_ERROR("msg is nullptr");
            continue;
        }

        auto opcode = msg->get_opcode();

        if (is_control(opcode)) {
            // TODO: handle close opcode
            if (opcode == websocketpp::frame::opcode::close) {
                //OnLost();
            }
            else {
                LOG_WARN("Unhandled opcode: %d", msg->get_opcode());
            }
            continue;
        }

        // 数据
        const auto &payload = msg->get_payload();
        auto msglen = payload.length();

        auto *raw = reinterpret_cast<const uint8_t *>(payload.data());
        auto *len = reinterpret_cast<const uint32_t *>(raw);
        if (*len != msglen) {
            LOG_ERROR("Invalid msg format");
            continue;
        }

        data_cache cache;
        cache.data_len = msglen - sizeof(uint32_t);
        cache.buff_size = cache.data_len;

        CBufManager::GetInstance()->GetBuffer(cache.buff, cache.buff_size, true);

        if (!cache.buff) {
            LOG_ERROR("GetBuffer failed. len: %d", cache.data_len);
            continue;
        }

        auto rc = m_aes.Decrypt(raw + sizeof(uint32_t), cache.data_len,
            reinterpret_cast<uint8_t *>(cache.buff));
        if (rc <= 0) {
            LOG_ERROR("Decrypt failed with error %d", rc);
            CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
            continue;
        }

        RecordMsgID(cache, cache.buff, cache.data_len);

        size_t count = 0;
        {
            CLockGuard guard(m_recv_caches_mutex);
            m_recv_caches.emplace_back(cache);
            m_recv_peak ++;
        }
        if (m_recv_peak_MAX < m_recv_peak) m_recv_peak_MAX = m_recv_peak;
    }

    data_len -= processed;
    if (data_len < 0) data_len = 0;
    if (data_len > 0) memmove(recv_buf, recv_buf + processed, data_len);
}

void CSocket::ParsePacks_CL_HTTP()
{
    LOG_TRACE("ParsePacks_CL_HTTP, data type: %d", GetDataType());
    if (GetDataType() != DATA_TYPE_CL_HTTP) return;

    auto* recv_buf = reinterpret_cast<uint8_t*>(m_recv_cache.buff);
    auto& data_len = m_recv_cache.data_len;
    if (!recv_buf || data_len == 0) return;

    namespace wspp = websocketpp;
    wspp::http::parser::response rsp;
    size_t processed = 0;

    try {
        processed = rsp.consume(recv_buf, data_len);
    }
    catch (wspp::http::exception& e) {
        LOG_ERROR("CL Http Response parse exception: %s", e.what());
        m_RecvPos = 0;
        return;
    }

    if (m_processor) {
        wspp::http::parser::request req;
        {
            char uri[200] = { 0 };
            sprintf_s(uri, sizeof(uri), "ws://%s:%d", GetRemoteIp().c_str(), GetRemotePort());
            wspp::uri_ptr uriPtr = std::make_shared<wspp::uri>(uri);
            std::vector<std::string>subProtol;
            m_processor->client_handshake_request(req, uriPtr, subProtol);
        }
        auto ec = m_processor->validate_server_handshake_response(req, rsp);

        if (ec) {
            LOG_WARN("validate_server_handshake_response failed with error %d", ec.value());
        }
        else {
            SetDataType(DATA_TYPE_CL_WS);
            //char buff[100] = "abc";
            //DoSend_WebSocket(buff, strlen(buff));
        }
    }

    data_len -= processed;
    if (data_len < 0) data_len = 0;
    if (data_len > 0) memmove(recv_buf, recv_buf + processed, data_len);
}

void CSocket::ParsePacks_CL_WS()
{
    LOG_TRACE("ParsePacks_CL_WS, data type: %d", GetDataType());
    if (GetDataType() != DATA_TYPE_CL_WS) return;

    auto* recv_buf = reinterpret_cast<uint8_t*>(m_recv_cache.buff);
    auto& data_len = m_recv_cache.data_len;
    if (!recv_buf || data_len == 0) return;

    if (!m_processor) {
        LOG_ERROR("m_processor is nullptr");
        data_len = 0;
        return;
    }

    size_t processed = 0;

    while (processed < data_len) {

        websocketpp::lib::error_code ec;
        auto num = m_processor->consume(recv_buf + processed, data_len - processed, ec);
        if (ec) {
            LOG_ERROR("consume failed with error code %d", ec.value());
            m_processor->reset_headers();
            if (num == 0) {
                data_len = 0;
                break;
            }
            else {
                processed += num;
                continue;
            }
        }

        processed += num;
        if (!m_processor->ready()) break;

        auto msg = m_processor->get_message();
        if (!msg) {
            LOG_ERROR("msg is nullptr");
            continue;
        }

        auto opcode = msg->get_opcode();

        if (is_control(opcode)) {
            // TODO: handle close opcode
            if (opcode == websocketpp::frame::opcode::close) {
                //OnLost();
            }
            else {
                LOG_WARN("Unhandled opcode: %d", msg->get_opcode());
            }
            continue;
        }

        // 数据
        const auto& payload = msg->get_payload();
        auto msglen = payload.length();

        data_cache cache;
        cache.data_len = msglen;
        cache.buff_size = cache.data_len;

        CBufManager::GetInstance()->GetBuffer(cache.buff, cache.buff_size, true);

        if (!cache.buff) {
            LOG_ERROR("GetBuffer failed. len: %d", cache.data_len);
            continue;
        }

        memcpy(cache.buff, payload.c_str(), cache.data_len);

        RecordMsgID(cache, cache.buff, cache.data_len);

        size_t count = 0;
        {
            CLockGuard guard(m_recv_caches_mutex);
            m_recv_caches.emplace_back(cache);
            m_recv_peak++;
        }
        if (m_recv_peak_MAX < m_recv_peak) m_recv_peak_MAX = m_recv_peak;
    }

    data_len -= processed;
    if (data_len < 0) data_len = 0;
    if (data_len > 0) memmove(recv_buf, recv_buf + processed, data_len);
}

void CSocket::ParsePacks_CL_HTTP()
{
    if (GetDataType() != DATA_TYPE_CL_HTTP) return;

    namespace wspp = websocketpp;
    wspp::http::parser::response rsp;
    size_t processed = 0;

    try {
        processed = rsp.consume(m_RecvBuf, m_RecvPos);
    }
    catch (wspp::http::exception& e) {
        LOG_ERROR("CL Http Response parse exception: %s", e.what());
        m_RecvPos = 0;
        return;
    }

    if (m_processor) {
        wspp::http::parser::request req;
        {
            char uri[200] = { 0 };
            sprintf_s(uri, sizeof(uri), "ws://%s:%d", GetRemoteIp().c_str(), GetRemotePort());
            wspp::uri_ptr uriPtr = std::make_shared<wspp::uri>(uri);
            std::vector<std::string>subProtol;
            m_processor->client_handshake_request(req, uriPtr, subProtol);
        }
        auto ec = m_processor->validate_server_handshake_response(req, rsp);

        if (ec) {
            LOG_WARN("validate_server_handshake_response failed with error %d", ec.value());
        }
        else {
            SetDataType(DATA_TYPE_CL_WS);
            //char buff[100] = "abc";
            //DoSend_WebSocket(buff, strlen(buff));
        }
    }

    m_RecvPos -= processed;
    if (m_RecvPos < 0) m_RecvPos = 0;
    if (m_RecvPos > 0) {
        memmove(m_RecvBuf, m_RecvBuf + processed, m_RecvPos);
        ParsePacks();
    }
}

void CSocket::ParsePacks_CL_WS()
{

}

void CSocket::InitWSProcessor(int version)
{
    using namespace websocketpp;

    if (m_processor) return;
    if (!m_msg_manager) m_msg_manager = lib::make_shared<msg_manager>();

    switch (version) {
    case 0:
        m_processor = lib::make_shared<processor::hybi00<ws_config>>(false, true, m_msg_manager);
        break;
    case 7:
        m_processor = lib::make_shared<processor::hybi07<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
        break;
    case 8:
        m_processor = lib::make_shared<processor::hybi08<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
        break;
    case 13:
        m_processor = lib::make_shared<processor::hybi13<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
        break;
    default:
        break;
    }
}

void CSocket::InitCLWSProcessor(int version)
{
    using namespace websocketpp;

    if (m_processor) return;
    if (!m_msg_manager) m_msg_manager = lib::make_shared<msg_manager>();

    switch (version) {
    case 0:
        m_processor = lib::make_shared<processor::hybi00<ws_config>>(false, false, m_msg_manager);
        break;
    case 7:
        m_processor = lib::make_shared<processor::hybi07<ws_config>>(false, false, m_msg_manager, lib::ref(m_rng));
        break;
    case 8:
        m_processor = lib::make_shared<processor::hybi08<ws_config>>(false, false, m_msg_manager, lib::ref(m_rng));
        break;
    case 13:
        m_processor = lib::make_shared<processor::hybi13<ws_config>>(false, false, m_msg_manager, lib::ref(m_rng));
        break;
    default:
        break;
    }
}

CSocket::read_data_result CSocket::ReadOnePack()
{
    CLockGuard guard(m_recv_mutex);

    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) return read_data_invalid_fd;

    uint32_t need_read = 0;
    uint32_t num_read = 0;
    uint8_t *p = nullptr;

    if (m_header_read < HDRLEN) {

        need_read = HDRLEN - m_header_read;
        p = m_header + m_header_read;

        auto result = RecvData(p, need_read, num_read);
        m_header_read += num_read;

        if (result != read_data_success) return result;
    }

    auto &cache = m_recv_cache;

    need_read = *(uint32_t *)m_header - HDRLEN;
    if (need_read == 0) {
        LOG_ERROR("No data after header");
        CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
        cache.reset();
        m_header_read = 0;
        return read_data_weird;
    }

    if (cache.empty()) {
        cache.buff_size = m_sock_ctx.encrypt ? need_read * 2 : need_read;     // 加密数据后半部分用于解密
        CBufManager::GetInstance()->GetBuffer(cache.buff, cache.buff_size, true);
        cache.data_len = 0;
    }

    if (cache.data_len >= need_read) {
        LOG_ERROR("IMPOSSIBLE!!!");
        CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
        cache.reset();
        m_header_read = 0;
        return read_data_weird;
    }

    // LOG_TRACE("cache buff: %p, data_len: %d, buff_size: %d, need_read: %d",
    //     cache.buff, cache.data_len, cache.buff_size, need_read);

    need_read -= cache.data_len;
    p = (uint8_t *)cache.buff + cache.data_len;

    auto result = RecvData(p, need_read, num_read);
    cache.data_len += num_read;

    if (result != read_data_success) return result;

    if (m_sock_ctx.encrypt) {
        auto rc = m_aes.Decrypt((uint8_t *)cache.buff, cache.data_len, (uint8_t *)cache.buff + cache.data_len);

        if (rc < 0) {
            LOG_ERROR("Decrypt failed with error %d", rc);
            CBufManager::GetInstance()->ReleaseBuffer(cache.buff, cache.buff_size);
            cache.reset();
            m_header_read = 0;
            return read_data_invalid_data;
        }

        RecordMsgID(cache, cache.buff + cache.data_len, cache.data_len);
    }
    else {
        RecordMsgID(cache, cache.buff, cache.data_len);
    }

    size_t num = 0;
    {
        CLockGuard guard(m_recv_caches_mutex);
        m_recv_caches.emplace_back(cache);
        m_recv_peak ++;
    }
    if (m_recv_peak_MAX < m_recv_peak) m_recv_peak_MAX = m_recv_peak;

    cache.reset();
    m_header_read = 0;

    return read_data_success;
}

CSocket::read_data_result CSocket::RecvData(uint8_t *buff, uint32_t need_read, uint32_t &num_read)
{
    auto &fd = m_sock_ctx.sock_fd;
    if (fd == INVALID_SOCKET) return read_data_invalid_fd;

    num_read = 0;

    while (true) {

        auto num = read(fd, buff + num_read, need_read);

        if (num > 0) {
            num_read += num;
            need_read -= num;
            if (need_read == 0) return read_data_success;
            continue;
        }

        if (num == 0) {
            LOG_WARN("peer shutdown");
            return read_data_lost_conn;
        }

        if (errno == EINTR) continue;

        if (errno == EAGAIN || errno == EWOULDBLOCK) return read_data_would_block;

        LOG_WARN("read failed with error %d", errno);
        return read_data_sock_error;
    }
}

void CSocket::SetLocalIpPort(const std::string &ip, uint32_t port)
{
    m_local_ip = ip;
    m_local_port = port;
}

void CSocket::SetRemoteIpPort(const std::string &ip, uint32_t port)
{
    m_remote_ip = ip;
    m_remote_port = port;
}

void CSocket::LogDebugInfo(DEBUG_DATA &data)
{
    {
        CLockGuard guard(m_send_mutex);
        data.sendCache += m_send_peak;
        for (auto &cache : m_send_caches) {
            data.sendMem += cache.data_len;
        }

        if (data.sendPeak < m_send_peak_MAX)
            data.sendPeak = m_send_peak_MAX;
    }

    {
        CLockGuard guard(m_recv_caches_mutex);
        data.recvCache += m_recv_peak;
        for (auto &cache : m_recv_caches) {
            data.recvMem += cache.data_len;
        }

        if (data.recvPeak < m_recv_peak_MAX)
            data.recvPeak = m_recv_peak_MAX;
    }
}

bool CSocket::SetSocketReuseAddr(int sockfd, int enable)
{
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
        LOG_WARN("setsocketopt failed with error %d", errno);
        return false;
    }
    return true;
}

bool CSocket::SetSocketNoDelay(int sockfd, int enable)
{
    if (setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable)) == -1) {
        LOG_WARN("setsocketopt failed with error %d", errno);
        return false;
    }
    return true;
}

int CSocket::GetSocketError(int sockfd)
{
    int error;
    socklen_t len = sizeof(int);

    if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) == -1) {
        LOG_WARN("getsockopt failed with error %d", errno);
        return -1;
    }

    return error;
}

sockaddr CSocket::GetSockAddr(const std::string &ip, uint32_t port)
{
    sockaddr addr{0};
    auto *paddr = (sockaddr_in *)&addr;

    paddr->sin_family = AF_INET;
    paddr->sin_addr.s_addr = ip.empty() ? htonl(INADDR_ANY) : inet_addr(ip.c_str());
    paddr->sin_port = htons(static_cast<uint16_t>(port));

    return addr;
}
