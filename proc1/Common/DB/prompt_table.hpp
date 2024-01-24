/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Prompt
	{
		uint8_t       Type;                        /// ��ʾ����
		char        Content[296];                /// ����
		uint32_t      Code;                        /// �ͻ���������ʾ������
	};


	class PromptConfig : public TableBase<Prompt>
	{
		DECLARE_SINGLETON(PromptConfig);
    public:
	    void FillData(TItem *row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Type", row->Type, 0);
            CELL_VALUE(InRow, "Content", row->Content, 1);
            CELL_VALUE(InRow, "Code", row->Code, 0);
		}
		void FillMapping(TItem *row) override
		{
			if (key_id_mappings_.find(row->Code) == key_id_mappings_.end())
				key_id_mappings_[row->Code] = 0;
			TItem *&t1 = key_id_mappings_[row->Code];
			t1 = row;
		}
	};


#define sPromptConfig (*DATA::PromptConfig::Instance())
}