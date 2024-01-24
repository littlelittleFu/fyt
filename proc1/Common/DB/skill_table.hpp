/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once
#include "TableBase.h"

#include <map>
#include <utility>


class CsvHelper;
namespace DATA
{
    struct SkillAttachedBuff
    {
        int32_t                 Target                  = 0;            /// 1-��Ŀ���BUFF��2-���Լ���BUFF
        int32_t                 BuffID                  = 0;
        int32_t                 Duration                = 0;            /// ����ʱ��

        SkillAttachedBuff(int32_t target, int32_t buffID, int32_t duration) : Target(target), BuffID(buffID), Duration(duration) {}
    };

    struct SummonMonsterParam                                           /// �ٻ����޲���
    {
        int32_t                 RoleLevel               = 0;            /// ����ȼ�
        std::string             MonsterName;                            /// ����KeyName
        int32_t                 MaxNum                  = 0;            /// ���ٻ��������
        int32_t                 MonsterLevel            = 0;            /// ���޵ȼ�
    };

	struct Skill
	{
        int32_t                 Id                      = 0;            /// ���
        std::string             Name                    = "";           /// ����
        int32_t                 HurtType                = 0;            /// �˺����� 1-����2-ħ��3-��
        int32_t                 SkillType               = 0;            /// �������� 0-�����༼�ܣ�1-�������չ���2-״̬���չ���3-���������ࣻ4-ʩ���༼�ܣ�5-�̶���������
        int32_t                 SkillTypeParam          = 0;            /// ���ܲ���
        std::string             Script                  = "";           /// ���ܻص��ű�
        int32_t                 CD                      = 0;            /// ��ȴʱ��
        int32_t                 Icon                    = 0;            /// ͼ����
        int32_t                 UIOrder                 = 0;            /// �ͻ�����ʾ�����б�ʱ����ʾ˳��
        int32_t                 MagicID                 = 0;            /// ���ܸ�������Ч
        int32_t                 CastWay                 = 0;            /// ʩ����ʽ 1-ֱ���ͷţ�2-��Ŀ�ꣻ3-���߼���
        int32_t                 RangeType               = 0;            /// ��Χ���� 0-�㣻1-�ߣ�2-���Σ�3-�Զ���
        int32_t                 RangeParam              = 0;            /// ��Χ����
        std::vector<int32_t>    CustomShape;                            /// �Զ�����״��������Ϊ������Ϸ���ʼ����ѡ�߼�����
        int32_t                 TargetType              = 0;            /// Ŀ���ж� 0-���У�1-���Լ���2-�Թ��3-�����
        int32_t                 CastDistance            = 0;            /// ʩ������
        int32_t                 SpecialEffectType       = 0;            /// ����Ч������ 0-���������ͣ�1-�����ഥ����2-������ʵʱ��3-�ٻ��ࣻ4-�����ࣨ�ж��赲��5-������
        std::vector<int32_t>    SpecialEffectParam;                     /// ����Ч������
        int32_t                 LevelCompare            = 0;            /// �ȼ���ϵ 0-�޵ȼ���ϵ��1-����Ŀ��ȼ���2-���ڻ����Ŀ��ȼ�
        std::vector<SkillAttachedBuff>  AttachedBuff;                   /// ����BUFF
        int32_t                 FixedDelay              = 0;            /// �̶���ʱ����λ����
        int32_t                 ConsumeHP               = 0;            /// ����HP
        int32_t                 ConsumeMP               = 0;            /// ����MP
        int32_t                 AttackRatio             = 0;            /// ����ϵ��
        int32_t                 DefEffectRatio          = 0;            /// ������Чϵ��
        int32_t                 BaseRandValMin          = 0;            /// ������С���ֵ
        int32_t                 BaseRandValMax          = 0;            /// ����������ֵ
        int32_t                 Hatred                  = 0;            /// ���ֵ
        int32_t                 NeedRoleLevel           = 0;            /// ������һ�������ɫ�ȼ�
        int32_t                 NeedProficiency         = 0;            /// ������һ������������
        int32_t                 NextLevelID             = 0;            /// ��һ������ID
        int32_t                 SkillChainID            = 0;            /// ������ID
        std::vector<SummonMonsterParam> SummonParams;                   /// �ٻ����޲���
        int32_t                 SafeRangeEffect         = 0;            /// ��ȫ�����ͷ���Ч
    };

	class SkillConfig : public TableBase<Skill>
	{
		DECLARE_SINGLETON(SkillConfig);

	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
            CELL_PARAM_DEFINE;
            GET_CELL_VALUE_INT(Id);
            GET_CELL_VALUE_STRING(Name);
            GET_CELL_VALUE_INT(HurtType);
            GET_CELL_VALUE_INT(SkillType);
            GET_CELL_VALUE_INT(SkillTypeParam);
            GET_CELL_VALUE_STRING(Script);
            GET_CELL_VALUE_INT(CD);
            GET_CELL_VALUE_INT(Icon);
            GET_CELL_VALUE_INT(UIOrder);
            GET_CELL_VALUE_INT(MagicID);
            GET_CELL_VALUE_INT(CastWay);
            GET_CELL_VALUE_INT(RangeType);
            GET_CELL_VALUE_INT(RangeParam);
            GET_CELL_VALUE_INT(TargetType);
            GET_CELL_VALUE_INT(CastDistance);
            GET_CELL_VALUE_INT(SpecialEffectType);
            GET_CELL_VALUE_INT(LevelCompare);
            GET_CELL_VALUE_INT(FixedDelay);
            GET_CELL_VALUE_INT(AttackRatio);
            GET_CELL_VALUE_INT(DefEffectRatio);
            GET_CELL_VALUE_INT(BaseRandValMin);
            GET_CELL_VALUE_INT(BaseRandValMax);
            GET_CELL_VALUE_INT(Hatred);
            GET_CELL_VALUE_INT(NeedRoleLevel);
            GET_CELL_VALUE_INT(NeedProficiency);
            GET_CELL_VALUE_INT(NextLevelID);
            GET_CELL_VALUE_INT(SkillChainID);

            GET_CELL_VALUE_INT(SafeRangeEffect);
            FillData_Cost(row, InRow);
            FillData_CustomShape(row, InRow["CustomShape"]);
            FillData_AttachedBuff(row, InRow["AttachedBuff"]);

            if (row->SpecialEffectType == skill_special_summon) {
                FillData_SummonParams(row, InRow["SpecialEffectParam"]);
            }
            else {
                FillData_SpecialEffectParam(row, InRow);
            }
		}

        void FillData_SpecialEffectParam(TItem *row, const CSV_HELPER::Row &InRow)
        {
            const char *value = InRow["SpecialEffectParam"];
            if (!value) return;

            auto v = str_split(value, ";");
            for (auto &i : v) {
                row->SpecialEffectParam.push_back(atoi(i.c_str()));
            }
        }

        void FillData_Cost(TItem *row, const CSV_HELPER::Row &InRow)
        {
            const char *value = InRow["Cost"];
            if (!value) return;

            auto v = str_split(value, "|");
            for (auto &i : v) {
                auto u = str_split(std::move(i), ";");
                if (u.size() != 2) continue;
                if (u[0] == "HP") row->ConsumeHP = atoi(u[1].c_str());
                else if (u[0] == "MP") row->ConsumeMP = atoi(u[1].c_str());
            }
        }

        void FillData_CustomShape(TItem *row, std::string data)
        {
            auto v = str_split(std::move(data), ";");
            std::vector<int32_t> CustomShape;
            for (auto &i : v) {
                CustomShape.push_back(atoi(i.c_str()));
            }
            if (!CustomShape.empty()) row->CustomShape = std::move(CustomShape);
        }

        void FillData_AttachedBuff(TItem *row, std::string data)
        {
            auto v = str_split(std::move(data), "|");
            std::vector<SkillAttachedBuff>  AttachedBuff;
            for (auto &i : v) {
                auto u = str_split(std::move(i), ";");
                if (u.size() != 3) continue;
                AttachedBuff.emplace_back(atoi(u[0].c_str()), atoi(u[1].c_str()), atoi(u[2].c_str()));
            }
            if (!AttachedBuff.empty()) row->AttachedBuff = std::move(AttachedBuff);
        }

        void FillData_SummonParams(TItem *row, std::string data)
        {
            auto sects = str_split(std::move(data), "|");
            if (sects.size() < 4) return;

            auto roleLevels = str_split(std::move(sects[0]), ",");
            auto monstKeyNames = str_split(std::move(sects[1]), ",");
            auto maxNums = str_split(std::move(sects[2]), ",");
            auto monstLevels = str_split(std::move(sects[3]), ",");

            std::vector<SummonMonsterParam> SummonParams;
            auto elems = std::min<std::size_t>({roleLevels.size(), monstKeyNames.size(), maxNums.size(), monstLevels.size()});
            for (auto i = 0; i < elems; ++i) {
                SummonMonsterParam param;
                param.RoleLevel = std::stoi(roleLevels[i]);
                param.MonsterName = std::move(monstKeyNames[i]);
                param.MaxNum = std::stoi(maxNums[i]);
                param.MonsterLevel = std::stoi(monstLevels[i]);
                SummonParams.emplace_back(std::move(param));
            }

            if (!SummonParams.empty()) {
                std::sort(SummonParams.begin(), SummonParams.end(), [](const auto &a, const auto &b){
                    return a.RoleLevel < b.RoleLevel;
                });
                row->SummonParams = std::move(SummonParams);
            }
        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->Id == 0 || row->Name.empty()) return false;
            return true;
        }

        virtual void FillMapping(TItem *row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = 0;
            TItem *&t1 = (*t0)[row->Id];
            t1 = row;
            key_name_mappings_[row->Name] = row;
        }
    };

#define sSkillConfig (*DATA::SkillConfig::Instance())
}