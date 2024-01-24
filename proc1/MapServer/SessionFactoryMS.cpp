#include "stdafx.h"
#include "SessionFactoryMS.h"
#include "SessionMS2SS.h"
#include "SessionMS2DB.h"
#include "SessionMS2CS.h"
#include "SessionMS2GS.h"
#include "SessionMS2Log.h"


SessionFactoryMS::SessionFactoryMS()
{

}

SessionFactoryMS::~SessionFactoryMS()
{

}

ISession* SessionFactoryMS::DoCreateSession(INT _Type)
{
    switch (_Type)
    {
    case SESSION_TYPE_MS2SS:
        return new SessionMS2SS;

    case SESSION_TYPE_MS2DB:
        return new SessionMS2DB;

    case SESSION_TYPE_MS2GS:
        return new SessionMS2GS;

    case SESSION_TYPE_MS2CS:
        return new SessionMS2CS;

    case SESSION_TYPE_MS2LOG:
        return new SessionMS2Log;

    default:
        return nullptr;
    }
}
