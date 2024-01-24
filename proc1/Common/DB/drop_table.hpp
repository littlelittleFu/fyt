#pragma once

#include <map>
#include <string>
#include <list>
#include <vector>

namespace DATA
{
	struct DropData {
		int itemid;
		int num;
	};

	struct MonDropInfo
	{
		int dropgroup;                      ///掉落组ID
		std::map<int,int> item;             ///掉落物ID
		std::map<int,int> group;            ///掉落物品组ID
		int rate;                           ///掉落概率万分比
		int min;                            ///最小数量
		int max;                            ///最大数量
		int dropgroupid;                    ///掉落组不同行id
	};


	class DropConfig : public TableBase<MonDropInfo>
	{
		DECLARE_SINGLETON(DropConfig);
	public:
        virtual ~DropConfig()
        {
            Release();
        }

        virtual void Release()
        {
            for (auto &it : key_name_mappings_rows) {
                auto &row = it.second;
                if (row) delete row;
            }

            TableBase<MonDropInfo>::Release();
        }

		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_VALUE(InRow, "dropgroup", row->dropgroup, 0);
			SPLIT_CELL_KEY_VALUE_AUTO_PAD(InRow, "itemid", "|", ";", row->item);
			SPLIT_CELL_KEY_VALUE_AUTO_PAD(InRow, "itemgroupid", "|", ";", row->group);
			CELL_VALUE(InRow, "rate", row->rate, 0);
			CELL_VALUE(InRow, "min", row->min, 0);
			CELL_VALUE(InRow, "max", row->max, 0);
			CELL_VALUE(InRow, "dropgroupid", row->dropgroupid, 0);

		}

		virtual void FillMapping(TItem* row) override
		{
			TKeyNameMappingTRows* t0 = &key_name_mappings_rows;
			if (t0->find(to_string(row->dropgroup)) == t0->end())
				(*t0)[to_string(row->dropgroup)] = new vector<TItem*>();
			TRows*& t1 = (*t0)[to_string(row->dropgroup)];
			t1->push_back(row);
		}
	};

#define sDropConfig (*DATA::DropConfig::Instance())
}