/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once

#include <sstream>



class CsvHelper;
namespace DATA
{
	struct NpcQuestBinding
	{
		char        NpcKeyName[32];              /// npc的KeyName
		uint16_t      QuestId;                     /// 任务模板id
		uint8_t       Accept;                      /// 能否向此npc接任务
		uint8_t       Accomplish;                  /// 能否向此npc交任务
	};


	class NpcQuestBindingConfig  : public TableBase<NpcQuestBinding>
	{
		DECLARE_SINGLETON(NpcQuestBindingConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "NpcKeyName", row->NpcKeyName, 1);
            CELL_VALUE(InRow, "QuestId", row->QuestId, 0);
            CELL_VALUE(InRow, "Accept", row->Accept, 0);
            CELL_VALUE(InRow, "Accomplish", row->Accomplish, 0);
        }
        virtual void FillMapping(TItem* row) override
		{
            stringstream ss;
            ss << row->NpcKeyName << "_" << row->QuestId;
            string keyName = ss.str();
            key_name_mappings_[keyName] = row;
		}
		TItem *Get(const std::string& NpcKeyName, uint16_t QuestId)
		{
            stringstream ss;
            ss << NpcKeyName << "_" << QuestId;
            string keyName = ss.str();

			if (key_name_mappings_.find(NpcKeyName) == key_name_mappings_.end())
				return 0;

            return key_name_mappings_[keyName];
		}

		bool Has(const std::string& NpcKeyName, uint16_t QuestId)
		{
            stringstream ss;
            ss << NpcKeyName << "_" << QuestId;
            string keyName = ss.str();

            if (key_name_mappings_.find(NpcKeyName) == key_name_mappings_.end())
                return false;

            return true;
		}
	};


#define sNpcQuestBindingConfig (*DATA::NpcQuestBindingConfig::Instance())
}