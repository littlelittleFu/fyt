#pragma once

#include "Session.h"

class SessionCS2SS : public Session
{
public:
    SessionCS2SS();
    ~SessionCS2SS();

    virtual void OnEstablish(SOCKET _Socket);
    virtual void OnLost();
    virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
    virtual void OnError(DWORD _ErrorCode);
    virtual void OnUpdate(UINT _Delta);
    virtual void DoHeartBeat();

private:
    void HandleCenterServMsg(uint16_t protoid, void *pData);
    void HandleCenterServMsg_HeartBeatAck(void *pData);
    void HandleCenterServMsg_ConfigAck(void *pData);

    void UploadConfigToServiceServer();
    void RequestServerConfig();
    bool HasGetConfigFromSS();
};
