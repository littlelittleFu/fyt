#pragma once



#include "Object.h"


class ItemBase : public Object
{
public:
	ItemBase() {};
	ItemBase(const ItemBase*item);
    ItemBase(const ITEM_INFO* item);
	virtual ~ItemBase() {};

    void SetTemplateID(uint32_t tempid) { mTempid = tempid; }
    uint32_t GetTemplateID() const { return mTempid; }

	void SetLife(unsigned int   mount) { mLife = mount; }
	unsigned int    GetLife() const { return mLife; }

    void SetCategory(item_category cat) { mCategory = cat; }
    item_category GetCategory() const{ return mCategory; }

    void SetCustVar(std::string name, std::string value, const uint8_t &type, bool& beDelete);
    void SetCustVar(CUST_VAR& cv);
    const std::string & GetCustVar(const std::string &name, bool& beDelete);
    const CUST_VAR_SP& GetCustVarSP(const std::string& name, bool& beDelete);

    void AddCustVar(CUST_VAR_SP var) { if (var) mCustVars[var->name] = std::move(var); }

    void SetCustVars(CUST_VAR_SP_MAP vars) { mCustVars = std::move(vars); }
    CUST_VAR_SP_MAP & GetCustVars() { return mCustVars; }


    void SetDynAttrs(DYN_ATTRS attrs) { mDynAttrs = std::move(attrs); }
    DYN_ATTRS & GetDynAttrs() { return mDynAttrs; }

    void SetDynAttr(uint16_t index, uint16_t attr, int32_t value);
    DYN_ATTR GetDynAttr(uint16_t index);

protected:
	void InitWithBaseItem(const ItemBase* item);
    void InitWithBaseItemInfo(const ITEM_INFO* item);
    void GenerateBaseItemInfo(ITEM_INFO& item);

protected:
    uint16_t                  mTempid       = 0;
	unsigned int              mLife         = 0; 
    item_category             mCategory     = item_cat_unknown;
    CUST_VAR_SP_MAP           mCustVars;
    DYN_ATTRS                 mDynAttrs;
};


