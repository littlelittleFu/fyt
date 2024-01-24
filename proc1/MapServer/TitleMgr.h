#pragma once
#include<map>
#include<string>
#include"Player.h"
#include"title_table.hpp"

enum timeType {
    time_type_relation = 1,
    time_type_abs,
};

enum titleWear
{
    title_unwear = 0,
    title_wear = 1,
};

enum titleSubType
{
    titile_subtype_no_wear = 0,
    title_subtype_wear  =1,
};

enum titlePropUpdateType 
{
    title_prop_decrease = 0,
    title_prop_increase = 1,
};

class Player;
class TitleDataMgr 
{
public:

    TitleDataMgr(Player* player);
    ~TitleDataMgr();
    void Init();
    void Update(int delta);
    bool AddTitle(DATA::Title* title);
    bool AddTitle(uint32_t id);
    bool AddTitle(const std::string& name);
    bool DelTitle(uint32_t id);
    bool DelTitle(const std::string& name);
    bool WearTitle(uint32_t id);
    bool WearTitle(const std::string& name);
    void UnWearTitle(uint32_t id);
    void UnWearTitle(const std::string& name);
    bool IsExpired(SP_TITLE_INFO info);
    bool IsExpired(TITLE_INFO* info);
    bool IsHasTitle(uint32_t id);
    bool IsHasTitle(const std::string& name);
    bool IsCanAdd(uint32_t id);

    void UpdateTitleProp(uint32_t id, DATA::Title* cfg, uint8_t updateType);
    void TriggerEffect(uint32_t id, DATA::Title* cfg);
    void UnTriggerEffect(uint32_t id, DATA::Title* cfg);

    void SendAddTitleToClient(SP_TITLE_INFO info);
    void SendAddTitleToCS(SP_TITLE_INFO info);
    void SendDelTitleToClient(uint32_t id);
    void SendDelTitleToCS(uint16_t num, uint32_t* id);
    void SendWearTypeTitleToCS(uint32_t id, uint16_t isWear);
    void SendWearNtf(uint32_t id);
    void SendUnWearNtf(uint32_t id);

    void GetTitleInfoFromDB(uint16_t num, TITLE_INFO* data);
    void SendTitleListInfoToGS();

    std::map<uint32_t, SP_TITLE_INFO>& GetTitleList() { return mTitleList; };
private:
    Player* mMaster;
    std::map<uint32_t, SP_TITLE_INFO>mTitleList;
};