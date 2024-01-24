#ifndef __LOGIC_DEF__
#define __LOGIC_DEF__

#include <map>
#include <string>
//#include <vector>

/// �����Ա�
enum gender_type {
    gender_nullptr = 0,
    gender_male,   /// ��
    gender_female, /// Ů
    gender_max,
};

/// �������е�ְҵ����
enum job_type {
    job_nullptr = 0,
    job_warrior, /// սʿ
    job_mage,    /// ��ʦ
    job_tao,     /// ��ʿ
    job_max,
};
enum EExitType
{
	E_EXIT_EXITGS = 1,  //����,�˳���Ϸ
	E_EXIT_LOGOUTGS,    //С��,�˵�ѡ��ɫ����
	E_EXIT_JUMPGS,      //����
	E_EXIT_DBKICK,      //DBServer����
	E_EXIT_GSKICK,      //Game Server����
	E_EXIT_GTKICK,      //Gate����,ͬһ�ʺ������ͻ�������ͬһgateʱ
	E_EXIT_SAVE,        //��ʱ����
	E_EXIT_NETERROR,    //�������,����ͻ��˶���
	E_EXIT_RELOGIN,     //���µ�½
	E_EXIT_FORCE_KICK   //ǿ������
};

#define LO_BYTE(x) (uint8_t)(uint16_t(x) & 0x00FF)
#define HI_BYTE(x) (uint8_t)((uint16_t(x) >> 8) & 0x00FF)

#define LO_WORD(x) (uint16_t)(uint32_t(x) & 0x0000FFFF)
#define HI_WORD(x) (uint16_t)((uint32_t(x) >> 16) & 0x0000FFFF)

#define LO_unsigned long(x) (uint32_t)(UINT64(x) & 0x00000000FFFFFFFF)
#define HI_unsigned long(x) (uint32_t)((UINT64(x) >> 32) & 0x00000000FFFFFFFF)

#define MK_unsigned long(x, y) (uint32_t)(uint16_t(x) << 16 | uint16_t(y))

//////////////////////////////////////////////////////////////////////////
#define MAP_VIEW_X 12 //��ͼ��ҰX�뾶
#define MAP_VIEW_Y 15 //��ͼ��ҰY�뾶

#define MAX_REGION_OBJ 50000                 //��������������
#define MAX_REGION_PLAYER 10000              //��������������
#define MAX_INT64_2_DOUBLE 9007199254740992  // int64��double֮��ת�������ֵ
#define MIN_INT64_2_DOUBLE -9007199254740992 // int64��double֮��ת������Сֵ

#define INFINITE_ITEM_NUM   0xFFFF
#define PRECISION   0.00010000100   // ��ֱ�
#define PERCENTAGE  0.010000100     // �ٷֱ�
#define TRADE_DELEGATE_TIME	86400	// Ĭ��ί��ʱ��,��λ��(ȫ����������Сʱ)
#define INVALID_ITEM_SITE  (uint16_t)(site_nullptr)
#define CLOSE_SERVER_DELAY_TIME 10000
#define CLOSE_CUR_SERVER_DELAY_TIME 1000
#define KICK_PLAYER_DELAY_TIME 5000    //ms
#define ONE_MONTH_STAMP 2592000  // һ����(s)
#define ADD_MAIL_MAX_NUM 500

#define MAX_ROLE_NAME_LENGTH    32
#define SEND_SYNC_DATA_INTERVAL_TIME 5000
#define SEND_SYNC_USER_DATA_INTERVAL_TIME 60000
#define CIRCLE_SEND_SYS_CHAT_TIMES 3
#define SYNC_CLIENT_BASE_SETTING_PREFIX	"SCBS_"
#define CUST_VAR_STALL_NAME_KEY	"��̯��"
#define CUST_VAR_ALIAS_KEY	"����"
#define LOG_PARAMS_INFO_INIT "��¼��ʼ��"

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
    role_1000_min = 1000,               /// ��ǰ1000��ʼ�ֶ�
    role_hp = 1001,                     /// ��ǰhp
    role_mp = 1002,                     /// ��ǰmp
    role_base_max_hp = 1003,            /// ���hp 
    role_base_max_mp = 1004,            /// ���mp
    role_base_min_phy_def = 1005,       /// �����������
    role_base_max_phy_def = 1006,       /// �����������
    role_base_min_mag_def = 1007,       /// ħ����������
    role_base_max_mag_def = 1008,       /// ħ����������
    role_base_min_phy_atk = 1009,       /// ����������
    role_base_max_phy_atk = 1010,       /// ����������
    role_base_min_mag_atk = 1011,       /// ħ����������
    role_base_max_mag_atk = 1012,       /// ħ����������
    role_base_min_tao_atk = 1013,       /// ������������
    role_base_max_tao_atk = 1014,       /// ������������
    role_luck_curse       = 1015,       /// ����/����
    role_base_hp_rec = 1016,            /// hp�ظ�ֵ
    role_base_mp_rec = 1017,            /// mp�ظ�ֵ
    role_base_move_speed = 1018,        /// �����ƶ��ٶ�
    role_base_attack_speed = 1019,      /// ���������ٶ�
    role_base_casting_speed = 1020,     /// ����ʩ���ٶ�
    role_imm_phy = 1021,                /// �����˺�����ֵ
    role_imm_mag = 1022,                /// ħ���˺�����ֵ
    role_monster_harm = 1023,           /// �Թ��˺�ֵ
    role_player_harm = 1024,            /// �����˺�ֵ
    role_real_harm = 1025,              /// ��ʵ�˺�
    role_curse = 1026,                  /// ����
    role_1000_max,                      /// ��ǰ1000��β�ֶ�

    // 2000
    role_2000_min = 2000,                       /// ��ǰ2000��ʼ�ֶ�
    role_base_max_hp_pct = 2001,                /// �������ӱ�
    role_base_max_mp_pct = 2002,                /// ħ�����ӱ�
    role_base_min_phy_def_pct = 2003,           /// ����������ޱ�
    role_base_max_phy_def_pct = 2004,           /// ����������ޱ�
    role_base_min_mag_def_pct = 2005,           /// ħ���������ޱ�
    role_base_max_mag_def_pct = 2006,           /// ħ���������ޱ�
    role_base_min_phy_atk_pct = 2007,           /// ���������ޱ�
    role_base_max_phy_atk_pct = 2008,           /// ���������ޱ�
    role_base_min_mag_atk_pct = 2009,           /// ħ���������ޱ�
    role_base_max_mag_atk_pct = 2010,           /// ħ���������ޱ�
    role_base_min_tao_atk_pct = 2011,           /// �����������ޱ�
    role_base_max_tao_atk_pct = 2012,           /// �����������ޱ�
    role_base_hp_rec_pct = 2013,                /// hp�ظ�ֵ��
    role_base_mp_rec_pct = 2014,                /// mp�ظ�ֵ��
    role_base_attack_speed_pct = 2015,          /// ���������ٶȱ�
    role_base_casting_speed_pct = 2016,         /// ����ʩ���ٶȱ�
    role_base_move_speed_pct = 2017,            /// �����ƶ��ٶȱ�
    role_hit = 2018,                        /// ��������
    role_miss = 2019,                       /// ��������
    role_mag_miss = 2020,                   /// ħ������
    role_burst = 2021,                      /// ������
    role_burst_harm = 2022,                 /// �����˺�
    role_burst_def = 2023,                  /// �����ֿ�
    role_burst_harm_def = 2024,             /// �����˺��ֿ�
    role_attack_harm_pct = 2025,            /// �����˺��ӳ�
    role_imm_phy_pct = 2026,                /// �����˺������
    role_imm_mag_pct = 2027,                /// ħ���˺������
    role_ignore_def_pct = 2028,             /// ����Ŀ�������
    role_ignore_imm_pct = 2029,             /// ����Ŀ������
    role_ref_harm_pct = 2030,               /// �����˱�
    role_suck_hp_pct = 2031,                /// ��hp��
    role_attack_suck_hp_pct = 2032,         ///	������hp��
    role_monster_drop_pct = 2033,           /// �����һ�ɱ����ʱ����Ʒ����
    role_drug_rec = 2034,                   /// ҩƷ�ָ�
    role_palsy_miss = 2035,                 /// �������
    role_exp_consume_pct = 2036,                   /// �������ı��� ��ֱ�
    role_exp_monster = 2037,                /// ��־��鱶��       
    role_2000_max,                          /// ��ǰ2000��β�ֶ�
    // 3000 ��������
    // 4000 ʱ������
    // 5000 ״̬����

////////////////////////////////////
    // 6000 �������
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
    // 7000 ������
    role_7000_min = 7000,
    role_level = 7001,              /// �ȼ�
    role_job = 7002,                /// ְҵ
    role_weight = 7003,             /// ��������
    role_equip_weight = 7004,       /// װ������
    role_brawn = 7005,              /// ��ǰ����
    role_max_weight = 7006,         /// �����
    role_max_equip_weight = 7007,   /// ���װ������
    role_max_brawn = 7008,          /// �������
    role_7000_max,

    role_7400_min = 7400,
    role_bag_size_0 = 7401,         /// ����0��С
    role_bag_size_1,                /// ����1��С
    role_bag_size_2,                /// ����2��С
    role_bag_size_3,                /// ����3��С
    role_bag_size_4,                /// ����4��С
    role_warehouse_size,            /// ��ҵĲֿ��С
    role_warehouse_adv_size,        /// ��Ҹ߼��ֿ��С
    role_atk_mode,                  /// ��������
    role_pk,                        /// PKֵ
    role_holy,                      /// ��ʥ
    role_imm_shield,                /// ���߻���ֵ
    role_gender,                    /// �Ա�
    role_head,                      /// ͷ��
    role_hair,                      /// ͷ��
    role_hair_color,                /// ͷ����ɫ
    role_gm_level,                  /// gm�ȼ�
    role_stall,                     /// ��̯״̬0: δ��̯ 1: ��̯׼�� 2: ��̯��
    role_vip_level,                 /// ��ɫvip�ȼ�
    role_secondary_password_status, /// ��������״̬
    role_camp,                      /// ��Ӫ
    role_avatar,                    /// ����
    role_max_imm_shield,            /// ������߻���ֵ,role_imm_shield
    role_horse_modelid,             /// ����ʱ���
    role_7400_max,

    role_7700_min = 7700,
    role_can_walk = 7701,           /// ����·
    role_can_run,                   /// ���ܲ�
    role_can_turn,                  /// ��ת��
    role_can_jump_map,              /// ������ͼ
    role_can_phy_atk,               /// ��������
    role_can_mag_atk,               /// ��ħ������
    role_can_use_item,              /// ��ʹ�õ���
    role_is_phy_imm,                /// ��������
    role_is_mag_imm,                /// ħ������
    role_is_stealth,                /// ����
    role_has_imm_shield,            /// ���߻���
    role_has_collide,               /// ���ڳ�ײ״̬
    role_has_repelled,              /// ���ڻ���״̬
    role_can_push,                  /// �ܱ���
    role_can_use_skill,             /// ��ʹ�ü���
    role_is_poisoning,              /// �Ƿ��ж�
    role_can_through,               /// �Ƿ���Դ���
    role_can_zhenshi,               /// �Ƿ�����״̬
    role_has_team,                  /// �ж���
    role_friend_switch,             /// �Ƿ�ɼӺ���0:���ɼ�,1: �ɼ�
    role_team_switch,               /// �Ƿ���ܶ�������0:������,1: ����
    role_has_family,                /// ���л�
    role_ride_switch,               /// ������
    role_is_ghost,                  /// �Ƿ�����ģʽ
    role_is_gray,                   /// �Ƿ����
    role_is_show_fashion,           /// �Ƿ���ʾʱװ
    role_changed_modelid,           /// �ı������
    role_can_through_monster,       /// �Ƿ���Դ���
    role_7700_max,

    /// ��̬���Զ�
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

    // �Զ�������
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
    // 10001 ��������(����������)
    role_10000_min = 10000,
    role_max_hp = 10001,             /// ���hp 
    role_max_mp = 10002,             /// ���mp
    role_min_phy_def = 10003,        /// �����������
    role_max_phy_def = 10004,        /// �����������
    role_min_mag_def = 10005,        /// ħ����������
    role_max_mag_def = 10006,        /// ħ����������
    role_min_phy_atk = 10007,        /// ����������
    role_max_phy_atk = 10008,        /// ����������
    role_min_mag_atk = 10009,        /// ħ����������
    role_max_mag_atk = 10010,        /// ħ����������
    role_min_tao_atk = 10011,        /// ������������
    role_max_tao_atk = 10012,        /// ������������
    role_hp_rec = 10013,             /// hp�ظ�ֵ
    role_mp_rec = 10014,             /// mp�ظ�ֵ
    role_move_speed = 10015,         /// �����ƶ��ٶ�
    role_attack_speed = 10016,       /// ���������ٶ�
    role_casting_speed = 10017,      /// ����ʩ���ٶ�
    role_10000_max,
/////////////////////////////////////////////////////
    role_attr_min = role_1000_min,
    role_attr_max = role_10000_max,
};
/// ��ɫ���
enum role_appearence_item {
    role_app_body = 0, /// ����
    role_app_weapon,   /// ����
    role_app_wings,    /// ���
    role_app_mount,    /// ����
    role_app_amulet,   /// �ػ�
    role_app_max,
};

//////////////////////////////////////////////////////////////////////////

/// ��Ʒ����
enum item_type {
    item_type_nullptr = 0,
    item_type_equip,         /// װ��
    item_type_consumable,    /// ����Ʒ
    item_type_finite,        /// ����Ʒ
    item_type_material,      /// ����
    item_type_sundries,      /// �ӻ�
    item_type_bag,           /// ����
    item_type_warehouse_adv, /// �߼��ֿ�
    item_type_gold,          /// ���
    item_type_bundle,        /// ������Ʒ
    item_type_skill,         /// ������Ч����Ʒ
    item_type_script,        /// �ű���Ʒ

    item_type_max,
};

/// ��Ʒ����������
enum item_category {
    item_cat_unknown,
    item_cat_player,        /// �����Ʒ
    item_cat_scene          /// ������Ʒ
};

/// װ������
enum equip_type {
    equip_nullptr = 0,
    equip_weapon,   /// ����
    equip_helmet,   /// ͷ��
    equip_wrist,    /// ����
    equip_armor,    /// �·�
    equip_juju,     /// ����
    equip_shoes,    /// Ь��
    equip_shoulder, /// ����
    equip_necklace, /// ����
    equip_ring,     /// ��ָ
    equip_medal,    /// ѫ��

    equip_gem,    /// ��ʯ
    equip_wings,  /// ���
    equip_amulet, /// �ػ�
    equip_mount,  /// ����

    equip_shield,  /// ����
    equip_fashion, /// ʱװ
    equip_hat,     /// ����
    equip_gloves,  /// ����
    equip_jewelry, /// �鱦

	equip_glasses,              /// �۾�
	equip_bracelet,             /// ����
	equip_mask,                 /// ���
	equip_kneelet,              /// ��ϥ
	equip_chestplate,           /// ����
	equip_cloak,                /// ����
	equip_earrings,             /// ����
	equip_headwear,             /// ͷ��
	equip_legguard,             /// ����
	equip_jade,                 /// ����
	equip_instrument,           /// ����
	equip_hangings,             /// ����
	equip_fashion_weapon,       /// ʱװ����,
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

/// ��������
enum material_type {
    material_nullptr = 0,
    material_weapon_upgrade,   /// ������������
    material_reserved,         /// (����δʹ��)
    material_identify,         /// ����װ������
    material_drill,            /// װ����ײ���
    material_lucky,            /// ��������ף������
    material_gem,              /// ��ʯ
    material_synthesis,        /// ��ʯ�ϳɷ�
    material_dig,              /// ��ʯժ����
    material_embed,            /// ��ʯ��Ƕ��
    material_refine,           /// װ����������
    material_refine_lucky,     /// װ���������˷�����
    material_speaker,          /// ����
    material_refine_transform, /// װ������ת�Ʋ���
    material_refine_imm,       /// װ��������
    material_identify_imm,     /// װ��������
    material_horse,            /// δ������
    material_identify_horse,   /// ����ӡ
    material_max,
};

/// ��������
enum weapon_type {
    weapon_nullptr = 0, /// ͨ����
    weapon_knife,       /// ���ࣨսʿ�ࣩ
    weapon_sword,       /// ���ࣨ��ʿ�ࣩ
    weapon_stick,       /// ���ࣨ��ʦ�ࣩ
    weapon_max,
};

/// ��������
enum juju_type {
    juju_nullptr = 0,
    juju_juju,   /// ������
    juju_poison, /// ��ҩ��
    juju_max,
};

/// ������
enum bind_type {
    bind_nullptr = 0, /// �ް�
    bind_on_pick_up,  /// ʰȡ��   bangding
    bind_on_use,      /// ʹ�ð�   weibangding
    bind_max,
};

/// ��������
#define MAX_BAG_COUNT 5
/// һ��������������
#define MAX_SLOT_PER_BAG 40
/// �������ĸ�����
#define MAX_BAG_SLOT (MAX_BAG_COUNT * MAX_SLOT_PER_BAG)
/// �ֿ���������
#define MAX_WAREHOUSE_SIZE 160
/// �߼��ֿ���������
#define MAX_WAREHOUSE_ADV_SIZE 160

enum item_site {
    site_nullptr = 0,
    site_weapon,   /// ����
    site_helmet,   /// ͷ��
    site_wrist_0,  /// ����0
    site_wrist_1,  /// ����1
    site_armor,    /// �·�
    site_juju,     /// ����
    site_shoes,    /// Ь��
    site_shoulder, /// ����
    site_necklace, /// ����
    site_ring_0,   /// ��ָ0
    site_ring_1,   /// ��ָ1
    site_medal,    /// ѫ��

    site_gem,    /// ��ʯ
    site_wings,  /// ���
    site_amulet, /// �ػ�
    site_mount,  /// ����

    site_shield,    /// ����
    site_fashion,   /// ʱװ
    site_hat,       /// ����
    site_gloves,    /// ����
    site_jewelry,   /// �鱦
    site_equip_end, /// װ��λ����,��һ�ε���ʼ

    site_bag_0 = site_equip_end,                /// ��0����
    site_bag_1 = site_bag_0 + MAX_SLOT_PER_BAG, /// ��1����
    site_bag_2 = site_bag_1 + MAX_SLOT_PER_BAG, /// ��2����
    site_bag_3 = site_bag_2 + MAX_SLOT_PER_BAG, /// ��3����
    site_bag_4 = site_bag_3 + MAX_SLOT_PER_BAG, /// ��4����

    // �ֿ�ͱ���һ����ҳ,Ŀǰֻ��һ��role_warehouse_size��role_warehouse_adv_size
    // ���Բֿ���Ӱ�˳����,���������Ҫÿҳ����,���role_warehouse_size_ҳ,�޸Ĵ���
    site_warehouse = site_bag_4 + MAX_SLOT_PER_BAG,                 /// �ֿ�222
    site_warehouse_0 = site_warehouse,                              /// 222
    site_warehouse_1 = site_warehouse_0 + MAX_SLOT_PER_BAG,         /// 264
    site_warehouse_2 = site_warehouse_1 + MAX_SLOT_PER_BAG,         /// 304
    site_warehouse_3 = site_warehouse_2 + MAX_SLOT_PER_BAG,         /// 342
    site_warehouse_adv = site_warehouse_3 + MAX_SLOT_PER_BAG,       /// �߼��ֿ�382
    site_warehouse_adv_0 = site_warehouse_adv,                      /// 382
    site_warehouse_adv_1 = site_warehouse_adv_0 + MAX_SLOT_PER_BAG, /// 422
    site_warehouse_adv_2 = site_warehouse_adv_1 + MAX_SLOT_PER_BAG, /// 462
    site_warehouse_adv_3 = site_warehouse_adv_2 + MAX_SLOT_PER_BAG, /// 502
    site_bag_end = site_warehouse_adv_3 + MAX_SLOT_PER_BAG,         /// 542

    site_expand_0 = site_bag_end, /// ����0����λ��                 /// 542
    site_expand_1,                /// ����1����λ��
    site_expand_2,                /// ����2����λ��
    site_expand_3,                /// ����3����λ��
    site_expand_4,                /// ����4����λ��
    site_expand_end = 550,        /// �����������

	site_glasses,                           /// �۾�          /// 551
	site_bracelet_0,                        /// ����0
	site_bracelet_1,                        /// ����1
	site_mask,                              /// ���
	site_kneelet,                           /// ��ϥ
	site_chestplate,                        /// ����
	site_cloak,                             /// ����
	site_earrings,                          /// ����
	site_headwear,                          /// ͷ��
	site_legguard,                          /// ����
	site_jade,                              /// ����
	site_instrument,                        /// ����
	site_hangings,                          /// ����
	site_fashion_weapon,                    /// ʱװ����
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
	// �Զ���װ��λ
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

    // ��Ʒ�����λ
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
    site_end = site_item_quick_bar_end,   /// ������
};

/// ��Ʒ��Ʒ��
enum item_quality {
    quality_general = 0, /// ��ͨ, ��ɫ
};

/// ��Ʒ����
enum item_attr {
    item_att_pos = 0,        /// ��Ʒ��ǰ���ڵ�λ��
    item_att_amount,         /// ��Ʒ��ǰ�Ķѵ�����
    item_att_durability,     /// ��Ʒ��ǰ�;�
    item_att_max_durability, /// ��Ʒ����;�
    item_att_use_count,      /// ��Ʒ��ǰ��ʹ�ô���
    item_att_is_bound,       /// ��Ʒ�Ƿ񱻰�
    item_att_life,           /// ��Ʒ���ʱ��
    item_att_skill_id,       /// ����id

    item_att_name,           /// ��Ʒname
    item_att_color,          /// ��Ʒcolor
    item_att_icon,           /// ��Ʒicon
    item_att_quality,        /// ��Ʒquality
    item_att_subtype,        /// ��Ʒsubtype
    item_att_max,
};

enum skill_type {
    skill_type_passive,     /// �����༼��
    skill_type_switch,      /// �������չ�
    skill_type_status,      /// ״̬���չ�
    skill_type_action,      /// ����������
    skill_type_cast,        /// ʩ���༼��
    skill_type_fixed,       /// �̶�������
    skill_type_direct,      /// ֱ���ͷţ����������ж�
};

enum skill_hurt_type {
    skill_hurt_type_phy = 1,
    skill_hurt_type_mag = 2,
    skill_hurt_type_tao = 3
};

enum skill_cast_way {
    skill_cast_direct   = 1,    /// ֱ���ͷ�
    skill_cast_target   = 2,    /// ��Ŀ��
    skill_cast_grid     = 3,    /// ���߼���
};

enum skill_special_effect_type {
    skill_special_trap_trigger  = 1,        /// �����ഥ��
    skill_special_trap_rt       = 2,        /// ������ʵʱ
    skill_special_summon        = 3,        /// �ٻ���
    skill_special_fly           = 4,        /// ������
    skill_special_repell        = 5,        /// ������
    skill_special_doplganr      = 6,        /// ����
};

enum skill_range_type {
    skill_range_type_point      = 0,
    skill_range_type_line       = 1,
    skill_range_type_rect       = 2,
    skill_range_type_cust       = 3
};

enum skill_target_type {
    skill_target_all            = 0,        /// ����
    skill_target_self           = 1,        /// ���Լ�
    skill_target_monster        = 2,        /// �Թ���
    skill_target_player         = 3,        /// �����
    skill_target_friend         = 4,        /// ���ѷ�
};

enum skill_level_compare {
    skill_level_compare_no      = 0,        /// �޵ȼ���ϵ
    skill_level_compare_greater = 1,        /// ����Ŀ��ȼ�
    skill_level_compare_ge      = 2,        /// ���ڻ����Ŀ��ȼ�
};

enum skill_attached_buff {
    skill_buff_target           = 1,        /// ��Ŀ���BUFF
    skill_buff_self             = 2,        /// ���Լ���BUFF
    skill_buff_all              = 3,        /// �����л�ȡ����Ŀ���buff
};

enum teleport_type {
    teleport_nullptr = 0,
    teleport_rand_limit,  /// ����ͼ�������
    teleport_rand,        /// ����ͼ���
    teleport_relive,      /// �����
    teleport_relive_rand, /// ��������ڵ�ͼ���
    teleport_relive_max,
};

enum repel_type {
    repel_type_nullptr = 0, /// ��
    repel_type_collide,     /// ��ײ
    repel_type_repelled,    /// ����
};

enum repel_cmp_type {
    repel_cmp_nullptr = 0,   /// ��
    repel_cmp_less_equal,    /// С�ڵ���
    repel_cmp_greater_equal, /// ���ڵ���
};

enum repel_collide_type {
    repel_collide_nullptr = 0, /// ��
    repel_collide_with_target, /// ��Ŀ���ײ
    repel_collide_no_target,   /// ��Ŀ���ײ
};

enum role_attr_ext {
    role_exp = 0,      /// ����
    role_ingot,        /// Ԫ��
    role_bind_ingot,   /// ��Ԫ��
    role_integral,     /// ����
    role_gold,         /// ���
    role_bind_gold,    /// �󶨽��
    role_gold_deposit, /// �ֿ���
    role_inner_force_exp,   /// �ڹ�����
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
    relive_skill = 0, //���ܸ���
    relive_local,     //ԭ�ظ���
    relive_map,       //�سǸ���
    relive_dungeon,   //��������
};
enum item_enhance_type {
    enhance_type_phy = 0,
    enhance_type_mag,
    enhance_type_tao,
    enhance_type_max,
};

enum stall_state_type {
    stall_state_nullptr = 0, /// δ��̯
    stall_state_ready,       /// ��̯׼��
    stall_state_ok,          /// ��̯��
    stall_state_max,
};

enum stall_price_type {
    stall_price_gold = 0, /// ���
    stall_price_ingot,    /// Ԫ��
	stall_price_integral,   /// ����
    stall_price_bind_gold,/// �󶨽��
    stall_price_bind_ingot,/// ��Ԫ��
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
    servant_source_catch,  /// ��׽
    servant_source_summon, /// �ٻ�
    servant_source_max,
};

enum pk_state_type {
    pk_state_nullptr = 0,
    pk_state_white,  /// ����
    pk_state_yellow, /// ����
    pk_state_gray,   /// ����
    pk_state_red,    /// ����
    pk_state_max,
};

enum region_type {
    region_safe = 0,  ///��ȫ��
    region_stall,     ///��̯��
    region_athletics, ///������
    region_relive,    ///������
    region_red_name,  ///������
    region_born,      ///��������
    region_jump,      ///��ת����
    region_mine,      ///����
    region_through,   ///�ɴ�͸��
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
    map_common = 0, //��ͨ��ͼ
    map_dungeon,    //������ͼ
};

enum role_last_time_type {
    role_last_login = 0, //��ɫ����½ʱ��FLAG
    role_online,         //��ɫ����ʱ��FLAG
    role_max_online,     //��ɫ������ʱ��FLAG
    role_last_attack,    //��ɫ��󹥻�ʱ��FLAG
    role_last_move,      //��ɫ����ƶ�ʱ��FLAG
    role_last_chat,      //��ɫ�������ʱ��FLAG
    role_today_online,   //��ɫ��������ʱ��
    role_last_logout,    //��ɫ�������ʱ��FLAG
};

enum role_attr_name_type {
    role_account_name = 0, //��ɫ�ʺ�����FLAG
    role_ip,               //��ɫ��IP��ַ
    role_user_name,        //��ɫ�û�����FLAG
    role_home_map,         //��ɫ�سǵ�ͼ��FLAG
    role_home_map_key,     //��ɫ�سǵ�ͼ��keyname
    role_alias,            //��ɫ��ν��FLAG
    role_guild,            //��ɫ��������FLAG
    role_current_map,      //��ɫ��ǰ��ͼ����FLAG
    role_current_map_key,  //��ɫ��ǰ��ͼ��keyname
};

enum role_attr_id_type {
    role_guild_id = 0,   //��ɫ����ID��FLAG
    role_current_map_id, //���������ͼID��FLAG
    role_home_map_id,    //��һسǵ�ͼID(GUID)��FLAG
};

enum role_attr_modify_type {
    role_attr_add = 10000, //��ɫ��������
    role_attr_sub,         //��ɫ���Լ���
    role_attr_equal,       //��ɫ��������
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

/// ��Ʒ������
enum bind_require {
    bind_require_false = 0, /// ����ǰ�
    bind_require_true,      /// �����
    bind_require_any,       /// �󶨷ǰ󶨶�����
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
    * @brief            ����������
    * @return           ��
    */
    trigger_system_start                        = 1,        /// system call, don't need to manually add
    /**
    * @brief            ��һ�ε�½
    * @param1           ��ɫguid
    * @return           ��
    */
    trigger_first_in_game                       = 2,
    /**
    * @brief            ��½
    * @param1           ��ɫguid
    * @return           ��
    */
    trigger_login                               = 3,
    /**
    * @brief            �ǳ�
    * @param1           ��ɫguid
    * @return           ��
    */
    trigger_logout                              = 4,
    /**
    * @brief            ֪ͨ�ͻ��˹�ɳ��ʼ
    * @return           ��
    */
    trigger_castle_war_start                    = 5,
    /**
    * @brief            ֪ͨ�ͻ��˹�ɳ����
    * @return           ��
    */
    trigger_castle_war_end                      = 6,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_castle_war_init                     = 7,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_gp                                  = 8,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_gp_one                              = 9,
     /**
    * @brief            ��ͼ����
    * @param1           ��ͼguid
    * @param2           ��ͼ����
    * @return           ��
    */
    trigger_map_create                          = 200,      /// system call, don't need to manually add
     /**
    * @brief            ��ͼ�ر�
    * @param1           ��ͼguid
    * @param2           ��ͼ����
    * @return           ��
    */
    trigger_map_destroy                         = 201,      /// system call, don't need to manually add
    /**
    * @brief            �����ͼ
    * @param1           ��ɫguid
    * @return           ��
    */
    trigger_enter_map                           = 202,
    /**
    * @brief            �뿪��ͼ
    * @param1           ��ɫguid
    * @return           ��
    */
    trigger_leave_map                           = 203,
    /**
    * @brief            ��Ʒ�����ڵ�ͼ
    * @param1           ��ͼguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           ��Ʒ����
    * @param5           x
    * @param6           y
    * @return           ��
    */
    trigger_item_appear                         = 204,
    /**
    * @brief            ��Ʒ��ʧ�ڵ�ͼ
    * @param1           ��ͼguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           ��Ʒ����
    * @param5           x
    * @param6           y
    * @return           ��
    */
    trigger_item_disappear                      = 205,
    /**
    * @brief            ��������ڵ�ͼ
    * @param1           ����guid
    * @param2           ����ģ��id
    * @param3           ��������
    * @param4           x
    * @param5           y
    * @return           ��
    */
    trigger_monster_appear                      = 206,
    /**
    * @brief            ������ʧ�ڵ�ͼ
    * @param1           ����guid
    * @param2           ����ģ��id
    * @param3           ��������
    * @param4           x
    * @param5           y
    * @return           ��
    */
    trigger_monster_disappear                   = 207,
    /**
    * @brief            npc�����ڵ�ͼ
    * @param1           npcguid
    * @param2           npcģ��id
    * @param3           npc����
    * @param4           x
    * @param5           y
    * @return           ��
    */
    trigger_npc_appear                          = 208,
    /**
    * @brief            npc��ʧ�ڵ�ͼ
    * @param1           npcguid
    * @param2           npcģ��id
    * @param3           npc����
    * @param4           x
    * @param5           y
    * @return           ��
    */
    trigger_npc_disappear                       = 209,
    /**
    * @brief            ��������ڵ�ͼ
    * @param1           ����guid
    * @param2           ����ģ��id
    * @param3           ��������
    * @param4           x
    * @param5           y
    * @return           ��
    */
    trigger_pet_appear                          = 210,
    /**
    * @brief            ������ʧ�ڵ�ͼ
    * @param1           ����guid
    * @param2           ����ģ��id
    * @param3           ��������
    * @param4           x
    * @param5           y
    * @return           ��
    */
    trigger_pet_disappear                       = 211,
    /**
    * @brief            ��������ڵ�ͼ
    * @return           ��
    */
    trigger_doplganr_appear                    = 212,
    /**
    * @brief            ��ɫ����
    * @param1           ��ɫguid
    * @param2           �ȼ�
    * @return           ��
    */
    trigger_level_up                            = 300,
    /**
    * @brief            ��ɫ��װ��ǰ
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           װ��λ��
    * @return           ��
    */
    trigger_pre_equip                           = 301,
    /**
    * @brief            ��ɫ��װ��
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           װ��λ��
    * @return           bool �Ƿ���Դ���
    */
    trigger_post_equip                          = 302,
     /**
    * @brief            ��ɫ����װ��ǰ
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           װ��λ��
    * @return           bool �Ƿ��������
    */
    trigger_pre_un_equip                        = 303,
    /**
    * @brief            ��ɫ����װ��
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           װ��λ��
    * @return           ��
    */
    trigger_post_un_equip                       = 304,
    /**
    * @brief            �ƶ�����
    * @param1           ��ɫguid
    * @param2           λ������x
    * @param3           λ������y
    * @param4           �ƶ�����  �� = 0, �� = 1, �� = 2
    * @return           ��
    */
    trigger_move                                = 305,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_spell                           = 306,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_spell                               = 307,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_mining                          = 308,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_mining                              = 309,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_item_apply                      = 310,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_apply                          = 311,
    /**
    * @brief            ��Ʒʰȡ
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           ��Ʒλ������x
    * @param5           ��Ʒλ������y
    * @return           bool  �Ƿ���ʰȡ
    */
    trigger_pre_item_pickup                     = 312,
    /**
    * @brief            ��Ʒʰȡ
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           ��Ʒ��ֵ
    * @return           ��
    */
    trigger_item_pickup                         = 313,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_item_drop                       = 314,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_drop                           = 315,      /// �Ӷ����Ĵ���
    /**
    * @brief            ��������
    * @param1           ������ɫguid
    * @param2           ������ɫguid
    * @return           bool �Ƿ�����
    */
    trigger_pre_die                             = 316,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_post_die                            = 317,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_kill                                = 318,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_attack                              = 319,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_hp                                  = 320,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_mp                                  = 321,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_damage_process                      = 322,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_restore_process                     = 323,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_teleport                            = 324,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_catch                           = 325,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_catch                               = 326,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_dig_meat                        = 327,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_dig_meat                            = 328,
    /**
    * @brief            ���buffǰ���
    * @param1           buffID
    * @param2           ���guid
    * @param3           �ͷ���guid
    * @return           �Ƿ����buff
    */
    trigger_check_add_buff                      = 329,
    /**
    * @brief            ���buff
    * @param1           ���guid
    * @param2           buffid
    * @param3           ����guid
    * @return           ��
    */
    trigger_add_buff                            = 330,
    /**
    * @brief            �Ƴ�buff
    * @param            ���guid
    * @param            buffid
    * @return           ��
    */
    trigger_remove_buff                         = 331,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_drop                            = 332,      /// Ҫ��Ҫ������
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_post_drop                           = 333,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_drop_one                        = 334,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_post_drop_one                       = 335,      /// ����ĳ������Ķ���
    /**
    * @brief            ��Ӽ���
    * @param1           ���guid
    * @param2           ����id
    * @return           ��
    */
    trigger_add_skill                           = 336,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_switch_skill                        = 337,
    /**
    * @brief            �ٻ�
    * @param1           ���guid
    * @param2           ����guid
    * @return
    */
    trigger_summon                              = 338,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_process_pk                      = 339,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_post_process_pk                     = 340,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_create                              = 341,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_destroy                             = 342,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_npc_visit                           = 343,
    /**
    * @brief            ����ͼǰ
    * @param1           string ���guid
    * @param2           string ��ǰ��ͼguid
    * @param3           string ��ת����ͼ��guid
    * @return           �Ƿ���ת
    */
    trigger_pre_enter_jump                      = 344,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_equip_suit                          = 345,      /// ��װ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_un_equip_suit                       = 346,      /// ��װ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_amount_zero                    = 347,      /// amountΪ0ɾ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_use_zero                       = 348,      /// ʹ�ô���Ϊ0ɾ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_dur_zero                       = 349,      /// �;�Ϊ0ɾ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_timeup                         = 350,      /// ʱЧ����ɾ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_add_exp                             = 351,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_monster_born                        = 352,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_player_relive                       = 353,
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_dungeon_end                         = 354,      /// ��������ʱ�ص�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_timer_check                         = 355,      /// ��ʱ���
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_add_exp_all                         = 356,      /// ���л�ȡ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_player_pre_die                      = 357,      /// ��������ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_player_post_die                     = 358,      /// ���������󴥷�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_monster_pre_die                     = 359,      /// ��������ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_monster_post_die                    = 360,      /// ���������󴥷�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_attack_ex                           = 361,      /// on_attack��ǿ�棬���˿�Ѫֵ�뼼�ܲ���
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_system_stop                         = 362,      /// system call, don't need to manually add
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_logout                          = 363,      ///
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_ride_request                        = 364,      /// �յ��������󴥷�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_unride_request                      = 365,      /// �յ��������󴥷�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_billin                              = 366,      /// ��ֵ������ֻ��������߲Żᴥ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_mall                                = 367,      /// �̳����Ѵ���
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_mall                            = 368,      /// �̳�����ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_escorter_fail                       = 369,      /// ���͹�ʧ��,ϵͳ������
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_escorter_far                        = 370,      /// ���͹ֹ�Զ,ϵͳ������
    /**
    * @brief            buff�����ص�
    * @params1          ��ɫguid
    * @params2          buffID
    * @return           ��
    */
    trigger_apply_buff                          = 371,      /// buff�����ص�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_monster_in_fight                    = 372,      /// �������ս��״̬����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_monster_out_fight                   = 373,      /// �����˳�ս��״̬����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_player_pre_curse                    = 374,      /// ����������ǰ����
    /**
    * @brief            ɫ�ܵ��˺�ʱ����
    * @params1          ʩ����guid
    * @params2          �ܻ���guid
    * @params3          ����id
    * @return           �����ᶨ�˺���ֵ table{["Harm"]=�˺���ֵ, ["type"]=�˺�����}
    */
    trigger_role_pre_harm                       = 375,      /// ��ɫ�ܵ��˺�ʱ����,�����ᶨ�˺���ֵ
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_npc_buy                         = 376,      /// npc����ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_npc_buy                             = 377,      /// npc���򴥷�
    /**
    * @brief            ��̯ǰ����
    * @params1          ��̯��guid
    * @return           �Ƿ���԰�̯
    */
    trigger_pre_stall                           = 378,      /// ��̯ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_hack_check                          = 379,      /// ��Ҽ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_auto_add_gold                       = 380,      /// ɱ���Զ��ӽ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_hack_check2                         = 381,      /// ��Ҽ��
    /**
    * @brief            ��̯ǰ����
    * @params1          �л�guid
    * @params2          �л���
    * @params3          ��ɫguid
    * @params4          �л��������
    * @params5          ��ɫ����
    * @params6          ������guid
    * @return           ��
    */
    trigger_family_member_ntf                   = 382,      /// �л��¼�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_stall_buy                       = 383,      /// �����̯��Ʒǰ����
    /**
    * @brief            �лᴴ�����ٴ���
    * @params1          �л�guid
    * @params2          �л���
    * @params3          ������guid
    * @return           ��
    */
    trigger_family_ntf                          = 384,      /// �лᴴ�����ٴ���
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_dur_zero_ex                    = 385,      /// �;�Ϊ0ɾ����չ
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_dummy_pre_die                       = 386,      /// ��������ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_dummy_post_die                      = 387,      /// ���������󴥷�
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_item_attr_zero                      = 388,      /// ��Ʒ���Ա�Ϊ0����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
	trigger_attacker_pre_harm                   = 389,      /// �������ܵ��˺�ʱ����,���ع̶��˺���ֵ
    /**
    * @brief            ��ɫ����ǰ����
    * @params1          ��ɫguid
    * @params2          �ȼ�
    * @params3          �ı侭��ֵ
    * @return           table {["BeUpgrade"] = (bool)�Ƿ����������["AddExp"] = (uint64_t)���ӵľ���}
    */
	trigger_pre_level_up                        = 390,      /// ��ɫ����ǰ����
	trigger_pre_add_gray                        = 391,      /// ��ɫ�����ǰ����
    /**
    * @brief            ��������л�ǰ����
    * @params1          ��ɫguid
    * @params2          �л�guid
    * @return           ��
    */
	trigger_pre_join_family                     = 392,      /// ��������л�ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_invite_family                   = 393,      /// ��������л�ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
    trigger_pre_relate_family                   = 394,      /// ���˻�ж��л�ǰ����
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
	trigger_billin_ex                           = 395,      /// ��ֵ��������ڲ����߶��ᴥ��
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
	trigger_player_change_name                  = 396,      /// ��Ҹ����������
    /**
    * @brief            ��ʵ��
    * @return           ��
    */
	trigger_sub_ingot                           = 397,      /// ��ҿ�Ԫ������
    /**
    * @brief            ���ٽ�ɫ����
    * @params1          ��ɫguid
    * @return           ��
    */
    trigger_role_destroyed                      = 398,      /// ���ٽ�ɫ����
    /**
    * @brief            �л������¼�
    * @params1          ��ɫguid
    * @params2          �л�guid
    * @params3          �л���
    * @params4          ������guid
    * @params5          �Ƿ���ͨ��
    * @return           ��
    */
    trigger_family_apply_ntf                    = 399,      /// �л������¼�
    /**
    * @brief            ����ǰ�����¼�
    * @params1          ����guid
    * @params2          ����guid
    * @return           {{��Ʒid(int32_t)����Ʒ����(int32_t)}��...}
    */
    trigger_pre_drop_rate                       = 400,      /// ����ǰ�����¼�
    /**
    * @brief            �˺��󴥷��¼�
    * @params1          ʩ����guid
    * @params2          �ܻ���guid
    * @return           ��
    */
    trigger_role_post_harm                      = 401,      /// �˺��󴥷��¼�
    /**
    * @brief            �������ϼ���Ʒ
    * @return           ��
    */
    trigger_auction_add                         = 402,      /// �������ϼ���Ʒ
    /**
    * @brief            �������¼���Ʒ
    * @return           ��
    */
    trigger_auction_end                         = 403,      /// �������¼���Ʒ
    /**
    * @brief            ��������Ʒ״̬�ı�
    * @return           ��
    */
    trigger_auction_start                       = 404,      /// ��������Ʒ״̬�ı�
    /**
    * @brief            ��������Ʒ�۸����ı�
    * @return           ��
    */
    trigger_auction_price_update                = 405,      /// ��������Ʒ�۸����ı�
    /**
    * @brief            ��������Ʒ�۸����ı�
    * @params1          �ɵ�Ӯ��
    * @params2          �µ�Ӯ��
    * @return           ��
    */
    trigger_castle_owner_changed                = 406,      /// ɳ�Ϳ˹�������¼�
    /**
    * @brief            ����ص���ص�
    * @param1           ר����ɫguid
    * @param2           ��ǰ��ɫguid
    * @param3           ������Ʒ��
    * @return           ��
    */
    trigger_post_item_drop                      = 407,      /// ��Ʒ�����
    /**
    * @brief            buff��Ϣ���º�ص�
    * @param1           ��ɫguid
    * @param2           buffid
    * @param3           ����guid
    * @return           ��
    */
    trigger_update_buff                         = 408,      /// buff����
    /**
    * @brief            ��������ʬ���Ƿ���ʧǰ�ص�
    * @param1           ����guid
    * @return           ʬ���Ƿ���ʧ
    */
    trigger_monster_disappear_pre_die           = 409,      /// ����������ʧǰ����
    /**
    * @brief            �������ͽ���ص�
    * @param1           �����Ƿ�ɹ�
    * @param2           ����������guid
    * @param3           ������������
    * @param4           ��������guid
    * @param5           ����������
    * @param6           �ͽ�
    * @param7           ����������Ϣ
    * @param8           ���Ϳ�ʼʱ��
    * @return           ��
    */
    trigger_post_bounty_result                  = 410,      /// �������ͽ��
    /**
    * @brief            �ڳ����ﵽ���ص�
    * @param1           �ڳ�����guid
    * @param2           �ڳ�����ģ��id
    * @param3           �ڳ����ﵱǰx����
    * @param4           �ڳ����ﵱǰy����
    * @return           ��
    */
    trigger_monster_biaoche_arrived             = 412,      /// �ڳ����ﵽ��
    /**
    * @brief            ����ǰ��Ȩ�ػص�,��Ҫ��ǰ��ֵԤ������Ϣ��LuaRet
    * @param1           ר����ɫguid
    * @param2           ��ǰ����guid
    * @return           ������Ʒ��Ϣ��
    */
    trigger_pre_drop_weight                     = 413,      /// ����ǰ��Ȩ��
    /**
    * @brief            ��ͼ��ת��ص�
    * @param1           ��ɫguid
    * @param2           ��תǰ�ĵ�ͼguid
    * @param3           ��ת��ĵ�ͼguid
    * @param4           ��ת��ĵ�ͼx����
    * @param5           ��ת��ĵ�ͼy����
    * @param6           ��ת����
    * @return           ��
    */
    trigger_post_enter_jump                     = 500,      /// ��ת��
    /**
    * @brief            ʹ�ü��ܺ�ص�
    * @param1           ��ɫguid
    * @param2           ����id
    * @param3           �����ͷŵ�x����
    * @param4           �����ͷŵ�y����
    * @param5           �����ͷ�Ŀ���ɫguid
    * @return           ��
    */
    trigger_after_apply_skill                   = 501,      /// ʹ�ü��ܺ󴥷�
    /**
    * @brief            ������Ʒ�Ƿ�����ǰ�ص�
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒ�Ƿ��Ѱ�
    * @return           �Ƿ�������Ʒ
    */
    trigger_drop_item_whether_destroy           = 502,      /// ������Ʒ�Ƿ�����
    /**
    * @brief            ��ʼ�ڱ��ص�
    * @param1           ��ɫguid
    * @param2           ����guid
    * @param3           ��������ʱ
    * @return           �ص�{(bool)�Ƿ�����ڱ�,(uint32_t)�ڱ�ʱ��}
    */
    trigger_start_dig                           = 503,      /// ��ʼ�ڱ�
    /**
    * @brief            �ڱ���ʱ�ص�
    * @param1           ��ɫguid
    * @param2           ����guid
    * @return           ��
    */
    trigger_dig_timesup                         = 504,      /// �ڱ���ʱ
    /**
    * @brief            ������Ʒ�ص�
    * @param1           ��ɫguid
    * @param2           ��Ʒid
    * @param3           ��Ʒ����
    * @return           �Ƿ��ѷ���
    */
    trigger_issue_goods                         = 505,      /// ������Ʒ
    /**
    * @brief            �Ƿ���Թ�����Ʒ�ص�
    * @param1           ��ɫguid
    * @param2           ��Ʒid
    * @param3           ��������
    * @param4           ����۸�
    * @return           �Ƿ���Թ���
    */
    trigger_can_buy_goods                       = 506,      /// �Ƿ���Թ�����Ʒ
    /**
    * @brief            ���������ȱ仯ʱ�ص�
    * @param1           ��ɫguid
    * @param2           ����id
    * @param3           �仯��
    * @return           ��
    */
    trigger_proficiency_changed                 = 507,      /// ���������ȱ仯
    /**
    * @brief            �������ϼ�ǰ�ص�
    * @param1           ����guid
    * @param2           ��Ʒģ��id
    * @param3           ��Ʒguid
    * @param4           ��������
    * @param5           ��Ʒ����
    * @return           �ϼ�ǰ�жϽ��{"Ret"=(bool)�Ƿ������ϼ�,"Type"=(uint8_t)��������,"TDTime"=(uint_t)�ϼ�ʱ��}
    */
    trigger_pre_trade_delegate_sell             = 508,      /// �������ϼ�ǰ
    /**
    * @brief            �������ϼܺ�ص�
    * @param1           ����guid
    * @param2           ��Ʒģ��id
    * @param3           ��Ʒguid
    * @return           ��
    */
    trigger_post_trade_delegate_sell            = 509,      /// �������ϼܺ�
    /**
    * @brief            ��������ǰ�ص�
    * @param1           ����guid
    * @param2           ��Ʒģ��id
    * @param3           ��������
    * @param4           ��Ʒ����
    * @param5           ��Ʒ����
    * @return           ��ǰ�жϽ��{"Ret"=(bool)�Ƿ�������,"Type"=(uint8_t)��������,"TDTime"=(uint_t)��ʱ��}
    */
    trigger_pre_trade_delegate_buy              = 510,      /// ��������ǰ
    /**
    * @brief            �������󹺺�ص�
    * @param1           ����guid
    * @param2           ��Ʒģ��id
    * @param3           ��������
    * @param4           ��Ʒ����
    * @param5           ��Ʒ����
    * @return           ��
    */
    trigger_post_trade_delegate_buy             = 511,      /// �������󹺺�
    /**
    * @brief            �����г���ǰ�ص�
    * @param1           ������guid
    * @param2           ��Ʒģ��id
    * @param3           ��Ʒguid
    * @return           �Ƿ��������{"Ret"=(bool)���}
    */
    trigger_pre_trade_market_sell               = 512,      /// �����г���ǰ
    /**
    * @brief            �����г���ǰ�ص�
    * @param1           ������guid
    * @param2           ����guid
    * @param3           ��Ʒģ��id
    * @param4           ��Ʒguid
    * @param5           ��Ʒ����
    * @return           ��
    */
    trigger_post_trade_market_sell              = 513,      /// �����г��ۺ�
    /**
    * @brief            �����й���ǰ�ص�
    * @param1           ������guid
    * @param2           ��Ʒģ��id
    * @param3           ��������
    * @param4           ��Ʒ����
    * @param5           ��������
    * @return           �Ƿ�������{"Ret"=(bool)���}
    */
    trigger_pre_trade_market_buy                = 514,      /// �����й���ǰ
    /**
    * @brief            �����й����ص�
    * @param1           ������guid
    * @param2           �ϼ���guid
    * @param3           ��Ʒģ��id
    * @param4           ��Ʒguid
    * @param5           ��������
    * @param6           ��Ʒ����
    * @param7           ��������
    * @return           ��
    */
    trigger_post_trade_market_buy               = 515,      /// �����й����
    /**
    * @brief            ��ȡ��Ʒ��ص�
    * @param1           ��ɫguid
    * @param2           ��Ʒguid
    * @param3           ��Ʒģ��id
    * @param4           siteλ
    * @return           ��
    */
    trigger_add_item                            = 516,      /// ��ȡ��Ʒ
    /**
    * @brief            ���������ص�
    * @param1           ��ɫguid
    * @param2           ����id
    * @param3           ������ȼ�
    * @return           ��
    */
    trigger_skill_level_up                      = 517,      /// ���������¼�
    /**
    * @brief            ��ɫ���Ա仯�ص�
    * @param1           ��ɫguid
    * @param2           ����id
    * @param3           32λ���Ի���64λ����
    * @param4           �仯ǰֵ
    * @param5           �仯��ֵ
    * @return           ��
    */
    trigger_role_update_attr                    = 518,      /// ��ɫ���Ը���
    /**
    * @brief            ��ҵ�����Ʒǰ�ص�
    * @param1           ��ɫguid
    * @param2           ��ɱ��guid
    * @return           lua����,Ԥ������Ϣ{{(int32_t)siteλ1,(int32_t)Ȩ��1},...}
    */
    trigger_player_pre_drop                     = 519,      /// ��ҵ���ǰ�¼�
    /**
    * @brief            ��ҵ���ص�,��Ҫ��ǰ��ֵԤ������Ϣ��LuaRet
    * @param1           ��ɫguid
    * @param2           ��ɱ��guid
    * @return           lua����,���յ�����Ϣ{{(int32_t)siteλ1,(int32_t)siteλ2},...}
    */
    trigger_player_drop                         = 520,      /// ��ҵ����¼�
    /**
    * @brief            ��ҵ����ص�,��δʹ��
    */
    trigger_player_post_drop                    = 521,      /// ��ҵ�����¼�
    /**
    * @brief            ��Ҷһ�����ȡ��ص�
    * @param1           ��ɫguid
    * @param2           ������
    * @param3           ������Ϣ
    * @return           ��
    */
    trigger_player_redeem_code                  = 522,      /// ��Ҷһ�����ȡ���¼�
    /**
    * @brief            ���������ȸ���ǰ�ص�
    * @param1           ��ɫguid
    * @param2           ����id
    * @param3           �����С������
    * @param4           ������������
    * @return           ��õ�������
    */
    trigger_proficiency_pre_changed             = 523,      /// �޸ļ���������֮ǰ
    /**
    * @brief            ��Ҷһ�����ȡ��ص�
    * @param1           ��ɫguid
    * @param2           ������
    * @param3           ������Ϣ
    * @param4           �����
    * @param5           �������
    * @return           ��
    */
    trigger_player_redeem_code2                 = 524,      /// ������2��ȡ���¼�
    /**
    * @brief            ��Ҹ�����ص�
    * @param1           ��ɫguid
    * @param2           ������
    * @param3           ԭ��
    * @return           ��
    */
    trigger_player_set_name                     = 525,      /// ��Ҹ������¼�
    /**
    * @brief            �����������˻ص�
    * @param1           ����guid
    * @param2           ��������guid
    * @return           ��
    */
    trigger_pet_jump_to_master                  = 526,      /// �������������¼�
    /**
    * @brief            �����������˻ص�
    * @param1           ����guid
    * @param2           ��������guid
    * @return           ��
    */
    trigger_player_doplganr_jump_to_master      = 527,      /// �������������¼�
    /**
    * @brief            �Զ�������޸�ǰ�ص�
    * @param1           ��ɫguid
    * @param2           ������
    * @param3           ����ֵ
    * @param4           ��������
    * @return           �Ƿ������޸�
    */
    trigger_pre_set_customer_var                = 528,      /// �Զ�������޸�ǰ�¼�(���gm)
    /**
    * @brief            �Զ�������޸ĺ�ص�
    * @param1           ��ɫguid
    * @param2           ������
    * @param3           ����ֵ
    * @param4           ��������
    * @return           ��
    */
    trigger_post_set_customer_var               = 529,      /// �Զ�������޸ĺ��¼�
    /**
    * @brief            ��������ʱ�䵽��ص�
    * @param1           ����guid
    * @return           ��
    */
    trigger_monster_arrived_exist_time          = 530,      /// ��������ʱ�䵽����¼�
    /**
    * @brief            ����ǰ�ص�
    * @param1           ��ɫguid
    * @param2           ����id
    * @param3           ������
    * @return           ���յ�����
    */
    trigger_pre_decrease_mp                     = 531,      /// ����ǰ����
    /**
    * @brief            ����̳е����Իص�
    * @param1           ��������guid
    * @return           ������Ϣ
    */
    trigger_pre_Get_Doplganr_Att                = 532,      //����̳е�����
    /**
    * @brief            �����ж��ͷ�ʹ�ü��ܻص�
    * @param1           ����guid
    * @param2           ��������guid
    * @param3           ��������
    * @param4           �������
    * @param5           ������Ϣ
    * @return           ���ͷŵļ���id
    */
    trigger_pre_Doplganr_choose_skill           = 533,      //�����ж��ͷ�ʹ�ü���
    /**
    * @brief            �������Ʒλ���ƶ��Ƿ����ص�
    * @param1           ��Ʒid
    * @param2           ��Ʒsiteλ
    * @return           �Ƿ������ƶ�
    */
    trigger_item_CheckSite                      = 534,      //�������Ʒλ���ƶ��Ƿ����
    /**
    * @brief            ��ȡɾ������ǰ�ص�
    * @param1           ��ɫguid
    * @param2           �������
    * @return           �Ƿ��Ѿ�����
    */
    trigger_rebate_money                        = 535,      /// ��ȡɾ������
    /**
    * @brief            GM����תlua����
    * @param1           ����id
    * @param2           string �ɽ����ַ���
    * @return           �Ƿ�ɹ�
    */
    trigger_gm_cmd                              = 536,      //GM������ű�����
	/**
    * @brief            ���¼�������ǰ
    * @return           ��
    */
    trigger_pre_recalculate = 537,      //
	/**
    * @brief            ���¼���������
    * @return           ��
    */
    trigger_recalculate = 538,      //
    

        /**
    * @brief            ���������Ƿ�ɾ���ٻ���
    * @param1           ����guid
    * @param2           �ٻ���guid
    * @return           �Ƿ�ɾ��
    */
    trigger_remove_summon_monster_when_logout = 539,      //

    /**
    * @brief            ���������Ƿ�ɾ���ٻ���
    * @param1           ����guid
    * @param2           �ٻ���guid
    * @return           �Ƿ�ɾ��
    */
    trigger_remove_summon_monster_when_different_map = 540,      //
    /**
    * @brief            �����뿪����
    * @param1           ����id
    * @return           ��
    */
    trigger_team = 541,      //

    /**
    * @brief            ������ͼ�д������ʱ�����Ƿ�رո���
    * @param1           ����ID
    * @return           �Ƿ�رո���
    */
    trigger_whether_destroy_dgn_when_have_players = 542,

    /**
    * @brief            �л�ս��ʼ
    * @param1           �л�1guid
    * @param2           �л�2guid
    * @return           ��
    */
    trigger_guild_war_start = 543,

    /**
    * @brief            �л�ս����
    * @param1           �л�1guid
    * @param2           �л�2guid
    * @return           ��
    */
    trigger_guild_war_end = 544,
    /**
    * @brief            ������������ص�,��Ҫ��ǰ��ֵԤ������Ϣ��LuaRet
    * @param1           ��ɫguid
    * @param2           ��ɱ��guid
    * @return           ��
    *                   LuaRet��ȡ���յ�����Ʒ�б�{{(int32_t)��Ʒid,(int32_t)����},...}
    */
    trigger_player_drop_item_list = 545,      /// �������������Ʒ�б�

    trigger_max,
};

/// quest type
enum quest_type {
    quest_type_nullptr = 0, /// nullptr
    quest_type_main,        /// ����
    quest_type_side,        /// ֧��
    quest_type_ring,        /// �ܻ�
    quest_type_cycle,       /// ѭ��
    quest_type_max,
};

enum quest_abort_type {
    quest_cannot_abort = 1,         /// ���ɷ���
    quest_can_abort,                /// ���Է���
    quest_abort_cannot_accept,      /// ���Է������޷��ٽ�ȡ
};

enum quest_accept_type {
    quest_accept_from_npc = 1,      /// ��NPC������
    quest_auto_accept,              /// �ȼ������Զ���ȡ
};

enum quest_deliver_type {
    quest_deliver_to_npc = 1,       /// ��NPC������
    quest_auto_deliver,             /// �������������Զ�����
};

enum quest_achieve_type {
    quest_achev_talk_to_npc = 1,    /// ��NPC�Ի�
    quest_achev_kill_monster,       /// ��ɱ����
    quest_achev_collect_item,       /// �ռ�����
    quest_achev_level_judge,        /// ��ɫ�ȼ��ж�
    quest_achev_collect_equipment,  /// ��ɫװ���ռ��ж�
    quest_achev_script,             /// �ű����
    quest_achev_move_to_pos,        /// �ƶ���ָ����ͼָ������
};

enum quest_time_type {
    quest_relative_time = 1,        /// ���ʱ��
    quest_abs_time,                 /// ����ʱ��
    quest_period_time,              /// �̶�ʱ���
};

enum quest_state {

    quest_state_idle                = 0,        // ����
    quest_state_accepting           = 1,        // ׼��������
    quest_state_doing               = 2,        // ������
    quest_state_ready               = 3,        // �������׼���ύ
    quest_state_complete            = 4,        // ������ɣ���������
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
    equip_logic_weapon,   /// ����
    equip_logic_armor,    /// �·�
    equip_logic_helmet,   /// ͷ��
    equip_logic_necklace, /// ����
    equip_logic_wrist,    /// ����
    equip_logic_ring,     /// ��ָ
    equip_logic_shoes,    /// Ь��

    equip_logic_max,
};

enum material_logic_type {
    material_logic_all = 0,
    material_logic_image,  /// ͼ��
    material_logic_spirit, /// ��Ԫ
    material_logic_mine,   /// ��ʯ
    material_logic_refine, /// ����
    material_logic_other,  /// ����

    material_logic_max,
};

enum book_logic_type {
    book_logic_all = 0,
    book_logic_war, /// սʿ��
    book_logic_mag, /// ��ʦ��
    book_logic_tao, /// ��ʿ��

    book_logic_max,
};

enum drug_logic_type {
    drug_logic_all = 0,
    drug_logic_normal,    /// ��ͨ��
    drug_logic_immediate, /// ˲����
    drug_logic_other,     /// ������

    drug_logic_max,
};

enum function_logic_type {
    function_logic_all = 0,
    function_logic_poison, /// ����
    function_logic_fly,    /// ����
    function_logic_bag,    /// ������չ
    function_logic_other,  /// ����

    function_logic_max,
};

enum log_action_type {
    log_action_nullptr = 0,
    log_action_item_site_fixed,     /// λ��������
    log_action_item_site_error,     /// λ������ʧ��
    log_action_item_error,          /// ��Ʒ���ִ���ϵͳ�Զ�ɾ��
    log_action_buff_error,          /// buff���ִ���
    log_action_item_stream,         /// ��Ʒ���л�ɾ��
    log_action_crash,               /// �����쳣
    log_action_item_to_json_one,    /// ��Ʒ��������һ��
    log_action_item_to_json,        /// ��Ʒ��������
    log_action_bag_item_site_error, /// ������Ʒ���Ӵ���
    log_action_item_guid_error,     /// ��Ʒguid����
    log_action_item_guid_dup,       /// ��Ʒguid�ظ�
    log_action_item_site_dup,       /// ��Ʒsite�ظ�
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
    log_action_player_item_drop_map_auto, /// �Զ����ذ�
    log_action_player_item_drop_unknown,  /// δ֪����
    log_action_player_identify_item,
    log_action_player_modify_attr,         ///�޸��������
    log_action_player_trade_stall_item_in, ///����
    log_action_destroy_item_stack,         ///�ѵ���Ʒ����
    log_action_player_item_p2h,            ///��Ʒ�������ƶ���Ӣ��
    log_action_player_item_h2p,            ///��Ʒ��Ӣ���ƶ�������
    log_action_player_item_h2h,            ///Ӣ��֮�佻����Ʒ
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
    log_action_player_learn_skill, // ��һ�ȡ����
    log_action_player_join_team,   // ������
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
    castle_state_nullptr = 0, /// �Ǳ�սδ����
    castle_state_init,        /// �Ǳ���ʼ�����
    castle_state_starting,    /// �����Ǳ�ս�����ű��ص�
    castle_state_running,     /// �Ǳ��ű������ɹ�
    castle_state_ending,      /// �����Ǳ�ս�����ű��ص�
    castle_state_max,
};

enum gp_data_type {
    gp_data_type_move = 0,
    gp_data_type_spell,
    gp_data_type_max,
};

enum sort_type {
    // �ȼ���
    sort_type_level = 0,
    sort_type_level_warrior,
    sort_type_level_mage,
    sort_type_level_tao,

    // ������
    sort_type_beauty,
    sort_type_beauty_male,
    sort_type_beauty_female,

    // ʦͽ��
    sort_type_students,
    sort_type_students_warrior,
    sort_type_students_mage,
    sort_type_students_tao,

    //������
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
    // ������Ĳ���
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

    // �ű���Ĳ���
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
    db_var_action_ignore,  //����  ����Ŀ�����ݿ�����
    db_var_action_replace, //�滻  ����Դ���ݿ�����
    db_var_action_max,     //ȡ��  ȡ������ݣ�ֻ������
    db_var_action_min,     //ȡС  ȡС�����ݣ�ֻ������
    db_var_action_sum,     //���  �����ӣ�ֻ������
    db_var_action_concat,  //����  ���������ֻ���ַ���
    db_var_action_remove,  //ɾ��  ���
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
	NAME, // ����
	TYPE, // ����
	HEAD, // ͷ��
	LEVEL, // �ȼ�
	MULTIHPSINGLEVALUE, // ����Ѫ������Ѫ��
    NAMECOLOR, //�����������ɫ
    HP,        //������������ֵ
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

//����
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
    guild_apply_status_not_applied,     // δ����
    guild_apply_status_applied,         // ������
    guild_apply_status_passed,          // ��ͨ��
    guild_apply_status_failed           // δͨ��
};

enum guild_member_status {
    guild_member_status_normal,         // ����
    guild_member_status_removed,        // ����
};

enum cust_var_type {
    cust_var_type_normal,
    cust_var_type_daily,
    cust_var_type_temp,
};

enum cust_var_merge_type {
    cvmt_keep_main          = 0,        // ������������
    cvmt_addup              = 1,        // ������ӣ��ַ���������������ֵ��������ӣ�
    cvmt_choose_bigger      = 2,        // ȡ�������ݣ�������ֵ��������Ч��
    cvmt_choose_smaller     = 3,        // ȡ��С�����ݣ�������ֵ��������Ч��
    cvmt_delete             = 4         // �������
};

enum script_type {
    script_type_player      = 0,        // �����ؽű�
    script_type_hero        = 1,        // Ӣ����ؽű�
    script_type_monster     = 2,        // ������ؽű�
    script_type_npc         = 3,        // NPC��ؽű�
    script_type_item        = 4,        // ��Ʒ��ؽű�
    script_type_map         = 5,        // ��ͼ��ؽű�
    script_type_team        = 6,        // �����ؽű�
    script_type_guild       = 7,        // �л���ؽű�
    script_type_event       = 8,        // �¼���ؽű�
    script_type_scene_magic = 9,        // ����ħ����ؽű�
    script_type_system      = 10,       // ϵͳ��ؽű�
    script_type_mail        = 12,       // �ʼ���ؽű�
    script_type_consignment = 13,       // ��������ؽű�
    script_type_achievement = 14,       // �ɾ���ؽű�
    script_type_form        = 15,       // ����ؽű�
    script_type_console     = 16,       // ����̨��ؽű�
    script_type_activity    = 17,       // ���ؽű�
    script_type_quest       = 18,       // ������ؽű�
    script_type_vip         = 19,       // VIP��ؽű�
    script_type_skill       = 20,       // ������ؽű�
    script_type_buff        = 21,       // BUFF��ؽű�
    script_type_all         = 99,
};

//enum summon_monster_type {
//    summon_monster_type_unknown             = 0,
//    summon_monster_type_normal              = 1,         // ��ͨ
//    summon_monster_type_special             = 2,         // ����
//};

enum msg_type {
    msg_type_own,    // �Լ�
    msg_type_all,    // ������
    msg_type_guild,  // �л�
    msg_type_team,   // ����
    msg_type_present,// ��ǰ
};
// װ���ɲ�������
enum item_enable_type
{
    item_enable_drop = 1,       // �Ƿ�ɶ���
    item_enable_warehousing,    // �Ƿ�ɴ���ֿ�
    item_enable_repair,         // �Ƿ������
    item_enable_sell,           // �Ƿ�ɳ���
    item_enable_auction,        // �Ƿ������
    item_enable_purchase,       // �Ƿ���չ�
    item_enable_quickbar,       // �Ƿ�ɷ�������
    item_enable_identify,       // �Ƿ�ɼ���
    item_enable_drill,          // �Ƿ�ɴ��
    item_enable_unload,         // �Ƿ��ж��
    item_enable_refine,         // �Ƿ�ɾ���
    item_enable_enhance,        // �Ƿ��ǿ��
    item_enable_deal,           // �Ƿ�ɽ���
    item_enable_savelog,        // �Ƿ񱣴��¼
    item_enable_autodel,        // �Ƿ�ʹ�ô���Ϊ0�Զ���ʧ
    item_enable_expiredel,      // �Ƿ���ɾ��
};

// ����ɲ�������
enum monster_enable_type
{
    monster_enable_canAtk = 1,          /// �Ƿ�ɱ�����
    monster_enable_saveLog,             /// �Ƿ�д��log���ݿ�
    monster_enable_canTalk,             /// �Ƿ�ɶԻ�
    monster_enable_invDetect,           /// �Ƿ���������
    monster_enable_canTurn,             /// �Ƿ��ת��
};
// buff�ɲ�������
enum buff_enable_type
{
    buff_enable_clientShow = 1,         // �Ƿ�ͻ�����ʾ
    buff_enable_offlineSave,            // �Ƿ����߱���
    buff_enable_dieAutoDel,             // �Ƿ�����ʱɾ��
    buff_enable_immShield,              // �Ƿ��м����
    buff_enable_stealth,                // �Ƿ�������
    buff_enable_disappearStealth,       // �Ƿ�����ʱ�ƶ�����ʧ
    buff_enable_timeStack,              // �Ƿ�ʱ�����
    buff_enable_effectStack,            // �Ƿ�Ч������
    buff_enable_jumpMapSave,            // �Ƿ���ת��ͼ����
    buff_enable_live,                   // �Ƿ�����ʱ�����
    buff_enable_delOnAttack,            // �Ƿ��ܹ���ʱɾ��
    buff_enable_saveLog,                // �Ƿ�д��¼
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
};//�ʼ����
enum mail_status{
    //λ�øı�����
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
    relation_chat_ntf_type_current  = 1,        // ��ǰ
    relation_chat_ntf_type_team     = 2,        // ����
    relation_chat_ntf_type_guild    = 3,        // ����
    relation_chat_ntf_type_world    = 4,        // ����
    relation_chat_ntf_type_trumpt   = 5,        // ����
    relation_chat_ntf_type_camp     = 9,        // ��Ӫ
    relation_chat_ntf_type_whole    = 12,       // ȫ��
};

enum skill_harm_type
{
    skill_harm_type_none  = 0,
    skill_harm_type_ordinary = 1,   // ��ͨ
    skill_harm_type_crit,           // ����
    skill_harm_type_miss,           // ����
    skill_harm_type_immunity,       // ����
    skill_harm_type_holyblow,       // ��ʥһ��
    skill_harm_type_extra0,         // �����˺�0
    skill_harm_type_extra1,         // �����˺�1
    skill_harm_type_extra2,         // �����˺�2
    skill_harm_type_extra3,         // �����˺�3
    skill_harm_type_extra4,         // �����˺�4
    skill_harm_type_extra5,         // �����˺�5
    skill_harm_type_extra6,         // �����˺�6
    skill_harm_type_extra7,         // �����˺�7
    skill_harm_type_extra8,         // �����˺�8
    skill_harm_type_extra9,         // �����˺�9
};

enum trap_type {
    trap_type_none      = 0,        // ������
    trap_type_fire_wall = 1,        // ��ǽ�༼��
    trap_type_other     = 2,        // �ǻ�ǽ�༼��
};

enum target_relation {                          // ���ܿ�����Ŀ��
    target_relation_other_player    = 1,        // �������
    target_relation_self            = 2,        // �Լ�
    target_relation_pet             = 4,        // ����ӹ���
    target_relation_monster         = 8,        // ����ӹ���
};

enum attr_show_ntf_type {
    attr_show_ntf_type_ordinary     = 0,        // ��ͨ
    attr_show_ntf_type_crit         = 1,        // ����
    attr_show_ntf_type_holyblow     = 2,        // ��ʥһ��
};

enum miss_ntf_type {
    miss_ntf_type_miss              = 1,        // ����
    miss_ntf_type_immunity          = 2,        // ����
};
//����׷������Ϊ���� ������׷������Ϊż��
enum pursue_attack_type {
    all_type_stay_put         = 0,            // ��AI���͵Ĺ�������ɶ���ԭ�ز���
    type1_active_pursuit      = 1,            // AI����1������׷��
    type1_non_active_pursuit  = 2,            // AI����1�Ĳ�����׷��
    type2_dadaowei            = 3,            // ������
    type3_shouchengweibing    = 5,            // �س�����
    type4_biaoche_active      = 7,            // �ڳ����������ƶ�����
    type4_biaoche_non_active  = 8,            // �ڳ����ͱ����ƶ�����
    type5_biaoche_non_master  = 9,            // �ڳ����͹��� ֻ�ƶ����յ� ��Ѻ�����޹�
    type6_normal_pet          = 10,           // ��ͨ����
    type7_taoist_pet          = 11,           // ��ʿ����ʦ����

};

enum delegate_type 
{
    delegate_type_sell = 0,    // ����
    delegate_type_buy,         // �չ�
};

enum item_state_type
{
    item_state_owner = 0,       // �������(����\�ֿ�)
    item_state_selling,         // �ϼ�(����)��
    item_state_unaccalimed,     // δ��ȡ(�ʼ�)
};
enum delegate_cancel_reason
{
    delegate_cancel_manual = 0, // ����ֶ�ȡ��
    delegate_cancel_expired,    // ����
    delegate_cancel_delete_role,
};
enum precision_type
{
    precision_type_1 = 1,   // �ٷֱ�
    precision_type_2,       // ��ֱ�
};

enum log_type
{
    log_type_currency_change = 1,   // ���ҡ����ֱ仯
    log_type_item_update,           // ��Ʒ��ɾ��(����)
    log_type_login_out,             // ��¼�ǳ�
    log_type_entery_exit_map,       // ������ͼ
    log_type_drop_item,             // ��Ʒ����
    log_type_gm_cmd,                // gmָ��
    log_type_online_num,            // ��������
    log_type_trade_data,            // ���ۼ�¼
    log_type_mail_info,             // �ʼ���¼
    log_type_death_record,          // ������¼
    log_type_activity_data,         // �
    log_type_reward_data,           // ����
    log_type_giftpack_data,         // ���
    log_type_recovery_data,         // ����
    log_type_db_exesql,             // db sql
    log_type_item_dyn_attr,         // ��Ʒ��̬���Ը���
    log_type_item_cust_var,         // ��Ʒ�Զ������Ը���
};

struct log_params
{
    std::string info = "";

    uint16_t site = 0;
    uint8_t beTrade = 0;// ������ɾ��ʱΪ1
};

struct log_item_params
{
    std::string itemKeyname = "";
    uint32_t itemNum = 0;
};
enum log_item_change_reason
{
    log_item_change_reason_pickup = 1,          /// ʰȡ���
    log_item_change_reason_monster_reward,      /// ���ｱ��
    log_item_change_reason_quest_reward,        /// ������
    log_item_change_reason_stall_buy,           /// ��̯����
    log_item_change_reason_stall_sell,          /// ��̯����
    log_item_change_reason_delegate_buy,        /// ������ί����
    log_item_change_reason_delegate_sell,       /// ������ί����
    log_item_change_reason_market_buy,          /// ������������
    log_item_change_reason_market_sell,         /// ������������
    log_item_change_reason_use,                 /// ʹ�ø���
    log_item_change_reason_move,                /// �ƶ�����
    log_item_change_reason_login_init,          /// ��¼��ʼ��
    log_item_change_reason_drop,                /// ������ʧ
    log_item_change_reason_expired,             /// ������ʧ
    log_item_change_reason_mail_get,            /// �ʼ���ȡ
    log_item_change_reason_quest_consume,       /// ��������
    log_item_change_reason_quest_acquire,       /// ���񷢷�
    log_item_change_reason_quest_collect,       /// �����ռ�
    log_item_change_reason_bag_arrange,         /// ��������
    log_item_change_reason_shop_buy,            /// �̵깺��
    log_item_change_reason_trade_mall_buy,      /// �̵깺��
    log_item_change_reason_gold_deposit,        /// ProtoGS_GoldDeposit msg
    log_item_change_reason_gold_take,           /// ProttoGS_GoldTake msg
    log_item_change_reason_lua_add,             /// �ű��������Ӷѵ�����
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
    bag_type = 1,       //����
    warehouse_type = 2,   /// �ֿ�
    adv_warehouse_type = 3, /// �߼��ֿ�
};

enum monster_attck_status
{
    monster_attack_non          = 0,  //δ���빥��״̬
    monster_attack_ing          = 1,  //���ڹ�����
    monster_attack_finish       = 2,  //�������
    monster_attck_wait_finish   = 3,  //�����ȴ�
    monster_attack_ready_finish = 4,  //����׼�����
};

enum monster_behaviour_trigger
{
    monster_ai_discover_target,             //����Ŀ�꣺ָ���ﴦ�ڴ�����Ѳ�ߵȷ�ս��״̬�·���Ŀ��
    monster_ai_target_hp,                   //Ŀ��Ѫ��
    monster_ai_self_hp,                     //����Ѫ��
    monster_ai_die_trigger,                 //��������
    monster_ai_start_fight_time,            //ս����ʼʱ��
    monster_ai_target_and_self_instance,       //Ŀ�����������
    monster_ai_target_job,                     //Ŀ��ְҵ
    monster_ai_self_harmed_by_special_skill,  //�յ�ָ�������˺�
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
    // ���������ͬ relation_chat_ntf_type
    lua_chat_msg_dialog_current = 1,        // ��ǰ
    lua_chat_msg_dialog_team = 2,        // ����
    lua_chat_msg_dialog_guild = 3,        // ����
    lua_chat_msg_dialog_world = 4,        // ����
    lua_chat_msg_dialog_trumpt = 5,        // ����
    lua_chat_msg_dialog_camp = 9,        // ��Ӫ
    lua_chat_msg_dialog_whole = 12,       // ȫ��
    // ϵͳ��Ϣ
    lua_chat_msg_dialog_sys_all         = 20,
    lua_chat_msg_dialog_sys_map         = 21,
    lua_chat_msg_dialog_sys_region      = 22,
    lua_chat_msg_dialog_sys_single      = 23,
    // ������Ϣ
    lua_chat_msg_scene_appear_all       = 24,
    lua_chat_msg_scene_appear_map       = 25,
    lua_chat_msg_scene_appear_region    = 26,
    lua_chat_msg_scene_appear_single    = 27,
    // �����
    lua_chat_msg_scroll_text_all        = 28,
    lua_chat_msg_scroll_text_map        = 29,
    lua_chat_msg_scroll_text_region     = 30,
    lua_chat_msg_scroll_text_single     = 31,
};

enum castle_war_monster_type
{
    main_city_front_door_monster    = 1,        // �������Ź�
    palace_front_door_monster       = 2,        // �ʹ����Ź�
    palace_side_door_monster        = 3,        // �ʹ����Ź�
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
    server_status_maintenance = 1,        // ά��
    server_status_reset_maintenance = 2,  // �ر�ά��
    server_status_close = 3,              // �ط�
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
    pet_type_normal = 1,   // ͨ�ó���
    pet_type_taoist = 2,   // ��ʦ��ʿ����
};


enum check_role_existence_method
{
    by_name = 0,
    by_guid = 1,
};

enum role_status
{
    role_status_new         = 0,        // ��δ������Ϸ
    role_status_normal      = 1,        // ����
    role_status_deleted     = 2,        // ��ɫ��ɾ��
    role_status_permanent_deleted = 3,  // ��ɫ����ɾ��
    role_status_new_deleted = 4,        // ��ɫû�н�����Ϸ����ɾ��
};

enum class jump_map_type
{
    default_type_null = 0,
    sys_jump_map_point = 1,     // ϵͳ��ת��
    dyn_jump_map_point = 2,     // ��̬��ת��
    jump_map_item_1 = 3,    // ��ת����1
    jump_map_skill_1 = 4,   // ��ת����1

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
    start_dig_no_target     = 1,    // Ŀ�겻����
    start_dig_out_of_range  = 2,    // ���벻�ٷ�Χ��
    start_dig_digging       = 3,    // ������
    start_dig_other_reason  = 4     // ����ԭ��
};

enum stop_dig_reason
{
    stop_dig_timeup         = 0,    // ����ʱ����
    stop_dig_role_move      = 1,    // ��ɫ�ƶ�
    stop_dig_role_die       = 2,    // ��ɫ����
    stop_dig_taken_away     = 3     // ������������
};

enum role_appear_type
{
    role_appear_normal      = 0,
    role_appear_born        = 1,    // ����
    role_appear_jump        = 2,    // ��Ծ
    role_appear_digging     = 3     // �ڱ�
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
    middle_platform_chat_type_near     = 1,        // ����\����
    middle_platform_chat_type_team     = 2,        // ����
    middle_platform_chat_type_guild    = 3,        // ����
    middle_platform_chat_type_tumpt    = 4,        // ����
    middle_platform_chat_type_private  = 5,        // ˽��
    middle_platform_chat_type_world    = 6,        // ����
    middle_platform_chat_type_map      = 7,        // ��ͼ

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

// ��Ʒ���ø����� ��Ӧ����ֱ�ӵ���
enum player_drop_type
{
    player_drop_type_normal      = 0,
    player_drop_type_logout      = 2,   // �˳���¼ʱ    
    player_drop_type_leave_map   = 4,   // �뿪��ͼʱ
    player_drop_type_die         = 8,   // ����ʱ
    player_drop_type_jump_map    = 16,  // ��ת��ͼʱ
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