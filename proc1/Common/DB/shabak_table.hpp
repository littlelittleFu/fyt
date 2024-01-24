#pragma once


namespace DATA
{
    struct ShabakMonster
    {
        std::string                 KeyName;                        /// ����������
        uint16_t                    x           = 0;                /// x����
        uint16_t                    y           = 0;                /// y����
    };

    struct Shabak
    {
        std::string                 MainCityMap;                    /// ���ǵ�ͼ
        ShabakMonster               MainCityFrontDoorMonster;       /// �������Ź���
        std::vector<int32_t>        MainCityFrontDoorMonsterTakePos;    /// �������Ź���ռ���߼���

        std::string                 PalaceMap;                      /// �ʹ���ͼ
        ShabakMonster               PalaceFrontDoorMonster;         /// �ʹ����Ź���
        std::vector<ShabakMonster>  PalaceSideDoorMonsters;         /// �ʹ����Ź���

        std::vector<std::string>    RelMaps;                        /// ɳ�Ϳ�������ص�ͼ
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
