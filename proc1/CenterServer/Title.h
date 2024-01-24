#pragma once

class Title 
{
public:
	DECL_SINGLETON(Title);

	void AddTitle(uint64_t guid, const TITLE_INFO& info);
	void DelTitle(uint64_t guid, uint16_t num, const uint32_t* id);
	void ChangeWearType(uint64_t guid, uint32_t id, uint16_t wearType);
	void SyncPlayerTitleInfo(uint64_t guid, uint16_t num, const TITLE_INFO* info);
	void UpdateTiltleInfo(uint64_t guid, uint16_t num, const TITLE_INFO* info);
	void SendPlayerInfoToMS(uint64_t guid);
	//void GetTitleInfoFromDB(uint64_t guid, uint16_t num, const TITLE_INFO* info);
	void GenerateSyncInfoToDB(uint64_t guid, uint16_t& num, TITLE_INFO* info);

private:
	std::map<uint64_t, std::vector<SP_TITLE_INFO>> mTitleList;

	std::map<uint64_t ,std::vector<uint32_t>> mTitleFlag;
};
