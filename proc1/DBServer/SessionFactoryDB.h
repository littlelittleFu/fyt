#pragma once
#include "SessionFactory.h"

class SessionFactoryDB : public SessionFactory
{
public:
	SessionFactoryDB();
	~SessionFactoryDB();
protected:
	ISession* DoCreateSession(int _Type);
};
