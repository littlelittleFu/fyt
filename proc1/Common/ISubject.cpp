#include "stdafx.h"
#include "ISubject.h"
#include <iostream>


ISubject::ISubject():mNtfType(0)
{
}

ISubject::~ISubject()
{
	
}

void ISubject::Register(IObserver*obr)
{
	mObservers.push_back(obr);
}

void ISubject::UnRegister(IObserver*obr)
{
	if (mObservers.empty()) {
		return;
	}

	for (auto it = mObservers.begin(); it != mObservers.end(); ++it) {
		if ((*it) == obr) {
			mObservers.erase(it);
			break;
		}
	}
}

void ISubject::Notify(uint16_t type)
{
	
	if (mObservers.empty()) {
		return;
	}

	this->SetNtfType(type);

	uint16_t item = GetNtfType();
	auto &vec = mObservers;
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (nullptr != (*it)) {
			(*it)->Notify(this);//the notify is observer func
		}
	}
}
