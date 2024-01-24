/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once

class CsvHelper;
// ͬʱҲ�����ȼ�,ֵԽ��,���ȴ���
enum BuffGroupRelationOutreach
{
    BGRO_0 = 0,  // ����
    BGRO_1,      // �滻(��1BUFF�滻��2BUFF)
    BGRO_2,      // ����(��1BUFF��������BUFF������������buff�鶼��ʧ)
    BGRO_3,      // ����(��1BUFF��Ӻ���2BUFF�޷������)
};

namespace DATA
{
	struct BuffGroup
	{
        int32_t             Id = 0;							/// ���
        int32_t             GroupId1 = 0;                   /// ��1Id
        int32_t             GroupId2 = 0;                   /// ��2Id
        int32_t             GroupRelation = 0;			    /// ����ϵBuffGroupRelationOutreach
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

