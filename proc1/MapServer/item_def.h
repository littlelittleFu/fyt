#pragma once
#include "logic_def.hpp"



struct item
{
	uint16_t      Id;
	char          Name[32];                    /// ��Ʒ����
	char          KeyName[32];                 /// �������� ���ܺ���Ʒ������ͬ
	item_type     MajorType;					/// ������                      
	uint8_t       SubType;                     /// �����ͣ�������̫�࣬���ﲻҪ��ö�ٱ�ʾ��ֱ���û������ͱ�ʾ���ɣ�
	item_attr     ItemAttr;					   ///��Ʒ����
	item_quality  Quality;                      ///��ƷƷ��
};