#include<iostream>
#include<WinSock2.h>
#include<map>
#include<vector>
#include<thread>
#include<set>
#include <functional>
#include <cstdint>

#include <iconv.h>
#include <mutex>

#include"HttpParse.hpp"
#include "Log.h"
#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1


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

enum sock_type {
	sock_normal,
	sock_http,
	sock_ws,
};

struct SOCK_DATA {
	std::string ip;
	int         port;
	uint8_t     type;
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

	//namespace wspp = websocketpp;

	std::map<SOCKET,SOCK_DATA>m_s;

	std::mutex m;

	while (1) {
		auto n_sock = accept(sock, (sockaddr*)&n_addr, &nsize);
		int idx = 0;
		if (n_sock == INVALID_SOCKET) {
			LOG_ERROR("accept failed!");
		}
		SOCK_DATA data;
		data.port = ntohs(n_addr.sin_port);
		//data.ip = inet_ntoa(n_addr.sin_addr);
		data.type = sock_normal;
		m_s[n_sock] = data;

		std::thread t([=]() mutable{
			char buf[1000] = {0};
			char sendbuf[1000] = { 0 };
			while (1) {
				memset(buf, 0, 1000);
				memset(sendbuf, 0, 1000);
				recv(n_sock, buf, 1000, 0);
				std::cout << buf << std::endl;
				if (strlen(buf) == 0){
					closesocket(n_sock);
					return;
				}

				if (m_s[n_sock].type == sock_normal) {
					auto ret = HttpParse::GetInstance()->Parse(buf, strlen(buf), sendbuf);
					if (ret) {
						m_s[n_sock].type = sock_ws;
						send(n_sock, sendbuf, strlen(sendbuf), 0);
						continue;
					}
					std::string msg = "send message:";
					msg += buf;
					send(n_sock, msg.c_str(), msg.size(), 0);
				}
				else {
				// send ws message
					std::cout << "send ws message" << std::endl;
				}

				std::this_thread::sleep_for(std::chrono::seconds(1));

			}
			});
		t.join();
	}

	return 0;
}