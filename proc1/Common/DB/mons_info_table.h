#pragma once

#include <string>
#include <map>
#include <vector>



class CsvHelper;

namespace DATA
{
	struct MonsInfo
	{
		char map_name[32];
		char KeyName[32];
		uint32_t image;
		uint32_t x;
		uint32_t y;
		char Tips[1500];
	};


	class MonsInfoConfig : public TableBase<MonsInfo>
	{
		DECLARE_SINGLETON(MonsInfoConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "map_name", row->map_name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "image", row->image, 0);
            CELL_VALUE(InRow, "x", row->x, 0);
            CELL_VALUE(InRow, "y", row->y, 0);
            CELL_VALUE(InRow, "Tips", row->Tips, 1);
		}
		virtual void FillMapping(TItem *row) override
		{
			key_name_mappings_[row->KeyName] = row;
		}
	};


#define sMonsInfoConfig (*DATA::MonsInfoConfig::Instance())
}