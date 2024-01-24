#pragma once

#include "ProtoDef.h"
#include "ProtoLog.h"

#define DEF_PROTO_HEADER_CLIENT3(protoid) uint16_t moduleid = MODULE_TYPE_CLIENT3; uint16_t protocolid = protoid
#define REDEF_PROTO_HEADER_CLIENT3(protoid) moduleid = MODULE_TYPE_CLIENT3; protocolid = protoid

enum
{
    PROTO_CLIENT3_ENTER_GS_ACK                  = 1,            // CLIENT->GS->CS
    PROTO_CLIENT3_EXIT_GS_REQ                   = 2,            // CLIENT->GS->MS,���ˣ�С��
    PROTO_CLIENT3_EXIT_GS_ACK                   = 3,            // MS->GS->CLIENT

    PROTO_CLIENT3_KICK_ROLE_NTF                 = 5,            
    PROTO_CLIENT3_ENTER_GS_NTF                  = 6,            // CLIENT->GS->CS

    PROTO_CLIENT3_RELIVE_REQ                    = 9,           // ms ->gs-> client
    PROTO_CLIENT3_RELIVE_ACK                    = 10,           // ms ->gs-> client
    PROTO_CLIENT3_NPC_APPEAR_NTF                = 14,           // GS -> CLIENT
    PROTO_CLIENT3_DISAPPEAR_NTF                 = 15,           // ms ->gs-> client
    PROTO_CLIENT3_MOVE_REQ                      = 17,           // CLIENT -> GS
    PROTO_CLIENT3_MOVE_NTF                      = 18,           // ms ->gs-> client
    PROTO_CLIENT3_MOVE_ACK                      = 19,           // GS -> CLIENT
    PROTO_CLIENT3_TURN_REQ                      = 20,           // CLIENT -> GS
    PROTO_CLIENT3_TURN_NTF                      = 21,           // GS -> CLIENT
    PROTO_CLIENT3_OBJDIE_NTF                    = 23,           // GS -> CLIENT

    PROTO_CLIENT3_GM_COMMAND_REQ                = 25,

    PROTO_CLIENT3_ROLE_ATTR_NTF                 = 27,          // MS->GS->->CLIENT
    PROTO_CLIENT3_ROLE_ATTR_EXT_NTF             = 28,          // MS->GS->->CLIENT

    PROTO_CLIENT3_RUN_CLIENT_SCRIPT             = 30,           // GS -> CLIENT

    PROTO_CLIENT3_ITEM_ACK                      = 33,           // GS -> CLIENT
    PROTO_CLIENT3_ITEM_DESTROY_ACK              = 35,            // MS->GS->CLIENT
    PROTO_CLIENT3_ITEM_MOVE                     = 36,            // MS->GS->CLIENT
    PROTO_CLIENT3_ITEM_SPLIT                    = 37,            // MS->GS->CLIENT
    PROTO_CLIENT3_ITEM_ATTR_NTF                 = 38,
    PROTO_CLIENT3_ITEM_UPDATE_NTF               = 39,           // GS -> CLIENT
    PROTO_CLIENT3_ITEM_APPLY                    = 41,           // GS -> CLIENT
    PROTO_CLIENT3_ITEM_ARRANGE                  = 44,           // CLIENT -> GS           
    PROTO_CLIENT3_ITEM_PICK_UP                  = 45,           // GS -> CLIENT
    PROTO_CLIENT3_ITEM_DROP                     = 46,           // GS -> CLIENT

    PROTO_CLIENT3_ITEM_TIP                      = 48,          
    PROTO_CLIENT3_ITEM_TIP_NTF                  = 50,

    PROTO_CLIENT3_SKILL_ADD_ACK                 = 64,           // GS -> CLIENT
    PROTO_CLIENT3_SKILL_DELETE_ACK              = 66,
    PROTO_CLIENT3_SKILL_SWITCH                  = 67,           // CLIENT -> GS
    PROTO_CLIENT3_SKILL_SWITCH_ACK              = 68,           // GS -> CLIENT
    PROTO_CLIENT3_SKILL_PROFICIENCY_NTF         = 69,           // GS -> CLIENT
    PROTO_CLIENT3_BUFF_ADD_ACK                  = 70,           // GS -> CLIENT
    PROTO_CLIENT3_BUFF_DESTROY_ACK              = 72,           // GS -> CLIENT
    PROTO_CLIENT3_SPELL_TARGET                  = 76,           // CLIENT -> GS
    PROTO_CLIENT3_SPELL_GRID                    = 77,           // CLIENT -> GS
    PROTO_CLIENT3_SPELL_ACK                     = 78,           // GS -> CLIENT
    PROTO_CLIENT3_SPELL_NTF                     = 79,           // GS -> CLIENT
    PROTO_CLIENT3_MISS_NTF                      = 81,           // GS -> CLIENT
    PROTO_CLIENT3_TRADE_NPC_BUY                 = 84,           // CLIENT -> GS
    PROTO_CLIENT3_TRADE_NPC_SHOP_NTF            = 88,           // GS -> CLIENT
    PROTO_CLIENT3_PLAYER_SWITCH_REQ             = 114,          //
    PROTO_CLIENT3_ATK_MODE_REQ                  = 115,          // GS -> CLIENT
    PROTO_CLIENT3_LEVEL_UP_NTF                  = 118,          // GS -> CLIENT
    PROTO_CLIENT3_PLAYER_QUERY                  = 119,          // GS -> CLIENT
    PROTO_CLIENT3_PLAYER_QUERY_NTF              = 121,          // CLIENT -> GS

    PROTO_CLIENT3_TITLE_REMOVE                  = 126,
    PROTO_CLIENT3_TITLE_APPLY                   = 127,
    PROTO_CLIENT3_TITLE_ADD_ACK                 = 128,
    PROTO_CLINET3_TITLE_REMOVE_ACK              = 129,

    PROTO_CLIENT3_NPC_SELECT                    = 132,          // CLIENT -> GS
    PROTO_CLIENT3_NPC_TALK_REQ                  = 133,          // CLIENT -> GS
    PROTO_CLIENT3_QUEST_NPC_TALK_ACK            = 134,          // CLIENT -> GS

    PROTO_CLIENT3_QUICK_BAR_SET                 = 135,          // CLIENT -> GS  fyt
    PROTO_CLIENT3_QUICK_BAR_SET_NTF             = 136,          // GS -> CLIENT  fyt

    PROTO_CLIENT3_GOLD_DEPOSIT                  = 142,
    PROTO_CLIENT3_GOLD_TAKE                     = 143,

    PROTO_CLIENT3_ROLE_ATTR_EXT_REF_NTF         = 145,          // GS -> CLIENT
    PROTO_CLIENT3_FAMILY_WAR_NTF                = 147,          // GS -> CLIENT
    PROTO_CLIENT3_PLAYER_FAMILY_CHANGE_NTF      = 150,
    PROTO_CLIENT3_TRADE_MALL_BUY                = 159,
    PROTO_CLIENT3_TRADE_MALL_LIST_REQ           = 160,
    PROTO_CLIENT3_TRADE_MALL_LIST_ACK           = 161,
    PROTO_CLIENT3_QUEST_ACCEPT                  = 168,          // CLIENT -> GS
    PROTO_CLIENT3_QUEST_ACCOMPLISH              = 170,          // CLIENT -> GS
    PROTO_CLIENT3_QUEST_UPDATE_NTF              = 171,          // GS -> CLIENT
    PROTO_CLIENT3_QUEST_DROP                    = 176,          // CLIENT -> GS
    PROTO_CLIENT3_QUEST_DROP_NTF                = 177,          // GS -> CLIENT

    PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT        = 178,          // CLIENT -> GS
    PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT_NTF    = 179,          // GS -> CLIENT

    PROTO_CLIENT3_DELEGATE_SELL_CMD             = 180,
    PROTO_CLIENT3_DELEGATE_BUY_CMD              = 181,
    PROTO_CLIENT3_DELEGATE_SELL_LIST_REQ        = 182,
    PROTO_CLIENT3_DELEGATE_SELL_LIST_ACK        = 183,
    PROTO_CLIENT3_DELEGATE_BUY_LIST_REQ         = 184,
    //PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK         = 185,
    PROTO_CLIENT3_MARKET_BUY_CMD                = 186,
    PROTO_CLIENT3_MARKET_SELL_CMD               = 187,
    PROTO_CLIENT3_DELEGATE_CANCEL               = 188,
    PROTO_CLIENT3_DELEGATE_MINE_REQ             = 189,
    //PROTO_CLIENT3_DELEGATE_MINE_ACK             = 190,

    PROTO_CLIENT3_GLOBAL_NTF                    = 202,

    PROTO_CLIENT3_RUN_SERV_SCRIPT_ACK           = 242,          // GS -> CLIENT
    PROTO_CLIENT3_QUEST_NPC_STATE_NTF           = 253,          // GS -> CLIENT
    PROTO_CLIENT3_QUERY_EX                      = 283,    
    PROTO_CLIENT3_ENTER_GS_REQ                  = 307,          // CLIENT->GS->CS->MS
    PROTO_CLIENT3_GET_ARROUND_TEAM_REQ          = 329, 
    PROTO_CLIENT3_GET_ARROUND_TEAM_ACK          = 330, 
    PROTO_CLIENT3_ROLE_APP_NTF                  = 333, 
    PROTO_CLIENT3_ITEM_APPEAR_NTF4              = 338,         // MS->GS->->CLIENT
    PROTO_CLIENT3_DELEGATE_MINE_ACK2            = 342,
    PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK2        = 343,
    PROTO_CLIENT3_PLAYER_APPEAR_NTF3            = 346,         // MS->GS->->CLIENT
    PROTO_CLIENT3_MONSTER_APPEAR_NTF6           = 348,         // MS->GS->->CLIENT
    PROTO_CLIENT3_ATTR_SHOW_NTF2_EX2            = 355,         // MS->GS->->CLIENT
    PROTO_CLIENT3_SKILL_CD_CHANGED_NTF          = 402,         // GS -> CLIENT
    PROTO_CLIENT3_RUN_SERV_SCRIPT_REQ           = 403,         // CLIENT -> GS
    PROTO_CLIENT3_QUEST_ADD_NTF                 = 405,         // GS -> CLIENT
    PROTO_CLIENT3_SKILL_PROP_PERMANENT_CHANGED_NTF = 406,        // GS -> CLIENT
    PROTO_CLIENT3_QUEST_TIMEOUT_NTF             = 407,         // GS -> CLIENT
    PROTO_CLIENT3_QUEST_STATE_NTF               = 408,         // GS -> CLIENT
    PROTO_CLIENT3_SKILL_STATUS_NTF              = 409,         // GS -> CLIENT
    PROTO_CLIENT3_ROLE_DYN_ATTR_NTF             = 410,          // MS->GS->->CLIENT
    PROTO_CLIENT3_ROLE_CUST_VAR_NTF             = 411,          // MS->GS->->CLIENT
    PROTO_CLIENT3_SHABAK_OWNER_NTF              = 412,          // GS -> CLIENT
    PROTO_CLIENT3_SHABAK_LOSS_NTF               = 413,          // GS -> CLIENT
    PROTO_CLIENT3_SHABAK_ENGAGE_NTF             = 414,          // GS -> CLIENT
    PROTO_CLIENT3_SHABAK_END_NTF                = 415,          // GS -> CLIENT
    PROTO_CLINET3_TRADE_LIST_UPDATE             = 416,
    PROTO_CLIENT3_ROLE_INFO_CHANGE_NTF          = 417,
    PROTO_CLIENT3_JUMP_MAP_REQ                  = 418,
    PROTO_CLIENT3_ITEM_PICKUP_NTF               = 419,
    PROTO_CLIENT3_AUTO_PICKUP_SETTINGS_NTF      = 420,
    PROTO_CLINET3_MONSTER_PURSURE_STATUS_CHANGE_NTF = 421,
    PROTO_CLIENT3_GET_NPC_POS_REQ               = 422,
    PROTO_CLIENT3_GET_NPC_POS_ACK               = 423,
    PROTO_CLIENT3_START_DIG_REQ                 = 424,
    PROTO_CLIENT3_START_DIG_ACK                 = 425,
    PROTO_CLIENT3_STOP_DIG_NTF                  = 426,
    PROTO_CLIENT3_ROLE_APPEAR_NTF               = 427,
    PROTO_CLIENT3_RANGE_PICKUP                  = 428,
    PROTO_CLIENT3_SYNC_CLIENT_BASE_SETTING      = 429,
    PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_REQ      = 430,
    PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_ACK      = 431,
    PROTO_CLIENT3_PLAYER_SET_NAME_NTF           = 432,
    PROTO_CLIENT3_ITEM_REFRESH_REQ              = 433,
    PROTO_CLIENT3_TITLE_UNAPPLY                 = 434,
    PROTO_CLIENT3_TITLE_LIST                    = 435,
    PROTO_CLIENT3_TITLE_APPLY_NTF               = 436,
    PROTO_CLIENT3_TITLE_UNAPPLY_NTF             = 437,
    PROTO_CLIENT3_MONSTER_BACK_NTF              = 438,
    PROTO_CLIENT3_SET_AUTO_MODE_REQ             = 439,
    PROTO_CLIENT3_SET_AUTO_MODE_ACK             = 440,
    PROTO_CLIENT3_RECORDS_MIN_REQ               = 441,
    PROTO_CLIENT3_RECORDS_MINE_ACK              = 442,
    PROTO_CLIENT3_TITLE_GET_LIST_REQ            = 443,
    PROTO_CLIENT3_SCENE_ITEM_UPDATE_NTF         = 444,

    PROTO_CLIENT3_ROLE_CUST_VAR_REQ             = 445,
    PROTO_CLIENT3_Send_GOODS_POST_REOCRD_TO_CLIENT  = 446,
    PROTO_CLIENT3_GOODS_POST_RECORD_ACK        = 447,
    PROTO_CLIENT3_EFEECT_APPEAR_NTF = 448,
    PROTO_CLIENT3_EFFECT_DISAPPEAR_NTF = 449,

    PROTO_CLIENT3_MAX
};

struct ProtoClient3_EffectAppearNtf{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_EFEECT_APPEAR_NTF);
    uint16_t num = 0;
    EffectPoint info[100];
    uint16_t type = 0;
};

struct ProtoClient3_EffectDisAppearNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_EFFECT_DISAPPEAR_NTF);
    uint16_t num = 0;
    EffectPoint info[100];
    uint16_t type = 0;
};

struct ProtoClient3_GoodsPostRecordAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GOODS_POST_RECORD_ACK);
    char    order_no[ORDER_NO_BUFLEN] = { 0 };           // ������
    ProtoClient3_GoodsPostRecordAck() = default;
};

struct ProtoClient3_SendGoodsPostRecordToClient {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_Send_GOODS_POST_REOCRD_TO_CLIENT);
    GOODS_ISSUE_RECORD record;
    ProtoClient3_SendGoodsPostRecordToClient() = default;
};

struct ProtoClient3_TitleGetListReq{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_GET_LIST_REQ);
    ProtoClient3_TitleGetListReq() = default;
};

struct ProtoClient3_MonsterBackNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MONSTER_BACK_NTF);
    uint64_t guid   = 0;
    uint16_t status = 0;
    ProtoClient3_MonsterBackNtf() = default;
};

struct ProtoClient3_ItemTip {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_TIP);
    uint64_t owner_guid = 0;
    uint64_t item_guid  = 0;
    ProtoClient3_ItemTip() = default;
};

struct ProtoClient3_ItemTipNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_TIP_NTF);
    ITEM_INFO    info;
    ProtoClient3_ItemTipNtf() = default;
};

struct ProtoClient3_GetNpcPosReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GET_NPC_POS_REQ);
    char      name[256];                          // ����

    ProtoClient3_GetNpcPosReq() = default;
};

struct ProtoClient3_GetNpcPosAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GET_NPC_POS_ACK);
    uint16_t  posx;
    uint16_t  posy;
    uint8_t   result;
    ProtoClient3_GetNpcPosAck() = default;
};

struct ProtoClient3_TradeMallListUpdate {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLINET3_TRADE_LIST_UPDATE);
    unsigned char             item_count; //��Ʒ����
    MALL_ITEM_INFO            item_list[250]; //��Ʒ��Ϣ�б�
    ProtoClient3_TradeMallListUpdate() = default;
};

struct ProtoClient3_GMCommandReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GM_COMMAND_REQ);

    int32_t                     sn              = 0;        //���к�
    char                        cmd[256]        = {0};      //GM ָ��
    char                        param[65535]      = {0};      //ָ�����
    void Clear()
    {
        memset(this, 0, sizeof(ProtoClient3_GMCommandReq));
        REDEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GM_COMMAND_REQ);
    }
};

struct ProtoClient3_GoldTake {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GOLD_TAKE);
    int64_t                   gold; //gold
    ProtoClient3_GoldTake() = default;
};


struct ProtoClient3_GoldDeposit {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GOLD_DEPOSIT);
    int64_t                   gold; //gold
    ProtoClient3_GoldDeposit() = default;
};

struct ProtoClient3_GlobalNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GLOBAL_NTF);
    unsigned short            int_count = 0;      //�������ݸ���
    IntData                   int_data[256];  //����ֵ
    unsigned short            str_count = 0;      //�ַ������ݸ���
    StrData                   str_data[256];
    ProtoClient3_GlobalNtf() = default;
};

struct ProtoClient3_QuickBarSet {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUICK_BAR_SET);

    unsigned char             type;//0=null 1=item 2=skill
    unsigned char             slot;//��λ
    unsigned short            id;//ģ��id
    uint64_t                  guid;//��Ʒid

    ProtoClient3_QuickBarSet() = default;
};

struct ProtoClient3_QuickBarSetNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUICK_BAR_SET_NTF);

    unsigned short            num;//���������
    QUICK_BAR_INFO            info[30];//�������Ϣ
    ProtoClient3_QuickBarSetNtf() = default;
};

struct ProtoClient3_GetAroundTeamReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GET_ARROUND_TEAM_REQ);

    ProtoClient3_GetAroundTeamReq() = default;
};

struct ProtoClient3_GetAroundTeamAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_GET_ARROUND_TEAM_ACK);

    unsigned char             list_size; //�б��С
    TEAM_MEMBER               list_data[20]; //�б�����
    ProtoClient3_GetAroundTeamAck() = default;
};

struct ProtoClient3_PlayerSwitchReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_PLAYER_SWITCH_REQ);

    unsigned char             id; //id(player_switch_type)
    unsigned char             value; //����ֵ
    ProtoClient3_PlayerSwitchReq() = default;
};

struct ProtoClient3_PlayerReliveReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RELIVE_REQ);

    unsigned char             relive_type; //�������� 1=ԭ�ظ��� 2=�سǸ��� 3=������ڸ���
    ProtoClient3_PlayerReliveReq() = default;
};

struct ProtoClient3_PlayerReliveAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RELIVE_ACK);

    unsigned char             relive_type; //�������� 1=ԭ�ظ��� 2=�سǸ��� 3=������ڸ���
    int                       error_code; //������ 0=��ʾ�ɹ�
    ProtoClient3_PlayerReliveAck() = default;
};

struct ProtoClient3_ItemPickUp {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_PICK_UP);

    ProtoClient3_ItemPickUp() = default;
};

struct ProtoClient3_ItemAppearNtf4
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_APPEAR_NTF4);

    uint64_t                    item_guid           = 0;            // item guid
    uint16_t                    template_id         = 0;            // ģ��id
    int32_t                     dst_x               = 0;            // Ŀ���x
    int32_t                     dst_y               = 0;            // Ŀ���y
    uint16_t                    skill_id            = 0;            // ����id
    char                        item_name[64]       = {0};          // ��Ʒ����
    int16_t                     seed                = 0;            // У������
    uint8_t                     is_drop             = 0;            // �Ƿ��ǵ������
    uint64_t                    owner_guid          = 0;            // ӵ����guid
    uint64_t                    team_guid           = 0;            // ӵ���߶���guid
};

struct ProtoClient3_ItemDestroyAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_DESTROY_ACK);

    uint64_t                  item_guid; //��ƷGUID
    ProtoClient3_ItemDestroyAck() = default;
};


struct ProtoClient3_ItemUpdateNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_UPDATE_NTF);

    ITEM_INFO                 info;
    ProtoClient3_ItemUpdateNtf() = default;
};

struct ProtoClient3_ItemApply {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_APPLY);

    uint64_t                  item_guid; //��ƷGUID
    uint32_t                  num;       //��Ʒ����
    ProtoClient3_ItemApply() = default;
};

struct ProtoClient3_ItemDrop {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_DROP);

    uint64_t                  item_guid; //��ƷGUID
    ProtoClient3_ItemDrop() = default;
};

struct ProtoClient3_RoleCustVarReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_CUST_VAR_REQ);

    uint64_t                    role_guid = 0;
};

struct ProtoClient3_RoleCustVarNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_CUST_VAR_NTF);

    uint64_t                    role_guid = 0;
    CUSTOM_INFO                 custom;
    uint8_t                     type = 0;        //0=ȫ�� 1=����
};

struct ProtoClient3_RoleDynAttrNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_DYN_ATTR_NTF);

    uint64_t                  role_guid = 0;
    CUSTOM_INFO                 custom;
};

struct ProtoClient3_RoleInfoChangeNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_INFO_CHANGE_NTF);

    uint64_t                    role_guid = 0;
    uint16_t                    num = 0;
    CUSTOM_INFO                 custom;
};

struct ProtoClient3_RoleAttrExtNtf {

    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_ATTR_EXT_NTF);

    uint64_t                  player_guid; //player guid
    unsigned short            num; //����
    unsigned short            attr_name[20]; //��������
    int64_t                   attr_value[20]; //����ֵ
    ProtoClient3_RoleAttrExtNtf() = default;
};

struct ProtoClient3_RoleAttrNtf{

    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_ATTR_NTF);

    uint64_t                  role_guid; //role guid
    unsigned short            num; //����
    unsigned short            attr_name[100]; //��������
    int                       attr_value[100]; //����ֵ
    ProtoClient3_RoleAttrNtf() = default;
};

struct ProtoClient3_ItemAddAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_ACK);

    char                      isPackItem;
    ITEM_INFO                 info; 
    ProtoClient3_ItemAddAck() = default;
};
static ProtoClient3_ItemAddAck gProtoClient3_ItemAddAck;

struct ProtoClient3_ObjDisappearNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DISAPPEAR_NTF);

    uint64_t                  obj_guid; //obj guid
    ProtoClient3_ObjDisappearNtf() = default;
};

struct ProtoClient3_NpcAppearNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_NPC_APPEAR_NTF);

    uint64_t                    npc_guid            = 0;
    uint16_t                    template_id         = 0;            // ģ��id
    uint16_t                    dst_x               = 0;            // Ŀ���x
    uint16_t                    dst_y               = 0;            // Ŀ���y
    uint8_t                     dir                 = 0;            // ����
    char                        name[256];                          // ����
    uint32_t                    modelid             = 0;            // ģ��id

    ProtoClient3_NpcAppearNtf()
    {
        memset(name, 0, sizeof(name));
    }
};

struct ProtoClient3_NpcSelect
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_NPC_SELECT);

    uint64_t                    npc_guid            = 0;
};

struct ProtoClient3_NpcTalkReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_NPC_TALK_REQ);

    uint64_t                    npc_guid            = 0;
    char                        func[256]           = {0};
};

struct ProtoClient3_TradeNpcBuy
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TRADE_NPC_BUY);

    uint16_t                    shop_id             = 0;            // shop_index
    uint16_t                    item_index          = 0;            // item_index
    uint16_t                    item_amount         = 0;            // ��Ʒ����
    uint8_t                     is_bind             = 0;            // �Ƿ�ʹ�ð󶨽��, 1��ʹ�ã�0����ʹ��
};

struct ProtoClient3_TradeNpcShopNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TRADE_NPC_SHOP_NTF);

    uint16_t                    shop_id             = 0;            // shop_index
    uint8_t                     item_count          = 0;            // ��Ʒ����
    SHOP_ITEM_INFO              item_list[250];                     // ��Ʒ��Ϣ�б�

    ProtoClient3_TradeNpcShopNtf()
    {
        memset(item_list, 0, sizeof(item_list));
    }
};

struct ProtoClient3_MonsterAppearNtf6 {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MONSTER_APPEAR_NTF6);

    uint64_t                  monster_guid; //monster guid
    char                      monster_name[50];
    unsigned short            template_id; //ģ��id
    int                       dst_x; //Ŀ���x
    int                       dst_y; //Ŀ���y
    unsigned char             dir; //����
    unsigned int              cur_hp; //��ǰѪ��
    unsigned int              max_hp; //���Ѫ��
    unsigned char             status; //����״̬ 0=���� 1=���� 2=���ڹ�
    unsigned char             servant_lv; //��ӵȼ�
    unsigned short            move_speed; //�ƶ��ٶ�
    unsigned short            buff_num; //Buff����
    BUFF_INFO                 buffs[50]; //Buff��Ϣ
    char                      master_name[32]; //���˵�����
    unsigned char             appear_type; //�������� 0=������Ұ 1=���� 2=��Ծ
    short                     seed; //У������
    unsigned short            attack_speed; //�����ٶ�
    CUSTOM_INFO               custom; //�Զ�������
    unsigned int              inner_force; //��ǰ�ڹ�
    unsigned int              max_inner_force; //����ڹ�
    unsigned int              modelid; //�ı������
    unsigned short            reserve_num; //�����ֶ�����
    unsigned int              reserve_values[10]; //�����ֶ�
    char                      name_color[10];     //������ɫ
    ProtoClient3_MonsterAppearNtf6() = default;
};

struct ProtoClient3_ExitGSReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_EXIT_GS_REQ);

    unsigned char             exittype{2}; //�˳����� 1=���� 2=С��
    ProtoClient3_ExitGSReq() = default;
};

struct ProtoClient3_ExitGSAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_EXIT_GS_ACK);

    unsigned char             exittype{2}; //�˳����� 1=���� 2=С��
    int                       errcode{0}; //������
    char                      errmsg[256]; //��������
    ProtoClient3_ExitGSAck() 
    {
        memset(errmsg,0,256);
    }
};

struct ProtoClient3_MoveNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MOVE_NTF);

    uint64_t           guid;  // player/monster/npc's guid
    unsigned char   type;       //�ƶ����� 0=�� 1=�� 2=��
    unsigned short dst_x;     //Ŀ���x
    unsigned short dst_y;     //Ŀ���y
 

    ProtoClient3_MoveNtf() : guid(0), type(0), dst_x(0), dst_y(0)
    {
    }
};

struct ProtoClient3_MoveReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MOVE_REQ);

    uint64_t        role_guid   = 0;        //��ɫguid
    uint8_t         type        = 0;        //�ƶ����� 0=�� 1=��
    uint16_t        dst_x       = 0;        //Ŀ���x
    uint16_t        dst_y       = 0;        //Ŀ���y
    uint32_t        idx         = 0;        //�ͻ������к�
};

struct ProtoClient3_MoveAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MOVE_ACK);

    uint64_t        role_guid   = 0;        //��ɫguid
    uint8_t         ret         = 0;        //0=�ɹ�, 1=��ʾʧ��
    uint8_t         type        = 0;        //�ƶ����� 0=�� 1=��
    uint16_t        dst_x       = 0;        //�ƶ�ǰ�ĵ�x
    uint16_t        dst_y       = 0;        //�ƶ�ǰ�ĵ�y
    uint32_t        idx         = 0;        //�ͻ������к�
};

struct ProtoClient3_TurnReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TURN_REQ);

    uint64_t        role_guid   = 0;
    uint8_t         dir         = 0;        //��ɫ���ڵķ���
};

struct ProtoClient3_TurnNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TURN_NTF);

    uint64_t        guid;
    uint8_t         dir;        //��ɫ���ڵķ���

    ProtoClient3_TurnNtf() : guid(0), dir(0)
    {}
};

struct ProtoClient3_ObjDieNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_OBJDIE_NTF);

    uint64_t        die_guid    = 0;    //�����Ķ����guid ������player/monster/npc
    uint64_t        kill_guid   = 0;    //ɱ�ֵĶ����guid ������player/monster/npc
    char            kill_name[32];      //ɱ�ֵ�����

    ProtoClient3_ObjDieNtf()
    {
        memset(kill_name, 0, sizeof(kill_name));
    }
};

struct ProtoClient3_SkillAddAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_ADD_ACK);

    uint64_t        role_guid   = 0;    // ��ɫGUID
    uint16_t        num         = 0;    // ��������
    SKILL_INFO      info[100];          // ������Ϣ
    uint8_t         add = 0;            //�Ƿ�������
    ProtoClient3_SkillAddAck()
    {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoClient3_SkillDeleteAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_DELETE_ACK);

    unsigned short            id; //����id
    ProtoClient3_SkillDeleteAck() = default;
};

struct ProtoClient3_SkillSwitch
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_SWITCH);

    uint16_t        id          = 0;    // ����id
    uint8_t         active      = 0;    // 0=������ 1=����
};

struct ProtoClient3_SkillSwitchAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_SWITCH_ACK);

    uint16_t        id          = 0;    // ����id
    uint8_t         active      = 0;    // 0=������ 1=����
};

struct ProtoClient3_SkillProficiencyNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_PROFICIENCY_NTF);

    uint16_t        id          = 0;    // ����id
    uint32_t        proficiency = 0;    // ����������
};

struct ProtoClient3_BuffAddAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_BUFF_ADD_ACK);

    uint64_t        role_guid   = 0;    // ������player/monster/npc's guid
    uint16_t        num         = 0;    // Buff����
    BUFF_INFO       info[50];           // Buff��Ϣ

    ProtoClient3_BuffAddAck()
    {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoClient3_BuffDestroyAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_BUFF_DESTROY_ACK);

    uint64_t        role_guid   = 0;    // ������player/monster/npc's guid
    uint16_t        id          = 0;    // Buff id
};

struct ProtoClient3_SpellTarget
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SPELL_TARGET);

    uint64_t        role_guid   = 0;            //��ɫguid
    uint16_t        id          = 0;            //����id
    uint64_t        target      = 0;            //Ŀ��, ������player/monster/npc's guid
    uint16_t        idx         = 0;            //ʱ�������λms
};

struct ProtoClient3_SpellGrid
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SPELL_GRID);

    uint64_t        role_guid   = 0;            // ��ɫguid
    uint16_t        id          = 0;            // ����id
    uint16_t        target_x    = 0;            // Ŀ���߼����X����
    uint16_t        target_y    = 0;            // Ŀ���߼����Y����
    uint16_t        idx         = 0;            // ʱ�������λms
    uint64_t        ref_target  = 0;            // ����Ŀ��guid
    uint8_t         extra       = 0;            // �չ�ʱ������ʾ�Ƿ�ʹ�ô�ɱ��Ч
};

struct ProtoClient3_SpellAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SPELL_ACK);

    uint64_t        role_guid       = 0;
    uint16_t        id              = 0;        //����id
    int32_t         ecode           = -1;       //������
    char            detail[256]     = {0};      //��������
    uint16_t        idx             = 0;        //~
};

struct ProtoClient3_SpellNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SPELL_NTF);

    uint64_t        actor       = 0;            // ʩ����, ������player/monster/npc's guid
    uint16_t        id          = 0;            // ����id
    uint16_t        target_x    = 0;            // Ŀ���߼����X����
    uint16_t        target_y    = 0;            // Ŀ���߼����Y����
    uint16_t        num         = 0;            // ��ЧĿ������
    uint64_t        targets[50] = {0};          // Ŀ�꼯, ������player/monster/npc's guid
    uint8_t         extra       = 0;            // �չ�ʱ������ʾ�Ƿ�ʹ�ô�ɱ��Ч
};

struct ProtoClient3_EnterGSReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ENTER_GS_REQ);

    char                entertype   = -1;       //�������� 0=���� 1=����
    char                fangchenmi  = -1;       //�Ƿ�������û� 1���� 0����
    char                clienttype  = -1;       //�ͻ������� 0=�ͻ��� 1=ҳ�� 2=����

    ROLE_BRIEF_INFO     roleBriefInfo;

    ProtoClient3_EnterGSReq()
    {
        memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
    }
};


struct ProtoClient3_EnterMSAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ENTER_GS_ACK);

    unsigned char             entertype; //�������� 0=���� 1=����
    uint64_t                  roleguid; //��ɫguid
    unsigned int              gsobjid; //�ͻ�����GS�ϵ�objid
    int                       errcode; //������
    char                      errmsg[256]; //��������
    ProtoClient3_EnterMSAck() = default;
};

//<-------EnterMapNtf------>
struct ProtoClient3_EnterGSNTF
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ENTER_GS_NTF);

    uint64_t                  mapcode; //��ͼ��ˮ��
    char                      logic[256]; //��ͼ�߼����ļ�
    unsigned short            view_x; //��ͼ��Ұ��ΧX
    unsigned short            view_y; //��ͼ��Ұ��ΧY
    unsigned short            width; //��
    unsigned short            height; //��
};


struct ProtoClient3_PlayerAppearNtf3
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_PLAYER_APPEAR_NTF3);

    uint64_t                    player_guid         = 0;            // player guid
    char                        name[128]           = {0};          // ����
    uint8_t                     gender              = 0;            // �Ա�
    uint8_t                     job                 = 0;            // ְҵ
    uint8_t                     status              = 0;            // ����״̬ 0=���� 1=����
    uint16_t                    head                = 0;            // ͷ��
    uint32_t                    level               = 0;            // �ȼ�
    uint16_t                    dst_x               = 0;            // Ŀ���x
    uint16_t                    dst_y               = 0;            // Ŀ���y
    uint8_t                     dir                 = 0;            // ����
    uint16_t                    hair                = 0;            // ͷ��
    uint16_t                    hair_color          = 0;            // ͷ����ɫ
    uint16_t                    body                = 0;            // ����
    uint16_t                    weapon              = 0;            // ����
    uint16_t                    wings               = 0;            // ���
    uint16_t                    mount               = 0;            // ����
    uint16_t                    weapon_effect       = 0;            // ������Ч
    uint16_t                    body_effect         = 0;            // ������Ч
    uint16_t                    mount_effect        = 0;            // ������Ч
    uint32_t                    hp                  = 0;            // ��ǰѪ��
    uint32_t                    max_hp              = 0;            // ���Ѫ��
    uint32_t                    mp                  = 0;            // ��ǰmp
    uint32_t                    max_mp              = 0;            // ���mp
    int                         pk                  = 0;            // pk
    uint16_t                    move_speed          = 0;            // �ƶ��ٶ�
    uint16_t                    attack_speed        = 0;            // �����ٶ�
    uint16_t                    casting_speed       = 0;            // �����ٶ�
    uint16_t                    show_fashion        = 0;            // ��ʾʱװ
    uint32_t                    model_id            = 0;            // ��ʾ���ĺ�����
    uint16_t                    title               = 0;            // �ƺ�
    uint8_t                     has_team            = 0;            // �Ƿ��ж���
    uint8_t                     stall               = 0;            // 0: δ��̯ 1: ��̯׼�� 2: ��̯��
    char                        stall_name[32]      = {0};          // ��̯����
    uint16_t                    buff_num            = 0;            // Buff����
    BUFF_INFO                   buffs[50];                          // Buff��Ϣ
    char                        family_name[32]     = {0};          // �л�����
    char                        castle_name[256]    = {0};          // �Ǳ����ƣ����Զ��������ŷָ�
    char                        family_title[32]    = {0};          // �л�ƺ�
    char                        alias[64]           = {0};          // ����
    CUSTOM_INFO                 custom;                             // �Զ�������
    uint8_t                     appear_type         = 0;            // �������� 0=������Ұ 1=���� 2=��Ծ 3=�ڱ�
    uint16_t                    amulet              = 0;            // ����
    uint16_t                    equip_num           = 0;            // ��չװ������
    EQUIP_INFO                  equips[10];                         // ��չװ����Ϣ
    uint32_t                    inner_force         = 0;            // ��ǰ�ڹ�
    uint32_t                    max_inner_force     = 0;            // ����ڹ�
    uint16_t                    reserve_num         = 0;            // �����ֶ�����
    uint32_t                    reserve_values[10]  = {0};          // �����ֶ�
    uint64_t                    master_guid         = 0;            // ����guid
    uint16_t                    title_num           = 0;            // �ƺ�����
    uint32_t                    title_id[10]        = {0};          // �ƺ�id

    ProtoClient3_PlayerAppearNtf3()
    {
        memset(buffs, 0, sizeof(buffs));
        memset(&custom, 0, sizeof(custom));
        memset(equips, 0, sizeof(equips));
    }
};


struct ProtoClient3_AttrShowNtfEx2
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ATTR_SHOW_NTF2_EX2);

    uint64_t                  actor; //actor, ������player/monster/npc's guid
    unsigned short            skill_id; //skill id
    uint64_t                  target; //target, ������player/monster/npc's guid
    unsigned char             type; //0=��ͨ 1=����
    int                       actor_hp_ref; //actor hp��ʾֵ
    int                       target_hp_ref; //Ŀ��hp��ʾֵ
    int                       target_hp; //Ŀ��hp����ֵ
    int                       target_mp; //Ŀ��mp����ֵ
    int                       actor_mp_ref; //actor mp��ʾֵ
    int                       target_mp_ref; //Ŀ��mp��ʾֵ
    unsigned char             reserve_size; //�����ֶ�����
    unsigned int                       reserve[10]; //�����ֶ�
    ProtoClient3_AttrShowNtfEx2() = default;
};

struct ProtoClient3_KickRoleNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_KICK_ROLE_NTF);

    int                       errcode; //������
    char                      errmsg[256]; //��������
    ProtoClient3_KickRoleNtf() = default;
};

struct ProtoClient3_ItemMove {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_MOVE);

    uint64_t                  item_guid; //��ƷGUID
    unsigned short            dest_site; //��Ʒ��Ŀ��λ��
    ProtoClient3_ItemMove() = default;
};

struct ProtoClient3_ItemSplit {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_SPLIT);

    uint64_t                    item_guid;      //��ƷGUID
    uint16_t                    item_amount;    //��Ʒ����
    uint16_t                    dest_site;      //��Ʒ��Ŀ��λ��
    ProtoClient3_ItemSplit() = default;
};

struct ProtoClient3_ItemArrange {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_ARRANGE);

    unsigned char             type; //0=���� 1=�ֿ� 2=�߼��ֿ�
    ProtoClient3_ItemArrange() = default;
};

struct ProtoClient3_ItemAttrNtf {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_ATTR_NTF);

    uint64_t                  item_guid; //��ƷGUID
    unsigned int              attr_name; //��Ʒ��������
    int                       attr_value; //��Ʒ����ֵ
    ProtoClient3_ItemAttrNtf() = default;
};

struct ProtoClient3_RoleAppNtf2
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_APP_NTF);

    uint64_t                    player_guid         = 0;            //player guid
    uint16_t                    hair                = 0;            //ͷ��
    uint16_t                    hair_color          = 0;            //ͷ����ɫ
    uint16_t                    body                = 0;            //����
    uint16_t                    weapon              = 0;            //����
    uint16_t                    wings               = 0;            //���
    uint16_t                    mount               = 0;            //����
    uint16_t                    weapon_effect       = 0;            //������Ч
    uint16_t                    body_effect         = 0;            //������Ч
    uint16_t                    mount_effect        = 0;            //������Ч
    uint16_t                    amulet              = 0;            //����
    uint16_t                    equip_num           = 0;            //��չװ������
    EQUIP_INFO                  equips[10];                         //��չװ����Ϣ
    uint8_t					    is_first            = 0;
};

struct ProtoClient3_SkillCDChangedNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_CD_CHANGED_NTF);

    uint16_t                    skill_id            = 0;            // ����ID
    uint32_t                    new_cd              = 0;            // ������ȴʱ��
};

struct ProtoClient3_SkillPropPermanentChangedNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_PROP_PERMANENT_CHANGED_NTF);

    uint64_t                    player_guid         = 0;
    uint16_t                    num = 0;
    SKILL_INFO                  info[100];
    void Clear()
    {
        memset(this, 0, sizeof(ProtoClient3_SkillPropPermanentChangedNtf));
        REDEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_PROP_PERMANENT_CHANGED_NTF);
    }
};

struct ProtoClient3_RunServScriptReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RUN_SERV_SCRIPT_REQ);

    uint32_t                    form_count          = 0;            //������
    char                        script_name[256];                   //�ű�����
    char                        function_name[256];                 //��������
    uint16_t                    num                 = 0;            //��������
    PARAM_INFO2                 info[100];                          //������Ϣ

    ProtoClient3_RunServScriptReq()
    {
        memset(script_name, 0, sizeof(script_name));
        memset(function_name, 0, sizeof(function_name));
        memset(info, 0, sizeof(info));
    }
};

struct ProtoClient3_RunServScriptAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RUN_SERV_SCRIPT_ACK);

    char                        script_name[256];                   //�ű�����
    char                        result[256];                        //����

    ProtoClient3_RunServScriptAck()
    {
        memset(script_name, 0, sizeof(script_name));
        memset(result, 0, sizeof(result));
    }
};

struct ProtoClient3_RunClientScript
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RUN_CLIENT_SCRIPT);

    char                        form_name[256];                     //������
    uint16_t                    size                = 0;            //�������ֽ���
    char                        form_content[65535];                 //������
    uint8_t                     comp                = 0;            //�Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��

    ProtoClient3_RunClientScript()
    {
        memset(form_name, 0, sizeof(form_name));
        memset(form_content, 0, sizeof(form_content));
    }
};

struct ProtoClient3_TradeMallListReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TRADE_MALL_LIST_REQ);
    unsigned char             page_id; //��Ʒ�ķ�ҳ
    ProtoClient3_TradeMallListReq() = default;
};

struct ProtoClient3_TradeMallListAck {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TRADE_MALL_LIST_ACK);
    unsigned char             page_id; //��Ʒ�ķ�ҳ
    unsigned char             item_count; //��Ʒ����
    MALL_ITEM_INFO            item_list[250]; //��Ʒ��Ϣ�б�
    ProtoClient3_TradeMallListAck() = default;
};

struct ProtoClient3_TradeMallBuy {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TRADE_MALL_BUY);
    unsigned int              item_index; //item_index
    unsigned short            item_amount; //��Ʒ����
    ProtoClient3_TradeMallBuy() = default;
};

struct ProtoClient3_AtkModeReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ATK_MODE_REQ);

    uint8_t                     atk_mode            = 0;            // ����ģʽ
};

struct ProtoClient3_QuestQueryCanAccept
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT);
};

struct ProtoClient3_QuestQueryCanAcceptNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT_NTF);

    uint16_t                    num                 = 0;            // ����
    uint16_t                    quests[500]         = { 0 };        // �ɽ������б�
};

struct ProtoClient3_QuestAccept
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_ACCEPT);

    uint16_t                    quest_id            = 0;            // ����ģ��id
};

struct ProtoClient3_QuestAddNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_ADD_NTF);

    uint16_t                    quest_id            = 0;            // ����ģ��id
    char                        quest_name[256]     = {0};          // ���������
    uint8_t                     quest_type          = 0;            // ���������, ��ʾ��
    uint16_t                    group_huntings_len  = 0;            // ���ּ���
    QUEST_HUNTING_INFO          group_huntings[20];                 // ��������
    uint16_t                    huntings_len        = 0;            // ��ּ���
    QUEST_HUNTING_INFO          huntings[20];                       // �������
    uint16_t                    huntlevels_len      = 0;            // ��ȼ��ּ���
    QUEST_HUNTLEVEL_INFO        huntlevels[20];                     // ��ȼ�������
    uint16_t                    group_items_len     = 0;            // ����Ʒ�ռ�
    QUEST_ITEM_INFO             group_items[20];                    // ���ռ�����
    uint16_t                    collect_items_len   = 0;            // ��Ʒ�ռ�
    QUEST_ITEM_INFO             collect_items[20];                  // �ռ�����
    uint16_t                    apply_items_len     = 0;            // ��Ʒʹ��
    QUEST_ITEM_INFO             apply_items[20];                    // �ռ�ʹ��
    uint16_t                    npcs_len            = 0;            // Npc
    QUEST_NPC_INFO              npcs[20];                           // npc����
    uint8_t                     track_enabled       = 0;            // �Ƿ���׷��
    uint32_t                    life                = 0;            // ʣ��ʱ��
    char                        progressing[256]    = {0};          // �������ʱ׷���ı�
    char                        accomplishing[256]  = {0};          // �������ʱ׷���ı�

    ProtoClient3_QuestAddNtf()
    {
        memset(group_huntings, 0, sizeof(group_huntings));
        memset(huntings, 0, sizeof(huntings));
        memset(huntlevels, 0, sizeof(huntlevels));
        memset(group_items, 0, sizeof(group_items));
        memset(collect_items, 0, sizeof(collect_items));
        memset(apply_items, 0, sizeof(apply_items));
        memset(npcs, 0, sizeof(npcs));
    }
};

struct ProtoClient3_QuestNpcTalkAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_NPC_TALK_ACK);

    uint16_t                    width               = 0;            // NPC�Ի������Ŀ��
    uint16_t                    height              = 0;            // NPC�Ի������ĸ߶�
    uint64_t                    npc_guid            = 0;            // npc��GUID
    uint16_t                    talk_len            = 0;            // NPC������ݳ���
    char                        talk[7500]          = {0};          // NPC�����ʾ������
    uint16_t                    quest_state_num     = 0;            // ����״̬��������
    QUEST_STATE_INFO            quest_states[2];                    // ����״̬����
    uint8_t                     comp                = 0;            // �Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��

    ProtoClient3_QuestNpcTalkAck()
    {
        memset(quest_states, 0, sizeof(quest_states));
    }
};

struct ProtoClient3_QuestTimeoutNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_TIMEOUT_NTF);

    uint16_t                    quest_id            = 0;            // ����ģ��id
};

struct ProtoClient3_QuestUpdateNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_UPDATE_NTF);

    uint16_t                    quest_id            = 0;            // ����ģ��id
    int32_t                     data_type           = 0;            // ��������, �ο�quest_track_state
    int32_t                     id                  = 0;
    int32_t                     value               = 0;
};

struct ProtoClient3_QuestDrop
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_DROP);

    uint16_t                    quest_id            = 0;
};

struct ProtoClient3_QuestDropNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_DROP_NTF);

    uint16_t                    quest_id            = 0;
};

struct ProtoClient3_QuestAccomplish
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_ACCOMPLISH);

    uint16_t                    quest_id            = 0;            // ����ģ��id
    uint16_t                    select_index        = 0;            // ���ѡ��������
};

struct ProtoClient3_QuestStateNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_STATE_NTF);

    uint16_t                    quest_id            = 0;
    uint8_t                     state               = 0;            // 0�����У�1��׼��������2��������3��������4�����
};

struct ProtoClient3_QuestNpcStateNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUEST_NPC_STATE_NTF);

    uint16_t                    npc_id              = 0;
    uint8_t                     state               = 0;            // 0��null��1������ɽ���2������ɽӣ�3�������ѽӲ��ɽ�
};

struct ProtoClient3_RoleAttrExtRefNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_ATTR_EXT_REF_NTF);

    uint16_t                    attr_name           = 0;            // ��������
    int64_t                     attr_value          = 0;            // ���Ըı����ֵ
};

struct ProtoClient3_LevelUpNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_LEVEL_UP_NTF);

    uint64_t                    player_guid         = 0;
    uint32_t                    level               = 0;
};

struct ProtoClient3_PlayerQuery
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_PLAYER_QUERY);

    char                        player_name[128]    = {0};          // �������
};

struct ProtoClient3_PlayerQueryNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_PLAYER_QUERY_NTF);

    uint64_t                    player_guid         = 0;
    char                        name[128]           = {0};          //�������
    uint8_t                     gender              = 0;            //�Ա�
    uint8_t                     job                 = 0;            //ְҵ
    uint32_t                    level               = 0;            //�ȼ�
    char                        family_name[32]     = {0};          //�л�����
    char                        family_title[32]    = {0};          //�л�ƺ�
    char                        alias[64]           = {0};          //����
    uint16_t                    item_num            = 0;            //��Ʒ����
    ITEM_INFO                   item_info[45];                      //��Ʒ��Ϣ
    unsigned char               isFinalPack         = 0;

    ProtoClient3_PlayerQueryNtf()
    {
        memset(item_info, 0, sizeof(item_info));
    }
};

struct ProtoClient3_TitleAddAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_ADD_ACK);
    TITLE_INFO info;
};

struct ProtoClient3_TitleDel
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_REMOVE);
    uint32_t id = 0;
};

struct ProtoClient3_TitleDelAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLINET3_TITLE_REMOVE_ACK);
    uint32_t id;
    unsigned char err = 0;
};

struct ProtoClient3_TitleWear
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_APPLY);
    uint32_t id = 0;
};

struct ProtoClient3_TitleUnWear
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_UNAPPLY);
    uint32_t id = 0;

};

struct ProtoClient3_TitleWearNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_APPLY_NTF);
    uint32_t id = 0;
    uint64_t guid = 0;
};

struct ProtoClient3_TitleUnWearNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_UNAPPLY_NTF);
    uint32_t id = 0;
    uint64_t guid = 0;
};

struct ProtoClient3_TitleList
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_TITLE_LIST);
    uint16_t   num = 0;
    TITLE_INFO info[100];
};

struct ProtoClient3_PlayerFamilyChangeNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_PLAYER_FAMILY_CHANGE_NTF);

    uint64_t                    player_guid         = 0;
    char                        family_name[32]     = {0};          //�л�����
    char                        castle_name[256]    = {0};          //�Ǳ����ƣ����Զ��������ŷָ�
    uint8_t                     title               = 0;
};

struct ProtoClient3_MissNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MISS_NTF);

    uint64_t                    actor               = 0;            //actor, ������player/monster/npc's guid
    uint64_t                    target              = 0;            //target, ������player/monster/npc's guid
    uint16_t                    skill_id            = 0;            //����id
    uint8_t                     type                = 0;            //1=���� 2=����
};


////////////////////////////
struct ProtoClient3_DelegateSellCmd
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_SELL_CMD);
    uint64_t                item_guid = 0;  //��ƷGUID
    uint32_t                item_value = 0; //��Ʒ����
    uint32_t                item_unit = 1;  //��Ʒ��λ����
    uint8_t                 value_type = 0; //�۸����ͣ�0����ң�1��Ԫ��
};

struct ProtoClient3_DelegateBuyCmd {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_BUY_CMD);
    uint16_t                item_id = 0;    //��Ʒģ��ID
    uint32_t                item_count = 0; //��Ʒ����
    uint32_t                item_value = 0; //��Ʒ����
    uint32_t                item_unit = 1;  //��Ʒ��λ����
    uint8_t                 value_type = 0; //�۸����ͣ�0����ң�1��Ԫ��
};

struct ProtoClient3_DelegateSellListReq {
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_SELL_LIST_REQ);
    uint32_t                start = 0;  //��ʼ���к�
    uint32_t                count = 0;  //��������
    uint16_t                type = 0;   //����
    uint16_t                subtype = 0; //�ӷ���
    char                    item_name[32] = { 0 }; //��Ʒ���ƹ���
    uint8_t                 is_reverse = 0; //�Ƿ���
};

struct ProtoClient3_DelegateSellListAck 
{
    enum DSLA_MaxSize
    {
        Info_Size = 20
    };
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_SELL_LIST_ACK);
    uint16_t                type = 0;       //����
    uint16_t                subtype = 0;    //�ӷ���
    uint32_t                total = 0;      //����
    uint32_t                start = 0;      //��ʼ���к�
    uint32_t                count = 0;      //��������
    DELEGATE_SELL_ITEM      items[Info_Size];      //��Ʒ�б�
};

struct ProtoClient3_DelegateBuyListReq 
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_BUY_LIST_REQ);
    uint32_t                start = 0;      //��ʼ���к�
    uint32_t                count = 0;      //��������
    uint16_t                type = 0;       //����
    uint16_t                subtype = 0;    //�ӷ���
    char                    item_name[32] = {0}; //��Ʒ���ƹ���
    uint8_t                 is_reverse;     //�Ƿ���
};

struct ProtoClient3_DelegateBuyListAck2
{
    enum DBLA_MaxSize
    {
        Info_Size = 20
    };
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK2);
    uint16_t                type = 0;       //����
    uint16_t                subtype = 0;    //�ӷ���
    uint32_t                total = 0;      //����
    uint32_t                start = 0;      //��ʼ���к�
    uint32_t                count = 0;      //��������
    DELEGATE_BUY_ITEM2      items[Info_Size];      //��Ʒ�б�
};

struct ProtoClient3_MarketBuyCmd
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MARKET_BUY_CMD);
    uint64_t            trade_id = 0;       //���׺�
    uint32_t            count = 0;          //��������
};

struct ProtoClient3_MarketSellCmd
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_MARKET_SELL_CMD);
    uint64_t            trade_id = 0;   //���׺�
    uint64_t            item_guid = 0;  //��Ʒguid
};

struct ProtoClient3_DelegateCancel
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_CANCEL);
    uint64_t        trade_id = 0; //���׺�
};

struct ProtoClient3_RecordsMineReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RECORDS_MIN_REQ);
    uint64_t                  role_id = 0;
    uint16_t                  type = 0;
};

struct ProtoClient3_DelegateMineReq 
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_MINE_REQ);
    uint64_t                  role_id = 0;
};


struct ProtoClient3_RecordsMineAck
{
    enum RMA_MaxSize
    {
        Info_Size = 10
    };
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RECORDS_MINE_ACK);
    uint64_t                    role_id = 0;
    uint16_t                    type = 0;
    uint32_t                    count = 0;
    TRADE_RECORD                trade_record[Info_Size];
    uint8_t                     last_pack = 0;
};

struct ProtoClient3_DelegateMineAck2 
{
    enum DMA_MaxSize
    {
        Info_Size = 5
    };
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_DELEGATE_MINE_ACK2);
    uint64_t                    role_id = 0;
    uint32_t                    count_buy = 0; //��������
    uint32_t                    count_sell = 0; //��������
    DELEGATE_BUY_ITEM2          buy_items[Info_Size];
    DELEGATE_SELL_ITEM          sell_items[Info_Size];
    uint8_t                     last_pack = 0;
};

struct ProtoClient3_QueryEx
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_QUERY_EX);
    uint64_t                  role_id;
    ProtoClient3_QueryEx() = default;
};

struct ProtoClient3_SkillStatusNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SKILL_STATUS_NTF);

    uint16_t        id          = 0;    // ����id
    uint8_t         active      = 0;    // 0=������ 1=����
};

struct ProtoClient3_ShabakOwnerNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SHABAK_OWNER_NTF);

    uint64_t    role_guid           = 0;
};

struct ProtoClient3_ShabakLossNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SHABAK_LOSS_NTF);

    uint64_t    role_guid           = 0;
};

struct ProtoClient3_ShabakEngageNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SHABAK_ENGAGE_NTF);

    char        own_family[32]          = {0};          // �����л�
    char        attack_families[4096]   = {0};          // �����л�
};

struct ProtoClient3_ShabakEndNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SHABAK_END_NTF);
};

struct ProtoClient3_RunningFamilyWarNtf
{
    enum MaxSize {
        MAX_SIZE = 100,
    };
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_FAMILY_WAR_NTF);

    uint8_t                   idx = 0;
    uint8_t                   total = 0;
    uint16_t                   num;                      // �����е��л�ս����
    FAMILY_WAR_INFO           families[MAX_SIZE];       // �����е��л�ս��Ϣ
};

struct ProtoClient3_JumpMapReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_JUMP_MAP_REQ);

    uint16_t                    dst_x               = 0;            // Ŀ���x
    uint16_t                    dst_y               = 0;            // Ŀ���y
    uint8_t                     type                = 0;            // �� jump_map_type
};

struct ProtoClient3_ItemPickupNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_PICKUP_NTF);

    uint64_t                    item_guid           = 0;            // ��Ʒid
    uint64_t                    role_guid           = 0;            // ��˭����
};

struct ProtoClient3_AutoPickupSettingsNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_AUTO_PICKUP_SETTINGS_NTF);

    AUTO_PICKUP                 auto_pickup;
};

struct ProtoClient3_MonsterPursureAttackingNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLINET3_MONSTER_PURSURE_STATUS_CHANGE_NTF);
    uint64_t guid = 0;
    uint16_t status = 0;
};

struct ProtoClient3_StartDigReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_START_DIG_REQ);

    uint64_t                    treasure_guid       = 0;            // ����GUID
};

struct ProtoClient3_StartDigAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_START_DIG_ACK);

    uint64_t                    treasure_guid       = 0;            // ����GUID
    uint8_t                     code                = 0;            // 0��������1�����ﲻ���ڣ�2�������ڱ���Χ
    uint32_t                    dig_time            = 0;            // �ɼ�ʱ��ms
};

struct ProtoClient3_StopDigNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_STOP_DIG_NTF);

    uint64_t                    treasure_guid       = 0;            // ����GUID
    uint8_t                     reason              = 0;            // 0������ʱ������1����ɫ�ƶ���2����ɫ������3��������������
};

struct ProtoClient3_RangePickup
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_RANGE_PICKUP);

    uint8_t                     posnum              = 0;
    Point                       pos[AUTO_PICKUP_MAXPOS];
};

struct ProtoClient3_RoleAppearNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ROLE_APPEAR_NTF);

    uint64_t                    role_guid           = 0;            // ��ɫGUID
    uint8_t                     appear_type         = 0;            // 0=������Ұ 1=���� 2=��Ծ 3=�ڱ�
};

struct ProtoClient3_SyncClientBaseSetting
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SYNC_CLIENT_BASE_SETTING);
 
    uint16_t                    type = 0;
    int32_t                     value = 0;
};

struct ProtoClient3_VerifyBuyItemInfoReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_REQ);

    uint32_t                    item_id             = 0;            // �������ƷID
    uint8_t                     item_count          = 0;            // �������Ʒ����
    uint32_t                    item_price          = 0;            // �������Ʒ����(��)
};

struct ProtoClient3_VerifyBuyItemInfoAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_ACK);

    uint32_t                    item_id             = 0;            // �������ƷID
    uint8_t                     status              = 0;            // ��Ʒ�ܷ���
};

struct ProtoClient3_PlayerSetNameNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_PLAYER_SET_NAME_NTF);

    uint64_t guid = 0;
    char     name[32];
    char     orgName[32];
    ProtoClient3_PlayerSetNameNtf() {
        memset(name, 0, _countof(name));
    }
};

struct ProtoClient3_ItemRefreshReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_ITEM_REFRESH_REQ);
};

struct ProtoClient3_SetAutoModeReq
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SET_AUTO_MODE_REQ);

    uint64_t                    role_guid           = 0;
    uint8_t                     enable              = 0;
};

struct ProtoClient3_SetAutoModeAck
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SET_AUTO_MODE_ACK);

    uint64_t                    role_guid           = 0;
    uint8_t                     enable              = 0;
};

struct ProtoClient3_SceneItemUpdateNtf
{
    DEF_PROTO_HEADER_CLIENT3(PROTO_CLIENT3_SCENE_ITEM_UPDATE_NTF);

    uint64_t                    item_guid           = 0;
};

class ProtoClient3
{
public:
    ProtoClient3();
    ~ProtoClient3();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_CLIENT3; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_CLIENT3_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_CLIENT3_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_CLIENT3_MAX];
};
