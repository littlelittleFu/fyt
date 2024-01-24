/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Hair
	{
		char        Name[32];                    /// 名字
		uint32_t      Avatar;                      /// 外形
		uint8_t       Sex;                         /// 性别
	};


	class HairConfig : public TableBase<Hair>
	{
		DECLARE_SINGLETON(HairConfig);
	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Avatar", row->Avatar, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "Sex", row->Sex, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyNameMapping *t0 = &key_name_mappings_;
            if (t0->find(row->Name) == t0->end())
                (*t0)[row->Name] = 0;
            TItem *&t1 = (*t0)[row->Name];
            t1 = row;
        }
	};


#define sHairConfig (*DATA::HairConfig::Instance())
}