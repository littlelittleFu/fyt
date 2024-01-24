#include "stdafx.h"
#include "SessionFactoryCS.h"
#include "SessionCS2SS.h"
#include "SessionCS2DB.h"
#include "SessionCS2LS.h"
#include "SessionCS2MS.h"
#include "SessionCS2GS.h"
#include "SessionCS2Log.h"

SessionFactoryCS::SessionFactoryCS()
{

}

SessionFactoryCS::~SessionFactoryCS()
{

}

ISession* SessionFactoryCS::DoCreateSession(int _Type)
{
	switch (_Type)
	{
	case SESSION_TYPE_CS2SS:
		return new SessionCS2SS;
	case SESSION_TYPE_CS2DB:
		return new SessionCS2DB;
	case SESSION_TYPE_CS2LS:
		return new SessionCS2LS;
	case SESSION_TYPE_CS2MS:
		return new SessionCS2MS;
    case SESSION_TYPE_CS2GS:
        return new SessionCS2GS;
	case SESSION_TYPE_CS2LOG:
		return new SessionCS2Log;
	default:
		return nullptr;
	}
}
