/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Monster
	{
        bool CheckEnable(int32_t enableType)
        {
            if (Enable.empty()) return false;
            return Enable.find(enableType) != Enable.end();
        }
		int32_t				Id = 0;							/// 怪物编号
		std::string			Name = "";						/// 名称
		std::string			KeyName = "";					/// 关键字索引
		int32_t				Type = 0;						/// 类型
		int32_t				Model = 0;						/// 模型
		int32_t				Head = 0;						/// 小头像
		int32_t				Race = 0;						/// 种族
		int32_t				Level = 0;						/// 等级
		int32_t				HP = 0;							/// 配置生命
		int32_t				MP = 0;							/// 配置魔法
		int32_t				MaxPhyDef = 0;					/// 配置物防上限
		int32_t				MinPhyDef = 0;					/// 配置物防下限
		int32_t				MaxMagDef = 0;					/// 配置魔防上限
		int32_t				MinMagDef = 0;					/// 配置魔防下限
		int32_t				MaxPhyAtk = 0;					/// 配置物攻上限
		int32_t				MinPhyAtk = 0;					/// 配置物攻下限
		int32_t				MaxMagAtk = 0;					/// 配置魔攻上限
		int32_t				MinMagAtk = 0;					/// 配置魔攻下限
		int32_t				Hit = 0;						/// 配置准确（命中）
		int32_t				Miss = 0;						/// 配置敏捷（闪避）
		std::map<int32_t, int32_t> SpecialAttr;			    /// 特殊属性
        int32_t             AtkType = 0;                    /// 攻击类型
        int32_t             FigType = 0;                    /// 战斗类型
        int32_t             VieRange = 0;                   /// 视野
        int32_t             TraRange = 0;                   /// 追踪距离
        int32_t             MovRange = 0;                   /// 活动范围
        int32_t             MovTime = 0;                    /// 活动间隔
        int32_t             AttackSpeed = 0;                /// 攻击速度
        int32_t             AttackReady = 0;                /// 攻击准备时间
        int32_t             MoveSpeed = 0;                  /// 移动速度
        int32_t             MoveReady = 0;                  /// 移动准备时间
        int32_t             Step = 0;                       /// 步长间隔
        int32_t             StepWait = 0;                   /// 步长间隔等待时间
        int32_t             Back = 0;                       /// 后仰时间
        int32_t             EscapeStep = 0;                 /// 躲避步长
        int32_t             EscapeRate = 0;                 /// 躲避概率
		std::string         Script = "";                    /// 脚本编号
        std::set<int32_t>   Enable;                         /// 标识monster_enable_type
        std::map<int32_t, int32_t> SkillDamageCoff;         /// 技能伤害加成
        std::map<int32_t, std::vector<std::pair<int32_t, int32_t>>> SkillCastingRate;        /// 技能释放权重
        int32_t             Exp = 0;                        /// 怪物经验
        int32_t             BodySize = 0;                   /// 体形
		std::string         Drop = "";                      /// 掉落文本
        int32_t             Magic = 0;                      /// 怪物特效
        int32_t             ExistTime = 0;                  /// 怪物存在时间
        int32_t		        NameColor = 0;				    /// 名字ARGB颜色，当其值为0时，使用系统默认颜色
        int32_t             MonsterAIType = 0;              ///怪物AI类型
	};


	class MonsterConfig : public TableBase<Monster>
	{
		DECLARE_SINGLETON(MonsterConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_STRING_VALUE(InRow, "Name", row->Name);
            CELL_STRING_VALUE(InRow, "KeyName", row->KeyName);
            CELL_VALUE(InRow, "Type", row->Type, 0);
            CELL_VALUE(InRow, "Model", row->Model, 0);
            CELL_VALUE(InRow, "Head", row->Head, 0);
            CELL_VALUE(InRow, "Race", row->Race, 0);
            CELL_VALUE(InRow, "Level", row->Level, 0);
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
            CELL_VALUE(InRow, "Hit", row->Hit, 0);
            CELL_VALUE(InRow, "Miss", row->Miss, 0);
			SPLIT_CELL_KEY_VALUE(InRow, "SpecialAttr", "|", ":", row->SpecialAttr);
            CELL_VALUE(InRow, "AtkType", row->AtkType, 0);
            CELL_VALUE(InRow, "FigType", row->FigType, 0);
            CELL_VALUE(InRow, "VieRange", row->VieRange, 0);
            CELL_VALUE(InRow, "TraRange", row->TraRange, 0);
            CELL_VALUE(InRow, "MovRange", row->MovRange, 0);
            CELL_VALUE(InRow, "MovTime", row->MovTime, 0);
            CELL_VALUE(InRow, "AttackSpeed", row->AttackSpeed, 0);
            CELL_VALUE(InRow, "AttackReady", row->AttackReady, 0);
            CELL_VALUE(InRow, "MoveSpeed", row->MoveSpeed, 0);
            CELL_VALUE(InRow, "MoveReady", row->MoveReady, 0);
            CELL_VALUE(InRow, "Step", row->Step, 0);
            CELL_VALUE(InRow, "StepWait", row->StepWait, 0);
            CELL_VALUE(InRow, "Back", row->Back, 0);
            CELL_VALUE(InRow, "EscapeStep", row->EscapeStep, 0);
            CELL_VALUE(InRow, "EscapeRate", row->EscapeRate, 0);
            CELL_STRING_VALUE(InRow, "Script", row->Script);
            SPLIT_CELL_SET_VALUE(InRow, "Enable", "|", row->Enable);
            SPLIT_CELL_KEY_VALUE(InRow, "SkillDamageCoff", "|", ":", row->SkillDamageCoff);
            SPLIT_CELL_KEY_MUTIBAG_VALUE(InRow, "SkillCastingRate", "|", ";", ",", row->SkillCastingRate);
            CELL_VALUE(InRow, "Exp", row->Exp, 0);
            CELL_VALUE(InRow, "BodySize", row->BodySize, 0);
            CELL_STRING_VALUE(InRow, "Drop", row->Drop);
            CELL_VALUE(InRow, "Magic", row->Magic, 0);
            CELL_VALUE(InRow, "ExistTime", row->ExistTime, 0);
            CELL_VALUE(InRow, "NameColor", row->NameColor, 0);
            CELL_VALUE(InRow, "MonsterAIType", row->MonsterAIType, 0);
		}

        virtual bool CheckValid(TItem *row) override
        {
            if (row->Id == 0 || row->KeyName.empty()) return false;
            return true;
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


#define sMonsterConfig (*DATA::MonsterConfig::Instance())
}