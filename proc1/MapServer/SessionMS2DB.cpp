#include "stdafx.h"
#include "SessionMS2DB.h"
#include "ILogHelper.h"
#include <string>
#include "ProtoSS.h"
#include "ProtoMS.h"
#include "SessionManager.h"
#include "SessionFactory.h"

SessionMS2DB::SessionMS2DB()
{

}

SessionMS2DB::~SessionMS2DB()
{

}
void SessionMS2DB::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
}

void SessionMS2DB::OnLost()
{
	Session::OnLost();
	LOG_WARN("SessionDB2MS SESSION LOST!");
}

//pdata 为封装的数据，需要按照这个去实现,接受到的消息
void SessionMS2DB::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

	if (nullptr == _pData) {
		return;
	}
	
	//和 DB SERVER 交互的消息的处理，后续待设计
}

void SessionMS2DB::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionDB2MS ERROR %ld", _ErrorCode);
}

//按照回传的时间δ。进行心跳保活
void SessionMS2DB::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}
void SessionMS2DB::DoHeartBeat()
{
    ProtoMS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}
