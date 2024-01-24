#include "stdafx.h"
#include "quest_template_parser.hpp"

INSTANCE_SINGLETON(QuestTemplate)

bool QuestTemplate::parse_npc(const std::string &keyname, uint16_t &id) {
    auto npc_cfg = sNpcConfig.GetByKeyName(keyname);
    if (!npc_cfg) return false;
    id = npc_cfg->Id;
    return true;
}

bool QuestTemplate::parse_items(const std::string &str, QuestIdValuePairs &items) {
    auto kvs = str_split(str, ";");

    for (auto &s : kvs) {
        auto kv = str_split(s, "|");
        if (kv.size() < 2) return false;

        auto item_cfg = sItemConfig.GetByKeyName(kv[0]);
        if (!item_cfg) return false;

        bind_type require = bind_on_pick_up;
        if (kv.size() > 2) require = static_cast<bind_type>(atoi(kv[2].c_str()));

        items.emplace_back(item_cfg->Id, atoi(kv[1].c_str()), require);
    }

    return true;
}

bool QuestTemplate::parse_ext_attrs(const std::string &str, QuestRewardExtAttrs &attrs) {
    auto kvs = str_split(str, ";");

    for (auto &s : kvs) {
        auto kv = str_split(s, "|");
        if (kv.size() != 2) return false;

        auto &key = kv[0];
        role_attr_ext attr;

        if (key == "元宝") {
            attr = role_ingot;
        }
        else if (key == "绑元") {
            attr = role_bind_ingot;
        }
        else if (key == "金币") {
            attr = role_gold;
        }
        else if (key == "绑金") {
            attr = role_bind_gold;
        }
        else {
            return false;
        }

        attrs.emplace_back(attr, atoi(kv[1].c_str()));
    }

    return true;
}

bool QuestTemplate::parse_huntings(const std::string &str, QuestHolder &cfg) {
    if (str.find(";") != std::string::npos) {
        auto kvs = str_split(str, ";");

        for (auto &s : kvs) {
            auto kv = str_split(s, "|");
            if (kv.size() != 2) return false;

            auto monster_cfg = sMonsterConfig.GetByKeyName(kv[0]);
            if (!monster_cfg) return false;

            cfg.huntings.emplace_back(monster_cfg->Id, atoi(kv[1].c_str()));
        }
    }
    else {
        auto kv = str_split(str, "|");
        if (kv.size() != 2) return false;

        auto monsters = str_split(kv[0], ",");
        if (monsters.size() == 1) {
            auto monster_cfg = sMonsterConfig.GetByKeyName(monsters[0]);
            if (!monster_cfg) return false;
            cfg.huntings.emplace_back(monster_cfg->Id, atoi(kv[1].c_str()));
        }
        else {
            for (auto &monster : monsters) {
                auto monster_cfg = sMonsterConfig.GetByKeyName(monster);
                if (!monster_cfg) return false;
                cfg.group_huntings.ids.insert(monster_cfg->Id);
            }
            cfg.group_huntings.n = atoi(kv[1].c_str());
        }
    }

    return true;
}

bool QuestTemplate::parse_time_range(const std::string &str, QuestHolder &cfg) {
    auto dates = str_split(str, "-");
    if (dates.size() != 2) return false;

    if (!parse_date(dates[0], false, cfg.start_time)) return false;
    if (!parse_date(dates[1], true, cfg.end_time)) return false;

    return cfg.start_time < cfg.end_time;
}

bool QuestTemplate::parse_date(const std::string &str, bool whole_day, uint64_t &seconds) {
    auto ymd = str_split(str, "/");
    if (ymd.size() != 3) return false;

    tm t;
    memset(&t, 0, sizeof(t));

    t.tm_year = atoi(ymd[0].c_str()) - 1900;
    t.tm_mon = atoi(ymd[1].c_str()) - 1;
    t.tm_mday = atoi(ymd[2].c_str());

    if (whole_day) {
        t.tm_hour = 23;
        t.tm_min = 59;
        t.tm_sec = 59;
    }

    seconds = (uint64_t)mktime(&t);
    return true;
}

bool QuestTemplate::parse_dialog_line(const std::string &lines, QuestDialogs & dialogs) {

    std::vector<std::string> v = str_split(lines, "\n");
    for (auto& line : v)
    {
        auto kv = str_split(line, "=");
        if (kv.size() != 2) return false;

        //auto &key = kv[0];
        //trim_right(key, " \t]");
        //trim_left(key, " \t[");
        //auto index = atoi(key);

        auto& dialog = kv[1];
        trim(dialog);

        dialogs.emplace_back(std::move(dialog));
    }

    return true;
}
