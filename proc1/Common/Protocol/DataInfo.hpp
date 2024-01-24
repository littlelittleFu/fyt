#pragma once

#include "netdata.h"
#include <vector>
#include <set>
#include <memory>
#include <list>
#include <map>
#include <unordered_map>

//===============����������Э���ļ�===============
//===============�궨�忪ʼ===============
#define MAX_FRIEND_NUM                 50 //����������
#define MAX_ALLY_NUM                   20 //�л����������
#define MAX_ENEMY_NUM                  20 //�л����ж���
#define MAX_TITLE_NUM                  20 //�л��������
#define MAX_CUSTITLE_NUM               16 //�л��Զ�������
#define MAX_MAIL_REMAIN_DATE           2592000//�ʼ�����ʱ��
#define	MAX_ADDITION_NUM               5  //������������
#define MAX_MAIL_CURRENCY_TYPE_NUM     5  //�ʼ���������
#define MAX_AUCTION_HOUSE_REMAIN_DATE           2592000//���������ݱ���ʱ��

//===============�궨�����===============

//===============���ݶ��忪ʼ===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct KEY_VALUE_PAIR{
	char                      key[32]; //key
	char                      value[256]; //value
};

struct PARAM_INFO{
	unsigned char             type; //�������� 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64 9=�ַ���
	char                      value[1024]; //����ֵ
};

struct PARAM_INFO2{
	unsigned char             type; //�������� 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64 9=�ַ���
	int                       size; //���������ݴ�С
	char                      value[1024]; //����ֵ
};

struct IntData{
	char                      name[32]; //������
	unsigned char             type; //�������� 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64
	uint64_t                  value; //����ֵ
};

struct StrData{
	char                      name[32]; //������
	char                      value[256]; //����ֵ
};

struct BlobData{
	char                      name[32]; //������
	int                       size; //���������ݴ�С
	unsigned char             buf[262144]; //����������
};

struct ITEM_CFG_VAR
{
	uint32_t                  color = 0;
	uint64_t                  icon = 0;
	uint32_t                  quality = 0;
	uint32_t                  subtype = 0;
	ITEM_CFG_VAR() = default;
};

struct ROLE_DATA_INFO{
	int                       intdatanum; //��ɫ�������ݸ���
	IntData                   roleintdata[128]; //��ɫ��������
	int                       strdatanum; //�ַ������ݸ���
	StrData                   rolestrdata[64]; //��ɫ�ַ�������
	int                       blobdatanum; //��ɫ���������ݸ���
	BlobData                  roleblobdata[16]; //��ɫ����������
	BlobData                  gamedata; //��ʱ�������Ҷ���������
	int                       billinyuanbao; //�ۼƳ�ֵԪ��
	int                       billoutyuanbao; //�ۼ�����Ԫ��
	int                       gameinyuanbao; //�ۼƽ���Ԫ�����󶨣�
	int                       gameoutyuanbao; //�ۼ����ѵİ�Ԫ��
};

struct ITEM_DB_INFO
{
	uint64_t                  guid              = 0; //guid
	unsigned short            id                = 0; //ģ��Id
    char                      name[32]          = {0}; //����
	uint64_t                  role              = 0; //ӵ����GUID
	unsigned short            site              = 0; //��ǰ���ڵ�λ��
	unsigned short            amount            = 0; //��ǰ�Ķѵ�����
	int                       durability        = 0; //װ���;�
	int                       max_durability    = 0; //װ���;�
	unsigned short            use_count         = 0; //��ǰ��ʹ�ô���
	unsigned char             is_bound          = 0; //�Ƿ��Ѱ�
	unsigned int              life              = 0; //����ʱ����ʼ����ʱ��
	unsigned char             ext_len           = 0; //��չ���ݳ���
    unsigned char             ext_data[128]     = {0}; //��չ����
	ITEM_CFG_VAR              item_cfg_var;           //�Զ������ñ��ֶ�
};
struct CUST_VAR 
{
	uint64_t                    belong = 0;    // ����ID
	std::string                 name = "";
	std::string                 value = "";
	uint8_t                     type = 0;    // ����
	uint64_t                    expire = 0;    // ʧЧʱ��
	uint8_t						mergeType = 0;
};

struct DYN_ATTR {
	uint16_t                    index = 0;
	uint16_t                    attr = 0;
	int32_t                     value = 0;

	DYN_ATTR() = default;
	DYN_ATTR(uint16_t i, uint16_t a, int32_t v) : index(i), attr(a), value(v) {}

    bool operator == (const DYN_ATTR &other) {
        return index == other.index &&
               attr == other.attr &&
               value == other.value;
    }

    bool operator != (const DYN_ATTR &other) {
        return !operator == (other);
    }
};

using DYN_ATTRS = std::list<DYN_ATTR>;

struct ITEM_DYN_ATTRS {
	uint64_t                    guid = 0;
	DYN_ATTRS                   dyn_attrs;

	ITEM_DYN_ATTRS() = default;
	ITEM_DYN_ATTRS(uint64_t guid, const DYN_ATTRS& attrs) : guid(guid), dyn_attrs(attrs) {}
    ITEM_DYN_ATTRS(uint64_t guid, DYN_ATTRS &&attrs) : guid(guid), dyn_attrs(std::move(attrs)) {}
};

using CUST_VAR_MAP = std::map<std::string, CUST_VAR>;
using CUST_VAR_LIST = std::list<CUST_VAR>;

using CUST_VAR_SP = std::shared_ptr<CUST_VAR>;
using CUST_VAR_SP_MAP = std::map<std::string, CUST_VAR_SP>;
using CUST_VAR_SP_LIST = std::list<CUST_VAR_SP>;
using GUID_TO_CUST_VAR_MAP = std::unordered_map<uint64_t, CUST_VAR_SP_MAP>;
using ITEM_DYN_ATTRS_LIST = std::list<ITEM_DYN_ATTRS>;
using ROLE_DYN_ATTRS = ITEM_DYN_ATTRS;
using ROLE_DYN_ATTRS_LIST = ITEM_DYN_ATTRS_LIST;

struct CONSTANT_CFG
{
	std::string name = "";
	std::string value = "";
};
using CONSTANT_CFG_MAP = std::unordered_map<std::string, CONSTANT_CFG>;

struct CUSTOM_INFO {
	CUSTOM_INFO& operator<<(uint16_t);
	CUSTOM_INFO& operator<<(const std::string&);
	void operator<<(CONSTANT_CFG_MAP& constantCfgMap);
	void operator<<(CUST_VAR_MAP& mCustVars);
	void operator<<(CUST_VAR_SP_MAP& mCustVars);
	void operator<<(CUST_VAR_LIST& mCustVars);
	void operator<<(CUST_VAR_SP_LIST& mCustVars);
	void operator<<(DYN_ATTRS& mDynAttrs);
	void operator>>(CUST_VAR_LIST& mCustVars);
	void operator>>(DYN_ATTRS& mDynAttrs);
	void operator>>(CONSTANT_CFG_MAP& constantCfgMap);
	CUSTOM_INFO& operator>>(uint16_t&);
	CUSTOM_INFO& operator>>(std::string&);
	unsigned short            num = 0; //���泤��
	unsigned short			  idx = 0;
	char					  buf[65536] = { 0 }; //����
};

struct ITEM_INFO
{
	ITEM_DB_INFO               base_info;
	CUSTOM_INFO               custom;
};

struct CHAT_MSG{
	char                      role_name[256]; //��ɫ����
	char                      message[65535]; //��Ϣ����
};

struct SKILL_INFO{
	uint16_t				  id = 0; //ģ��Id
	uint8_t					  active = 1; //�Ƿ��ѿ���(���ؼ�����Ч)
	uint32_t                  proficiency = 0; //������
	char					  cfg[512] = { 0 };
};

struct BUFF_INFO{
	unsigned short            id    = 0; //ģ��Id
	unsigned short            stack = 0; //�ѵ�����
	unsigned int              life  = 0; //���ʱ��
	uint64_t                  host  = 0; //����
};

struct BUFF_INFO_DB {
    uint64_t                  index = 0;
    unsigned short            buffid = 0;
    unsigned int              timeleft = 0;
    uint64_t                  timestamp = 0;
    uint64_t                  actor_id = 0;
	char                      actor_name[32] = { 0 };
    unsigned char             actor_job = 0;
    unsigned int              actor_level = 0;
    unsigned short            actor_skill = 0;
	uint16_t				  stack = 1;
	char                      attr[256] = { 0 };
};

struct SHOP_ITEM_INFO{
	unsigned char             index; //��Ʒ�ڵ����еĸ���λ��
	unsigned short            id; //��Ʒ��ģ��id
	unsigned short            num; //��Ʒʣ������ 0xffff=��Ʒ����������
	unsigned int              value; //��Ʒ�ļ۸�
};

struct TEAM_MEMBER{
	uint64_t                  guid; //guid
	char                      name[32]; //��ɫ����
	unsigned short            head; //ͷ��
	unsigned char             is_online; //�Ƿ�����
	unsigned int              level; //�ȼ�
	unsigned char             job; //ְҵ
	unsigned char             gender; //�Ա�
	uint64_t                  map_code; //��ͼguid
	char                      map_name[32]; //��ͼ����
	unsigned short            x; //x
	unsigned short            y; //y
};

struct TEAM_INFO{
	uint64_t                  guid; //���� guid
	uint64_t                  leader_guid; //�ӳ� guid
	char                      leader_name[32]; //�ӳ� name
	unsigned char             permission; //1=������������Ȩ�� 0=�ر�
	int                       member_num; //��Ա����
	TEAM_MEMBER               members[100]; //��Ա��Ϣ
};

struct FRIEND_INFO{
	uint64_t                  guid; //���� guid
	char                      name[32]; //��������
	unsigned char             is_online; //�Ƿ�����
	short                     friendship; //���ܶ�
};

struct FRIEND_DETAIL{
	uint64_t                  guid; //���� guid
	char                      name[32]; //��������
	char                      family[32]; //���ѹ���
	char                      title[32]; //���ѷ��
	char                      position[32]; //���ڵ�ͼ
	unsigned short            head; //ͷ��
	unsigned char             job; //ְҵ
	unsigned char             gender; //�Ա�
	unsigned int              level; //�ȼ�
	short                     friendship; //���ܶ�
	unsigned char             is_in_team; //�Ƿ����
	unsigned char             members_num; //��������
	unsigned char             is_online; //�Ƿ�����
};

struct FRIEND_LIST{
	uint64_t                  guid; //��ҵ�guid
	int                       friend_num; //��������
	FRIEND_INFO               friends[MAX_FRIEND_NUM]; //������Ϣ
};

struct FRIEND_RELATION{
	uint64_t                  role1_guid; //��ɫ1id
	char                      role1_name[256]; //��ɫ1����
	uint64_t                  role2_guid; //��ɫ2id
	char                      role2_name[256]; //��ɫ2����
	short                     friendship; //���ܶȣ�0��û��˫����ѹ�ϵ��-1��������
	unsigned char             type; //���ͣ�0��˫����ѣ�1����ɫ1���ѣ�2����ɫ2����
};

struct SERVANT_INFO{
	uint64_t                  servant_guid; //��ӵ�guid
	unsigned short            monster_id; //����ģ��id
	unsigned char             level; //��ӵȼ�
	unsigned char             max_level; //�����ӵȼ�
	unsigned short            kill_count; //���ɱ����
	int                       hp; //Ѫ��
	unsigned int              gen_tick; //����ʱ��
	unsigned char             type; //������� ��ʦ�ٻ�=1 ��ʿ�ٻ�=2
	int                       buff_data_len; //buff���ݳ���
	char                      buff_data[1024]; //buff����
};

struct QUICK_BAR_INFO{
	unsigned char             type; //0=null 1=item 2=skill
	unsigned char             slot; //��λ
	unsigned short            id; //ģ��id
	uint64_t                  guid; //��Ʒguid
};

struct QUICK_BAR_LIST_INFO {
	uint64_t                  role_id;
	QUICK_BAR_INFO            quick;
};

struct DGN_BIND_INFO
{
	enum DBI_OPTTYPE
	{
		None = 0,
		Insert = 1,
		Update = 2,
		Delete = 3
	};
	enum DBI_KEYNAME_LEN
	{
		MAX_LEN = 64
	};
	DGN_BIND_INFO()
	{
		roleId = 0;
		memset(dgnKeyName, 0, sizeof(dgnKeyName));
		dgnId = 0;
		optType = DBI_OPTTYPE::Update;
	}
	void operator=(const DGN_BIND_INFO& a)
	{
		roleId = a.roleId;
		memcpy_s(dgnKeyName,sizeof(dgnKeyName),a.dgnKeyName, sizeof(a.dgnKeyName));
		dgnId = a.dgnId;
		optType = a.optType;
	}
	uint64_t                    roleId;
	char						dgnKeyName[MAX_LEN];
	uint64_t					dgnId;
	uint16_t					optType;		//1 ���� 2 ����
};

struct MAP_REGION_INFO{
	unsigned char             rg_type; //�������� 0=��ȫ�� 1=��̯�� 2=������ 3=������
	unsigned short            min_x; //��Сx����
	unsigned short            max_x; //���x����
	unsigned short            min_y; //��Сy����
	unsigned short            max_y; //���y����
};

struct FAMILY_TITLE{
	unsigned char             id; //���ID
	char                      title[32]; //�������
};

struct FAMILY_DETAIL{
	uint64_t                  guid; //�л�id
	char                      name[32]; //�л�����
	unsigned short            notice_len; //���泤��
	char                      notice[1280]; //�лṫ��
	unsigned short            titles_num; //��Ÿ���
	FAMILY_TITLE              titles[MAX_TITLE_NUM]; //�л��Զ����ţ����MAX_TITLE_NUM��
	unsigned short            msg_len; //�л���Ϣ����
	char                      sysmsgs[12800]; //�л���Ϣ��ÿ����Ϣ��'\n'����
	unsigned short            ally_count; //�л�����
	uint64_t                  allys[MAX_ALLY_NUM]; //�����л�
	unsigned short            enemy_count; //�л�����
	uint64_t                  enemys[MAX_ENEMY_NUM]; //�ж��л�
	unsigned int              create_time; //����ʱ��
};

struct FAMILY_INFO_GS{
	uint64_t                  guid; //�л�id
	char                      name[32]; //�л�����
	unsigned short            titles_num; //��Ÿ���
	FAMILY_TITLE              titles[MAX_TITLE_NUM]; //�л��Զ����ţ����MAX_TITLE_NUM��
	unsigned short            ally_count; //�л�����
	uint64_t                  allys[MAX_ALLY_NUM]; //�����л�
	unsigned short            enemy_count; //�л�����
	uint64_t                  enemys[MAX_ENEMY_NUM]; //�ж��л�
};

struct FAMILY_INFO{
	uint64_t                  guid; //�л�id
	char                      name[32]; //�л�����
};

struct MEMBER_INFO{
	uint64_t                  player_guid; //���guid
	char                      player_name[32]; //�������
	unsigned int              level; //�ȼ�
	unsigned char             job; //ְҵ
	uint64_t                  family_guid; //�л�ID
	unsigned char             title_id; //���ID, 0���л��Ա��1���᳤��2�����᳤��3����Ӣ��4����Ϊ�Զ���
	uint64_t                  join_time; //���ʱ��
	uint64_t                  login_time; //���һ������ʱ��
	unsigned char             is_online; //�Ƿ�����
    unsigned int              cur_ctrb; //��ǰ���׶�
    unsigned int              totle_ctrb; //�ۼƹ��׶�
    unsigned int              kills; //ɱ������
    unsigned int              combat_capability;//ս����
    unsigned int              reserved1;//Ԥ��λ1
    unsigned int              reserved2;//Ԥ��λ2
};

struct MEMBER_INFO_GS{
	uint64_t                  player_guid; //���guid
	uint64_t                  family_guid; //�л�ID
	unsigned char             title_id; //���ID, 0���л��Ա��1���᳤��2�����᳤��3����Ӣ��4����Ϊ�Զ���
	unsigned int              cur_ctrb; //��ǰ���׶�
	unsigned int              totle_ctrb; //�ۼƹ��׶�
	unsigned int              join_time; //���ʱ��
};

struct APPLICANTS_INFO{
	uint64_t                  player_guid; //���guid
	char                      player_name[32]; //�������
	unsigned int              level; //�ȼ�
	unsigned char             job; //ְҵ
};

struct ROLE_FORBIDTALK_INFO{
	char                      role_name[32]; //��������ҵ�����
	char                      end_forbid_time[256]; //���Ե���ʱ��
	char                      describe[256]; //����ԭ��
	unsigned char             type; //����, 1 ���ֽ��� 2 �������� 3 ���ֺ���������
};

struct FAMILY_APPLY_INFO{
	uint64_t                  guid; //�л�id
	char                      name[32]; //�л�����
	char                      leader_name[32]; //�᳤��
	unsigned int              members_num; //�л�����
	char                      hold_place[32]; //ռ�гǱ��ص�
	unsigned char             is_applied; //�Ƿ������
    char                      family_manifesto[100];//--�л�����
    uint64_t                  family_create_time;//��ᴴ��ʱ��
    unsigned int              family_level; //�л�ȼ�
    unsigned int              reserved1;//Ԥ��λ1
    unsigned int              reserved2;//Ԥ��λ2
};

struct FAMILY_WAR_INFO{
	uint64_t				  guid = 0;	//guid
	char                      name[32]; //�л�����
};

struct CASTLE_INFO{
	char                      name[32]; //�Ǳ�����
	unsigned char             is_start; //����ս�Ƿ�ʼ
	unsigned int              start_time; //����ս��ʼʱ��
	unsigned int              duration; //����ս����ʱ��
	char                      own_family[32]; //�����л�
	char                      attack_families[4096]; //�����л�
	char                      dst_map[32]; //������ͼ
	char                      basilica_map[32]; //�ʹ���ͼ
	CUSTOM_INFO               custom; //�Զ�������
	unsigned char             state; //system use only
};

using GUILD_ID_LIST = std::vector<uint64_t>;
using GUILD_ID_SET = std::set<uint64_t>;

struct GUILD_INFO {
    uint64_t                    id              = 0;        // �л�ID
    std::string                 name;                       // �л���
    uint16_t                    level           = 0;        // �л�ȼ�
    std::string                 manifesto;                  // ����
    std::string                 notice;                     // ����
    uint64_t                    ctime           = 0;        // ����ʱ��
    uint64_t                    creator_id      = 0;        // ������ID
    std::string                 creator_name;               // �������ǳ�
    uint64_t                    chairman_id     = 0;        // �᳤ID
    std::string                 chairman_name;              // �᳤�ǳ�
	uint32_t                    autojoin_level = 0;			// ��ɫ�ﵽ�ȼ������Զ�����
    GUILD_ID_LIST               allies;                     // �����л�
    GUILD_ID_LIST               enemies;                    // �ж��л�
};

using SPGUILD = std::shared_ptr<GUILD_INFO>;
using GUILD_MAP = std::map<uint64_t, SPGUILD>;

struct GUILD_MEMBER {
    uint64_t                    player_id       = 0;        // ���ID
    std::string                 player_name;                // ����ǳ�
    uint8_t                     job             = 0;        // ְҵ
    uint32_t                    level           = 0;        // �ȼ�
    uint64_t                    guild_id        = 0;        // �л�ID
    uint8_t                     title           = 0;        // ���ID, 0���л��Ա��1���᳤��2�����᳤��3����Ӣ��4����Ϊ�Զ���
    uint8_t                     new_title       = 0;        // �·��
    uint64_t                    join_time       = 0;        // ���ʱ��
    uint64_t                    login_time      = 0;        // ���һ������ʱ��
    uint32_t                    cur_contrib     = 0;        // ��ǰ���׶�
    uint32_t                    total_contrib   = 0;        // �ۼƹ��׶�
    uint32_t                    kills           = 0;        // ɱ������
    uint32_t                    combat_cap      = 0;        // ս����
    uint8_t                     status          = 0;        // ״̬, 0 - ����, 1 - ����
    std::string                 kicked_by;                  // ��������
    bool                        online          = false;    // �Ƿ�����
};

using SPGUILD_MEMBER = std::shared_ptr<GUILD_MEMBER>;
using GUILD_MEMBER_LIST = std::list<SPGUILD_MEMBER>;
using GUILD_MEMBER_MAP = std::unordered_map<uint64_t, SPGUILD_MEMBER>;

struct GUILD_APPLY_INFO {
    uint64_t                    player_id   = 0;    // ���ID
    std::string                 player_name;        // �������
    uint32_t                    level       = 0;    // �ȼ�
    uint8_t                     job         = 0;    // ְҵ
    uint64_t                    guild_id    = 0;    // �����л�ID
    uint64_t                    apply_time  = 0;    // ����ʱ��
    uint64_t                    login_time  = 0;    // �ϴε�¼ʱ��
    uint8_t                     status      = 0;    // ����״̬
    std::string                 handled_by;         // ������
};

using SPGUILD_APPLICANT = std::shared_ptr<GUILD_APPLY_INFO>;
using GUILD_APPLICANT_LIST = std::list<SPGUILD_APPLICANT>;

struct GUILD_DATA
{
    GUILD_MEMBER_LIST           members;
    GUILD_APPLICANT_LIST        applicants;
	GUILD_ID_SET				war;
};

using GUILD_DATA_MAP = std::map<uint64_t, GUILD_DATA>;

struct MALL_ITEM_INFO{
	unsigned int              item_index = 0; //��ƷID
	unsigned short            item_id = 0; //��Ʒ��ģ��id
	unsigned char             is_hot = 0; //�Ƿ�����
	unsigned short            num = 0; //��Ʒʣ������ 0xffff=��Ʒ����������
	unsigned char             value_type = 0; //�۸����ͣ�0:Ԫ����1:��Ԫ��2:���֣�3:��ң�4:���
	unsigned int              price = 0; //ԭ��
	unsigned int              discount = 0; //�ۿۼ�
	unsigned short            limits_type = 0;//�޹�����
	unsigned short            limits_time = 0;//�޹�ʱ��
};

struct MALL_ITEM_DETAIL{
	unsigned int              item_index = 0; //��ƷID
	unsigned short            item_id = 0; //��Ʒ��ģ��id
	unsigned short            image_desc = 0; //��ƷͼƬ����
	char                      text_desc[256]; //��Ʒ��������
	MALL_ITEM_DETAIL() 
	{
		memset(text_desc, 0, _countof(text_desc));
	}
};

struct MALL_ITEM_INFO_BASE
{
	uint64_t playerguid = 0;
	uint32_t item_idx = 0;
	uint32_t num = 0;
};

struct TOPLIST_INFO{
	char                      player_name[32]; //�������
	unsigned int              level; //�ȼ�
	unsigned char             job; //ְҵ
	unsigned char             gender; //�Ա�
	char                      ext1[32]; //��չ1
	char                      ext2[32]; //��չ2
	char                      ext3[32]; //��չ3
};

struct QUEST_HUNTING_INFO{
	unsigned short            id; //����ģ��ID
	unsigned short            count; //ɱ�ּ�������
	unsigned short            required; //ɱ����������
};

struct QUEST_HUNTLEVEL_INFO{
    unsigned short            id; //����ģ��ID
	unsigned short            min_num; //������Ч��С�ȼ�
	unsigned short            max_num; //ɱ����Ч���ȼ�
	unsigned short            count; //ɱ�ּ�������
	unsigned short            required; //ɱ����������
};

struct QUEST_ITEM_INFO{
	unsigned short            id; //��Ʒģ��ID
	unsigned short            count; //��Ʒ��������
	unsigned short            required; //��Ʒ��������
};

struct QUEST_NPC_INFO{
	unsigned short            id; //Npcģ��ID
	unsigned short            count; //Npc��������
};

struct MAIL_HEADER_INFO{
	uint64_t                  mail_id; //�ʼ�ID
	char                      title[64];
	unsigned int              send_time; //����ʱ��
	unsigned int              left_time; //ʣ��ʱ��
	char                      sender[32]; //������
	unsigned int              status; //�ʼ�״̬
	unsigned char             type; //�ʼ����� 1������ʼ���0��ϵͳ�ʼ�
};

struct MAIL_BODY_INFO{
	char                      text[400]; //�ʼ�����
	int                       gold; //�������
	int                       yuanbao; //Ԫ������
	unsigned char             count; //��Ʒ����
	ITEM_INFO                 items[5]; //��ƷID�б�
};

struct MAIL_BODY_INFO2{
	char                      text[400]; //�ʼ�����
	int64_t                   gold; //�������
	int64_t                   yuanbao; //Ԫ������
	int64_t                   integral; //��������
	int64_t                   bind_gold;
	int64_t                   bind_yunabao;
	unsigned char             count; //��Ʒ����
	ITEM_INFO                 items[5]; //��ƷID�б�
	MAIL_BODY_INFO2() :gold(0), yuanbao(0), integral(0) , count(0), bind_gold(0), bind_yunabao(0) {
		memset(text, 0, sizeof(text));
		memset(items, 0, sizeof(items));
	}
};

struct ADDITION_ITEM_INFO
{
	char         item_name[32];
	uint16_t     item_id = 0;
	uint64_t     item_guid;
	uint16_t     count;
	uint16_t     bind_status;
	ADDITION_ITEM_INFO() :item_id(0), item_guid(0),count(0), bind_status(0) {
		memset(item_name, 0, sizeof(item_name));
	}
};

struct CURRENCY_INFO
{
	uint16_t type;
	int64_t  num;
	CURRENCY_INFO() :type(0), num(0) {};
};

struct MAIL_INFO
{
	uint64_t                  playerguid = 0;
	uint64_t                  mail_id;
	char                      title[64];
	char                      text[400];
	unsigned int              status;          //��ȡ����ȡ״̬
	CURRENCY_INFO             mail_currency_info[MAX_MAIL_CURRENCY_TYPE_NUM];
	uint16_t                  currency_type_num;
	ADDITION_ITEM_INFO        mail_addition_item_info[MAX_ADDITION_NUM];
	uint16_t                  addition_item_num ;
	uint16_t                  type;            //0 ϵͳ 1 ������ 2 GM 
	char                      sendername[32];
	uint64_t                  send_timesmap;
	MAIL_INFO() :playerguid(0), mail_id(0), status(0), currency_type_num(0), addition_item_num(0), type(0), send_timesmap(0) {
		memset(title, 0, sizeof(title));
		memset(text, 0, sizeof(text));
		memset(sendername, 0, sizeof(sendername));
	};

	int64_t GetCurrencyNum(uint16_t type)
	{
		for (auto i = 0; i < _countof(mail_currency_info); ++i)
		{
			if (type == mail_currency_info[i].type)
			{
				return mail_currency_info[i].num;
			}
		}
		return 0;
	};
};

struct Mail_Info_Status {
	uint64_t mailid;
	uint32_t status;
	Mail_Info_Status() :mailid(0), status(0) {}
};

struct DELEGATE_SELL_ITEM{
	uint64_t                  id                = 0;    //ID,����id
	uint64_t          		  seller_guid       = 0;	//������guid
    char                      seller[32]        = {0};  //������
	unsigned int              item_value        = 0;    //��Ʒ����
	unsigned int              item_unit         = 0;    //��Ʒ��λ����
	unsigned int              time              = 0;    //�¼�ʣ��ʱ��
	ITEM_INFO                 item;                     //��Ʒ��ϸ��Ϣ
	unsigned char             value_type        = 0;    //�۸����ͣ�0����ң�1��Ԫ����2������ 
	unsigned int              td_time			= 0;	//ί��ʱ��
	unsigned int              trade_time		= 0;	//ί�п�ʼʱ��

};
/*
struct DELEGATE_BUY_ITEM{
	uint64_t                  id; //ID
	char                      buyer[32]; //�չ���
	unsigned int              time; //�¼�ʣ��ʱ��
	char                      item_name[32]; //��Ʒ����
	unsigned int              item_num; //������
	unsigned int              item_value; //��Ʒ����
	unsigned int              item_unit; //��Ʒ��λ����
	unsigned char             value_type; //�۸����ͣ�0����ң�1��Ԫ����2������
};
*/
/*
struct DELEGATE_INFO
{
	DELEGATE_INFO()
	{
		memset(this, 0, sizeof(DELEGATE_INFO));
		item_unit = 1;
	}
	uint64_t          			id;				//ID
	uint64_t          			time;			//ί��ʱ��
	uint64_t          			role_id;		//roleid
	char						role_name[32];	//��ɫ��
	uint64_t          			item_guid;		//��Ʒguid
	unsigned int				item_id;		//��Ʒid
	char						item_name[32];	//��Ʒ��
	unsigned int				item_num;		//ʣ������
	unsigned int				item_value;		//��Ʒ����
	unsigned int				item_unit;		//��Ʒ��λ����
	unsigned char				value_type;		//�۸����ͣ�0����ң�1��Ԫ��
	unsigned char				trade_type;		//ί�����ͣ�0�����ۣ�1���չ�
};
*/
struct CAMPAIGN_INFO{
	unsigned int              id; //�id
	char                      name[256]; //�����
	unsigned char             type; //����� 4��ÿ��ִ�� 5��ÿ��ִ��
	char                      begin[256]; //��ʼʱ��
	char                      end[256]; //����ʱ��
	unsigned int              minlevel; //��С�ȼ�
	unsigned int              maxlevel; //���ȼ�
	unsigned char             count; //�����
	unsigned char             max_count; //�������
	unsigned char             status; //�״̬ 1��δ��ʼ 2�������� 3���ѽ���
};

struct FAMILY_ALLY_INFO{
	char                      family1[32]; //�л�1
	char                      family2[32]; //�л�2
};

//struct TITLE_INFO{
//	unsigned short            id; //ģ��Id
//	unsigned int              life; //���ʱ��
//};

struct TAOBAO_ITEM_INFO{
	ITEM_INFO                 item; //��Ʒ��Ϣ
	unsigned int              value; //��Ʒ�ļ۸�
};

struct MAP_INFO{
	unsigned short            width; //width
	unsigned short            height; //height
	char                      name[32]; //name
};

struct TABLE_INFO{
	unsigned int              version; //�汾��
	int                       lines; //������
	int                       size; //���ݳ���
	char                      name[32]; //name
};

struct TOPLIST_ITEM_INFO{
	unsigned char             size; //���ݳ���
	ITEM_INFO                 item[100]; //��Ʒ����
};

struct DataInfoDoNotUse{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	DataInfoDoNotUse():moudleid(15),protocolid(0){}
};

struct VIP_ITEM{
	unsigned short            id; //����ID
	unsigned char             enable; //0δ���� 1VIP�Ѽ��� 2��������
	unsigned int              remain; //�������������ʾʣ��ʱ��
	unsigned int              price; //����۸�
};

struct VIP_LEVEL{
	unsigned short            level; //VIP�ȼ�
	unsigned int              price; //����۸�
	unsigned int              times; //VIP����ʱ��
};

struct QUEST_STATE_ITEM{
	char                      title[256]; //����
	unsigned short            template_id; //����ģ��id
	unsigned char             state; //״̬��1������ɽ���2������ɽӣ�3�������ѽӲ��ɽ�
};

struct QUEST_STATE_INFO{
	unsigned short            num; //����
	QUEST_STATE_ITEM          item[100]; //����״̬��
};

struct GLORY_STATE{
	unsigned short            template_id; //�ɾ�ģ��id
	unsigned char             state; //״̬��1��δ��ɣ�2������ɣ�3����������ȡ
};

struct ROLE_BRIEF_INFO{
	uint64_t                  guid; //��ɫGUID
	char                      name[32]; //��ɫ��
	unsigned short            head; //ͷ��
	unsigned int              level; //�ȼ�
	unsigned char             status; //��ɫ״̬ 0=��δ������Ϸ,1=����,2=��ɫ��ɾ��3=��ɫ����ɾ��4=��ɫû�н�����Ϸ����ɾ��
	unsigned char             job; //ְҵ
	unsigned char             hair; //ͷ��
	unsigned char             hair_color; //ͷ����ɫ
	unsigned char             gender; //�Ա�
	unsigned short            weapon; //����
	unsigned short            clothes; //�·�
	unsigned int              gssvrid; //��ɫ����gs��server id
	unsigned int              vipLevel; //vip�ȼ�
	unsigned char             is_lock;  // �Ƿ񱻷��
	uint64_t				  updateTime = 0;
	ROLE_BRIEF_INFO() 
	{
		memset(this, 0, sizeof(ROLE_BRIEF_INFO));
	}
};

struct Point {
	int16_t						x			= 0;
	int16_t						y			= 0;

	Point() = default;
	Point(int16_t x_, int16_t y_) : x(x_), y(y_) {}
	bool operator== (const Point &rhs) const { return (x == rhs.x) && (y == rhs.y); }
};

struct AUTO_PICKUP {
	uint8_t						mode		= 0;	// 1 - ��Χ��2 - ָ����
	uint8_t					    radius		= 0;
	uint8_t						numpos		= 0;
	Point						relpos[AUTO_PICKUP_MAXPOS];
    uint16_t                    interval    = 0;    // ������ms
};

struct ROLE_SETTINGS {
	AUTO_PICKUP					auto_pickup;

	bool Comp(const ROLE_SETTINGS& data) {
		if (auto_pickup.mode != data.auto_pickup.mode)return false;
		if (auto_pickup.radius != data.auto_pickup.radius)return false;
		if (auto_pickup.numpos != data.auto_pickup.numpos)return false;
		for (int i = 0; i < auto_pickup.numpos; ++i) {
			if (auto_pickup.relpos[i].x != data.auto_pickup.relpos->x || auto_pickup.relpos[i].y != data.auto_pickup.relpos->y)return false;
		}
		if (auto_pickup.interval != data.auto_pickup.interval)return false;
		return true;
	}
};

struct ROLE_EXTRA_INFO{
    uint64_t                  login_time;
    uint32_t                  hp;
    uint32_t                  mp;
    uint64_t                  exp;
    uint16_t                  mapid;
    uint16_t                  posx;
    uint16_t                  posy;
    uint8_t                   dir;
	uint64_t				  gold;						//���
	uint64_t				  bindGold;					//�󶨽��
	uint64_t				  ingot;					//Ԫ��
	uint64_t				  bindIngot;				//��Ԫ��
	uint64_t				  integral;					//����
	uint64_t				  depositGold;				//�ֿ���
	uint64_t				  innerForceExp;			//�ڹ�����
    uint8_t                   atkMode;                  //����ģʽ
    uint16_t                  birthMap;                 //������ͼID
    uint16_t                  rebirthMap;               //������ͼID
    uint16_t                  redNameMap;               //����������ͼID
	uint16_t                  rolePk;				    //����PKֵ
	uint32_t                  modelID;                  //ģ��id
};

struct QUEST_INFO {
    uint16_t                  pre_quest;                // ǰһ������ID
    uint16_t                  cur_quest;                // ��ǰ����ID
    uint32_t                  timeleft;                 // ����ʣ��ʱ��s
    uint64_t                  timestamp;                // �ϴ��ж�ʱ���s
};

struct QUEST_ACHIEVE {
    uint16_t                  quest;                    // ����ID
    uint8_t                   achev_type;               // ������ͣ�1��NPC�Ի�|2��ɱ����|3�ռ�����|4��ɫ�ȼ��ж�|5��ɫװ���ռ��ж�|6�ű����|7�ƶ���ָ����ͼָ������
    uint16_t                  achev_id;
    int32_t                   achev_num;
};

struct DUMMY_BRIEF_INFO{
	uint64_t                  master_guid; //��ɫGUID
};

struct CHECK_BUFF{
	char                      md5_data[32]; //md5
};

struct EQUIP_INFO{
	uint16_t                    site            = 0;    //λ��
	uint16_t                    id              = 0;    //ģ��Id
};

struct DELEGATE_BUY_ITEM2{
	uint64_t                  id                = 0; //ID
	uint64_t          		  buyer_guid        = 0;	//�չ���guid
    char                      buyer[32]         = {0}; //�չ���
	unsigned int              time              = 0; //�¼�ʣ��ʱ��
    char                      item_name[32]     = {0}; //��Ʒ����
	unsigned short            item_template_id  = 0; //��Ʒģ��ID
	unsigned int              item_num          = 0; //������
	unsigned int              item_value        = 0; //��Ʒ����
	unsigned int              item_unit         = 0; //��Ʒ��λ����
	unsigned char             value_type        = 0; //�۸����ͣ�0����ң�1��Ԫ����2������
	unsigned int              td_time			= 0; //ί��ʱ��
	unsigned int              trade_time		= 0; //ί�п�ʼʱ��
};

struct MOBA_ROOM_INFO{
	int                       room_id; //room id
	char                      room_name[32]; //��������
	unsigned short            max_num; //ÿ�ߵ��������
	unsigned short            cur_num; //��ǰ����
	unsigned char             state; //����״̬ 1=׼�� 2=��Ϸ�� 3=��Ϸ����
	unsigned char             lock; //1=������ 0=������
	unsigned short            map_id; //��ͼid
	unsigned short            room_mode; //����ģʽ
};

struct MOBA_ROOM_MEMBER_INFO{
	char                      name[32]; //����ǳ�
	uint64_t                  guid; //���guid
	unsigned char             camp; //�����Ӫ 1=red 2=blue
	unsigned char             job; //��ɫְҵ
	unsigned char             site; //���λ�� 0=��һ��λ��
	unsigned char             host; //�Ƿ��Ƿ���
	unsigned char             ready; //�Ƿ�׼�����
};

struct CUST_LIST_INFO
{
	uint64_t guid = 0;
	int      type = 0;
	int64_t  value = 0;
	uint64_t stamp = 0;
	char     desc[1000] = { 0 };
	uint16_t ranking = 0;
	CUST_LIST_INFO() {};
	CUST_LIST_INFO(uint64_t _guid, int _type, int64_t _value, uint64_t _stamp, const char* _desc) :guid(_guid), type(_type), value(_value), stamp(_stamp) {
		memcpy_s(desc, sizeof(desc), _desc, sizeof(_desc));
	};
};

using CUST_DATA_SP = std::shared_ptr<CUST_LIST_INFO>;

struct MONITOR_CHAT_INFO {
	uint64_t      user_id;
	char          user_name[32];
	uint64_t      to_user_id;
	char          to_user_name[32];
	uint16_t      channel;
	char          guild[32];
	char          stamp[100];
	char          content[65535];
};

using MONITOR_CHAT_INFO_SP = std::shared_ptr<MONITOR_CHAT_INFO>;
using MONITOR_CHAT_INFO_SP_LIST = std::list<MONITOR_CHAT_INFO_SP>;

struct PLATFORM_CREATE_ROLE_INFO
{
	std::string game_id = "";
	std::string region_id = "";
	std::string server_id = "";
	std::string role_id = "";
	std::string channel = "";
	std::string user_id = "";
};

using SP_BUY_DELEGATE = std::shared_ptr<DELEGATE_BUY_ITEM2>;
using SP_BUY_DELEGATE_MAP = std::map<uint64_t, SP_BUY_DELEGATE>;
using SP_BUY_DELEGATE_LIST = std::list<SP_BUY_DELEGATE>;
using SP_SELL_DELEGATE = std::shared_ptr<DELEGATE_SELL_ITEM>;
using SP_SELL_DELEGATE_MAP = std::map<uint64_t, SP_SELL_DELEGATE>;
using SP_SELL_DELEGATE_LIST = std::list<SP_SELL_DELEGATE>;
//using SPDELEGATE = std::shared_ptr<DELEGATE_INFO>;
//using DELEGATE_MAP = std::map<uint64_t, SPDELEGATE>;

using DGN_BIND_INFO_LIST = std::list<DGN_BIND_INFO>;

using QUICK_BAR_INFO_LIST = std::list<QUICK_BAR_INFO>;

struct Hated_Value
{
	float hated_value = 0;
	uint64_t timer = 0;
};

struct AUCTION_HOUSE_ITEM_INFO
{
	enum auction_house_item_status
	{
		auction_status_type_wait   = 0,
		auction_status_type_ing    = 1,
		auction_status_type_end    = 2,
		auction_status_type_passin = 3,
	};
	char           item_name[32];
	uint16_t       item_num;
	int            item_price;
	uint8_t        currency_type;
	uint64_t       start_time;
	uint64_t       keep_time;
	uint8_t        status;
	uint64_t       orderID;
	uint64_t       ownerID;
	char           ownerName[32];
	AUCTION_HOUSE_ITEM_INFO():item_num(0), item_price(0), start_time(0), keep_time(0),status(0),orderID(0), ownerID(0)
	{
		memset(item_name, 0, sizeof(item_name));
		memset(ownerName, 0, sizeof(ownerName));
	}
};

struct LOGIN_IP_DATA
{
	uint32_t ip    = 0;
	uint8_t  type  = 0;
	LOGIN_IP_DATA() = default;
};

struct PROHIBIT_CHAT_DATA
{
	uint64_t playerguid = 0;
	uint64_t time = 0;
	PROHIBIT_CHAT_DATA() = default;
};

using AUCTION_HOUSE_ITEM_INFO_LIST = std::map<uint64_t, AUCTION_HOUSE_ITEM_INFO>;


struct WANTED_BY                                                // ���ͷ�������Ϣ
{
    uint32_t                    index           = 0;            // ���ݿ��е����
    uint64_t                    guid            = 0;            // ���ͷ�����GUID
    std::string                 name;                           // ���ͷ���������
    std::string                 desc;                           // ����
    uint32_t                    bounty          = 0;            // ���ͽ��
    uint64_t                    ptime           = 0;            // ��������ʱ��
};

using WANTED_BY_SP = std::shared_ptr<WANTED_BY>;
using WANTED_BY_SP_LIST = std::list<WANTED_BY_SP>;

struct WANTED                                                   // ����������Ϣ
{
    uint64_t                    guid            = 0;            // ��������GUID
    std::string                 name;                           // ������������
    WANTED_BY_SP_LIST           wanted_by_list;                 // ���ͷ������б�
};

using WANTED_SP = std::shared_ptr<WANTED>;
using WANTED_SP_LIST = std::list<WANTED_SP>;

struct GOODS_ISSUE_RECORD                                       // ��ҳ�ֵ������Ʒ���ż�¼
{
    char                        order_no[ORDER_NO_BUFLEN] = {0};           // ������
    uint64_t                    role_guid       = 0;            // ��ɫGUID
    uint8_t                     pay_type        = 0;            // ��ֵ����
    uint32_t                    goods_id        = 0;            // ��ֵ��λID
    uint32_t                    goods_num       = 0;            // ��Ʒ����
    uint32_t                    pay_amount      = 0;            // ��ֵ���
    uint8_t                     issued          = 0;            // �Ƿ��ѷ���
	uint8_t                     isPost          = 0;            // �Ƿ����ϱ�
};

struct REBATE_MONEY_RECORD                                       // ���ɾ���������ż�¼
{
	uint8_t						be_load = 0;
	int64_t						inc_id = 0;						// �ӿ�set flagʱ��ѯЧ��
	uint64_t					account_id = 0;					// id
	char						account_name[256] = { 0 };		// �˺�
	int64_t						rebate_money = 0;				// �������
	uint8_t                     is_use = 0;						// �Ƿ��ѷ���
};

struct MESSAGE_INFO
{
	char       message[65535];
	char       font_color[32];
	char       background_color[32];
	int32_t    type                   = 0;
	uint32_t   size                   = 0;
	uint8_t    comp                   = 0;
	uint16_t   display_type           = 0;
	uint8_t    scroll_times           = 0;
	uint64_t   srcGuid                = 0;
	uint64_t   dstGuid                = 0;
	uint8_t    isAppearSrcName        = 0;
	uint16_t   posx                   = 0;
	uint16_t   posy                   = 0;
	uint16_t   marqueeType            = 0;
	MESSAGE_INFO() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
	void Clear() {
		memset(this, 0, sizeof(MESSAGE_INFO));
	}
};
static MESSAGE_INFO gMESSAGE_INFO;

struct RELATION_CHAT_NTF
{
	uint8_t     type                 = 0;    // 1����ǰ 2������ 3������ 4������ 5��С���� 9: ��Ӫ 12��ȫ��
	CHAT_MSG    chat_message;                // ��ɫ��ΪԴ��ɫ������
	uint8_t     scroll_times         = 0;
	char        font_color[32];
	char        background_color[32];
	uint32_t    size                 = 0;    // ѹ�������С
	uint8_t     comp                 = 0;    // �Ƿ�ѹ��
};

struct SYSTEN_MESSAGE_NTF
{
	char      message[65535];
	char      font_color[32];
	char      background_color[32];
	uint32_t  size                         = 0;
	uint8_t   comp                         = 0;

	SYSTEN_MESSAGE_NTF() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct SCENCE_DIALOG_NTF
{
	char       message[65535];
	char       font_color[32];
	char       background_color[32];
	uint64_t   objGuid                      = 0;
	uint8_t    isAppearSrcName              = 0;
	uint32_t   size                         = 0;
	uint8_t    comp                         = 0;

	SCENCE_DIALOG_NTF() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct SCROLL_TEXT
{
	char      message[65535];
	char      font_color[32];
	char      background_color[32];
	uint8_t   scroll_times               = 0;
	uint32_t  size                       = 0;
	uint8_t   comp                       = 0;
	uint8_t   type                       = 0;

	SCROLL_TEXT() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct CUST_MSG_NTF
{
	char      message[65535];
	char      font_color[32];
	char      background_color[32];
	uint32_t  size         = 0;
	uint8_t   comp         = 0;
	uint16_t  display_type = 0;  // 1 ����� 2 ����� 3 ���� 4��1&2�� 5��1&3�� 6��2&3�� 7��1&2&3��
	uint8_t   scroll_times = 0;
	CUST_MSG_NTF() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct TITLE_INFO {
	uint32_t         Id        = 0;         // id
	uint8_t          isWear    = 0;         // �Ƿ񴩴�
	uint64_t         addTime   = 0;         // ���ʱ��
	uint32_t         lifeTime  = 0;         // ����ʱ��
	uint32_t         timeLimit = 0;         // ����ʱ��
};

using SP_TITLE_INFO = std::shared_ptr<TITLE_INFO>;

struct RedemptionCodeInfo
{
	uint64_t userid = 0;
	uint64_t guid = 0;
	uint8_t  type = 0;
	char     code[50];
	char     name[50];
	RedemptionCodeInfo() {
		memset(code, 0, _countof(code));
		memset(name, 0, _countof(code));
	}
};

struct BossInfo {
	uint32_t tempID = 0;
	uint64_t guid = 0;
	uint32_t mapID = 0;
	std::string mapName;
	uint64_t reliveTime = 0;
	uint64_t lastGUID = 0;
	BossInfo(uint32_t _temp,uint64_t _guid,uint32_t _mapID,uint64_t _reliveTime,std::string _mapName, uint64_t _lastGUID):
		tempID(_temp),guid(_guid),mapID(_mapID),reliveTime(_reliveTime),mapName(_mapName),lastGUID(_lastGUID)
	{
	}
};

struct EffectPoint {
	uint16_t x       = 0;
	uint16_t y       = 0;
	uint32_t effect  = 0;
};

struct TrapPointEffect {
	uint32_t SkillID = 0;
	uint32_t timerID = 0;
	EffectPoint data;
};

#pragma warning( pop ) 
//===============���ݶ������===============
//===============�������������忪ʼ===============
int EnCodeKEY_VALUE_PAIR(void* pHost, CNetData* poNetData);
int DeCodeKEY_VALUE_PAIR(void* pHost, CNetData* poNetData);
int EnCodePARAM_INFO(void* pHost, CNetData* poNetData);
int DeCodePARAM_INFO(void* pHost, CNetData* poNetData);
int EnCodePARAM_INFO2(void* pHost, CNetData* poNetData);
int DeCodePARAM_INFO2(void* pHost, CNetData* poNetData);
int EnCodeIntData(void* pHost, CNetData* poNetData);
int DeCodeIntData(void* pHost, CNetData* poNetData);
int EnCodeStrData(void* pHost, CNetData* poNetData);
int DeCodeStrData(void* pHost, CNetData* poNetData);
int EnCodeBlobData(void* pHost, CNetData* poNetData);
int DeCodeBlobData(void* pHost, CNetData* poNetData);
int EnCodeITEM_CFG_VAR(void* pHost, CNetData* poNetData);
int DeCodeITEM_CFG_VAR(void* pHost, CNetData* poNetData);
int EnCodeROLE_DATA_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_DATA_INFO(void* pHost, CNetData* poNetData);
int EnCodeCUSTOM_INFO(void* pHost, CNetData* poNetData);
int DeCodeCUSTOM_INFO(void* pHost, CNetData* poNetData);
int EnCodeITEM_DB_INFO(void* pHost, CNetData* poNetData);
int DeCodeITEM_DB_INFO(void* pHost, CNetData* poNetData);
int EnCodeITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeLOGTRADE_DATA(void* pHost, CNetData* poNetData);
int DeCodeLOGTRADE_DATA(void* pHost, CNetData* poNetData);
int EnCodeCHAT_MSG(void* pHost, CNetData* poNetData);
int DeCodeCHAT_MSG(void* pHost, CNetData* poNetData);
int EnCodeSKILL_INFO(void* pHost, CNetData* poNetData);
int DeCodeSKILL_INFO(void* pHost, CNetData* poNetData);
int EnCodeBUFF_INFO(void* pHost, CNetData* poNetData);
int DeCodeBUFF_INFO(void* pHost, CNetData* poNetData);
int EnCodeBUFF_INFO_DB(void* pHost, CNetData* poNetData);
int DeCodeBUFF_INFO_DB(void* pHost, CNetData* poNetData);
int EnCodeSHOP_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeSHOP_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeTEAM_MEMBER(void* pHost, CNetData* poNetData);
int DeCodeTEAM_MEMBER(void* pHost, CNetData* poNetData);
int EnCodeTEAM_INFO(void* pHost, CNetData* poNetData);
int DeCodeTEAM_INFO(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_INFO(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_INFO(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_DETAIL(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_DETAIL(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_LIST(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_LIST(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_RELATION(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_RELATION(void* pHost, CNetData* poNetData);
int EnCodeSERVANT_INFO(void* pHost, CNetData* poNetData);
int DeCodeSERVANT_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAP_REGION_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAP_REGION_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_TITLE(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_TITLE(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_DETAIL(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_DETAIL(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_INFO_GS(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_INFO_GS(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_INFO(void* pHost, CNetData* poNetData);
int EnCodeMEMBER_INFO(void* pHost, CNetData* poNetData);
int DeCodeMEMBER_INFO(void* pHost, CNetData* poNetData);
int EnCodeMEMBER_INFO_GS(void* pHost, CNetData* poNetData);
int DeCodeMEMBER_INFO_GS(void* pHost, CNetData* poNetData);
int EnCodeAPPLICANTS_INFO(void* pHost, CNetData* poNetData);
int DeCodeAPPLICANTS_INFO(void* pHost, CNetData* poNetData);
int EnCodeROLE_FORBIDTALK_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_FORBIDTALK_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_APPLY_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_APPLY_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_WAR_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_WAR_INFO(void* pHost, CNetData* poNetData);
int EnCodeCASTLE_INFO(void* pHost, CNetData* poNetData);
int DeCodeCASTLE_INFO(void* pHost, CNetData* poNetData);
int EnCodeGUILD_INFO(void *pHost, CNetData *poNetData);
int DeCodeGUILD_INFO(void *pHost, CNetData *poNetData);
int EnCodeGUILD_MEMBER(void *pHost, CNetData *poNetData);
int DeCodeGUILD_MEMBER(void *pHost, CNetData *poNetData);
int EnCodeGUILD_APPLY_INFO(void *pHost, CNetData *poNetData);
int DeCodeGUILD_APPLY_INFO(void *pHost, CNetData *poNetData);
int EnCodeMALL_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeMALL_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeMALL_ITEM_DETAIL(void* pHost, CNetData* poNetData);
int DeCodeMALL_ITEM_DETAIL(void* pHost, CNetData* poNetData);
int EncodeMALL_ITEM_INFO_BASE(void* pHost, CNetData* poNetData);
int DecodeMALL_ITEM_INFO_BASE(void* pHost, CNetData* poNetData);
int EnCodeTOPLIST_INFO(void* pHost, CNetData* poNetData);
int DeCodeTOPLIST_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_HUNTING_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_HUNTING_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_HUNTLEVEL_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_HUNTLEVEL_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_NPC_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_NPC_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_HEADER_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_HEADER_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_BODY_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_BODY_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_BODY_INFO2(void* pHost, CNetData* poNetData);
int DeCodeMAIL_BODY_INFO2(void* pHost, CNetData* poNetData);
int EnCodeMAIL_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_ADDITIONITEMINFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_ADDITIONITEMINFO(void* pHost, CNetData* poNetData);
int EncodeMAIL_CURRENCYINFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_CURRENCYINFO(void* pHost, CNetData* poNetData);
int EnCodeMail_INFO_STATUS(void* pHost, CNetData* poNetData);
int DeCodeMail_INFO_STATUS(void* pHost, CNetData* poNetData);
int EnCodeDELEGATE_SELL_ITEM(void* pHost, CNetData* poNetData);
int DeCodeDELEGATE_SELL_ITEM(void* pHost, CNetData* poNetData);
//int EnCodeDELEGATE_BUY_ITEM(void* pHost, CNetData* poNetData);
//int DeCodeDELEGATE_BUY_ITEM(void* pHost, CNetData* poNetData);
//int EnCodeDELEGATE_INFO(void* pHost, CNetData* poNetData);
//int DeCodeDELEGATE_INFO(void* pHost, CNetData* poNetData);
int EnCodeCAMPAIGN_INFO(void* pHost, CNetData* poNetData);
int DeCodeCAMPAIGN_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_ALLY_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_ALLY_INFO(void* pHost, CNetData* poNetData);
int EnCodeTITLE_INFO(void* pHost, CNetData* poNetData);
int DeCodeTITLE_INFO(void* pHost, CNetData* poNetData);
int EnCodeTAOBAO_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeTAOBAO_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAP_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAP_INFO(void* pHost, CNetData* poNetData);
int EnCodeTABLE_INFO(void* pHost, CNetData* poNetData);
int DeCodeTABLE_INFO(void* pHost, CNetData* poNetData);
int EnCodeTOPLIST_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeTOPLIST_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeDataInfoDoNotUse(void* pHost, CNetData* poNetData);
int DeCodeDataInfoDoNotUse(void* pHost, CNetData* poNetData);
int EnCodeVIP_ITEM(void* pHost, CNetData* poNetData);
int DeCodeVIP_ITEM(void* pHost, CNetData* poNetData);
int EnCodeVIP_LEVEL(void* pHost, CNetData* poNetData);
int DeCodeVIP_LEVEL(void* pHost, CNetData* poNetData);
int EnCodeQUEST_STATE_ITEM(void* pHost, CNetData* poNetData);
int DeCodeQUEST_STATE_ITEM(void* pHost, CNetData* poNetData);
int EnCodeQUEST_STATE_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_STATE_INFO(void* pHost, CNetData* poNetData);
int EnCodeGLORY_STATE(void* pHost, CNetData* poNetData);
int DeCodeGLORY_STATE(void* pHost, CNetData* poNetData);
int EnCodeROLE_BRIEF_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_BRIEF_INFO(void* pHost, CNetData* poNetData);
int EnCodeROLE_EXTRA_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_EXTRA_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_ACHIEVE(void* pHost, CNetData* poNetData);
int DeCodeQUEST_ACHIEVE(void* pHost, CNetData* poNetData);
int EnCodeDUMMY_BRIEF_INFO(void* pHost, CNetData* poNetData);
int DeCodeDUMMY_BRIEF_INFO(void* pHost, CNetData* poNetData);
int EnCodeCHECK_BUFF(void* pHost, CNetData* poNetData);
int DeCodeCHECK_BUFF(void* pHost, CNetData* poNetData);
int EnCodeEQUIP_INFO(void* pHost, CNetData* poNetData);
int DeCodeEQUIP_INFO(void* pHost, CNetData* poNetData);
int EnCodeDELEGATE_BUY_ITEM2(void* pHost, CNetData* poNetData);
int DeCodeDELEGATE_BUY_ITEM2(void* pHost, CNetData* poNetData);
int EnCodeMOBA_ROOM_INFO(void* pHost, CNetData* poNetData);
int DeCodeMOBA_ROOM_INFO(void* pHost, CNetData* poNetData);
int EnCodeMOBA_ROOM_MEMBER_INFO(void* pHost, CNetData* poNetData);
int DeCodeMOBA_ROOM_MEMBER_INFO(void* pHost, CNetData* poNetData);
int EnCodeCUST_VAR(void *pHost, CNetData *poNetData);
int DeCodeCUST_VAR(void *pHost, CNetData *poNetData);
int EnCodeCUST_VAR_SP_LIST(void *pHost, CNetData *poNetData);
int DeCodeCUST_VAR_SP_LIST(void *pHost, CNetData *poNetData);

int EnCodeQUICK_BAR_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUICK_BAR_INFO(void* pHost, CNetData* poNetData);

int EnCodeQUICK_BAR_LIST_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUICK_BAR_LIST_INFO(void* pHost, CNetData* poNetData);
int EnCodeDYN_ATTR(void *pHost, CNetData *poNetData);
int DeCodeDYN_ATTR(void *pHost, CNetData *poNetData);
int EnCodeITEM_DYN_ATTRS(void *pHost, CNetData *poNetData);
int DeCodeITEM_DYN_ATTRS(void *pHost, CNetData *poNetData);
int EnCodeITEM_DYN_ATTRS_LIST(void *pHost, CNetData *poNetData);
int DeCodeITEM_DYN_ATTRS_LIST(void *pHost, CNetData *poNetData);
int EnCodeAUCTION_HOUSE_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeAUCTION_HOUSE_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeLOGIN_IP_DATA(void* pHost, CNetData* poNetData);
int DeCodeLOGIN_IP_DATA(void* pHost, CNetData* poNetData);
int EnCodePROHIBIT_CHAT_DATA(void* pHost, CNetData* poNetData);
int DeCodePROHIBIT_CHAT_DATA(void* pHost, CNetData* poNetData);
int EnCodeWANTED_BY(void *pHost, CNetData *poNetData);
int DeCodeWANTED_BY(void *pHost, CNetData *poNetData);
int EnCodeWANTED(void *pHost, CNetData *poNetData);
int DeCodeWANTED(void *pHost, CNetData *poNetData);
int EncodePoint(void *pHost, CNetData *poNetData);
int DecodePoint(void *pHost, CNetData *poNetData);
int EncodeAUTO_PICKUP(void *pHost, CNetData *poNetData);
int DecodeAUTO_PICKUP(void *pHost, CNetData *poNetData);
int EncodeROLE_SETTINGS(void *pHost, CNetData *poNetData);
int DecodeROLE_SETTINGS(void *pHost, CNetData *poNetData);
int EncodeGOODS_ISSUE_RECORD(void *pHost, CNetData *poNetData);
int DecodeGOODS_ISSUE_RECORD(void *pHost, CNetData *poNetData);
int EncodeREBATE_MONEY_RECORD(void* pHost, CNetData* poNetData);
int DecodeREBATE_MONEY_RECORD(void* pHost, CNetData* poNetData);
int EncodeMONITOR_CHAT_INFO(void* pHost, CNetData* poNetData);
int DecodeMONITOR_CHAT_INFO(void* pHost, CNetData* poNetData);
int EncodeSYSTEN_MESSAGE_NTF(void* pHost, CNetData* poNetData);
int DecodeSYSTEN_MESSAGE_NTF(void* pHost, CNetData* poNetData);
int EncodeSCENCE_DIALOG_NTF(void* pHost, CNetData* poNetData);
int DecodeSCENCE_DIALOG_NTF(void* pHost, CNetData* poNetData);
int EncodeSCROLL_TEXT(void* pHost, CNetData* poNetData);
int DecodeSCROLL_TEXT(void* pHost, CNetData* poNetData);
int EncodeRELATION_CHAT_NTF(void* pHost, CNetData* poNetData);
int DecodeRELATION_CHAT_NTF(void* pHost, CNetData* poNetData);
int EncodeCUST_MSG_NTF(void* pHost, CNetData* poNetData);
int DecodeCUST_MSG_NTF(void* pHost, CNetData* poNetData);
int EncodeCUST_LIST_INFO(void* pHost, CNetData* poNetData);
int DecodeCUST_LIST_INFO(void* pHost, CNetData* poNetData);
int EncodeEFFECT_POINT(void* pHost, CNetData* poNetData);
int DecodeEFFECT_POINT(void* pHost, CNetData* poNetData);


//===============�����������������===============
typedef int (*EnCodeFuncDataInfo)(void *pHost, CNetData* poNetData);
typedef int (*DeCodeFuncDataInfo)(void *pHost, CNetData* poNetData);

class CDataInfo
{
public:
	CDataInfo();
	~CDataInfo();
	int BuildProtocol(void* pHost, char *pNet, int iNetSize);

	bool HandleProtocol(char *pNet, int iNetSize, void* pHost);

	static inline unsigned short GetModuleID(void){ return 15; }

	static inline unsigned short GetProtocolNum(void){ return 1; }

	static const unsigned short module_id = 15;

	static const unsigned short protocol_num = 1;

//===============����Э��ص�������Ҫʹ������ʵ��===============
	virtual void OnRecv_DataInfoDoNotUse(DataInfoDoNotUse& rstProtocol){ rstProtocol; };
private:
	EnCodeFuncDataInfo m_EnCodeFuncArray[1];
	EnCodeFuncDataInfo m_DeCodeFuncArray[1];
};
