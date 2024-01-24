/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once


#include <map>
#include <utility>


class CsvHelper;
namespace DATA
{
	struct Item
	{
		bool CheckEnable(int32_t enableType)
		{
			if (Enable.empty()) return false;
			return Enable.find(enableType) != Enable.end();
		}
		int32_t      			Id = 0;							/// 物品编号
		std::string        		Name = "";						/// 名称
		std::string        		KeyName = "";					///	索引名称
		std::string        		Desc = "";						/// 物品说明
		int32_t       			Type = 0;                      	/// 主类型
		int32_t       			SubType = 0;                   	/// 子类型
		int32_t					WeaponType = 0;					/// 武器类型
		uint32_t        		Color = 0;                 		/// 道具颜色
		uint64_t      			Icon = 0;                       /// 图标编号
		uint64_t      			BigIcon = 0;               		/// 角色模型图片
		uint64_t				BigIconEffect = 0;				/// 内观特效图片
		int32_t      			AvatarMan = 0;                  /// 外形男
		int32_t      			AvatarWomen = 0;               	/// 外形女
		int32_t					AvatarEffect = 0;				/// 外观特效
		int32_t					DropEffect = 0;					/// 掉落特效	
		int32_t      			Quality = 0;                   	/// 品质	
		int32_t      			Level = 0;                     	/// 使用等级
		int32_t       			Gender = 0;                    	/// 使用性别	
		int32_t       			Job = 0;                       	/// 使用职业
		int32_t       			PhyLimit = 0;                  	/// 物攻限制
		int32_t       			MagLimit = 0;                  	/// 魔攻限制
		int32_t       			TaoLimit = 0;                  	/// 道术限制
		int32_t      			Stack = 0;                     	/// 叠加数量
		std::string     		Script = "";               		/// 脚本名
		std::set<int32_t>		DropType;						/// 掉落类型		
		int32_t       			HP = 0;                        	/// 生命
		int32_t       			MP = 0;                        	/// 魔法
		int32_t       			MaxPhyDef = 0;                 	/// 物防上限
		int32_t       			MinPhyDef = 0;                 	/// 物防下限
		int32_t       			MaxMagDef = 0;                 	/// 魔防上限
		int32_t       			MinMagDef = 0;                 	/// 魔防下限
		int32_t       			MaxPhyAtk = 0;                	/// 攻击力上限
		int32_t       			MinPhyAtk = 0;                 	/// 攻击力下限
		int32_t       			MaxMagAtk = 0;                 	/// 魔攻上限
		int32_t       			MinMagAtk = 0;                 	/// 魔攻下限
		int32_t       			MaxTaoAtk = 0;                 	/// 道术上限
		int32_t       			MinTaoAtk = 0;                  /// 道术下限
		int32_t        			Hit = 0;                        /// 准确(命中)
		int32_t        			Miss = 0;                       /// 敏捷(闪避)
		std::map<int32_t, int32_t>		SpecialAttr;			/// 特殊属性
		int32_t    				SkillId = 0;                    /// 触发技能
		std::set<int32_t> 		BuffId;                     	/// 道具自身携带的Buff				
		int32_t      			LS2 = 0;                        /// 包裹排列				
		int32_t       			BindType = 0;					/// 绑定类型
		std::set<int32_t>		Enable;							/// 可操作类型,item_enable_type
		int32_t      			UseCount = 0;					/// 使用数量
		int32_t       			JuJuType = 0;					/// 符咒类别
		int32_t      			TimeLimit = 0;					/// 存在时限
		int32_t      			TimeType = 0;					/// 时限类型(相对还是绝对)
		int32_t      			Suit = 0;						/// 套装编号
		int32_t       			BagSize = 0;					/// 开启背包格子数
		int32_t       			WarehouseSize = 0;				/// 开启仓库格子数
		int32_t        			Burst = 0;						/// 爆击率
		int32_t       			AttackSpeed = 0;				/// 攻击速度
		int32_t       			User = 0;						/// 使用者范畴
		int32_t					FashionId = 0;					/// 时装ID

		int32_t					Durability = 0;					/// 配置耐久度
		int32_t					Track = 0;						/// 跟踪
	};

	class ItemConfig : public TableBase<Item>
	{
	public:
		DECLARE_SINGLETON(ItemConfig);
	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_VALUE(InRow, "Id", row->Id, 0);
			CELL_STRING_VALUE(InRow, "Name", row->Name);
			CELL_STRING_VALUE(InRow, "KeyName", row->KeyName);
			CELL_STRING_VALUE(InRow, "Desc", row->Desc);
			CELL_VALUE(InRow, "Type", row->Type, 0);
			CELL_VALUE(InRow, "SubType", row->SubType, 0);
			CELL_VALUE(InRow, "WeaponType", row->WeaponType, 0);
			CELL_COLOR(InRow, "Color", row->Color);
			CELL_VALUE(InRow, "Icon", row->Icon, 0);
			CELL_VALUE(InRow, "BigIcon", row->BigIcon, 0);
			CELL_VALUE(InRow, "BigIconEffect", row->BigIconEffect, 0);
			CELL_VALUE(InRow, "AvatarMan", row->AvatarMan, 0);
			CELL_VALUE(InRow, "AvatarWomen", row->AvatarWomen, 0);
			CELL_VALUE(InRow, "AvatarEffect", row->AvatarEffect, 0);
			CELL_VALUE(InRow, "DropEffect", row->DropEffect, 0);
			CELL_VALUE(InRow, "Quality", row->Quality, 0);
			CELL_VALUE(InRow, "Level", row->Level, 0);
			CELL_VALUE(InRow, "Gender", row->Gender, 0);
			CELL_VALUE(InRow, "Job", row->Job, 0);
			CELL_VALUE(InRow, "PhyLimit", row->PhyLimit, 0);
			CELL_VALUE(InRow, "MagLimit", row->MagLimit, 0);
			CELL_VALUE(InRow, "TaoLimit", row->TaoLimit, 0);
			CELL_VALUE(InRow, "Stack", row->Stack, 0);
			CELL_STRING_VALUE(InRow, "Script", row->Script);
			SPLIT_CELL_SET_VALUE(InRow, "DropType", "|", row->DropType);
			CELL_VALUE(InRow, "HP", row->HP, 0);
			CELL_VALUE(InRow, "MP", row->MP, 0);
			CELL_VALUE(InRow, "MaxPhyDef", row->MaxPhyDef, 0);
			CELL_VALUE(InRow, "MinPhyDef", row->MinPhyDef, 0);
			CELL_VALUE(InRow, "MaxMagDef", row->MaxMagDef, 0);
			CELL_VALUE(InRow, "MinMagDef", row->MinMagDef, 0);
			CELL_VALUE(InRow, "MaxPhyAtk", row->MaxPhyAtk, 0);
			CELL_VALUE(InRow, "MinPhyAtk", row->MinPhyAtk, 0);
			CELL_VALUE(InRow, "MaxMagAtk", row->MaxMagAtk, 0);
			CELL_VALUE(InRow, "MinMagAtk", row->MinMagAtk, 0);
			CELL_VALUE(InRow, "MaxTaoAtk", row->MaxTaoAtk, 0);
			CELL_VALUE(InRow, "MinTaoAtk", row->MinTaoAtk, 0);
			CELL_VALUE(InRow, "Hit", row->Hit, 0);
			CELL_VALUE(InRow, "Miss", row->Miss, 0);
			SPLIT_CELL_KEY_VALUE(InRow, "SpecialAttr", "|", ":", row->SpecialAttr);
			CELL_VALUE(InRow, "SkillId", row->SkillId, 0);
			SPLIT_CELL_SET_VALUE(InRow, "BuffId", "|", row->BuffId);
			CELL_VALUE(InRow, "LS2", row->LS2, 0);
			CELL_VALUE(InRow, "BindType", row->BindType, 0);
			SPLIT_CELL_SET_VALUE(InRow, "Enable", "|", row->Enable);
			CELL_VALUE(InRow, "UseCount", row->UseCount, 0);
			CELL_VALUE(InRow, "JuJuType", row->JuJuType, 0);
			CELL_PAIR_INT_VALUE(InRow, "TimeLimit", "|", row->TimeLimit, row->TimeType);
			CELL_VALUE(InRow, "Suit", row->Suit, 0);
			CELL_VALUE(InRow, "BagSize", row->BagSize, 0);
			CELL_VALUE(InRow, "WarehouseSize", row->WarehouseSize, 0);
			CELL_VALUE(InRow, "Burst", row->Burst, 0);
			CELL_VALUE(InRow, "AttackSpeed", row->AttackSpeed, 0);
			CELL_VALUE(InRow, "User", row->User, 0);
			CELL_VALUE(InRow, "FashionId", row->FashionId, 0);
			CELL_VALUE(InRow, "Durability", row->Durability, 0);
			CELL_VALUE(InRow, "Track", row->Track, 0);

			if (row->Stack <= 0 || row->Stack > UINT16_MAX) row->Stack = UINT16_MAX;
		}
		virtual bool CheckValid(TItem *row) override
		{
			if (row->Id == 0 || row->KeyName.empty()) return false;
			return true;
		}
		virtual void FillMapping(TItem* row) override
		{
			TKeyIDMapping* t0 = &key_id_mappings_;
			if (t0->find(row->Id) == t0->end())
				(*t0)[row->Id] = 0;
			TItem*& t1 = (*t0)[row->Id];
			t1 = row;
			key_name_mappings_[row->KeyName] = row;
		}
	};

#define sItemConfig (*DATA::ItemConfig::Instance())
}