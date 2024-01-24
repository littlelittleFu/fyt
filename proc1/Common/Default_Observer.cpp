#include "stdafx.h"
#include "Default_Observer.h"
#include <iostream>
#include "ISubject.h"
#include "ILogHelper.h"
Default_Observer::Default_Observer()
{
}

Default_Observer::~Default_Observer()
{
}

void Default_Observer::Notify(ISubject* sub)
{
	if (nullptr == sub) {
		LOG_ERROR("subject is null,exit!!");
		return;
	}

	if ((1 != this->GetNtfType().count(sub->GetNtfType()))) {
		LOG_ERROR("notify type not match,exit!!");
		return;
	}

	LOG_NORMAL("observer get notify type %d", this->GetNtfType());	
	//Âß¼­Ğ´ÔÚÕâÀï
}
