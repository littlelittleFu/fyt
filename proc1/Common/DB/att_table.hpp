/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Att
	{
		uint16_t      Id;                          /// 属性表ID
		char        Name[144];                   /// 属性的英文字段名
		char        ChinaName[144];              /// 属性的中文字段名
		char        KeyName[144];                /// 索引名称
	};


	class AttConfig  : public TableBase<Att>
	{
		DECLARE_SINGLETON(AttConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "ChinaName", row->ChinaName, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
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


#define sAttConfig (*DATA::AttConfig::Instance())
}