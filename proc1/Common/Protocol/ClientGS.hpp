#pragma once

//===============����������Э���ļ�===============

 //===============�궨�忪ʼ===============
//===============�궨�����===============

//===============���ݶ��忪ʼ===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct EnterGSReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{0};
	unsigned char             entertype; //�������� 0=���� 1=����
	uint64_t                  roleguid; //��ɫguid
	unsigned char             fangchenmi; //�Ƿ�������û� 1���� 0����
	EnterGSReq() = default;
};

struct EnterGSAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{1};
	unsigned char             entertype; //�������� 0=���� 1=����
	uint64_t                  roleguid; //��ɫguid
	unsigned int              gsobjid; //�ͻ�����GS�ϵ�objid
	int                       errcode; //������
	char                      errmsg[256]; //��������
	EnterGSAck() = default;
};

struct ExitGSReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{2};
	unsigned char             exittype; //�˳����� 1=���� 2=С��
	ExitGSReq() = default;
};

struct ExitGSAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{3};
	unsigned char             exittype; //�˳����� 1=���� 2=С��
	int                       errcode; //������
	char                      errmsg[256]; //��������
	ExitGSAck() = default;
};

struct JumpGSNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{4};
	unsigned char             jumptype; //��ת���� 3=����ͼ 9=�ص�½
	unsigned int              gssvrid; //Ŀ��Game Server ID
	uint64_t                  mapcode; //Ŀ�ĵ�ͼ�ı��
	JumpGSNtf() = default;
};

struct KickRoleNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{5};
	uint64_t                  roleguid; //���߳���ɫ��GUID
	int                       errcode; //������
	char                      errmsg[256]; //��������
	KickRoleNtf() = default;
};

struct EnterMapNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{6};
	uint64_t                  mapcode; //��ͼ��ˮ��
	char                      logic[256]; //��ͼ�߼����ļ�
	unsigned short            view_x; //��ͼ��Ұ��ΧX
	unsigned short            view_y; //��ͼ��Ұ��ΧY
	unsigned short            width; //��
	unsigned short            height; //��
	EnterMapNtf() = default;
};

struct MapRegionNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{7};
	uint64_t                  mapcode; //��ͼ��ˮ��
	char                      logic[256]; //��ͼ�߼����ļ�
	unsigned char             rg_num; //��������
	MAP_REGION_INFO           rg_info[255]; //������Ϣ
	MapRegionNtf() = default;
};

struct SetRelivePT{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{8};
	SetRelivePT() = default;
};

struct PlayerReliveReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{9};
	unsigned char             relive_type; //�������� 1=ԭ�ظ��� 2=�سǸ��� 3=������ڸ���
	PlayerReliveReq() = default;
};

struct PlayerReliveAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{10};
	unsigned char             relive_type; //�������� 1=ԭ�ظ��� 2=�سǸ��� 3=������ڸ���
	int                       error_code; //������ 0=��ʾ�ɹ�
	PlayerReliveAck() = default;
};

struct PlayerAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{11};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //����
	unsigned char             gender; //�Ա�
	unsigned char             job; //ְҵ
	unsigned char             status; //����״̬ 0=���� 1=����
	unsigned short            head; //ͷ��
	unsigned int              level; //�ȼ�
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned char             dir; //����
	unsigned short            hair; //ͷ��
	unsigned short            hair_color; //ͷ����ɫ
	unsigned short            body; //����
	unsigned short            weapon; //����
	unsigned short            wings; //���
	unsigned short            mount; //����
	unsigned short            weapon_effect; //������Ч
	unsigned short            body_effect; //������Ч
	unsigned short            mount_effect; //������Ч
	unsigned int              hp; //��ǰѪ��
	unsigned int              max_hp; //���Ѫ��
	unsigned int              mp; //��ǰmp
	unsigned int              max_mp; //���mp
	int                       pk; //pk
	unsigned short            move_speed; //�ƶ��ٶ�
	unsigned short            attack_speed; //�����ٶ�
	unsigned short            title; //�ƺ�
	unsigned char             has_team; //�Ƿ��ж���
	unsigned char             stall; //0: δ��̯ 1: ��̯׼�� 2: ��̯��
	char                      stall_name[32]; //��̯����
	unsigned short            buff_num; //Buff����
	BUFF_INFO                 buffs[50]; //Buff��Ϣ
	char                      family_name[32]; //�л�����
	char                      castle_name[256]; //�Ǳ����ƣ����Զ��������ŷָ�
	char                      family_title[32]; //�л�ƺ�
	char                      alias[64]; //����
	CUSTOM_INFO               custom; //�Զ�������
	unsigned char             appear_type; //�������� 0=������Ұ 1=���� 2=��Ծ
	unsigned short            amulet; //����
	PlayerAppearNtf() = default;
};

struct MonsterAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{12};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //ģ��id
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
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
	MonsterAppearNtf() = default;
};

struct ItemAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{13};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //ģ��id
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned short            skill_id; //����id
	char                      item_name[32]; //��Ʒ����
	ItemAppearNtf() = default;
};

struct NPCAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{14};
	uint64_t                  npc_guid; //npc guid
	unsigned short            template_id; //ģ��id
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned char             dir; //����
	char                      name[256]; //����
	NPCAppearNtf() = default;
};

struct ObjDisappearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{15};
	uint64_t                  obj_guid; //obj guid
	ObjDisappearNtf() = default;
};

struct PlayerCreate{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{16};
	uint64_t                  player_guid; //player guid
	char                      name[32]; //����
	unsigned char             sex; //�Ա�
	unsigned short            head; //ͷ��
	unsigned short            hair; //����
	unsigned int              hair_color; //��ɫ
	unsigned int              level; //�ȼ�
	uint64_t                  exp; //����
	PlayerCreate() = default;
};

struct MoveReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{17};
	unsigned char             type; //�ƶ����� 0=�� 1=��
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned int              idx; //�ͻ������к�
	MoveReq() = default;
};

struct MoveNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{18};
	uint64_t                  guid; //player/monster/npc's guid
	unsigned char             type; //�ƶ����� 0=�� 1=�� 2=��
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	MoveNtf() = default;
};

struct MoveAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{19};
	unsigned char             ret; //0=�ɹ�, 1=��ʾʧ��
	unsigned char             type; //�ƶ����� 0=�� 1=��
	unsigned short            dst_x; //�ƶ�ǰ�ĵ�x
	unsigned short            dst_y; //�ƶ�ǰ�ĵ�y
	unsigned int              idx; //�ͻ������к�
	MoveAck() = default;
};

struct TurnReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{20};
	unsigned char             dir; //��ɫ���ڵķ���
	TurnReq() = default;
};

struct TurnNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{21};
	uint64_t                  guid; //player/monster/npc's guid
	unsigned char             dir; //��ɫ���ڵķ���
	TurnNtf() = default;
};

struct TurnAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{22};
	unsigned char             ret; //0=�ɹ�, 1=��ʾʧ��
	unsigned char             dir; //��ɫ���ڵķ���
	TurnAck() = default;
};

struct ObjDieNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{23};
	uint64_t                  die_guid; //�����Ķ����guid ������player/monster/npc
	uint64_t                  kill_guid; //ɱ�ֵĶ����guid ������player/monster/npc
	char                      kill_name[32]; //ɱ�ֵ�����
	ObjDieNtf() = default;
};

struct ChatReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{24};
	unsigned char             type; //�������� 1=��ͨ 5=����
	char                      sender[256]; //�����ߵ�����
	char                      text[256]; //message
	ChatReq() = default;
};

struct GMCommandReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{25};
	char                      cmd[256]; //GM ָ��
	char                      param[256]; //ָ�����
	GMCommandReq() = default;
};

struct RoleAppNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{26};
	uint64_t                  player_guid; //player guid
	unsigned short            hair; //ͷ��
	unsigned short            hair_color; //ͷ����ɫ
	unsigned short            body; //����
	unsigned short            weapon; //����
	unsigned short            wings; //���
	unsigned short            mount; //����
	unsigned short            weapon_effect; //������Ч
	unsigned short            body_effect; //������Ч
	unsigned short            mount_effect; //������Ч
	unsigned short            amulet; //����
	RoleAppNtf() = default;
};

struct RoleAttrNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{27};
	uint64_t                  role_guid; //role guid
	unsigned short            num; //����
	unsigned short            attr_name[100]; //��������
	int                       attr_value[100]; //����ֵ
	RoleAttrNtf() = default;
};

struct RoleAttrExtNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{28};
	uint64_t                  player_guid; //player guid
	unsigned short            num; //����
	unsigned short            attr_name[20]; //��������
	int64_t                   attr_value[20]; //����ֵ
	RoleAttrExtNtf() = default;
};

struct TeamMemberNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{29};
	uint64_t                  member_guid; //member guid
	unsigned short            x; //x
	unsigned short            y; //y
	TeamMemberNtf() = default;
};

struct ShowFormNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{30};
	char                      form_name[256]; //������
	unsigned short            size; //�������ֽ���
	char                      form_content[7900]; //������
	char                      comp; //�Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��
	ShowFormNtf() = default;
};

struct SubmitForm{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{31};
	char                      script_name[256]; //�ű�����
	char                      function_name[256]; //��������
	unsigned short            num; //��������
	PARAM_INFO                info[100]; //������Ϣ
	SubmitForm() = default;
};

struct ItemAddReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{32};
	unsigned short            item_id; //��Ʒģ��ID
	int                       item_amount; //��Ʒ����
	unsigned char             is_bind; //�Ƿ��
	ItemAddReq() = default;
};

struct ItemAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{33};
	ITEM_INFO                 info; //��Ʒ��Ϣ
	ItemAddAck() = default;
};

struct ItemDestroyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{34};
	uint64_t                  item_guid; //������Ʒ��GUID
	ItemDestroyReq() = default;
};

struct ItemDestroyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{35};
	uint64_t                  item_guid; //������Ʒ��GUID
	ItemDestroyAck() = default;
};

struct ItemMove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{36};
	uint64_t                  item_guid; //��ƷGUID
	unsigned short            dest_site; //��Ʒ��Ŀ��λ��
	ItemMove() = default;
};

struct ItemSplit{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{37};
	uint64_t                  item_guid; //��ƷGUID
	unsigned short            item_amount; //��Ʒ����
	unsigned short            dest_site; //��Ʒ��Ŀ��λ��
	ItemSplit() = default;
};

struct ItemAttrNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{38};
	uint64_t                  item_guid; //��ƷGUID
	unsigned int              attr_name; //��Ʒ��������
	int                       attr_value; //��Ʒ����ֵ
	ItemAttrNtf() = default;
};

struct ItemUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{39};
	ITEM_INFO                 info; //��Ʒ��Ϣ
	ItemUpdateNtf() = default;
};

struct ItemBind{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{40};
	uint64_t                  item_guid; //��ƷGUID
	ItemBind() = default;
};

struct ItemApply{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{41};
	uint64_t                  item_guid; //��ƷGUID
	ItemApply() = default;
};

struct ItemApplyOnTarget{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{42};
	uint64_t                  item_guid; //��ƷGUID
	uint64_t                  target; //target, ������player/monster/npc's guid
	ItemApplyOnTarget() = default;
};

struct ItemApplyOnGrid{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{43};
	uint64_t                  item_guid; //��ƷGUID
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	ItemApplyOnGrid() = default;
};

struct ItemArrange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{44};
	unsigned char             type; //0=���� 1=�ֿ� 2=�߼��ֿ�
	ItemArrange() = default;
};

struct ItemPickUp{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{45};
	ItemPickUp() = default;
};

struct ItemDrop{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{46};
	uint64_t                  item_guid; //��ƷGUID
	ItemDrop() = default;
};

struct ItemTieUp{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{47};
	uint64_t                  item_guid; //������ƷGUID
	ItemTieUp() = default;
};

struct ItemTip{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{48};
	uint64_t                  owner_guid; //��Ʒӵ���� guid
	uint64_t                  item_guid; //item's guid
	ItemTip() = default;
};

struct ItemTipBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{49};
	uint64_t                  owner_guid; //��Ʒӵ���� guid
	uint64_t                  item_guid; //item's guid
	unsigned int              target_userid; //Ŀ�� userid
	ItemTipBrd() = default;
};

struct ItemTipNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{50};
	ITEM_INFO                 info; //��Ʒ��Ϣ
	ItemTipNtf() = default;
};

struct ItemEnhance{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{51};
	uint64_t                  item_guid; //ǿ��������guid
	unsigned short            items_num; //��������
	uint64_t                  items_info[100]; //����װ��
	unsigned short            materials_num; //��������
	uint64_t                  materials_info[100]; //���Ĳ���
	ItemEnhance() = default;
};

struct ItemDrill{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{52};
	uint64_t                  item_guid; //�����Ʒ
	uint64_t                  material_guid; //��ײ���
	ItemDrill() = default;
};

struct ItemSynthesis{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{53};
	uint64_t                  material_guid; //��ʯ�ϳɷ�
	unsigned short            gems_num; //��ʯ����
	uint64_t                  gems_info[5]; //��ʯ
	ItemSynthesis() = default;
};

struct ItemEmbed{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{54};
	uint64_t                  item_guid; //��Ƕ��Ʒ
	uint64_t                  material_guid; //��ʯ��Ƕ��
	uint64_t                  gem_guid; //��ʯ
	ItemEmbed() = default;
};

struct ItemDig{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{55};
	uint64_t                  item_guid; //��Ƕ��Ʒ
	uint64_t                  material_guid; //��ʯժ����
	unsigned char             slot; //��ʯ��
	ItemDig() = default;
};

struct ItemIdentify{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{56};
	uint64_t                  item_guid; //������Ʒ
	uint64_t                  material_guid; //��������
	ItemIdentify() = default;
};

struct ItemRename{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{57};
	uint64_t                  item_guid; //��Ʒguid
	char                      new_name[32]; //��Ʒ������
	ItemRename() = default;
};

struct ItemRefine{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{58};
	uint64_t                  item_guid; //��Ʒguid
	uint64_t                  material_guid; //��������
	uint64_t                  lucky_guid; //�������˷�
	ItemRefine() = default;
};

struct ItemRepairQuery{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{59};
	uint64_t                  item_guid; //��Ʒguid
	unsigned char             type; //����ʽ 1:��ͨ 2:����
	ItemRepairQuery() = default;
};

struct ItemRepairQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{60};
	int                       gold; //�����
	ItemRepairQueryNtf() = default;
};

struct ItemRepair{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{61};
	uint64_t                  item_guid; //��Ʒguid
	unsigned char             type; //����ʽ 1:��ͨ 2:����
	ItemRepair() = default;
};

struct ItemSeg{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{62};
	unsigned short            begin_site; //��ʼsite
	unsigned short            end_site; //����site
	ItemSeg() = default;
};

struct SkillAddReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{63};
	unsigned short            id; //����id
	SkillAddReq() = default;
};

struct SkillAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{64};
	unsigned short            num; //��������
	SKILL_INFO                info[100]; //������Ϣ
	SkillAddAck() = default;
};

struct SkillDestroyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{65};
	unsigned short            id; //����id
	SkillDestroyReq() = default;
};

struct SkillDestroyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{66};
	unsigned short            id; //����id
	SkillDestroyAck() = default;
};

struct SkillSwitch{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{67};
	unsigned short            id; //����id
	unsigned char             active; //0=������ 1=����
	SkillSwitch() = default;
};

struct SkillSwitchAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{68};
	unsigned short            id; //����id
	unsigned char             active; //0=������ 1=����
	SkillSwitchAck() = default;
};

struct SkillProficiencyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{69};
	unsigned short            id; //����id
	unsigned short            proficiency; //����������
	SkillProficiencyNtf() = default;
};

struct BuffAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{70};
	uint64_t                  role_guid; //������player/monster/npc's guid
	unsigned short            num; //Buff����
	BUFF_INFO                 info[50]; //Buff��Ϣ
	BuffAddAck() = default;
};

struct BuffDestroyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{71};
	unsigned short            id; //Buff id
	BuffDestroyReq() = default;
};

struct BuffDestroyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{72};
	uint64_t                  role_guid; //������player/monster/npc's guid
	unsigned short            id; //Buff id
	BuffDestroyAck() = default;
};

struct BuffUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{73};
	uint64_t                  role_guid; //������player/monster/npc's guid
	BUFF_INFO                 info; //Buff��Ϣ
	BuffUpdateNtf() = default;
};

struct SpellTargetReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{74};
	uint64_t                  actor; //ʩ����, ������player/monster/npc's guid
	unsigned short            id; //����id
	uint64_t                  target; //Ŀ��, ������player/monster/npc's guid
	SpellTargetReadyNtf() = default;
};

struct SpellGridReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{75};
	uint64_t                  actor; //ʩ����, ������player/monster/npc's guid
	unsigned short            id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	SpellGridReadyNtf() = default;
};

struct SpellTarget{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{76};
	unsigned short            id; //����id
	uint64_t                  target; //Ŀ��, ������player/monster/npc's guid
	unsigned short            idx; //~
	SpellTarget() = default;
};

struct SpellGrid{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{77};
	unsigned short            id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	unsigned short            idx; //~
	uint64_t                  ref_target; //����Ŀ��guid
	SpellGrid() = default;
};

struct SpellAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{78};
	unsigned short            id; //����id
	int                       ecode; //������
	char                      detail[256]; //��������
	unsigned short            idx; //~
	SpellAck() = default;
};

struct SpellNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{79};
	uint64_t                  actor; //ʩ����, ������player/monster/npc's guid
	unsigned short            id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	unsigned short            num; //��ЧĿ������
	uint64_t                  targets[50]; //Ŀ�꼯, ������player/monster/npc's guid
	SpellNtf() = default;
};

struct AttrShowNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{80};
	uint64_t                  actor; //actor, ������player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, ������player/monster/npc's guid
	unsigned char             type; //0=��ͨ 1=����
	int                       actor_hp_ref; //actor hp��ʾֵ
	int                       target_hp_ref; //Ŀ��hp��ʾֵ
	int                       target_hp; //Ŀ��hp����ֵ
	AttrShowNtf() = default;
};

struct MissNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{81};
	uint64_t                  actor; //actor, ������player/monster/npc's guid
	uint64_t                  target; //target, ������player/monster/npc's guid
	unsigned short            skill_id; //����id
	unsigned char             type; //1=���� 2=����
	MissNtf() = default;
};

struct SpellDelayLostNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{82};
	uint64_t                  actor; //ʩ����, ������player/monster/npc's guid
	unsigned short            skill_id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	SpellDelayLostNtf() = default;
};

struct SpellDelayHitNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{83};
	uint64_t                  actor; //ʩ����, ������player/monster/npc's guid
	unsigned short            skill_id; //����id
	unsigned short            num; //��ЧĿ������
	uint64_t                  targets[50]; //Ŀ�꼯, ������player/monster/npc's guid
	SpellDelayHitNtf() = default;
};

struct TradeNpcBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{84};
	unsigned short            shop_id; //shop_index
	unsigned short            item_index; //item_index
	unsigned short            item_amount; //��Ʒ����
	unsigned char             is_bind; //�Ƿ�ʹ�ð󶨽��, 1��ʹ�ã�0����ʹ��
	TradeNpcBuy() = default;
};

struct TradeNpcSell{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{85};
	uint64_t                  item_guid; //item guid
	TradeNpcSell() = default;
};

struct TradeNpcValueReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{86};
	uint64_t                  item_guid; //item guid
	TradeNpcValueReq() = default;
};

struct TradeNpcValueAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{87};
	uint64_t                  item_guid; //item guid
	int                       value; //��Ʒ�۸�
	TradeNpcValueAck() = default;
};

struct TradeNpcShopNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{88};
	unsigned short            shop_id; //shop_index
	unsigned char             item_count; //��Ʒ����
	SHOP_ITEM_INFO            item_list[250]; //��Ʒ��Ϣ�б�
	TradeNpcShopNtf() = default;
};

struct TradeP2PRequest{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{89};
	uint64_t                  responsor; //��Ӧ��GUID
	TradeP2PRequest() = default;
};

struct TradeP2PRequestNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{90};
	uint64_t                  requestor; //������GUID
	char                      requestor_name[32]; //����������
	TradeP2PRequestNtf() = default;
};

struct TradeP2PResponse{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{91};
	uint64_t                  requestor; //������GUID
	unsigned char             accepted; //�Ƿ����
	TradeP2PResponse() = default;
};

struct TradeP2POpenNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{92};
	uint64_t                  requestor; //������GUID
	uint64_t                  responsor; //��Ӧ��GUID
	char                      requestor_name[32]; //����������
	char                      responsor_name[32]; //��Ӧ������
	TradeP2POpenNtf() = default;
};

struct TradeP2PArrange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{93};
	unsigned char             remove; //true��ɾ����false�����
	uint64_t                  item_guid; //item guid
	TradeP2PArrange() = default;
};

struct TradeP2PArrangeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{94};
	uint64_t                  player_guid; //player guid
	unsigned char             remove; //true��ɾ����false�����
	uint64_t                  item_guid; //item guid
	unsigned short            item_num; //��Ʒ����
	ITEM_INFO                 item_info[1]; //��Ʒ��Ϣ
	TradeP2PArrangeNtf() = default;
};

struct TradeP2PGold{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{95};
	int64_t                   gold; //��Ǯ
	TradeP2PGold() = default;
};

struct TradeP2PGoldNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{96};
	uint64_t                  player_guid; //player guid
	int64_t                   gold; //��Ǯ
	TradeP2PGoldNtf() = default;
};

struct TradeP2PLock{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{97};
	unsigned char             locked; //�Ƿ�����
	TradeP2PLock() = default;
};

struct TradeP2PLockNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{98};
	uint64_t                  player_guid; //player guid
	unsigned char             locked; //�Ƿ�����
	TradeP2PLockNtf() = default;
};

struct TradeP2PConfirme{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{99};
	TradeP2PConfirme() = default;
};

struct TradeP2PConfirmeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{100};
	uint64_t                  player_guid; //player guid
	unsigned char             confirmed; //�Ƿ�ȷ��
	TradeP2PConfirmeNtf() = default;
};

struct TradeP2PClose{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{101};
	TradeP2PClose() = default;
};

struct TradeP2PCloseNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{102};
	uint64_t                  player_guid; //player guid
	TradeP2PCloseNtf() = default;
};

struct TradeStallReady{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{103};
	TradeStallReady() = default;
};

struct TradeStallReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{104};
	uint64_t                  player_guid; //player guid
	TradeStallReadyNtf() = default;
};

struct TradeStall{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{105};
	char                      stall_name[32]; //̯λ����
	unsigned short            item_num; //��Ʒ����
	uint64_t                  item_guids[25]; //��Ʒguid
	unsigned char             price_types[25]; //��Ʒ�۸����� 0=��� 1=Ԫ�� 2=����
	int64_t                   item_prices[25]; //��Ʒ�۸�
	TradeStall() = default;
};

struct TradeStallNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{106};
	uint64_t                  player_guid; //player guid
	char                      stall_name[32]; //̯λ����
	TradeStallNtf() = default;
};

struct TradeStallArrange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{107};
	TradeStallArrange() = default;
};

struct TradeStallQuery{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{108};
	uint64_t                  player_guid; //̯λӵ����guid
	TradeStallQuery() = default;
};

struct TradeStallQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{109};
	uint64_t                  player_guid; //player guid
	char                      stall_name[32]; //̯λ����
	unsigned short            item_num; //��Ʒ����
	int64_t                   item_prices[25]; //��Ʒ�۸�
	unsigned char             price_types[25]; //��Ʒ�۸����� 0=��� 1=Ԫ�� 2=����
	ITEM_INFO                 item_info[25]; //��Ʒ��Ϣ
	TradeStallQueryNtf() = default;
};

struct TradeStallBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{110};
	uint64_t                  player_guid; //player guid
	uint64_t                  item_guid; //item's guid
	unsigned short            item_amount; //item's amount
	TradeStallBuy() = default;
};

struct TradeStallBuyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{111};
	uint64_t                  buyer_guid; //���
	uint64_t                  seller_guid; //����
	uint64_t                  item_guid; //item's guid
	unsigned short            item_id; //��Ʒid
	unsigned short            item_amount; //item's amount
	unsigned char             price_type; //��Ʒ�۸����� 0=��� 1=Ԫ�� 2=����
	int64_t                   price; //��Ʒ�۸�
	TradeStallBuyNtf() = default;
};

struct TradeStallClose{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{112};
	TradeStallClose() = default;
};

struct TradeStallCloseNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{113};
	uint64_t                  player_guid; //player guid
	TradeStallCloseNtf() = default;
};

struct PlayerSwitch{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{114};
	unsigned char             id; //id(player_switch_type)
	unsigned char             value; //����ֵ
	PlayerSwitch() = default;
};

struct AtkModeReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{115};
	unsigned char             atk_mode; //����ģʽ
	AtkModeReq() = default;
};

struct ServantModeReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{116};
	ServantModeReq() = default;
};

struct RoleAddPoint{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{117};
	unsigned char             hp; //hp point
	unsigned char             mp; //mp point
	unsigned char             phy_atk; //physical attack point
	unsigned char             mag_atk; //magical attack point
	unsigned char             tao_atk; //taoism attack point
	unsigned char             phy_def; //physical defense point
	unsigned char             mag_def; //magical defense point
	RoleAddPoint() = default;
};

struct LevelUpNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{118};
	uint64_t                  player_guid; //player guid
	int                       level; //level
	LevelUpNtf() = default;
};

struct PlayerQuery{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{119};
	char                      player_name[128]; //�������
	PlayerQuery() = default;
};

struct PlayerQueryBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{120};
	char                      target_name[32]; //�������
	unsigned int              target_userid; //Ŀ�� userid
	PlayerQueryBrd() = default;
};

struct PlayerQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{121};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //�������
	unsigned char             gender; //�Ա�
	unsigned char             job; //ְҵ
	unsigned int              level; //�ȼ�
	char                      family_name[32]; //�л�����
	char                      family_title[32]; //�л�ƺ�
	char                      alias[64]; //����
	unsigned short            item_num; //��Ʒ����
	ITEM_INFO                 item_info[45]; //��Ʒ��Ϣ
	PlayerQueryNtf() = default;
};

struct PlayerSiteSeg{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{122};
	uint64_t                  player_guid; //player guid
	PlayerSiteSeg() = default;
};

struct PlayerSiteSegBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{123};
	uint64_t                  player_guid; //player guid
	PlayerSiteSegBrd() = default;
};

struct PlayerSiteSegNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{124};
	uint64_t                  player_guid; //player guid
	PlayerSiteSegNtf() = default;
};

struct TitleAdd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{125};
	unsigned short            title_id; //title id
	TitleAdd() = default;
};

struct TitleRemove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{126};
	unsigned short            title_id; //title id
	TitleRemove() = default;
};

struct TitleApply{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{127};
	unsigned short            title_id; //title id
	TitleApply() = default;
};

struct TitleAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{128};
	int                       title_num; //�ƺ�����
	TITLE_INFO                titles[100]; //�ƺ���Ϣ
	TitleAddAck() = default;
};

struct TitleRemoveAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{129};
	unsigned short            title_id; //title id
	TitleRemoveAck() = default;
};

struct SysMsgNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{130};
	unsigned char             msg_type; //ָ����Ϣ�����ͣ�����ȷ����Ϣ����ʾ����
	unsigned char             scroll_count; //��Ϣ�Ĺ������� Ĭ�ϣ�1��
	char                      msg[256]; //�������Ϣ����
	SysMsgNtf() = default;
};

struct RelationChatNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{131};
	unsigned char             type; //1����ǰ 2������ 3������ 4������ 12��ȫ��
	CHAT_MSG                  chat_message; //��ɫ��ΪԴ��ɫ������
	RelationChatNtf() = default;
};

struct NpcSelect{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{132};
	uint64_t                  npc_guid; //npc��GUID
	NpcSelect() = default;
};

struct NpcTalkReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{133};
	uint64_t                  npc_guid; //npc��GUID
	char                      func[256]; //ѡ��ִ�е�NPC����
	NpcTalkReq() = default;
};

struct NpcTalkAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{134};
	unsigned short            width; //NPC�Ի������Ŀ��
	unsigned short            height; //NPC�Ի������ĸ߶�
	uint64_t                  npc_guid; //npc��GUID
	unsigned short            talk_len; //NPC������ݳ���
	char                      talk[7500]; //NPC�����ʾ������
	unsigned short            quest_state_num; //����״̬��������
	QUEST_STATE_INFO          quest_states[2]; //����״̬����
	char                      comp; //�Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��
	NpcTalkAck() = default;
};

struct QuickBarSet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{135};
	unsigned char             type; //0=null 1=item 2=skill
	unsigned char             slot; //��λ
	unsigned short            id; //ģ��id
	uint64_t                  guid; //��Ʒguid
	QuickBarSet() = default;
};

struct QuickBarSetNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{136};
	unsigned short            num; //���������
	QUICK_BAR_INFO            info[30]; //�������Ϣ
	QuickBarSetNtf() = default;
};

struct QuickBarRemove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{137};
	unsigned char             slot; //��λ
	QuickBarRemove() = default;
};

struct QuickBarRemoveNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{138};
	unsigned char             slot; //��λ
	QuickBarRemoveNtf() = default;
};

struct QuickBarMove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{139};
	unsigned char             src_slot; //ԭ��λ
	unsigned char             dst_slot; //Ŀ���λ
	QuickBarMove() = default;
};

struct ShortcutSet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{140};
	unsigned short            info[16]; //��ݼ���Ϣ
	ShortcutSet() = default;
};

struct ShortcutNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{141};
	unsigned short            info[16]; //��ݼ���Ϣ
	ShortcutNtf() = default;
};

struct GoldDeposit{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{142};
	int64_t                   gold; //gold
	GoldDeposit() = default;
};

struct GoldTake{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{143};
	int64_t                   gold; //gold
	GoldTake() = default;
};

struct BeServantNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{144};
	uint64_t                  servant_guid; //���guid
	unsigned char             servant_level; //��ӵȼ�
	char                      master_name[32]; //��������
	BeServantNtf() = default;
};

struct RoleAttrExtRefNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{145};
	unsigned short            attr_name; //��������
	int64_t                   attr_value; //���Ըı����ֵ
	RoleAttrExtRefNtf() = default;
};

struct StartFamilyWarBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{146};
	char                      attack[32]; //��
	char                      defence[32]; //��
	StartFamilyWarBrd() = default;
};

struct RunningFamilyWarNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{147};
	unsigned short            num; //�����е��л�ս����
	FAMILY_WAR_INFO           families[100]; //�����е��л�ս��Ϣ
	RunningFamilyWarNtf() = default;
};

struct CastleNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{148};
	unsigned short            num; //����
	CASTLE_INFO               castles[5]; //�Ǳ���Ϣ
	CastleNtf() = default;
};

struct GoldDrop{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{149};
	int64_t                   gold; //�������
	GoldDrop() = default;
};

struct PlayerFamilyChangeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{150};
	uint64_t                  player_guid; //���guid
	char                      family_name[32]; //�л�����
	char                      castle_name[256]; //�Ǳ����ƣ����Զ��������ŷָ�
	PlayerFamilyChangeNtf() = default;
};

struct NotifyMapEffect{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{151};
	unsigned int              effect_id; //Ҫ���ŵ���Чid
	unsigned short            effect_x; //����x����
	unsigned short            effect_y; //����y����
	unsigned int              effect_life; //��Ч������
	NotifyMapEffect() = default;
};

struct RoleTalkNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{152};
	uint64_t                  role_guid; //��ɫ��GUID
	char                      msg[256]; //��Ϣ����
	RoleTalkNtf() = default;
};

struct ProgressStartNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{153};
	uint64_t                  player_guid; //���guid
	char                      desc[256]; //����������
	unsigned int              duration; //����ʱ��
	ProgressStartNtf() = default;
};

struct ProgressCancelNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{154};
	uint64_t                  player_guid; //���guid
	unsigned char             complete; //0: ȡ�� 1:���
	ProgressCancelNtf() = default;
};

struct VerifyImageQuestion{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{155};
	unsigned short            size; //ͼƬ�ļ���С
	unsigned char             buffer[4096]; //ͼƬ����
	VerifyImageQuestion() = default;
};

struct VerifyImageAnswer{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{156};
	char                      answer[16]; //�û������Ĵ�
	VerifyImageAnswer() = default;
};

struct VerifyImageReset{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{157};
	VerifyImageReset() = default;
};

struct VerifyImageResultNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{158};
	unsigned int              fail_count; //ʧ�ܵĴ���
	VerifyImageResultNtf() = default;
};

struct TradeMallBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{159};
	unsigned int              item_index; //item_index
	unsigned short            item_amount; //��Ʒ����
	TradeMallBuy() = default;
};

struct TradeMallListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{160};
	unsigned char             page_id; //��Ʒ�ķ�ҳ
	TradeMallListReq() = default;
};

struct TradeMallListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{161};
	unsigned char             page_id; //��Ʒ�ķ�ҳ
	unsigned char             item_count; //��Ʒ����
	MALL_ITEM_INFO            item_list[250]; //��Ʒ��Ϣ�б�
	TradeMallListAck() = default;
};

struct TradeMallItemDetailReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{162};
	unsigned int              item_index; //��Ʒindex
	TradeMallItemDetailReq() = default;
};

struct TradeMallItemDetailAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{163};
	MALL_ITEM_DETAIL          item; //ĳ��Ʒ��ϸ��Ϣ
	TradeMallItemDetailAck() = default;
};

struct TradeMallChartsReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{164};
	TradeMallChartsReq() = default;
};

struct TradeMallChartsAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{165};
	unsigned char             item_count; //��Ʒ����
	MALL_ITEM_INFO            item_list[5]; //��Ʒ��Ϣ�б�
	TradeMallChartsAck() = default;
};

struct NpcTalkReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{166};
	char                      func[256]; //ѡ��ִ�е�NPC����
	NpcTalkReqEx() = default;
};

struct NpcTalkAckEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{167};
	unsigned short            width; //NPC�Ի������Ŀ��
	unsigned short            height; //NPC�Ի������ĸ߶�
	unsigned short            talk_len; //NPC������ݳ���
	char                      talk[8000]; //NPC�����ʾ������
	char                      comp; //�Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��
	NpcTalkAckEx() = default;
};

struct QuestAccept{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{168};
	unsigned short            quest_id; //����ģ��id
	QuestAccept() = default;
};

struct QuestAddNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{169};
	unsigned short            quest_id; //����ģ��id
	char                      quest_name[256]; //���������
	unsigned char             quest_type; //���������, ��ʾ��
	unsigned short            group_huntings_len; //���ּ���
	QUEST_HUNTING_INFO        group_huntings[5]; //��������
	unsigned short            huntings_len; //��ּ���
	QUEST_HUNTING_INFO        huntings[5]; //�������
	unsigned short            huntlevels_len; //��ȼ��ּ���
	QUEST_HUNTLEVEL_INFO      huntlevels[5]; //��ȼ�������
	unsigned short            group_items_len; //����Ʒ�ռ�
	QUEST_ITEM_INFO           group_items[5]; //���ռ�����
	unsigned short            collect_items_len; //��Ʒ�ռ�
	QUEST_ITEM_INFO           collect_items[5]; //�ռ�����
	unsigned short            apply_items_len; //��Ʒʹ��
	QUEST_ITEM_INFO           apply_items[5]; //�ռ�ʹ��
	unsigned short            npcs_len; //Npc
	QUEST_NPC_INFO            npcs[5]; //npc����
	unsigned char             track_enabled; //�Ƿ���׷��
	unsigned int              life; //ʣ��ʱ��
	char                      progressing[256]; //�������ʱ׷���ı�
	char                      accomplishing[256]; //�������ʱ׷���ı�
	QuestAddNtf() = default;
};

struct QuestAccomplish{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{170};
	unsigned short            quest_id; //����ģ��id
	unsigned short            select_index; //���ѡ��������
	QuestAccomplish() = default;
};

struct QuestUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{171};
	unsigned short            quest_id; //����ģ��id
	int                       data_type; //��������, �ο�quest_track_state
	int                       id; //Id
	int                       value; //value
	QuestUpdateNtf() = default;
};

struct QuestTrackChange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{172};
	unsigned short            quest_id; //����ģ��id
	unsigned char             track_enabled; //�Ƿ���׷��
	QuestTrackChange() = default;
};

struct QuestTrackChangeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{173};
	unsigned short            quest_id; //����ģ��id
	unsigned char             track_enabled; //�Ƿ���׷��
	QuestTrackChangeNtf() = default;
};

struct QuestReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{174};
	unsigned short            quest_id; //����ģ��id
	QuestReadyNtf() = default;
};

struct QuestCompleteNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{175};
	unsigned short            quest_id; //����ģ��id
	QuestCompleteNtf() = default;
};

struct QuestDrop{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{176};
	unsigned short            quest_id; //����ģ��id
	QuestDrop() = default;
};

struct QuestDropNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{177};
	unsigned short            quest_id; //����ģ��id
	QuestDropNtf() = default;
};

struct QuestQueryCanAccept{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{178};
	QuestQueryCanAccept() = default;
};

struct QuestQueryCanAcceptNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{179};
	unsigned short            num; //����
	unsigned short            quests[500]; //�ɽ������б�
	QuestQueryCanAcceptNtf() = default;
};

struct DelegateSellCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{180};		// PROTO_CLIENT3_DELEGATE_SELL_CMD
	uint64_t                  item_guid; //��ƷGUID
	unsigned int              item_value; //��Ʒ����
	unsigned int              item_unit; //��Ʒ��λ����
	unsigned char             value_type; //�۸����ͣ�0����ң�1��Ԫ��
	DelegateSellCmd() = default;
};

struct DelegateBuyCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{181};		// PROTO_CLIENT3_DELEGATE_BUY_CMD
	unsigned short            item_id; //��Ʒģ��ID
	unsigned int              item_count; //��Ʒ����
	unsigned int              item_value; //��Ʒ����
	unsigned int              item_unit; //��Ʒ��λ����
	unsigned char             value_type; //�۸����ͣ�0����ң�1��Ԫ��
	DelegateBuyCmd() = default;
};

struct DelegateSellListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{182};		// PROTO_CLIENT3_DELEGATE_SELL_LIST_REQ
	unsigned int              start; //��ʼ���к�
	unsigned int              count; //��������
	unsigned short            type; //����
	unsigned short            subtype; //�ӷ���
	char                      item_name[32]; //��Ʒ���ƹ���
	unsigned char             is_reverse; //�Ƿ���
	DelegateSellListReq() = default;
};

struct DelegateSellListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{183};		// PROTO_CLIENT3_DELEGATE_SELL_LIST_ACK
	unsigned short            type; //����
	unsigned short            subtype; //�ӷ���
	unsigned int              total; //����
	unsigned int              start; //��ʼ���к�
	unsigned int              count; //��������
	DELEGATE_SELL_ITEM        items[20]; //��Ʒ�б�
	DelegateSellListAck() = default;
};

struct DelegateBuyListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{184};		// PROTO_CLIENT3_DELEGATE_BUY_LIST_REQ
	unsigned int              start; //��ʼ���к�
	unsigned int              count; //��������
	unsigned short            type; //����
	unsigned short            subtype; //�ӷ���
	char                      item_name[32]; //��Ʒ���ƹ���
	unsigned char             is_reverse; //�Ƿ���
	DelegateBuyListReq() = default;
};
/*
struct DelegateBuyListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{185};		// PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK
	unsigned short            type; //����
	unsigned short            subtype; //�ӷ���
	unsigned int              total; //����
	unsigned int              start; //��ʼ���к�
	unsigned int              count; //��������
	DELEGATE_BUY_ITEM         items[20]; //��Ʒ�б�
	DelegateBuyListAck() = default;
};
*/
struct MarketBuyCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{186};		// PROTO_CLIENT3_MARKET_BUY_CMD
	uint64_t                  trade_id; //���׺�
	unsigned int              count; //��������
	MarketBuyCmd() = default;
};

struct MarketSellCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{187};		// PROTO_CLIENT3_MARKET_SELL_CMD
	uint64_t                  trade_id; //���׺�
	uint64_t                  item_guid; //��Ʒguid
	MarketSellCmd() = default;
};

struct DelegateCancel{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{188};	// PROTO_CLIENT3_DELEGATE_CANCEL
	uint64_t                  trade_id; //���׺�
	DelegateCancel() = default;
};

struct DelegateMineReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{189};	// PROTO_CLIENT3_DELEGATE_MINE_REQ
	DelegateMineReq() = default;
};
/*
struct DelegateMineAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{190};	// PROTO_CLIENT3_DELEGATE_MINE_ACK
	unsigned int              count; //����
	DELEGATE_INFO             trade[5]; //����
	DelegateMineAck() = default;
};
*/
struct AttrShowExNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{191};
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, ������player/monster/npc's guid
	AttrShowExNtf() = default;
};

struct CampaignListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{192};
	CampaignListReq() = default;
};

struct CampaignListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{193};
	unsigned int              svr_time; //��������ǰʱ��(��)
	unsigned int              count; //�������
	CAMPAIGN_INFO             campaigns[50]; //����б�
	CampaignListAck() = default;
};

struct CampaignDetailReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{194};
	unsigned int              id; //�id
	CampaignDetailReq() = default;
};

struct CampaignDetailAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{195};
	unsigned int              id; //�id
	char                      npc[256]; //�NPC
	char                      desc[256]; //��������
	char                      award[256]; //��������
	CampaignDetailAck() = default;
};

struct InputDlgReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{196};
	unsigned int              dlg_id; //�Ի���id
	unsigned int              timeout; //����ʱ
	unsigned int              param_len; //���������ַ�����
	unsigned int              str_len; //�������ݵĳ���
	char                      str[8000]; //��������
	InputDlgReq() = default;
};

struct InputDlgAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{197};
	unsigned int              dlg_id; //�Ի���id
	unsigned int              str_len; //��������ݳ���
	char                      str[8000]; //���������
	InputDlgAck() = default;
};

struct MsgDlgReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{198};
	unsigned int              dlg_id; //�Ի���id
	unsigned int              timeout; //����ʱ
	unsigned int              str_len; //�������ݵĳ���
	char                      str[8000]; //��������
	MsgDlgReq() = default;
};

struct MsgDlgAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{199};
	unsigned int              dlg_id; //�Ի���id
	unsigned char             key; //�������ť�����
	MsgDlgAck() = default;
};

struct WebDlgNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{200};
	char                      title[256]; //��ҳ����
	char                      parm[256]; //��ҳ����
	unsigned int              url_len; //url����
	char                      url[2048]; //url
	WebDlgNtf() = default;
};

struct OpenWebPageNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{201};
	unsigned int              url_len; //url����
	char                      url[2048]; //url
	OpenWebPageNtf() = default;
};

struct GlobalNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{202};
	unsigned short            int_count; //�������ݸ���
	IntData                   int_data[256]; //����ֵ
	unsigned short            str_count; //�ַ������ݸ���
	StrData                   str_data[256]; //����ֵ
	GlobalNtf() = default;
};

struct SpeakerMsgAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{203};
	unsigned char             ret; //���ؽ�� 0���ɹ� 1��ʧ��
	int                       ecode; //������
	char                      msg[256]; //��Ϣ����
	SpeakerMsgAck() = default;
};

struct ClientKeepAlive{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{204};
	ClientKeepAlive() = default;
};

struct FamilyAllyTableNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{205};
	unsigned int              count; //����
	FAMILY_ALLY_INFO          table[MAX_ALLY_NUM]; //ͬ�˹�ϵ��
	unsigned char             type; //1�����ˣ�2������
	FamilyAllyTableNtf() = default;
};

struct PlayerCustomReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{206};
	PlayerCustomReq() = default;
};

struct PlayerCustomAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{207};
	CUSTOM_INFO               info; //�Զ�������
	PlayerCustomAck() = default;
};

struct WebPageNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{208};
	unsigned short            url_len; //url����
	char                      url[1024]; //url
	WebPageNtf() = default;
};

struct CustomNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{209};
	unsigned char             type; //0: int 1:string 255:not exist
	KEY_VALUE_PAIR            info; //Key->Value
	CustomNtf() = default;
};

struct CustomBroadcast{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{210};
	uint64_t                  player_guid; //���guid
	unsigned char             type; //0: int 1:string 255:not exist
	KEY_VALUE_PAIR            info; //Key->Value
	CustomBroadcast() = default;
};

struct ItemCustomNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{211};
	uint64_t                  role_guid; //role guid
	uint64_t                  item_guid; //item guid
	CUSTOM_INFO               info; //�Զ�������
	ItemCustomNtf() = default;
};

struct TaobaoNpcBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{212};
	unsigned short            shop_id; //shop_index
	uint64_t                  item_guid; //��Ʒguid
	TaobaoNpcBuy() = default;
};

struct TaobaoNpcShopReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{213};
	unsigned short            shop_id; //shop_index
	unsigned char             item_index; //��һ����Ʒ��������Ʒ�е�������0��ʼ
	unsigned char             item_count; //������Ʒ����
	TaobaoNpcShopReq() = default;
};

struct TaobaoNpcShopAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{214};
	unsigned short            shop_id; //shop_index
	unsigned char             total_count; //��Ʒ������
	unsigned char             item_index; //��һ����Ʒ��������Ʒ�е�������0��ʼ
	unsigned char             item_count; //��ǰ������Ʒ����
	TAOBAO_ITEM_INFO          item_list[20]; //��Ʒ��Ϣ�б�
	TaobaoNpcShopAck() = default;
};

struct RunClientScriptNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{215};
	char                      lua_name[256]; //lua�ļ���
	char                      lua_func[256]; //lua������
	char                      lua_params[256]; //lua����,��'#'�ŷָ�
	RunClientScriptNtf() = default;
};

struct ObjCustomNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{216};
	uint64_t                  obj_guid; //obj guid
	CUSTOM_INFO               info; //�Զ�������
	ObjCustomNtf() = default;
};

struct CampaignJoinNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{217};
	unsigned int              id; //�id
	CampaignJoinNtf() = default;
};

struct MapReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{218};
	MapReq() = default;
};

struct MapNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{219};
	unsigned short            count; //����
	MAP_INFO                  info[512]; //��Ϣ
	MapNtf() = default;
};

struct GridReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{220};
	char                      logic[32]; //logic
	int                       index; //index
	unsigned short            count; //count
	GridReq() = default;
};

struct GridNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{221};
	char                      logic[32]; //logic
	int                       index; //index
	unsigned short            count; //count
	unsigned int              info[1024]; //������Ϣ
	GridNtf() = default;
};

struct TableReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{222};
	TableReq() = default;
};

struct TableNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{223};
	unsigned short            count; //����
	TABLE_INFO                info[256]; //��Ϣ
	TableNtf() = default;
};

struct TableDataReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{224};
	char                      name[32]; //name
	int                       index; //index
	unsigned short            count; //count
	TableDataReq() = default;
};

struct TableDataNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{225};
	char                      name[32]; //name
	int                       index; //index
	int                       size; //�����ݴ�С
	unsigned char             buf[65536]; //������
	TableDataNtf() = default;
};

struct CampaignRunNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{226};
	unsigned int              id; //�id
	CampaignRunNtf() = default;
};

struct RideReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{227};
	unsigned char             enable; //0:���� 1:����
	RideReq() = default;
};

struct RideNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{228};
	unsigned char             enable; //0:���� 1:����
	RideNtf() = default;
};

struct PermissionReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{229};
	char                      key[256]; //key
	char                      value[256]; //value
	PermissionReq() = default;
};

struct VipItemListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{230};
	VipItemListReq() = default;
};

struct VipItemListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{231};
	unsigned short            vip_level; //��ǰvip�ȼ�
	unsigned int              remain; //��ǰVIP�ȼ�ʣ��ʱ��
	unsigned int              num; //VIP��Ʒ����
	VIP_ITEM                  items[50]; //��Ʒ��Ϣ
	VipItemListAck() = default;
};

struct VipLevelBuyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{232};
	unsigned short            vip_level; //vip�ȼ�
	VipLevelBuyReq() = default;
};

struct VipLevelBuyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{233};
	unsigned short            vip_level; //vip�ȼ�
	unsigned int              errcode; //������
	VipLevelBuyAck() = default;
};

struct VipItemBuyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{234};
	unsigned short            id; //vip��ƷID
	VipItemBuyReq() = default;
};

struct VipItemBuyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{235};
	unsigned short            id; //vip��ƷID
	unsigned int              errcode; //������
	VipItemBuyAck() = default;
};

struct VipItemApplyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{236};
	unsigned short            id; //vip��ƷID
	VipItemApplyReq() = default;
};

struct VipItemApplyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{237};
	unsigned short            id; //vip��ƷID
	unsigned int              errcode; //������
	VipItemApplyAck() = default;
};

struct VipExpireNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{238};
	unsigned short            vip_level; //��Ա�ȼ�
	VipExpireNtf() = default;
};

struct VipLevelListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{239};
	VipLevelListReq() = default;
};

struct VipLevelListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{240};
	unsigned int              num; //VIP�ȼ�����
	VIP_LEVEL                 levels[100]; //�ȼ���Ϣ
	VipLevelListAck() = default;
};

struct TradeNpcShopNumNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{241};
	unsigned short            shop_id; //shop_index
	unsigned short            item_index; //item_index
	unsigned short            item_amount; //��Ʒ����
	TradeNpcShopNumNtf() = default;
};

struct SubmitFormAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{242};
	char                      script_name[256]; //�ű�����
	char                      result[256]; //����
	SubmitFormAck() = default;
};

struct ItemAttrReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{243};
	uint64_t                  item_guid; //��ƷGUID
	unsigned int              attr_name; //��Ʒ��������
	int                       attr_value; //��Ʒ����ֵ
	ItemAttrReq() = default;
};

struct QuestStateReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{244};
	uint64_t                  npc_guid; //npc��GUID
	QuestStateReq() = default;
};

struct QuestStateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{245};
	uint64_t                  npc_guid; //npc��GUID
	QUEST_STATE_INFO          info; //����״̬������
	QuestStateNtf() = default;
};

struct QuestQueryReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{246};
	unsigned short            quest_id; //����ģ��id
	unsigned char             use_context; //�Ƿ�ʹ�������ļ��
	QuestQueryReq() = default;
};

struct QuestQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{247};
	unsigned short            quest_id; //����ģ��id
	unsigned char             result_type; //��ѯ�����ͣ������֣�0����״̬��ѯ��1��������2��δ��ɣ�3�������
	char                      quest_name[256]; //���������
	unsigned int              life; //���ʱ��
	QuestQueryNtf() = default;
};

struct GloryFinishNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{248};
	GLORY_STATE               status; //�ɾ�״̬
	GloryFinishNtf() = default;
};

struct GloryStateQuery{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{249};
	GloryStateQuery() = default;
};

struct GloryStateAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{250};
	unsigned short            count; //�ɾ͸���
	GLORY_STATE               glories[512]; //�ɾ�״̬
	GloryStateAck() = default;
};

struct GloryAwardGet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{251};
	unsigned short            id; //�ɾ͵�ģ��ID
	GloryAwardGet() = default;
};

struct TraceReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{252};
	char                      text[256]; //text
	TraceReq() = default;
};

struct QuestNpcStateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{253};
	unsigned short            npc_id; //npc id
	unsigned char             state; //0��null��1������ɽ���2������ɽӣ�3�������ѽӲ��ɽ�
	QuestNpcStateNtf() = default;
};

struct ClientKeepAliveRet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{254};
	ClientKeepAliveRet() = default;
};

struct RemoveClientNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{255};
	char                      user_name[256]; //�˺���
	RemoveClientNtf() = default;
};

struct SceneMagicAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{256};
	uint64_t                  scenemagic_guid; //scenemaigc guid
	unsigned char             resource_type; //��Դ����
	unsigned int              resource_id; //��Դid
	unsigned int              property; //����
	SceneMagicAppearNtf() = default;
};

struct DummyPackage{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{257};
	uint64_t                  dummy_guid; //dummy guid
	int                       package_len; //����
	char                      package[65535]; //����
	DummyPackage() = default;
};

struct DummyItemMove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{258};
	uint64_t                  src_guid; //Դguid
	uint64_t                  dst_guid; //Ŀ��guid
	unsigned short            dst_site; //Ŀ��site
	uint64_t                  item_guid; //��ƷGUID
	DummyItemMove() = default;
};

struct DummyControlNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{259};
	uint64_t                  dummy_guid; //guid
	unsigned char             is_open; //���ƿ���, 1���򿪣�0���ر�
	DummyControlNtf() = default;
};

struct ServantNumNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{260};
	unsigned int              num; //��������
	ServantNumNtf() = default;
};

struct DummyStateSwitchReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{261};
	uint64_t                  dummy_guid; //guid
	unsigned char             state; //��Ҫ�л���״̬��1���ͻ��˿��� 2������
	unsigned short            x; //�ػ�״̬ʱ��x����
	unsigned short            y; //�ػ�״̬ʱ��y����
	DummyStateSwitchReq() = default;
};

struct DummyStateSwitchAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{262};
	uint64_t                  dummy_guid; //guid
	int                       err_code; //�л��Ƿ�ɹ���0���ɹ� ������������
	unsigned char             state; //��ǰ״̬���μ�DummyStateSwitchReq˵��
	DummyStateSwitchAck() = default;
};

struct HeroCreateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{263};
	uint64_t                  dummy_guid; //guid
	HeroCreateNtf() = default;
};

struct HeroDestroyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{264};
	uint64_t                  dummy_guid; //guid
	HeroDestroyNtf() = default;
};

struct AutoSetOptNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{265};
	unsigned char             is_auto_fight; //�Ƿ����Զ���� 0=������ 1=����
	unsigned char             is_auto_pick; //�Ƿ����Զ����� 0=������ 1=����
	unsigned int              auto_time; //�Զ�����ʱ�� ��λ��
	AutoSetOptNtf() = default;
};

struct AutoRunBeginNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{266};
	unsigned char             opt[256]; //�һ�ѡ��
	AutoRunBeginNtf() = default;
};

struct AutoRunEndNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{267};
	AutoRunEndNtf() = default;
};

struct NetCheckNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{268};
	unsigned char             opt; //0=�ر� 1=����
	NetCheckNtf() = default;
};

struct HeroSkillSwitchReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{269};
	uint64_t                  hero_guid; //Ӣ��guid
	unsigned short            skill_id; //����id��Ϊ����鿴���н��õļ���
	unsigned char             disable; //�Ƿ���øü��ܣ�1��ʾ���ã�0��ʾ������
	HeroSkillSwitchReq() = default;
};

struct HeroSkillSwitchAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{270};
	uint64_t                  hero_guid; //Ӣ��guid
	unsigned short            skill_num; //�Ѿ����õļ�������
	unsigned short            skill_id[64]; //�Ѿ����õļ�����id(ע�⣬���Ǽ���id)
	HeroSkillSwitchAck() = default;
};

struct MoveReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{271};
	unsigned char             type; //�ƶ����� 0=�� 1=��
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned int              idx; //�ͻ������к�
	unsigned int              tick; //gate�յ��˰���tick
	MoveReqEx() = default;
};

struct SpellTargetEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{272};
	unsigned short            id; //����id
	uint64_t                  target; //Ŀ��, ������player/monster/npc's guid
	unsigned short            idx; //~
	unsigned int              tick; //gate�յ��˰���tick
	SpellTargetEx() = default;
};

struct SpellGridEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{273};
	unsigned short            id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	unsigned short            idx; //~
	uint64_t                  ref_target; //����Ŀ��guid
	unsigned int              tick; //gate�յ��˰���tick
	SpellGridEx() = default;
};

struct HeroLockTargetCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{274};
	uint64_t                  hero_guid; //Ӣ��guid
	uint64_t                  target_guid; //Ŀ��guid
	HeroLockTargetCmd() = default;
};

struct ServantStatNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{275};
	uint64_t                  servant_guid; //���guid
	unsigned char             stat; //״̬ 0=��ͨ 1=ս��
	ServantStatNtf() = default;
};

struct JointHitNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{276};
	uint64_t                  actor; //��ʩ����, ������player/dummy's guid
	uint64_t                  helper; //Э��ʩ����, ������player/dummy's guid
	unsigned short            id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	unsigned short            num; //��ЧĿ������
	uint64_t                  targets[50]; //Ŀ�꼯, ������player/monster/npc's guid
	JointHitNtf() = default;
};

struct JointHit{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{277};
	unsigned short            id; //����id
	uint64_t                  hero; //�ϻ���Ӣ��guid
	uint64_t                  target; //Ŀ��, ������player/monster/npc's guid
	JointHit() = default;
};

struct QuestAcceptEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{278};
	unsigned short            quest_id; //����ģ��id
	uint64_t                  npc_guid; //npc��GUID
	QuestAcceptEx() = default;
};

struct QuestAccomplishEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{279};
	unsigned short            quest_id; //����ģ��id
	unsigned short            select_index; //���ѡ��������
	uint64_t                  npc_guid; //npc��GUID
	QuestAccomplishEx() = default;
};

struct HeroLockTargetAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{280};
	uint64_t                  hero_guid; //Ӣ��guid
	uint64_t                  target_guid; //Ŀ��guid
	unsigned int              err; //������
	HeroLockTargetAck() = default;
};

struct ShieldActiveNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{281};
	uint64_t                  role_guid; //guid
	ShieldActiveNtf() = default;
};

struct ShieldRemoveNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{282};
	uint64_t                  role_guid; //guid
	ShieldRemoveNtf() = default;
};

struct PlayerQueryEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{283};
	uint64_t                  player_guid; //���guid
	PlayerQueryEx() = default;
};

struct PlayerQueryBrdEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{284};
	uint64_t                  target_guid; //���guid
	unsigned int              target_userid; //Ŀ�� userid
	PlayerQueryBrdEx() = default;
};

struct GSVersion{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{285};
	char                      version[256]; //�汾��
	GSVersion() = default;
};

struct UpdateCheckCode{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{286};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	UpdateCheckCode() = default;
};

struct MoveReq2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{287};
	unsigned char             type; //�ƶ����� 0=�� 1=��
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned int              idx; //�ͻ������к�
	unsigned int              tick; //gate�յ��˰���tick
	uint64_t                  check; //У����
	MoveReq2() = default;
};

struct SpellTarget2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{288};
	unsigned short            id; //����id
	uint64_t                  target; //Ŀ��, ������player/monster/npc's guid
	unsigned short            idx; //~
	unsigned int              tick; //gate�յ��˰���tick
	uint64_t                  check; //У����
	SpellTarget2() = default;
};

struct SpellGrid2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{289};
	unsigned short            id; //����id
	unsigned short            target_x; //Ŀ���߼����X����
	unsigned short            target_y; //Ŀ���߼����Y����
	unsigned short            idx; //~
	uint64_t                  ref_target; //����Ŀ��guid
	unsigned int              tick; //gate�յ��˰���tick
	uint64_t                  check; //У����
	SpellGrid2() = default;
};

struct NpcSelect2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{290};
	uint64_t                  npc_guid; //npc��GUID
	uint64_t                  check; //У����
	NpcSelect2() = default;
};

struct NpcTalkReq2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{291};
	uint64_t                  npc_guid; //npc��GUID
	char                      func[256]; //ѡ��ִ�е�NPC����
	uint64_t                  check; //У����
	NpcTalkReq2() = default;
};

struct ClientVerNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{292};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	uint64_t                  client_ver; //У����
	ClientVerNtf() = default;
};

struct ItemApply2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{293};
	uint64_t                  item_guid; //��ƷGUID
	uint64_t                  check; //У����
	ItemApply2() = default;
};

struct MonsterAppearNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{294};
	uint64_t                  monster_guid; //monster guid
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
	MonsterAppearNtf2() = default;
};

struct ItemAppearNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{295};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //ģ��id
	int                       dst_x; //Ŀ���x
	int                       dst_y; //Ŀ���y
	unsigned short            skill_id; //����id
	char                      item_name[32]; //��Ʒ����
	short                     seed; //У������
	ItemAppearNtf2() = default;
};

struct ClientKeepAliveEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{296};
	int                       seed; //У������
	short                     opt_num; //ѡ��
	int                       opt[10]; //������Ϣ
	ClientKeepAliveEx() = default;
};

struct GSVersionEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{297};
	unsigned char             version[256]; //�汾��
	GSVersionEx() = default;
};

struct ClientVerReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{298};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	ClientVerReq() = default;
};

struct NetDelayReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{299};
	unsigned int              gs_tick; //GS���ʹ�����tick
	unsigned int              gt_tick; //GT���ʹ�����tick
	unsigned int              sg_tick; //SG���ʹ�����tick
	unsigned char             ping; //�Ƿ�ping 1=��ʼ 0=����
	NetDelayReq() = default;
};

struct NetDelayAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{300};
	int                       sg_elpase; //SG�ӷ���NetDelayReq���յ�NetDelayAck�ĺ�ʱ
	int                       gt_elpase; //GT�ӷ���NetDelayReq���յ�NetDelayAck�ĺ�ʱ
	int                       gs_elpase; //GS�ӷ���NetDelayReq���յ�NetDelayAck�ĺ�ʱ
	int                       baidu_delay; //�ٶȵ���ʱ
	int                       taobao_delay; //�Ա�����ʱ
	char                      sg_id[256]; //������id
	NetDelayAck() = default;
};

struct ClientVerNtfEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{301};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	uint64_t                  client_ver; //У����
	ClientVerNtfEx() = default;
};

struct ClientVerReq2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{302};
	unsigned int              version; //�汾��
	unsigned int              data_len; //���ݳ���
	unsigned char             data[4096]; //����
	ClientVerReq2() = default;
};

struct ClientVerAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{303};
	unsigned int              version; //�汾��
	unsigned int              data_len; //���ݳ���
	unsigned char             data[4096]; //����
	ClientVerAck2() = default;
};

struct NpcTalkReq3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{304};
	uint64_t                  npc_guid; //npc��GUID
	char                      func[256]; //ѡ��ִ�е�NPC����
	unsigned char             check[32]; //У����
	NpcTalkReq3() = default;
};

struct NpcTalkAck3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{305};
	unsigned short            width; //NPC�Ի������Ŀ��
	unsigned short            height; //NPC�Ի������ĸ߶�
	uint64_t                  npc_guid; //npc��GUID
	unsigned short            talk_len; //NPC������ݳ���
	char                      talk[7500]; //NPC�����ʾ������
	unsigned short            quest_state_num; //����״̬��������
	QUEST_STATE_INFO          quest_states[2]; //����״̬����
	char                      comp; //�Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��
	unsigned char             check[32]; //У����
	NpcTalkAck3() = default;
};

struct AttrShowNtfEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{306};
	uint64_t                  actor; //actor, ������player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, ������player/monster/npc's guid
	unsigned char             type; //0=��ͨ 1=����
	int                       actor_hp_ref; //actor hp��ʾֵ
	int                       target_hp_ref; //Ŀ��hp��ʾֵ
	int                       target_hp; //Ŀ��hp����ֵ
	int                       actor_mp_ref; //actor mp��ʾֵ
	int                       target_mp_ref; //Ŀ��mp��ʾֵ
	AttrShowNtfEx() = default;
};

struct EnterGSReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{307};
	unsigned char             entertype; //�������� 0=���� 1=����
	uint64_t                  roleguid; //��ɫguid
	unsigned char             fangchenmi; //�Ƿ�������û� 1���� 0����
	unsigned char             clienttype; //�ͻ������� 0=�ͻ��� 1=ҳ�� 2=����
	EnterGSReqEx() = default;
};

struct ReloginNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{308};
	ReloginNtf() = default;
};

struct BehaviorNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{309};
	unsigned short            version; //�汾
	unsigned char             zip; //�Ƿ�ѹ��
	unsigned int              seed; //��������
	int                       size; //���������ݴ�С
	unsigned char             buf[7936]; //����������
	BehaviorNtf() = default;
};

struct FashionReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{310};
	unsigned char             enable; //0:���� 1:����
	FashionReq() = default;
};

struct FashionNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{311};
	unsigned char             enable; //0:���� 1:����
	FashionNtf() = default;
};

struct ErrorNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{312};
	char                      errmsg[256]; //��������
	ErrorNtf() = default;
};

struct NpcTalkReqEx3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{313};
	char                      func[256]; //ѡ��ִ�е�NPC����
	unsigned char             check[32]; //У����
	NpcTalkReqEx3() = default;
};

struct NpcTalkAckEx3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{314};
	unsigned short            width; //NPC�Ի������Ŀ��
	unsigned short            height; //NPC�Ի������ĸ߶�
	unsigned short            talk_len; //NPC������ݳ���
	char                      talk[8000]; //NPC�����ʾ������
	char                      comp; //�Ƿ�Ҫ�Ա����ݽ���ѹ�� 0 = ��ѹ�� 1 = ѹ��
	unsigned char             check[32]; //У����
	NpcTalkAckEx3() = default;
};

struct SubmitForm2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{315};
	char                      script_name[256]; //�ű�����
	char                      function_name[256]; //��������
	unsigned short            num; //��������
	PARAM_INFO                info[100]; //������Ϣ
	unsigned char             check[32]; //У����
	SubmitForm2() = default;
};

struct SubmitFormAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{316};
	char                      script_name[256]; //�ű�����
	char                      result[256]; //����
	unsigned char             check[32]; //У����
	SubmitFormAck2() = default;
};

struct RoleAddPointEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{317};
	int                       hp; //hp point
	int                       mp; //mp point
	int                       phy_atk; //physical attack point
	int                       mag_atk; //magical attack point
	int                       tao_atk; //taoism attack point
	int                       phy_def; //physical defense point
	int                       mag_def; //magical defense point
	RoleAddPointEx() = default;
};

struct GetClientCheckInfoReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{318};
	GetClientCheckInfoReq() = default;
};

struct GetClientCheckInfoAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{319};
	int                       seed; //У������
	short                     opt_num; //ѡ��
	int                       opt[128]; //������Ϣ
	GetClientCheckInfoAck() = default;
};

struct GetMD5CheckListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{320};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	unsigned short            md5_list_num; //md5�б���
	CHECK_BUFF                md5_list[128]; //md5�б�
	GetMD5CheckListReq() = default;
};

struct GetMD5CheckListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{321};
	unsigned short            md5_list_num; //md5�б���
	unsigned short            check_num[128]; //md5�б���
	CHECK_BUFF                md5_list[128]; //md5�б�
	GetMD5CheckListAck() = default;
};

struct DelayCloseNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{322};
	int                       delay; //�ӳٺ�����
	DelayCloseNtf() = default;
};

struct FamilyJoinInviteReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{323};
	unsigned char             action; //�������� 1=���� 2=����
	uint64_t                  family_guid; //��������л��guid
	char                      invite_name[256]; //��������л���ҵ�����
	FamilyJoinInviteReq() = default;
};

struct FamilyJoinInviteAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{324};
	unsigned char             action; //�������� 1=���� 2=����
	uint64_t                  family_guid; //��������л��guid
	char                      invite_name[256]; //��������л���ҵ�����
	unsigned char             result; //0=���� 1=������
	FamilyJoinInviteAck() = default;
};

struct FamilyRelationShipReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{325};
	unsigned char             type; //���ͣ�1�����ˣ�2���ж�
	char                      family_name[32]; //�Է��л�����
	FamilyRelationShipReq() = default;
};

struct FamilyRelationShipAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{326};
	unsigned char             type; //���ͣ�1�����ˣ�2���ж�
	char                      family_name[32]; //�Է��л�����
	unsigned char             result; //0=���� 1=������
	FamilyRelationShipAck() = default;
};

struct MonsterAppearNtf3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{327};
	uint64_t                  monster_guid; //monster guid
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
	unsigned short            attack_speed; //�����ٶ�
	CUSTOM_INFO               custom; //�Զ�������
	MonsterAppearNtf3() = default;
};

struct MonsterAppearNtf4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{328};
	uint64_t                  monster_guid; //monster guid
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
	MonsterAppearNtf4() = default;
};

struct GetAroundTeamReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{329};
	GetAroundTeamReq() = default;
};

struct GetAroundTeamAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{330};
	unsigned char             list_size; //�б��С
	TEAM_MEMBER               list_data[20]; //�б�����
	GetAroundTeamAck() = default;
};

struct MigrateRoleDataNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{331};
	uint64_t                  role_guid; //���guid
	char                      user_name[256]; //�˺���
	unsigned int              dst_zone_id; //Ŀ����id
	unsigned int              status; //1=Ǩ�ƿ�ʼ 2=Ǩ�ƽ���
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MigrateRoleDataNtf() = default;
};

struct PlayerAppearNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{332};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //����
	unsigned char             gender; //�Ա�
	unsigned char             job; //ְҵ
	unsigned char             status; //����״̬ 0=���� 1=����
	unsigned short            head; //ͷ��
	unsigned int              level; //�ȼ�
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned char             dir; //����
	unsigned short            hair; //ͷ��
	unsigned short            hair_color; //ͷ����ɫ
	unsigned short            body; //����
	unsigned short            weapon; //����
	unsigned short            wings; //���
	unsigned short            mount; //����
	unsigned short            weapon_effect; //������Ч
	unsigned short            body_effect; //������Ч
	unsigned short            mount_effect; //������Ч
	unsigned int              hp; //��ǰѪ��
	unsigned int              max_hp; //���Ѫ��
	unsigned int              mp; //��ǰmp
	unsigned int              max_mp; //���mp
	int                       pk; //pk
	unsigned short            move_speed; //�ƶ��ٶ�
	unsigned short            attack_speed; //�����ٶ�
	unsigned short            title; //�ƺ�
	unsigned char             has_team; //�Ƿ��ж���
	unsigned char             stall; //0: δ��̯ 1: ��̯׼�� 2: ��̯��
	char                      stall_name[32]; //��̯����
	unsigned short            buff_num; //Buff����
	BUFF_INFO                 buffs[50]; //Buff��Ϣ
	char                      family_name[32]; //�л�����
	char                      castle_name[256]; //�Ǳ����ƣ����Զ��������ŷָ�
	char                      family_title[32]; //�л�ƺ�
	char                      alias[64]; //����
	CUSTOM_INFO               custom; //�Զ�������
	unsigned char             appear_type; //�������� 0=������Ұ 1=���� 2=��Ծ
	unsigned short            amulet; //����
	unsigned short            equip_num; //��չװ������
	EQUIP_INFO                equips[10]; //��չװ����Ϣ
	PlayerAppearNtf2() = default;
};

struct RoleAppNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{333};
	uint64_t                  player_guid; //player guid
	unsigned short            hair; //ͷ��
	unsigned short            hair_color; //ͷ����ɫ
	unsigned short            body; //����
	unsigned short            weapon; //����
	unsigned short            wings; //���
	unsigned short            mount; //����
	unsigned short            weapon_effect; //������Ч
	unsigned short            body_effect; //������Ч
	unsigned short            mount_effect; //������Ч
	unsigned short            amulet; //����
	unsigned short            equip_num; //��չװ������
	EQUIP_INFO                equips[10]; //��չװ����Ϣ
	RoleAppNtf2() = default;
};

struct ItemBatchDestroyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{334};
	unsigned char             num; //��Ʒ����
	uint64_t                  guids[200]; //��Ʒguids
	ItemBatchDestroyNtf() = default;
};

struct SubmitForm3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{335};
	unsigned int              form_count; //������
	unsigned char             script_name[256]; //�ű�����
	unsigned char             function_name[256]; //��������
	unsigned short            num; //��������
	PARAM_INFO2               info[100]; //������Ϣ
	SubmitForm3() = default;
};

struct SubmitFormAck3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{336};
	char                      script_name[256]; //�ű�����
	char                      result[256]; //����
	SubmitFormAck3() = default;
};

struct ItemAppearNtf3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{337};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //ģ��id
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned short            skill_id; //����id
	char                      item_name[64]; //��Ʒ����
	unsigned char             is_drop; //�Ƿ��ǵ������
	ItemAppearNtf3() = default;
};

struct ItemAppearNtf4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{338};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //ģ��id
	int                       dst_x; //Ŀ���x
	int                       dst_y; //Ŀ���y
	unsigned short            skill_id; //����id
	char                      item_name[64]; //��Ʒ����
	short                     seed; //У������
	unsigned char             is_drop; //�Ƿ��ǵ������
	ItemAppearNtf4() = default;
};

struct InnerForceLevelUpReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{339};
	unsigned char             type; //0 ��һ�� 1 �������
	InnerForceLevelUpReq() = default;
};

struct InnerForceLevelUpAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{340};
	int                       errcode; //������
	char                      errmsg[256]; //��������
	InnerForceLevelUpAck() = default;
};

struct ClientFangChenMiNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{341};
	unsigned char             type; //���ͣ�0=HOUR_1 1=HOUR_2 2=HOUR_3 3=HOUR_3_H 4=HOUR_4 5=HOUR_4_H 6=HOUR_5 7=HOUR_5_1 8=HOUR_5_2 9=HOUR_5_3 10=HOUR_6
	ClientFangChenMiNtf() = default;
};

struct DelegateMineAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{342};		// PROTO_CLIENT3_DELEGATE_MINE_ACK2
	unsigned int              count_buy; //��������
	unsigned int              count_sell; //��������
	DELEGATE_BUY_ITEM2        buy_items[5];
	DELEGATE_SELL_ITEM        sell_items[5];
	DelegateMineAck2() = default;
};

struct DelegateBuyListAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{343};		// PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK2
	unsigned short            type; //����
	unsigned short            subtype; //�ӷ���
	unsigned int              total; //����
	unsigned int              start; //��ʼ���к�
	unsigned int              count; //��������
	DELEGATE_BUY_ITEM2        items[20]; //��Ʒ�б�
	DelegateBuyListAck2() = default;
};

struct FashionWeaponReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{344};
	unsigned char             enable; //0:ж�� 1:װ����
	FashionWeaponReq() = default;
};

struct FashionWeaponNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{345};
	unsigned char             enable; //0:ж�� 1:װ����
	FashionWeaponNtf() = default;
};

struct PlayerAppearNtf3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{346};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //����
	unsigned char             gender; //�Ա�
	unsigned char             job; //ְҵ
	unsigned char             status; //����״̬ 0=���� 1=����
	unsigned short            head; //ͷ��
	unsigned int              level; //�ȼ�
	unsigned short            dst_x; //Ŀ���x
	unsigned short            dst_y; //Ŀ���y
	unsigned char             dir; //����
	unsigned short            hair; //ͷ��
	unsigned short            hair_color; //ͷ����ɫ
	unsigned short            body; //����
	unsigned short            weapon; //����
	unsigned short            wings; //���
	unsigned short            mount; //����
	unsigned short            weapon_effect; //������Ч
	unsigned short            body_effect; //������Ч
	unsigned short            mount_effect; //������Ч
	unsigned int              hp; //��ǰѪ��
	unsigned int              max_hp; //���Ѫ��
	unsigned int              mp; //��ǰmp
	unsigned int              max_mp; //���mp
	int                       pk; //pk
	unsigned short            move_speed; //�ƶ��ٶ�
	unsigned short            attack_speed; //�����ٶ�
	unsigned short            title; //�ƺ�
	unsigned char             has_team; //�Ƿ��ж���
	unsigned char             stall; //0: δ��̯ 1: ��̯׼�� 2: ��̯��
	char                      stall_name[32]; //��̯����
	unsigned short            buff_num; //Buff����
	BUFF_INFO                 buffs[50]; //Buff��Ϣ
	char                      family_name[32]; //�л�����
	char                      castle_name[256]; //�Ǳ����ƣ����Զ��������ŷָ�
	char                      family_title[32]; //�л�ƺ�
	char                      alias[64]; //����
	CUSTOM_INFO               custom; //�Զ�������
	unsigned char             appear_type; //�������� 0=������Ұ 1=���� 2=��Ծ
	unsigned short            amulet; //����
	unsigned short            equip_num; //��չװ������
	EQUIP_INFO                equips[10]; //��չװ����Ϣ
	unsigned int              inner_force; //��ǰ�ڹ�
	unsigned int              max_inner_force; //����ڹ�
	unsigned short            reserve_num; //�����ֶ�����
	unsigned int              reserve_values[10]; //�����ֶ�
	PlayerAppearNtf3() = default;
};

struct MonsterAppearNtf5{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{347};
	uint64_t                  monster_guid; //monster guid
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
	unsigned short            attack_speed; //�����ٶ�
	CUSTOM_INFO               custom; //�Զ�������
	unsigned int              inner_force; //��ǰ�ڹ�
	unsigned int              max_inner_force; //����ڹ�
	unsigned short            reserve_num; //�����ֶ�����
	unsigned int              reserve_values[10]; //�����ֶ�
	MonsterAppearNtf5() = default;
};

struct MonsterAppearNtf6{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{348};
	uint64_t                  monster_guid; //monster guid
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
	unsigned short            reserve_num; //�����ֶ�����
	unsigned int              reserve_values[10]; //�����ֶ�
	MonsterAppearNtf6() = default;
};

struct CaptchaReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{349};
	unsigned short            seed; //����
	unsigned short            type; //����
	unsigned short            timeout; //����ʱ
	unsigned char             qsize; //�������ݴ�С
	char                      qvalue[256]; //��������ֵ
	unsigned short            size; //���ݴ�С
	char                      value[4096]; //����ֵ
	CaptchaReq() = default;
};

struct CaptchaAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{350};
	unsigned char             check1; //ѡ��1
	unsigned short            size1; //����1��С
	char                      value1[256]; //����1ֵ
	unsigned char             check2; //ѡ��2
	unsigned short            size2; //����2��С
	char                      value2[256]; //����2ֵ
	CaptchaAck() = default;
};

struct AgentKeyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{351};
	AgentKeyReq() = default;
};

struct AgentKeyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{352};
	char                      key[128]; //����key
	AgentKeyAck() = default;
};

struct PlatformInfoNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{353};
	char                      platform[256]; //ƽ̨����
	char                      info[4096]; //ƽ̨��Ϣ
	PlatformInfoNtf() = default;
};

struct AttrShowNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{354};
	uint64_t                  actor; //actor, ������player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, ������player/monster/npc's guid
	unsigned char             type; //0=��ͨ 1=����
	int                       actor_hp_ref; //actor hp��ʾֵ
	int                       target_hp_ref; //Ŀ��hp��ʾֵ
	int                       target_hp; //Ŀ��hp����ֵ
	int                       target_mp; //Ŀ��mp����ֵ
	unsigned char             reserve_size; //�����ֶ�����
	int                       reserve[10]; //�����ֶ�
	AttrShowNtf2() = default;
};

struct AttrShowNtfEx2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{355};
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
	int                       reserve[10]; //�����ֶ�
	AttrShowNtfEx2() = default;
};

struct BehaviorReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{356};
	unsigned int              seed; //��������
	BehaviorReq() = default;
};

struct FangChenMiNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{357};
	unsigned char             type; //0 FULL 1 HALF 2 NONE
	FangChenMiNtf() = default;
};

struct NpcShopIdsNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{358};
	uint64_t                  guid; //npc guid
	unsigned char             size; //�̵���������
	unsigned short            shops[20]; //�̵�id
	NpcShopIdsNtf() = default;
};

struct CreateMobaRoomReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{359};
	unsigned short            room_mode; //����ģʽ
	unsigned short            vs_num; //��ս�������������
	unsigned short            map_id; //��ս��ͼ��map���Ӧ����
	char                      room_pwd[256]; //��������
	char                      room_name[256]; //��������
	CreateMobaRoomReq() = default;
};

struct CreateMobaRoomAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{360};
	int                       room_id; //����ʧ��room id = 0
	int                       errcode; //������
	char                      errmsg[256]; //��������
	CreateMobaRoomAck() = default;
};

struct EnterMobaRoomReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{361};
	int                       room_id; //room id
	char                      room_pwd[256]; //��������
	EnterMobaRoomReq() = default;
};

struct EnterMobaRoomAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{362};
	int                       room_id; //room id
	int                       errcode; //������
	char                      errmsg[256]; //��������
	EnterMobaRoomAck() = default;
};

struct ExitMobaRoomReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{363};
	ExitMobaRoomReq() = default;
};

struct ExitMobaRoomAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{364};
	int                       room_id; //room id
	int                       errcode; //������
	char                      errmsg[256]; //��������
	ExitMobaRoomAck() = default;
};

struct GetMobaRoomListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{365};
	unsigned short            begin_pos; //�б������б����ʵλ�� 0Ϊ��һ������
	GetMobaRoomListReq() = default;
};

struct MobaRoomListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{366};
	unsigned short            begin_pos; //�б������б����ʵλ�� 0Ϊ��һ������
	unsigned short            all_pos; //���б�һ������λ��
	unsigned short            room_num; //�б���Ϣ�е���Ϣ��
	MOBA_ROOM_INFO            room_list[64]; //�б���Ϣ
	MobaRoomListAck() = default;
};

struct MobaRoomMemberListNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{367};
	int                       room_id; //room id
	unsigned char             member_num; //�б���Ϣ�е���Ϣ��
	MOBA_ROOM_MEMBER_INFO     member_list[256]; //�б���Ϣ
	MobaRoomMemberListNtf() = default;
};

struct GetMobaMemberListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{368};
	int                       room_id; //room id
	GetMobaMemberListReq() = default;
};

struct MobaRoomKickReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{369};
	uint64_t                  guid; //���guid
	MobaRoomKickReq() = default;
};

struct MobaRoomKickAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{370};
	uint64_t                  guid; //���guid
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomKickAck() = default;
};

struct MobaRoomKickedNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{371};
	MobaRoomKickedNtf() = default;
};

struct MobaRoomCampReadyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{372};
	MobaRoomCampReadyReq() = default;
};

struct MobaRoomCampReadyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{373};
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomCampReadyAck() = default;
};

struct MobaRoomCampReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{374};
	unsigned char             camp; //��Ӫ 1=red 2=blue
	unsigned char             yes; //0 δ׼�� 1 ��׼��
	MobaRoomCampReadyNtf() = default;
};

struct MobaRoomGameStartNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{375};
	int                       room_id; //room id
	unsigned char             success; //�ɹ���� 0 ʧ�� 1 �ɹ�
	MobaRoomGameStartNtf() = default;
};

struct MobaRoomSetViceHostReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{376};
	uint64_t                  guid; //���guid
	MobaRoomSetViceHostReq() = default;
};

struct MobaRoomSetViceHostAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{377};
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomSetViceHostAck() = default;
};

struct MobaRoomToggleCampReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{378};
	uint64_t                  guid; //���guid
	MobaRoomToggleCampReq() = default;
};

struct MobaRoomToggleCampAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{379};
	uint64_t                  guid; //���guid
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomToggleCampAck() = default;
};

struct MobaRoomDestroyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{380};
	int                       room_id; //room id
	MobaRoomDestroyNtf() = default;
};

struct MobaRoomMemberReadyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{381};
	MobaRoomMemberReadyReq() = default;
};

struct MobaRoomMemberReadyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{382};
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomMemberReadyAck() = default;
};

struct MobaRoomMemberReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{383};
	uint64_t                  guid; //���guid
	unsigned char             yes; //0 δ׼�� 1 ��׼��
	MobaRoomMemberReadyNtf() = default;
};

struct MobaRoomUpdateNameAndPasswordReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{384};
	char                      room_name[256]; //��������
	char                      room_pwd[256]; //��������
	MobaRoomUpdateNameAndPasswordReq() = default;
};

struct MobaRoomUpdateNameAndPasswordAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{385};
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomUpdateNameAndPasswordAck() = default;
};

struct MobaRoomNameUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{386};
	int                       room_id; //room id
	char                      room_name[256]; //��������
	MobaRoomNameUpdateNtf() = default;
};

struct MobaRoomChangeCampAndPosReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{387};
	unsigned char             change_camp; //�Ƿ������Ӫ
	unsigned char             pos; //���ĵ�λ��
	MobaRoomChangeCampAndPosReq() = default;
};

struct MobaRoomChangeCampAndPosAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{388};
	int                       errcode; //������
	char                      errmsg[256]; //��������
	MobaRoomChangeCampAndPosAck() = default;
};

struct ReloginRefreshReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{389};
	ReloginRefreshReq() = default;
};

struct GameGuardReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{390};
	unsigned short            size; //�����ֽ���
	unsigned char             content[4224]; //����
	GameGuardReq() = default;
};

struct GameGuardAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{391};
	unsigned short            size; //�����ֽ���
	unsigned char             content[4224]; //����
	GameGuardAck() = default;
};

struct GameGuardCheckFailedNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{392};
	GameGuardCheckFailedNtf() = default;
};

struct GameGuardHackRpt{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{393};
	unsigned short            size; //���������ֽ���
	unsigned char             content[4224]; //��������
	GameGuardHackRpt() = default;
};

struct GameGuardHeartBeat{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{394};
	unsigned int              seed; //����
	unsigned short            size; //�ֽ���
	unsigned char             content[6144]; //����
	GameGuardHeartBeat() = default;
};

struct BangcleHeartBeat{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{395};
	unsigned int              seed; //����
	unsigned short            size; //�ֽ���
	unsigned char             content[6144]; //����
	BangcleHeartBeat() = default;
};

struct TradeStallSetBuyList{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{396};
	unsigned short            buy_num; //��Ʒ��������
	unsigned short            item_ids[25]; //��Ʒģ��ID
	unsigned short            item_nums[25]; //������Ʒ�չ�����
	unsigned char             price_types[25]; //��Ʒ�۸����� 0=��� 1=Ԫ�� 2=����
	int64_t                   item_prices[25]; //��Ʒ�۸�
	TradeStallSetBuyList() = default;
};

struct TradeStallQueryBuyGoodsNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{397};
	uint64_t                  player_guid; //player guid
	unsigned short            buy_num; //��Ʒ��������
	unsigned short            item_ids[25]; //��Ʒģ��ID
	unsigned short            item_nums[25]; //������Ʒ�չ�����
	unsigned char             price_types[25]; //��Ʒ�۸����� 0=��� 1=Ԫ�� 2=����
	int64_t                   item_prices[25]; //��Ʒ�۸�
	TradeStallQueryBuyGoodsNtf() = default;
};

struct TradeStallSell{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{398};
	uint64_t                  player_guid; //player guid
	uint64_t                  item_guid; //item's guid
	unsigned short            item_amount; //item's amount
	TradeStallSell() = default;
};

struct TradeStallSellNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{399};
	uint64_t                  buyer_guid; //���
	uint64_t                  seller_guid; //����
	uint64_t                  item_guid; //item's guid
	unsigned short            item_id; //��Ʒid
	unsigned short            item_amount; //item's amount
	unsigned char             price_type; //��Ʒ�۸����� 0=��� 1=Ԫ�� 2=����
	int64_t                   price; //��Ʒ�۸�
	TradeStallSellNtf() = default;
};

struct TaobaoNpcShopReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{400};
	unsigned short            shop_id; //shop_index
	unsigned char             item_type; //��Ʒ����
	unsigned char             item_index; //��һ����Ʒ��������Ʒ�е�������0��ʼ
	unsigned char             item_count; //������Ʒ����
	TaobaoNpcShopReqEx() = default;
};

struct TaobaoNpcShopAckEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{401};
	unsigned short            shop_id; //shop_index
	unsigned char             item_type; //��Ʒ����
	unsigned char             total_count; //��Ʒ������
	unsigned char             item_index; //��һ����Ʒ��������Ʒ�е�������0��ʼ
	unsigned char             item_count; //��ǰ������Ʒ����
	TAOBAO_ITEM_INFO          item_list[20]; //��Ʒ��Ϣ�б�
	TaobaoNpcShopAckEx() = default;
};

struct SkillCDChangedNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{402};
	unsigned short            skill_id; //����ID
	unsigned int              new_cd; //������ȴʱ��
	SkillCDChangedNtf() = default;
};

struct SubmitForm4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{403};
	unsigned int              form_count; //������
	unsigned char             script_name[256]; //�ű�����
	unsigned char             function_name[256]; //��������
	unsigned short            num; //��������
	PARAM_INFO2               info[100]; //������Ϣ
	SubmitForm4() = default;
};

struct SubmitFormAck4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{404};
	char                      script_name[256]; //�ű�����
	char                      result[256]; //����
	SubmitFormAck4() = default;
};

struct QuestAddNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{405};
	unsigned short            quest_id; //����ģ��id
	char                      quest_name[256]; //���������
	unsigned char             quest_type; //���������, ��ʾ��
	unsigned short            group_huntings_len; //���ּ���
	QUEST_HUNTING_INFO        group_huntings[20]; //��������
	unsigned short            huntings_len; //��ּ���
	QUEST_HUNTING_INFO        huntings[20]; //�������
	unsigned short            huntlevels_len; //��ȼ��ּ���
	QUEST_HUNTLEVEL_INFO      huntlevels[20]; //��ȼ�������
	unsigned short            group_items_len; //����Ʒ�ռ�
	QUEST_ITEM_INFO           group_items[20]; //���ռ�����
	unsigned short            collect_items_len; //��Ʒ�ռ�
	QUEST_ITEM_INFO           collect_items[20]; //�ռ�����
	unsigned short            apply_items_len; //��Ʒʹ��
	QUEST_ITEM_INFO           apply_items[20]; //�ռ�ʹ��
	unsigned short            npcs_len; //Npc
	QUEST_NPC_INFO            npcs[20]; //npc����
	unsigned char             track_enabled; //�Ƿ���׷��
	unsigned int              life; //ʣ��ʱ��
	char                      progressing[256]; //�������ʱ׷���ı�
	char                      accomplishing[256]; //�������ʱ׷���ı�
	QuestAddNtf2() = default;
};

struct SkillCDPermenantChangedNtf { // ������ȴ��������֪ͨ
    const unsigned short      moudleid{3};
    const unsigned short      protocolid{406};
    unsigned short            skill_id; //����ID
    unsigned int              new_cd; //������ȴʱ��
    SkillCDPermenantChangedNtf() = default;
};

#pragma warning( pop ) 
//===============���ݶ������===============
//===============�������������忪ʼ===============
int EnCodeEnterGSReq(void* pHost, CNetData* poNetData);
int DeCodeEnterGSReq(void* pHost, CNetData* poNetData);
int EnCodeEnterGSAck(void* pHost, CNetData* poNetData);
int DeCodeEnterGSAck(void* pHost, CNetData* poNetData);
int EnCodeExitGSReq(void* pHost, CNetData* poNetData);
int DeCodeExitGSReq(void* pHost, CNetData* poNetData);
int EnCodeExitGSAck(void* pHost, CNetData* poNetData);
int DeCodeExitGSAck(void* pHost, CNetData* poNetData);
int EnCodeJumpGSNtf(void* pHost, CNetData* poNetData);
int DeCodeJumpGSNtf(void* pHost, CNetData* poNetData);
int EnCodeKickRoleNtf(void* pHost, CNetData* poNetData);
int DeCodeKickRoleNtf(void* pHost, CNetData* poNetData);
int EnCodeEnterMapNtf(void* pHost, CNetData* poNetData);
int DeCodeEnterMapNtf(void* pHost, CNetData* poNetData);
int EnCodeMapRegionNtf(void* pHost, CNetData* poNetData);
int DeCodeMapRegionNtf(void* pHost, CNetData* poNetData);
int EnCodeSetRelivePT(void* pHost, CNetData* poNetData);
int DeCodeSetRelivePT(void* pHost, CNetData* poNetData);
int EnCodePlayerReliveReq(void* pHost, CNetData* poNetData);
int DeCodePlayerReliveReq(void* pHost, CNetData* poNetData);
int EnCodePlayerReliveAck(void* pHost, CNetData* poNetData);
int DeCodePlayerReliveAck(void* pHost, CNetData* poNetData);
int EnCodePlayerAppearNtf(void* pHost, CNetData* poNetData);
int DeCodePlayerAppearNtf(void* pHost, CNetData* poNetData);
int EnCodeMonsterAppearNtf(void* pHost, CNetData* poNetData);
int DeCodeMonsterAppearNtf(void* pHost, CNetData* poNetData);
int EnCodeItemAppearNtf(void* pHost, CNetData* poNetData);
int DeCodeItemAppearNtf(void* pHost, CNetData* poNetData);
int EnCodeNPCAppearNtf(void* pHost, CNetData* poNetData);
int DeCodeNPCAppearNtf(void* pHost, CNetData* poNetData);
int EnCodeObjDisappearNtf(void* pHost, CNetData* poNetData);
int DeCodeObjDisappearNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerCreate(void* pHost, CNetData* poNetData);
int DeCodePlayerCreate(void* pHost, CNetData* poNetData);
int EnCodeMoveReq(void* pHost, CNetData* poNetData);
int DeCodeMoveReq(void* pHost, CNetData* poNetData);
int EnCodeMoveNtf(void* pHost, CNetData* poNetData);
int DeCodeMoveNtf(void* pHost, CNetData* poNetData);
int EnCodeMoveAck(void* pHost, CNetData* poNetData);
int DeCodeMoveAck(void* pHost, CNetData* poNetData);
int EnCodeTurnReq(void* pHost, CNetData* poNetData);
int DeCodeTurnReq(void* pHost, CNetData* poNetData);
int EnCodeTurnNtf(void* pHost, CNetData* poNetData);
int DeCodeTurnNtf(void* pHost, CNetData* poNetData);
int EnCodeTurnAck(void* pHost, CNetData* poNetData);
int DeCodeTurnAck(void* pHost, CNetData* poNetData);
int EnCodeObjDieNtf(void* pHost, CNetData* poNetData);
int DeCodeObjDieNtf(void* pHost, CNetData* poNetData);
int EnCodeChatReq(void* pHost, CNetData* poNetData);
int DeCodeChatReq(void* pHost, CNetData* poNetData);
int EnCodeGMCommandReq(void* pHost, CNetData* poNetData);
int DeCodeGMCommandReq(void* pHost, CNetData* poNetData);
int EnCodeRoleAppNtf(void* pHost, CNetData* poNetData);
int DeCodeRoleAppNtf(void* pHost, CNetData* poNetData);
int EnCodeRoleAttrNtf(void* pHost, CNetData* poNetData);
int DeCodeRoleAttrNtf(void* pHost, CNetData* poNetData);
int EnCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData);
int DeCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamMemberNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamMemberNtf(void* pHost, CNetData* poNetData);
int EnCodeShowFormNtf(void* pHost, CNetData* poNetData);
int DeCodeShowFormNtf(void* pHost, CNetData* poNetData);
int EnCodeSubmitForm(void* pHost, CNetData* poNetData);
int DeCodeSubmitForm(void* pHost, CNetData* poNetData);
int EnCodeItemAddReq(void* pHost, CNetData* poNetData);
int DeCodeItemAddReq(void* pHost, CNetData* poNetData);
int EnCodeItemAddAck(void* pHost, CNetData* poNetData);
int DeCodeItemAddAck(void* pHost, CNetData* poNetData);
int EnCodeItemDestroyReq(void* pHost, CNetData* poNetData);
int DeCodeItemDestroyReq(void* pHost, CNetData* poNetData);
int EnCodeItemDestroyAck(void* pHost, CNetData* poNetData);
int DeCodeItemDestroyAck(void* pHost, CNetData* poNetData);
int EnCodeItemMove(void* pHost, CNetData* poNetData);
int DeCodeItemMove(void* pHost, CNetData* poNetData);
int EnCodeItemSplit(void* pHost, CNetData* poNetData);
int DeCodeItemSplit(void* pHost, CNetData* poNetData);
int EnCodeItemAttrNtf(void* pHost, CNetData* poNetData);
int DeCodeItemAttrNtf(void* pHost, CNetData* poNetData);
int EnCodeItemUpdateNtf(void* pHost, CNetData* poNetData);
int DeCodeItemUpdateNtf(void* pHost, CNetData* poNetData);
int EnCodeItemBind(void* pHost, CNetData* poNetData);
int DeCodeItemBind(void* pHost, CNetData* poNetData);
int EnCodeItemApply(void* pHost, CNetData* poNetData);
int DeCodeItemApply(void* pHost, CNetData* poNetData);
int EnCodeItemApplyOnTarget(void* pHost, CNetData* poNetData);
int DeCodeItemApplyOnTarget(void* pHost, CNetData* poNetData);
int EnCodeItemApplyOnGrid(void* pHost, CNetData* poNetData);
int DeCodeItemApplyOnGrid(void* pHost, CNetData* poNetData);
int EnCodeItemArrange(void* pHost, CNetData* poNetData);
int DeCodeItemArrange(void* pHost, CNetData* poNetData);
int EnCodeItemPickUp(void* pHost, CNetData* poNetData);
int DeCodeItemPickUp(void* pHost, CNetData* poNetData);
int EnCodeItemDrop(void* pHost, CNetData* poNetData);
int DeCodeItemDrop(void* pHost, CNetData* poNetData);
int EnCodeItemTieUp(void* pHost, CNetData* poNetData);
int DeCodeItemTieUp(void* pHost, CNetData* poNetData);
int EnCodeItemTip(void* pHost, CNetData* poNetData);
int DeCodeItemTip(void* pHost, CNetData* poNetData);
int EnCodeItemTipBrd(void* pHost, CNetData* poNetData);
int DeCodeItemTipBrd(void* pHost, CNetData* poNetData);
int EnCodeItemTipNtf(void* pHost, CNetData* poNetData);
int DeCodeItemTipNtf(void* pHost, CNetData* poNetData);
int EnCodeItemEnhance(void* pHost, CNetData* poNetData);
int DeCodeItemEnhance(void* pHost, CNetData* poNetData);
int EnCodeItemDrill(void* pHost, CNetData* poNetData);
int DeCodeItemDrill(void* pHost, CNetData* poNetData);
int EnCodeItemSynthesis(void* pHost, CNetData* poNetData);
int DeCodeItemSynthesis(void* pHost, CNetData* poNetData);
int EnCodeItemEmbed(void* pHost, CNetData* poNetData);
int DeCodeItemEmbed(void* pHost, CNetData* poNetData);
int EnCodeItemDig(void* pHost, CNetData* poNetData);
int DeCodeItemDig(void* pHost, CNetData* poNetData);
int EnCodeItemIdentify(void* pHost, CNetData* poNetData);
int DeCodeItemIdentify(void* pHost, CNetData* poNetData);
int EnCodeItemRename(void* pHost, CNetData* poNetData);
int DeCodeItemRename(void* pHost, CNetData* poNetData);
int EnCodeItemRefine(void* pHost, CNetData* poNetData);
int DeCodeItemRefine(void* pHost, CNetData* poNetData);
int EnCodeItemRepairQuery(void* pHost, CNetData* poNetData);
int DeCodeItemRepairQuery(void* pHost, CNetData* poNetData);
int EnCodeItemRepairQueryNtf(void* pHost, CNetData* poNetData);
int DeCodeItemRepairQueryNtf(void* pHost, CNetData* poNetData);
int EnCodeItemRepair(void* pHost, CNetData* poNetData);
int DeCodeItemRepair(void* pHost, CNetData* poNetData);
int EnCodeItemSeg(void* pHost, CNetData* poNetData);
int DeCodeItemSeg(void* pHost, CNetData* poNetData);
int EnCodeSkillAddReq(void* pHost, CNetData* poNetData);
int DeCodeSkillAddReq(void* pHost, CNetData* poNetData);
int EnCodeSkillAddAck(void* pHost, CNetData* poNetData);
int DeCodeSkillAddAck(void* pHost, CNetData* poNetData);
int EnCodeSkillDestroyReq(void* pHost, CNetData* poNetData);
int DeCodeSkillDestroyReq(void* pHost, CNetData* poNetData);
int EnCodeSkillDestroyAck(void* pHost, CNetData* poNetData);
int DeCodeSkillDestroyAck(void* pHost, CNetData* poNetData);
int EnCodeSkillSwitch(void* pHost, CNetData* poNetData);
int DeCodeSkillSwitch(void* pHost, CNetData* poNetData);
int EnCodeSkillSwitchAck(void* pHost, CNetData* poNetData);
int DeCodeSkillSwitchAck(void* pHost, CNetData* poNetData);
int EnCodeSkillProficiencyNtf(void* pHost, CNetData* poNetData);
int DeCodeSkillProficiencyNtf(void* pHost, CNetData* poNetData);
int EnCodeBuffAddAck(void* pHost, CNetData* poNetData);
int DeCodeBuffAddAck(void* pHost, CNetData* poNetData);
int EnCodeBuffDestroyReq(void* pHost, CNetData* poNetData);
int DeCodeBuffDestroyReq(void* pHost, CNetData* poNetData);
int EnCodeBuffDestroyAck(void* pHost, CNetData* poNetData);
int DeCodeBuffDestroyAck(void* pHost, CNetData* poNetData);
int EnCodeBuffUpdateNtf(void* pHost, CNetData* poNetData);
int DeCodeBuffUpdateNtf(void* pHost, CNetData* poNetData);
int EnCodeSpellTargetReadyNtf(void* pHost, CNetData* poNetData);
int DeCodeSpellTargetReadyNtf(void* pHost, CNetData* poNetData);
int EnCodeSpellGridReadyNtf(void* pHost, CNetData* poNetData);
int DeCodeSpellGridReadyNtf(void* pHost, CNetData* poNetData);
int EnCodeSpellTarget(void* pHost, CNetData* poNetData);
int DeCodeSpellTarget(void* pHost, CNetData* poNetData);
int EnCodeSpellGrid(void* pHost, CNetData* poNetData);
int DeCodeSpellGrid(void* pHost, CNetData* poNetData);
int EnCodeSpellAck(void* pHost, CNetData* poNetData);
int DeCodeSpellAck(void* pHost, CNetData* poNetData);
int EnCodeSpellNtf(void* pHost, CNetData* poNetData);
int DeCodeSpellNtf(void* pHost, CNetData* poNetData);
int EnCodeAttrShowNtf(void* pHost, CNetData* poNetData);
int DeCodeAttrShowNtf(void* pHost, CNetData* poNetData);
int EnCodeMissNtf(void* pHost, CNetData* poNetData);
int DeCodeMissNtf(void* pHost, CNetData* poNetData);
int EnCodeSpellDelayLostNtf(void* pHost, CNetData* poNetData);
int DeCodeSpellDelayLostNtf(void* pHost, CNetData* poNetData);
int EnCodeSpellDelayHitNtf(void* pHost, CNetData* poNetData);
int DeCodeSpellDelayHitNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeNpcBuy(void* pHost, CNetData* poNetData);
int DeCodeTradeNpcBuy(void* pHost, CNetData* poNetData);
int EnCodeTradeNpcSell(void* pHost, CNetData* poNetData);
int DeCodeTradeNpcSell(void* pHost, CNetData* poNetData);
int EnCodeTradeNpcValueReq(void* pHost, CNetData* poNetData);
int DeCodeTradeNpcValueReq(void* pHost, CNetData* poNetData);
int EnCodeTradeNpcValueAck(void* pHost, CNetData* poNetData);
int DeCodeTradeNpcValueAck(void* pHost, CNetData* poNetData);
int EnCodeTradeNpcShopNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeNpcShopNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PRequest(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PRequest(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PRequestNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PRequestNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PResponse(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PResponse(void* pHost, CNetData* poNetData);
int EnCodeTradeP2POpenNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2POpenNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PArrange(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PArrange(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PArrangeNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PArrangeNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PGold(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PGold(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PGoldNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PGoldNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PLock(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PLock(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PLockNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PLockNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PConfirme(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PConfirme(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PConfirmeNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PConfirmeNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PClose(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PClose(void* pHost, CNetData* poNetData);
int EnCodeTradeP2PCloseNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeP2PCloseNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeStallReady(void* pHost, CNetData* poNetData);
int DeCodeTradeStallReady(void* pHost, CNetData* poNetData);
int EnCodeTradeStallReadyNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallReadyNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeStall(void* pHost, CNetData* poNetData);
int DeCodeTradeStall(void* pHost, CNetData* poNetData);
int EnCodeTradeStallNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeStallArrange(void* pHost, CNetData* poNetData);
int DeCodeTradeStallArrange(void* pHost, CNetData* poNetData);
int EnCodeTradeStallQuery(void* pHost, CNetData* poNetData);
int DeCodeTradeStallQuery(void* pHost, CNetData* poNetData);
int EnCodeTradeStallQueryNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallQueryNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeStallBuy(void* pHost, CNetData* poNetData);
int DeCodeTradeStallBuy(void* pHost, CNetData* poNetData);
int EnCodeTradeStallBuyNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallBuyNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeStallClose(void* pHost, CNetData* poNetData);
int DeCodeTradeStallClose(void* pHost, CNetData* poNetData);
int EnCodeTradeStallCloseNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallCloseNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerSwitch(void* pHost, CNetData* poNetData);
int DeCodePlayerSwitch(void* pHost, CNetData* poNetData);
int EnCodeAtkModeReq(void* pHost, CNetData* poNetData);
int DeCodeAtkModeReq(void* pHost, CNetData* poNetData);
int EnCodeServantModeReq(void* pHost, CNetData* poNetData);
int DeCodeServantModeReq(void* pHost, CNetData* poNetData);
int EnCodeRoleAddPoint(void* pHost, CNetData* poNetData);
int DeCodeRoleAddPoint(void* pHost, CNetData* poNetData);
int EnCodeLevelUpNtf(void* pHost, CNetData* poNetData);
int DeCodeLevelUpNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerQuery(void* pHost, CNetData* poNetData);
int DeCodePlayerQuery(void* pHost, CNetData* poNetData);
int EnCodePlayerQueryBrd(void* pHost, CNetData* poNetData);
int DeCodePlayerQueryBrd(void* pHost, CNetData* poNetData);
int EnCodePlayerQueryNtf(void* pHost, CNetData* poNetData);
int DeCodePlayerQueryNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerSiteSeg(void* pHost, CNetData* poNetData);
int DeCodePlayerSiteSeg(void* pHost, CNetData* poNetData);
int EnCodePlayerSiteSegBrd(void* pHost, CNetData* poNetData);
int DeCodePlayerSiteSegBrd(void* pHost, CNetData* poNetData);
int EnCodePlayerSiteSegNtf(void* pHost, CNetData* poNetData);
int DeCodePlayerSiteSegNtf(void* pHost, CNetData* poNetData);
int EnCodeTitleAdd(void* pHost, CNetData* poNetData);
int DeCodeTitleAdd(void* pHost, CNetData* poNetData);
int EnCodeTitleRemove(void* pHost, CNetData* poNetData);
int DeCodeTitleRemove(void* pHost, CNetData* poNetData);
int EnCodeTitleApply(void* pHost, CNetData* poNetData);
int DeCodeTitleApply(void* pHost, CNetData* poNetData);
int EnCodeTitleAddAck(void* pHost, CNetData* poNetData);
int DeCodeTitleAddAck(void* pHost, CNetData* poNetData);
int EnCodeTitleRemoveAck(void* pHost, CNetData* poNetData);
int DeCodeTitleRemoveAck(void* pHost, CNetData* poNetData);
int EnCodeSysMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeSysMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeRelationChatNtf(void* pHost, CNetData* poNetData);
int DeCodeRelationChatNtf(void* pHost, CNetData* poNetData);
int EnCodeNpcSelect(void* pHost, CNetData* poNetData);
int DeCodeNpcSelect(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkReq(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkReq(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkAck(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkAck(void* pHost, CNetData* poNetData);
int EnCodeQuickBarSet(void* pHost, CNetData* poNetData);
int DeCodeQuickBarSet(void* pHost, CNetData* poNetData);
int EnCodeQuickBarSetNtf(void* pHost, CNetData* poNetData);
int DeCodeQuickBarSetNtf(void* pHost, CNetData* poNetData);
int EnCodeQuickBarRemove(void* pHost, CNetData* poNetData);
int DeCodeQuickBarRemove(void* pHost, CNetData* poNetData);
int EnCodeQuickBarRemoveNtf(void* pHost, CNetData* poNetData);
int DeCodeQuickBarRemoveNtf(void* pHost, CNetData* poNetData);
int EnCodeQuickBarMove(void* pHost, CNetData* poNetData);
int DeCodeQuickBarMove(void* pHost, CNetData* poNetData);
int EnCodeShortcutSet(void* pHost, CNetData* poNetData);
int DeCodeShortcutSet(void* pHost, CNetData* poNetData);
int EnCodeShortcutNtf(void* pHost, CNetData* poNetData);
int DeCodeShortcutNtf(void* pHost, CNetData* poNetData);
int EnCodeGoldDeposit(void* pHost, CNetData* poNetData);
int DeCodeGoldDeposit(void* pHost, CNetData* poNetData);
int EnCodeGoldTake(void* pHost, CNetData* poNetData);
int DeCodeGoldTake(void* pHost, CNetData* poNetData);
int EnCodeBeServantNtf(void* pHost, CNetData* poNetData);
int DeCodeBeServantNtf(void* pHost, CNetData* poNetData);
int EnCodeRoleAttrExtRefNtf(void* pHost, CNetData* poNetData);
int DeCodeRoleAttrExtRefNtf(void* pHost, CNetData* poNetData);
int EnCodeStartFamilyWarBrd(void* pHost, CNetData* poNetData);
int DeCodeStartFamilyWarBrd(void* pHost, CNetData* poNetData);
int EnCodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData);
int DeCodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData);
int EnCodeCastleNtf(void* pHost, CNetData* poNetData);
int DeCodeCastleNtf(void* pHost, CNetData* poNetData);
int EnCodeGoldDrop(void* pHost, CNetData* poNetData);
int DeCodeGoldDrop(void* pHost, CNetData* poNetData);
int EnCodePlayerFamilyChangeNtf(void* pHost, CNetData* poNetData);
int DeCodePlayerFamilyChangeNtf(void* pHost, CNetData* poNetData);
int EnCodeNotifyMapEffect(void* pHost, CNetData* poNetData);
int DeCodeNotifyMapEffect(void* pHost, CNetData* poNetData);
int EnCodeRoleTalkNtf(void* pHost, CNetData* poNetData);
int DeCodeRoleTalkNtf(void* pHost, CNetData* poNetData);
int EnCodeProgressStartNtf(void* pHost, CNetData* poNetData);
int DeCodeProgressStartNtf(void* pHost, CNetData* poNetData);
int EnCodeProgressCancelNtf(void* pHost, CNetData* poNetData);
int DeCodeProgressCancelNtf(void* pHost, CNetData* poNetData);
int EnCodeVerifyImageQuestion(void* pHost, CNetData* poNetData);
int DeCodeVerifyImageQuestion(void* pHost, CNetData* poNetData);
int EnCodeVerifyImageAnswer(void* pHost, CNetData* poNetData);
int DeCodeVerifyImageAnswer(void* pHost, CNetData* poNetData);
int EnCodeVerifyImageReset(void* pHost, CNetData* poNetData);
int DeCodeVerifyImageReset(void* pHost, CNetData* poNetData);
int EnCodeVerifyImageResultNtf(void* pHost, CNetData* poNetData);
int DeCodeVerifyImageResultNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeMallBuy(void* pHost, CNetData* poNetData);
int DeCodeTradeMallBuy(void* pHost, CNetData* poNetData);
int EnCodeTradeMallListReq(void* pHost, CNetData* poNetData);
int DeCodeTradeMallListReq(void* pHost, CNetData* poNetData);
int EnCodeTradeMallListAck(void* pHost, CNetData* poNetData);
int DeCodeTradeMallListAck(void* pHost, CNetData* poNetData);
int EnCodeTradeMallItemDetailReq(void* pHost, CNetData* poNetData);
int DeCodeTradeMallItemDetailReq(void* pHost, CNetData* poNetData);
int EnCodeTradeMallItemDetailAck(void* pHost, CNetData* poNetData);
int DeCodeTradeMallItemDetailAck(void* pHost, CNetData* poNetData);
int EnCodeTradeMallChartsReq(void* pHost, CNetData* poNetData);
int DeCodeTradeMallChartsReq(void* pHost, CNetData* poNetData);
int EnCodeTradeMallChartsAck(void* pHost, CNetData* poNetData);
int DeCodeTradeMallChartsAck(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkReqEx(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkReqEx(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkAckEx(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkAckEx(void* pHost, CNetData* poNetData);
int EnCodeQuestAccept(void* pHost, CNetData* poNetData);
int DeCodeQuestAccept(void* pHost, CNetData* poNetData);
int EnCodeQuestAddNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestAddNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestAccomplish(void* pHost, CNetData* poNetData);
int DeCodeQuestAccomplish(void* pHost, CNetData* poNetData);
int EnCodeQuestUpdateNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestUpdateNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestTrackChange(void* pHost, CNetData* poNetData);
int DeCodeQuestTrackChange(void* pHost, CNetData* poNetData);
int EnCodeQuestTrackChangeNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestTrackChangeNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestReadyNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestReadyNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestCompleteNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestCompleteNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestDrop(void* pHost, CNetData* poNetData);
int DeCodeQuestDrop(void* pHost, CNetData* poNetData);
int EnCodeQuestDropNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestDropNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestQueryCanAccept(void* pHost, CNetData* poNetData);
int DeCodeQuestQueryCanAccept(void* pHost, CNetData* poNetData);
int EnCodeQuestQueryCanAcceptNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestQueryCanAcceptNtf(void* pHost, CNetData* poNetData);
int EnCodeDelegateSellCmd(void* pHost, CNetData* poNetData);
int DeCodeDelegateSellCmd(void* pHost, CNetData* poNetData);
int EnCodeDelegateBuyCmd(void* pHost, CNetData* poNetData);
int DeCodeDelegateBuyCmd(void* pHost, CNetData* poNetData);
int EnCodeDelegateSellListReq(void* pHost, CNetData* poNetData);
int DeCodeDelegateSellListReq(void* pHost, CNetData* poNetData);
int EnCodeDelegateSellListAck(void* pHost, CNetData* poNetData);
int DeCodeDelegateSellListAck(void* pHost, CNetData* poNetData);
int EnCodeDelegateBuyListReq(void* pHost, CNetData* poNetData);
int DeCodeDelegateBuyListReq(void* pHost, CNetData* poNetData);
//int EnCodeDelegateBuyListAck(void* pHost, CNetData* poNetData);
//int DeCodeDelegateBuyListAck(void* pHost, CNetData* poNetData);
int EnCodeMarketBuyCmd(void* pHost, CNetData* poNetData);
int DeCodeMarketBuyCmd(void* pHost, CNetData* poNetData);
int EnCodeMarketSellCmd(void* pHost, CNetData* poNetData);
int DeCodeMarketSellCmd(void* pHost, CNetData* poNetData);
int EnCodeDelegateCancel(void* pHost, CNetData* poNetData);
int DeCodeDelegateCancel(void* pHost, CNetData* poNetData);
int EnCodeDelegateMineReq(void* pHost, CNetData* poNetData);
int DeCodeDelegateMineReq(void* pHost, CNetData* poNetData);
//int EnCodeDelegateMineAck(void* pHost, CNetData* poNetData);
//int DeCodeDelegateMineAck(void* pHost, CNetData* poNetData);
int EnCodeAttrShowExNtf(void* pHost, CNetData* poNetData);
int DeCodeAttrShowExNtf(void* pHost, CNetData* poNetData);
int EnCodeCampaignListReq(void* pHost, CNetData* poNetData);
int DeCodeCampaignListReq(void* pHost, CNetData* poNetData);
int EnCodeCampaignListAck(void* pHost, CNetData* poNetData);
int DeCodeCampaignListAck(void* pHost, CNetData* poNetData);
int EnCodeCampaignDetailReq(void* pHost, CNetData* poNetData);
int DeCodeCampaignDetailReq(void* pHost, CNetData* poNetData);
int EnCodeCampaignDetailAck(void* pHost, CNetData* poNetData);
int DeCodeCampaignDetailAck(void* pHost, CNetData* poNetData);
int EnCodeInputDlgReq(void* pHost, CNetData* poNetData);
int DeCodeInputDlgReq(void* pHost, CNetData* poNetData);
int EnCodeInputDlgAck(void* pHost, CNetData* poNetData);
int DeCodeInputDlgAck(void* pHost, CNetData* poNetData);
int EnCodeMsgDlgReq(void* pHost, CNetData* poNetData);
int DeCodeMsgDlgReq(void* pHost, CNetData* poNetData);
int EnCodeMsgDlgAck(void* pHost, CNetData* poNetData);
int DeCodeMsgDlgAck(void* pHost, CNetData* poNetData);
int EnCodeWebDlgNtf(void* pHost, CNetData* poNetData);
int DeCodeWebDlgNtf(void* pHost, CNetData* poNetData);
int EnCodeOpenWebPageNtf(void* pHost, CNetData* poNetData);
int DeCodeOpenWebPageNtf(void* pHost, CNetData* poNetData);
int EnCodeGlobalNtf(void* pHost, CNetData* poNetData);
int DeCodeGlobalNtf(void* pHost, CNetData* poNetData);
int EnCodeSpeakerMsgAck(void* pHost, CNetData* poNetData);
int DeCodeSpeakerMsgAck(void* pHost, CNetData* poNetData);
int EnCodeClientKeepAlive(void* pHost, CNetData* poNetData);
int DeCodeClientKeepAlive(void* pHost, CNetData* poNetData);
int EnCodeFamilyAllyTableNtf(void* pHost, CNetData* poNetData);
int DeCodeFamilyAllyTableNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerCustomReq(void* pHost, CNetData* poNetData);
int DeCodePlayerCustomReq(void* pHost, CNetData* poNetData);
int EnCodePlayerCustomAck(void* pHost, CNetData* poNetData);
int DeCodePlayerCustomAck(void* pHost, CNetData* poNetData);
int EnCodeWebPageNtf(void* pHost, CNetData* poNetData);
int DeCodeWebPageNtf(void* pHost, CNetData* poNetData);
int EnCodeCustomNtf(void* pHost, CNetData* poNetData);
int DeCodeCustomNtf(void* pHost, CNetData* poNetData);
int EnCodeCustomBroadcast(void* pHost, CNetData* poNetData);
int DeCodeCustomBroadcast(void* pHost, CNetData* poNetData);
int EnCodeItemCustomNtf(void* pHost, CNetData* poNetData);
int DeCodeItemCustomNtf(void* pHost, CNetData* poNetData);
int EnCodeTaobaoNpcBuy(void* pHost, CNetData* poNetData);
int DeCodeTaobaoNpcBuy(void* pHost, CNetData* poNetData);
int EnCodeTaobaoNpcShopReq(void* pHost, CNetData* poNetData);
int DeCodeTaobaoNpcShopReq(void* pHost, CNetData* poNetData);
int EnCodeTaobaoNpcShopAck(void* pHost, CNetData* poNetData);
int DeCodeTaobaoNpcShopAck(void* pHost, CNetData* poNetData);
int EnCodeRunClientScriptNtf(void* pHost, CNetData* poNetData);
int DeCodeRunClientScriptNtf(void* pHost, CNetData* poNetData);
int EnCodeObjCustomNtf(void* pHost, CNetData* poNetData);
int DeCodeObjCustomNtf(void* pHost, CNetData* poNetData);
int EnCodeCampaignJoinNtf(void* pHost, CNetData* poNetData);
int DeCodeCampaignJoinNtf(void* pHost, CNetData* poNetData);
int EnCodeMapReq(void* pHost, CNetData* poNetData);
int DeCodeMapReq(void* pHost, CNetData* poNetData);
int EnCodeMapNtf(void* pHost, CNetData* poNetData);
int DeCodeMapNtf(void* pHost, CNetData* poNetData);
int EnCodeGridReq(void* pHost, CNetData* poNetData);
int DeCodeGridReq(void* pHost, CNetData* poNetData);
int EnCodeGridNtf(void* pHost, CNetData* poNetData);
int DeCodeGridNtf(void* pHost, CNetData* poNetData);
int EnCodeTableReq(void* pHost, CNetData* poNetData);
int DeCodeTableReq(void* pHost, CNetData* poNetData);
int EnCodeTableNtf(void* pHost, CNetData* poNetData);
int DeCodeTableNtf(void* pHost, CNetData* poNetData);
int EnCodeTableDataReq(void* pHost, CNetData* poNetData);
int DeCodeTableDataReq(void* pHost, CNetData* poNetData);
int EnCodeTableDataNtf(void* pHost, CNetData* poNetData);
int DeCodeTableDataNtf(void* pHost, CNetData* poNetData);
int EnCodeCampaignRunNtf(void* pHost, CNetData* poNetData);
int DeCodeCampaignRunNtf(void* pHost, CNetData* poNetData);
int EnCodeRideReq(void* pHost, CNetData* poNetData);
int DeCodeRideReq(void* pHost, CNetData* poNetData);
int EnCodeRideNtf(void* pHost, CNetData* poNetData);
int DeCodeRideNtf(void* pHost, CNetData* poNetData);
int EnCodePermissionReq(void* pHost, CNetData* poNetData);
int DeCodePermissionReq(void* pHost, CNetData* poNetData);
int EnCodeVipItemListReq(void* pHost, CNetData* poNetData);
int DeCodeVipItemListReq(void* pHost, CNetData* poNetData);
int EnCodeVipItemListAck(void* pHost, CNetData* poNetData);
int DeCodeVipItemListAck(void* pHost, CNetData* poNetData);
int EnCodeVipLevelBuyReq(void* pHost, CNetData* poNetData);
int DeCodeVipLevelBuyReq(void* pHost, CNetData* poNetData);
int EnCodeVipLevelBuyAck(void* pHost, CNetData* poNetData);
int DeCodeVipLevelBuyAck(void* pHost, CNetData* poNetData);
int EnCodeVipItemBuyReq(void* pHost, CNetData* poNetData);
int DeCodeVipItemBuyReq(void* pHost, CNetData* poNetData);
int EnCodeVipItemBuyAck(void* pHost, CNetData* poNetData);
int DeCodeVipItemBuyAck(void* pHost, CNetData* poNetData);
int EnCodeVipItemApplyReq(void* pHost, CNetData* poNetData);
int DeCodeVipItemApplyReq(void* pHost, CNetData* poNetData);
int EnCodeVipItemApplyAck(void* pHost, CNetData* poNetData);
int DeCodeVipItemApplyAck(void* pHost, CNetData* poNetData);
int EnCodeVipExpireNtf(void* pHost, CNetData* poNetData);
int DeCodeVipExpireNtf(void* pHost, CNetData* poNetData);
int EnCodeVipLevelListReq(void* pHost, CNetData* poNetData);
int DeCodeVipLevelListReq(void* pHost, CNetData* poNetData);
int EnCodeVipLevelListAck(void* pHost, CNetData* poNetData);
int DeCodeVipLevelListAck(void* pHost, CNetData* poNetData);
int EnCodeTradeNpcShopNumNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeNpcShopNumNtf(void* pHost, CNetData* poNetData);
int EnCodeSubmitFormAck(void* pHost, CNetData* poNetData);
int DeCodeSubmitFormAck(void* pHost, CNetData* poNetData);
int EnCodeItemAttrReq(void* pHost, CNetData* poNetData);
int DeCodeItemAttrReq(void* pHost, CNetData* poNetData);
int EnCodeQuestStateReq(void* pHost, CNetData* poNetData);
int DeCodeQuestStateReq(void* pHost, CNetData* poNetData);
int EnCodeQuestStateNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestStateNtf(void* pHost, CNetData* poNetData);
int EnCodeQuestQueryReq(void* pHost, CNetData* poNetData);
int DeCodeQuestQueryReq(void* pHost, CNetData* poNetData);
int EnCodeQuestQueryNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestQueryNtf(void* pHost, CNetData* poNetData);
int EnCodeGloryFinishNtf(void* pHost, CNetData* poNetData);
int DeCodeGloryFinishNtf(void* pHost, CNetData* poNetData);
int EnCodeGloryStateQuery(void* pHost, CNetData* poNetData);
int DeCodeGloryStateQuery(void* pHost, CNetData* poNetData);
int EnCodeGloryStateAck(void* pHost, CNetData* poNetData);
int DeCodeGloryStateAck(void* pHost, CNetData* poNetData);
int EnCodeGloryAwardGet(void* pHost, CNetData* poNetData);
int DeCodeGloryAwardGet(void* pHost, CNetData* poNetData);
int EnCodeTraceReq(void* pHost, CNetData* poNetData);
int DeCodeTraceReq(void* pHost, CNetData* poNetData);
int EnCodeQuestNpcStateNtf(void* pHost, CNetData* poNetData);
int DeCodeQuestNpcStateNtf(void* pHost, CNetData* poNetData);
int EnCodeClientKeepAliveRet(void* pHost, CNetData* poNetData);
int DeCodeClientKeepAliveRet(void* pHost, CNetData* poNetData);
int EnCodeRemoveClientNtf(void* pHost, CNetData* poNetData);
int DeCodeRemoveClientNtf(void* pHost, CNetData* poNetData);
int EnCodeSceneMagicAppearNtf(void* pHost, CNetData* poNetData);
int DeCodeSceneMagicAppearNtf(void* pHost, CNetData* poNetData);
int EnCodeDummyPackage(void* pHost, CNetData* poNetData);
int DeCodeDummyPackage(void* pHost, CNetData* poNetData);
int EnCodeDummyItemMove(void* pHost, CNetData* poNetData);
int DeCodeDummyItemMove(void* pHost, CNetData* poNetData);
int EnCodeDummyControlNtf(void* pHost, CNetData* poNetData);
int DeCodeDummyControlNtf(void* pHost, CNetData* poNetData);
int EnCodeServantNumNtf(void* pHost, CNetData* poNetData);
int DeCodeServantNumNtf(void* pHost, CNetData* poNetData);
int EnCodeDummyStateSwitchReq(void* pHost, CNetData* poNetData);
int DeCodeDummyStateSwitchReq(void* pHost, CNetData* poNetData);
int EnCodeDummyStateSwitchAck(void* pHost, CNetData* poNetData);
int DeCodeDummyStateSwitchAck(void* pHost, CNetData* poNetData);
int EnCodeHeroCreateNtf(void* pHost, CNetData* poNetData);
int DeCodeHeroCreateNtf(void* pHost, CNetData* poNetData);
int EnCodeHeroDestroyNtf(void* pHost, CNetData* poNetData);
int DeCodeHeroDestroyNtf(void* pHost, CNetData* poNetData);
int EnCodeAutoSetOptNtf(void* pHost, CNetData* poNetData);
int DeCodeAutoSetOptNtf(void* pHost, CNetData* poNetData);
int EnCodeAutoRunBeginNtf(void* pHost, CNetData* poNetData);
int DeCodeAutoRunBeginNtf(void* pHost, CNetData* poNetData);
int EnCodeAutoRunEndNtf(void* pHost, CNetData* poNetData);
int DeCodeAutoRunEndNtf(void* pHost, CNetData* poNetData);
int EnCodeNetCheckNtf(void* pHost, CNetData* poNetData);
int DeCodeNetCheckNtf(void* pHost, CNetData* poNetData);
int EnCodeHeroSkillSwitchReq(void* pHost, CNetData* poNetData);
int DeCodeHeroSkillSwitchReq(void* pHost, CNetData* poNetData);
int EnCodeHeroSkillSwitchAck(void* pHost, CNetData* poNetData);
int DeCodeHeroSkillSwitchAck(void* pHost, CNetData* poNetData);
int EnCodeMoveReqEx(void* pHost, CNetData* poNetData);
int DeCodeMoveReqEx(void* pHost, CNetData* poNetData);
int EnCodeSpellTargetEx(void* pHost, CNetData* poNetData);
int DeCodeSpellTargetEx(void* pHost, CNetData* poNetData);
int EnCodeSpellGridEx(void* pHost, CNetData* poNetData);
int DeCodeSpellGridEx(void* pHost, CNetData* poNetData);
int EnCodeHeroLockTargetCmd(void* pHost, CNetData* poNetData);
int DeCodeHeroLockTargetCmd(void* pHost, CNetData* poNetData);
int EnCodeServantStatNtf(void* pHost, CNetData* poNetData);
int DeCodeServantStatNtf(void* pHost, CNetData* poNetData);
int EnCodeJointHitNtf(void* pHost, CNetData* poNetData);
int DeCodeJointHitNtf(void* pHost, CNetData* poNetData);
int EnCodeJointHit(void* pHost, CNetData* poNetData);
int DeCodeJointHit(void* pHost, CNetData* poNetData);
int EnCodeQuestAcceptEx(void* pHost, CNetData* poNetData);
int DeCodeQuestAcceptEx(void* pHost, CNetData* poNetData);
int EnCodeQuestAccomplishEx(void* pHost, CNetData* poNetData);
int DeCodeQuestAccomplishEx(void* pHost, CNetData* poNetData);
int EnCodeHeroLockTargetAck(void* pHost, CNetData* poNetData);
int DeCodeHeroLockTargetAck(void* pHost, CNetData* poNetData);
int EnCodeShieldActiveNtf(void* pHost, CNetData* poNetData);
int DeCodeShieldActiveNtf(void* pHost, CNetData* poNetData);
int EnCodeShieldRemoveNtf(void* pHost, CNetData* poNetData);
int DeCodeShieldRemoveNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerQueryEx(void* pHost, CNetData* poNetData);
int DeCodePlayerQueryEx(void* pHost, CNetData* poNetData);
int EnCodePlayerQueryBrdEx(void* pHost, CNetData* poNetData);
int DeCodePlayerQueryBrdEx(void* pHost, CNetData* poNetData);
int EnCodeGSVersion(void* pHost, CNetData* poNetData);
int DeCodeGSVersion(void* pHost, CNetData* poNetData);
int EnCodeUpdateCheckCode(void* pHost, CNetData* poNetData);
int DeCodeUpdateCheckCode(void* pHost, CNetData* poNetData);
int EnCodeMoveReq2(void* pHost, CNetData* poNetData);
int DeCodeMoveReq2(void* pHost, CNetData* poNetData);
int EnCodeSpellTarget2(void* pHost, CNetData* poNetData);
int DeCodeSpellTarget2(void* pHost, CNetData* poNetData);
int EnCodeSpellGrid2(void* pHost, CNetData* poNetData);
int DeCodeSpellGrid2(void* pHost, CNetData* poNetData);
int EnCodeNpcSelect2(void* pHost, CNetData* poNetData);
int DeCodeNpcSelect2(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkReq2(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkReq2(void* pHost, CNetData* poNetData);
int EnCodeClientVerNtf(void* pHost, CNetData* poNetData);
int DeCodeClientVerNtf(void* pHost, CNetData* poNetData);
int EnCodeItemApply2(void* pHost, CNetData* poNetData);
int DeCodeItemApply2(void* pHost, CNetData* poNetData);
int EnCodeMonsterAppearNtf2(void* pHost, CNetData* poNetData);
int DeCodeMonsterAppearNtf2(void* pHost, CNetData* poNetData);
int EnCodeItemAppearNtf2(void* pHost, CNetData* poNetData);
int DeCodeItemAppearNtf2(void* pHost, CNetData* poNetData);
int EnCodeClientKeepAliveEx(void* pHost, CNetData* poNetData);
int DeCodeClientKeepAliveEx(void* pHost, CNetData* poNetData);
int EnCodeGSVersionEx(void* pHost, CNetData* poNetData);
int DeCodeGSVersionEx(void* pHost, CNetData* poNetData);
int EnCodeClientVerReq(void* pHost, CNetData* poNetData);
int DeCodeClientVerReq(void* pHost, CNetData* poNetData);
int EnCodeNetDelayReq(void* pHost, CNetData* poNetData);
int DeCodeNetDelayReq(void* pHost, CNetData* poNetData);
int EnCodeNetDelayAck(void* pHost, CNetData* poNetData);
int DeCodeNetDelayAck(void* pHost, CNetData* poNetData);
int EnCodeClientVerNtfEx(void* pHost, CNetData* poNetData);
int DeCodeClientVerNtfEx(void* pHost, CNetData* poNetData);
int EnCodeClientVerReq2(void* pHost, CNetData* poNetData);
int DeCodeClientVerReq2(void* pHost, CNetData* poNetData);
int EnCodeClientVerAck2(void* pHost, CNetData* poNetData);
int DeCodeClientVerAck2(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkReq3(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkReq3(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkAck3(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkAck3(void* pHost, CNetData* poNetData);
int EnCodeAttrShowNtfEx(void* pHost, CNetData* poNetData);
int DeCodeAttrShowNtfEx(void* pHost, CNetData* poNetData);
int EnCodeEnterGSReqEx(void* pHost, CNetData* poNetData);
int DeCodeEnterGSReqEx(void* pHost, CNetData* poNetData);
int EnCodeReloginNtf(void* pHost, CNetData* poNetData);
int DeCodeReloginNtf(void* pHost, CNetData* poNetData);
int EnCodeBehaviorNtf(void* pHost, CNetData* poNetData);
int DeCodeBehaviorNtf(void* pHost, CNetData* poNetData);
int EnCodeFashionReq(void* pHost, CNetData* poNetData);
int DeCodeFashionReq(void* pHost, CNetData* poNetData);
int EnCodeFashionNtf(void* pHost, CNetData* poNetData);
int DeCodeFashionNtf(void* pHost, CNetData* poNetData);
int EnCodeErrorNtf(void* pHost, CNetData* poNetData);
int DeCodeErrorNtf(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkReqEx3(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkReqEx3(void* pHost, CNetData* poNetData);
int EnCodeNpcTalkAckEx3(void* pHost, CNetData* poNetData);
int DeCodeNpcTalkAckEx3(void* pHost, CNetData* poNetData);
int EnCodeSubmitForm2(void* pHost, CNetData* poNetData);
int DeCodeSubmitForm2(void* pHost, CNetData* poNetData);
int EnCodeSubmitFormAck2(void* pHost, CNetData* poNetData);
int DeCodeSubmitFormAck2(void* pHost, CNetData* poNetData);
int EnCodeRoleAddPointEx(void* pHost, CNetData* poNetData);
int DeCodeRoleAddPointEx(void* pHost, CNetData* poNetData);
int EnCodeGetClientCheckInfoReq(void* pHost, CNetData* poNetData);
int DeCodeGetClientCheckInfoReq(void* pHost, CNetData* poNetData);
int EnCodeGetClientCheckInfoAck(void* pHost, CNetData* poNetData);
int DeCodeGetClientCheckInfoAck(void* pHost, CNetData* poNetData);
int EnCodeGetMD5CheckListReq(void* pHost, CNetData* poNetData);
int DeCodeGetMD5CheckListReq(void* pHost, CNetData* poNetData);
int EnCodeGetMD5CheckListAck(void* pHost, CNetData* poNetData);
int DeCodeGetMD5CheckListAck(void* pHost, CNetData* poNetData);
int EnCodeDelayCloseNtf(void* pHost, CNetData* poNetData);
int DeCodeDelayCloseNtf(void* pHost, CNetData* poNetData);
int EnCodeFamilyJoinInviteReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyJoinInviteReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyJoinInviteAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyJoinInviteAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyRelationShipReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyRelationShipReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyRelationShipAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyRelationShipAck(void* pHost, CNetData* poNetData);
int EnCodeMonsterAppearNtf3(void* pHost, CNetData* poNetData);
int DeCodeMonsterAppearNtf3(void* pHost, CNetData* poNetData);
int EnCodeMonsterAppearNtf4(void* pHost, CNetData* poNetData);
int DeCodeMonsterAppearNtf4(void* pHost, CNetData* poNetData);
int EnCodeGetAroundTeamReq(void* pHost, CNetData* poNetData);
int DeCodeGetAroundTeamReq(void* pHost, CNetData* poNetData);
int EnCodeGetAroundTeamAck(void* pHost, CNetData* poNetData);
int DeCodeGetAroundTeamAck(void* pHost, CNetData* poNetData);
int EnCodeMigrateRoleDataNtf(void* pHost, CNetData* poNetData);
int DeCodeMigrateRoleDataNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerAppearNtf2(void* pHost, CNetData* poNetData);
int DeCodePlayerAppearNtf2(void* pHost, CNetData* poNetData);
int EnCodeRoleAppNtf2(void* pHost, CNetData* poNetData);
int DeCodeRoleAppNtf2(void* pHost, CNetData* poNetData);
int EnCodeItemBatchDestroyNtf(void* pHost, CNetData* poNetData);
int DeCodeItemBatchDestroyNtf(void* pHost, CNetData* poNetData);
int EnCodeSubmitForm3(void* pHost, CNetData* poNetData);
int DeCodeSubmitForm3(void* pHost, CNetData* poNetData);
int EnCodeSubmitFormAck3(void* pHost, CNetData* poNetData);
int DeCodeSubmitFormAck3(void* pHost, CNetData* poNetData);
int EnCodeItemAppearNtf3(void* pHost, CNetData* poNetData);
int DeCodeItemAppearNtf3(void* pHost, CNetData* poNetData);
int EnCodeItemAppearNtf4(void* pHost, CNetData* poNetData);
int DeCodeItemAppearNtf4(void* pHost, CNetData* poNetData);
int EnCodeInnerForceLevelUpReq(void* pHost, CNetData* poNetData);
int DeCodeInnerForceLevelUpReq(void* pHost, CNetData* poNetData);
int EnCodeInnerForceLevelUpAck(void* pHost, CNetData* poNetData);
int DeCodeInnerForceLevelUpAck(void* pHost, CNetData* poNetData);
int EnCodeClientFangChenMiNtf(void* pHost, CNetData* poNetData);
int DeCodeClientFangChenMiNtf(void* pHost, CNetData* poNetData);
int EnCodeDelegateMineAck2(void* pHost, CNetData* poNetData);
int DeCodeDelegateMineAck2(void* pHost, CNetData* poNetData);
int EnCodeDelegateBuyListAck2(void* pHost, CNetData* poNetData);
int DeCodeDelegateBuyListAck2(void* pHost, CNetData* poNetData);
int EnCodeFashionWeaponReq(void* pHost, CNetData* poNetData);
int DeCodeFashionWeaponReq(void* pHost, CNetData* poNetData);
int EnCodeFashionWeaponNtf(void* pHost, CNetData* poNetData);
int DeCodeFashionWeaponNtf(void* pHost, CNetData* poNetData);
int EnCodePlayerAppearNtf3(void* pHost, CNetData* poNetData);
int DeCodePlayerAppearNtf3(void* pHost, CNetData* poNetData);
int EnCodeMonsterAppearNtf5(void* pHost, CNetData* poNetData);
int DeCodeMonsterAppearNtf5(void* pHost, CNetData* poNetData);
int EnCodeMonsterAppearNtf6(void* pHost, CNetData* poNetData);
int DeCodeMonsterAppearNtf6(void* pHost, CNetData* poNetData);
int EnCodeCaptchaReq(void* pHost, CNetData* poNetData);
int DeCodeCaptchaReq(void* pHost, CNetData* poNetData);
int EnCodeCaptchaAck(void* pHost, CNetData* poNetData);
int DeCodeCaptchaAck(void* pHost, CNetData* poNetData);
int EnCodeAgentKeyReq(void* pHost, CNetData* poNetData);
int DeCodeAgentKeyReq(void* pHost, CNetData* poNetData);
int EnCodeAgentKeyAck(void* pHost, CNetData* poNetData);
int DeCodeAgentKeyAck(void* pHost, CNetData* poNetData);
int EnCodePlatformInfoNtf(void* pHost, CNetData* poNetData);
int DeCodePlatformInfoNtf(void* pHost, CNetData* poNetData);
int EnCodeAttrShowNtf2(void* pHost, CNetData* poNetData);
int DeCodeAttrShowNtf2(void* pHost, CNetData* poNetData);
int EnCodeAttrShowNtfEx2(void* pHost, CNetData* poNetData);
int DeCodeAttrShowNtfEx2(void* pHost, CNetData* poNetData);
int EnCodeBehaviorReq(void* pHost, CNetData* poNetData);
int DeCodeBehaviorReq(void* pHost, CNetData* poNetData);
int EnCodeFangChenMiNtf(void* pHost, CNetData* poNetData);
int DeCodeFangChenMiNtf(void* pHost, CNetData* poNetData);
int EnCodeNpcShopIdsNtf(void* pHost, CNetData* poNetData);
int DeCodeNpcShopIdsNtf(void* pHost, CNetData* poNetData);
int EnCodeCreateMobaRoomReq(void* pHost, CNetData* poNetData);
int DeCodeCreateMobaRoomReq(void* pHost, CNetData* poNetData);
int EnCodeCreateMobaRoomAck(void* pHost, CNetData* poNetData);
int DeCodeCreateMobaRoomAck(void* pHost, CNetData* poNetData);
int EnCodeEnterMobaRoomReq(void* pHost, CNetData* poNetData);
int DeCodeEnterMobaRoomReq(void* pHost, CNetData* poNetData);
int EnCodeEnterMobaRoomAck(void* pHost, CNetData* poNetData);
int DeCodeEnterMobaRoomAck(void* pHost, CNetData* poNetData);
int EnCodeExitMobaRoomReq(void* pHost, CNetData* poNetData);
int DeCodeExitMobaRoomReq(void* pHost, CNetData* poNetData);
int EnCodeExitMobaRoomAck(void* pHost, CNetData* poNetData);
int DeCodeExitMobaRoomAck(void* pHost, CNetData* poNetData);
int EnCodeGetMobaRoomListReq(void* pHost, CNetData* poNetData);
int DeCodeGetMobaRoomListReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomListAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomListAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomMemberListNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomMemberListNtf(void* pHost, CNetData* poNetData);
int EnCodeGetMobaMemberListReq(void* pHost, CNetData* poNetData);
int DeCodeGetMobaMemberListReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomKickReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomKickReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomKickAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomKickAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomKickedNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomKickedNtf(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomCampReadyReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomCampReadyReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomCampReadyAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomCampReadyAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomCampReadyNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomCampReadyNtf(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomGameStartNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomGameStartNtf(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomSetViceHostReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomSetViceHostReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomSetViceHostAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomSetViceHostAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomToggleCampReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomToggleCampReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomToggleCampAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomToggleCampAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomDestroyNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomDestroyNtf(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomMemberReadyReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomMemberReadyReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomMemberReadyAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomMemberReadyAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomMemberReadyNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomMemberReadyNtf(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomUpdateNameAndPasswordReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomUpdateNameAndPasswordReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomUpdateNameAndPasswordAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomUpdateNameAndPasswordAck(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomNameUpdateNtf(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomNameUpdateNtf(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomChangeCampAndPosReq(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomChangeCampAndPosReq(void* pHost, CNetData* poNetData);
int EnCodeMobaRoomChangeCampAndPosAck(void* pHost, CNetData* poNetData);
int DeCodeMobaRoomChangeCampAndPosAck(void* pHost, CNetData* poNetData);
int EnCodeReloginRefreshReq(void* pHost, CNetData* poNetData);
int DeCodeReloginRefreshReq(void* pHost, CNetData* poNetData);
int EnCodeGameGuardReq(void* pHost, CNetData* poNetData);
int DeCodeGameGuardReq(void* pHost, CNetData* poNetData);
int EnCodeGameGuardAck(void* pHost, CNetData* poNetData);
int DeCodeGameGuardAck(void* pHost, CNetData* poNetData);
int EnCodeGameGuardCheckFailedNtf(void* pHost, CNetData* poNetData);
int DeCodeGameGuardCheckFailedNtf(void* pHost, CNetData* poNetData);
int EnCodeGameGuardHackRpt(void* pHost, CNetData* poNetData);
int DeCodeGameGuardHackRpt(void* pHost, CNetData* poNetData);
int EnCodeGameGuardHeartBeat(void* pHost, CNetData* poNetData);
int DeCodeGameGuardHeartBeat(void* pHost, CNetData* poNetData);
int EnCodeBangcleHeartBeat(void* pHost, CNetData* poNetData);
int DeCodeBangcleHeartBeat(void* pHost, CNetData* poNetData);
int EnCodeTradeStallSetBuyList(void* pHost, CNetData* poNetData);
int DeCodeTradeStallSetBuyList(void* pHost, CNetData* poNetData);
int EnCodeTradeStallQueryBuyGoodsNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallQueryBuyGoodsNtf(void* pHost, CNetData* poNetData);
int EnCodeTradeStallSell(void* pHost, CNetData* poNetData);
int DeCodeTradeStallSell(void* pHost, CNetData* poNetData);
int EnCodeTradeStallSellNtf(void* pHost, CNetData* poNetData);
int DeCodeTradeStallSellNtf(void* pHost, CNetData* poNetData);
int EnCodeTaobaoNpcShopReqEx(void* pHost, CNetData* poNetData);
int DeCodeTaobaoNpcShopReqEx(void* pHost, CNetData* poNetData);
int EnCodeTaobaoNpcShopAckEx(void* pHost, CNetData* poNetData);
int DeCodeTaobaoNpcShopAckEx(void* pHost, CNetData* poNetData);
int EnCodeSkillCDChangedNtf(void* pHost, CNetData* poNetData);
int DeCodeSkillCDChangedNtf(void* pHost, CNetData* poNetData);
int EnCodeSubmitForm4(void* pHost, CNetData* poNetData);
int DeCodeSubmitForm4(void* pHost, CNetData* poNetData);
int EnCodeSubmitFormAck4(void* pHost, CNetData* poNetData);
int DeCodeSubmitFormAck4(void* pHost, CNetData* poNetData);
int EnCodeQuestAddNtf2(void* pHost, CNetData* poNetData);
int DeCodeQuestAddNtf2(void* pHost, CNetData* poNetData);
int EnCodeSkillCDPermenantChangedNtf(void* pHost, CNetData* poNetData);
int DeCodeSkillCDPermenantChangedNtf(void* pHost, CNetData* poNetData);
//===============�����������������===============
using EnCodeFuncClientGS = int (*)(void *pHost, CNetData* poNetData);
using DeCodeFuncClientGS = int (*)(void *pHost, CNetData* poNetData);

class CClientGS
{
public:
	CClientGS();
	~CClientGS();
	int BuildProtocol(void* pHost, char *pNet, int iNetSize);

	bool HandleProtocol(char *pNet, int iNetSize, void* pHost);

	static inline unsigned short GetModuleID(){ return 3; }

	static inline unsigned short GetProtocolNum(){ return 407; }

	static const unsigned short module_id = 3;

	static const unsigned short protocol_num = 407;

//===============����Э��ص�������Ҫʹ������ʵ��===============
	virtual void OnRecv_EnterGSReq(EnterGSReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EnterGSAck(EnterGSAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ExitGSReq(ExitGSReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ExitGSAck(ExitGSAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_JumpGSNtf(JumpGSNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_KickRoleNtf(KickRoleNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EnterMapNtf(EnterMapNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MapRegionNtf(MapRegionNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SetRelivePT(SetRelivePT& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerReliveReq(PlayerReliveReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerReliveAck(PlayerReliveAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerAppearNtf(PlayerAppearNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MonsterAppearNtf(MonsterAppearNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAppearNtf(ItemAppearNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NPCAppearNtf(NPCAppearNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ObjDisappearNtf(ObjDisappearNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerCreate(PlayerCreate& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MoveReq(MoveReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MoveNtf(MoveNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MoveAck(MoveAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TurnReq(TurnReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TurnNtf(TurnNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TurnAck(TurnAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ObjDieNtf(ObjDieNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ChatReq(ChatReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GMCommandReq(GMCommandReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAppNtf(RoleAppNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAttrNtf(RoleAttrNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAttrExtNtf(RoleAttrExtNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamMemberNtf(TeamMemberNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ShowFormNtf(ShowFormNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitForm(SubmitForm& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAddReq(ItemAddReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAddAck(ItemAddAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemDestroyReq(ItemDestroyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemDestroyAck(ItemDestroyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemMove(ItemMove& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemSplit(ItemSplit& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAttrNtf(ItemAttrNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemUpdateNtf(ItemUpdateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemBind(ItemBind& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemApply(ItemApply& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemApplyOnTarget(ItemApplyOnTarget& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemApplyOnGrid(ItemApplyOnGrid& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemArrange(ItemArrange& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemPickUp(ItemPickUp& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemDrop(ItemDrop& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemTieUp(ItemTieUp& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemTip(ItemTip& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemTipBrd(ItemTipBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemTipNtf(ItemTipNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemEnhance(ItemEnhance& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemDrill(ItemDrill& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemSynthesis(ItemSynthesis& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemEmbed(ItemEmbed& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemDig(ItemDig& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemIdentify(ItemIdentify& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemRename(ItemRename& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemRefine(ItemRefine& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemRepairQuery(ItemRepairQuery& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemRepairQueryNtf(ItemRepairQueryNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemRepair(ItemRepair& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemSeg(ItemSeg& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillAddReq(SkillAddReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillAddAck(SkillAddAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillDestroyReq(SkillDestroyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillDestroyAck(SkillDestroyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillSwitch(SkillSwitch& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillSwitchAck(SkillSwitchAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillProficiencyNtf(SkillProficiencyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BuffAddAck(BuffAddAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BuffDestroyReq(BuffDestroyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BuffDestroyAck(BuffDestroyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BuffUpdateNtf(BuffUpdateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellTargetReadyNtf(SpellTargetReadyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellGridReadyNtf(SpellGridReadyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellTarget(SpellTarget& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellGrid(SpellGrid& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellAck(SpellAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellNtf(SpellNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AttrShowNtf(AttrShowNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MissNtf(MissNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellDelayLostNtf(SpellDelayLostNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellDelayHitNtf(SpellDelayHitNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeNpcBuy(TradeNpcBuy& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeNpcSell(TradeNpcSell& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeNpcValueReq(TradeNpcValueReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeNpcValueAck(TradeNpcValueAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeNpcShopNtf(TradeNpcShopNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PRequest(TradeP2PRequest& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PRequestNtf(TradeP2PRequestNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PResponse(TradeP2PResponse& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2POpenNtf(TradeP2POpenNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PArrange(TradeP2PArrange& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PArrangeNtf(TradeP2PArrangeNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PGold(TradeP2PGold& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PGoldNtf(TradeP2PGoldNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PLock(TradeP2PLock& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PLockNtf(TradeP2PLockNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PConfirme(TradeP2PConfirme& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PConfirmeNtf(TradeP2PConfirmeNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PClose(TradeP2PClose& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeP2PCloseNtf(TradeP2PCloseNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallReady(TradeStallReady& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallReadyNtf(TradeStallReadyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStall(TradeStall& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallNtf(TradeStallNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallArrange(TradeStallArrange& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallQuery(TradeStallQuery& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallQueryNtf(TradeStallQueryNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallBuy(TradeStallBuy& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallBuyNtf(TradeStallBuyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallClose(TradeStallClose& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallCloseNtf(TradeStallCloseNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerSwitch(PlayerSwitch& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AtkModeReq(AtkModeReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ServantModeReq(ServantModeReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAddPoint(RoleAddPoint& rstProtocol){ rstProtocol; };
	virtual void OnRecv_LevelUpNtf(LevelUpNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerQuery(PlayerQuery& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerQueryBrd(PlayerQueryBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerQueryNtf(PlayerQueryNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerSiteSeg(PlayerSiteSeg& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerSiteSegBrd(PlayerSiteSegBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerSiteSegNtf(PlayerSiteSegNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TitleAdd(TitleAdd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TitleRemove(TitleRemove& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TitleApply(TitleApply& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TitleAddAck(TitleAddAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TitleRemoveAck(TitleRemoveAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SysMsgNtf(SysMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RelationChatNtf(RelationChatNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcSelect(NpcSelect& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkReq(NpcTalkReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkAck(NpcTalkAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuickBarSet(QuickBarSet& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuickBarSetNtf(QuickBarSetNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuickBarRemove(QuickBarRemove& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuickBarRemoveNtf(QuickBarRemoveNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuickBarMove(QuickBarMove& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ShortcutSet(ShortcutSet& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ShortcutNtf(ShortcutNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GoldDeposit(GoldDeposit& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GoldTake(GoldTake& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BeServantNtf(BeServantNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAttrExtRefNtf(RoleAttrExtRefNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_StartFamilyWarBrd(StartFamilyWarBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RunningFamilyWarNtf(RunningFamilyWarNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CastleNtf(CastleNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GoldDrop(GoldDrop& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerFamilyChangeNtf(PlayerFamilyChangeNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NotifyMapEffect(NotifyMapEffect& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleTalkNtf(RoleTalkNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ProgressStartNtf(ProgressStartNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ProgressCancelNtf(ProgressCancelNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VerifyImageQuestion(VerifyImageQuestion& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VerifyImageAnswer(VerifyImageAnswer& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VerifyImageReset(VerifyImageReset& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VerifyImageResultNtf(VerifyImageResultNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallBuy(TradeMallBuy& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallListReq(TradeMallListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallListAck(TradeMallListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallItemDetailReq(TradeMallItemDetailReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallItemDetailAck(TradeMallItemDetailAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallChartsReq(TradeMallChartsReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeMallChartsAck(TradeMallChartsAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkReqEx(NpcTalkReqEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkAckEx(NpcTalkAckEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestAccept(QuestAccept& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestAddNtf(QuestAddNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestAccomplish(QuestAccomplish& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestUpdateNtf(QuestUpdateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestTrackChange(QuestTrackChange& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestTrackChangeNtf(QuestTrackChangeNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestReadyNtf(QuestReadyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestCompleteNtf(QuestCompleteNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestDrop(QuestDrop& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestDropNtf(QuestDropNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestQueryCanAccept(QuestQueryCanAccept& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestQueryCanAcceptNtf(QuestQueryCanAcceptNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateSellCmd(DelegateSellCmd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateBuyCmd(DelegateBuyCmd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateSellListReq(DelegateSellListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateSellListAck(DelegateSellListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateBuyListReq(DelegateBuyListReq& rstProtocol){ rstProtocol; };
	//virtual void OnRecv_DelegateBuyListAck(DelegateBuyListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MarketBuyCmd(MarketBuyCmd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MarketSellCmd(MarketSellCmd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateCancel(DelegateCancel& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateMineReq(DelegateMineReq& rstProtocol){ rstProtocol; };
	//virtual void OnRecv_DelegateMineAck(DelegateMineAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AttrShowExNtf(AttrShowExNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CampaignListReq(CampaignListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CampaignListAck(CampaignListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CampaignDetailReq(CampaignDetailReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CampaignDetailAck(CampaignDetailAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_InputDlgReq(InputDlgReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_InputDlgAck(InputDlgAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MsgDlgReq(MsgDlgReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MsgDlgAck(MsgDlgAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_WebDlgNtf(WebDlgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_OpenWebPageNtf(OpenWebPageNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GlobalNtf(GlobalNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpeakerMsgAck(SpeakerMsgAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientKeepAlive(ClientKeepAlive& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyAllyTableNtf(FamilyAllyTableNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerCustomReq(PlayerCustomReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerCustomAck(PlayerCustomAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_WebPageNtf(WebPageNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CustomNtf(CustomNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CustomBroadcast(CustomBroadcast& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemCustomNtf(ItemCustomNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TaobaoNpcBuy(TaobaoNpcBuy& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TaobaoNpcShopReq(TaobaoNpcShopReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TaobaoNpcShopAck(TaobaoNpcShopAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RunClientScriptNtf(RunClientScriptNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ObjCustomNtf(ObjCustomNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CampaignJoinNtf(CampaignJoinNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MapReq(MapReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MapNtf(MapNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GridReq(GridReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GridNtf(GridNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TableReq(TableReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TableNtf(TableNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TableDataReq(TableDataReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TableDataNtf(TableDataNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CampaignRunNtf(CampaignRunNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RideReq(RideReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RideNtf(RideNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PermissionReq(PermissionReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipItemListReq(VipItemListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipItemListAck(VipItemListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipLevelBuyReq(VipLevelBuyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipLevelBuyAck(VipLevelBuyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipItemBuyReq(VipItemBuyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipItemBuyAck(VipItemBuyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipItemApplyReq(VipItemApplyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipItemApplyAck(VipItemApplyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipExpireNtf(VipExpireNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipLevelListReq(VipLevelListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_VipLevelListAck(VipLevelListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeNpcShopNumNtf(TradeNpcShopNumNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitFormAck(SubmitFormAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAttrReq(ItemAttrReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestStateReq(QuestStateReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestStateNtf(QuestStateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestQueryReq(QuestQueryReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestQueryNtf(QuestQueryNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GloryFinishNtf(GloryFinishNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GloryStateQuery(GloryStateQuery& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GloryStateAck(GloryStateAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GloryAwardGet(GloryAwardGet& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TraceReq(TraceReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestNpcStateNtf(QuestNpcStateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientKeepAliveRet(ClientKeepAliveRet& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RemoveClientNtf(RemoveClientNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SceneMagicAppearNtf(SceneMagicAppearNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyPackage(DummyPackage& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyItemMove(DummyItemMove& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyControlNtf(DummyControlNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ServantNumNtf(ServantNumNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyStateSwitchReq(DummyStateSwitchReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyStateSwitchAck(DummyStateSwitchAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeroCreateNtf(HeroCreateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeroDestroyNtf(HeroDestroyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AutoSetOptNtf(AutoSetOptNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AutoRunBeginNtf(AutoRunBeginNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AutoRunEndNtf(AutoRunEndNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NetCheckNtf(NetCheckNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeroSkillSwitchReq(HeroSkillSwitchReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeroSkillSwitchAck(HeroSkillSwitchAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MoveReqEx(MoveReqEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellTargetEx(SpellTargetEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellGridEx(SpellGridEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeroLockTargetCmd(HeroLockTargetCmd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ServantStatNtf(ServantStatNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_JointHitNtf(JointHitNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_JointHit(JointHit& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestAcceptEx(QuestAcceptEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestAccomplishEx(QuestAccomplishEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeroLockTargetAck(HeroLockTargetAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ShieldActiveNtf(ShieldActiveNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ShieldRemoveNtf(ShieldRemoveNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerQueryEx(PlayerQueryEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerQueryBrdEx(PlayerQueryBrdEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GSVersion(GSVersion& rstProtocol){ rstProtocol; };
	virtual void OnRecv_UpdateCheckCode(UpdateCheckCode& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MoveReq2(MoveReq2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellTarget2(SpellTarget2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpellGrid2(SpellGrid2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcSelect2(NpcSelect2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkReq2(NpcTalkReq2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientVerNtf(ClientVerNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemApply2(ItemApply2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MonsterAppearNtf2(MonsterAppearNtf2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAppearNtf2(ItemAppearNtf2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientKeepAliveEx(ClientKeepAliveEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GSVersionEx(GSVersionEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientVerReq(ClientVerReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NetDelayReq(NetDelayReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NetDelayAck(NetDelayAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientVerNtfEx(ClientVerNtfEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientVerReq2(ClientVerReq2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientVerAck2(ClientVerAck2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkReq3(NpcTalkReq3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkAck3(NpcTalkAck3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AttrShowNtfEx(AttrShowNtfEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EnterGSReqEx(EnterGSReqEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ReloginNtf(ReloginNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BehaviorNtf(BehaviorNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FashionReq(FashionReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FashionNtf(FashionNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ErrorNtf(ErrorNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkReqEx3(NpcTalkReqEx3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcTalkAckEx3(NpcTalkAckEx3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitForm2(SubmitForm2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitFormAck2(SubmitFormAck2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAddPointEx(RoleAddPointEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetClientCheckInfoReq(GetClientCheckInfoReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetClientCheckInfoAck(GetClientCheckInfoAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetMD5CheckListReq(GetMD5CheckListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetMD5CheckListAck(GetMD5CheckListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelayCloseNtf(DelayCloseNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyJoinInviteReq(FamilyJoinInviteReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyJoinInviteAck(FamilyJoinInviteAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyRelationShipReq(FamilyRelationShipReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyRelationShipAck(FamilyRelationShipAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MonsterAppearNtf3(MonsterAppearNtf3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MonsterAppearNtf4(MonsterAppearNtf4& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetAroundTeamReq(GetAroundTeamReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetAroundTeamAck(GetAroundTeamAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MigrateRoleDataNtf(MigrateRoleDataNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerAppearNtf2(PlayerAppearNtf2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleAppNtf2(RoleAppNtf2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemBatchDestroyNtf(ItemBatchDestroyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitForm3(SubmitForm3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitFormAck3(SubmitFormAck3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAppearNtf3(ItemAppearNtf3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ItemAppearNtf4(ItemAppearNtf4& rstProtocol){ rstProtocol; };
	virtual void OnRecv_InnerForceLevelUpReq(InnerForceLevelUpReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_InnerForceLevelUpAck(InnerForceLevelUpAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientFangChenMiNtf(ClientFangChenMiNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateMineAck2(DelegateMineAck2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DelegateBuyListAck2(DelegateBuyListAck2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FashionWeaponReq(FashionWeaponReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FashionWeaponNtf(FashionWeaponNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlayerAppearNtf3(PlayerAppearNtf3& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MonsterAppearNtf5(MonsterAppearNtf5& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MonsterAppearNtf6(MonsterAppearNtf6& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CaptchaReq(CaptchaReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CaptchaAck(CaptchaAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AgentKeyReq(AgentKeyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AgentKeyAck(AgentKeyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PlatformInfoNtf(PlatformInfoNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AttrShowNtf2(AttrShowNtf2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_AttrShowNtfEx2(AttrShowNtfEx2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BehaviorReq(BehaviorReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FangChenMiNtf(FangChenMiNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NpcShopIdsNtf(NpcShopIdsNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CreateMobaRoomReq(CreateMobaRoomReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CreateMobaRoomAck(CreateMobaRoomAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EnterMobaRoomReq(EnterMobaRoomReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EnterMobaRoomAck(EnterMobaRoomAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ExitMobaRoomReq(ExitMobaRoomReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ExitMobaRoomAck(ExitMobaRoomAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetMobaRoomListReq(GetMobaRoomListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomListAck(MobaRoomListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomMemberListNtf(MobaRoomMemberListNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetMobaMemberListReq(GetMobaMemberListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomKickReq(MobaRoomKickReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomKickAck(MobaRoomKickAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomKickedNtf(MobaRoomKickedNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomCampReadyReq(MobaRoomCampReadyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomCampReadyAck(MobaRoomCampReadyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomCampReadyNtf(MobaRoomCampReadyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomGameStartNtf(MobaRoomGameStartNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomSetViceHostReq(MobaRoomSetViceHostReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomSetViceHostAck(MobaRoomSetViceHostAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomToggleCampReq(MobaRoomToggleCampReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomToggleCampAck(MobaRoomToggleCampAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomDestroyNtf(MobaRoomDestroyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomMemberReadyReq(MobaRoomMemberReadyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomMemberReadyAck(MobaRoomMemberReadyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomMemberReadyNtf(MobaRoomMemberReadyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomUpdateNameAndPasswordReq(MobaRoomUpdateNameAndPasswordReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomUpdateNameAndPasswordAck(MobaRoomUpdateNameAndPasswordAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomNameUpdateNtf(MobaRoomNameUpdateNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomChangeCampAndPosReq(MobaRoomChangeCampAndPosReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MobaRoomChangeCampAndPosAck(MobaRoomChangeCampAndPosAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ReloginRefreshReq(ReloginRefreshReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GameGuardReq(GameGuardReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GameGuardAck(GameGuardAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GameGuardCheckFailedNtf(GameGuardCheckFailedNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GameGuardHackRpt(GameGuardHackRpt& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GameGuardHeartBeat(GameGuardHeartBeat& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BangcleHeartBeat(BangcleHeartBeat& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallSetBuyList(TradeStallSetBuyList& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallQueryBuyGoodsNtf(TradeStallQueryBuyGoodsNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallSell(TradeStallSell& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TradeStallSellNtf(TradeStallSellNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TaobaoNpcShopReqEx(TaobaoNpcShopReqEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TaobaoNpcShopAckEx(TaobaoNpcShopAckEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SkillCDChangedNtf(SkillCDChangedNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitForm4(SubmitForm4& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SubmitFormAck4(SubmitFormAck4& rstProtocol){ rstProtocol; };
	virtual void OnRecv_QuestAddNtf2(QuestAddNtf2& rstProtocol){ rstProtocol; };
    virtual void OnRecv_SkillCDPermenantChangedNtf(SkillCDPermenantChangedNtf& rstProtocol) { rstProtocol; };
private:
	EnCodeFuncClientGS m_EnCodeFuncArray[407];
	EnCodeFuncClientGS m_DeCodeFuncArray[407];
};
