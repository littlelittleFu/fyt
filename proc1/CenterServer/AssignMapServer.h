#pragma once
#include <unordered_map>


struct MapServer
{
	uint32_t  mSessionID;      // 中心服务器与地图服务器之间的session id
	std::string m_Ip;
	uint32_t m_Port;
};

//ssignMapServer 不仅负责调度map server（虽然目前框架只有一台map server，考虑支持后续多台map server的架构），而且可以决定玩家进入地图！
class AssignMapServer
{
	DECL_SINGLETON(AssignMapServer);
public:


	MapServer& GetMapServerById(uint16_t id);
	void  UpdateMapServerTableById(const uint16_t & id, MapServer mapserver);
	const std::unordered_map<uint16_t, MapServer> &  GetMapServerTable() const { return mMapServerTable; }
private:
	AssignMapServer() {};
	~AssignMapServer() {};
	std::unordered_map<uint16_t, MapServer> mMapServerTable;//维护一张表，《地图ID，map server》
};


