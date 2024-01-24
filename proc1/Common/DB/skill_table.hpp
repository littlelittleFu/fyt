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
        int32_t                 Target                  = 0;            /// 1-给目标加BUFF；2-给自己加BUFF
        int32_t                 BuffID                  = 0;
        int32_t                 Duration                = 0;            /// 持续时间

        SkillAttachedBuff(int32_t target, int32_t buffID, int32_t duration) : Target(target), BuffID(buffID), Duration(duration) {}
    };

    struct SummonMonsterParam                                           /// 召唤神兽参数
    {
        int32_t                 RoleLevel               = 0;            /// 人物等级
        std::string             MonsterName;                            /// 神兽KeyName
        int32_t                 MaxNum                  = 0;            /// 可召唤最大数量
        int32_t                 MonsterLevel            = 0;            /// 神兽等级
    };

	struct Skill
	{
        int32_t                 Id                      = 0;            /// 编号
        std::string             Name                    = "";           /// 名称
        int32_t                 HurtType                = 0;            /// 伤害类型 1-攻；2-魔；3-道
        int32_t                 SkillType               = 0;            /// 技能类型 0-被动类技能；1-开关类普攻；2-状态类普攻；3-攻击动作类；4-施法类技能；5-固定动作技能
        int32_t                 SkillTypeParam          = 0;            /// 技能参数
        std::string             Script                  = "";           /// 技能回调脚本
        int32_t                 CD                      = 0;            /// 冷却时间
        int32_t                 Icon                    = 0;            /// 图标编号
        int32_t                 UIOrder                 = 0;            /// 客户端显示技能列表时的显示顺序
        int32_t                 MagicID                 = 0;            /// 技能附带的特效
        int32_t                 CastWay                 = 0;            /// 施法方式 1-直接释放；2-对目标；3-对逻辑格
        int32_t                 RangeType               = 0;            /// 范围类型 0-点；1-线；2-矩形；3-自定义
        int32_t                 RangeParam              = 0;            /// 范围参数
        std::vector<int32_t>    CustomShape;                            /// 自定义形状：以自身为起点正上方开始，挑选逻辑格编号
        int32_t                 TargetType              = 0;            /// 目标判断 0-所有；1-对自己；2-对怪物；3-对玩家
        int32_t                 CastDistance            = 0;            /// 施法距离
        int32_t                 SpecialEffectType       = 0;            /// 特殊效果类型 0-非特殊类型；1-陷阱类触发；2-陷阱类实时；3-召唤类；4-弹道类（判断阻挡）5-击退类
        std::vector<int32_t>    SpecialEffectParam;                     /// 特殊效果参数
        int32_t                 LevelCompare            = 0;            /// 等级关系 0-无等级关系；1-高于目标等级；2-高于或等于目标等级
        std::vector<SkillAttachedBuff>  AttachedBuff;                   /// 附加BUFF
        int32_t                 FixedDelay              = 0;            /// 固定延时，单位毫秒
        int32_t                 ConsumeHP               = 0;            /// 消耗HP
        int32_t                 ConsumeMP               = 0;            /// 消耗MP
        int32_t                 AttackRatio             = 0;            /// 攻击系数
        int32_t                 DefEffectRatio          = 0;            /// 防御生效系数
        int32_t                 BaseRandValMin          = 0;            /// 基础最小随机值
        int32_t                 BaseRandValMax          = 0;            /// 基础最大随机值
        int32_t                 Hatred                  = 0;            /// 仇恨值
        int32_t                 NeedRoleLevel           = 0;            /// 升到下一级所需角色等级
        int32_t                 NeedProficiency         = 0;            /// 升到下一级所需熟练度
        int32_t                 NextLevelID             = 0;            /// 下一级技能ID
        int32_t                 SkillChainID            = 0;            /// 技能链ID
        std::vector<SummonMonsterParam> SummonParams;                   /// 召唤神兽参数
        int32_t                 SafeRangeEffect         = 0;            /// 安全区内释放有效
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