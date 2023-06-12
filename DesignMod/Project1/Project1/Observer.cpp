#include"Observer.h"

void Secretary::Attach(StockObserverSP ob)
{
	m_colleagerList.push_back(ob);
}

void Secretary::Notify()
{
	for (StockObserverSP i : m_colleagerList)
	{
		if (i)
		{
			i->Update();
		}
		
	}
}

std::string Secretary::SecretatyAction(int _event)
{
	if (_event)
	{
		Notify();
	}
	return "";
}