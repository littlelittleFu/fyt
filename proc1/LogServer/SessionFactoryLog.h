#pragma once
#include "SessionFactory.h"

class SessionFactoryLog : public SessionFactory
{
public:
	SessionFactoryLog();
	~SessionFactoryLog();
protected:
	ISession* DoCreateSession(int _Type);
};
