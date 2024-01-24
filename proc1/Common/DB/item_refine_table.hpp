/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct ItemRefine
	{
		uint32_t      Level;                       /// �����ȼ�
		uint32_t      Att1;                        /// ����1
		uint32_t      AttValue1;                   /// ����ֵ1
		uint32_t      Att2;                        /// ����2
		uint32_t      AttValue2;                   /// ����ֵ2
		uint32_t      Att3;                        /// ����3
		uint32_t      AttValue3;                   /// ����ֵ3
		uint32_t      Att4;                        /// ����4
		uint32_t      AttValue4;                   /// ����ֵ4
		uint32_t      Att5;                        /// ����5
		uint32_t      AttValue5;                   /// ����ֵ5
		uint32_t      Att6;                        /// ����6
		uint32_t      AttValue6;                   /// ����ֵ6
		uint32_t      Att7;                        /// ����7
		uint32_t      AttValue7;                   /// ����ֵ7
		uint32_t      Att8;                        /// ����8
		uint32_t      AttValue8;                   /// ����ֵ8
		uint32_t      Att9;                        /// ����9
		uint32_t      AttValue9;                   /// ����ֵ9
		uint32_t      Att10;                       /// ����10
		uint32_t      AttValue10;                  /// ����ֵ10
		uint32_t      Icon;                        /// ��ʾͼ��
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