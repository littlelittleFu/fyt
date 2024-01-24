#pragma once

#include <string.h>
#include "ItemBase.h"

class MallItem : public ItemBase
{
	
public:
	MallItem() {};
	 ~MallItem() {};



protected:
	unsigned short			  midx = 0;
	unsigned char             mIsHot = 0;
	unsigned short            mNum = 0;
	unsigned short            mvaluetype = 0;
	unsigned short            mdiscount = 0;
	unsigned short            mprice = 0;
};


