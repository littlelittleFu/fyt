#pragma once
#include"Clistener.h"
class CNetMgr
{
private:
	CNetMgr() {};
	~CNetMgr() {};
public:
	void AddListener();



private:
	CListener* m_listener;



private:
	static CNetMgr* instance;
public:
	static CNetMgr* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CNetMgr;
			return instance;
		}
		return instance;
	}
};