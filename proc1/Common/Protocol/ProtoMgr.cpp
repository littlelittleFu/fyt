#include "stdafx.h"
#include "ProtoMgr.h"
#include "ProtoDef.h"


int ProtoMgr::EncodeMsg(void* pIn, char* pOut, uint32_t nSize)
{
    if (!pIn || !pOut || nSize == 0) return -1;

	uint16_t moduleid = *(uint16_t*)pIn;
    switch (moduleid)
    {
    case MODULE_TYPE_CLIENT:
        return mProtoClient.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CLIENT2:
        return mProtoClient2.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CLIENT3:
        return mProtoClient3.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CLIENT7:
        return mProtoClient7.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_SS:
        return mProtoSS.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_GS:
        return mProtoGS.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_DB:
        return mProtoDB.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_LS:
        return mProtoLS.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_MS:
        return mProtoMS.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CS:
        return mProtoCS.BuildProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_LOG:
        return mProtoLog.BuildProtocol(pIn, pOut, nSize);
    default:
        return -1;
    }
}

int ProtoMgr::DecodeMsg(void* pIn, char* pOut, uint32_t nSize)
{
    if (!pIn || !pOut || nSize == 0) return -1;

	uint16_t moduleid = *(uint16_t*)pIn;
    switch (moduleid)
    {
    case MODULE_TYPE_CLIENT:
        return mProtoClient.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CLIENT2:
        return mProtoClient2.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CLIENT3:
        return mProtoClient3.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CLIENT7:
        return mProtoClient7.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_SS:
        return mProtoSS.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_GS:
        return mProtoGS.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_DB:
        return mProtoDB.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_LS:
        return mProtoLS.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_MS:
        return mProtoMS.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_CS:
        return mProtoCS.HandleProtocol(pIn, pOut, nSize);

    case MODULE_TYPE_LOG:
        return mProtoLog.HandleProtocol(pIn, pOut, nSize);
    default:
        return -1;
    }
}