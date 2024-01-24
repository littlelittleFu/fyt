#pragma once
#include <string>
#include <map>
#include <vector>
#define JUMP_SPECIAL 28721


class CsvHelper;

namespace DATA
{
	struct Jump
	{
		char from_map[144];
		uint32_t from_left;
		uint32_t from_top;
		uint32_t from_width;
		uint32_t from_height;

		char to_map[144];
		uint32_t to_left;
		uint32_t to_top;
		uint32_t to_width;
		uint32_t to_height;

		uint32_t jump_pic;    // Ìø×ªÇøÓÃ
		uint32_t ShowEffect;
		uint8_t NotShowPathFindingPoint;
		Jump():from_left(0),from_top(0),from_width(0),from_height(0),to_left(0),to_top(0),to_width(0),to_height(0),
			jump_pic(JUMP_SPECIAL),ShowEffect(1),NotShowPathFindingPoint(0) {
			std::memset(from_map, 0, sizeof(from_map));
		}
	};


	class JumpConfig : public TableBase<Jump>
	{
		DECLARE_SINGLETON(JumpConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "from_map", row->from_map, 1);
            CELL_VALUE(InRow, "from_left", row->from_left, 0);
            CELL_VALUE(InRow, "from_top", row->from_top, 0);
            CELL_VALUE(InRow, "from_width", row->from_width, 0);
            CELL_VALUE(InRow, "from_height", row->from_height, 0);
            CELL_VALUE(InRow, "to_map", row->to_map, 1);
            CELL_VALUE(InRow, "to_left", row->to_left, 0);
            CELL_VALUE(InRow, "to_top", row->to_top, 0);
            CELL_VALUE(InRow, "to_width", row->to_width, 0);
            CELL_VALUE(InRow, "to_height", row->to_height, 0);
            CELL_VALUE(InRow, "jump_pic", row->jump_pic, 0);
            CELL_VALUE(InRow, "ShowEffect", row->ShowEffect, 0);
            CELL_VALUE(InRow, "NotShowPathFindingPoint", row->NotShowPathFindingPoint, 0);
        }
		virtual bool CheckValid(TItem *row) override
		{
			if (row->from_map[0] == 0 || row->to_map[0] == 0) return false;
			return true;
		}
		virtual void FillMapping(TItem *row) override
        {
            std::string _KeyName = std::string(row->from_map) + "_" + std::string(row->to_map)+"_"+std::to_string(row->from_left)+"_"+std::to_string(row->from_top);
            key_name_mappings_[_KeyName] = row;

	/*		TKeyNameMappingTRows* t0 = &key_name_mappings_rows;

			std::string _KeyName = std::string(row->from_map) + "_" + std::string(row->to_map);
			if (t0->find(_KeyName) == t0->end())
				(*t0)[_KeyName] = new TRows();
			TRows*& t1 = (*t0)[_KeyName];

			t1->push_back(row);*/
        }
	};


#define sJumpConfig (*DATA::JumpConfig::Instance())
}