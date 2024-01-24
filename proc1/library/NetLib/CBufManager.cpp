#include "pch.h"
#include "CBufManager.h"
#include "Config.h"

#define ADD_SIZE	64
#define ADD_SIZE2	1024
#define POOL_ADD_SIZE	65536
#define DEFAULT_OVERLODE_VAL	10000
#define SR_DEFAULT_OVERLODE_VAL	32
#define BLOCK_DEFAULT_COUNT		16
#define POOLBLOCK_DEFAULT_COUNT	4

IMPLEMENT_INSTANCE(CBufManager)

CBufManager::CBufManager()
{
	Init();
}

CBufManager::~CBufManager()
{

}

void CBufManager::Init()
{
	/*char* Buffer = NULL;
	for (uint16_t i = 1; i <= BLOCK_DEFAULT_COUNT; ++i)
	{
		UINT blockSize = i * ADD_SIZE;
		for (uint16_t j = 0; j < 32; ++j)
		{
			Buffer = new char[blockSize];
			m_mapIdle[blockSize].push_back(Buffer);
		}
		m_mapBusy[blockSize] = 0;
	}*/
	/*
	// Ì«Õ¼ÄÚ´æ
	UINT sBlockSize = g_SendBufSize;
	UINT rBlockSize = g_RecvBufSize;
	for (uint16_t i = 0; i < SR_DEFAULT_OVERLODE_VAL / 4; ++i)
	{
		Buffer = new char[sBlockSize];
		m_send.push_back(Buffer);
		Buffer = new char[rBlockSize];
		m_recv.push_back(Buffer);
	}
	*/
}

void CBufManager::OnUpdate(INT _Delta)
{
	UpdatePeakInfo();
}

bool CBufManager::GetSendOrRecvBuffer(char*& _Buffer, UINT& _Size, bool beSend)
{
	return  beSend ? GetBuffer(m_send, _Buffer, _Size) : GetBuffer(m_recv, _Buffer, _Size);
}

void CBufManager::ReleaseSendOrRecvBuffer(char*& _Buffer, UINT& _Size, bool beSend)
{
	beSend ? ReleaseBuffer(m_send, _Buffer, _Size, SR_DEFAULT_OVERLODE_VAL) : ReleaseBuffer(m_recv, _Buffer, _Size, SR_DEFAULT_OVERLODE_VAL);
}

bool CBufManager::GetBuffer(char*& _Buffer, UINT& _Size, bool _AutoSize)
{
	if (_AutoSize) {
		if (_Size < ADD_SIZE2)
		{
			_Size = _Size / ADD_SIZE * ADD_SIZE + ADD_SIZE;
		}
		else
		{
			_Size = _Size / ADD_SIZE2 * ADD_SIZE2 + ADD_SIZE2;
		}
	}

	if (_Size > 0) {
		m_Mutex.Lock();
		auto& busy = m_mapBusy[_Size];
		auto& idle = m_mapIdle[_Size];
		GetBuffer(idle, _Buffer, _Size);
		busy < UINT32_MAX ? ++ busy : 1;
		m_Mutex.Unlock();
	}

	return _Buffer != nullptr;
}

bool CBufManager::GetBuffer(std::vector<char*>& arr, char*& _Buffer, UINT& _Size)
{
	if (arr.size() > 0)
	{
		_Buffer = arr.back();
		arr.pop_back();
	}
	else
	{
		_Buffer = new char[_Size];
	}
	return _Buffer != nullptr;
}

void CBufManager::ReleaseBuffer(char*& _Buffer, UINT _Size)
{
	if ((NULL != _Buffer) && (_Size > 0)) {
		m_Mutex.Lock();
		auto _Iter = m_mapBusy.find(_Size);
		if (_Iter != m_mapBusy.end()) {
			_Iter->second > 0 ? -- _Iter->second : 1;
		}

		ReleaseBuffer(m_mapIdle[_Size], _Buffer, _Size, DEFAULT_OVERLODE_VAL);
		m_Mutex.Unlock();
	}
}

void CBufManager::ReleaseBuffer(std::vector<char*>& arr, char*& _Buffer, UINT _Size, UINT overlodeValue)
{
    if (_Buffer == nullptr) return;
	if (arr.size() >= overlodeValue) {
		delete [] _Buffer;
		_Buffer = NULL;
	}
	else {
		arr.push_back(_Buffer);
	}
}

void CBufManager::UpdatePeakInfo()
{
	if (!g_LogLevel) return;

	uint32_t idlePeak = 0;
	uint32_t busyPeak = 0;
	m_Mutex.Lock();
	for (auto &it : m_mapIdle) {
		idlePeak += it.second.size();
	}
	for (auto &it : m_mapBusy) {
		busyPeak += it.second;
	}
	m_Mutex.Unlock();

	if (m_IdlePeak < idlePeak) m_IdlePeak = idlePeak;
	if (m_BusyPeak < busyPeak) m_BusyPeak = busyPeak;
}
void CBufManager::LogDebugInfo(DEBUG_DATA& debugData)
{
	m_Mutex.Lock();
	for (auto &it : m_mapIdle) {
		debugData.buffIdleCache += it.second.size();
		debugData.buffIdleMem += it.first * it.second.size();
	}
	for (auto &it : m_mapBusy) {
		debugData.buffBusyCache += it.second;
		debugData.buffBusyMem += it.first * it.second;
	}
	m_Mutex.Unlock();

	debugData.buffIdlePeak = m_IdlePeak;
	debugData.buffBusyPeak = m_BusyPeak;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_INSTANCE(CBufPoolManager)
CBufPoolManager::CBufPoolManager()
{
	Init();
}

CBufPoolManager::~CBufPoolManager()
{
	auto iter = m_bufMap.begin();
	for (; iter != m_bufMap.end(); ++iter)
	{
		SAFE_RELEASE(iter->second);
	}
	m_bufMap.clear();
}

void CBufPoolManager::Init()
{
	for (uint16_t i = 1; i <= POOLBLOCK_DEFAULT_COUNT; ++i)
	{
		UINT blockSize = i * POOL_ADD_SIZE;
		m_bufMap[blockSize] = new char[blockSize];
	}
}

bool CBufPoolManager::GetBuffer(char*& _Buffer, UINT& _Size, bool _AutoSize)
{
	if (_AutoSize) {
		if ((_Size % POOL_ADD_SIZE) > 0) {
			_Size = _Size / POOL_ADD_SIZE * POOL_ADD_SIZE + POOL_ADD_SIZE;
		}
	}

	if (_Size > 0) 
	{
		auto iter = m_bufMap.find(_Size);
		if (iter != m_bufMap.end())
		{
			_Buffer = iter->second;
		}
		else
		{
			_Buffer = new char[_Size];
			m_bufMap[_Size] = _Buffer;
		}
	}

	return _Buffer != nullptr;
}
