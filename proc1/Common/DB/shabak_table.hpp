#pragma once


namespace DATA
{
    struct ShabakMonster
    {
        std::string                 KeyName;                        /// 怪物索引名
        uint16_t                    x           = 0;                /// x坐标
        uint16_t                    y           = 0;                /// y坐标
    };

    struct Shabak
    {
        std::string                 MainCityMap;                    /// 主城地图
        ShabakMonster               MainCityFrontDoorMonster;       /// 主城正门怪物
        std::vector<int32_t>        MainCityFrontDoorMonsterTakePos;    /// 主城正门怪物占用逻辑格

        std::string                 PalaceMap;                      /// 皇宫地图
        ShabakMonster               PalaceFrontDoorMonster;         /// 皇宫正门怪物
        std::vector<ShabakMonster>  PalaceSideDoorMonsters;         /// 皇宫侧门怪物

        std::vector<std::string>    RelMaps;                        /// 沙巴克其他相关地图
    };

    class ShabakConfig : public TableBase<Shabak>
    {
        DECLARE_SINGLETON(ShabakConfig);

    public:
        virtual void FillData(TItem *row, const CSV_HELPER::Row &InRow) override
        {
            GetValue(InRow, "MainCityMap", row->MainCityMap);

            std::string value;

            if (GetValue(InRow, "MainCityFrontDoorMonster", value))
                ParseMonster(row->MainCityFrontDoorMonster, std::move(value));

            if (GetValue(InRow, "MainCityFrontDoorMonsterTakePos", value)) {
                auto v = str_split(std::move(value), ";");
                for (const auto &s : v) {
                    row->MainCityFrontDoorMonsterTakePos.push_back(atoi(s.c_str()));
                }
            }

            GetValue(InRow, "PalaceMap", row->PalaceMap);

            if (GetValue(InRow, "PalaceFrontDoorMonster", value))
                ParseMonster(row->PalaceFrontDoorMonster, std::move(value));

            if (GetValue(InRow, "PalaceSideDoorMonsters", value)) {

                ShabakMonster monster;
                auto strVec = str_split(std::move(value), ";");

                for (auto &str : strVec) {
                    if (!ParseMonster(monster, std::move(str))) continue;
                    row->PalaceSideDoorMonsters.emplace_back(std::move(monster));
                }
            }

            if (GetValue(InRow, "RelMaps", value))
                row->RelMaps = str_split(std::move(value), ";");
        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->MainCityMap.empty() || row->PalaceMap.empty()) return false;
            return true;
        }

    private:

        bool GetValue(const CSV_HELPER::Row &InRow, const char *key, std::string &value)
        {
            if (!key) return false;

            const char *temp = InRow[key];
            if (!temp) return false;

            value = temp;
            return true;
        }

        bool ParseMonster(ShabakMonster &monster, std::string str)
        {
            auto v = str_split(std::move(str), "|");
            if (v.size() < 3) return false;

            monster.KeyName = std::move(v[0]);
            monster.x = atoi(v[1].c_str());
            monster.y = atoi(v[2].c_str());

            return true;
        }
    };
}

#define sShabakConfig (*DATA::ShabakConfig::Instance())
