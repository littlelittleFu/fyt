#pragma once

#include "RoleAction.h"
#include <unordered_set>
#include <functional>

enum {
    attr_ntf_type_none,
    attr_ntf_type_self,
    attr_ntf_type_around,
};
struct Propchange
{
public:
    int32_t nbefore;
    int32_t nafter;
};

struct Propinfo
{
public:
    int32_t type;
    int32_t id;
    int32_t predValue;
    int32_t curValue;
    int32_t changeValue;
};

class RoleAttr : public RoleAction
{
    typedef std::function<int32_t(int32_t, int32_t, bool, Role*, RoleAttr*)> ReCalcFunc;
public:
    RoleAttr(Role* master = nullptr);
    ~RoleAttr();

public:
    void SetRolePos(uint16_t x, uint16_t y, bool raiseEvent = true,bool takeGrid = true);
    void GetRolePos(uint16_t& x, uint16_t& y) { x = PosX; y = PosY; }

    uint16_t GetRolePosX() { return PosX; }
    uint16_t GetRolePosY() { return PosY; }

    void SetRoleDir(uint8_t dir);
    uint8_t GetRoleDir() { return Dir; }

    void SetMoveType(uint8_t type) { MoveType = type; }
    uint8_t GetMoveType() { return MoveType; }

    void SetUpGradeExp(uint64_t exp) { UpGradeExp = exp; }
    uint64_t GetUpGradeExp(void) { return UpGradeExp; }

    const DYN_ATTRS& GetDynAttrs() { return mDynAttrs; }

    void SetDynAttr(uint16_t index, uint16_t attr, int32_t value);
    DYN_ATTR GetDynAttr(uint16_t index);

    bool Init() override;
    void Update(int32_t delta) override;
    void CopyFromOwner(RoleAction* ra) override;
    void CalculateRoleAttr_Base();

    // 32位属性
    int32_t SetRoleProp(int32_t prop, int32_t value);
    int32_t AddRoleProp(int32_t prop, int32_t value);
    int32_t GetRoleProp(int32_t prop);
    // 64位属性
    void SetProp64(int32_t prop, int64_t value, const log_params& lp);
    void AddProp64(int32_t prop, int64_t value, const log_params& lp);
    int64_t GetProp64(int32_t prop);

    void SendPropertyModyNtf();
    void OnRecvRoleDynAttrsList(ROLE_DYN_ATTRS& attrsList);

    void GetListProp(CLuaObject& list, uint16_t type , uint16_t min, uint16_t max);
    void ClearPropertyHistoryMap() { PropertyHistoryMap.clear();};
    void InsterPropertyHistoryMap(int32_t prop, int32_t before, int32_t after);
    void PrintPropertyMap(int32_t prop);
protected:
    void UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue);
    void UpdateOtherStatusByProp64(int32_t prop, int64_t predValue, int64_t curValue);
    int32_t UpdateProp(int32_t prop, int32_t value, bool beSet = true);
    std::pair<int32_t, int32_t> ReCalcProperty(int32_t prop, int32_t value, bool beSet = true);
    // 恢复属性
    void RecoveryProperty(int32_t delta);
    // 检测属性值区间限制
    bool CheckProp32ValueLimit(int32_t prop, int32_t& value, bool beSet = true);
    bool CheckRoleState(int32_t prop);
    // 检测属性键区间限制
    inline static bool CheckProp32KeyRange(int32_t prop);
    inline static bool CheckProp64KeyRange(int32_t prop);

    void CheckNeedRecoverHP(int32_t preValue, int32_t curValue);
    void CheckNeedRecoverMP(int32_t preValue, int32_t curValue);
    void CheckNeedUpdatePK(int32_t preValue, int32_t curValue);
    void CheckNeedUpdate();

    bool PropModified();

    bool NeedNotifyOther(int32_t prop);
    void SendRoleAttrNtfToSelf();
    void SendRoleAttrNtfToOther();
    void SendRoleAttrExtNtfToSelf();

    struct PropVec
    {
    public:
        PropVec(int32_t min, int32_t max) : Min(min), Max(max), High1(Min / 100), High2(Max / 100)
        {
            Prop.resize(max - min, 0);
        }
        bool CheckIn(int32_t prop)
        {
            return Min < prop && prop < Max;
        }
        int32_t& operator[](int32_t prop)
        {
            int16_t high = prop / 100;
            int16_t low = prop % 100;
            uint16_t idx = (high - High1) * 100 + low;
            assert(idx < Prop.size());
            return Prop[idx];
        }
        int32_t Min;
        int32_t Max;
        int16_t High1;
        int16_t High2;
        std::vector<int32_t> Prop;
    };
    struct AllPropVec
    {
        int32_t& operator[](int32_t prop);
        void push_back(PropVec& prop)
        {
            Property.push_back(std::move(prop));
        }
        std::vector<PropVec>    Property;
        int32_t Null = 0;
    };
protected:
    uint16_t        PosX;               //位置X坐标
    uint16_t        PosY;               //位置Y坐标
    uint8_t         Dir;			    //方向
    uint8_t         MoveType;           //移动类型 0=走 1=跑
   
    uint64_t        UpGradeExp;         // 当前等级升级所需经验
    uint32_t        RecoveryIntervalTime;       // 恢复间隔
    int32_t         CurRecoveryInterval;        // 当前

    AllPropVec                  Property;                // 属性集合
    std::vector<int64_t>        Property64;

    std::set<uint16_t>PropertyMody;           // 更新的属性集合
    std::set<uint16_t>PropertyMody64;

    bool                        mDynAttrsMody   = false;
    DYN_ATTRS                   mDynAttrs;
    DYN_ATTRS                   mTmpDynAttrs;

    bool                        mNeedRecoverHP  = false;
    bool                        mNeedRecoverMP  = false;

    static std::list<std::pair<int32_t, int32_t>> AllPropList;
    std::map<int32_t, std::map<int32_t, Propinfo>> PropertyHistoryMap;
};
