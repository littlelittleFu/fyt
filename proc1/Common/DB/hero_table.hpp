/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Hero
	{
		uint32_t      Level;                       /// 当前等级
		uint8_t       Job;                         /// 职业
		uint64_t      UpgradeExp;                  /// 升级经验
		uint32_t      HP;                          /// 配置生命
		uint32_t      MP;                          /// 配置魔法
		uint16_t      Weight;                      /// 配置背包负重
		uint16_t      EquipWeight;                 /// 配置装备负重
		uint16_t      Brawn;                       /// 腕力重量
		uint32_t      MaxPhyDef;                   /// 配置物防上限
		uint32_t      MinPhyDef;                   /// 配置物防下限
		uint32_t      MaxMagDef;                   /// 配置魔防上限
		uint32_t      MinMagDef;                   /// 配置魔防下限
		uint32_t      MaxPhyAtk;                   /// 配置攻击力上限
		uint32_t      MinPhyAtk;                   /// 配置攻击力下限
		uint32_t      MaxMagAtk;                   /// 配置魔攻上限
		uint32_t      MinMagAtk;                   /// 配置魔攻下限
		uint32_t      MaxTaoAtk;                   /// 配置道术上限
		uint32_t      MinTaoAtk;                   /// 配置道术下限
		uint32_t      Hit;                         /// 配置准确（命中）
		uint32_t      Miss;                        /// 配置敏捷（闪避）
		uint8_t       LC;                          /// 配置幸运/诅咒
		uint8_t       Burst;                       /// 配置暴击率
		uint16_t      Poison;                      /// 配置中毒 回复速度
		uint16_t      HPRec;                       /// 配置生命回复速度
		uint16_t      MPRec;                       /// 配置魔法回复速度
		uint32_t      Interval;                    /// 回复间隔
		uint16_t      MoveSpeed;                   /// 移动速度
		uint16_t      AttackSpeed;                 /// 普通攻击速度
		uint32_t      HeroXp;                      /// 怒气
		uint32_t      HeroXpMax;                   /// 怒气上限
	};


	class HeroConfig : public TableBase<Hero>
	{
		DECLARE_SINGLETON(HeroConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Level", row->Level, 0);
            CELL_VALUE(InRow, "Job", row->Job, 0);
            CELL_VALUE(InRow, "UpgradeExp", row->UpgradeExp, 0);
            CELL_VALUE(InRow, "HP", row->HP, 0);
            CELL_VALUE(InRow, "MP", row->MP, 0);
            CELL_VALUE(InRow, "Weight", row->Weight, 0);
            CELL_VALUE(InRow, "EquipWeight", row->EquipWeight, 0);
            CELL_VALUE(InRow, "Brawn", row->Brawn, 0);
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
            CELL_VALUE(InRow, "LC", row->LC, 0);
            CELL_VALUE(InRow, "Burst", row->Burst, 0);
            CELL_VALUE(InRow, "Poison", row->Poison, 0);
            CELL_VALUE(InRow, "HPRec", row->HPRec, 0);
            CELL_VALUE(InRow, "MPRec", row->MPRec, 0);
            CELL_VALUE(InRow, "Interval", row->Interval, 0);
            CELL_VALUE(InRow, "MoveSpeed", row->MoveSpeed, 0);
            CELL_VALUE(InRow, "AttackSpeed", row->AttackSpeed, 0);
            CELL_VALUE(InRow, "HeroXp", row->HeroXp, 0);
            CELL_VALUE(InRow, "HeroXpMax", row->HeroXpMax, 0);
		}
        virtual void FillMapping(TItem *row) override
        {
            uint32_t keyId = (row->Level << 16) | row->Job;
            key_id_mappings_[keyId] = row;
        }
        TItem *Get(uint16_t Level, uint16_t Job)
        {
            uint32_t keyId = (Level << 16) | Job;

            if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
                return 0;
            return key_id_mappings_[keyId];
        }
        bool Has(uint16_t Level, uint16_t Job)
        {
            uint32_t keyId = (Level << 16) | Job;

            if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
                return false;
            return true;
        }
	};


#define sHeroConfig (*DATA::HeroConfig::Instance())
}