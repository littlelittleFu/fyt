#include"CNetMgr.h"
CNetMgr* CNetMgr::instance = nullptr;

void CNetMgr::AddListener()
{
	m_listener->AddListener();
}
