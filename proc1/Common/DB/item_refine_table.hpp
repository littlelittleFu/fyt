/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct ItemRefine
	{
		uint32_t      Level;                       /// 精炼等级
		uint32_t      Att1;                        /// 属性1
		uint32_t      AttValue1;                   /// 属性值1
		uint32_t      Att2;                        /// 属性2
		uint32_t      AttValue2;                   /// 属性值2
		uint32_t      Att3;                        /// 属性3
		uint32_t      AttValue3;                   /// 属性值3
		uint32_t      Att4;                        /// 属性4
		uint32_t      AttValue4;                   /// 属性值4
		uint32_t      Att5;                        /// 属性5
		uint32_t      AttValue5;                   /// 属性值5
		uint32_t      Att6;                        /// 属性6
		uint32_t      AttValue6;                   /// 属性值6
		uint32_t      Att7;                        /// 属性7
		uint32_t      AttValue7;                   /// 属性值7
		uint32_t      Att8;                        /// 属性8
		uint32_t      AttValue8;                   /// 属性值8
		uint32_t      Att9;                        /// 属性9
		uint32_t      AttValue9;                   /// 属性值9
		uint32_t      Att10;                       /// 属性10
		uint32_t      AttValue10;                  /// 属性值10
		uint32_t      Icon;                        /// 显示图标
	};


	class ItemRefineConfig : public TableBase<ItemRefine>
	{
		DECLARE_SINGLETON(ItemRefineConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Level", row->Level, 0);
            CELL_VALUE(InRow, "Att1", row->Att1, 0);
            CELL_VALUE(InRow, "AttValue1", row->AttValue1, 0);
            CELL_VALUE(InRow, "Att2", row->Att2, 0);
            CELL_VALUE(InRow, "AttValue2", row->AttValue2, 0);
            CELL_VALUE(InRow, "Att3", row->Att3, 0);
            CELL_VALUE(InRow, "AttValue3", row->AttValue3, 0);
            CELL_VALUE(InRow, "Att4", row->Att4, 0);
            CELL_VALUE(InRow, "AttValue4", row->AttValue4, 0);
            CELL_VALUE(InRow, "Att5", row->Att5, 0);
            CELL_VALUE(InRow, "AttValue5", row->AttValue5, 0);
            CELL_VALUE(InRow, "Att6", row->Att6, 0);
            CELL_VALUE(InRow, "AttValue6", row->AttValue6, 0);
            CELL_VALUE(InRow, "Att7", row->Att7, 0);
            CELL_VALUE(InRow, "AttValue7", row->AttValue7, 0);
            CELL_VALUE(InRow, "Att8", row->Att8, 0);
            CELL_VALUE(InRow, "AttValue8", row->AttValue8, 0);
            CELL_VALUE(InRow, "Att9", row->Att9, 0);
            CELL_VALUE(InRow, "AttValue9", row->AttValue9, 0);
            CELL_VALUE(InRow, "Att10", row->Att10, 0);
            CELL_VALUE(InRow, "AttValue10", row->AttValue10, 0);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Level) == t0->end())
                (*t0)[row->Level] = 0;
            TItem *&t1 = (*t0)[row->Level];
            t1 = row;
        }
	};


#define sItemRefineConfig (*DATA::ItemRefineConfig::Instance())
}