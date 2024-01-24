#pragma once
#include "SessionFactory.h"

class SessionFactoryLS :public SessionFactory
{
public:
    SessionFactoryLS();
	~SessionFactoryLS();

protected:
	virtual ISession* DoCreateSession(INT _Type);
};
