#pragma once
#include "ISubject.h"
#include <string>

class Default_Subject:public ISubject
{
public:
	Default_Subject();
	~Default_Subject();
	//virtual void Register(IObserver*) override;
	//virtual void UnRegister(IObserver*) override;
	//virtual void Notify(uint16_t ) override;

};

