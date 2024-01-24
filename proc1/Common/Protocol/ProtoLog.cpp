#include "stdafx.h"
#include "ProtoLog.h"

static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoLog_HeartBeatReq);
	END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoLog_HeartBeatReq);
	END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoLog_HeartBeatAck);
	END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoLog_HeartBeatAck);
	END_DECODE();
}

static int EncodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoLog_UploadConfigReq);
	ENCODE_DWORD(ip);
	ENCODE_DWORD(port);
	END_ENCODE();
}

static int DecodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoLog_UploadConfigReq);
	DECODE_DWORD(ip);
	DECODE_DWORD(port);
	END_DECODE();
}

static int EncodeLoggingReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoLog_LoggingReq);
	ENCODE_STRING(serverIp);
	ENCODE_WORD(serverPort);
	ENCODE_WORD(serverType);
	ENCODE_DWORD(serverId);
	ENCODE_WORD(logType);
	ENCODE_QWORD(timestamp);
	ENCODE_WORD(logLength);
	ENCODE_FIXSTRING(logContent, logLength);
	END_ENCODE();
}

static int DecodeLoggingReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoLog_LoggingReq);
	DECODE_STRING(serverIp);
	DECODE_WORD(serverPort);
	DECODE_WORD(serverType);
	DECODE_DWORD(serverId);
	DECODE_WORD(logType);
	DECODE_QWORD(timestamp);
	DECODE_WORD(logLength);
	DECODE_FIXSTRING(logContent);
	END_DECODE();
}

ProtoLog::ProtoLog()
{
	SET_ENCODER_DECODER(PROTO_LOG_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
	SET_ENCODER_DECODER(PROTO_LOG_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
	SET_ENCODER_DECODER(PROTO_LOG_UPLOAD_CONFIG_REQ, EncodeUploadConfigReq, DecodeUploadConfigReq);
	SET_ENCODER_DECODER(PROTO_LOG_LOGGING_REQ, EncodeLoggingReq, DecodeLoggingReq);
}

ProtoLog::~ProtoLog()
{

}

int ProtoLog::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
	unsigned short moduleid = *(unsigned short*)pHost;
	unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
	if (moduleid != GetModuleID()) {
		return -1;
	}
	if (protoid >= PROTO_LOG_MAX) {
		return -1;
	}

	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);
	return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoLog::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
	unsigned short moduleid = *(unsigned short*)pNet;
	unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
	if (moduleid != GetModuleID()) {
		return -1;
	}
	if (protoid >= PROTO_LOG_MAX) {
		return -1;
	}

	CNetData m_oData;
	m_oData.Prepare((char *)pNet, iNetSize);
	return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}