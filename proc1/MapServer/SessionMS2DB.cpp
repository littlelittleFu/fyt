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

//pdata Ϊ��װ�����ݣ���Ҫ�������ȥʵ��,���ܵ�����Ϣ
void SessionMS2DB::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

	if (nullptr == _pData) {
		return;
	}
	
	//�� DB SERVER ��������Ϣ�Ĵ������������
}

void SessionMS2DB::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionDB2MS ERROR %ld", _ErrorCode);
}

//���ջش���ʱ��ġ�������������
void SessionMS2DB::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}
void SessionMS2DB::DoHeartBeat()
{
    ProtoMS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}
