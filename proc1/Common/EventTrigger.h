#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>

class EventTrigger
{
public:
	void AddTrigger(uint32_t eventID, const std::string& callBack)
	{
		mEventMap[eventID].insert(callBack);
	}

	void RemoveTrigger(uint32_t eventID, const std::string& callBack)
	{
		mInvalidEventMap[eventID].insert(callBack);
        OnRemoveTrigger();
	}

    virtual void OnRemoveTrigger() {}

	bool IsHaveEvent(uint32_t eventID)
	{
		if (mEventMap.find(eventID) == mEventMap.end())
			return false;
		return true;
	}

	template <typename... Args>
	void TriggerEvent(uint32_t eventID, const Args&... p1)
	{
		if (mEventMap.find(eventID) == mEventMap.end()) return;
		for (auto& callBack : mEventMap[eventID]) {
            LuaBindCallVoid(callBack, p1...);
		}
	}

	//������ֵ�Ļص�������true��ʾ���������¼���false��ʾ�¼��Ѵ�����Ҫ�������ݡ�ͬһ���¼�ֻ�����һ���ص�
	template <typename T, typename... Args>
	bool TriggerEventRet(T& ret, uint32_t eventID, const Args&... p1)
	{
		if (mEventMap.find(eventID) != mEventMap.end()) {
			for (auto& callBack : mEventMap[eventID]) {
                LuaBindCallRet(ret, callBack, p1...);
				return false;
			}
		}
		return true;
	}

protected:
	void DoRemoveTrigger(uint32_t eventID, const std::string& callBack)
	{
		if (mEventMap.find(eventID) == mEventMap.end()) return;
		mEventMap[eventID].erase(callBack);
		if (mEventMap[eventID].size() == 0) mEventMap.erase(eventID);
	}

	void UpdateEventMap()
	{
		if (!mInvalidEventMap.empty()) {
			for (auto& it : mInvalidEventMap) {
				for (auto cb : it.second) {
					DoRemoveTrigger(it.first, cb);
				}
			}
			mInvalidEventMap.clear();
		}
	}

protected:
	std::unordered_map<uint32_t, std::unordered_set<std::string>> mEventMap;
	std::unordered_map<uint32_t, std::unordered_set<std::string>> mInvalidEventMap;
};