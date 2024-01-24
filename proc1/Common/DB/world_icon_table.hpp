/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct WorldIcon
	{
		uint32_t      Id;                          /// 索引号
		char        KeyName[32];                 /// 地图索引名
		uint32_t      Icon;                        /// 图片编号
		char        BtnName[32];                 /// 按钮名称
		uint32_t      PosX;                        /// 坐标X
		uint32_t      PosY;                        /// 坐标Y
	};


	class WorldIconConfig  : public TableBase<WorldIcon>
	{
		DECLARE_SINGLETON(WorldIconConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "BtnName", row->BtnName, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
            CELL_VALUE(InRow, "PosX", row->PosX, 0);
            CELL_VALUE(InRow, "PosY", row->PosY, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = 0;
            TItem *&t1 = (*t0)[row->Id];
            t1 = row;
            key_name_mappings_[row->KeyName] = row;
        }
	};


#define sWorldIconConfig (*DATA::WorldIconConfig::Instance())
}