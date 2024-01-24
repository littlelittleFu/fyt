/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Achievement
	{
		uint32_t      Id;                          /// ���
		char        Name[32];                    /// ����
		uint16_t      Type;                        /// ��ǩ���
		uint32_t      TypeId;                      /// ��ǩͼƬ���
		char        TypeName[32];                /// ��ǩ����
		char        TypeDes[144];                /// ��ǩ����
		char        AchDes[384];                 /// �ɾ�����
		uint8_t       Gender;                      /// �ɾ��Ա�
		uint8_t       Job;                         /// �ɾ�ְҵ
		uint16_t      AwardLevel;                  /// ��ȡ�ȼ�
		uint8_t       TriggerLevel;                /// �����ȼ�
		uint32_t      ExpAward;                    /// ���齱��
		uint32_t      GoldAward;                   /// ��ҽ���
		uint32_t      bindGoldAward;               /// �󶨽�ҽ���
		char        ItemAward1[32];              /// ���߽���1
		uint8_t       ItemAward1Num;               /// ���߽���1����
		uint8_t       Bind1;                       /// ����1�Ƿ��
		char        ItemAward2[32];              /// ���߽���2
		uint8_t       ItemAward2Num;               /// ���߽���2����
		uint8_t       Bind2;                       /// ����2�Ƿ��
		char        ItemAward3[32];              /// ���߽���3
		uint8_t       ItemAward3Num;               /// ���߽���3����
		uint8_t       Bind3;                       /// ����3�Ƿ��
		char        ItemAward4[32];              /// ���߽���4
		uint8_t       ItemAward4Num;               /// ���߽���4����
		uint8_t       Bind4;                       /// ����4�Ƿ��
		char        Script[32];                  /// �ű�
		uint16_t      Trigger1;                    /// ��������1
		uint16_t      Trigger2;                    /// ��������2
		uint16_t      Trigger3;                    /// ��������3
		uint16_t      Trigger4;                    /// ��������4
		uint16_t      Trigger5;                    /// ��������5
		uint8_t       GloryOpen;                   /// �����ɾ�
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