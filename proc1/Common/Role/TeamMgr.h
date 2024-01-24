#pragma once
#include <list>
#include <Protocol/DataInfo.hpp>
#include <unordered_map>

#define MAX_TEAM_NUM 15

class Player;
struct TeamData
{
	uint64_t mGUID = 0;
	uint64_t mLeaderGUID = 0;
	std::string mLeaderName = "";
	unsigned char mPermission = 0;
	std::list<TEAM_MEMBER> mMemberList;

	int AddMember(Player* player);
	void RemoveMember(uint64_t id);
	TEAM_MEMBER* FindMember(uint64_t id);
	TEAM_MEMBER* FindMember(const std::string& name);
	TEAM_MEMBER* FindMemberNotLeader(void);
};

class TeamMgr
{
public:
	TeamMgr();
	~TeamMgr();
	DECL_SINGLETON(TeamMgr);

public:
	TeamData* CreateTeam();
	void RemoveTeam(uint64_t teamGUID);
	TeamData* FindTeam(uint64_t teamGUID);
	std::unordered_map<uint64_t, TeamData*>& GetTeamMap(void) { return mTeamMap; }
	void ChangeMemberNameInfo(uint64_t guid, const std::string& name);
protected:
	std::unordered_map<uint64_t, TeamData*> mTeamMap;
};

class TeamDataMgr
{
	friend Player;
public:
	TeamDataMgr(Player* player);
	virtual ~TeamDataMgr();

	CLuaObject GetTeamInfo();
	uint16_t GetTeamMemNum(void);
	std::string GetTeamGuid();
	void HandleTeamOperation(uint8_t operation, const string& content);
	void HandleTeamLeave(void);
	void HandleTeamInviteRsp(uint8_t accept, const string& inviter_name);
	void HandleTeamJoin(const string& joiner_name);
	void HandleTeamJoinRsp(uint8_t accept, const string& joiner_name);
	void HandleTeamKick(const string& name);
	void HandleTeamInvite(const string& invitee_name);
	void HandleTeamArround(void);
protected:
	void HandleTeamCreate(void);
	void HandleTeamDisMiss(void);

	void HandleTransferTeamLeader(const string& name);
protected:
	void SendTeamInfoNtf();//BROCAST
	void SendTeamLeaveNtf(uint64_t id, unsigned char type);//BROCAST Ö÷¶¯Àë¿ª
	void SendTeamLeaderNtf();//BROCAST
	void SendTeamInviteNtf(TeamData* INFO, Player* player);//BROCAST
protected:
	Player* m_player;
};
