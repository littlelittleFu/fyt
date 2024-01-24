#pragma once
#define MAX_ROLE_PK 10000
class PKValueMgr
{
public:
	PKValueMgr(Player* master):mCurRedNameTime(0),mPlayer(master){};
	~PKValueMgr() {};

	static void AddPKValue(uint64_t killerguid, Player *victim);
	static bool IsWhiteName(uint64_t guid);
	static bool IsYellowName(uint64_t guid);
	//static bool IsYellowName(uint64_t guid);
	void UpdatePKValue(int delta);

private:
    static bool IsShabakNoPK(Player *killer, Player *victim);

private:
	Player* mPlayer = nullptr;
	uint64_t mCurRedNameTime = 0;
};
