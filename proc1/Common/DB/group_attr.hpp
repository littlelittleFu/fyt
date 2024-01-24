/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once


#include <map>
#include <utility>


class CsvHelper;
namespace DATA
{
	struct GroupAttr
	{
		int32_t      			Id = 0;							/// id
		std::string        		Desc = "";						/// 说明
		std::map<int32_t, int32_t>		GroupInfo;				/// 属性集合，first:属性id second:比例
	};

	class GroupAttrConfig : public TableBase<GroupAttr>
	{
	public:
		DECLARE_SINGLETON(GroupAttrConfig);
	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_VALUE(InRow, "Id", row->Id, 0);
			SPLIT_CELL_KEY_VALUE(InRow, "GroupInfo", "|", ":", row->GroupInfo);
			CELL_STRING_VALUE(InRow, "Desc", row->Desc);
		}
		virtual bool CheckValid(TItem *row) override
		{
			if (row->Id == 0) return false;
			return true;
		}
		virtual void FillMapping(TItem* row) override
		{
			TKeyIDMapping* t0 = &key_id_mappings_;
			if (t0->find(row->Id) == t0->end())
				(*t0)[row->Id] = 0;
			TItem*& t1 = (*t0)[row->Id];
			t1 = row;
			key_name_mappings_[to_string(row->Id)] = row;
		}
	};

#define sGroupAttrConfig (*DATA::GroupAttrConfig::Instance())
}