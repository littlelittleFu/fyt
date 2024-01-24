#pragma once

#include "IProtoMgr.h"
#include "ProtoClient.h"
#include "ProtoClient2.h"
#include "ProtoClient3.h"
#include "ProtoClient7.h"
#include "ProtoSS.h"
#include "ProtoGS.h"
#include "ProtoDB.h"
#include "ProtoLS.h"
#include "ProtoMS.h"
#include "ProtoCS.h"
#include "ProtoLog.h"

class ProtoMgr : public IProtoMgr
{
public:
	ProtoMgr() {};
	~ProtoMgr() {};

public:
	virtual int EncodeMsg(void* pIn, char* pOut, uint32_t nSize) override;
	virtual int DecodeMsg(void* pIn, char* pOut, uint32_t nSize) override;

protected:
    ProtoClient mProtoClient;
    ProtoClient2 mProtoClient2;
    ProtoClient3 mProtoClient3;
    ProtoClient7 mProtoClient7;
    ProtoSS mProtoSS;
    ProtoGS mProtoGS;
    ProtoDB mProtoDB;
    ProtoLS mProtoLS;
    ProtoMS mProtoMS;
    ProtoCS mProtoCS;
    ProtoLog mProtoLog;
};
