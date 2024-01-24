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

/// 任务奖赏---扩展属性
struct QuestRewardExtAttr {
    role_attr_ext           att                 = role_exp;     /// 扩展属性编码
    int32_t                 n                   = 0;            /// 修改的数量

    QuestRewardExtAttr(role_attr_ext _att, int32_t _n) : att(_att), n(_n) {}
};
typedef std::vector<QuestRewardExtAttr> QuestRewardExtAttrs;

typedef std::vector<std::string> QuestDialogs;

/// 任务配置
struct QuestHolder {
    uint16_t                id                  = 0;            /// 任务编号
    uint8_t                 type                = 0;            /// 任务类型, 1主线2支线3跑环4循环
    std::string             name;                               /// 任务名称
    uint8_t                 abort               = 0;            /// 是否可以放弃, 1不可放弃2可以放弃3可以放弃且无法再接取

    uint16_t                previd              = 0;            /// 前置任务
    uint16_t                nextid              = 0;            /// 后续任务
    uint32_t                min_level           = 0;            /// 最小接取等级
    uint32_t                max_level           = 0;            /// 最大完成等级

    uint8_t                 accept_type         = 0;            /// 接取类型, 1从NPC领任务2等级触发自动接取
    uint16_t                accept_from         = 0;            /// 接取 NPC
    QuestDialogs            accept_dialogs;                     /// 接任务对话
    QuestIdValuePairs       consume_items;                      /// 接取消耗物品
    QuestIdValuePairs       acquire_items;                      /// 接取发放物品

    uint8_t                 deliver_type        = 0;            /// 结束类型, 1给NPC交任务2完成条件满足后自动结束
    uint16_t                deliver_to          = 0;            /// 交任务NPC, 结束类型1有效
    QuestDialogs            deliver_dialogs;                    /// 交任务对话
    QuestIdValuePairs       reward_items;                       /// 完成奖励物品
    QuestRewardExtAttrs     reward_attrs;                       /// 完成奖励经验、货币

    uint8_t                 achieve_type        = 0;            /// 任务完成类型, 1与NPC对话|2击杀怪物|3收集道具|4角色等级判定|5角色装备收集判断|6脚本编号|7移动到指定地图指定坐标
    QuestIdValuePairs       huntings;                           /// 所要杀死的怪物及其数量
    QuestGroupData          group_huntings;                     /// 所要杀死的怪物组及其数量
    QuestIdValuePairs       collect_items;                      /// 任务收集物品

    uint8_t                 time_limit_type     = 0;            /// 时限类型, 1相对时限|2绝对时限|3固定时间段
    uint32_t                fixed_time          = 0;            /// 固定时间
    uint64_t                start_time          = 0;            /// 起始时间
    uint64_t                end_time            = 0;            /// 结束时间
};

typedef std::map<uint16_t, QuestHolder> QuestHolderMap;

/// 任务模板
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