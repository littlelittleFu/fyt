#pragma once
class CsvHelper;
namespace DATA
{

	struct DropPlusInfo
	{
		int groupid;               ///掉落组ID
		int item;                  ///物品ID
		int weight;                ///组内权重
	};

	class DropplusConfig : public TableBase<DropPlusInfo>
	{
		DECLARE_SINGLETON(DropplusConfig);
	public:
        virtual ~DropplusConfig()
        {
            Release();
        }

        virtual void Release()
        {
            for (auto &it : key_name_mappings_rows) {
                auto &row = it.second;
                if (row) delete row;
            }

            TableBase<DropPlusInfo>::Release();
        }

		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_VALUE(InRow, "groupid", row->groupid, 0);
			CELL_VALUE(InRow, "item", row->item, 0);
			CELL_VALUE(InRow, "weight", row->weight, 0);
		}

		virtual void FillMapping(TItem* row) override
		{
			TKeyNameMappingTRows* t0 = &key_name_mappings_rows;
			if (t0->find(to_string(row->groupid)) == t0->end())
				(*t0)[to_string(row->groupid)] = new vector<TItem*>();
			TRows*& t1 = (*t0)[to_string(row->groupid)];
			t1->push_back(row);
		}
	};


#define sDropplusConfig (*DATA::DropplusConfig::Instance())

}
