#pragma once
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<thread>
#include<iostream>

#define LENGTH 128

enum IO_TYPE {
	IO_TYPE_ACCEPT,
	IO_TYPE_RECV,
	IO_TYPE_SEND,
};

enum HANDLE_TYPE {
	HANDLE_TYPE_LISTEN,
	HANDLE_TYPE_SOCKET,
};

 struct pre_handle_data{
	 HANDLE_TYPE _Type;
	 void* _Pointer;
};
 typedef pre_handle_data PRE_HANDLE_DATA;

struct pre_io_data {
	OVERLAPPED overlapped;       //iocp的句柄（id）（描述符）
	SOCKET     socket;           // io请求中的套接字
	LPWSABUF     wsabuf;         // 用于从缓冲区中获取数据的结构
	char       buffer[LENGTH];   // 保存获取的数据
	IO_TYPE    opt_type;         // io的请求类型
};
typedef pre_io_data PRE_IO_DATA;

struct stDataCache
{
	char* _Data;
	UINT _MaxLen;
	UINT _Len;
};
typedef stDataCache DATA_CACHE;

class CSocket
{
public:
	CSocket() {};
	~CSocket() {}

	void CreateListener();

	void OnSend(UINT len);
	void OnRecv(UINT len);

	bool PostRecv();


private:

	PRE_HANDLE_DATA m_HandleData;
	PRE_IO_DATA m_IoDataSend;
	PRE_IO_DATA m_IoDataRecv;

	SOCKET m_Socket;

	char* m_SendBuf;
	char* m_RecvBuf;

	unsigned int m_SendSize;
	unsigned int m_RecvSize;
	unsigned int m_SendPos;
	unsigned int m_RecvPos;

	DATA_CACHE m_SendDataCache;
	DATA_CACHE m_RecvDataCache;
};