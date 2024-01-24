#pragma once
#include <set>
#include <string>
class ISubject;
class IObserver {
public:
	IObserver();
	virtual ~IObserver();
	
	virtual void Notify(ISubject* sub) = 0;	
	std::set<uint16_t> GetNtfType(void) { return mNtfType; }
	void SetNtfType(uint16_t ntfType);
protected:
	std::set<uint16_t> mNtfType;
};



