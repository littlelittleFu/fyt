#pragma once
#include "SessionFactory.h"

class SessionFactoryGS : public SessionFactory
{
public:
	SessionFactoryGS();
	~SessionFactoryGS();
protected:
	ISession* DoCreateSession(int _Type);
};
