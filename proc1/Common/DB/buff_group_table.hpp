/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once

class CsvHelper;
// 同时也是优先级,值越高,优先处理
enum BuffGroupRelationOutreach
{
    BGRO_0 = 0,  // 共存
    BGRO_1,      // 替换(组1BUFF替换组2BUFF)
    BGRO_2,      // 抵消(组1BUFF抵消已有BUFF，抵消后两个buff组都消失)
    BGRO_3,      // 忽略(组1BUFF添加后，组2BUFF无法被添加)
};

namespace DATA
{
	struct BuffGroup
	{
        int32_t             Id = 0;							/// 编号
        int32_t             GroupId1 = 0;                   /// 组1Id
        int32_t             GroupId2 = 0;                   /// 组2Id
        int32_t             GroupRelation = 0;			    /// 组间关系BuffGroupRelationOutreach
	};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif
    struct GroupIdKey
    {
        int32_t             GroupId1 = 0;
        int32_t             GroupId2 = 0;
        GroupIdKey(int32_t g1,int32_t g2) :GroupId1(g1), GroupId2(g2)
        {}
        bool operator==(const GroupIdKey& a)
        {
            return (a.GroupId1 == GroupId1 && a.GroupId2 == GroupId2) ||
                (a.GroupId1 == GroupId2 && a.GroupId2 == GroupId1);
        }
        bool operator<(const GroupIdKey& a) const
        {
            if (GroupId1 < a.GroupId1)
                return true;
            if (GroupId1 == a.GroupId1)
            {
                if (GroupId2 < a.GroupId2)
                    return true;
            }
            return false;
        }
    };
	class BuffGroupConfig  : public TableBase<BuffGroup>
	{
		DECLARE_SINGLETON(BuffGroupConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "GroupId1", row->GroupId1, 0);
            CELL_VALUE(InRow, "GroupId2", row->GroupId2, 0);
            CELL_VALUE(InRow, "GroupRelation", row->GroupRelation, 0);
        }
        virtual bool CheckValid(TItem *row) override
        {
            if (row->GroupId1 == row->GroupId2) return false;
            return true;
        }
        virtual void FillMapping(TItem* row) override
        {
            if (row->GroupId1 == row->GroupId2) return;

            auto *t0 = &key_mappings_;
            GroupIdKey key(row->GroupId1, row->GroupId2);

            if (t0->find(key) == t0->end())
            {
                TItem*& t1 = (*t0)[key];
                t1 = row;
            }
        }
        TItem* GetByGroupIdKey(const GroupIdKey& key)
        {
            if (key_mappings_.find(key) == key_mappings_.end())
                return nullptr;

            return key_mappings_[key];
        }
    protected:
        std::map<GroupIdKey, TItem*>         key_mappings_;
	};


#if defined(_WIN32)
#pragma warning( pop )
#endif

#define sBuffGroupConfig (*DATA::BuffGroupConfig::Instance())
}

