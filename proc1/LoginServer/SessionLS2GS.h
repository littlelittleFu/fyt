#pragma once
#include "Session.h"
#include "SessionContextMgr.h"

struct ProtoGS_LoginReq;
struct ProtoGS_LogoutReq;
struct ProtoLS_LoginAck;

class SessionLS2GS : public Session
{
public:
    SessionLS2GS();
	~SessionLS2GS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

    void HandleDBServMsg_LoginAck(ProtoLS_LoginAck* pLoginAck);       // SessionDB -> SessionLS2GS

    void HandleThirdPartLoginResult(SPSessionContext context);

private:
    void HandleGateServMsg(uint16_t protoid, void* pData);
    void HandleGateServMsg_HeartBeatReq(void *pData);
    void HandleGateServMsg_LoginReq(void *pData);
    void HandleGateServMsg_ThirdLoginReq(void *pData);
    void HandleGateServMsg_LogoutReq(void *pData);
    void HandleGateServMsg_ReloginReq(void* pData);
    void HandleGateServMsg_UpdateOnlineState(void *pData);
    void HandleGateServMsg_SetMaintenanceStatus(void* pData);
    void HandleGateServMsg_KickOutByLock(void* pData);

    bool SendLoginReqToDB(ProtoGS_LoginReq* req,uint8_t isThirdLogin = 0);

    bool SendSaveLoginReqToCS(SPSessionContext &spSessionContext, uint8_t saveProhibitChat = 0, int64_t isProhibitChat = 0,
                    uint8_t saveSupport = 0, uint8_t isSupport = 0);
    bool SendLogoutNtfToGS(SPSessionContext &spContext);
    bool SendLogoutReqToCS(ProtoGS_LogoutReq* pLogoutReq);
    void SendKickRoleNtf(uint32_t gssess, uint32_t clsess, uint64_t roleguid, int32_t errorcode, const char* errmsg);
    void SendInsertPlayerToDB(uint64_t playerid, const char *username);
    void SendLogoutReqToCS(uint32_t session, uint32_t token, uint8_t info = 0);
    void HandleGateServMsg_SaveKeyNtf(void* pData);
    void SendRemoveContextToGS(uint32_t nGSSessionID, uint32_t nClientSessionID);

    void SendLoginAckToGS(uint32_t clsessid, int32_t errcode, const char *errmsg = nullptr, const char *username = nullptr,
        uint64_t userid = 0, uint32_t token = 0, const char *randkey = nullptr);

    void SendReloginAckToGS(uint32_t nClientSessionID, int32_t nErrCode, const char *pErrMsg,
        const char *pUserName = nullptr, const char *pPassword = nullptr, uint64_t nPlayerGUID = 0,
        uint64_t nRoleGUID = 0, uint32_t nToken = 0, const char *pRandKey = nullptr);
};
