#include "stdafx.h"
#include <iostream>
#include "IObserver.h"
#include "ISubject.h"

IObserver::IObserver() :mNtfType({0})
{
	
}

IObserver::~IObserver()
{

}

void IObserver::SetNtfType(uint16_t ntfType)
{
	if (mNtfType.empty()) {
		mNtfType.emplace(ntfType);
	}
	else {
		if (mNtfType.count(ntfType)) {
			return;
		}
		mNtfType.emplace(ntfType);
	}
}