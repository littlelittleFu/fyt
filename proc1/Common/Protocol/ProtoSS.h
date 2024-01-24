#pragma once
#include "ProtoDef.h"
enum
{
	PROTO_CONFIG_MAX = 1,
};

class ProtoSS
{
public:
	ProtoSS();
	~ProtoSS();

	static inline uint16_t GetModuleID(void) { return MODULE_TYPE_SS; }
	static inline uint16_t GetProtocolNum(void) { return PROTO_CONFIG_MAX; }

	int BuildProtocol(void* pHost, char* pNet, int iNetSize);
	int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
	EnCodeFunc m_EnCodeFuncArray[PROTO_CONFIG_MAX];
	DeCodeFunc m_DeCodeFuncArray[PROTO_CONFIG_MAX];
};
