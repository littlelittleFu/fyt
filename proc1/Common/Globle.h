#pragma once
#include <iostream>
#include <tuple>
#include <typeinfo>

#include "EventTrigger.h"

class Globle : public EventTrigger
{
	DECL_SINGLETON(Globle)
public:
	
	void Update(int delta);
};
