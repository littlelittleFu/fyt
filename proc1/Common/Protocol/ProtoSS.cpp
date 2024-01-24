#include "stdafx.h"
#include "ProtoSS.h"


ProtoSS::ProtoSS()
{
}

ProtoSS::~ProtoSS()
{

}

int ProtoSS::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
	unsigned short moduleid = *(unsigned short*)pHost;
	unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
	if (moduleid != GetModuleID()) {
		return -1;
	}
	if (protoid >= PROTO_CONFIG_MAX) {
		return -1;
	}

	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);
	return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoSS::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
	unsigned short moduleid = *(unsigned short*)pNet;
	unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
	if (moduleid != GetModuleID()) {
		return -1;
	}
	if (protoid >= PROTO_CONFIG_MAX) {
		return -1;
	}

	CNetData m_oData;
	m_oData.Prepare((char *)pNet, iNetSize);
	return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}