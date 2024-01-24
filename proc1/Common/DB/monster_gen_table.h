#pragma once

#include <string>
#include <map>
#include <vector>



class CsvHelper;
namespace DATA
{
	struct MonsterGen
	{
		uint16_t left;									//左
		uint16_t top;									//上
		uint16_t width;									//宽
		uint16_t height;								//高
		char KeyName[32];								//怪物KeyName
		char map_name[32];								//所在地图的名字
		uint8_t direction;								//朝向
		uint16_t number;								//怪物数量
		uint8_t is_way_finding;							//是否可寻路
		uint8_t camp;									//怪物阵营
		uint32_t color;									//颜色
		uint32_t reborn;								//死亡重生间隔
		uint32_t reborn_ex;								//
		uint32_t ContentId;								//
	};


	class MonsterGenConfig : public TableBase<MonsterGen>
	{
		DECLARE_SINGLETON(MonsterGenConfig);


	public:
		  virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "left", row->left, 0);
            CELL_VALUE(InRow, "top", row->top, 0);
            CELL_VALUE(InRow, "width", row->width, 0);
            CELL_VALUE(InRow, "height", row->height, 0);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "map_name", row->map_name, 1);
            CELL_VALUE(InRow, "direction", row->direction, 0);
            CELL_VALUE(InRow, "number", row->number, 0);
			CELL_VALUE(InRow, "is_way_finding", row->is_way_finding, 0);
		    CELL_VALUE(InRow, "camp", row->camp, 0);
		    CELL_VALUE(InRow, "color", row->color, 0);
	        CELL_VALUE(InRow, "reborn", row->reborn, 0);
	        CELL_VALUE(InRow, "reborn_ex", row->reborn_ex, 0);
		    CELL_VALUE(InRow, "ContentId", row->ContentId, 0);
        }

       	};


#define sMonsterGenConfig (*DATA::MonsterGenConfig::Instance())
}