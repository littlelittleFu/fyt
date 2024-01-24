#include "pch.h"
#include "ISessionFactory.h"

ISessionFactory* ISessionFactory::m_Instance = NULL;

ISessionFactory::ISessionFactory()
{
	
}

ISessionFactory::~ISessionFactory()
{

}

void ISessionFactory::SetInstance(ISessionFactory* _pInstance)
{
	m_Instance = _pInstance;
}

ISessionFactory* ISessionFactory::GetInstance()
{
	return m_Instance;
}

ISession* ISessionFactory::CreateSession(INT _Type,INT _Param)
{
	return NULL;
}

void ISessionFactory::RemoveSession(ISession* _pSession)
{

}