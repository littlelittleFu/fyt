#include "stdafx.h"
#include "AssignMapServer.h"

IMPL_SINGLETON(AssignMapServer);
MapServer& AssignMapServer::GetMapServerById(uint16_t id)
{
	/*if (mMapServerTable.empty()) {
		LOG_WARN("there is no available map server exist!");
		return;
	}*/
	return mMapServerTable[id];
}


void AssignMapServer::UpdateMapServerTableById(const uint16_t &id, MapServer new_ms)
{
	if (mMapServerTable.empty()) {
		LOG_WARN("there is no available map server exist!");
		//return;
	}

	auto iter = mMapServerTable.find(id);
	if (mMapServerTable.end() == iter) {
		mMapServerTable.emplace(id, new_ms);
		return;
	}
	mMapServerTable[id] = new_ms;

}
