#include<iostream>
#include<WinSock2.h>
#include<map>
#include<vector>
#include<thread>
#include<set>
#include <functional>
#include <cstdint>

#include <iconv.h>
#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/processors/hybi07.hpp>
#include <websocketpp/processors/hybi08.hpp>
#include <websocketpp/processors/hybi13.hpp>

#include <websocketpp/config/core.hpp>
#include <websocketpp/processors/processor.hpp>

#include "Log.h"
#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

using ws_config = websocketpp::config::core;
using ws_processor = websocketpp::processor::processor<ws_config>;
using ws_processor_ptr = websocketpp::lib::shared_ptr<ws_processor>;
using msg_manager = ws_config::con_msg_manager_type;
using msg_manager_ptr = msg_manager::ptr;
using rng_type = ws_config::rng_type;

static msg_manager_ptr m_msg_manager = nullptr;
static ws_processor_ptr m_processor = nullptr;
static rng_type m_rng;

void InitWSProcessor(int version)
{
	using namespace websocketpp;
	m_msg_manager = lib::make_shared<msg_manager>();
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

std::string gbk_to_utf8(const char* str)
{
	if (!str || !str[0]) return "";

	auto inleft = strlen(str);
	auto outleft = inleft * 2 + 1;

	std::string utf8str(outleft, '\0');

	auto* inbuf = (char*)str;
	auto* outbuf = (char*)utf8str.data();

	auto cd = iconv_open("UTF-8", "GBK");
	iconv(cd, &inbuf, &inleft, &outbuf, &outleft);
	iconv_close(cd);

	utf8str.erase(utf8str.size() - outleft, outleft);
	return utf8str;
}

struct SOCK_DATA {
	std::string ip;
	int port;
};

int main() {
	WSADATA _WsaData;
	int res = WSAStartup(MAKEWORD(2, 2),&_WsaData);
	if (res != NO_ERROR) {
		LOG_ERROR("WSAstartup failed!");
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET) {
		LOG_ERROR("create sock failed!");
	}

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(16999);

	if (-1 == bind(sock, (sockaddr*)&addr, sizeof(addr))) {
		LOG_ERROR("bind failed!");
	}

	if (-1 == listen(sock, 128)) {
		LOG_ERROR("listen failed!");
	}

	sockaddr_in n_addr = {0};
	int nsize = sizeof(n_addr);

	namespace wspp = websocketpp;

	std::map<SOCKET,SOCK_DATA>m_s;
	while (1) {
		auto n_sock = accept(sock, (sockaddr*)&n_addr, &nsize);
		if (n_sock == INVALID_SOCKET) {
			LOG_ERROR("accept failed!");
		}
		SOCK_DATA data;
		data.port = ntohs(n_addr.sin_port);
		//data.ip = inet_ntoa(n_addr.sin_addr);
		m_s[n_sock] = data;
		std::thread t([&]() {
			char buf[1000] = {0};
			while (1) {
				memset(buf, 0, 1000);
				recv(n_sock, buf, 1000, 0);

				namespace wspp = websocketpp;
				wspp::http::parser::request req;
				size_t processed = 0;

				try {
					processed = req.consume(buf, strlen(buf));
				}
				catch (wspp::http::exception& e) {
					LOG_ERROR("parse exception: %s", e.what());
					//m_RecvPos = 0;
					return;
				}

				if (!req.ready()) {
					//if (m_RecvPos > 1024) m_RecvPos = 0;
					return;
				}

				if (wspp::processor::is_websocket_handshake(req)) {

					auto version = wspp::processor::get_websocket_version(req);
					InitWSProcessor(version);

					if (m_processor) {
						auto ec = m_processor->validate_handshake(req);

						if (ec) {
							LOG_ERROR("validate_handshake failed with error %d", ec.value());
						}
						else {
							wspp::http::parser::response rsp;
							ec = m_processor->process_handshake(req, "", rsp);
							if (ec) {
								LOG_ERROR("process_handshake failed with error %d", ec.value());
							}
							else {
								rsp.set_version("HTTP/1.1");
								rsp.set_status(wspp::http::status_code::switching_protocols);
								rsp.append_header("Sec-WebSocket-Protocol", "binary");
								auto ans = rsp.raw();
								send(n_sock, ans.c_str(), ans.length(), 0);
							}
						}
					}
					else {
						LOG_ERROR("InitWSProcessor failed, version: %d", version);
					}
				}

				if (strcmp(buf, "close") == 0) {
					closesocket(n_sock);
					m_s.erase(n_sock);
					break;
				}
				std::cout << buf << std::endl;
				memset(buf, 'a', 1000);
				send(n_sock, buf, 1000, 0);

				//std::this_thread::sleep_for(std::chrono::seconds(1));

			}
			});
		t.join();
	}

	return 0;
}