#include "pch.h"
#include "SessionFactory.h"


SessionFactory::SessionFactory()
{

}

SessionFactory::~SessionFactory()
{

}

ISession* SessionFactory::CreateSession(INT _Type, INT _Param)
{
	ISession* _pSession = nullptr;
	_pSession = DoCreateSession(_Type);
	if (_pSession) {
		_pSession->SetType(_Type);
		_pSession->SetParam(_Param);
	}

	return _pSession;
}

void SessionFactory::RemoveSession(ISession* _pSession)
{
	SAFE_RELEASE(_pSession);
}

ISession* SessionFactory::DoCreateSession(INT _Type)
{
	return nullptr;
}