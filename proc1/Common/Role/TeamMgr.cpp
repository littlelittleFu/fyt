#include "stdafx.h"

#include "RoleType.h"
#include "Player.h"
#include "MapRoleMgr.h"
#include "TeamMgr.h"
#include "Map.h"
#include "CNetManager.h"

int TeamData::AddMember(Player* player)
{
	if (nullptr == player) return ERR_TEAM_NO_PLAYER;
	if (mMemberList.size() > MAX_TEAM_NUM)return ERR_TEAM_FULL;

	auto& briefInfo = player->GetRoleBriefInfo();

    for (const auto &member : mMemberList)
        if (member.guid == briefInfo.guid)
            return ERR_TEAM_JOIN_TIME;

	TEAM_MEMBER mem;
	mem.gender = briefInfo.gender;
	mem.guid = briefInfo.guid;
	mem.head = briefInfo.head;
	mem.is_online = 1;
	mem.job = briefInfo.job;
	mem.level = briefInfo.level;
	mem.map_code = player->GetMapCode();
	mem.x = player->GetRolePosX();
	mem.y = player->GetRolePosY();
	strcpy(mem.map_name, player->GetCurMapKeyName().c_str());
	strcpy(mem.name, briefInfo.name);

	mMemberList.push_back(mem);
	return ERR_OK;
}

void TeamData::RemoveMember(uint64_t id)
{
	for (auto it = mMemberList.begin(); it != mMemberList.end();++it) {
		if (it->guid == id) {
			mMemberList.erase(it);
			return;
		}
	}
}

TEAM_MEMBER* TeamData::FindMember(uint64_t id)
{
	for (auto& mem : mMemberList) {
		if (mem.guid == id) return &mem;
	}
	return nullptr;
}

TEAM_MEMBER* TeamData::FindMember(const std::string& name)
{
	for (auto& mem : mMemberList) {
		if (mem.name == name) return &mem;
	}
	return nullptr;
}

TEAM_MEMBER* TeamData::FindMemberNotLeader(void)
{
	for (auto& mem : mMemberList) {
		if (mem.guid != mLeaderGUID) return &mem;
	}
	return nullptr;
}

IMPL_SINGLETON(TeamMgr)

TeamMgr::TeamMgr(){}

TeamMgr::~TeamMgr()
{
	for (auto it = mTeamMap.begin(); it != mTeamMap.end(); ++it) {
		SAFE_RELEASE(it->second);
	}
	mTeamMap.clear();
}

TeamData* TeamMgr::CreateTeam()
{
	SAFE_BEGIN_EX;
	auto teamGUID = GenerateObjID(E_OBJ_TEAM, ConfigInfo::GetInstance());
	TeamData* team = new TeamData();
	team->mGUID = teamGUID;
	team->mPermission = 1;
	mTeamMap[teamGUID] = team;
	return team;
	SAFE_END_EX(nullptr);
}

void TeamMgr::RemoveTeam(uint64_t teamGUID)
{
	auto team = FindTeam(teamGUID);
	if (nullptr == team) {
		LOG_ERROR("team not exist. teamGUID:%" PRIu64, teamGUID);
		return;
	}

	SAFE_RELEASE(team);
	mTeamMap.erase(teamGUID);
}

TeamData* TeamMgr::FindTeam(uint64_t teamID)
{
	auto it = mTeamMap.find(teamID);
	if ( it != mTeamMap.end())
		return it->second;
	return nullptr;
}

void TeamMgr::ChangeMemberNameInfo(uint64_t guid, const std::string& name)
{
	for (auto i : mTeamMap) {
		if (!i.second)continue;
		if (i.second->mLeaderGUID == guid) {
			i.second->mLeaderName = name;
		}
		auto member = i.second->FindMember(guid);
		if (!member)continue;
		strcpy_s(member->name, _countof(member->name), name);
	}
}



TeamDataMgr::TeamDataMgr(Player* player) :m_player(player)
{
	assert(m_player != nullptr);
}

TeamDataMgr::~TeamDataMgr()
{

}


CLuaObject TeamDataMgr::GetTeamInfo(void)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return NewLuaObj();

	auto params = NewLuaObj();
	int i = 0;
	auto  team_info = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr != team_info) {
		params[++i] = (team_info->mLeaderGUID == m_player->GetGUID()) ? 1 : 0;
		for (auto& mem : team_info->mMemberList) {
			params[++i] = mem.name;
		}
	}

	return params;
}

uint16_t TeamDataMgr::GetTeamMemNum(void)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return 0;

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr != team) {
		return team->mMemberList.size();
	}
	return 0;
}

std::string TeamDataMgr::GetTeamGuid()
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return "";

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr != team) {
		return to_string(team->mGUID);
	}
	return "";
}

void TeamDataMgr::HandleTeamOperation(uint8_t operation, const string& content)
{
	switch (operation) {
	case 1: HandleTeamCreate(); break;
	case 2: HandleTeamDisMiss(); break;//解散
	case 3: HandleTeamArround(); break;
	case 4:	HandleTransferTeamLeader(content); break;//转移队长
	default: break;
	}
}

void TeamDataMgr::HandleTeamLeave(void)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;
	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr == team) {
		return;
	}

	if (team->mMemberList.size() == 1) {
		HandleTeamDisMiss();
		return;
	}

	if (team->mLeaderGUID == m_player->GetGUID()) {
		auto mem = team->FindMemberNotLeader();
		if (nullptr != mem) {
			HandleTransferTeamLeader(mem->name);
		}
	}

	SendTeamLeaveNtf(m_player->GetGUID(), 2);
	team->RemoveMember(m_player->GetGUID());
	roleTeam->Clear();
	//SendTeamInfoNtf();
}

//玩家处理队长的组队邀请
void TeamDataMgr::HandleTeamInviteRsp(uint8_t accept, const string& inviter_name)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;
	//队长
	auto inviter_player = MapRoleMgr::GetInstance()->GetPlayerByName(inviter_name);
	if (nullptr == inviter_player) {
		LOG_ERROR("inviter_player error!");
		m_player->SendErrorAck(ERR_TEAM_TARGET_LEADER_OFFLINE);
		return;
	}

	if (!accept) {
		inviter_player->SendErrorAck(ERR_TEAM_REFUSE);
		return;
	}

	auto team_info = TeamMgr::GetInstance()->FindTeam(inviter_player->GetRoleTeam()->GetTeamGUID());
	if (nullptr == team_info) {
		// 如果没有队伍 则说明邀请者的队伍已销毁
		m_player->SendErrorAck(ERR_TEAM_INVITE_EXPIRE);
		return;
		//team_info = TeamMgr::GetInstance()->CreateTeam();
		//if (nullptr == team_info) {
		//	LOG_ERROR("CreateTeam error!");
		//	return;
		//}

		//team_info->mLeaderGUID = inviter_player->GetGUID();
		//team_info->mLeaderName = inviter_name;
		//team_info->AddMember(inviter_player);
		//inviter_player->GetRoleTeam()->SetTeamGUID(team_info->mGUID);
	}

	if (team_info->AddMember(m_player) != ERR_OK) {
		m_player->SendErrorAck(ERR_TEAM_FULL);
		return;
	};
	roleTeam->SetTeamGUID(team_info->mGUID);
	SendTeamInfoNtf();
}

//申请加入别人的队伍
void TeamDataMgr::HandleTeamJoin(const string& joiner_name)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;

	auto leader = MapRoleMgr::GetInstance()->GetPlayerByName(joiner_name);//对方队长
	if (leader == nullptr) {
		LOG_ERROR("joiner_player is not exist!");
		m_player->SendErrorAck(ERR_TEAM_TARGET_LEADER_OFFLINE);
		return;
	}

	//被申请者是否允许组队
	auto permit = leader->GetRoleProp(role_team_switch);
	if (0 >= permit) {
		LOG_ERROR("joiner is not permit!");
		m_player->SendErrorAck(ERR_TEAM_SWITCH_REFUSE);
		return;
	}

	// 邀请者队伍已满
	auto  tarTeam = TeamMgr::GetInstance()->FindTeam(leader->GetRoleTeam()->GetTeamGUID());
	if (tarTeam == nullptr) {
		LOG_ERROR("team target is not exist!");
		m_player->SendErrorAck(ERR_TEAM_TARGET_NO_TEAM);
		return;
	}

	if (tarTeam->mMemberList.size() > MAX_TEAM_NUM)
	{
		LOG_ERROR("team is full yet!");
		m_player->SendErrorAck(ERR_TEAM_FULL);
		return;
	}

	auto myTeam = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (myTeam != nullptr)
	{
		LOG_ERROR("joiner_player is  exist yet!");
		return;
	}

	ProtoMS_TeamJoinNtf ntf;
	strcpy_s(ntf.joiner, _countof(ntf.joiner), m_player->GetName().c_str());
	ntf.session_id = leader->GetClSessionID();
	SendDataBySessionID(leader->GetGsSessionID(), ntf);//BY SESSID!
}
//队长处理别人的入队申请
void TeamDataMgr::HandleTeamJoinRsp(uint8_t accept, const string& joiner_name)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr == team) {
		LOG_ERROR("team not exist");
		return;
	}

	if (team->mLeaderGUID != m_player->GetGUID()) {
		m_player->SendErrorAck(ERR_TEAM_NO_RIGHT);
		return;
	}

	auto joiner_player = MapRoleMgr::GetInstance()->GetPlayerByName(joiner_name);
	if (nullptr == joiner_player) {
		m_player->SendErrorAck(ERR_TEAM_NO_PLAYER);
		return;
	}

	if (!accept) {
		joiner_player->SendErrorAck(ERR_TEAM_JOIN_REFUSE);
		return;
	}

	auto ret = team->AddMember(joiner_player);
	if (ret != ERR_OK) {
		m_player->SendErrorAck(ret);
		return;
	}
	joiner_player->GetRoleTeam()->SetTeamGUID(team->mGUID);

	SendTeamInfoNtf();
}

void TeamDataMgr::HandleTeamKick(const string& kick_name)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;
	if (m_player->GetName() == kick_name) return;//自己不能踢自己

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr == team) return;

	if (team->mLeaderGUID != m_player->GetGUID()) {
		m_player->SendErrorAck(ERR_TEAM_NO_RIGHT);
		return;
	}

	if (nullptr == team->FindMember(kick_name)) {
		m_player->SendErrorAck(ERR_TEAM_NO_PLAYER);
		return;
	}

	auto player = MapRoleMgr::GetInstance()->GetPlayerByName(kick_name);
	if (nullptr == player) {
		m_player->SendErrorAck(ERR_TEAM_NO_PLAYER);
		return;
	}
	SendTeamLeaveNtf(player->GetGUID(), 1);
	team->RemoveMember(player->GetGUID());
	player->GetRoleTeam()->Clear();
	//SendTeamInfoNtf();
}
//队长邀请别人组队
void TeamDataMgr::HandleTeamInvite(const string& invitee_name)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;
	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr != team && team->mMemberList.size() == 15) {
		m_player->SendErrorAck(ERR_TEAM_FULL);
		return;
	}

	// 没有组队则创建队伍
	if (nullptr == team) {
		HandleTeamCreate();
	}

	//被邀请者是否在线或者存在
	auto player = MapRoleMgr::GetInstance()->GetPlayerByName(invitee_name);
	if (nullptr == player) {
		LOG_ERROR("invitee is not exist!");
		m_player->SendErrorAck(ERR_TEAM_NO_PLAYER);
		return;
	}

	//被邀请者是否允许组队
	auto permit = player->GetRoleProp(role_team_switch);
	if (0 >= permit) {
		LOG_ERROR("invitee is not permit!");
		m_player->SendErrorAck(ERR_TEAM_SWITCH_REFUSE);
		return;
	}

	//被邀请者是否已经组队
	auto playerTeam = TeamMgr::GetInstance()->FindTeam(player->GetRoleTeam()->GetTeamGUID());
	if (nullptr != playerTeam) {
		LOG_ERROR("invitee has team yet!");
		m_player->SendErrorAck(ERR_TEAM_TARGET_HAS_TEAM);
		return;
	}

	//邀请者地图是否允许
	if (nullptr == m_player->GetCurMap() || !m_player->GetCurMap()->GetMapConfig()->Team) {
		m_player->SendErrorAck(ERR_TEAM_MAP);
		return;
	}

	//被邀请者地图是否允许
	if (nullptr == player->GetCurMap() || !player->GetCurMap()->GetMapConfig()->Team) {
		m_player->SendErrorAck(ERR_TEAM_TARGET_MAP);
		return;
	}

	SendTeamInviteNtf(team, player);
}



void TeamDataMgr::HandleTeamArround(void)
{
	ProtoMS_GetAroundTeamAck ack;
	ack.list_size = 0;
	ack.session_id = m_player->GetClSessionID();
	auto& teamMap = TeamMgr::GetInstance()->GetTeamMap();
	auto curCount = 0;
	for (auto& team : teamMap) {
		for (auto& mem : team.second->mMemberList) {
			if (team.second->mLeaderGUID == mem.guid) {
				ack.list_data[ack.list_size] = mem;
				break;
			}
		}

		if (++ack.list_size == _countof(ack.list_data) || ++curCount == teamMap.size()) {
			SendDataBySessionID(m_player->GetGsSessionID(), ack);
			ack.list_size = 0;
		}
	}
}











/////////////////////////////////////
void TeamDataMgr::HandleTeamCreate(void)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr != team) {
		LOG_ERROR("Team already exist,Create team failed!");
		m_player->SendErrorAck(ERR_TEAM_ALREADY_EXIST);
		return;
	}

	//地图是否允许
	if (nullptr == m_player->GetCurMap() || !m_player->GetCurMap()->GetMapConfig()->Team) {
		m_player->SendErrorAck(ERR_TEAM_MAP);
		return;
	}

	team = TeamMgr::GetInstance()->CreateTeam();
	if (nullptr == team) {
		LOG_ERROR("create team failed.");
		return;
	}

	team->mLeaderGUID = m_player->GetGUID();
	team->mLeaderName = m_player->GetName();
	team->AddMember(m_player);

	roleTeam->SetTeamGUID(team->mGUID);
	SendTeamInfoNtf();
}

void TeamDataMgr::HandleTeamDisMiss(void)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr == team) {
		LOG_ERROR("player not in any team. playerGUID:%" PRIu64 ", teamGUID:%" PRIu64, m_player->GetGUID(), roleTeam->GetTeamGUID());
		return;
	}

	if (m_player->GetGUID() != team->mLeaderGUID) {
		LOG_ERROR("only team leader allow dismiss team. playerGUID:%" PRIu64 ", teamGUID:%" PRIu64 ", teamGUID:%" PRIu64,
			m_player->GetGUID(), team->mGUID, team->mLeaderGUID);
		m_player->SendErrorAck(ERR_TEAM_NO_RIGHT);
		return;
	}

	ProtoMS_TeamLeaveNtf ntf;
	for (auto& member : team->mMemberList) {
		auto player = MapRoleMgr::GetInstance()->GetPlayerByName(member.name);
		if (nullptr == player) continue;
		ntf.player_guid = player->GetGUID();
		ntf.type = 0;
		ntf.session_id = player->GetClSessionID();
		SendDataBySessionID(player->GetGsSessionID(), ntf);//BY SESSID!
	}

	TeamMgr::GetInstance()->RemoveTeam(team->mGUID);
	roleTeam->Clear();
}

void TeamDataMgr::HandleTransferTeamLeader(const string& name)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr == team) {
		LOG_ERROR("team not exist.");
		return;
	}

	if (team->mLeaderGUID != m_player->GetGUID()) {
		LOG_ERROR("Only team leader allow transfer leader.");
		m_player->SendErrorAck(ERR_TEAM_NO_RIGHT);
		return;
	}

	auto tarPlayer = MapRoleMgr::GetInstance()->GetPlayerByName(name);
	if (nullptr == tarPlayer) {
		LOG_ERROR("target player is not exist!");
		m_player->SendErrorAck(ERR_TEAM_NO_PLAYER);
		return;
	}

	auto teamMember = team->FindMember(name);
	if (nullptr == teamMember) {
		LOG_ERROR("team member not exist. name:%s", name.c_str());
		m_player->SendErrorAck(ERR_TEAM_NO_PLAYER);
		return;
	}

	team->mLeaderGUID = tarPlayer->GetGUID();
	team->mLeaderName = tarPlayer->GetName();

	SendTeamLeaderNtf();
}





void TeamDataMgr::SendTeamInfoNtf()
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;
	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (nullptr == team) return;

	ProtoMS_TeamNtf ntf;
	ntf.info.guid = team->mGUID;
	ntf.info.leader_guid = team->mLeaderGUID;
	ntf.info.member_num = 0;
	ntf.info.permission = team->mPermission;
	strcpy_s(ntf.info.leader_name, _countof(ntf.info.leader_name), team->mLeaderName.c_str());

	for (auto& mem : team->mMemberList) {
		ntf.info.members[ntf.info.member_num++] = mem;
		if (ntf.info.member_num >= _countof(ntf.info.members)) break;//只发前100个，后面优化
	}

	for (auto& mem : team->mMemberList) {
		auto player = MapRoleMgr::GetInstance()->GetPlayerByName(mem.name);
		if (nullptr == player) continue;
		ntf.gatesession_id = player->GetGsSessionID();
		ntf.session_id = player->GetClSessionID();
		SendDataBySessionID(ntf.gatesession_id, ntf);//BY SESSID!
	}
}


void TeamDataMgr::SendTeamLeaveNtf(uint64_t id, unsigned char type)
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;
	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (team == nullptr) return;

	ProtoMS_TeamLeaveNtf ntf;
	ntf.player_guid = id;
	ntf.type = type;

	for (auto& mem : team->mMemberList) {
		auto player = MapRoleMgr::GetInstance()->GetPlayerByName(mem.name);
		if (nullptr == player) continue;
		ntf.session_id = player->GetClSessionID();
		SendDataBySessionID(player->GetGsSessionID(), ntf);
	}
}

void TeamDataMgr::SendTeamLeaderNtf()
{
	auto roleTeam = m_player->GetRoleTeam();
	if (!roleTeam) return;

	auto team = TeamMgr::GetInstance()->FindTeam(roleTeam->GetTeamGUID());
	if (team == nullptr) return;

	ProtoMS_TeamLeaderNtf ntf;
	ntf.leader_guid = team->mLeaderGUID;

	for (auto& mem : team->mMemberList) {
		auto player = MapRoleMgr::GetInstance()->GetPlayerByName(mem.name);
		if (nullptr == player) continue;
		ntf.session_id = player->GetClSessionID();
		SendDataBySessionID(player->GetGsSessionID(), ntf);
	}
}

void TeamDataMgr::SendTeamInviteNtf(TeamData* team_info, Player* player)
{
	if (!player) return;

	ProtoMS_TeamInviteNtf invite_ntf;
	invite_ntf.exist = team_info == nullptr ? 0 : 1;
	invite_ntf.num = team_info == nullptr ? 0 : 1;
	memcpy(invite_ntf.inviter_name, m_player->GetName().c_str(), m_player->GetName().size() + 1);
	invite_ntf.session_id = player->GetClSessionID();
	if (team_info != nullptr) {
		invite_ntf.info[0].guid = team_info->mGUID;
		invite_ntf.info[0].leader_guid = team_info->mLeaderGUID;
		strcpy_s(invite_ntf.info[0].leader_name, _countof(invite_ntf.info[0].leader_name), team_info->mLeaderName.c_str());
		invite_ntf.info[0].member_num = 0;
		invite_ntf.info[0].permission = team_info->mPermission;
		int i = 0;
		for (auto& mem : team_info->mMemberList) {
			invite_ntf.info[0].members[invite_ntf.info[0].member_num++] = mem;
			if (invite_ntf.info[0].member_num == _countof(invite_ntf.info[0].members))break;
		}
	}

	SendDataBySessionID(player->GetGsSessionID(), invite_ntf);//BY SESSID!
}
