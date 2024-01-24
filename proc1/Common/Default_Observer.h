#pragma once
#include "IObserver.h"

class Default_Observer:public IObserver
{
public:
	Default_Observer();
	~Default_Observer();
	virtual void Notify(ISubject* sub) override;
};

