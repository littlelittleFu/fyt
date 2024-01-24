#pragma once

#include "Map.h"
#include <string>
#include <unordered_map>
#include "ProtoCS.h"

typedef std::unordered_map<std::string, Map*> MapList;
typedef std::map<uint64_t, DgnMap*> DgnMapList;

class MapMgr
{
	DECL_SINGLETON(MapMgr);
	using       Func = std::function<void(Role*)>;

public:
	bool Init();

	void ApplyFuncToAllMap(Func f);
	Map* CreateMap(const std::string& mapName);
	void DestroyMap(const std::string& mapName);
	Map* FindMap(const std::string& mapName);
    Map* FindMapByID(uint16_t mapID);
    Map* FindMapByGUID(uint64_t mapGUID);
	void Update(int delta);
	void OnRecv_EnterMSReq(ProtoCS_EnterMSReq& req);
	void OnRecv_EnterMSNtf(ProtoCS_EnterMSNtf& ntf);
    const std::string & GetScriptName() { return mScriptName; }

	// sDgnMapNameָ����keyName,��������Ψһ��ʶһ����ͼ������
	// ��������
	std::string CreateMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, bool delayInit, uint32_t exitTime, CLuaObject call_back);
	// ���ٸ���
	uint32_t	DestroyMulDgnMap(const std::string& sDgnMapGuid);
	// ������id����Ұ�
	uint32_t	BindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapGuid, const std::string& sPlayerGuid);
	// ��ҽ��ǰ����id
	uint32_t	UnBindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid);
	// ��ҽ��븱��
	uint32_t	EnteryMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, uint16_t posX, uint16_t posY, const log_params& lp);
	// ����˳�����
	uint32_t	ExitMulDgnMap(const std::string& sDgnMapGuid, const std::string& sPlayerGuid);
	// ��ȡ��Ұ󶨵ĸ���id
	std::string	GetMulDgnGuidByPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid);
private:
	// ���ݸ���id���ظ���ʵ��
	DgnMap*		FindMulDgnMapByDgnGuid(uint64_t dgnGuid);
	uint32_t	DestroyMulDgnMap(uint64_t dgnGuid);
protected:
	MapList 	mMapList;
	DgnMapList 	mDgnMapList;
	std::string mScriptName;
};