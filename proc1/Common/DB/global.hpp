/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once

#define BEGIN_PARSE_KEY(name) if (key == #name) data_.name = row[1]
#define PARSE_KEY(name) else if (key == #name) data_.name = row[1]
#define PARSE_KEY_CUST(name) else if (key == #name)
#define PARSE_KET_STRING(name) else if(key == #name) strcpy_s(data_.name,sizeof(data_.name), (const char *)row[1])


namespace DATA
{
    struct Global
    {
        uint32_t        SceneItemSurvivalTime           = 60000;            /// 场景物品的生存时间
        uint32_t        SceneItemDeadTime               = 120000;           /// 场景物品的死亡时间
        uint32_t        TeamBenefitRange                = 20;               /// 怪物死亡同一队加经验、任务范围
        uint32_t        RemoteOpenWarehouse             = 1;
        uint32_t        TopListFlashTime                = 300000;           /// 排行榜刷新时间
        uint32_t        JoinGuildLevel                  = 30;               /// 创建、加入行会等级
        uint32_t        RecoveryPropertyTime            = 3000;             /// 恢复属性间隔时间
        uint32_t        CorpseTime                      = 5000;             /// 尸体消失时间 
        uint32_t        TradeDelegateTime               = 24;               /// 交易行委托时间(小时)
        uint32_t        DropIsRandom                    = 0;                /// 怪物掉落物品顺序随机打乱
        uint32_t        RoleBaseDropRate                = 10000;            /// 人物默认的爆率
        uint32_t        Precision                       = 2;                /// 精度(1:百分比,2:万分比)
        uint32_t        SyncDataIntervalTime            = 60000;             /// 同步数据间隔时间   
        uint16_t        CommonAttackSkillID             = 10001;            /// 普攻ID
        std::vector<uint16_t> SkillPriority = {10803, 10903, 10603, 10303, 10403, 10203, 10001};    /// 技能优先级：开天 > 逐日 > 烈火 > 刺杀 > 半月 > 攻杀 > 普攻
        uint32_t        IncreasePKValueWithKillWhite    = 80;               /// 击杀白名玩家增加PK值
        uint32_t        DcreasePKValueInterval          = 1;                /// PK值自然衰减间隔 s
        uint16_t        PKValueOfYellowName             = 100;              /// 黄名玩家的PK值
        uint16_t        PKValueOfRedName                = 200;              /// 红名玩家的PK值
        uint16_t        GrayBuffID                      = 9999;             /// 灰名buffID
        uint16_t        SafeRegionCanThroughHuman       = 1;                /// 安全区可以穿人
        uint16_t        StallRegionCanThroughHuman      = 1;                /// 摆摊区可以穿人
        uint16_t        SafeRegionCanThroughMonster     = 1;                /// 安全区可以穿怪
        uint16_t        StallRegionCanThroughMonster    = 1;                /// 摆摊区可以穿怪
        char            MallDayUpdateTime[256]          = {0};
        char            MallWeekUpdateTime[256]         = {0};
        char            MallMonthUpdateTime[256]        = {0};
        uint16_t        GainProficiencyMin              = 1;                /// 使用技能获得最小熟练度
        uint16_t        GainProficiencyMax              = 3;                /// 使用技能获得最大熟练度
        uint32_t        PetHateTime                     = 10000;            /// 法师道士宠物主动攻击延续时长
        uint8_t         AutoPickupMaxDistance           = 10;               /// 自动捡物最远距离
        uint32_t        MonsterBackRate                 = 0;                /// 怪物后仰概率
        uint16_t        MaxMapWidth                     = 2000;             /// 最大地图宽度
        uint16_t        MaxMapHeight                    = 2000;             /// 最大地图高度
        uint32_t        TradeTaxRate                    = 500;              /// 万分比的寄售行税率
        uint16_t        PlayerCanDrop                   = 0;                /// 玩家掉落
        uint32_t        PlayerDropIsRandom              = 0;                /// 人物掉落物品顺序随机打乱

        uint32_t        TradeRecordsExpireTime          = 2592000;          /// 寄售行记录到期时间
        uint32_t        TradeRecordsMaxCnt              = 200;              /// 寄售行记录保留数量

        uint32_t        SyncUserDataIntervalTime        = 60000;            /// center同步userdata时间间隔
        std::vector<uint16_t> GuildMaxMemberLimit       = {100};            /// 各等级人数限制
		char            DeleteMailDayUpdateTime[256] = "01:00:00";            /// 删除邮件更新时间
		uint32_t        PlayerDropSiteItemMaxCount      = 0;                /// 人物死亡可堆叠物品掉落上线数量

    };

    class GlobalConfig
    {
        DECLARE_SINGLETON(GlobalConfig);

    private:
        Global                  data_;

        bool                    beReloaded = false;
    public:
        bool GetReloaded() { return beReloaded; }
        void ResetReload() { beReloaded = false; }
        bool Load(const std::string &path)
        {
            CSV_HELPER::CsvHelper csv;

            auto content = csv.LoadFile(path, CSV_HELPER::CsvEncoding::e_ANSI);
            csv.Parser(content, -1);

            auto result = csv.GetError();
            if (result != CSV_HELPER::CsvError::e_Success) {
                LOG_ERROR("Parse global config failed with error %d", result);
                return false;
            }

            int idx = 0;
            const auto &rows = csv.GetRows();
            for (const auto &row : rows) {
                if (row.Size() < 2) continue;
                // 去掉表头
                if (idx++ == 0) continue;

                std::string key = row[0];

                BEGIN_PARSE_KEY(SceneItemSurvivalTime);
                PARSE_KEY(SceneItemDeadTime);
                PARSE_KEY(TeamBenefitRange);
                PARSE_KEY(RemoteOpenWarehouse);
                PARSE_KEY(TopListFlashTime);
                PARSE_KEY(JoinGuildLevel);
                PARSE_KEY(RecoveryPropertyTime);
                PARSE_KEY(CorpseTime);
                PARSE_KEY(TradeDelegateTime);
                PARSE_KEY(DropIsRandom);
                PARSE_KEY(RoleBaseDropRate);
                PARSE_KEY(Precision);
                PARSE_KEY(SyncDataIntervalTime);
                PARSE_KEY(CommonAttackSkillID);
                PARSE_KEY(IncreasePKValueWithKillWhite);
                PARSE_KEY(DcreasePKValueInterval);
                PARSE_KEY(PKValueOfYellowName);
                PARSE_KEY(PKValueOfRedName);
                PARSE_KEY(GrayBuffID);
                PARSE_KEY(SafeRegionCanThroughHuman);
                PARSE_KEY(StallRegionCanThroughHuman);
                PARSE_KEY(SafeRegionCanThroughMonster);
                PARSE_KEY(StallRegionCanThroughMonster);
                PARSE_KET_STRING(MallDayUpdateTime);
                PARSE_KET_STRING(MallWeekUpdateTime);
                PARSE_KET_STRING(MallMonthUpdateTime);
                PARSE_KEY(GainProficiencyMin);
                PARSE_KEY(GainProficiencyMax);
                PARSE_KEY(PetHateTime);
                PARSE_KEY(AutoPickupMaxDistance);
                PARSE_KEY(MonsterBackRate);
                PARSE_KEY(MaxMapWidth);
                PARSE_KEY(MaxMapHeight);
                PARSE_KEY(TradeTaxRate);
                PARSE_KEY(PlayerCanDrop);
                PARSE_KEY(PlayerDropIsRandom);
                PARSE_KEY(TradeRecordsExpireTime);
                PARSE_KEY(TradeRecordsMaxCnt);
                PARSE_KEY(SyncUserDataIntervalTime);
                PARSE_KET_STRING(DeleteMailDayUpdateTime);
                PARSE_KEY(PlayerDropSiteItemMaxCount);

                PARSE_KEY_CUST(SkillPriority) {

                    data_.SkillPriority.clear();

                    const char *value = row[1];
                    auto skillIDList = str_split(value, "|");

                    for (auto &skillID : skillIDList) {
                        data_.SkillPriority.push_back(atoi(skillID.c_str()));
                    }
                }

                PARSE_KEY_CUST(GuildMaxMemberLimit) {

                    data_.GuildMaxMemberLimit.clear();

                    const char *value = row[1];
                    auto numLimits = str_split(value, "|");

                    for (auto &num : numLimits) {
                        data_.GuildMaxMemberLimit.push_back(atoi(num.c_str()));
                    }
                }
            }

            beReloaded = true;
            return true;
        }

        const Global * GetData() { return &data_; }
    };

#define sGlobalConfig (*DATA::GlobalConfig::Instance())
}