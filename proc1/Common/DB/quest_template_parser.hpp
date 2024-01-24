#pragma once

#include <cstdint>
#include <set>

#include <vector>
#include <string>

/// id-value pair
struct QuestIdValuePair {
    uint16_t                id                  = 0;            /// id
    int32_t                 n                   = 0;            /// value
    bind_type               require             = bind_on_pick_up;

    QuestIdValuePair(uint16_t _id, int32_t _n) : id(_id), n(_n) {}
    QuestIdValuePair(uint16_t _id, int32_t _n, bind_type _require) : id(_id), n(_n), require(_require) {}
};
typedef std::vector<QuestIdValuePair> QuestIdValuePairs;

struct QuestGroupData {
    std::set<uint16_t>      ids;                                /// ids
    int32_t                 n                   = 0;            /// value
};

/// ������---��չ����
struct QuestRewardExtAttr {
    role_attr_ext           att                 = role_exp;     /// ��չ���Ա���
    int32_t                 n                   = 0;            /// �޸ĵ�����

    QuestRewardExtAttr(role_attr_ext _att, int32_t _n) : att(_att), n(_n) {}
};
typedef std::vector<QuestRewardExtAttr> QuestRewardExtAttrs;

typedef std::vector<std::string> QuestDialogs;

/// ��������
struct QuestHolder {
    uint16_t                id                  = 0;            /// ������
    uint8_t                 type                = 0;            /// ��������, 1����2֧��3�ܻ�4ѭ��
    std::string             name;                               /// ��������
    uint8_t                 abort               = 0;            /// �Ƿ���Է���, 1���ɷ���2���Է���3���Է������޷��ٽ�ȡ

    uint16_t                previd              = 0;            /// ǰ������
    uint16_t                nextid              = 0;            /// ��������
    uint32_t                min_level           = 0;            /// ��С��ȡ�ȼ�
    uint32_t                max_level           = 0;            /// �����ɵȼ�

    uint8_t                 accept_type         = 0;            /// ��ȡ����, 1��NPC������2�ȼ������Զ���ȡ
    uint16_t                accept_from         = 0;            /// ��ȡ NPC
    QuestDialogs            accept_dialogs;                     /// ������Ի�
    QuestIdValuePairs       consume_items;                      /// ��ȡ������Ʒ
    QuestIdValuePairs       acquire_items;                      /// ��ȡ������Ʒ

    uint8_t                 deliver_type        = 0;            /// ��������, 1��NPC������2�������������Զ�����
    uint16_t                deliver_to          = 0;            /// ������NPC, ��������1��Ч
    QuestDialogs            deliver_dialogs;                    /// ������Ի�
    QuestIdValuePairs       reward_items;                       /// ��ɽ�����Ʒ
    QuestRewardExtAttrs     reward_attrs;                       /// ��ɽ������顢����

    uint8_t                 achieve_type        = 0;            /// �����������, 1��NPC�Ի�|2��ɱ����|3�ռ�����|4��ɫ�ȼ��ж�|5��ɫװ���ռ��ж�|6�ű����|7�ƶ���ָ����ͼָ������
    QuestIdValuePairs       huntings;                           /// ��Ҫɱ���Ĺ��Ｐ������
    QuestGroupData          group_huntings;                     /// ��Ҫɱ���Ĺ����鼰������
    QuestIdValuePairs       collect_items;                      /// �����ռ���Ʒ

    uint8_t                 time_limit_type     = 0;            /// ʱ������, 1���ʱ��|2����ʱ��|3�̶�ʱ���
    uint32_t                fixed_time          = 0;            /// �̶�ʱ��
    uint64_t                start_time          = 0;            /// ��ʼʱ��
    uint64_t                end_time            = 0;            /// ����ʱ��
};

typedef std::map<uint16_t, QuestHolder> QuestHolderMap;

/// ����ģ��
class QuestTemplate : public TableBase<QuestHolder>
{
    DECLARE_SINGLETON(QuestTemplate)
public:
    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
    {
        CELL_PARAM_DEFINE;
        int32_t value = 0;
        CELL_VALUE(InRow, "Id", row->id, 0);
        CELL_VALUE(InRow, "Type", row->type, 0);
        CELL_STRING_VALUE(InRow, "Name", row->name);
        CELL_VALUE(InRow, "IsAbandon", row->abort, 0);

        CELL_VALUE(InRow, "PreId", row->previd, 0);
        CELL_VALUE(InRow, "NextId", row->nextid, 0);
        CELL_VALUE(InRow, "MinLevel", row->min_level, 0);
        CELL_VALUE(InRow, "MaxLevel", row->max_level, 0);

        CELL_VALUE(InRow, "AcceptType", row->accept_type, 0);
        parse_npc(InRow["AcceptNpc"], row->accept_from);
        parse_dialog_line(InRow["AcceptContent"], row->accept_dialogs);
        parse_items(InRow["AcceptConsume"], row->consume_items); 
        parse_items(InRow["AcceptAcquire"], row->acquire_items);

        CELL_VALUE(InRow, "DeliverType", row->deliver_type, 0);
        parse_npc(InRow["DeliverNpc"], row->deliver_to);
        parse_dialog_line(InRow["DeliverContent"], row->deliver_dialogs);
        parse_items(InRow["AwardItems"], row->reward_items);

        CELL_VALUE(InRow, "AwardExperience", value, 0);
        row->reward_attrs.emplace_back(role_exp, value);
        parse_ext_attrs(InRow["AwardMoney"], row->reward_attrs);

        CELL_VALUE(InRow, "AchieveType", row->achieve_type, 0);
        parse_huntings(InRow["HuntCondition"], *row);
        parse_items(InRow["CollectItems"], row->collect_items);

        CELL_VALUE(InRow, "TimeLimitType", row->time_limit_type, 0);
        CELL_VALUE(InRow, "FixedTime", row->fixed_time, 0);
        parse_time_range(InRow["TiemPeriod"], *row);
    }

    virtual bool CheckValid(TItem *row) override
    {
        if (row->id == 0) return false;
        return true;
    }

    virtual void FillMapping(TItem* row) override
    {
        TKeyIDMapping* t0 = &key_id_mappings_;
        if (t0->find(row->id) == t0->end())
            (*t0)[row->id] = 0;
        TItem*& t1 = (*t0)[row->id];
        t1 = row;
        key_name_mappings_[std::to_string(row->id)] = row;
    }


    bool parse(const std::string &filename);

    QuestHolder * get_config(uint16_t template_id) { return Get(template_id);}
    bool has_config(uint16_t template_id){  return Has(template_id); }

private:
    bool parse_dialog_line(const std::string &line, QuestDialogs& dialogs);
    bool parse_npc(const std::string &keyname, uint16_t &id);
    bool parse_items(const std::string &str, QuestIdValuePairs &items);
    bool parse_ext_attrs(const std::string &str, QuestRewardExtAttrs &attrs);
    bool parse_huntings(const std::string &str, QuestHolder &cfg);
    bool parse_time_range(const std::string &str, QuestHolder &cfg);
    bool parse_date(const std::string &str, bool whole_day, uint64_t &seconds);
};

#define sQuestTemplate (*QuestTemplate::Instance())