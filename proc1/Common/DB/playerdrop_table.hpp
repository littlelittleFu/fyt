#pragma once


namespace DATA
{
	struct PlayerDropInfo {
		std::string site;
		uint32_t rate;

	};

	class PlayerDropConfig:public TableBase<PlayerDropInfo>
	{
	public:
		DECLARE_SINGLETON(PlayerDropConfig);
	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_STRING_VALUE(InRow, "site", row->site);
			CELL_VALUE(InRow, "rate", row->rate , 0);
		}

		virtual void FillMapping(TItem* row) override
		{
			TKeyIDMapping* t0 = &key_id_mappings_;
			auto groupVec = str_split(row->site, "|");
			for (auto iter = groupVec.begin(); iter != groupVec.end(); ++iter) {
				auto rangeVec = str_split(*iter, "-");
				if (rangeVec.size() == 1) {
					int site = atoi(rangeVec[0].c_str());
					if (t0->find(site) == t0->end()) {
						(*t0)[site] = 0;
						TItem*& t1 = (*t0)[site];
						t1 = row;
					}
				}
				else if (rangeVec.size() == 2) {
					int beginSite = atoi(rangeVec[0].c_str());
					int endSite = atoi(rangeVec[1].c_str());
					for (int i = beginSite; i <= endSite; ++i) {
						if (t0->find(i) == t0->end()) {
							(*t0)[i] = 0;
							TItem*& t1 = (*t0)[i];
							t1 = row;
						}
					}


				}
			}
		}

		virtual bool CheckValid(TItem* row)override {
			if (row->rate == 0)return false;
			return true;
		}

	};

#define sPlayerDropConfig (*DATA::PlayerDropConfig::Instance())
}
