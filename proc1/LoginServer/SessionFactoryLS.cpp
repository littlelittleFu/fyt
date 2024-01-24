#include "stdafx.h"
#include "SessionFactoryLS.h"
#include "SessionLS2SS.h"
#include "SessionLS2DB.h"
#include "SessionLS2CS.h"
#include "SessionLS2GS.h"
#include "SessionLS2Log.h"

SessionFactoryLS::SessionFactoryLS()
{
}

SessionFactoryLS::~SessionFactoryLS()
{

}

ISession* SessionFactoryLS::DoCreateSession(INT _Type)
{
    switch (_Type)
    {
    case SESSION_TYPE_LS2SS:
        return new SessionLS2SS;

    case SESSION_TYPE_LS2DB:
        return new SessionLS2DB;

    case SESSION_TYPE_LS2CS:
        return new SessionLS2CS;

    case SESSION_TYPE_LS2GS:
        return new SessionLS2GS;

    case SESSION_TYPE_LS2LOG:
        return new SessionLS2Log;
    default:
        return nullptr;
    }
}
