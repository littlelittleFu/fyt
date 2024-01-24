#ifndef __LOGIC_DEF__
#define __LOGIC_DEF__

#include <map>
#include <string>
//#include <vector>

/// 定义性别
enum gender_type {
    gender_nullptr = 0,
    gender_male,   /// 男
    gender_female, /// 女
    gender_max,
};

/// 定义所有的职业类型
enum job_type {
    job_nullptr = 0,
    job_warrior, /// 战士
    job_mage,    /// 法师
    job_tao,     /// 道士
    job_max,
};
enum EExitType
{
	E_EXIT_EXITGS = 1,  //大退,退出游戏
	E_EXIT_LOGOUTGS,    //小退,退到选角色界面
	E_EXIT_JUMPGS,      //跳服
	E_EXIT_DBKICK,      //DBServer踢人
	E_EXIT_GSKICK,      //Game Server踢人
	E_EXIT_GTKICK,      //Gate踢人,同一帐号两个客户端连接同一gate时
	E_EXIT_SAVE,        //定时保存
	E_EXIT_NETERROR,    //网络错误,例如客户端断线
	E_EXIT_RELOGIN,     //重新登陆
	E_EXIT_FORCE_KICK   //强制踢人
};

#define LO_BYTE(x) (uint8_t)(uint16_t(x) & 0x00FF)
#define HI_BYTE(x) (uint8_t)((uint16_t(x) >> 8) & 0x00FF)

#define LO_WORD(x) (uint16_t)(uint32_t(x) & 0x0000FFFF)
#define HI_WORD(x) (uint16_t)((uint32_t(x) >> 16) & 0x0000FFFF)

#define LO_unsigned long(x) (uint32_t)(UINT64(x) & 0x00000000FFFFFFFF)
#define HI_unsigned long(x) (uint32_t)((UINT64(x) >> 32) & 0x00000000FFFFFFFF)

#define MK_unsigned long(x, y) (uint32_t)(uint16_t(x) << 16 | uint16_t(y))

//////////////////////////////////////////////////////////////////////////
#define MAP_VIEW_X 12 //地图视野X半径
#define MAP_VIEW_Y 15 //地图视野Y半径

#define MAX_REGION_OBJ 50000                 //区域内最多对象数
#define MAX_REGION_PLAYER 10000              //区域内最多玩家数
#define MAX_INT64_2_DOUBLE 9007199254740992  // int64和double之间转换的最大值
#define MIN_INT64_2_DOUBLE -9007199254740992 // int64和double之间转换的最小值

#define INFINITE_ITEM_NUM   0xFFFF
#define PRECISION   0.00010000100   // 万分比
#define PERCENTAGE  0.010000100     // 百分比
#define TRADE_DELEGATE_TIME	86400	// 默认委托时间,单位秒(全局配置里是小时)
#define INVALID_ITEM_SITE  (uint16_t)(site_nullptr)
#define CLOSE_SERVER_DELAY_TIME 10000
#define CLOSE_CUR_SERVER_DELAY_TIME 1000
#define KICK_PLAYER_DELAY_TIME 5000    //ms
#define ONE_MONTH_STAMP 2592000  // 一个月(s)
#define ADD_MAIL_MAX_NUM 500

#define MAX_ROLE_NAME_LENGTH    32
#define SEND_SYNC_DATA_INTERVAL_TIME 5000
#define SEND_SYNC_USER_DATA_INTERVAL_TIME 60000
#define CIRCLE_SEND_SYS_CHAT_TIMES 3
#define SYNC_CLIENT_BASE_SETTING_PREFIX	"SCBS_"
#define CUST_VAR_STALL_NAME_KEY	"摆摊名"
#define CUST_VAR_ALIAS_KEY	"别名"
#define LOG_PARAMS_INFO_INIT "登录初始化"

#define CURRENCY_CHANGE_TEMPLATE_TABLE_NAME  "currency_change"
#define ITEM_UPDATE_TEMPLATE_TABLE_NAME  "item_update"
#define LOGIN_OUT_TEMPLATE_TABLE_NAME  "login_out"
#define ENTERY_EXIT_MAP_TEMPLATE_TABLE_NAME  "entery_exit_map"
#define DROP_ITEM_TEMPLATE_TABLE_NAME  "drop_item"
#define GM_CMD_TEMPLATE_TABLE_NAME  "gm_cmd"
#define ONLINE_NUM_TEMPLATE_TABLE_NAME  "online_num"
#define TRADE_DATA_TEMPLATE_TABLE_NAME  "trade_data"
#define TRADE_DATA_LOG_TEMPLATE_TABLE_NAME  "trade_data_log"
#define TRADE_ITEM_TEMPLATE_TABLE_NAME  "trade_item"
#define TRADE_ITEM_LOG_TEMPLATE_TABLE_NAME  "trade_item_log"
#define TRADE_ITEM_CUST_VAR_TEMPLATE_TABLE_NAME  "trade_item_cust_var"
#define TRADE_ITEM_CUST_VAR_LOG_TEMPLATE_TABLE_NAME  "trade_item_cust_var_log"
#define TRADE_ITEM_DYN_ATTR_TEMPLATE_TABLE_NAME  "trade_item_dyn_attr"
#define TRADE_ITEM_DYN_ATTR_LOG_TEMPLATE_TABLE_NAME  "trade_item_dyn_attr_log"
#define MAIL_INFO_TEMPLATE_TABLE_NAME  "mail_info"
#define DEATH_RECORD_TEMPLATE_TABLE_NAME "death_record"
#define ACTIVITY_DATA_TEMPLATE_TABLE_NAME "activity_data"
#define REWARD_DATA_TEMPLATE_TABLE_NAME "reward_data"
#define GIFTPACK_DATA_TEMPLATE_TABLE_NAME "giftpack_data"
#define RECOVERY_DATA_TEMPLATE_TABLE_NAME "recovery_data"
#define DB_SQL_TEMPLATE_TABLE_NAME  "db_sql"
#define ITEM_DYN_ATTR_UPDATE_TEMPLATE_TABLE_NAME  "item_dyn_attr_update"
#define ITEM_CUST_VAR_UPDATE_TEMPLATE_TABLE_NAME  "item_cust_var_update"

#define CONSTANT_CREATE_ROLE_NEED_CODE "Constant_CreateRoleNeedCode"

enum role_attr
{
    // 1000
    role_1000_min = 1000,               /// 当前1000起始字段
    role_hp = 1001,                     /// 当前hp
    role_mp = 1002,                     /// 当前mp
    role_base_max_hp = 1003,            /// 最大hp 
    role_base_max_mp = 1004,            /// 最大mp
    role_base_min_phy_def = 1005,       /// 物理防御下限
    role_base_max_phy_def = 1006,       /// 物理防御上限
    role_base_min_mag_def = 1007,       /// 魔法防御下限
    role_base_max_mag_def = 1008,       /// 魔法防御上限
    role_base_min_phy_atk = 1009,       /// 物理攻击下限
    role_base_max_phy_atk = 1010,       /// 物理攻击上限
    role_base_min_mag_atk = 1011,       /// 魔法攻击上限
    role_base_max_mag_atk = 1012,       /// 魔法攻击下限
    role_base_min_tao_atk = 1013,       /// 道术攻击上限
    role_base_max_tao_atk = 1014,       /// 道术攻击下限
    role_luck_curse       = 1015,       /// 幸运/诅咒
    role_base_hp_rec = 1016,            /// hp回复值
    role_base_mp_rec = 1017,            /// mp回复值
    role_base_move_speed = 1018,        /// 基础移动速度
    role_base_attack_speed = 1019,      /// 基础攻击速度
    role_base_casting_speed = 1020,     /// 基础施法速度
    role_imm_phy = 1021,                /// 物理伤害减免值
    role_imm_mag = 1022,                /// 魔法伤害减免值
    role_monster_harm = 1023,           /// 对怪伤害值
    role_player_harm = 1024,            /// 对人伤害值
    role_real_harm = 1025,              /// 真实伤害
    role_curse = 1026,                  /// 诅咒
    role_1000_max,                      /// 当前1000结尾字段

    // 2000
    role_2000_min = 2000,                       /// 当前2000起始字段
    role_base_max_hp_pct = 2001,                /// 体力增加比
    role_base_max_mp_pct = 2002,                /// 魔力增加比
    role_base_min_phy_def_pct = 2003,           /// 物理防御下限比
    role_base_max_phy_def_pct = 2004,           /// 物理防御上限比
    role_base_min_mag_def_pct = 2005,           /// 魔法防御下限比
    role_base_max_mag_def_pct = 2006,           /// 魔法防御上限比
    role_base_min_phy_atk_pct = 2007,           /// 物理攻击下限比
    role_base_max_phy_atk_pct = 2008,           /// 物理攻击上限比
    role_base_min_mag_atk_pct = 2009,           /// 魔法攻击上限比
    role_base_max_mag_atk_pct = 2010,           /// 魔法攻击下限比
    role_base_min_tao_atk_pct = 2011,           /// 道术攻击上限比
    role_base_max_tao_atk_pct = 2012,           /// 道术攻击下限比
    role_base_hp_rec_pct = 2013,                /// hp回复值比
    role_base_mp_rec_pct = 2014,                /// mp回复值比
    role_base_attack_speed_pct = 2015,          /// 基础攻击速度比
    role_base_casting_speed_pct = 2016,         /// 基础施法速度比
    role_base_move_speed_pct = 2017,            /// 基础移动速度比
    role_hit = 2018,                        /// 物理命中
    role_miss = 2019,                       /// 物理闪避
    role_mag_miss = 2020,                   /// 魔法闪避
    role_burst = 2021,                      /// 暴击率
    role_burst_harm = 2022,                 /// 暴击伤害
    role_burst_def = 2023,                  /// 暴击抵抗
    role_burst_harm_def = 2024,             /// 暴击伤害抵抗
    role_attack_harm_pct = 2025,            /// 攻击伤害加成
    role_imm_phy_pct = 2026,                /// 物理伤害减免比
    role_imm_mag_pct = 2027,                /// 魔法伤害减免比
    role_ignore_def_pct = 2028,             /// 忽视目标防御比
    role_ignore_imm_pct = 2029,             /// 忽视目标减免比
    role_ref_harm_pct = 2030,               /// 反弹伤比
    role_suck_hp_pct = 2031,                /// 吸hp比
    role_attack_suck_hp_pct = 2032,         ///	攻击吸hp比
    role_monster_drop_pct = 2033,           /// 提高玩家击杀怪物时的物品爆率
    role_drug_rec = 2034,                   /// 药品恢复
    role_palsy_miss = 2035,                 /// 麻痹闪避
    role_exp_consume_pct = 2036,                   /// 经验消耗倍率 万分比
    role_exp_monster = 2037,                /// 打怪经验倍率       
    role_2000_max,                          /// 当前2000结尾字段
    // 3000 特殊属性
    // 4000 时间属性
    // 5000 状态属性

////////////////////////////////////
    // 6000 组合属性
    role_6000_min = 6000,
    role_group_1 = 6001,
    role_group_2 = 6002,
    role_group_3 = 6003,
    role_group_4 = 6004,
    role_group_5 = 6005,
    role_group_6 = 6006,
    role_group_7 = 6007,
    role_group_8 = 6008,
    role_group_9 = 6009,
    role_group_10 = 6010,
    role_group_11 = 6011,
    role_group_12 = 6012,
    role_group_13 = 6013,
    role_group_14 = 6014,
    role_group_15 = 6015,
    role_group_16 = 6016,
    role_group_17 = 6017,
    role_group_18 = 6018,
    role_group_19 = 6019,
    role_group_20 = 6020,
    role_6000_max,
////////////////////////////////////
    // 7000 单属性
    role_7000_min = 7000,
    role_level = 7001,              /// 等级
    role_job = 7002,                /// 职业
    role_weight = 7003,             /// 背包负重
    role_equip_weight = 7004,       /// 装备负重
    role_brawn = 7005,              /// 当前腕力
    role_max_weight = 7006,         /// 最大负重
    role_max_equip_weight = 7007,   /// 最大装备负重
    role_max_brawn = 7008,          /// 最大腕力
    role_7000_max,

    role_7400_min = 7400,
    role_bag_size_0 = 7401,         /// 包裹0大小
    role_bag_size_1,                /// 包裹1大小
    role_bag_size_2,                /// 包裹2大小
    role_bag_size_3,                /// 包裹3大小
    role_bag_size_4,                /// 包裹4大小
    role_warehouse_size,            /// 玩家的仓库大小
    role_warehouse_adv_size,        /// 玩家高级仓库大小
    role_atk_mode,                  /// 攻击类型
    role_pk,                        /// PK值
    role_holy,                      /// 神圣
    role_imm_shield,                /// 免疫护盾值
    role_gender,                    /// 性别
    role_head,                      /// 头像
    role_hair,                      /// 头发
    role_hair_color,                /// 头发颜色
    role_gm_level,                  /// gm等级
    role_stall,                     /// 摆摊状态0: 未摆摊 1: 摆摊准备 2: 摆摊中
    role_vip_level,                 /// 角色vip等级
    role_secondary_password_status, /// 二级密码状态
    role_camp,                      /// 阵营
    role_avatar,                    /// 外形
    role_max_imm_shield,            /// 最大免疫护盾值,role_imm_shield
    role_horse_modelid,             /// 骑马时外观
    role_7400_max,

    role_7700_min = 7700,
    role_can_walk = 7701,           /// 能走路
    role_can_run,                   /// 能跑步
    role_can_turn,                  /// 能转向
    role_can_jump_map,              /// 能跳地图
    role_can_phy_atk,               /// 能物理攻击
    role_can_mag_atk,               /// 能魔法攻击
    role_can_use_item,              /// 能使用道具
    role_is_phy_imm,                /// 物理免疫
    role_is_mag_imm,                /// 魔法免疫
    role_is_stealth,                /// 隐形
    role_has_imm_shield,            /// 免疫护盾
    role_has_collide,               /// 处于冲撞状态
    role_has_repelled,              /// 处于击退状态
    role_can_push,                  /// 能被推
    role_can_use_skill,             /// 能使用技能
    role_is_poisoning,              /// 是否中毒
    role_can_through,               /// 是否可以穿人
    role_can_zhenshi,               /// 是否真视状态
    role_has_team,                  /// 有队伍
    role_friend_switch,             /// 是否可加好友0:不可加,1: 可加
    role_team_switch,               /// 是否接受队伍邀请0:不接收,1: 接收
    role_has_family,                /// 有行会
    role_ride_switch,               /// 骑马开关
    role_is_ghost,                  /// 是否幽灵模式
    role_is_gray,                   /// 是否灰名
    role_is_show_fashion,           /// 是否显示时装
    role_changed_modelid,           /// 改变后的外观
    role_can_through_monster,       /// 是否可以穿怪
    role_7700_max,

    /// 动态属性段
    role_9000_min = 9000,
    role_dyn_att0 = 9001,
    role_dyn_value0,
    role_dyn_att1,
    role_dyn_value1,
    role_dyn_att2,
    role_dyn_value2,
    role_dyn_att3,
    role_dyn_value3,
    role_dyn_att4,
    role_dyn_value4,
    role_dyn_att5,
    role_dyn_value5,
    role_dyn_att6,
    role_dyn_value6,
    role_dyn_att7,
    role_dyn_value7,
    role_dyn_att8,
    role_dyn_value8,
    role_dyn_att9,
    role_dyn_value9,
    role_dyn_att10,
    role_dyn_value10,
    role_dyn_att11,
    role_dyn_value11,
    role_dyn_att12,
    role_dyn_value12,
    role_dyn_att13,
    role_dyn_value13,
    role_dyn_att14,
    role_dyn_value14,
    role_dyn_att15,
    role_dyn_value15,
    role_dyn_att16,
    role_dyn_value16,
    role_dyn_att17,
    role_dyn_value17,
    role_dyn_att18,
    role_dyn_value18,
    role_dyn_att19,
    role_dyn_value19,
    role_dyn_att20,
    role_dyn_value20,
    role_dyn_att21,
    role_dyn_value21,
    role_dyn_att22,
    role_dyn_value22,
    role_dyn_att23,
    role_dyn_value23,
    role_dyn_att24,
    role_dyn_value24,
    role_dyn_att25,
    role_dyn_value25,
    role_dyn_att26,
    role_dyn_value26,
    role_dyn_att27,
    role_dyn_value27,
    role_dyn_att28,
    role_dyn_value28,
    role_dyn_att29,
    role_dyn_value29,
    role_dyn_att30,
    role_dyn_value30,
    role_dyn_att31,
    role_dyn_value31,
    role_dyn_att32,
    role_dyn_value32,
    role_dyn_att33,
    role_dyn_value33,
    role_dyn_att34,
    role_dyn_value34,
    role_dyn_att35,
    role_dyn_value35,
    role_dyn_att36,
    role_dyn_value36,
    role_dyn_att37,
    role_dyn_value37,
    role_dyn_att38,
    role_dyn_value38,
    role_dyn_att39,
    role_dyn_value39,
    role_dyn_att40,
    role_dyn_value40,
    role_dyn_att41,
    role_dyn_value41,
    role_dyn_att42,
    role_dyn_value42,
    role_dyn_att43,
    role_dyn_value43,
    role_dyn_att44,
    role_dyn_value44,
    role_dyn_att45,
    role_dyn_value45,
    role_dyn_att46,
    role_dyn_value46,
    role_dyn_att47,
    role_dyn_value47,
    role_dyn_att48,
    role_dyn_value48,
    role_dyn_att49,
    role_dyn_value49,
    role_dyn_att50,
    role_dyn_value50,
    role_dyn_att51,
    role_dyn_value51,
    role_dyn_att52,
    role_dyn_value52,
    role_dyn_att53,
    role_dyn_value53,
    role_dyn_att54,
    role_dyn_value54,
    role_dyn_att55,
    role_dyn_value55,
    role_dyn_att56,
    role_dyn_value56,
    role_dyn_att57,
    role_dyn_value57,
    role_dyn_att58,
    role_dyn_value58,
    role_dyn_att59,
    role_dyn_value59,
    role_dyn_att60,
    role_dyn_value60,
    role_dyn_att61,
    role_dyn_value61,
    role_dyn_att62,
    role_dyn_value62,
    role_dyn_att63,
    role_dyn_value63,
    role_dyn_att64,
    role_dyn_value64,
    role_dyn_att65,
    role_dyn_value65,
    role_dyn_att66,
    role_dyn_value66,
    role_dyn_att67,
    role_dyn_value67,
    role_dyn_att68,
    role_dyn_value68,
    role_dyn_att69,
    role_dyn_value69,
    role_dyn_att70,
    role_dyn_value70,
    role_dyn_att71,
    role_dyn_value71,
    role_dyn_att72,
    role_dyn_value72,
    role_dyn_att73,
    role_dyn_value73,
    role_dyn_att74,
    role_dyn_value74,
    role_dyn_att75,
    role_dyn_value75,
    role_dyn_att76,
    role_dyn_value76,
    role_dyn_att77,
    role_dyn_value77,
    role_dyn_att78,
    role_dyn_value78,
    role_dyn_att79,
    role_dyn_value79,
    role_dyn_att80,
    role_dyn_value80,
    role_dyn_att81,
    role_dyn_value81,
    role_dyn_att82,
    role_dyn_value82,
    role_dyn_att83,
    role_dyn_value83,
    role_dyn_att84,
    role_dyn_value84,
    role_dyn_att85,
    role_dyn_value85,
    role_dyn_att86,
    role_dyn_value86,
    role_dyn_att87,
    role_dyn_value87,
    role_dyn_att88,
    role_dyn_value88,
    role_dyn_att89,
    role_dyn_value89,
    role_dyn_att90,
    role_dyn_value90,
    role_dyn_att91,
    role_dyn_value91,
    role_dyn_att92,
    role_dyn_value92,
    role_dyn_att93,
    role_dyn_value93,
    role_dyn_att94,
    role_dyn_value94,
    role_dyn_att95,
    role_dyn_value95,
    role_dyn_att96,
    role_dyn_value96,
    role_dyn_att97,
    role_dyn_value97,
    role_dyn_att98,
    role_dyn_value98,
    role_dyn_att99,
    role_dyn_value99,
    role_9000_max,

    // 自定义属性
    role_9500_min = 9500,
    role_custom_att_0 = 9501,
    role_custom_att_1,
    role_custom_att_2,
    role_custom_att_3,
    role_custom_att_4,
    role_custom_att_5,
    role_custom_att_6,
    role_custom_att_7,
    role_custom_att_8,
    role_custom_att_9,
    role_custom_att_10,
    role_custom_att_11,
    role_custom_att_12,
    role_custom_att_13,
    role_custom_att_14,
    role_custom_att_15,
    role_custom_att_16,
    role_custom_att_17,
    role_custom_att_18,
    role_custom_att_19,
    role_custom_att_20,
    role_custom_att_21,
    role_custom_att_22,
    role_custom_att_23,
    role_custom_att_24,
    role_custom_att_25,
    role_custom_att_26,
    role_custom_att_27,
    role_custom_att_28,
    role_custom_att_29,
    role_custom_att_30,
    role_custom_att_31,
    role_custom_att_32,
    role_custom_att_33,
    role_custom_att_34,
    role_custom_att_35,
    role_custom_att_36,
    role_custom_att_37,
    role_custom_att_38,
    role_custom_att_39,
    role_custom_att_40,
    role_custom_att_41,
    role_custom_att_42,
    role_custom_att_43,
    role_custom_att_44,
    role_custom_att_45,
    role_custom_att_46,
    role_custom_att_47,
    role_custom_att_48,
    role_custom_att_49,
    role_custom_att_50,
    role_custom_att_51,
    role_custom_att_52,
    role_custom_att_53,
    role_custom_att_54,
    role_custom_att_55,
    role_custom_att_56,
    role_custom_att_57,
    role_custom_att_58,
    role_custom_att_59,
    role_custom_att_60,
    role_custom_att_61,
    role_custom_att_62,
    role_custom_att_63,
    role_custom_att_64,
    role_custom_att_65,
    role_custom_att_66,
    role_custom_att_67,
    role_custom_att_68,
    role_custom_att_69,
    role_custom_att_70,
    role_custom_att_71,
    role_custom_att_72,
    role_custom_att_73,
    role_custom_att_74,
    role_custom_att_75,
    role_custom_att_76,
    role_custom_att_77,
    role_custom_att_78,
    role_custom_att_79,
    role_custom_att_80,
    role_custom_att_81,
    role_custom_att_82,
    role_custom_att_83,
    role_custom_att_84,
    role_custom_att_85,
    role_custom_att_86,
    role_custom_att_87,
    role_custom_att_88,
    role_custom_att_89,
    role_custom_att_90,
    role_custom_att_91,
    role_custom_att_92,
    role_custom_att_93,
    role_custom_att_94,
    role_custom_att_95,
    role_custom_att_96,
    role_custom_att_97,
    role_custom_att_98,
    role_custom_att_99,
    role_custom_att_199 = 9700,
    role_9500_max = 9999,
/////////////////////////////////////////////////////
    // 10001 最终属性(对配置隐藏)
    role_10000_min = 10000,
    role_max_hp = 10001,             /// 最大hp 
    role_max_mp = 10002,             /// 最大mp
    role_min_phy_def = 10003,        /// 物理防御下限
    role_max_phy_def = 10004,        /// 物理防御上限
    role_min_mag_def = 10005,        /// 魔法防御下限
    role_max_mag_def = 10006,        /// 魔法防御上限
    role_min_phy_atk = 10007,        /// 物理攻击下限
    role_max_phy_atk = 10008,        /// 物理攻击上限
    role_min_mag_atk = 10009,        /// 魔法攻击上限
    role_max_mag_atk = 10010,        /// 魔法攻击下限
    role_min_tao_atk = 10011,        /// 道术攻击上限
    role_max_tao_atk = 10012,        /// 道术攻击下限
    role_hp_rec = 10013,             /// hp回复值
    role_mp_rec = 10014,             /// mp回复值
    role_move_speed = 10015,         /// 基础移动速度
    role_attack_speed = 10016,       /// 基础攻击速度
    role_casting_speed = 10017,      /// 基础施法速度
    role_10000_max,
/////////////////////////////////////////////////////
    role_attr_min = role_1000_min,
    role_attr_max = role_10000_max,
};
/// 角色外观
enum role_appearence_item {
    role_app_body = 0, /// 身体
    role_app_weapon,   /// 武器
    role_app_wings,    /// 翅膀
    role_app_mount,    /// 坐骑
    role_app_amulet,   /// 守护
    role_app_max,
};

//////////////////////////////////////////////////////////////////////////

/// 物品类型
enum item_type {
    item_type_nullptr = 0,
    item_type_equip,         /// 装备
    item_type_consumable,    /// 消耗品
    item_type_finite,        /// 有限品
    item_type_material,      /// 材料
    item_type_sundries,      /// 杂货
    item_type_bag,           /// 包裹
    item_type_warehouse_adv, /// 高级仓库
    item_type_gold,          /// 金币
    item_type_bundle,        /// 打捆物品
    item_type_skill,         /// 技能特效类物品
    item_type_script,        /// 脚本物品

    item_type_max,
};

/// 物品按归属分类
enum item_category {
    item_cat_unknown,
    item_cat_player,        /// 玩家物品
    item_cat_scene          /// 场景物品
};

/// 装备类型
enum equip_type {
    equip_nullptr = 0,
    equip_weapon,   /// 武器
    equip_helmet,   /// 头盔
    equip_wrist,    /// 护腕
    equip_armor,    /// 衣服
    equip_juju,     /// 符咒
    equip_shoes,    /// 鞋子
    equip_shoulder, /// 护肩
    equip_necklace, /// 项链
    equip_ring,     /// 戒指
    equip_medal,    /// 勋章

    equip_gem,    /// 宝石
    equip_wings,  /// 翅膀
    equip_amulet, /// 守护
    equip_mount,  /// 坐骑

    equip_shield,  /// 盾牌
    equip_fashion, /// 时装
    equip_hat,     /// 斗笠
    equip_gloves,  /// 手套
    equip_jewelry, /// 珠宝

	equip_glasses,              /// 眼镜
	equip_bracelet,             /// 手镯
	equip_mask,                 /// 面甲
	equip_kneelet,              /// 护膝
	equip_chestplate,           /// 护胸
	equip_cloak,                /// 披风
	equip_earrings,             /// 耳环
	equip_headwear,             /// 头饰
	equip_legguard,             /// 护腿
	equip_jade,                 /// 玉佩
	equip_instrument,           /// 乐器
	equip_hangings,             /// 挂饰
	equip_fashion_weapon,       /// 时装武器,
	equip_reserved_1,
	equip_reserved_2,
	equip_reserved_3,
	equip_reserved_4,
	equip_reserved_5,
	equip_reserved_6,
	equip_reserved_7,
	equip_reserved_8,
	equip_reserved_9,

	equip_custom_0,
	equip_custom_1,
	equip_custom_2,
	equip_custom_3,
	equip_custom_4,
	equip_custom_5,
	equip_custom_6,
	equip_custom_7,
	equip_custom_8,
	equip_custom_9,
	equip_custom_10,
	equip_custom_11,
	equip_custom_12,
	equip_custom_13,
	equip_custom_14,
	equip_custom_15,
	equip_custom_16,
	equip_custom_17,
	equip_custom_18,
	equip_custom_19,
    equip_custom_end = 242,

    equip_fashion_helmet = 300,
    equip_fashion_wrist,
    equip_fashion_armor,
    equip_fashion_juju,
    equip_fashion_shoes,
    equip_fashion_shoulder,
    equip_fashion_necklace,
    equip_fashion_ring,
    equip_fashion_medal,
    equip_fashion_gem,
    equip_fashion_wings,
    equip_fashion_amulet,
    equip_fashion_mount,
    equip_fashion_shield,
    equip_fashion_hat,
    equip_fashion_gloves,
    equip_fashion_jewelry,

    equip_fashion_glasses,
    equip_fashion_bracelet,
    equip_fashion_mask,
    equip_fashion_kneelet,
    equip_fashion_chestplate,
    equip_fashion_cloak,
    equip_fashion_earrings,
    equip_fashion_headwear,
    equip_fashion_legguard,
    equip_fashion_jade,
    equip_fashion_instrument,
    equip_fashion_hangings,

    equip_fashion_end = 350,

    equip_max,
};

/// 材料类型
enum material_type {
    material_nullptr = 0,
    material_weapon_upgrade,   /// 升级武器材料
    material_reserved,         /// (保留未使用)
    material_identify,         /// 鉴定装备材料
    material_drill,            /// 装备打孔材料
    material_lucky,            /// 附加武器祝福材料
    material_gem,              /// 宝石
    material_synthesis,        /// 宝石合成符
    material_dig,              /// 宝石摘除符
    material_embed,            /// 宝石镶嵌符
    material_refine,           /// 装备精练材料
    material_refine_lucky,     /// 装备精练幸运符材料
    material_speaker,          /// 喇叭
    material_refine_transform, /// 装备精练转移材料
    material_refine_imm,       /// 装备精练符
    material_identify_imm,     /// 装备鉴定符
    material_horse,            /// 未开光马
    material_identify_horse,   /// 开光印
    material_max,
};

/// 武器类型
enum weapon_type {
    weapon_nullptr = 0, /// 通用类
    weapon_knife,       /// 刀类（战士类）
    weapon_sword,       /// 剑类（道士类）
    weapon_stick,       /// 仗类（法师类）
    weapon_max,
};

/// 符咒类型
enum juju_type {
    juju_nullptr = 0,
    juju_juju,   /// 符咒类
    juju_poison, /// 毒药类
    juju_max,
};

/// 绑定类型
enum bind_type {
    bind_nullptr = 0, /// 无绑定
    bind_on_pick_up,  /// 拾取绑定   bangding
    bind_on_use,      /// 使用绑定   weibangding
    bind_max,
};

/// 背包数量
#define MAX_BAG_COUNT 5
/// 一个背包最大格子数
#define MAX_SLOT_PER_BAG 40
/// 背包最大的格子数
#define MAX_BAG_SLOT (MAX_BAG_COUNT * MAX_SLOT_PER_BAG)
/// 仓库最大格子数
#define MAX_WAREHOUSE_SIZE 160
/// 高级仓库最大格子数
#define MAX_WAREHOUSE_ADV_SIZE 160

enum item_site {
    site_nullptr = 0,
    site_weapon,   /// 武器
    site_helmet,   /// 头盔
    site_wrist_0,  /// 护腕0
    site_wrist_1,  /// 护腕1
    site_armor,    /// 衣服
    site_juju,     /// 符咒
    site_shoes,    /// 鞋子
    site_shoulder, /// 护肩
    site_necklace, /// 项链
    site_ring_0,   /// 戒指0
    site_ring_1,   /// 戒指1
    site_medal,    /// 勋章

    site_gem,    /// 宝石
    site_wings,  /// 翅膀
    site_amulet, /// 守护
    site_mount,  /// 坐骑

    site_shield,    /// 盾牌
    site_fashion,   /// 时装
    site_hat,       /// 斗笠
    site_gloves,    /// 手套
    site_jewelry,   /// 珠宝
    site_equip_end, /// 装备位结束,下一段的起始

    site_bag_0 = site_equip_end,                /// 第0背包
    site_bag_1 = site_bag_0 + MAX_SLOT_PER_BAG, /// 第1背包
    site_bag_2 = site_bag_1 + MAX_SLOT_PER_BAG, /// 第2背包
    site_bag_3 = site_bag_2 + MAX_SLOT_PER_BAG, /// 第3背包
    site_bag_4 = site_bag_3 + MAX_SLOT_PER_BAG, /// 第4背包

    // 仓库和背包一样分页,目前只有一个role_warehouse_size和role_warehouse_adv_size
    // 所以仓库格子按顺序开启,后续如果需要每页独立,添加role_warehouse_size_页,修改代码
    site_warehouse = site_bag_4 + MAX_SLOT_PER_BAG,                 /// 仓库222
    site_warehouse_0 = site_warehouse,                              /// 222
    site_warehouse_1 = site_warehouse_0 + MAX_SLOT_PER_BAG,         /// 264
    site_warehouse_2 = site_warehouse_1 + MAX_SLOT_PER_BAG,         /// 304
    site_warehouse_3 = site_warehouse_2 + MAX_SLOT_PER_BAG,         /// 342
    site_warehouse_adv = site_warehouse_3 + MAX_SLOT_PER_BAG,       /// 高级仓库382
    site_warehouse_adv_0 = site_warehouse_adv,                      /// 382
    site_warehouse_adv_1 = site_warehouse_adv_0 + MAX_SLOT_PER_BAG, /// 422
    site_warehouse_adv_2 = site_warehouse_adv_1 + MAX_SLOT_PER_BAG, /// 462
    site_warehouse_adv_3 = site_warehouse_adv_2 + MAX_SLOT_PER_BAG, /// 502
    site_bag_end = site_warehouse_adv_3 + MAX_SLOT_PER_BAG,         /// 542

    site_expand_0 = site_bag_end, /// 背包0扩充位置                 /// 542
    site_expand_1,                /// 背包1扩充位置
    site_expand_2,                /// 背包2扩充位置
    site_expand_3,                /// 背包3扩充位置
    site_expand_4,                /// 背包4扩充位置
    site_expand_end = 550,        /// 背包扩充结束

	site_glasses,                           /// 眼镜          /// 551
	site_bracelet_0,                        /// 手镯0
	site_bracelet_1,                        /// 手镯1
	site_mask,                              /// 面甲
	site_kneelet,                           /// 护膝
	site_chestplate,                        /// 护胸
	site_cloak,                             /// 披风
	site_earrings,                          /// 耳环
	site_headwear,                          /// 头饰
	site_legguard,                          /// 护腿
	site_jade,                              /// 玉佩
	site_instrument,                        /// 乐器
	site_hangings,                          /// 挂饰
	site_fashion_weapon,                    /// 时装武器
	site_equip_reserved_1,
	site_equip_reserved_2,
	site_equip_reserved_3,
	site_equip_reserved_4,
	site_equip_reserved_5,
	site_equip_reserved_6,
	site_equip_reserved_7,
	site_equip_reserved_8,
	site_equip_reserved_9,
    site_equip_reserved_end,        /// 574
	// 自定义装备位
	site_equip_custom_0 = 575,
	site_equip_custom_1,
	site_equip_custom_2,
	site_equip_custom_3,
	site_equip_custom_4,
	site_equip_custom_5,
	site_equip_custom_6,
	site_equip_custom_7,
	site_equip_custom_8,
	site_equip_custom_9,
	site_equip_custom_10,
	site_equip_custom_11,
	site_equip_custom_12,
	site_equip_custom_13,
	site_equip_custom_14,
	site_equip_custom_15,
	site_equip_custom_16,
	site_equip_custom_17,
	site_equip_custom_18,
	site_equip_custom_19,
	site_equip_custom_end = 699,

    site_fashion_helmet = 700,
    site_fashion_wrist_0,
    site_fashion_armor,
    site_fashion_juju,
    site_fashion_shoes,
    site_fashion_shoulder,
    site_fashion_necklace,
    site_fashion_ring_0,
    site_fashion_medal,
    site_fashion_gem,
    site_fashion_wings,
    site_fashion_amulet,
    site_fashion_mount,
    site_fashion_shield,
    site_fashion_hat,
    site_fashion_gloves,
    site_fashion_jewelry,

    site_fashion_wrist_1,
    site_fashion_ring_1,

    site_fashion_glasses,
    site_fashion_bracelet_0,
    site_fashion_bracelet_1,
    site_fashion_mask,
    site_fashion_kneelet,
    site_fashion_chestplate,
    site_fashion_cloak,
    site_fashion_earrings,
    site_fashion_headwear,
    site_fashion_legguard,
    site_fashion_jade,
    site_fashion_instrument,
    site_fashion_hangings,

    site_fashion_end = 750,

    // 物品快捷栏位
    site_item_quick_bar_0 = 800,
    site_item_quick_bar_1,
    site_item_quick_bar_2,
    site_item_quick_bar_3,
    site_item_quick_bar_4,
    site_item_quick_bar_5,
    site_item_quick_bar_6,
    site_item_quick_bar_7,
    site_item_quick_bar_8,
    site_item_quick_bar_9,
    site_item_quick_bar_10,
    site_item_quick_bar_11,
    site_item_quick_bar_12,
    site_item_quick_bar_13,
    site_item_quick_bar_14,
    site_item_quick_bar_15,
    site_item_quick_bar_16,
    site_item_quick_bar_17,
    site_item_quick_bar_18,
    site_item_quick_bar_19,
    site_item_quick_bar_20,
    site_item_quick_bar_21,
    site_item_quick_bar_22,
    site_item_quick_bar_23,
    site_item_quick_bar_24,
    site_item_quick_bar_25,
    site_item_quick_bar_26,
    site_item_quick_bar_27,
    site_item_quick_bar_28,
    site_item_quick_bar_29,
    site_item_quick_bar_end = 1000,
    site_end = site_item_quick_bar_end,   /// 结束格
};

/// 物品的品质
enum item_quality {
    quality_general = 0, /// 普通, 白色
};

/// 物品属性
enum item_attr {
    item_att_pos = 0,        /// 物品当前所在的位置
    item_att_amount,         /// 物品当前的堆叠数量
    item_att_durability,     /// 物品当前耐久
    item_att_max_durability, /// 物品最大耐久
    item_att_use_count,      /// 物品当前的使用次数
    item_att_is_bound,       /// 物品是否被绑定
    item_att_life,           /// 物品存活时间
    item_att_skill_id,       /// 技能id

    item_att_name,           /// 物品name
    item_att_color,          /// 物品color
    item_att_icon,           /// 物品icon
    item_att_quality,        /// 物品quality
    item_att_subtype,        /// 物品subtype
    item_att_max,
};

enum skill_type {
    skill_type_passive,     /// 被动类技能
    skill_type_switch,      /// 开关类普攻
    skill_type_status,      /// 状态类普攻
    skill_type_action,      /// 攻击动作类
    skill_type_cast,        /// 施法类技能
    skill_type_fixed,       /// 固定动作类
    skill_type_direct,      /// 直接释放，不作条件判断
};

enum skill_hurt_type {
    skill_hurt_type_phy = 1,
    skill_hurt_type_mag = 2,
    skill_hurt_type_tao = 3
};

enum skill_cast_way {
    skill_cast_direct   = 1,    /// 直接释放
    skill_cast_target   = 2,    /// 对目标
    skill_cast_grid     = 3,    /// 对逻辑格
};

enum skill_special_effect_type {
    skill_special_trap_trigger  = 1,        /// 陷阱类触发
    skill_special_trap_rt       = 2,        /// 陷阱类实时
    skill_special_summon        = 3,        /// 召唤类
    skill_special_fly           = 4,        /// 弹道类
    skill_special_repell        = 5,        /// 击退类
    skill_special_doplganr      = 6,        /// 分身
};

enum skill_range_type {
    skill_range_type_point      = 0,
    skill_range_type_line       = 1,
    skill_range_type_rect       = 2,
    skill_range_type_cust       = 3
};

enum skill_target_type {
    skill_target_all            = 0,        /// 所有
    skill_target_self           = 1,        /// 对自己
    skill_target_monster        = 2,        /// 对怪物
    skill_target_player         = 3,        /// 对玩家
    skill_target_friend         = 4,        /// 对友方
};

enum skill_level_compare {
    skill_level_compare_no      = 0,        /// 无等级关系
    skill_level_compare_greater = 1,        /// 高于目标等级
    skill_level_compare_ge      = 2,        /// 高于或等于目标等级
};

enum skill_attached_buff {
    skill_buff_target           = 1,        /// 给目标加BUFF
    skill_buff_self             = 2,        /// 给自己加BUFF
    skill_buff_all              = 3,        /// 给所有获取到的目标加buff
};

enum teleport_type {
    teleport_nullptr = 0,
    teleport_rand_limit,  /// 本地图限制随机
    teleport_rand,        /// 本地图随机
    teleport_relive,      /// 复活点
    teleport_relive_rand, /// 复活点所在地图随机
    teleport_relive_max,
};

enum repel_type {
    repel_type_nullptr = 0, /// 无
    repel_type_collide,     /// 冲撞
    repel_type_repelled,    /// 击退
};

enum repel_cmp_type {
    repel_cmp_nullptr = 0,   /// 无
    repel_cmp_less_equal,    /// 小于等于
    repel_cmp_greater_equal, /// 大于等于
};

enum repel_collide_type {
    repel_collide_nullptr = 0, /// 无
    repel_collide_with_target, /// 带目标冲撞
    repel_collide_no_target,   /// 无目标冲撞
};

enum role_attr_ext {
    role_exp = 0,      /// 经验
    role_ingot,        /// 元宝
    role_bind_ingot,   /// 绑定元宝
    role_integral,     /// 积分
    role_gold,         /// 金币
    role_bind_gold,    /// 绑定金币
    role_gold_deposit, /// 仓库金币
    role_inner_force_exp,   /// 内功经验
    role_attr_ext_min = role_exp,
    role_attr_ext_max = role_inner_force_exp,

};

enum atk_mode_type {
    atk_mode_all = 0,
    atk_mode_peace,
    atk_mode_team,
    atk_mode_guild,
    atk_mode_pk,
    atk_mode_alliance,
    atk_mode_camp,
    atk_mode_max,
};

enum restore_type {
    restore_type_nullptr = 0,
    restore_type_quick,
    restore_type_tao,
    restore_type_max,
};

enum shape_type {
    shape_type_point    = 0,
    shape_type_line     = 1,
    shape_type_rect     = 2,
    shape_type_cust     = 3,
};

enum fan_degree {
    fan_degree_90   = 1,
    fan_degree_180  = 2,
    fan_degree_270  = 3,
    fan_degree_360  = 4
};

enum buff_relation_type {
    buff_relation_nullptr = 0,
    buff_relation_replace,
    buff_relation_offset,
    buff_relation_ignore,
    buff_relation_max,
};

enum quick_bar_type {
    quick_bar_nullptr = 0,
    quick_bar_item,
    quick_bar_skill,
    quick_bar_max,
};

enum relive_type {
    relive_skill = 0, //技能复活
    relive_local,     //原地复活
    relive_map,       //回城复活
    relive_dungeon,   //副本复活
};
enum item_enhance_type {
    enhance_type_phy = 0,
    enhance_type_mag,
    enhance_type_tao,
    enhance_type_max,
};

enum stall_state_type {
    stall_state_nullptr = 0, /// 未摆摊
    stall_state_ready,       /// 摆摊准备
    stall_state_ok,          /// 摆摊中
    stall_state_max,
};

enum stall_price_type {
    stall_price_gold = 0, /// 金币
    stall_price_ingot,    /// 元宝
	stall_price_integral,   /// 积分
    stall_price_bind_gold,/// 绑定金币
    stall_price_bind_ingot,/// 绑定元宝
    stall_price_max,
};

enum item_drop_type {
    item_drop_nullptr = 0,
    item_drop_active,
    item_drop_player,
    item_drop_monster,
    item_drop_script,
    item_drop_map,
    item_drop_map_auto,
    item_drop_max,
};

enum item_special_drop_type {
    item_special_drop_never = 1,
    item_special_drop_on_logout = 2,
    item_special_drop_on_jump_map = 4,
    item_special_drop_on_die = 8,
    item_special_disappear_on_die = 16,
    item_special_drop_max,
};

enum servant_source_type {
    servant_source_nullptr = 0,
    servant_source_catch,  /// 捕捉
    servant_source_summon, /// 召唤
    servant_source_max,
};

enum pk_state_type {
    pk_state_nullptr = 0,
    pk_state_white,  /// 白名
    pk_state_yellow, /// 黄名
    pk_state_gray,   /// 灰名
    pk_state_red,    /// 红名
    pk_state_max,
};

enum region_type {
    region_safe = 0,  ///安全区
    region_stall,     ///摆摊区
    region_athletics, ///竞技区
    region_relive,    ///复活区
    region_red_name,  ///红名区
    region_born,      ///出生区域
    region_jump,      ///跳转区域
    region_mine,      ///矿区
    region_through,   ///可穿透区
    region_num,
};

enum player_switch_type {
    player_switch_type_friend = 0,
    player_switch_type_team,
    player_switch_type_max,
};

enum normal_attack_type {
    normal_attack_nullptr = 0,
    normal_attack_liehuo,
    normal_attack_gongsha,
    normal_attack_cisha,
    normal_attack_banyue,
    normal_attack_self,
    normal_attack_max,
};

enum skill_find_target_type {
    skill_find_target_on_spell = 0,
    skill_find_target_after_delay,
    skill_find_target_max,
};

enum event_type {
    event_nullptr = 0,
    event_fire_wall,
    event_max,
};

enum repair_type {
    repair_type_nullptr = 0,
    repair_type_normal,
    repair_type_ex,
    repair_type_max,
};

enum map_type {
    map_common = 0, //普通地图
    map_dungeon,    //副本地图
};

enum role_last_time_type {
    role_last_login = 0, //角色最后登陆时间FLAG
    role_online,         //角色在线时间FLAG
    role_max_online,     //角色总在线时长FLAG
    role_last_attack,    //角色最后攻击时间FLAG
    role_last_move,      //角色最后移动时间FLAG
    role_last_chat,      //角色最后聊天时间FLAG
    role_today_online,   //角色当天在线时长
    role_last_logout,    //角色最后下线时间FLAG
};

enum role_attr_name_type {
    role_account_name = 0, //角色帐号名的FLAG
    role_ip,               //角色的IP地址
    role_user_name,        //角色用户名的FLAG
    role_home_map,         //角色回城地图的FLAG
    role_home_map_key,     //角色回城地图的keyname
    role_alias,            //角色称谓的FLAG
    role_guild,            //角色公会名的FLAG
    role_current_map,      //角色当前地图名的FLAG
    role_current_map_key,  //角色当前地图的keyname
};

enum role_attr_id_type {
    role_guild_id = 0,   //角色公会ID的FLAG
    role_current_map_id, //玩家所属地图ID的FLAG
    role_home_map_id,    //玩家回城地图ID(GUID)的FLAG
};

enum role_attr_modify_type {
    role_attr_add = 10000, //角色属性增加
    role_attr_sub,         //角色属性减少
    role_attr_equal,       //角色属性设置
};

enum param_type {
	param_type_null = 0,
	param_type_int8,
	param_type_uint8,
	param_type_int16,
	param_type_uint16,
	param_type_int32,
	param_type_uint32,
	param_type_int64,
	param_type_uint64,
	param_type_string,
	param_type_max,
};

/// 物品绑定需求
enum bind_require {
    bind_require_false = 0, /// 必须非绑定
    bind_require_true,      /// 必须绑定
    bind_require_any,       /// 绑定非绑定都可以
    bind_require_max,
};

enum site_range {
    site_range_all = 0,
    site_range_bag,
    site_range_equip,
    site_range_quick,
};

enum rand_type {
    rand_type_only_one = 0, /// only one
    rand_type_rand,         /// rand
    rand_type_max,
};

enum trigger_type {
    trigger_nullptr                             = 0,
    /**
    * @brief            服务器启动
    * @return           无
    */
    trigger_system_start                        = 1,        /// system call, don't need to manually add
    /**
    * @brief            第一次登陆
    * @param1           角色guid
    * @return           无
    */
    trigger_first_in_game                       = 2,
    /**
    * @brief            登陆
    * @param1           角色guid
    * @return           无
    */
    trigger_login                               = 3,
    /**
    * @brief            登出
    * @param1           角色guid
    * @return           无
    */
    trigger_logout                              = 4,
    /**
    * @brief            通知客户端攻沙开始
    * @return           无
    */
    trigger_castle_war_start                    = 5,
    /**
    * @brief            通知客户端攻沙结束
    * @return           无
    */
    trigger_castle_war_end                      = 6,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_castle_war_init                     = 7,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_gp                                  = 8,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_gp_one                              = 9,
     /**
    * @brief            地图创建
    * @param1           地图guid
    * @param2           地图名字
    * @return           无
    */
    trigger_map_create                          = 200,      /// system call, don't need to manually add
     /**
    * @brief            地图关闭
    * @param1           地图guid
    * @param2           地图名字
    * @return           无
    */
    trigger_map_destroy                         = 201,      /// system call, don't need to manually add
    /**
    * @brief            进入地图
    * @param1           角色guid
    * @return           无
    */
    trigger_enter_map                           = 202,
    /**
    * @brief            离开地图
    * @param1           角色guid
    * @return           无
    */
    trigger_leave_map                           = 203,
    /**
    * @brief            物品出现在地图
    * @param1           地图guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           物品名字
    * @param5           x
    * @param6           y
    * @return           无
    */
    trigger_item_appear                         = 204,
    /**
    * @brief            物品消失在地图
    * @param1           地图guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           物品名字
    * @param5           x
    * @param6           y
    * @return           无
    */
    trigger_item_disappear                      = 205,
    /**
    * @brief            怪物出现在地图
    * @param1           怪物guid
    * @param2           怪物模板id
    * @param3           怪物名字
    * @param4           x
    * @param5           y
    * @return           无
    */
    trigger_monster_appear                      = 206,
    /**
    * @brief            怪物消失在地图
    * @param1           怪物guid
    * @param2           怪物模板id
    * @param3           怪物名字
    * @param4           x
    * @param5           y
    * @return           无
    */
    trigger_monster_disappear                   = 207,
    /**
    * @brief            npc出现在地图
    * @param1           npcguid
    * @param2           npc模板id
    * @param3           npc名字
    * @param4           x
    * @param5           y
    * @return           无
    */
    trigger_npc_appear                          = 208,
    /**
    * @brief            npc消失在地图
    * @param1           npcguid
    * @param2           npc模板id
    * @param3           npc名字
    * @param4           x
    * @param5           y
    * @return           无
    */
    trigger_npc_disappear                       = 209,
    /**
    * @brief            宠物出现在地图
    * @param1           宠物guid
    * @param2           宠物模板id
    * @param3           宠物名字
    * @param4           x
    * @param5           y
    * @return           无
    */
    trigger_pet_appear                          = 210,
    /**
    * @brief            宠物消失在地图
    * @param1           宠物guid
    * @param2           宠物模板id
    * @param3           宠物名字
    * @param4           x
    * @param5           y
    * @return           无
    */
    trigger_pet_disappear                       = 211,
    /**
    * @brief            镜像出现在地图
    * @return           无
    */
    trigger_doplganr_appear                    = 212,
    /**
    * @brief            角色升级
    * @param1           角色guid
    * @param2           等级
    * @return           无
    */
    trigger_level_up                            = 300,
    /**
    * @brief            角色穿装备前
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           装备位置
    * @return           无
    */
    trigger_pre_equip                           = 301,
    /**
    * @brief            角色穿装备
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           装备位置
    * @return           bool 是否可以穿戴
    */
    trigger_post_equip                          = 302,
     /**
    * @brief            角色脱下装备前
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           装备位置
    * @return           bool 是否可以脱下
    */
    trigger_pre_un_equip                        = 303,
    /**
    * @brief            角色脱下装备
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           装备位置
    * @return           无
    */
    trigger_post_un_equip                       = 304,
    /**
    * @brief            移动触发
    * @param1           角色guid
    * @param2           位置坐标x
    * @param3           位置坐标y
    * @param4           移动类型  走 = 0, 跑 = 1, 跳 = 2
    * @return           无
    */
    trigger_move                                = 305,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_spell                           = 306,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_spell                               = 307,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_mining                          = 308,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_mining                              = 309,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_item_apply                      = 310,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_apply                          = 311,
    /**
    * @brief            物品拾取
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           物品位置坐标x
    * @param5           物品位置坐标y
    * @return           bool  是否能拾取
    */
    trigger_pre_item_pickup                     = 312,
    /**
    * @brief            物品拾取
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           物品价值
    * @return           无
    */
    trigger_item_pickup                         = 313,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_item_drop                       = 314,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_drop                           = 315,      /// 扔东西的触发
    /**
    * @brief            死亡触发
    * @param1           死亡角色guid
    * @param2           攻击角色guid
    * @return           bool 是否死亡
    */
    trigger_pre_die                             = 316,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_post_die                            = 317,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_kill                                = 318,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_attack                              = 319,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_hp                                  = 320,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_mp                                  = 321,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_damage_process                      = 322,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_restore_process                     = 323,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_teleport                            = 324,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_catch                           = 325,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_catch                               = 326,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_dig_meat                        = 327,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_dig_meat                            = 328,
    /**
    * @brief            添加buff前检测
    * @param1           buffID
    * @param2           玩家guid
    * @param3           释放者guid
    * @return           是否添加buff
    */
    trigger_check_add_buff                      = 329,
    /**
    * @brief            添加buff
    * @param1           玩家guid
    * @param2           buffid
    * @param3           宿主guid
    * @return           无
    */
    trigger_add_buff                            = 330,
    /**
    * @brief            移除buff
    * @param            玩家guid
    * @param            buffid
    * @return           无
    */
    trigger_remove_buff                         = 331,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_drop                            = 332,      /// 要不要爆东西
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_post_drop                           = 333,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_drop_one                        = 334,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_post_drop_one                       = 335,      /// 掉了某个具体的东西
    /**
    * @brief            添加技能
    * @param1           玩家guid
    * @param2           技能id
    * @return           无
    */
    trigger_add_skill                           = 336,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_switch_skill                        = 337,
    /**
    * @brief            召唤
    * @param1           玩家guid
    * @param2           宠物guid
    * @return
    */
    trigger_summon                              = 338,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_process_pk                      = 339,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_post_process_pk                     = 340,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_create                              = 341,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_destroy                             = 342,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_npc_visit                           = 343,
    /**
    * @brief            跳地图前
    * @param1           string 玩家guid
    * @param2           string 当前地图guid
    * @param3           string 跳转至地图的guid
    * @return           是否跳转
    */
    trigger_pre_enter_jump                      = 344,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_equip_suit                          = 345,      /// 套装穿齐
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_un_equip_suit                       = 346,      /// 套装不齐
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_amount_zero                    = 347,      /// amount为0删除
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_use_zero                       = 348,      /// 使用次数为0删除
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_dur_zero                       = 349,      /// 耐久为0删除
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_timeup                         = 350,      /// 时效过期删除
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_add_exp                             = 351,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_monster_born                        = 352,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_player_relive                       = 353,
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_dungeon_end                         = 354,      /// 副本结束时回调
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_timer_check                         = 355,      /// 定时检查
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_add_exp_all                         = 356,      /// 所有获取经验
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_player_pre_die                      = 357,      /// 人物死亡前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_player_post_die                     = 358,      /// 人物死亡后触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_monster_pre_die                     = 359,      /// 怪物死亡前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_monster_post_die                    = 360,      /// 怪物死亡后触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_attack_ex                           = 361,      /// on_attack加强版，多了扣血值与技能参数
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_system_stop                         = 362,      /// system call, don't need to manually add
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_logout                          = 363,      ///
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_ride_request                        = 364,      /// 收到上马请求触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_unride_request                      = 365,      /// 收到下马请求触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_billin                              = 366,      /// 充值触发，只有玩家在线才会触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_mall                                = 367,      /// 商城消费触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_mall                            = 368,      /// 商城消费前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_escorter_fail                       = 369,      /// 护送怪失败,系统级触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_escorter_far                        = 370,      /// 护送怪过远,系统级触发
    /**
    * @brief            buff触发回调
    * @params1          角色guid
    * @params2          buffID
    * @return           无
    */
    trigger_apply_buff                          = 371,      /// buff触发回调
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_monster_in_fight                    = 372,      /// 怪物进入战斗状态触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_monster_out_fight                   = 373,      /// 怪物退出战斗状态触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_player_pre_curse                    = 374,      /// 武器被诅咒前触发
    /**
    * @brief            色受到伤害时触发
    * @params1          施法者guid
    * @params2          受击者guid
    * @params3          技能id
    * @return           返回提定伤害数值 table{["Harm"]=伤害数值, ["type"]=伤害类型}
    */
    trigger_role_pre_harm                       = 375,      /// 角色受到伤害时触发,返回提定伤害数值
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_npc_buy                         = 376,      /// npc购买前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_npc_buy                             = 377,      /// npc购买触发
    /**
    * @brief            摆摊前触发
    * @params1          摆摊者guid
    * @return           是否可以摆摊
    */
    trigger_pre_stall                           = 378,      /// 摆摊前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_hack_check                          = 379,      /// 外挂检查
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_auto_add_gold                       = 380,      /// 杀怪自动加金币
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_hack_check2                         = 381,      /// 外挂检查
    /**
    * @brief            摆摊前触发
    * @params1          行会guid
    * @params2          行会名
    * @params3          角色guid
    * @params4          行会操作类型
    * @params5          角色名字
    * @params6          创建者guid
    * @return           无
    */
    trigger_family_member_ntf                   = 382,      /// 行会事件
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_stall_buy                       = 383,      /// 购买摆摊物品前触发
    /**
    * @brief            行会创建销毁触发
    * @params1          行会guid
    * @params2          行会名
    * @params3          创建者guid
    * @return           无
    */
    trigger_family_ntf                          = 384,      /// 行会创建销毁触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_dur_zero_ex                    = 385,      /// 耐久为0删除扩展
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_dummy_pre_die                       = 386,      /// 假人死亡前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_dummy_post_die                      = 387,      /// 假人死亡后触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_item_attr_zero                      = 388,      /// 物品属性变为0触发
    /**
    * @brief            无实现
    * @return           无
    */
	trigger_attacker_pre_harm                   = 389,      /// 攻击者受到伤害时触发,返回固定伤害数值
    /**
    * @brief            角色升级前触发
    * @params1          角色guid
    * @params2          等级
    * @params3          改变经验值
    * @return           table {["BeUpgrade"] = (bool)是否可以升级，["AddExp"] = (uint64_t)增加的经验}
    */
	trigger_pre_level_up                        = 390,      /// 角色升级前触发
	trigger_pre_add_gray                        = 391,      /// 角色变灰名前触发
    /**
    * @brief            申请加入行会前触发
    * @params1          角色guid
    * @params2          行会guid
    * @return           无
    */
	trigger_pre_join_family                     = 392,      /// 申请加入行会前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_invite_family                   = 393,      /// 邀请加入行会前触发
    /**
    * @brief            无实现
    * @return           无
    */
    trigger_pre_relate_family                   = 394,      /// 联盟或敌对行会前触发
    /**
    * @brief            无实现
    * @return           无
    */
	trigger_billin_ex                           = 395,      /// 充值触发玩家在不在线都会触发
    /**
    * @brief            无实现
    * @return           无
    */
	trigger_player_change_name                  = 396,      /// 玩家改名结果触发
    /**
    * @brief            无实现
    * @return           无
    */
	trigger_sub_ingot                           = 397,      /// 玩家扣元宝触发
    /**
    * @brief            销毁角色触发
    * @params1          角色guid
    * @return           无
    */
    trigger_role_destroyed                      = 398,      /// 销毁角色触发
    /**
    * @brief            行会申请事件
    * @params1          角色guid
    * @params2          行会guid
    * @params3          行会名
    * @params4          受理人guid
    * @params5          是否已通过
    * @return           无
    */
    trigger_family_apply_ntf                    = 399,      /// 行会申请事件
    /**
    * @brief            掉落前申请事件
    * @params1          归属guid
    * @params2          怪物guid
    * @return           {{物品id(int32_t)，物品数量(int32_t)}，...}
    */
    trigger_pre_drop_rate                       = 400,      /// 掉落前申请事件
    /**
    * @brief            伤害后触发事件
    * @params1          施法者guid
    * @params2          受击者guid
    * @return           无
    */
    trigger_role_post_harm                      = 401,      /// 伤害后触发事件
    /**
    * @brief            拍卖行上架物品
    * @return           无
    */
    trigger_auction_add                         = 402,      /// 拍卖行上架物品
    /**
    * @brief            拍卖行下架物品
    * @return           无
    */
    trigger_auction_end                         = 403,      /// 拍卖行下架物品
    /**
    * @brief            拍卖行物品状态改变
    * @return           无
    */
    trigger_auction_start                       = 404,      /// 拍卖行物品状态改变
    /**
    * @brief            拍卖行物品价格发生改变
    * @return           无
    */
    trigger_auction_price_update                = 405,      /// 拍卖行物品价格发生改变
    /**
    * @brief            拍卖行物品价格发生改变
    * @params1          旧的赢家
    * @params2          新的赢家
    * @return           无
    */
    trigger_castle_owner_changed                = 406,      /// 沙巴克归属变更事件
    /**
    * @brief            掉落回调后回调
    * @param1           专属角色guid
    * @param2           当前角色guid
    * @param3           掉落物品表
    * @return           无
    */
    trigger_post_item_drop                      = 407,      /// 物品掉落后
    /**
    * @brief            buff信息更新后回调
    * @param1           角色guid
    * @param2           buffid
    * @param3           宿主guid
    * @return           无
    */
    trigger_update_buff                         = 408,      /// buff更新
    /**
    * @brief            怪物死后尸体是否消失前回调
    * @param1           怪物guid
    * @return           尸体是否消失
    */
    trigger_monster_disappear_pre_die           = 409,      /// 怪物死后消失前触发
    /**
    * @brief            发布悬赏结果回调
    * @param1           悬赏是否成功
    * @param2           发布悬赏者guid
    * @param3           发布悬赏者名
    * @param4           被悬赏者guid
    * @param5           被悬赏者名
    * @param6           赏金
    * @param7           悬赏描述信息
    * @param8           悬赏开始时间
    * @return           无
    */
    trigger_post_bounty_result                  = 410,      /// 发布悬赏结果
    /**
    * @brief            镖车怪物到达后回调
    * @param1           镖车怪物guid
    * @param2           镖车怪物模板id
    * @param3           镖车怪物当前x坐标
    * @param4           镖车怪物当前y坐标
    * @return           无
    */
    trigger_monster_biaoche_arrived             = 412,      /// 镖车怪物到达
    /**
    * @brief            掉落前组权重回调,需要提前赋值预掉落信息表LuaRet
    * @param1           专属角色guid
    * @param2           当前怪物guid
    * @return           掉落物品信息表
    */
    trigger_pre_drop_weight                     = 413,      /// 掉落前组权重
    /**
    * @brief            地图跳转后回调
    * @param1           角色guid
    * @param2           跳转前的地图guid
    * @param3           跳转后的地图guid
    * @param4           跳转后的地图x坐标
    * @param5           跳转后的地图y坐标
    * @param6           跳转类型
    * @return           无
    */
    trigger_post_enter_jump                     = 500,      /// 跳转后
    /**
    * @brief            使用技能后回调
    * @param1           角色guid
    * @param2           技能id
    * @param3           技能释放点x坐标
    * @param4           技能释放点y坐标
    * @param5           技能释放目标角色guid
    * @return           无
    */
    trigger_after_apply_skill                   = 501,      /// 使用技能后触发
    /**
    * @brief            丢弃物品是否销毁前回调
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品是否已绑定
    * @return           是否销毁物品
    */
    trigger_drop_item_whether_destroy           = 502,      /// 丢弃物品是否销毁
    /**
    * @brief            开始挖宝回调
    * @param1           角色guid
    * @param2           宝物guid
    * @param3           读条倒计时
    * @return           回调{(bool)是否可以挖宝,(uint32_t)挖宝时间}
    */
    trigger_start_dig                           = 503,      /// 开始挖宝
    /**
    * @brief            挖宝到时回调
    * @param1           角色guid
    * @param2           宝物guid
    * @return           无
    */
    trigger_dig_timesup                         = 504,      /// 挖宝到时
    /**
    * @brief            发放商品回调
    * @param1           角色guid
    * @param2           商品id
    * @param3           商品数量
    * @return           是否已发货
    */
    trigger_issue_goods                         = 505,      /// 发放商品
    /**
    * @brief            是否可以购买商品回调
    * @param1           角色guid
    * @param2           商品id
    * @param3           购买数量
    * @param4           购买价格
    * @return           是否可以购买
    */
    trigger_can_buy_goods                       = 506,      /// 是否可以购买商品
    /**
    * @brief            技能熟练度变化时回调
    * @param1           角色guid
    * @param2           技能id
    * @param3           变化量
    * @return           无
    */
    trigger_proficiency_changed                 = 507,      /// 技能熟练度变化
    /**
    * @brief            寄售行上架前回调
    * @param1           卖家guid
    * @param2           物品模板id
    * @param3           物品guid
    * @param4           货币类型
    * @param5           物品单价
    * @return           上架前判断结果{"Ret"=(bool)是否允许上架,"Type"=(uint8_t)货币类型,"TDTime"=(uint_t)上架时间}
    */
    trigger_pre_trade_delegate_sell             = 508,      /// 寄售行上架前
    /**
    * @brief            寄售行上架后回调
    * @param1           卖家guid
    * @param2           物品模板id
    * @param3           物品guid
    * @return           无
    */
    trigger_post_trade_delegate_sell            = 509,      /// 寄售行上架后
    /**
    * @brief            寄售行求购前回调
    * @param1           求购者guid
    * @param2           物品模板id
    * @param3           货币类型
    * @param4           物品单价
    * @param5           物品数量
    * @return           求购前判断结果{"Ret"=(bool)是否允许求购,"Type"=(uint8_t)货币类型,"TDTime"=(uint_t)求购时间}
    */
    trigger_pre_trade_delegate_buy              = 510,      /// 寄售行求购前
    /**
    * @brief            寄售行求购后回调
    * @param1           求购者guid
    * @param2           物品模板id
    * @param3           货币类型
    * @param4           物品单价
    * @param5           物品数量
    * @return           无
    */
    trigger_post_trade_delegate_buy             = 511,      /// 寄售行求购后
    /**
    * @brief            寄售行出售前回调
    * @param1           购买者guid
    * @param2           物品模板id
    * @param3           物品guid
    * @return           是否允许出售{"Ret"=(bool)结果}
    */
    trigger_pre_trade_market_sell               = 512,      /// 寄售行出售前
    /**
    * @brief            寄售行出售前回调
    * @param1           出售者guid
    * @param2           求购者guid
    * @param3           物品模板id
    * @param4           物品guid
    * @param5           物品数量
    * @return           无
    */
    trigger_post_trade_market_sell              = 513,      /// 寄售行出售后
    /**
    * @brief            寄售行购买前回调
    * @param1           购买者guid
    * @param2           物品模板id
    * @param3           货币类型
    * @param4           物品单价
    * @param5           购买数量
    * @return           是否允许购买{"Ret"=(bool)结果}
    */
    trigger_pre_trade_market_buy                = 514,      /// 寄售行购买前
    /**
    * @brief            寄售行购买后回调
    * @param1           购买者guid
    * @param2           上架者guid
    * @param3           物品模板id
    * @param4           物品guid
    * @param5           货币类型
    * @param6           物品单价
    * @param7           购买数量
    * @return           无
    */
    trigger_post_trade_market_buy               = 515,      /// 寄售行购买后
    /**
    * @brief            获取物品后回调
    * @param1           角色guid
    * @param2           物品guid
    * @param3           物品模板id
    * @param4           site位
    * @return           无
    */
    trigger_add_item                            = 516,      /// 获取物品
    /**
    * @brief            技能升级回调
    * @param1           角色guid
    * @param2           技能id
    * @param3           升级后等级
    * @return           无
    */
    trigger_skill_level_up                      = 517,      /// 技能升级事件
    /**
    * @brief            角色属性变化回调
    * @param1           角色guid
    * @param2           属性id
    * @param3           32位属性还是64位属性
    * @param4           变化前值
    * @param5           变化后值
    * @return           无
    */
    trigger_role_update_attr                    = 518,      /// 角色属性更新
    /**
    * @brief            玩家掉落物品前回调
    * @param1           角色guid
    * @param2           击杀者guid
    * @return           lua对象,预掉落信息{{(int32_t)site位1,(int32_t)权重1},...}
    */
    trigger_player_pre_drop                     = 519,      /// 玩家掉落前事件
    /**
    * @brief            玩家掉落回调,需要提前赋值预掉落信息表LuaRet
    * @param1           角色guid
    * @param2           击杀者guid
    * @return           lua对象,最终掉落信息{{(int32_t)site位1,(int32_t)site位2},...}
    */
    trigger_player_drop                         = 520,      /// 玩家掉落事件
    /**
    * @brief            玩家掉落后回调,暂未使用
    */
    trigger_player_post_drop                    = 521,      /// 玩家掉落后事件
    /**
    * @brief            玩家兑换码领取后回调
    * @param1           角色guid
    * @param2           错误码
    * @param3           错误信息
    * @return           无
    */
    trigger_player_redeem_code                  = 522,      /// 玩家兑换码领取后事件
    /**
    * @brief            技能熟练度更新前回调
    * @param1           角色guid
    * @param2           技能id
    * @param3           获得最小熟练度
    * @param4           获得最大熟练度
    * @return           获得的熟练度
    */
    trigger_proficiency_pre_changed             = 523,      /// 修改技能熟练度之前
    /**
    * @brief            玩家兑换码领取后回调
    * @param1           角色guid
    * @param2           错误码
    * @param3           错误信息
    * @param4           礼包名
    * @param5           礼包内容
    * @return           无
    */
    trigger_player_redeem_code2                 = 524,      /// 激活码2领取后事件
    /**
    * @brief            玩家改名后回调
    * @param1           角色guid
    * @param2           错误码
    * @param3           原名
    * @return           无
    */
    trigger_player_set_name                     = 525,      /// 玩家改名后事件
    /**
    * @brief            宠物跳向主人回调
    * @param1           宠物guid
    * @param2           宠物主人guid
    * @return           无
    */
    trigger_pet_jump_to_master                  = 526,      /// 宠物跳向主人事件
    /**
    * @brief            分身跳向主人回调
    * @param1           分身guid
    * @param2           分身主人guid
    * @return           无
    */
    trigger_player_doplganr_jump_to_master      = 527,      /// 分身跳向主人事件
    /**
    * @brief            自定义变量修改前回调
    * @param1           角色guid
    * @param2           变量名
    * @param3           变量值
    * @param4           变量类型
    * @return           是否允许修改
    */
    trigger_pre_set_customer_var                = 528,      /// 自定义变量修改前事件(针对gm)
    /**
    * @brief            自定义变量修改后回调
    * @param1           角色guid
    * @param2           变量名
    * @param3           变量值
    * @param4           变量类型
    * @return           无
    */
    trigger_post_set_customer_var               = 529,      /// 自定义变量修改后事件
    /**
    * @brief            怪物生存时间到达回调
    * @param1           怪物guid
    * @return           无
    */
    trigger_monster_arrived_exist_time          = 530,      /// 怪物生存时间到达的事件
    /**
    * @brief            掉蓝前回调
    * @param1           角色guid
    * @param2           技能id
    * @param3           掉蓝量
    * @return           最终掉蓝量
    */
    trigger_pre_decrease_mp                     = 531,      /// 掉蓝前触发
    /**
    * @brief            分身继承的属性回调
    * @param1           分身主人guid
    * @return           属性信息
    */
    trigger_pre_Get_Doplganr_Att                = 532,      //分身继承的属性
    /**
    * @brief            分身判断释放使用技能回调
    * @param1           分身guid
    * @param2           分身主人guid
    * @param3           怪物数量
    * @param4           玩家数量
    * @param5           技能信息
    * @return           可释放的技能id
    */
    trigger_pre_Doplganr_choose_skill           = 533,      //分身判断释放使用技能
    /**
    * @brief            快捷栏物品位置移动是否合理回调
    * @param1           物品id
    * @param2           物品site位
    * @return           是否允许移动
    */
    trigger_item_CheckSite                      = 534,      //快捷栏物品位置移动是否合理
    /**
    * @brief            领取删档奖励前回调
    * @param1           角色guid
    * @param2           返利金额
    * @return           是否已经发放
    */
    trigger_rebate_money                        = 535,      /// 领取删档奖励
    /**
    * @brief            GM命令转lua处理
    * @param1           命令id
    * @param2           string 可解析字符串
    * @return           是否成功
    */
    trigger_gm_cmd                              = 536,      //GM命令进脚本处理
	/**
    * @brief            重新计算属性前
    * @return           无
    */
    trigger_pre_recalculate = 537,      //
	/**
    * @brief            重新计算属性中
    * @return           无
    */
    trigger_recalculate = 538,      //
    

        /**
    * @brief            主人离线是否删除召唤物
    * @param1           主人guid
    * @param2           召唤物guid
    * @return           是否删除
    */
    trigger_remove_summon_monster_when_logout = 539,      //

    /**
    * @brief            主人离线是否删除召唤物
    * @param1           主人guid
    * @param2           召唤物guid
    * @return           是否删除
    */
    trigger_remove_summon_monster_when_different_map = 540,      //
    /**
    * @brief            加入离开队伍
    * @param1           队伍id
    * @return           无
    */
    trigger_team = 541,      //

    /**
    * @brief            副本地图中存在玩家时请求是否关闭副本
    * @param1           副本ID
    * @return           是否关闭副本
    */
    trigger_whether_destroy_dgn_when_have_players = 542,

    /**
    * @brief            行会战开始
    * @param1           行会1guid
    * @param2           行会2guid
    * @return           无
    */
    trigger_guild_war_start = 543,

    /**
    * @brief            行会战结束
    * @param1           行会1guid
    * @param2           行会2guid
    * @return           无
    */
    trigger_guild_war_end = 544,
    /**
    * @brief            玩家死亡掉落后回调,需要提前赋值预掉落信息表LuaRet
    * @param1           角色guid
    * @param2           击杀者guid
    * @return           无
    *                   LuaRet获取最终掉落物品列表{{(int32_t)物品id,(int32_t)数量},...}
    */
    trigger_player_drop_item_list = 545,      /// 玩家死亡掉落物品列表

    trigger_max,
};

/// quest type
enum quest_type {
    quest_type_nullptr = 0, /// nullptr
    quest_type_main,        /// 主线
    quest_type_side,        /// 支线
    quest_type_ring,        /// 跑环
    quest_type_cycle,       /// 循环
    quest_type_max,
};

enum quest_abort_type {
    quest_cannot_abort = 1,         /// 不可放弃
    quest_can_abort,                /// 可以放弃
    quest_abort_cannot_accept,      /// 可以放弃且无法再接取
};

enum quest_accept_type {
    quest_accept_from_npc = 1,      /// 从NPC领任务
    quest_auto_accept,              /// 等级触发自动接取
};

enum quest_deliver_type {
    quest_deliver_to_npc = 1,       /// 向NPC交任务
    quest_auto_deliver,             /// 完成条件满足后自动结束
};

enum quest_achieve_type {
    quest_achev_talk_to_npc = 1,    /// 与NPC对话
    quest_achev_kill_monster,       /// 击杀怪物
    quest_achev_collect_item,       /// 收集道具
    quest_achev_level_judge,        /// 角色等级判定
    quest_achev_collect_equipment,  /// 角色装备收集判断
    quest_achev_script,             /// 脚本编号
    quest_achev_move_to_pos,        /// 移动到指定地图指定坐标
};

enum quest_time_type {
    quest_relative_time = 1,        /// 相对时间
    quest_abs_time,                 /// 绝对时间
    quest_period_time,              /// 固定时间段
};

enum quest_state {

    quest_state_idle                = 0,        // 空闲
    quest_state_accepting           = 1,        // 准备接任务
    quest_state_doing               = 2,        // 做任务
    quest_state_ready               = 3,        // 任务完成准备提交
    quest_state_complete            = 4,        // 任务完成，结束任务
};


/// quest_track_state
enum quest_track_state {
    quest_track_state_nullptr = 0, /// nullptr
    quest_track_state_group_hunting,
    quest_track_state_hunting,
    quest_track_state_huntlevel,
    quest_track_state_group_item,
    quest_track_state_item,
    quest_track_state_apply_item,
    quest_track_state_npc,
    quest_track_state_max,
};

enum item_logic_type {
    item_logic_type_all = 0,

    item_logic_type_money,
    item_logic_type_equip,
    item_logic_type_material,
    item_logic_type_book,
    item_logic_type_drug,
    item_logic_type_function,
    item_logic_type_other,

    item_logic_type_max,
};

enum equip_logic_type {
    equip_logic_all = 0,
    equip_logic_weapon,   /// 武器
    equip_logic_armor,    /// 衣服
    equip_logic_helmet,   /// 头盔
    equip_logic_necklace, /// 项链
    equip_logic_wrist,    /// 护腕
    equip_logic_ring,     /// 戒指
    equip_logic_shoes,    /// 鞋子

    equip_logic_max,
};

enum material_logic_type {
    material_logic_all = 0,
    material_logic_image,  /// 图样
    material_logic_spirit, /// 精元
    material_logic_mine,   /// 矿石
    material_logic_refine, /// 精炼
    material_logic_other,  /// 其他

    material_logic_max,
};

enum book_logic_type {
    book_logic_all = 0,
    book_logic_war, /// 战士类
    book_logic_mag, /// 法师类
    book_logic_tao, /// 道士类

    book_logic_max,
};

enum drug_logic_type {
    drug_logic_all = 0,
    drug_logic_normal,    /// 普通类
    drug_logic_immediate, /// 瞬回类
    drug_logic_other,     /// 其他类

    drug_logic_max,
};

enum function_logic_type {
    function_logic_all = 0,
    function_logic_poison, /// 符毒
    function_logic_fly,    /// 传送
    function_logic_bag,    /// 格子扩展
    function_logic_other,  /// 其他

    function_logic_max,
};

enum log_action_type {
    log_action_nullptr = 0,
    log_action_item_site_fixed,     /// 位置已修正
    log_action_item_site_error,     /// 位置修正失败
    log_action_item_error,          /// 物品出现错误，系统自动删除
    log_action_buff_error,          /// buff出现错误
    log_action_item_stream,         /// 物品序列化删除
    log_action_crash,               /// 程序异常
    log_action_item_to_json_one,    /// 物品紧急保存一个
    log_action_item_to_json,        /// 物品紧急保存
    log_action_bag_item_site_error, /// 背包物品格子错误
    log_action_item_guid_error,     /// 物品guid错误
    log_action_item_guid_dup,       /// 物品guid重复
    log_action_item_site_dup,       /// 物品site重复
    log_action_player_die = 1000,
    log_action_player_chat,
    log_action_player_level_up,
    log_action_player_exp,
    log_action_player_ingot,
    log_action_player_bind_ingot,
    log_action_player_integral,
    log_action_player_gold,
    log_action_player_bind_gold,
    log_action_player_gold_deposit,
    log_action_player_use_item,
    log_action_player_buy_item,
    log_action_player_sell_item,
    log_action_player_drop_item,
    log_action_player_pickup_item,
    log_action_player_mall_item,
    log_action_player_enter_map,
    log_action_player_leave_map,
    log_action_player_die_drop_item,
    log_action_player_trade_p2p_item,
    log_action_player_trade_stall_item,
    log_action_player_login,
    log_action_player_logout,
    log_action_player_item_dur_zero,
    log_action_player_item_usecount_zero,
    log_action_player_item_time_zero,
    log_action_player_user_cmd,
    log_action_player_gm_cmd,
    log_action_player_market_sell,
    log_action_player_market_buy,
    log_action_player_market_delegate,
    log_action_player_mail_pick,
    log_action_player_mail_send,
    log_action_player_item_e2e,
    log_action_player_item_e2b,
    log_action_player_item_b2e,
    log_action_player_item_b2b,
    log_action_player_item_b2w,
    log_action_player_item_b2wa,
    log_action_player_item_be2be,
    log_action_player_item_b2be,
    log_action_player_item_be2b,
    log_action_player_item_w2w,
    log_action_player_item_w2b,
    log_action_player_item_wa2wa,
    log_action_player_item_wa2b,
    log_action_player_item_amount_zero,
    log_action_player_kick,
    log_action_player_create,
    log_action_player_delete,
    log_action_player_recover,
    log_action_player_dig_item,
    log_action_player_mine_item,
    log_action_player_gm_item,
    log_action_player_gm_map_item,
    log_action_player_item_drop_map_auto, /// 自动掉地板
    log_action_player_item_drop_unknown,  /// 未知掉落
    log_action_player_identify_item,
    log_action_player_modify_attr,         ///修改玩家属性
    log_action_player_trade_stall_item_in, ///买入
    log_action_destroy_item_stack,         ///堆叠物品销毁
    log_action_player_item_p2h,            ///物品从主人移动到英雄
    log_action_player_item_h2p,            ///物品从英雄移动到主人
    log_action_player_item_h2h,            ///英雄之间交换物品
	log_action_player_mail_delete,
    log_action_player_arrange_b = 1500,
    log_action_player_arrange_w,
    log_action_player_arrange_wa,
    log_action_player_buff_add = 1600,
    log_action_player_buff_remove,
	log_action_player_load_json_fail,
    log_action_player_quest_accept = 1800,
    log_action_player_quest_accomplish,
    log_action_player_quest_track_change,
    log_action_player_quest_drop,
    log_action_player_gp,
    log_action_player_gp_drop,
    log_action_player_gp_detail,
    log_action_player_kill,
    log_action_player_learn_skill, // 玩家获取技能
    log_action_player_join_team,   // 玩家组队
    log_action_player_family_create,
    log_action_player_family_join,
    log_action_player_family_leave,
    log_action_player_family_expell,
    log_action_player_family_promote,
    log_action_player_family_destroy,
    log_action_player_active,
    log_action_player_gp_one,
    log_action_gmbox,
    log_action_monster_die = 2000,
    log_action_monster_die_drop_item,
    log_action_monster_die_drop_gold,
    log_action_monster_relive,
    log_action_script_add_item = 3000,
    log_action_script_remove_item,
    log_action_map_drop_item = 4000,
    log_action_map_drop_gold,
    log_action_map_item_expire,
    log_action_castle_init_war = 5000,
    log_action_castle_starting_war,
    log_action_castle_ending_war,
    log_action_castle_stop_war,
    log_action_castle_temp_family,
    log_action_glory_finish = 5500,
    log_action_test = 10000,
    log_action_user_define_start = 30000,
    log_action_script_timeout,
    log_action_max,
};

enum castle_state {
    castle_state_nullptr = 0, /// 城堡战未定义
    castle_state_init,        /// 城堡初始化完成
    castle_state_starting,    /// 触发城堡战开启脚本回调
    castle_state_running,     /// 城堡脚本触发成功
    castle_state_ending,      /// 触发城堡战结束脚本回调
    castle_state_max,
};

enum gp_data_type {
    gp_data_type_move = 0,
    gp_data_type_spell,
    gp_data_type_max,
};

enum sort_type {
    // 等级榜
    sort_type_level = 0,
    sort_type_level_warrior,
    sort_type_level_mage,
    sort_type_level_tao,

    // 魅力榜
    sort_type_beauty,
    sort_type_beauty_male,
    sort_type_beauty_female,

    // 师徒榜
    sort_type_students,
    sort_type_students_warrior,
    sort_type_students_mage,
    sort_type_students_tao,

    //兵器榜
    sort_type_weapon_warrior,
    sort_type_weapon_mage,
    sort_type_weapon_tao,

    sort_type_max,
};

enum eMail_Type {
    eMail_Type_System  = 0,
    eMail_Type_Trade   = 1,
    eMail_Type_GM      = 2,
    eMail_Type_Auction = 3,
    eMail_Type_Num,
};

enum glory_trigger_type {
    // 代码里的操作
    glory_trigger_wield_equip = 1,
    glory_trigger_kill_monster,
    glory_trigger_level_up,
    glory_trigger_dig,
    glory_trigger_learn_skill,
    glory_trigger_use_item,
    glory_trigger_finish_glory,
    glory_trigger_join_team,
    glory_trigger_market_delegate,
    glory_trigger_enter_map,
    glory_trigger_trade_stall_sell,
    glory_trigger_join_family,
    glory_trigger_join_war,
    glory_trigger_join_castle,
    glory_trigger_vip,

    // 脚本里的操作
    glory_trigger_script_start = 1000,
    glory_trigger_offline_exp,
    glory_trigger_taofa,
    glory_trigger_jinglian,
    glory_trigger_jianding,
    glory_trigger_fengying,
    glory_trigger_catch_horse,
    glory_trigger_horse_kaiguang,
    glory_trigger_biao,
};

enum db_var_action {
    db_var_action_ignore,  //忽略  保留目标数据库数据
    db_var_action_replace, //替换  保留源数据库数据
    db_var_action_max,     //取大  取大的数据，只对整型
    db_var_action_min,     //取小  取小的数据，只对整形
    db_var_action_sum,     //相加  结果相加，只对整形
    db_var_action_concat,  //相连  结果相连，只对字符串
    db_var_action_remove,  //删除  清除
};

enum CLIENT_HERO_STATE {
    CLIENT_DUMMY_STATE_IDLE = 0,
    CLIENT_DUMMY_STATE_CONTROL = 1,
    CLIENT_DUMMY_STATE_FOLLOW = 2,
    CLIENT_DUMMY_STATE_FIGHT = 3,
    CLIENT_DUMMY_STATE_PROTECT = 4,
};

enum MonsterDefine {
	ID = 0, // ID
	NAME, // 名字
	TYPE, // 类型
	HEAD, // 头像
	LEVEL, // 等级
	MULTIHPSINGLEVALUE, // 多重血条单条血量
    NAMECOLOR, //怪物的名字颜色
    HP,        //怪物配置生命值
};

enum move_type {
    move_type_walk = 0,
    move_type_run = 1,
    move_type_jump = 2,
    move_type_sucked = 3
};

enum eFamilyInfoReqType
{
    eFamilyInfoReq_Notice = (1 << 0),
    eFamilyInfoReq_Message = (1 << 1),
    eFamilyInfoReq_Title = (1 << 2),
    eFamilyInfoReq_Member = (1 << 3),
    eFamilyInfoReq_Enemy = (1 << 4),
    eFamilyInfoReq_Ally = (1 << 5),
    eFamilyInfoReq_Apply = (1 << 6),
    eFamilyInfoReq_BasicInfo = (1 << 7),
    eFamilyInfoReq_FamilyList = (1 << 8),
    eFamilyInfoReq_MemberOL = (1 << 9),
    eFamilyInfoReq_Unused = (1 << 10),
    eFamilyInfoReq_Allmember = (1 << 11)
};

//方向
enum
{
    dir_up,
    dir_right_up,
    dir_right,
    dir_right_down,
    dir_down,
    dir_left_down,
    dir_left,
    dir_left_up,
    dir_max,
};

enum guild_relation {
    guild_relation_no_relation,
    guild_relation_ally,
    guild_relation_enemy
};

enum guild_member_title {
    guild_member_title_member,
    guild_member_title_chairman,
    guild_member_title_vice_chairman,
    guild_member_title_elite,
    guild_member_title_not_member = 0xFF
};

enum guild_apply_status {
    guild_apply_status_not_applied,     // 未申请
    guild_apply_status_applied,         // 已申请
    guild_apply_status_passed,          // 已通过
    guild_apply_status_failed           // 未通过
};

enum guild_member_status {
    guild_member_status_normal,         // 正常
    guild_member_status_removed,        // 被踢
};

enum cust_var_type {
    cust_var_type_normal,
    cust_var_type_daily,
    cust_var_type_temp,
};

enum cust_var_merge_type {
    cvmt_keep_main          = 0,        // 保留主区数据
    cvmt_addup              = 1,        // 数据相加（字符型数据相连，数值型数据相加）
    cvmt_choose_bigger      = 2,        // 取最大的数据（仅对数值型数据生效）
    cvmt_choose_smaller     = 3,        // 取最小的数据（仅对数值型数据生效）
    cvmt_delete             = 4         // 数据清除
};

enum script_type {
    script_type_player      = 0,        // 玩家相关脚本
    script_type_hero        = 1,        // 英雄相关脚本
    script_type_monster     = 2,        // 怪物相关脚本
    script_type_npc         = 3,        // NPC相关脚本
    script_type_item        = 4,        // 物品相关脚本
    script_type_map         = 5,        // 地图相关脚本
    script_type_team        = 6,        // 组队相关脚本
    script_type_guild       = 7,        // 行会相关脚本
    script_type_event       = 8,        // 事件相关脚本
    script_type_scene_magic = 9,        // 场景魔法相关脚本
    script_type_system      = 10,       // 系统相关脚本
    script_type_mail        = 12,       // 邮件相关脚本
    script_type_consignment = 13,       // 寄售行相关脚本
    script_type_achievement = 14,       // 成就相关脚本
    script_type_form        = 15,       // 表单相关脚本
    script_type_console     = 16,       // 控制台相关脚本
    script_type_activity    = 17,       // 活动相关脚本
    script_type_quest       = 18,       // 任务相关脚本
    script_type_vip         = 19,       // VIP相关脚本
    script_type_skill       = 20,       // 技能相关脚本
    script_type_buff        = 21,       // BUFF相关脚本
    script_type_all         = 99,
};

//enum summon_monster_type {
//    summon_monster_type_unknown             = 0,
//    summon_monster_type_normal              = 1,         // 普通
//    summon_monster_type_special             = 2,         // 特殊
//};

enum msg_type {
    msg_type_own,    // 自己
    msg_type_all,    // 所有人
    msg_type_guild,  // 行会
    msg_type_team,   // 队伍
    msg_type_present,// 当前
};
// 装备可操作类型
enum item_enable_type
{
    item_enable_drop = 1,       // 是否可丢弃
    item_enable_warehousing,    // 是否可存入仓库
    item_enable_repair,         // 是否可修理
    item_enable_sell,           // 是否可出售
    item_enable_auction,        // 是否可拍卖
    item_enable_purchase,       // 是否可收购
    item_enable_quickbar,       // 是否可放入快捷栏
    item_enable_identify,       // 是否可鉴定
    item_enable_drill,          // 是否可打孔
    item_enable_unload,         // 是否可卸下
    item_enable_refine,         // 是否可精炼
    item_enable_enhance,        // 是否可强化
    item_enable_deal,           // 是否可交易
    item_enable_savelog,        // 是否保存记录
    item_enable_autodel,        // 是否使用次数为0自动消失
    item_enable_expiredel,      // 是否到期删除
};

// 怪物可操作类型
enum monster_enable_type
{
    monster_enable_canAtk = 1,          /// 是否可被攻击
    monster_enable_saveLog,             /// 是否写入log数据库
    monster_enable_canTalk,             /// 是否可对话
    monster_enable_invDetect,           /// 是否可侦测隐形
    monster_enable_canTurn,             /// 是否可转向
};
// buff可操作类型
enum buff_enable_type
{
    buff_enable_clientShow = 1,         // 是否客户端显示
    buff_enable_offlineSave,            // 是否下线保存
    buff_enable_dieAutoDel,             // 是否死亡时删除
    buff_enable_immShield,              // 是否有减免盾
    buff_enable_stealth,                // 是否有隐身
    buff_enable_disappearStealth,       // 是否隐身时移动后消失
    buff_enable_timeStack,              // 是否时间叠加
    buff_enable_effectStack,            // 是否效果叠加
    buff_enable_jumpMapSave,            // 是否跳转地图保存
    buff_enable_live,                   // 是否死亡时可添加
    buff_enable_delOnAttack,            // 是否受攻击时删除
    buff_enable_saveLog,                // 是否写记录
};

enum db_op_type {
    db_op_type_add      = 1,
    db_op_type_del      = 2,
    db_op_type_update   = 3
};

enum family_member_ntf_opt {
    family_member_ntf_add_member    = 1,
    family_member_ntf_del_member    = 2,
    family_member_ntf_change_title  = 3
};//邮件相关
enum mail_status{
    //位置改变相与
    mail_status_read          = 0x0001,
    mail_status_unread        = 0x0001,
    mail_status_gold          = 0x0002,
    mail_status_yuanbao       = 0x0004,
    mail_status_item1         = 0x0008,
    mail_status_item2         = 0x0010,
    mail_status_item3         = 0x0020,
    mail_status_item4         = 0x0040,
    mail_status_item5         = 0x0080,
    mail_status_integral      = 0x0100,
    mail_status_bind_gold     = 0x0200,
    mail_status_bind_yuanbao  = 0x0400,
    mail_status_non_delete    = 0x07FE,
    mail_status_delete        = 0x0800,

};

enum mail_status_bite {
    mail_status_bite_read      = 0,
    mail_status_bite_unread    = 0,
    mail_status_bite_gold      = 1,
    mail_status_bite_yuanbao   = 2,
    mail_status_bite_item1     = 3,
    mail_status_bite_item2     = 4,
    mail_status_bite_item3     = 5,
    mail_status_bite_item4     = 6,
    mail_status_bite_item5     = 7,
    mail_status_bite_integral  = 8,
    mail_status_bite_bind_gold = 9,
    mail_status_bite_bind_yuanbao = 10,
    mail_status_bite_del       = 11,
    mail_status_bite_end,
};


enum relation_chat_ntf_type {
    relation_chat_ntf_type_current  = 1,        // 当前
    relation_chat_ntf_type_team     = 2,        // 队伍
    relation_chat_ntf_type_guild    = 3,        // 公会
    relation_chat_ntf_type_world    = 4,        // 世界
    relation_chat_ntf_type_trumpt   = 5,        // 喇叭
    relation_chat_ntf_type_camp     = 9,        // 阵营
    relation_chat_ntf_type_whole    = 12,       // 全服
};

enum skill_harm_type
{
    skill_harm_type_none  = 0,
    skill_harm_type_ordinary = 1,   // 普通
    skill_harm_type_crit,           // 暴击
    skill_harm_type_miss,           // 闪避
    skill_harm_type_immunity,       // 免疫
    skill_harm_type_holyblow,       // 神圣一击
    skill_harm_type_extra0,         // 附加伤害0
    skill_harm_type_extra1,         // 附加伤害1
    skill_harm_type_extra2,         // 附加伤害2
    skill_harm_type_extra3,         // 附加伤害3
    skill_harm_type_extra4,         // 附加伤害4
    skill_harm_type_extra5,         // 附加伤害5
    skill_harm_type_extra6,         // 附加伤害6
    skill_harm_type_extra7,         // 附加伤害7
    skill_harm_type_extra8,         // 附加伤害8
    skill_harm_type_extra9,         // 附加伤害9
};

enum trap_type {
    trap_type_none      = 0,        // 非陷阱
    trap_type_fire_wall = 1,        // 火墙类技能
    trap_type_other     = 2,        // 非火墙类技能
};

enum target_relation {                          // 技能可作用目标
    target_relation_other_player    = 1,        // 其他玩家
    target_relation_self            = 2,        // 自己
    target_relation_pet             = 4,        // 对随从怪物
    target_relation_monster         = 8,        // 非随从怪物
};

enum attr_show_ntf_type {
    attr_show_ntf_type_ordinary     = 0,        // 普通
    attr_show_ntf_type_crit         = 1,        // 暴击
    attr_show_ntf_type_holyblow     = 2,        // 神圣一击
};

enum miss_ntf_type {
    miss_ntf_type_miss              = 1,        // 闪避
    miss_ntf_type_immunity          = 2,        // 免疫
};
//主动追击类型为奇数 非主动追击类型为偶数
enum pursue_attack_type {
    all_type_stay_put         = 0,            // 该AI类型的怪物仅生成定在原地不动
    type1_active_pursuit      = 1,            // AI类型1的主动追击
    type1_non_active_pursuit  = 2,            // AI类型1的不主动追击
    type2_dadaowei            = 3,            // 大刀卫型
    type3_shouchengweibing    = 5,            // 守城卫兵
    type4_biaoche_active      = 7,            // 镖车类型主动移动怪物
    type4_biaoche_non_active  = 8,            // 镖车类型被动移动怪物
    type5_biaoche_non_master  = 9,            // 镖车类型怪物 只移动至终点 与押镖人无关
    type6_normal_pet          = 10,           // 普通宠物
    type7_taoist_pet          = 11,           // 道士、法师宠物

};

enum delegate_type 
{
    delegate_type_sell = 0,    // 出售
    delegate_type_buy,         // 收购
};

enum item_state_type
{
    item_state_owner = 0,       // 玩家身上(背包\仓库)
    item_state_selling,         // 上架(出售)中
    item_state_unaccalimed,     // 未领取(邮件)
};
enum delegate_cancel_reason
{
    delegate_cancel_manual = 0, // 玩家手动取消
    delegate_cancel_expired,    // 到期
    delegate_cancel_delete_role,
};
enum precision_type
{
    precision_type_1 = 1,   // 百分比
    precision_type_2,       // 万分比
};

enum log_type
{
    log_type_currency_change = 1,   // 货币、积分变化
    log_type_item_update,           // 物品增删改(更新)
    log_type_login_out,             // 登录登出
    log_type_entery_exit_map,       // 进出地图
    log_type_drop_item,             // 物品掉落
    log_type_gm_cmd,                // gm指令
    log_type_online_num,            // 在线人数
    log_type_trade_data,            // 寄售记录
    log_type_mail_info,             // 邮件记录
    log_type_death_record,          // 死亡记录
    log_type_activity_data,         // 活动
    log_type_reward_data,           // 奖励
    log_type_giftpack_data,         // 礼包
    log_type_recovery_data,         // 回收
    log_type_db_exesql,             // db sql
    log_type_item_dyn_attr,         // 物品动态属性更新
    log_type_item_cust_var,         // 物品自定义属性更新
};

struct log_params
{
    std::string info = "";

    uint16_t site = 0;
    uint8_t beTrade = 0;// 寄售行删除时为1
};

struct log_item_params
{
    std::string itemKeyname = "";
    uint32_t itemNum = 0;
};
enum log_item_change_reason
{
    log_item_change_reason_pickup = 1,          /// 拾取获得
    log_item_change_reason_monster_reward,      /// 怪物奖励
    log_item_change_reason_quest_reward,        /// 任务奖励
    log_item_change_reason_stall_buy,           /// 摆摊购买
    log_item_change_reason_stall_sell,          /// 摆摊卖出
    log_item_change_reason_delegate_buy,        /// 寄售行委托买
    log_item_change_reason_delegate_sell,       /// 寄售行委托卖
    log_item_change_reason_market_buy,          /// 寄售行主动买
    log_item_change_reason_market_sell,         /// 寄售行主动卖
    log_item_change_reason_use,                 /// 使用更新
    log_item_change_reason_move,                /// 移动更新
    log_item_change_reason_login_init,          /// 登录初始化
    log_item_change_reason_drop,                /// 丢弃消失
    log_item_change_reason_expired,             /// 到期消失
    log_item_change_reason_mail_get,            /// 邮件领取
    log_item_change_reason_quest_consume,       /// 任务消耗
    log_item_change_reason_quest_acquire,       /// 任务发放
    log_item_change_reason_quest_collect,       /// 任务收集
    log_item_change_reason_bag_arrange,         /// 背包整理
    log_item_change_reason_shop_buy,            /// 商店购买
    log_item_change_reason_trade_mall_buy,      /// 商店购买
    log_item_change_reason_gold_deposit,        /// ProtoGS_GoldDeposit msg
    log_item_change_reason_gold_take,           /// ProttoGS_GoldTake msg
    log_item_change_reason_lua_add,             /// 脚本调用增加堆叠数量
    log_item_change_reason_max,
};

enum log_loginout_type
{
    log_loginout_login = 1,
    log_loginout_logout = 2,
};

enum log_drop_item_type
{
    log_drop_item_type_item = 1,
    log_drop_item_type_currency = 2,
};

enum rolepack_opt_type{
    bag_type = 1,       //背包
    warehouse_type = 2,   /// 仓库
    adv_warehouse_type = 3, /// 高级仓库
};

enum monster_attck_status
{
    monster_attack_non          = 0,  //未进入攻击状态
    monster_attack_ing          = 1,  //正在攻击中
    monster_attack_finish       = 2,  //攻击完成
    monster_attck_wait_finish   = 3,  //攻击等待
    monster_attack_ready_finish = 4,  //攻击准备完成
};

enum monster_behaviour_trigger
{
    monster_ai_discover_target,             //发现目标：指怪物处于待机、巡逻等非战斗状态下发现目标
    monster_ai_target_hp,                   //目标血量
    monster_ai_self_hp,                     //自身血量
    monster_ai_die_trigger,                 //死亡触发
    monster_ai_start_fight_time,            //战斗开始时间
    monster_ai_target_and_self_instance,       //目标与自身距离
    monster_ai_target_job,                     //目标职业
    monster_ai_self_harmed_by_special_skill,  //收到指定技能伤害
};

enum simple_Arithmetic_type
{
    simple_Arithmetic_add      = 1,
    simple_Arithmetic_subtract = 2,
    simple_Arithmetic_multiply = 3,
    simple_Arithmetic_divide   = 4,

};

enum lua_chat_msg_type
{
    // 聊天框类型同 relation_chat_ntf_type
    lua_chat_msg_dialog_current = 1,        // 当前
    lua_chat_msg_dialog_team = 2,        // 队伍
    lua_chat_msg_dialog_guild = 3,        // 公会
    lua_chat_msg_dialog_world = 4,        // 世界
    lua_chat_msg_dialog_trumpt = 5,        // 喇叭
    lua_chat_msg_dialog_camp = 9,        // 阵营
    lua_chat_msg_dialog_whole = 12,       // 全服
    // 系统消息
    lua_chat_msg_dialog_sys_all         = 20,
    lua_chat_msg_dialog_sys_map         = 21,
    lua_chat_msg_dialog_sys_region      = 22,
    lua_chat_msg_dialog_sys_single      = 23,
    // 场景信息
    lua_chat_msg_scene_appear_all       = 24,
    lua_chat_msg_scene_appear_map       = 25,
    lua_chat_msg_scene_appear_region    = 26,
    lua_chat_msg_scene_appear_single    = 27,
    // 跑马灯
    lua_chat_msg_scroll_text_all        = 28,
    lua_chat_msg_scroll_text_map        = 29,
    lua_chat_msg_scroll_text_region     = 30,
    lua_chat_msg_scroll_text_single     = 31,
};

enum castle_war_monster_type
{
    main_city_front_door_monster    = 1,        // 主城正门怪
    palace_front_door_monster       = 2,        // 皇宫正门怪
    palace_side_door_monster        = 3,        // 皇宫侧门怪
};

enum online_state
{
    online_state_not_logged_in      = 0,
    online_state_logged_in          = 1,
    online_state_disconnected       = 2,
    online_state_being_kicked       = 3,
};

enum mall_limit_type
{
    mall_limit_type_non    = 0,
    mall_limit_type_all    = 1,
    mall_limit_type_single = 2,
};

enum login_ip_type
{
    login_ip_type_white = 1,  // white
    login_ip_type_black = 2,  // black
};

enum server_status
{
    server_status_maintenance = 1,        // 维护
    server_status_reset_maintenance = 2,  // 关闭维护
    server_status_close = 3,              // 关服
};

enum pet_activity_status
{
    pet_activity_status_non = 0,
    pet_activity_status_follow = 1,
    pet_activity_status_active = 2,
    pet_activity_status_defend = 3,
    pet_activity_status_stay   = 4,
};

enum pet_type
{
    pet_type_normal = 1,   // 通用宠物
    pet_type_taoist = 2,   // 法师道士宠物
};


enum check_role_existence_method
{
    by_name = 0,
    by_guid = 1,
};

enum role_status
{
    role_status_new         = 0,        // 从未进过游戏
    role_status_normal      = 1,        // 正常
    role_status_deleted     = 2,        // 角色已删除
    role_status_permanent_deleted = 3,  // 角色永久删除
    role_status_new_deleted = 4,        // 角色没有进过游戏就已删除
};

enum class jump_map_type
{
    default_type_null = 0,
    sys_jump_map_point = 1,     // 系统跳转点
    dyn_jump_map_point = 2,     // 动态跳转点
    jump_map_item_1 = 3,    // 跳转道具1
    jump_map_skill_1 = 4,   // 跳转技能1

};

enum blank_grid_type
{
    blank_grid_normal,
    blank_grid_drop,
};

enum auto_pick_item_mode
{
    auto_pick_item_mode_undef       = 0,
    auto_pick_item_mode_around      = 1,
    auto_pick_item_mode_designated  = 2
};

enum mail_type
{
    mail_type_sys    = 0,
    mail_type_player = 1,
    mail_type_all    = 2,
};

enum start_dig_result
{
    start_dig_ok            = 0,
    start_dig_no_target     = 1,    // 目标不存在
    start_dig_out_of_range  = 2,    // 距离不再范围内
    start_dig_digging       = 3,    // 正在挖
    start_dig_other_reason  = 4     // 其他原因
};

enum stop_dig_reason
{
    stop_dig_timeup         = 0,    // 倒计时结束
    stop_dig_role_move      = 1,    // 角色移动
    stop_dig_role_die       = 2,    // 角色死亡
    stop_dig_taken_away     = 3     // 被其他人挖走
};

enum role_appear_type
{
    role_appear_normal      = 0,
    role_appear_born        = 1,    // 出生
    role_appear_jump        = 2,    // 跳跃
    role_appear_digging     = 3     // 挖宝
};

enum sync_client_base_setting_type
{
    scbs_null = 0,
    scbs_auto_stack = 11,
    scbse_stall_bind_trade = 34,
};

enum gm_cmd_msg_type
{
    gm_cmd_msg_type_sys     = 1,
    gm_cmd_msg_type_scroll  = 2,
    gm_cmd_msg_type_trumpt  = 3,
};

enum middle_platform_chat_type
{
    middle_platform_chat_type_non,
    middle_platform_chat_type_near     = 1,        // 附近\附近
    middle_platform_chat_type_team     = 2,        // 队伍
    middle_platform_chat_type_guild    = 3,        // 公会
    middle_platform_chat_type_tumpt    = 4,        // 喇叭
    middle_platform_chat_type_private  = 5,        // 私聊
    middle_platform_chat_type_world    = 6,        // 世界
    middle_platform_chat_type_map      = 7,        // 地图

};

enum count_suit_type
{
    count_suit_by_num                   = 0,
    count_suit_by_sub_type              = 1,
    count_suit_by_template_id           = 2,
};

enum redemption_code_type 
{
    redemption_code_type_npc    = 1,
    redemption_code_type_cdkey  = 2,
    redemption_code_type_game   = 3,
};

enum drop_type
{
    drop_type_item  = 1,
    drop_type_group = 2,
};

// 物品配置该类型 对应场景直接掉落
enum player_drop_type
{
    player_drop_type_normal      = 0,
    player_drop_type_logout      = 2,   // 退出登录时    
    player_drop_type_leave_map   = 4,   // 离开地图时
    player_drop_type_die         = 8,   // 死亡时
    player_drop_type_jump_map    = 16,  // 跳转地图时
    player_drop_type_max,
};

enum role_brief_info_flag
{
    flag_brief_guid,
	flag_brief_name,
	flag_brief_head,
	flag_brief_level,
	flag_brief_status,
	flag_brief_job,
	flag_brief_hair,
	flag_brief_hair_color,
	flag_brief_gender,
	flag_brief_weapon,
	flag_brief_clothes,
	flag_brief_gssvrid,
	flag_brief_vipLevel,
	flag_brief_is_lock,
    flag_brief_max,
};

enum role_extra_info_flag {

    flag_extra_login_time,
    flag_extra_hp,
    flag_extra_mp,
    flag_extra_exp,
    flag_extra_mapid,
    flag_extra_posx,
    flag_extra_posy,
    flag_extra_dir,
    flag_extra_gold,
    flag_extra_bindGold,
    flag_extra_ingot,
    flag_extra_bindIngot,
    flag_extra_integral,
    flag_extra_depositGold,
    flag_extra_innerForceExp,
    flag_extra_atkMode,
    flag_extra_birthMap,
    flag_extra_rebirthMap,
    flag_extra_redNameMap,
    flag_extra_rolePk,
    flag_extra_modelID,
    flag_extra_max,
};

enum table_ident {
    table_role                  = 1,
    table_role_settings         = 2,
    table_role_location         = 3,
};

enum role_eid {
    role_eid_id                 = 1,
    role_eid_pid                = 2,
    role_eid_name               = 3,
    role_eid_head               = 4,
    role_eid_level              = 5,
    role_eid_vip_level          = 6,
    role_eid_status             = 7,
    role_eid_job                = 8,
    role_eid_hair               = 9,
    role_eid_hair_color         = 10,
    role_eid_gender             = 11,
    role_eid_weapon             = 12,
    role_eid_clothes            = 13,
    role_eid_gold               = 14,
    role_eid_bind_gold          = 15,
    role_eid_ingot              = 16,
    role_eid_bind_ingot         = 17,
    role_eid_integral           = 18,
    role_eid_deposit_gold       = 19,
    role_eid_inner_force_exp    = 20,
    role_eid_hp                 = 21,
    role_eid_mp                 = 22,
    role_eid_exp                = 23,
    role_eid_atk_mode           = 24,
    role_eid_login_time         = 25,
    role_eid_role_pk            = 26,
    role_eid_is_lock            = 27,
    role_eid_model_id           = 28,
    role_eid_create_date        = 29,
    role_eid_online_duration    = 30,
    role_eid_update_time        = 31,
    role_eid_online_state       = 32,
};

enum role_settings_eid {
    role_settings_role          = 1,
    role_settings_auto_pickup   = 2,
};

enum role_location_eid {
    role_location_role          = 1,
    role_location_map           = 2,
    role_location_posx          = 3,
    role_location_posy          = 4,
    role_location_dir           = 5,
    role_location_birth_map     = 6,
    role_location_rebirth_map   = 7,
    role_location_redname_map   = 8,
};

enum effect_point_type {
    effect_point_type_trap = 0,
    effect_point_type_jump = 1
};

enum lua_get_prop_type {
    lua_get_prop = 1,
    lua_get_prop_64 = 2,
    lua_get_prop_dyn = 3,
};

enum CustType {
    CustType_1 = 1,
    CustType_2,
    CustType_3,
    CustType_4,
    CustType_5,
    CustType_6,
    CustType_7,
    CustType_8,
    CustType_9,
    CustType_10,
    CustType_11,
    CustType_12,
    CustType_13,
    CustType_14,
    CustType_15,
    CustType_16,
    CustType_17,
    CustType_18,
    CustType_19,
    CustType_20,
    CustType_Max = 21
};

enum DestroyDgnErr {
    Destroy_ok = 0,
    Destroy_have_player = 109,
};

//////////////////////////////////////////////////////////////////////////

typedef std::map<std::string, std::string> TLuaKeyword;
class CLuaKeyword {
    // DECLARE_SINGLETON(CLuaKeyword);
public:
    bool RegLuaKeyword(void);
    bool IsLuaKeyword(const std::string &key);
    std::string GetLuaKeyword(const std::string &key);

private:
    bool AddLuaKeyword(const std::string &key, int value);

private:
    TLuaKeyword m_oKeywords;
};

#endif