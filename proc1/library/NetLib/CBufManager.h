#pragma once
#include "Type.h"
#include <map>
#include <unordered_set>
#include "CMutex.h"
using namespace std;
class CBufManager
{
private:
	CBufManager();
	~CBufManager();
	void Init();

public:
	void OnUpdate(INT _Delta);
	bool GetSendOrRecvBuffer(char*& _Buffer, UINT& _Size, bool beSend = true);
	void ReleaseSendOrRecvBuffer(char*& _Buffer, UINT& _Size, bool beSend = true);

	bool GetBuffer(char*& _Buffer, UINT& _Size,bool _AutoSize = false);
	void ReleaseBuffer(char*& _Buffer, UINT _Size);

	void UpdatePeakInfo();
	void LogDebugInfo(DEBUG_DATA& debugData);

	DECLARE_INSTANCE(CBufManager)

private:
	bool GetBuffer(std::vector<char*>& arr, char*& _Buffer, UINT& _Size);
	void ReleaseBuffer(std::vector<char*>& arr, char*& _Buffer, UINT _Size, UINT overloevalue);
private:
	std::vector<char*>				m_send;
	std::vector<char*>				m_recv;

	map<UINT, UINT>					m_mapBusy;
	map<UINT, std::vector<char*>>	m_mapIdle;

	CMutex m_Mutex;

	uint32_t m_IdlePeak = 0;
	uint32_t m_BusyPeak = 0;
};

class CBufPoolManager
{
private:
	CBufPoolManager();
	~CBufPoolManager();
	void Init();

public:
	bool GetBuffer(char*& _Buffer, UINT& _Size, bool _AutoSize = true);
	DECLARE_INSTANCE(CBufPoolManager)

private:
	map<UINT, char*>				m_bufMap;
};
