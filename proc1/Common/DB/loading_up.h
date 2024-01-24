#pragma once


#include <map>
#include <utility>


class CsvHelper;
namespace DATA
{
	struct LoadingWords
	{
		char info[4096];
	};

	class LoadingWordsConfig : public TableBase<LoadingWords>
	{
		DECLARE_SINGLETON(LoadingWordsConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
			CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Content", row->info, 1);
        }
	};
}