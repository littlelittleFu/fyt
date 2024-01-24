#include "stdafx.h"
#include "Default_Subject.h"
#include <iostream>
#include "ILogHelper.h"

Default_Subject::Default_Subject()
{
}

Default_Subject::~Default_Subject()
{
}

#if 0
void Default_Subject::Register(IObserver* obs)
{
	if (nullptr == obs) {
		return;
	}

	auto ntfType = this->GetNtfType();
	if (mObservers.count(ntfType) > 0) {
		mObservers[ntfType].push_back(obs);
	}
	else {
		mObservers.emplace(ntfType, std::vector<IObserver*>{obs});
	}
}


void Default_Subject::UnRegister(IObserver* obs)//id is obs attr!
{
	if (nullptr == obs) {
		return;
	}

	if (mObservers.empty()) {
		return;
	}

	auto ntfType = this->GetNtfType();
	if (mObservers.count(ntfType) <= 0) {
		return;
	}
	
	auto ans = mObservers[ntfType];
	for (auto it = ans.begin(); it != ans.end(); ++it) {
		if ((*it) == obs) {
			ans.erase(it);
			break;
		}
	}
}

void Default_Subject::Notify(ISubject*sub)
{
	if (nullptr == sub) {
		return;
	}

	if (mObservers.empty()) {
		return;
	}

	uint16_t item = GetNtfType();
	auto vec = mObservers[item];
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (nullptr != (*it)) {
			(*it)->Notify(this);//the notify is observer func
		}
	}
}
#endif