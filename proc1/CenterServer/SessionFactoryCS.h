#pragma once

#include "SessionFactory.h"

class SessionFactoryCS : public SessionFactory
{
public:
	SessionFactoryCS();
	~SessionFactoryCS();

protected:
	ISession* DoCreateSession(int _Type);
};
