#pragma once
#include "logic_def.hpp"



struct item
{
	uint16_t      Id;
	char          Name[32];                    /// 物品名称
	char          KeyName[32];                 /// 索引名称 可能和物品名称相同
	item_type     MajorType;					/// 主类型                      
	uint8_t       SubType;                     /// 子类型，子类型太多，这里不要用枚举表示，直接用基本类型表示即可！
	item_attr     ItemAttr;					   ///物品属性
	item_quality  Quality;                      ///物品品质
};