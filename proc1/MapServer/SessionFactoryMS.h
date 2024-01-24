#pragma once
#include "SessionFactory.h"

class SessionFactoryMS : public SessionFactory
{
public:
	SessionFactoryMS();
	~SessionFactoryMS();

protected:
	ISession* DoCreateSession(INT _Type);
};
