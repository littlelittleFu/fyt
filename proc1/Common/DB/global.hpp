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
        uint32_t        SceneItemSurvivalTime           = 60000;            /// ������Ʒ������ʱ��
        uint32_t        SceneItemDeadTime               = 120000;           /// ������Ʒ������ʱ��
        uint32_t        TeamBenefitRange                = 20;               /// ��������ͬһ�ӼӾ��顢����Χ
        uint32_t        RemoteOpenWarehouse             = 1;
        uint32_t        TopListFlashTime                = 300000;           /// ���а�ˢ��ʱ��
        uint32_t        JoinGuildLevel                  = 30;               /// �����������л�ȼ�
        uint32_t        RecoveryPropertyTime            = 3000;             /// �ָ����Լ��ʱ��
        uint32_t        CorpseTime                      = 5000;             /// ʬ����ʧʱ�� 
        uint32_t        TradeDelegateTime               = 24;               /// ������ί��ʱ��(Сʱ)
        uint32_t        DropIsRandom                    = 0;                /// ���������Ʒ˳���������
        uint32_t        RoleBaseDropRate                = 10000;            /// ����Ĭ�ϵı���
        uint32_t        Precision                       = 2;                /// ����(1:�ٷֱ�,2:��ֱ�)
        uint32_t        SyncDataIntervalTime            = 60000;             /// ͬ�����ݼ��ʱ��   
        uint16_t        CommonAttackSkillID             = 10001;            /// �չ�ID
        std::vector<uint16_t> SkillPriority = {10803, 10903, 10603, 10303, 10403, 10203, 10001};    /// �������ȼ������� > ���� > �һ� > ��ɱ > ���� > ��ɱ > �չ�
        uint32_t        IncreasePKValueWithKillWhite    = 80;               /// ��ɱ�����������PKֵ
        uint32_t        DcreasePKValueInterval          = 1;                /// PKֵ��Ȼ˥����� s
        uint16_t        PKValueOfYellowName             = 100;              /// ������ҵ�PKֵ
        uint16_t        PKValueOfRedName                = 200;              /// ������ҵ�PKֵ
        uint16_t        GrayBuffID                      = 9999;             /// ����buffID
        uint16_t        SafeRegionCanThroughHuman       = 1;                /// ��ȫ�����Դ���
        uint16_t        StallRegionCanThroughHuman      = 1;                /// ��̯�����Դ���
        uint16_t        SafeRegionCanThroughMonster     = 1;                /// ��ȫ�����Դ���
        uint16_t        StallRegionCanThroughMonster    = 1;                /// ��̯�����Դ���
        char            MallDayUpdateTime[256]          = {0};
        char            MallWeekUpdateTime[256]         = {0};
        char            MallMonthUpdateTime[256]        = {0};
        uint16_t        GainProficiencyMin              = 1;                /// ʹ�ü��ܻ����С������
        uint16_t        GainProficiencyMax              = 3;                /// ʹ�ü��ܻ�����������
        uint32_t        PetHateTime                     = 10000;            /// ��ʦ��ʿ����������������ʱ��
        uint8_t         AutoPickupMaxDistance           = 10;               /// �Զ�������Զ����
        uint32_t        MonsterBackRate                 = 0;                /// �����������
        uint16_t        MaxMapWidth                     = 2000;             /// ����ͼ���
        uint16_t        MaxMapHeight                    = 2000;             /// ����ͼ�߶�
        uint32_t        TradeTaxRate                    = 500;              /// ��ֱȵļ�����˰��
        uint16_t        PlayerCanDrop                   = 0;                /// ��ҵ���
        uint32_t        PlayerDropIsRandom              = 0;                /// ���������Ʒ˳���������

        uint32_t        TradeRecordsExpireTime          = 2592000;          /// �����м�¼����ʱ��
        uint32_t        TradeRecordsMaxCnt              = 200;              /// �����м�¼��������

        uint32_t        SyncUserDataIntervalTime        = 60000;            /// centerͬ��userdataʱ����
        std::vector<uint16_t> GuildMaxMemberLimit       = {100};            /// ���ȼ���������
		char            DeleteMailDayUpdateTime[256] = "01:00:00";            /// ɾ���ʼ�����ʱ��
		uint32_t        PlayerDropSiteItemMaxCount      = 0;                /// ���������ɶѵ���Ʒ������������

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
                // ȥ����ͷ
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