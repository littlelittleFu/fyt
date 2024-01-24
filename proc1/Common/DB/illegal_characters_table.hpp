/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once
class CsvHelper;
namespace DATA
{
	struct IllegalCharacters
	{
		uint32_t            Id = 0;                      /// ID
        std::string         characters = "";             /// ·Ç·¨×Ö·û
	};

	class IllegalCharactersConfig : public TableBase<IllegalCharacters>
	{
		DECLARE_SINGLETON(IllegalCharactersConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "id", row->Id, 0);
            CELL_STRING_VALUE(InRow, "characters", row->characters);
        }

        virtual void FillMapping(TItem* row) override
        {
        }
	};


#define sIllegalCharactersConfig (*DATA::IllegalCharactersConfig::Instance())
}