#include "stdafx.h"
#include "SessionFactoryDB.h"
#include "SessionDB2LS.h"
#include "SessionDB2CS.h"
#include "SessionDB2SS.h"
#include "SessionDB2Log.h"

SessionFactoryDB::SessionFactoryDB()
{

}

SessionFactoryDB::~SessionFactoryDB()
{

}

ISession* SessionFactoryDB::DoCreateSession(int _Type)
{
	switch (_Type)
	{
	case SESSION_TYPE_DB2SS:
		return new SessionDB2SS;
	case SESSION_TYPE_DB2LS:
		return new SessionDB2LS;
	case SESSION_TYPE_DB2CS:
		return new SessionDB2CS;
	case SESSION_TYPE_DB2LOG:
		return new SessionDB2Log;
	default:
		return nullptr;
	}
}