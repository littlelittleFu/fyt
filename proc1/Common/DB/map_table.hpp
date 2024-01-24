/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;

enum EMapType
{
    EMT_TOWN = 0,   // 城镇地图
    EMT_DGN,        // 副本
};

namespace DATA
{
	struct Map
	{
		uint16_t      Id;                          /// 地图索引
		uint8_t       GSIndex;                     /// Game Server索引
		char        KeyName[32];                 /// 关键字索引
		char        Logic[32];                   /// 地图逻辑格文件名
		uint8_t       MapType;                     /// 地图类型
		char        Name[32];                    /// 地图名称
		char        Script[32];                  /// 地图脚本
		int32_t       MaxLevel;                    /// 进入最大等级
		int32_t       MinLevel;                    /// 进入最小等级
		int32_t       PKMax;                       /// PK值最大限制
		int32_t       PKMin;                       /// PK值最小限制
		uint8_t       Job;                         /// 职业限制
		uint8_t       Gender;                      /// 性别限制
		char        TOffline[32];                /// 离线自动传送
		uint16_t      TX;                          /// 对应地图的X坐标
		uint16_t      TY;                          /// 对应地图的Y坐标
		char        ItemType[384];               /// 禁用类道具
		char        ItemId[512];                 /// 禁用单独道具
		char        SkillType[384];              /// 禁用类技能
		char        SkillId[384];                /// 禁用ID技能
		uint8_t       Hero;                        /// 可否召唤英雄
		uint8_t       Riding;                      /// 可否骑马
		uint8_t       Team;                        /// 可否组队
		uint16_t      LightXr;                     /// 视野范围
		uint16_t      LightYr;                     /// 视野范围
		uint8_t       BagDrop;                     /// 死亡是否有包裹掉落
		uint8_t       EquipDrop;                   /// 死亡是否有装备掉落
		uint8_t       Talk;                        /// 可否聊天
		uint8_t       Dropable;                    /// 可否丢弃物品
		uint8_t       Option;                      /// 死亡弹出
		uint16_t      ShowUI;                      /// 进入地图是否弹UI
		uint16_t      BackPic;                     /// 背景图资源编号
		uint16_t      EnterEffect;                 /// 进入场景特效
		uint16_t      LeftEffect;                  /// 离开场景特效
		uint32_t      MiniMap;                     /// 缩略图资源ID
		uint8_t       CanTalk;                     /// 禁止喊话
		uint8_t       KillPk;                      /// 杀人是否增加PK值
		uint8_t       CrossHuman;                  /// 是否允许穿人
		uint8_t       CrossMonster;                /// 是否允许穿怪
		uint8_t       Ride;                        /// 是否允许骑马
		uint8_t       Mask;                        /// 是否有遮罩
		char        CustomMiniMap[96];           /// 小地图名
		uint32_t		MapBg;
		uint8_t       ShowBigThumbnail;
		char		SoundInfo[64];
		uint8_t		AddKillerToBlackList;		//是否把击杀我的玩家加到黑名单
        uint8_t     AutoPickItem;               /// 是否自动捡物
	};


	class MapConfig : public TableBase<Map>
	{
		DECLARE_SINGLETON(MapConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "GSIndex", row->GSIndex, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "Script", row->Script, 1);
            CELL_VALUE(InRow, "Logic", row->Logic, 1);
            CELL_VALUE(InRow, "MapType", row->MapType, 0);
            CELL_VALUE(InRow, "MaxLevel", row->MaxLevel, 0);
            CELL_VALUE(InRow, "MinLevel", row->MinLevel, 0);
            CELL_VALUE(InRow, "PKMax", row->PKMax, 0);
            CELL_VALUE(InRow, "PKMin", row->PKMin, 0);
            CELL_VALUE(InRow, "Job", row->Job, 0);
            CELL_VALUE(InRow, "Gender", row->Gender, 0);
            CELL_VALUE(InRow, "TOffline", row->TOffline, 1);
            CELL_VALUE(InRow, "TX", row->TX, 0);
            CELL_VALUE(InRow, "TY", row->TY, 0);
            CELL_VALUE(InRow, "ItemType", row->ItemType, 1);
            CELL_VALUE(InRow, "ItemId", row->ItemId, 1);
            CELL_VALUE(InRow, "SkillType", row->SkillType, 1);
            CELL_VALUE(InRow, "SkillId", row->SkillId, 1);
            CELL_VALUE(InRow, "Hero", row->Hero, 0);
            CELL_VALUE(InRow, "Riding", row->Riding, 0);
            CELL_VALUE(InRow, "Team", row->Team, 0);
            CELL_VALUE(InRow, "LightXr", row->LightXr, 0);
            CELL_VALUE(InRow, "LightYr", row->LightYr, 0);
            CELL_VALUE(InRow, "BagDrop", row->BagDrop, 0);
            CELL_VALUE(InRow, "EquipDrop", row->EquipDrop, 0);
            CELL_VALUE(InRow, "Talk", row->Talk, 0);
            CELL_VALUE(InRow, "Dropable", row->Dropable, 0);
            CELL_VALUE(InRow, "Option", row->Option, 0);
            CELL_VALUE(InRow, "ShowUI", row->ShowUI, 0);
            CELL_VALUE(InRow, "BackPic", row->BackPic, 0);
            CELL_VALUE(InRow, "EnterEffect", row->EnterEffect, 0);
            CELL_VALUE(InRow, "LeftEffect", row->LeftEffect, 0);
            CELL_VALUE(InRow, "MiniMap", row->MiniMap, 0);
            CELL_VALUE(InRow, "CanTalk", row->CanTalk, 0);
            CELL_VALUE(InRow, "KillPk", row->KillPk, 0);
            CELL_VALUE(InRow, "CrossHuman", row->CrossHuman, 0);
            CELL_VALUE(InRow, "CrossMonster", row->CrossMonster, 0);
            CELL_VALUE(InRow, "Ride", row->Ride, 0);
            CELL_VALUE(InRow, "Mask", row->Mask, 0);
            CELL_VALUE(InRow, "CustomMiniMap", row->CustomMiniMap, 1);
            CELL_VALUE(InRow, "ShowBigThumbnail", row->ShowBigThumbnail, 0);
            CELL_VALUE(InRow, "SoundInfo", row->SoundInfo, 1);
            CELL_VALUE(InRow, "MapBg", row->MapBg, 0);
            CELL_VALUE(InRow, "PKeffectsocial", row->AddKillerToBlackList, 0);
            CELL_VALUE(InRow, "AutoPickItem", row->AutoPickItem, 0);
        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->Id == 0 || row->KeyName[0] == 0) return false;
            return true;
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = 0;
            TItem *&t1 = (*t0)[row->Id];
            t1 = row;
            key_name_mappings_[row->KeyName] = row;
        }
	};


#define sMapConfig (*DATA::MapConfig::Instance())
}