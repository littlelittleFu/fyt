#pragma once
#include "Type.h"
#include "CListener.h"
#include <string>
#include <vector>
#include <map>
#include "ISession.h"
#include <functional>
#include "CConnectCtrl.h"
#include "CLogger.h"


class CNetManager
{
private:
	CNetManager();
	~CNetManager();

public:
	void Init(uint32_t nThreadNum);
	void UnInit();
	bool AddListener(std::string _Ip, UINT _Port, INT _Type, INT _Param = 0, bool _Encrypt = false);
	bool AddConnector(std::string _Ip, UINT _Port, INT _Type, INT _Param = 0, bool _Encrypt = false);

	void SetLogFunction(std::function<void(const char*,int)> _Func);

	void RemoveSession(ISession* _pSession);
	ISession* GetSessionByType(INT _Type);
	ISession* GetSessionByID(UINT _ID);
    const ISessionMap* GetAllSessionByType(INT type);

	void OnUpdate(UINT _Delta);

    void SetLogLevel(int32_t logLevel);
    void LogDebugInfo(DEBUG_DATA& debugData);

	DECLARE_INSTANCE(CNetManager);

private:
	std::vector<CListener*> m_Listeners;
	CConnectCtrl m_ConnectCtrl;
};


template <typename T>
bool SendDataBySessionType(int nSessionType, T &data, bool all = false)
{
    if (all) {
        auto *sessions = CNetManager::GetInstance()->GetAllSessionByType(nSessionType);
        if (!sessions) {
            LOG_ERROR("sessions is NULL. nSessionType: %d, data type: %s",
                      nSessionType, typeid(data).name());
            return false;
        }

        bool ret = true;
        for (auto &it : *sessions) {
            if (!it.second) continue;
            if (!it.second->SendPkg((std::remove_const_t<T> *)&data, sizeof(data))) {
                LOG_ERROR("SendPkg failed. Data type: %s", typeid(data).name());
                ret = false;
            }
        }
        return ret;
    }
    else {
        auto *session = CNetManager::GetInstance()->GetSessionByType(nSessionType);
        if (!session) {
            LOG_ERROR("session is NULL. nSessionType: %d, data type: %s",
                      nSessionType, typeid(data).name());
            return false;
        }
        if (!session->SendPkg((std::remove_const_t<T> *)&data, sizeof(data))) {
            LOG_ERROR("SendPkg failed. Data type: %s", typeid(data).name());
            return false;
        }
        return true;
    }
}

template <typename T>
bool SendDataBySessionID(uint32_t nSessionID, T &data, bool candrop = false)
{
    auto *session = CNetManager::GetInstance()->GetSessionByID(nSessionID);
    if (!session) {
        LOG_ERROR("session is NULL. nSessionID: %u, data type: %s",
                  nSessionID, typeid(data).name());
        return false;
    }
    if (!session->SendPkg((std::remove_const_t<T> *)&data, sizeof(data), candrop)) {
        LOG_ERROR("SendPkg failed. Data type: %s", typeid(data).name());
        return false;
    }
    return true;
}

template <typename T>
bool SendDataBySessionID(const std::map<uint32_t, std::vector<uint32_t>> &clsessidsMap,
                         T &data, bool candrop = false)
{
    auto &n = data.clsessnum;
    bool result = true;

    for (const auto &it : clsessidsMap) {
        const auto &gssessid = it.first;
        const auto &clsessids = it.second;

        auto i = 0;
        auto total = clsessids.size();

        while (i < total) {
            n = std::min<uint16_t>(_countof(data.clsessids), total - i);
            std::copy(clsessids.begin() + i, clsessids.begin() + i + n, data.clsessids);
            if (!SendDataBySessionID(gssessid, data, candrop)) result = false;
            i += n;
        }
    }
    return result;
}

inline bool IssueConnectionRequest(const std::string& sIP, uint32_t nPort, int32_t nType, int32_t nParam = 0, bool bEncrypt = false)
{
    return CNetManager::GetInstance()->AddConnector(sIP, nPort, nType, nParam, bEncrypt);
}

inline bool SessionExist(int32_t nSessionType)
{
    return (CNetManager::GetInstance()->GetSessionByType(nSessionType) != nullptr);
}
