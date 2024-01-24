/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Vip
	{
		uint16_t						id = 0;				/// id
		uint16_t						vipLevel = 0;		/// vip等级
		std::map<int32_t, int32_t>		basicProp;			/// 基础属性
		std::map<int32_t, int32_t>		specialProp;		/// 特殊属性
		std::string						show = "";			/// 客户端显示
		std::set<int32_t>				addSkill;			/// 添加技能
		std::set<int32_t>				extePermissions;	/// 拓展权限
		std::string						script;				/// 脚本名
		std::set<int32_t>				buffId;				/// 附带buff
		std::string						remark;				/// 属性备注
	};

	class VipConfig : public TableBase<Vip>
	{
		DECLARE_SINGLETON(VipConfig)
	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_VALUE(InRow, "Id", row->id, 0);
			CELL_VALUE(InRow, "VipLevel", row->vipLevel, 0);
			SPLIT_CELL_KEY_VALUE(InRow, "BasicProp", "|", ":", row->basicProp);
			SPLIT_CELL_KEY_VALUE(InRow, "SpecialProp", "|", ":", row->specialProp);
			CELL_STRING_VALUE(InRow, "Show", row->show);
			SPLIT_CELL_SET_VALUE(InRow, "AddSkill", "|", row->addSkill);
			SPLIT_CELL_SET_VALUE(InRow, "ExtePermissions", "|", row->extePermissions);
			CELL_STRING_VALUE(InRow, "Script", row->script);
			SPLIT_CELL_SET_VALUE(InRow, "BuffId", "|", row->buffId);
			CELL_STRING_VALUE(InRow, "Remark", row->remark);
		}
		virtual bool CheckValid(TItem *row) override
		{
			if (row->id == 0 || row->vipLevel == 0) return false;
			return true;
		}
		virtual void FillMapping(TItem* row) override
		{
			TKeyIDMapping* t0 = &key_id_mappings_;
			if (t0->find(row->vipLevel) == t0->end())
				(*t0)[row->vipLevel] = 0;
			TItem*& t1 = (*t0)[row->vipLevel];
			t1 = row;
			key_name_mappings_[to_string(row->id)] = row;
		}
	};


#define sVipConfig (*DATA::VipConfig::Instance())
}