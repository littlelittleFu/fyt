/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Mapicon
	{
		uint32_t      Id;                          /// 索引号
		char        KeyName[32];                 /// 地图索引名
		char        JumpName[32];                /// 跳转点名称
		uint32_t      MapX;                        /// 坐标X
		uint32_t      MapY;                        /// 坐标Y
		uint32_t	NameColor;					///跳转点名称的颜色
		uint32_t	NotKilledImg;				///怪物未击杀时的图片
		uint32_t	KilledImg;					///怪物已击杀时的图片
	};


	class MapiconConfig : public TableBase<Mapicon>
	{
		DECLARE_SINGLETON(MapiconConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "JumpName", row->JumpName, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "MapX", row->MapX, 0);
            CELL_VALUE(InRow, "MapY", row->MapY, 0);
            CELL_VALUE(InRow, "NameColor", row->NameColor, 0);
            CELL_VALUE(InRow, "NotKilledImg", row->NotKilledImg, 0);
            CELL_VALUE(InRow, "KilledImg", row->KilledImg, 0);
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


#define sMapiconConfig (*DATA::MapiconConfig::Instance())
}