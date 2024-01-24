#pragma once
#include <WinSock2.h>
#include "Type.h"
#include <list>
#include "CMutex.h"
#include "ISession.h"

#include <websocketpp/config/core.hpp>
#include <websocketpp/processors/processor.hpp>

enum HANDLE_TYPE
{
	HANDLE_TYPE_LISTEN,
	HANDLE_TYPE_SOCKET,
};

enum IO_TYPE
{
	IO_TYPE_ACCEPT,
	IO_TYPE_RECV,
	IO_TYPE_SEND,
};

enum CLIENT_PROTO
{
    CLIENT_PROTO_DEF,
    CLIENT_PROTO_WS
};

enum DATA_TYPE
{
    DATA_TYPE_DEF,
    DATA_TYPE_HTTP,
    DATA_TYPE_WS
};

struct stPerHandleData
{
	HANDLE_TYPE _Type;
	void* _Pointer;
};
typedef stPerHandleData PER_HANDLE_DATA;

struct stPerIoData
{
	OVERLAPPED _OverLapped;
	IO_TYPE _Type;
	SOCKET _Socket;
	LPWSABUF _WsaBuf;
	char _Buf[128];
};
typedef stPerIoData PER_IO_DATA;

struct stDataCache
{
	char* _Data;
	UINT _MaxLen;
	UINT _Len;
};
typedef stDataCache DATA_CACHE;

class CSocket
{
    using ws_config = websocketpp::config::core;
    using ws_processor = websocketpp::processor::processor<ws_config>;
    using ws_processor_ptr = websocketpp::lib::shared_ptr<ws_processor>;
    using msg_manager = ws_config::con_msg_manager_type;
    using msg_manager_ptr = msg_manager::ptr;
    using rng_type = ws_config::rng_type;
	using cache_info_type = std::map<uint32_t, DEBUG_DATA::cache_value>;

public:
	CSocket();
	~CSocket();

public:
	UINT GetID() { return m_ID; }
	bool IsConnected() { return m_IsConnect; }
	void OnUpdate(int _Delta);

	void OnEstablish(SOCKET _Socket);
	void OnLost();
	void DoClose();

	void DoSend(const void* _Data, UINT _Len, bool candrop = false);
    void SendDirectly(const void *_Data, UINT _Len);
	bool PostSend();
	void OnSend(UINT _Len);

	void OnRecv(UINT _Len);
	bool PostRecv();

	bool HandleIocpError(DWORD _Error);

	void SetLocalIpPort(std::string& _LocalIP, UINT _LocalPort);
	void SetRemoteIpPort(std::string& _RemoteIP, UINT _RemotePort);
	std::string GetLocalIp() { return m_LocalIP; };
	std::string GetRemoteIp() { return m_RemoteIP; };
	UINT GetLocalPort() { return m_LocalPort; };
	UINT GetRemotePort() { return m_RemotePort; };

	void SetSession(ISession* _pSession);
    void SetEncrypt(bool _Encrypt) { m_Encrypt = _Encrypt; }

	void OnError(DWORD _ErrorCode);

	void LogDebugInfo(DEBUG_DATA& debugData);

private:
	void Init();
	void UnInit();
	bool AssociateWithIocp();
	bool IsSocketAlive();
	//void ParseIpAndPort();

	void IncPostRecv();
	void DecPostRecv();
	uint32_t GetPostRecv();

    void ParsePacks();
    void ParsePacks_Default();
    void ParsePacks_HTTP();
    void ParsePacks_WebSocket();

    void DoSend_Default(const void *_Data, UINT _Len);
    void DoSend_WebSocket(const void *_Data, UINT _Len);

    void InitWSProcessor(int version);
    void SetDataType(DATA_TYPE type) { m_DataType = type; }
    DATA_TYPE GetDataType() { return m_DataType; }
private:
	UINT m_ID;
	SOCKET m_Socket;
	bool m_IsConnect;

	char* m_SendBuf;
	char* m_RecvBuf;
	unsigned int m_SendSize;
	unsigned int m_RecvSize;
	int m_SendPos;
	int m_RecvPos;

	PER_HANDLE_DATA m_HandleData;
	PER_IO_DATA m_IoDataSend;
	PER_IO_DATA m_IoDataRecv;
    DATA_TYPE m_DataType;

	std::list<DATA_CACHE> m_SendCache;
	std::list<DATA_CACHE> m_RecvCache;
	CMutex m_SendMutex;
	CMutex m_RecvMutex;

	std::string m_LocalIP;
	UINT m_LocalPort;
	std::string m_RemoteIP;
	UINT m_RemotePort;

	ISession* m_pSession;
    bool m_Encrypt;
	bool m_NeedClose;
    bool m_bNeedNotifySessionOnLost;

	bool m_SendingData;

	DATA_CACHE m_SendDataCache;
	DATA_CACHE m_RecvDataCache;

	volatile uint32_t m_dwPostRecv;

	uint32_t m_SendPeak = 0;
	uint32_t m_RecvPeak = 0;

    AES      m_aes;

    ws_processor_ptr                m_processor;
    msg_manager_ptr                 m_msg_manager;
    static rng_type                 m_rng;
};
