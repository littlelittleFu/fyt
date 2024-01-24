#pragma once

#include <string>
#include <map>
#include <vector>



class CsvHelper;
namespace DATA
{
	struct NpcGen
	{
		uint32_t x;										//������x
		uint32_t y;										//������y
		char KeyName[32];								//������
		char map_name[32];								//��ͼ��
		uint32_t direction;								//����
		uint32_t r;										//��ʱ����
		uint32_t AddToMap;								//�Ƿ���ʾ�ڵ�ͼUI�����ϣ��ͻ�����
		uint32_t color;									//��ɫ���ͻ�����
	};


	class NpcGenConfig  : public TableBase<NpcGen>
	{
		DECLARE_SINGLETON(NpcGenConfig);
	public:
		void FillData(TItem *row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "x", row->x, 0);
            CELL_VALUE(InRow, "y", row->y, 0);
            CELL_VALUE(InRow, "map_name", row->map_name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "direction", row->direction, 0);
            CELL_VALUE(InRow, "r", row->r, 0);
            CELL_VALUE(InRow, "AddToMap", row->AddToMap, 0);
            CELL_VALUE(InRow, "color", row->color, 0);
		}
		virtual bool CheckValid(TItem *row) override
		{
			if (row->KeyName[0] == 0) return false;
			return true;
		}
		virtual void FillMapping(TItem *row) override
		{
			key_name_mappings_[row->KeyName] = row;
		}
	};


#define sNpcGenConfig (*DATA::NpcGenConfig::Instance())
}