#pragma once
#include "ISessionFactory.h"

class SessionFactory : public ISessionFactory
{
public:
	SessionFactory();
	virtual ~SessionFactory();

	ISession* CreateSession(INT _Type, INT _Param);
	virtual void RemoveSession(ISession* _pSession);

protected:
	virtual ISession* DoCreateSession(INT _Type);
};
