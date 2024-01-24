#include "stdafx.h"
#include "SessionFactoryGS.h"
#include "SessionGS2SS.h"
#include "SessionGS2CS.h"
#include "SessionGS2LS.h"
#include "SessionGS2MS.h"
#include "SessionGS2CL.h"
#include "SessionGS2Log.h"

SessionFactoryGS::SessionFactoryGS()
{

}

SessionFactoryGS::~SessionFactoryGS()
{

}

ISession* SessionFactoryGS::DoCreateSession(int _Type)
{
	switch (_Type)
	{
	case SESSION_TYPE_GS2SS:
		return new SessionGS2SS;

	case SESSION_TYPE_GS2CS:
		return new SessionGS2CS;

	case SESSION_TYPE_GS2LS:
		return new SessionGS2LS;

	case SESSION_TYPE_GS2MS:
		return new SessionGS2MS;

	case SESSION_TYPE_GS2CL:
		return new SessionGS2CL;

	case SESSION_TYPE_GS2LOG:
		return new SessionGS2Log;
	default:
		return nullptr;
	}
}
