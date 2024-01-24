/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Title
	{
		uint32_t     Id;                          /// ID
		char         Name[32];                    /// 名字
		char         KeyName[32];                 /// 索引名
        uint16_t     type;                        /// 类型
        uint32_t     Icon;                        /// 图片编号
        uint32_t     BigIconEffect;               /// 内观特效图
        uint32_t     Effect;                      /// 外观特效
		uint8_t      Size;                        /// 面板结构位置
		uint8_t      Priority;                    /// 优先级
		uint8_t      Unique;                      /// 全服唯一
		uint16_t     BuffID;                      /// BUFFID
		uint8_t      MergeDel;                    /// 合服是否删除
		char         Tips[296];                   /// 描述
		char         TipsSource[296];             /// 称号来源描述
		uint8_t      TetelShow;                   /// 是否加入未获得称号显示
		uint8_t      Color;                       /// 字体颜色
		uint8_t      HasShowName;                 /// 是否显示头顶宋称号
		uint32_t     TimeLimit;                   /// 存在时限
		uint8_t      UseAbsTime;                  /// 绝对时间或相对时间
		char	     ColorString[96];             /// 颜色
        uint32_t     HP;                          /// 声明
        uint32_t     MP;                          /// 魔法
        uint32_t     MinPhyDef;                   /// 物防下限
        uint32_t     MaxPhyDef;                   /// 物防上限
        uint32_t     MinMagDef;                   /// 魔防下限
        uint32_t     MaxMagDef;                   /// 魔防上限
        uint32_t     MinPhyAtk;                   /// 攻击力下限
        uint32_t     MaxPhyAtk;                   /// 攻击力上限
        uint32_t     MinMagAtk;                   /// 魔攻下限
        uint32_t     MaxMagAtk;                   /// 魔攻上限
        uint32_t     MinTaoAtk;                   /// 道术下限
        uint32_t     MaxTaoAtk;                   /// 道术上限
        uint32_t     Hit;                         /// 物理准确
        uint32_t     Miss;                        /// 物理闪避
        std::map<int,int> SpecialAttr;            /// 附加属性
        uint32_t     SkillId;                     /// 触发技能ID

	};


	class TitleConfig : public TableBase<Title>
	{
		DECLARE_SINGLETON(TitleConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "type", row->type, 0);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
            CELL_VALUE(InRow, "BigIconEffect", row->BigIconEffect, 0);
            CELL_VALUE(InRow, "Effect", row->Effect, 0);
            CELL_VALUE(InRow, "Size", row->Size, 0);
            CELL_VALUE(InRow, "Priority", row->Priority, 0);
            CELL_VALUE(InRow, "Unique", row->Unique, 0);
            CELL_VALUE(InRow, "BuffId", row->BuffID, 0);
            CELL_VALUE(InRow, "MergeDel", row->MergeDel, 0);
            CELL_VALUE(InRow, "Tips", row->Tips, 1);
            CELL_VALUE(InRow, "TipsSource", row->TipsSource, 1);
            CELL_VALUE(InRow, "TetelShow", row->TetelShow, 0);
            CELL_VALUE(InRow, "Color", row->Color, 0);
            CELL_VALUE(InRow, "HasShowName", row->HasShowName, 0);
            CELL_VALUE(InRow, "TimeLimit", row->TimeLimit, 0);
            CELL_VALUE(InRow, "UseAbsTime", row->UseAbsTime, 0);
            CELL_VALUE(InRow, "ColorString", row->ColorString, 1);
            CELL_VALUE(InRow, "HP", row->HP, 0);
            CELL_VALUE(InRow, "MP", row->MP, 0);
            CELL_VALUE(InRow, "MinPhyDef", row->MinPhyDef, 0);
            CELL_VALUE(InRow, "MaxPhyDef", row->MaxPhyDef, 0);
            CELL_VALUE(InRow, "MinMagDef", row->MinMagDef, 0);
            CELL_VALUE(InRow, "MaxMagDef", row->MaxMagDef, 0);
            CELL_VALUE(InRow, "MinPhyAtk", row->MinPhyAtk, 0);
            CELL_VALUE(InRow, "MaxPhyAtk", row->MaxPhyAtk, 0);
            CELL_VALUE(InRow, "MinMagAtk", row->MinMagAtk, 0);
            CELL_VALUE(InRow, "MaxMagAtk", row->MaxMagAtk, 0);
            CELL_VALUE(InRow, "MinTaoAtk", row->MinTaoAtk, 0);
            CELL_VALUE(InRow, "MaxTaoAtk", row->MaxTaoAtk, 0);
            CELL_VALUE(InRow, "Hit", row->Hit, 0);
            CELL_VALUE(InRow, "Miss", row->Miss, 0);
            SPLIT_CELL_KEY_VALUE(InRow, "SpecialAttr", "|", ":", row->SpecialAttr);
            CELL_VALUE(InRow, "SkillId", row->SkillId, 0);
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


#define sTitleConfig (*DATA::TitleConfig::Instance())
}