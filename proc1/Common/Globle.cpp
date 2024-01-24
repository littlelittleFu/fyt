#include "stdafx.h"
#include "Globle.h"
#include <DB/role_table.hpp>


IMPL_SINGLETON(Globle)
void Globle::Update(int delta)
{
	UpdateEventMap();
}