#pragma once
#include <cstdint>

class IProtoMgr
{
public:
	static void SetInstance(IProtoMgr* inst) { m_instance = inst; };
	static IProtoMgr* GetInstance() { return m_instance; };

public:
	virtual int EncodeMsg(void* pIn, char* pOut, uint32_t nSize) = 0;
	virtual int DecodeMsg(void* pIn, char* pOut, uint32_t nSize) = 0;

private:
	static IProtoMgr* m_instance;
};