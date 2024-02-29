#pragma once
#include <iostream>
#include<winsock2.h>
#include<vector>
#pragma comment(lib,"ws2_32")

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7890);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	bind(sock, (sockaddr*)&addr, sizeof(addr));

	listen(sock, 128);

	// �������
	fd_set fdSocket; //�׽��ּ���
	FD_ZERO(&fdSocket);
	FD_SET(sock, &fdSocket);

	while (true) {
		FD_SET fdRead = fdSocket;
		int ret = ::select(0, &fdRead, NULL, NULL, NULL);
		if (ret > 0) {
			for (int i = 0; i < fdRead.fd_count; i++) {
				if (FD_ISSET(fdSocket.fd_array[i], &fdRead)) {
					if (fdSocket.fd_array[i] == sock) {
						sockaddr_in c_addr;
						int len = sizeof(c_addr);

						auto c_sock = ::accept(sock, (sockaddr*)&c_addr, &len);
						FD_SET(c_sock, &fdSocket); //�����ӵķŵ�������

					}
					else
					{
						//more connect
					}
				}
				else {
					// ���������ӵĶ�sock
					char buff[256];
					int _recv = ::recv(fdSocket.fd_array[i], buff, strlen(buff), 0);
					if (_recv) {
					   //success  �ɶ���
						
					}
					else {
						::closesocket(fdSocket.fd_array[i]);
						FD_CLR(fdSocket.fd_array[i], &fdSocket); // ������ӹرյ�socket
					}
				
				}
			}
		}
		else {
		//select failed
		}


	}

	return 0;
}