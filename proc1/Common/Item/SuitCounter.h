#pragma once

class Role;

class Suit
{
public:
                    Suit(Role *role, uint16_t suitID) : mRole(role), mSuitID(suitID) {}
    virtual        ~Suit() = default;

    virtual void    OnLoadEquip(uint16_t templateID) = 0;
    virtual void    OnUnloadEquip(uint16_t templateID) = 0;

protected:
    Role           *GetRole() { return mRole; }
    uint16_t        GetSuitID() { return mSuitID; }

    void            IncSuitNum();
    void            DecSuitNum();
    uint16_t        GetSuitNum() { return mSuitNum; }

    void            OnIncSuitNum();
    void            OnDecSuitNum();

private:
    Role           *mRole       = nullptr;
    uint16_t        mSuitID     = 0;
    uint16_t        mSuitNum    = 0;
};

class SuitByNum : public Suit
{
public:
                    SuitByNum(Role *role, uint16_t suitID) : Suit(role, suitID) {}

    void            OnLoadEquip(uint16_t templateID) override { IncSuitNum(); }
    void            OnUnloadEquip(uint16_t templateID) override { DecSuitNum(); }
};

class SuitBySubType : public Suit
{
    using ItemNumMap = std::map<uint16_t, uint16_t>;        // sub type -> num

public:
                    SuitBySubType(Role *role, uint16_t suitID);

    void            OnLoadEquip(uint16_t templateID) override;
    void            OnUnloadEquip(uint16_t templateID) override;

private:
    void            Init();
    void            CheckSuitNum();

private:
    ItemNumMap      mItemNumMap;
};


class SuitByTemplateID : public Suit
{
    using ItemNumMap = std::map<uint16_t, uint16_t>;        // template id -> num

public:
                    SuitByTemplateID(Role *role, uint16_t suitID);

    void            OnLoadEquip(uint16_t templateID) override;
    void            OnUnloadEquip(uint16_t templateID) override;

private:
    void            Init();
    void            CheckSuitNum();

private:
    ItemNumMap      mItemNumMap;
};

class SuitCounter
{
    using SuitPtr = std::unique_ptr<Suit>;
    using SuitMap = std::map<uint16_t, SuitPtr>;

public:
                    SuitCounter(Role *role) : mRole(role) {}

    void            OnLoadEquip(uint16_t templateID);
    void            OnUnloadEquip(uint16_t templateID);
    void            ClearAllSuit() { mSuitMap.clear(); }

private:
    SuitMap         mSuitMap;
    Role           *mRole       = nullptr;
};