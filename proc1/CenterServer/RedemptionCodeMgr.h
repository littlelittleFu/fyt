#pragma once
#include "ProtoCS.h"
class RedemptionCodeMgr
{
public:

	RedemptionCodeMgr() = delete;
	~RedemptionCodeMgr() = delete;

	static void SendToPlatform(const RedemptionCodeInfo& info);
	static bool ComposeHttpRequest(const RedemptionCodeInfo& info, char* buf, int bufsz);
	static bool ParseResult(ProtoCS_ActivationCodeAck& ack,const char* raw, uint16_t type);
	static size_t CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp);

};