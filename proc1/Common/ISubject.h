#pragma once
#include <vector>
#include "IObserver.h"
#include <map>

class ISubject
{
public:
	ISubject();
	virtual ~ISubject();
	virtual void Register(IObserver*) ;
	virtual void UnRegister(IObserver*) ;
	virtual void Notify(uint16_t type);
	uint16_t GetNtfType(void) { return mNtfType; };
	void SetNtfType(uint16_t ntfType) { mNtfType = ntfType; };
protected:
	uint16_t mNtfType;
	std::vector<IObserver*> mObservers;
};

