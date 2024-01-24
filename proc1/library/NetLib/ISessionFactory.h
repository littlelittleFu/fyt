#pragma once

#include "ISession.h"

enum
{
	SESSION_TYPE_NULL = 0,
	//SS SERVER
	SESSION_TYPE_SS2DB,
	SESSION_TYPE_SS2CS,
	SESSION_TYPE_SS2LS,
	SESSION_TYPE_SS2MS,
	SESSION_TYPE_SS2GS,
	SESSION_TYPE_SS2LOG,

	//DB SERVER
	SESSION_TYPE_DB2SS,
	SESSION_TYPE_DB2CS,
	SESSION_TYPE_DB2LS,
	SESSION_TYPE_DB2LOG,

	//CENTER SERVER
	SESSION_TYPE_CS2SS,
	SESSION_TYPE_CS2DB,
	SESSION_TYPE_CS2LS,
	SESSION_TYPE_CS2MS,
	SESSION_TYPE_CS2GS,
	SESSION_TYPE_CS2LOG,

	//LOGIN SERVER
	SESSION_TYPE_LS2SS,
	SESSION_TYPE_LS2DB,
	SESSION_TYPE_LS2CS,
	SESSION_TYPE_LS2GS,
	SESSION_TYPE_LS2LOG,

	//MAP SERVER
	SESSION_TYPE_MS2SS,
	SESSION_TYPE_MS2DB,
	SESSION_TYPE_MS2CS,
	SESSION_TYPE_MS2GS,
	SESSION_TYPE_MS2LOG,

	//GATE SERVER
	SESSION_TYPE_GS2CL,
	SESSION_TYPE_GS2SS,
	SESSION_TYPE_GS2CS,
	SESSION_TYPE_GS2LS,
	SESSION_TYPE_GS2MS,
	SESSION_TYPE_GS2LOG,

	//GAME CLIENT
	SESSION_TYPE_CL2GS,

	//LOG SERVER
	SESSION_TYPE_LOG2SS,
	SESSION_TYPE_LOG2CS,
	SESSION_TYPE_LOG2GS,
	SESSION_TYPE_LOG2LS,
	SESSION_TYPE_LOG2MS,
	SESSION_TYPE_LOG2DB,

	// ����
	SESSION_TYPE_COUNT,
};

class ISessionFactory
{
protected:
	ISessionFactory();
	virtual ~ISessionFactory();

public:
	static void SetInstance(ISessionFactory* _pInstance);
	static ISessionFactory* GetInstance();
	virtual ISession* CreateSession(INT _Type, INT _Param);
	virtual void RemoveSession(ISession* _pSession);

private:
	static ISessionFactory* m_Instance;
};
