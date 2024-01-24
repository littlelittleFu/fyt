#include "stdafx.h"
#include "SessionFactoryLog.h"
#include "SessionLOG2LS.h"
#include "SessionLOG2CS.h"
#include "SessionLOG2SS.h"
#include "SessionLOG2MS.h"
#include "SessionLog2GS.h"
#include "SessionLog2DB.h"

SessionFactoryLog::SessionFactoryLog()
{

}

SessionFactoryLog::~SessionFactoryLog()
{

}

ISession* SessionFactoryLog::DoCreateSession(int _Type)
{
	switch (_Type)
	{
	case SESSION_TYPE_LOG2SS:
		return new SessionLog2SS;
	case SESSION_TYPE_LOG2LS:
		return new SessionLog2LS;
	case SESSION_TYPE_LOG2CS:
		return new SessionLog2CS;
	case SESSION_TYPE_LOG2MS:
		return new SessionLog2MS;
	case SESSION_TYPE_LOG2GS:
		return new SessionLog2GS;
	case SESSION_TYPE_LOG2DB:
		return new SessionLog2DB;
	default:
		return nullptr;
	}
}