#pragma once
#include "LuaScript.h"
#include <unordered_set>
#include "Globle.h"

#include "MapMgr.h"
#include "MapRoleMgr.h"

class CLuaLib
{
	DECL_SINGLETON(CLuaLib)

public:
    void AddTrigger(uint64_t objGUID, uint32_t eventID, const::std::string& callBack);
	void AddTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack);

    void RemoveTrigger(uint64_t objGUID, uint32_t eventID, const::std::string& callBack);
	void RemoveTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack);

    bool IsHaveEvent(uint32_t eventID);

    template <typename... Args>
    void TriggerEvent(uint32_t eventID, const Args&... args)
    {
        Globle::GetInstance()->TriggerEvent(eventID, args...);
    }

    template <typename... Args>
    void TriggerEvent(Role *role, uint32_t eventID, const Args&... args)
    {
        if (role) {

            //��ɫ���ȴ���
            role->TriggerEvent(eventID, args...);

            //����ǵ�ͼ
            auto *map = role->GetCurMap();
            if (map) {
                map->TriggerEvent(eventID, args...);
            }
        }

        //�����ϵͳ
        Globle::GetInstance()->TriggerEvent(eventID, args...);
    }

    template <typename... Args>
    void TriggerEvent(Map *map, uint32_t eventID, const Args&... args)
    {
        if (map) {

            //��ɫ���ȴ���
            //map->ApplyFuncToAllRoles([&](Role *role){ role->TriggerEvent(eventID, args...); });

            //����ǵ�ͼ
            map->TriggerEvent(eventID, args...);
        }

        //�����ϵͳ
        Globle::GetInstance()->TriggerEvent(eventID, args...);
    }

    template <typename T, typename... Args>
    void TriggerEventRet(T& ret, uint32_t eventID, const Args&... args)
    {
        Globle::GetInstance()->TriggerEventRet<T>(ret, eventID, args...);
    }

	template <typename T, typename... Args>
	void TriggerEventRet(T& ret, Role *role, uint32_t eventID, const Args&... args)
	{
        if (role) {

		    //��ɫ���ȴ���
		    if (!role->TriggerEventRet<T>(ret, eventID, args...)) return;

		    //����ǵ�ͼ
            auto *map = role->GetCurMap();
            if (map) {
		        if (!map->TriggerEventRet<T>(ret, eventID, args...)) return;
            }
        }

		//�����ϵͳ
		Globle::GetInstance()->TriggerEventRet<T>(ret, eventID, args...);
	}

    template <typename T, typename... Args>
    void TriggerEventRet(T& ret, Map *map, uint32_t eventID, const Args&... args)
    {
        if (map) {

            //��ɫ���ȴ���
            bool handled = false;
            map->ApplyFuncToAllRoles([&](Role *role){
                if (handled) return;
                if (!role->TriggerEventRet<T>(ret, eventID, args...)) handled = true;
            });

            if (handled) return;

            //����ǵ�ͼ
            if (!map->TriggerEventRet<T>(ret, eventID, args...)) return;
        }

        //�����ϵͳ
        Globle::GetInstance()->TriggerEventRet<T>(ret, eventID, args...);
    }
};

#define TRIGGER_EVENT CLuaLib::GetInstance()->TriggerEvent
#define TRIGGER_EVENT_RET CLuaLib::GetInstance()->TriggerEventRet
#define ADD_TRIGGER CLuaLib::GetInstance()->AddTrigger
