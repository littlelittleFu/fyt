/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Achievement
	{
		uint32_t      Id;                          /// 编号
		char        Name[32];                    /// 名称
		uint16_t      Type;                        /// 标签编号
		uint32_t      TypeId;                      /// 标签图片编号
		char        TypeName[32];                /// 标签名称
		char        TypeDes[144];                /// 标签描述
		char        AchDes[384];                 /// 成就描述
		uint8_t       Gender;                      /// 成就性别
		uint8_t       Job;                         /// 成就职业
		uint16_t      AwardLevel;                  /// 领取等级
		uint8_t       TriggerLevel;                /// 触发等级
		uint32_t      ExpAward;                    /// 经验奖励
		uint32_t      GoldAward;                   /// 金币奖励
		uint32_t      bindGoldAward;               /// 绑定金币奖励
		char        ItemAward1[32];              /// 道具奖励1
		uint8_t       ItemAward1Num;               /// 道具奖励1数量
		uint8_t       Bind1;                       /// 道具1是否绑定
		char        ItemAward2[32];              /// 道具奖励2
		uint8_t       ItemAward2Num;               /// 道具奖励2数量
		uint8_t       Bind2;                       /// 道具2是否绑定
		char        ItemAward3[32];              /// 道具奖励3
		uint8_t       ItemAward3Num;               /// 道具奖励3数量
		uint8_t       Bind3;                       /// 道具3是否绑定
		char        ItemAward4[32];              /// 道具奖励4
		uint8_t       ItemAward4Num;               /// 道具奖励4数量
		uint8_t       Bind4;                       /// 道具4是否绑定
		char        Script[32];                  /// 脚本
		uint16_t      Trigger1;                    /// 触发条件1
		uint16_t      Trigger2;                    /// 触发条件2
		uint16_t      Trigger3;                    /// 触发条件3
		uint16_t      Trigger4;                    /// 触发条件4
		uint16_t      Trigger5;                    /// 触发条件5
		uint8_t       GloryOpen;                   /// 开启成就
	};


	class AchievementConfig : public TableBase<Achievement>
	{
		DECLARE_SINGLETON(AchievementConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "Type", row->Type, 0);
            CELL_VALUE(InRow, "TypeId", row->TypeId, 0);
            CELL_VALUE(InRow, "TypeName", row->TypeName, 1);
            CELL_VALUE(InRow, "TypeDes", row->TypeDes, 1);
            CELL_VALUE(InRow, "AchDes", row->AchDes, 1);
            CELL_VALUE(InRow, "Gender", row->Gender, 0);
            CELL_VALUE(InRow, "Job", row->Job, 0);
            CELL_VALUE(InRow, "AwardLevel", row->AwardLevel, 0);
            CELL_VALUE(InRow, "TriggerLevel", row->TriggerLevel, 0);
            CELL_VALUE(InRow, "ExpAward", row->ExpAward, 0);
            CELL_VALUE(InRow, "GoldAward", row->GoldAward, 0);
            CELL_VALUE(InRow, "bindGoldAward", row->bindGoldAward, 0);
            CELL_VALUE(InRow, "ItemAward1", row->ItemAward1, 1);
            CELL_VALUE(InRow, "ItemAward1Num", row->ItemAward1Num, 0);
            CELL_VALUE(InRow, "Bind1", row->Bind1, 0);
            CELL_VALUE(InRow, "ItemAward2", row->ItemAward2, 1);
            CELL_VALUE(InRow, "ItemAward1Num", row->ItemAward2Num, 0);
            CELL_VALUE(InRow, "Bind2", row->Bind2, 0);
            CELL_VALUE(InRow, "ItemAward3", row->ItemAward3, 1);
            CELL_VALUE(InRow, "ItemAward1Num", row->ItemAward3Num, 0);
            CELL_VALUE(InRow, "Bind3", row->Bind3, 0);
            CELL_VALUE(InRow, "ItemAward4", row->ItemAward4, 1);
            CELL_VALUE(InRow, "ItemAward1Num", row->ItemAward4Num, 0);
            CELL_VALUE(InRow, "Bind4", row->Bind4, 0);
            CELL_VALUE(InRow, "Script", row->Script, 1);
            CELL_VALUE(InRow, "Trigger1", row->Trigger1, 0);
            CELL_VALUE(InRow, "Trigger2", row->Trigger2, 0);
            CELL_VALUE(InRow, "Trigger3", row->Trigger3, 0);
            CELL_VALUE(InRow, "Trigger4", row->Trigger4, 0);
            CELL_VALUE(InRow, "Trigger5", row->Trigger5, 0);
            CELL_VALUE(InRow, "GloryOpen", row->GloryOpen, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = 0;
            TItem *&t1 = (*t0)[row->Id];
            t1 = row;
        }
	};


#define sAchievementConfig (*DATA::AchievementConfig::Instance())
}