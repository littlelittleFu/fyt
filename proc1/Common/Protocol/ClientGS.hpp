#pragma once

//===============包含的其他协议文件===============

 //===============宏定义开始===============
//===============宏定义结束===============

//===============数据定义开始===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct EnterGSReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{0};
	unsigned char             entertype; //进入类型 0=上线 1=跳服
	uint64_t                  roleguid; //角色guid
	unsigned char             fangchenmi; //是否防沉迷用户 1：是 0：否
	EnterGSReq() = default;
};

struct EnterGSAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{1};
	unsigned char             entertype; //进入类型 0=上线 1=跳服
	uint64_t                  roleguid; //角色guid
	unsigned int              gsobjid; //客户端在GS上的objid
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	EnterGSAck() = default;
};

struct ExitGSReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{2};
	unsigned char             exittype; //退出类型 1=大退 2=小退
	ExitGSReq() = default;
};

struct ExitGSAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{3};
	unsigned char             exittype; //退出类型 1=大退 2=小退
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	ExitGSAck() = default;
};

struct JumpGSNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{4};
	unsigned char             jumptype; //跳转类型 3=跳地图 9=重登陆
	unsigned int              gssvrid; //目标Game Server ID
	uint64_t                  mapcode; //目的地图的编号
	JumpGSNtf() = default;
};

struct KickRoleNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{5};
	uint64_t                  roleguid; //被踢除角色的GUID
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	KickRoleNtf() = default;
};

struct EnterMapNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{6};
	uint64_t                  mapcode; //地图流水号
	char                      logic[256]; //地图逻辑格文件
	unsigned short            view_x; //地图视野范围X
	unsigned short            view_y; //地图视野范围Y
	unsigned short            width; //宽
	unsigned short            height; //高
	EnterMapNtf() = default;
};

struct MapRegionNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{7};
	uint64_t                  mapcode; //地图流水号
	char                      logic[256]; //地图逻辑格文件
	unsigned char             rg_num; //区域数量
	MAP_REGION_INFO           rg_info[255]; //区域信息
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
	unsigned char             relive_type; //复活类型 1=原地复活 2=回城复活 3=副本入口复活
	PlayerReliveReq() = default;
};

struct PlayerReliveAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{10};
	unsigned char             relive_type; //复活类型 1=原地复活 2=回城复活 3=副本入口复活
	int                       error_code; //错误码 0=表示成功
	PlayerReliveAck() = default;
};

struct PlayerAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{11};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //名称
	unsigned char             gender; //性别
	unsigned char             job; //职业
	unsigned char             status; //人物状态 0=活着 1=死亡
	unsigned short            head; //头像
	unsigned int              level; //等级
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned short            hair; //头发
	unsigned short            hair_color; //头发颜色
	unsigned short            body; //身体
	unsigned short            weapon; //武器
	unsigned short            wings; //翅膀
	unsigned short            mount; //坐骑
	unsigned short            weapon_effect; //武器特效
	unsigned short            body_effect; //身体特效
	unsigned short            mount_effect; //坐骑特效
	unsigned int              hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned int              mp; //当前mp
	unsigned int              max_mp; //最大mp
	int                       pk; //pk
	unsigned short            move_speed; //移动速度
	unsigned short            attack_speed; //攻击速度
	unsigned short            title; //称号
	unsigned char             has_team; //是否有队伍
	unsigned char             stall; //0: 未摆摊 1: 摆摊准备 2: 摆摊中
	char                      stall_name[32]; //摆摊名称
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      family_name[32]; //行会名称
	char                      castle_name[256]; //城堡名称，可以多个用与符号分隔
	char                      family_title[32]; //行会称号
	char                      alias[64]; //别名
	CUSTOM_INFO               custom; //自定义数据
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	unsigned short            amulet; //法宝
	PlayerAppearNtf() = default;
};

struct MonsterAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{12};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //模板id
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned int              cur_hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
	unsigned char             servant_lv; //随从等级
	unsigned short            move_speed; //移动速度
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      master_name[32]; //主人的名字
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	MonsterAppearNtf() = default;
};

struct ItemAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{13};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //模板id
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned short            skill_id; //技能id
	char                      item_name[32]; //物品名称
	ItemAppearNtf() = default;
};

struct NPCAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{14};
	uint64_t                  npc_guid; //npc guid
	unsigned short            template_id; //模板id
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned char             dir; //方向
	char                      name[256]; //名字
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
	char                      name[32]; //名称
	unsigned char             sex; //性别
	unsigned short            head; //头像
	unsigned short            hair; //发型
	unsigned int              hair_color; //发色
	unsigned int              level; //等级
	uint64_t                  exp; //经验
	PlayerCreate() = default;
};

struct MoveReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{17};
	unsigned char             type; //移动类型 0=走 1=跑
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned int              idx; //客户端序列号
	MoveReq() = default;
};

struct MoveNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{18};
	uint64_t                  guid; //player/monster/npc's guid
	unsigned char             type; //移动类型 0=走 1=跑 2=跳
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	MoveNtf() = default;
};

struct MoveAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{19};
	unsigned char             ret; //0=成功, 1=表示失败
	unsigned char             type; //移动类型 0=走 1=跑
	unsigned short            dst_x; //移动前的点x
	unsigned short            dst_y; //移动前的点y
	unsigned int              idx; //客户端序列号
	MoveAck() = default;
};

struct TurnReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{20};
	unsigned char             dir; //角色现在的方向
	TurnReq() = default;
};

struct TurnNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{21};
	uint64_t                  guid; //player/monster/npc's guid
	unsigned char             dir; //角色现在的方向
	TurnNtf() = default;
};

struct TurnAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{22};
	unsigned char             ret; //0=成功, 1=表示失败
	unsigned char             dir; //角色现在的方向
	TurnAck() = default;
};

struct ObjDieNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{23};
	uint64_t                  die_guid; //死亡的对象的guid 可能是player/monster/npc
	uint64_t                  kill_guid; //杀手的对象的guid 可能是player/monster/npc
	char                      kill_name[32]; //杀手的名称
	ObjDieNtf() = default;
};

struct ChatReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{24};
	unsigned char             type; //聊天类型 1=普通 5=世界
	char                      sender[256]; //发送者的名字
	char                      text[256]; //message
	ChatReq() = default;
};

struct GMCommandReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{25};
	char                      cmd[256]; //GM 指令
	char                      param[256]; //指令参数
	GMCommandReq() = default;
};

struct RoleAppNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{26};
	uint64_t                  player_guid; //player guid
	unsigned short            hair; //头发
	unsigned short            hair_color; //头发颜色
	unsigned short            body; //身体
	unsigned short            weapon; //武器
	unsigned short            wings; //翅膀
	unsigned short            mount; //坐骑
	unsigned short            weapon_effect; //武器特效
	unsigned short            body_effect; //身体特效
	unsigned short            mount_effect; //坐骑特效
	unsigned short            amulet; //法宝
	RoleAppNtf() = default;
};

struct RoleAttrNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{27};
	uint64_t                  role_guid; //role guid
	unsigned short            num; //数量
	unsigned short            attr_name[100]; //属性名称
	int                       attr_value[100]; //属性值
	RoleAttrNtf() = default;
};

struct RoleAttrExtNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{28};
	uint64_t                  player_guid; //player guid
	unsigned short            num; //数量
	unsigned short            attr_name[20]; //属性名称
	int64_t                   attr_value[20]; //属性值
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
	char                      form_name[256]; //表单名称
	unsigned short            size; //表单内容字节数
	char                      form_content[7900]; //表单内容
	char                      comp; //是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
	ShowFormNtf() = default;
};

struct SubmitForm{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{31};
	char                      script_name[256]; //脚本名称
	char                      function_name[256]; //函数名称
	unsigned short            num; //参数个数
	PARAM_INFO                info[100]; //参数信息
	SubmitForm() = default;
};

struct ItemAddReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{32};
	unsigned short            item_id; //物品模板ID
	int                       item_amount; //物品数量
	unsigned char             is_bind; //是否绑定
	ItemAddReq() = default;
};

struct ItemAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{33};
	ITEM_INFO                 info; //物品信息
	ItemAddAck() = default;
};

struct ItemDestroyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{34};
	uint64_t                  item_guid; //销毁物品的GUID
	ItemDestroyReq() = default;
};

struct ItemDestroyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{35};
	uint64_t                  item_guid; //销毁物品的GUID
	ItemDestroyAck() = default;
};

struct ItemMove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{36};
	uint64_t                  item_guid; //物品GUID
	unsigned short            dest_site; //物品的目标位置
	ItemMove() = default;
};

struct ItemSplit{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{37};
	uint64_t                  item_guid; //物品GUID
	unsigned short            item_amount; //物品数量
	unsigned short            dest_site; //物品的目标位置
	ItemSplit() = default;
};

struct ItemAttrNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{38};
	uint64_t                  item_guid; //物品GUID
	unsigned int              attr_name; //物品属性名称
	int                       attr_value; //物品属性值
	ItemAttrNtf() = default;
};

struct ItemUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{39};
	ITEM_INFO                 info; //物品信息
	ItemUpdateNtf() = default;
};

struct ItemBind{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{40};
	uint64_t                  item_guid; //物品GUID
	ItemBind() = default;
};

struct ItemApply{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{41};
	uint64_t                  item_guid; //物品GUID
	ItemApply() = default;
};

struct ItemApplyOnTarget{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{42};
	uint64_t                  item_guid; //物品GUID
	uint64_t                  target; //target, 可能是player/monster/npc's guid
	ItemApplyOnTarget() = default;
};

struct ItemApplyOnGrid{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{43};
	uint64_t                  item_guid; //物品GUID
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	ItemApplyOnGrid() = default;
};

struct ItemArrange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{44};
	unsigned char             type; //0=背包 1=仓库 2=高级仓库
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
	uint64_t                  item_guid; //物品GUID
	ItemDrop() = default;
};

struct ItemTieUp{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{47};
	uint64_t                  item_guid; //参照物品GUID
	ItemTieUp() = default;
};

struct ItemTip{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{48};
	uint64_t                  owner_guid; //物品拥有者 guid
	uint64_t                  item_guid; //item's guid
	ItemTip() = default;
};

struct ItemTipBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{49};
	uint64_t                  owner_guid; //物品拥有者 guid
	uint64_t                  item_guid; //item's guid
	unsigned int              target_userid; //目标 userid
	ItemTipBrd() = default;
};

struct ItemTipNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{50};
	ITEM_INFO                 info; //物品信息
	ItemTipNtf() = default;
};

struct ItemEnhance{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{51};
	uint64_t                  item_guid; //强化的武器guid
	unsigned short            items_num; //技能数量
	uint64_t                  items_info[100]; //消耗装备
	unsigned short            materials_num; //材料数量
	uint64_t                  materials_info[100]; //消耗材料
	ItemEnhance() = default;
};

struct ItemDrill{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{52};
	uint64_t                  item_guid; //打孔物品
	uint64_t                  material_guid; //打孔材料
	ItemDrill() = default;
};

struct ItemSynthesis{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{53};
	uint64_t                  material_guid; //宝石合成符
	unsigned short            gems_num; //宝石数量
	uint64_t                  gems_info[5]; //宝石
	ItemSynthesis() = default;
};

struct ItemEmbed{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{54};
	uint64_t                  item_guid; //镶嵌物品
	uint64_t                  material_guid; //宝石镶嵌符
	uint64_t                  gem_guid; //宝石
	ItemEmbed() = default;
};

struct ItemDig{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{55};
	uint64_t                  item_guid; //镶嵌物品
	uint64_t                  material_guid; //宝石摘除符
	unsigned char             slot; //宝石槽
	ItemDig() = default;
};

struct ItemIdentify{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{56};
	uint64_t                  item_guid; //鉴定物品
	uint64_t                  material_guid; //鉴定材料
	ItemIdentify() = default;
};

struct ItemRename{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{57};
	uint64_t                  item_guid; //物品guid
	char                      new_name[32]; //物品新名称
	ItemRename() = default;
};

struct ItemRefine{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{58};
	uint64_t                  item_guid; //物品guid
	uint64_t                  material_guid; //精炼材料
	uint64_t                  lucky_guid; //精炼幸运符
	ItemRefine() = default;
};

struct ItemRepairQuery{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{59};
	uint64_t                  item_guid; //物品guid
	unsigned char             type; //修理方式 1:普通 2:特殊
	ItemRepairQuery() = default;
};

struct ItemRepairQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{60};
	int                       gold; //修理费
	ItemRepairQueryNtf() = default;
};

struct ItemRepair{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{61};
	uint64_t                  item_guid; //物品guid
	unsigned char             type; //修理方式 1:普通 2:特殊
	ItemRepair() = default;
};

struct ItemSeg{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{62};
	unsigned short            begin_site; //起始site
	unsigned short            end_site; //结束site
	ItemSeg() = default;
};

struct SkillAddReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{63};
	unsigned short            id; //技能id
	SkillAddReq() = default;
};

struct SkillAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{64};
	unsigned short            num; //技能数量
	SKILL_INFO                info[100]; //技能信息
	SkillAddAck() = default;
};

struct SkillDestroyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{65};
	unsigned short            id; //技能id
	SkillDestroyReq() = default;
};

struct SkillDestroyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{66};
	unsigned short            id; //技能id
	SkillDestroyAck() = default;
};

struct SkillSwitch{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{67};
	unsigned short            id; //技能id
	unsigned char             active; //0=不激活 1=激活
	SkillSwitch() = default;
};

struct SkillSwitchAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{68};
	unsigned short            id; //技能id
	unsigned char             active; //0=不激活 1=激活
	SkillSwitchAck() = default;
};

struct SkillProficiencyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{69};
	unsigned short            id; //技能id
	unsigned short            proficiency; //技能熟练度
	SkillProficiencyNtf() = default;
};

struct BuffAddAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{70};
	uint64_t                  role_guid; //可能是player/monster/npc's guid
	unsigned short            num; //Buff数量
	BUFF_INFO                 info[50]; //Buff信息
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
	uint64_t                  role_guid; //可能是player/monster/npc's guid
	unsigned short            id; //Buff id
	BuffDestroyAck() = default;
};

struct BuffUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{73};
	uint64_t                  role_guid; //可能是player/monster/npc's guid
	BUFF_INFO                 info; //Buff信息
	BuffUpdateNtf() = default;
};

struct SpellTargetReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{74};
	uint64_t                  actor; //施放者, 可能是player/monster/npc's guid
	unsigned short            id; //技能id
	uint64_t                  target; //目标, 可能是player/monster/npc's guid
	SpellTargetReadyNtf() = default;
};

struct SpellGridReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{75};
	uint64_t                  actor; //施放者, 可能是player/monster/npc's guid
	unsigned short            id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	SpellGridReadyNtf() = default;
};

struct SpellTarget{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{76};
	unsigned short            id; //技能id
	uint64_t                  target; //目标, 可能是player/monster/npc's guid
	unsigned short            idx; //~
	SpellTarget() = default;
};

struct SpellGrid{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{77};
	unsigned short            id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	unsigned short            idx; //~
	uint64_t                  ref_target; //参照目标guid
	SpellGrid() = default;
};

struct SpellAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{78};
	unsigned short            id; //技能id
	int                       ecode; //错误码
	char                      detail[256]; //错误描述
	unsigned short            idx; //~
	SpellAck() = default;
};

struct SpellNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{79};
	uint64_t                  actor; //施放者, 可能是player/monster/npc's guid
	unsigned short            id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	unsigned short            num; //有效目标数量
	uint64_t                  targets[50]; //目标集, 可能是player/monster/npc's guid
	SpellNtf() = default;
};

struct AttrShowNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{80};
	uint64_t                  actor; //actor, 可能是player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, 可能是player/monster/npc's guid
	unsigned char             type; //0=普通 1=爆击
	int                       actor_hp_ref; //actor hp显示值
	int                       target_hp_ref; //目标hp显示值
	int                       target_hp; //目标hp绝对值
	AttrShowNtf() = default;
};

struct MissNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{81};
	uint64_t                  actor; //actor, 可能是player/monster/npc's guid
	uint64_t                  target; //target, 可能是player/monster/npc's guid
	unsigned short            skill_id; //技能id
	unsigned char             type; //1=闪避 2=免疫
	MissNtf() = default;
};

struct SpellDelayLostNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{82};
	uint64_t                  actor; //施放者, 可能是player/monster/npc's guid
	unsigned short            skill_id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	SpellDelayLostNtf() = default;
};

struct SpellDelayHitNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{83};
	uint64_t                  actor; //施放者, 可能是player/monster/npc's guid
	unsigned short            skill_id; //技能id
	unsigned short            num; //有效目标数量
	uint64_t                  targets[50]; //目标集, 可能是player/monster/npc's guid
	SpellDelayHitNtf() = default;
};

struct TradeNpcBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{84};
	unsigned short            shop_id; //shop_index
	unsigned short            item_index; //item_index
	unsigned short            item_amount; //物品数量
	unsigned char             is_bind; //是否使用绑定金币, 1、使用；0、不使用
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
	int                       value; //物品价格
	TradeNpcValueAck() = default;
};

struct TradeNpcShopNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{88};
	unsigned short            shop_id; //shop_index
	unsigned char             item_count; //商品数量
	SHOP_ITEM_INFO            item_list[250]; //商品信息列表
	TradeNpcShopNtf() = default;
};

struct TradeP2PRequest{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{89};
	uint64_t                  responsor; //响应者GUID
	TradeP2PRequest() = default;
};

struct TradeP2PRequestNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{90};
	uint64_t                  requestor; //发起者GUID
	char                      requestor_name[32]; //发起者名称
	TradeP2PRequestNtf() = default;
};

struct TradeP2PResponse{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{91};
	uint64_t                  requestor; //发起者GUID
	unsigned char             accepted; //是否接受
	TradeP2PResponse() = default;
};

struct TradeP2POpenNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{92};
	uint64_t                  requestor; //发起者GUID
	uint64_t                  responsor; //响应者GUID
	char                      requestor_name[32]; //发起者名称
	char                      responsor_name[32]; //响应者名称
	TradeP2POpenNtf() = default;
};

struct TradeP2PArrange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{93};
	unsigned char             remove; //true：删除；false：添加
	uint64_t                  item_guid; //item guid
	TradeP2PArrange() = default;
};

struct TradeP2PArrangeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{94};
	uint64_t                  player_guid; //player guid
	unsigned char             remove; //true：删除；false：添加
	uint64_t                  item_guid; //item guid
	unsigned short            item_num; //物品数量
	ITEM_INFO                 item_info[1]; //物品信息
	TradeP2PArrangeNtf() = default;
};

struct TradeP2PGold{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{95};
	int64_t                   gold; //金钱
	TradeP2PGold() = default;
};

struct TradeP2PGoldNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{96};
	uint64_t                  player_guid; //player guid
	int64_t                   gold; //金钱
	TradeP2PGoldNtf() = default;
};

struct TradeP2PLock{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{97};
	unsigned char             locked; //是否锁定
	TradeP2PLock() = default;
};

struct TradeP2PLockNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{98};
	uint64_t                  player_guid; //player guid
	unsigned char             locked; //是否锁定
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
	unsigned char             confirmed; //是否确认
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
	char                      stall_name[32]; //摊位名称
	unsigned short            item_num; //物品数量
	uint64_t                  item_guids[25]; //物品guid
	unsigned char             price_types[25]; //物品价格类型 0=金币 1=元宝 2=积分
	int64_t                   item_prices[25]; //物品价格
	TradeStall() = default;
};

struct TradeStallNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{106};
	uint64_t                  player_guid; //player guid
	char                      stall_name[32]; //摊位名称
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
	uint64_t                  player_guid; //摊位拥有者guid
	TradeStallQuery() = default;
};

struct TradeStallQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{109};
	uint64_t                  player_guid; //player guid
	char                      stall_name[32]; //摊位名称
	unsigned short            item_num; //物品数量
	int64_t                   item_prices[25]; //物品价格
	unsigned char             price_types[25]; //物品价格类型 0=金币 1=元宝 2=积分
	ITEM_INFO                 item_info[25]; //物品信息
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
	uint64_t                  buyer_guid; //买家
	uint64_t                  seller_guid; //卖家
	uint64_t                  item_guid; //item's guid
	unsigned short            item_id; //物品id
	unsigned short            item_amount; //item's amount
	unsigned char             price_type; //物品价格类型 0=金币 1=元宝 2=积分
	int64_t                   price; //物品价格
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
	unsigned char             value; //开关值
	PlayerSwitch() = default;
};

struct AtkModeReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{115};
	unsigned char             atk_mode; //攻击模式
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
	char                      player_name[128]; //玩家名称
	PlayerQuery() = default;
};

struct PlayerQueryBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{120};
	char                      target_name[32]; //玩家名称
	unsigned int              target_userid; //目标 userid
	PlayerQueryBrd() = default;
};

struct PlayerQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{121};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //玩家名称
	unsigned char             gender; //性别
	unsigned char             job; //职业
	unsigned int              level; //等级
	char                      family_name[32]; //行会名称
	char                      family_title[32]; //行会称号
	char                      alias[64]; //别名
	unsigned short            item_num; //物品数量
	ITEM_INFO                 item_info[45]; //物品信息
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
	int                       title_num; //称号数量
	TITLE_INFO                titles[100]; //称号信息
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
	unsigned char             msg_type; //指定消息的类型，用来确定消息的显示区域
	unsigned char             scroll_count; //消息的滚动次数 默认：1次
	char                      msg[256]; //具体的消息内容
	SysMsgNtf() = default;
};

struct RelationChatNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{131};
	unsigned char             type; //1：当前 2：队伍 3：公会 4：世界 12：全服
	CHAT_MSG                  chat_message; //角色名为源角色的名字
	RelationChatNtf() = default;
};

struct NpcSelect{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{132};
	uint64_t                  npc_guid; //npc的GUID
	NpcSelect() = default;
};

struct NpcTalkReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{133};
	uint64_t                  npc_guid; //npc的GUID
	char                      func[256]; //选择执行的NPC内容
	NpcTalkReq() = default;
};

struct NpcTalkAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{134};
	unsigned short            width; //NPC对话框面板的宽度
	unsigned short            height; //NPC对话框面板的高度
	uint64_t                  npc_guid; //npc的GUID
	unsigned short            talk_len; //NPC面板内容长度
	char                      talk[7500]; //NPC面板显示的内容
	unsigned short            quest_state_num; //任务状态数据数量
	QUEST_STATE_INFO          quest_states[2]; //任务状态数据
	char                      comp; //是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
	NpcTalkAck() = default;
};

struct QuickBarSet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{135};
	unsigned char             type; //0=null 1=item 2=skill
	unsigned char             slot; //槽位
	unsigned short            id; //模板id
	uint64_t                  guid; //物品guid
	QuickBarSet() = default;
};

struct QuickBarSetNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{136};
	unsigned short            num; //快捷栏数量
	QUICK_BAR_INFO            info[30]; //快捷栏信息
	QuickBarSetNtf() = default;
};

struct QuickBarRemove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{137};
	unsigned char             slot; //槽位
	QuickBarRemove() = default;
};

struct QuickBarRemoveNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{138};
	unsigned char             slot; //槽位
	QuickBarRemoveNtf() = default;
};

struct QuickBarMove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{139};
	unsigned char             src_slot; //原槽位
	unsigned char             dst_slot; //目标槽位
	QuickBarMove() = default;
};

struct ShortcutSet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{140};
	unsigned short            info[16]; //快捷键信息
	ShortcutSet() = default;
};

struct ShortcutNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{141};
	unsigned short            info[16]; //快捷键信息
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
	uint64_t                  servant_guid; //随从guid
	unsigned char             servant_level; //随从等级
	char                      master_name[32]; //主人名字
	BeServantNtf() = default;
};

struct RoleAttrExtRefNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{145};
	unsigned short            attr_name; //属性名称
	int64_t                   attr_value; //属性改变相对值
	RoleAttrExtRefNtf() = default;
};

struct StartFamilyWarBrd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{146};
	char                      attack[32]; //攻
	char                      defence[32]; //守
	StartFamilyWarBrd() = default;
};

struct RunningFamilyWarNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{147};
	unsigned short            num; //进行中的行会战数量
	FAMILY_WAR_INFO           families[100]; //进行中的行会战信息
	RunningFamilyWarNtf() = default;
};

struct CastleNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{148};
	unsigned short            num; //数量
	CASTLE_INFO               castles[5]; //城堡信息
	CastleNtf() = default;
};

struct GoldDrop{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{149};
	int64_t                   gold; //金币数量
	GoldDrop() = default;
};

struct PlayerFamilyChangeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{150};
	uint64_t                  player_guid; //玩家guid
	char                      family_name[32]; //行会名称
	char                      castle_name[256]; //城堡名称，可以多个用与符号分隔
	PlayerFamilyChangeNtf() = default;
};

struct NotifyMapEffect{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{151};
	unsigned int              effect_id; //要播放的特效id
	unsigned short            effect_x; //播放x坐标
	unsigned short            effect_y; //播放y坐标
	unsigned int              effect_life; //特效生存期
	NotifyMapEffect() = default;
};

struct RoleTalkNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{152};
	uint64_t                  role_guid; //角色的GUID
	char                      msg[256]; //消息内容
	RoleTalkNtf() = default;
};

struct ProgressStartNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{153};
	uint64_t                  player_guid; //玩家guid
	char                      desc[256]; //进度条文字
	unsigned int              duration; //持续时间
	ProgressStartNtf() = default;
};

struct ProgressCancelNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{154};
	uint64_t                  player_guid; //玩家guid
	unsigned char             complete; //0: 取消 1:完成
	ProgressCancelNtf() = default;
};

struct VerifyImageQuestion{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{155};
	unsigned short            size; //图片文件大小
	unsigned char             buffer[4096]; //图片数据
	VerifyImageQuestion() = default;
};

struct VerifyImageAnswer{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{156};
	char                      answer[16]; //用户给出的答案
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
	unsigned int              fail_count; //失败的次数
	VerifyImageResultNtf() = default;
};

struct TradeMallBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{159};
	unsigned int              item_index; //item_index
	unsigned short            item_amount; //物品数量
	TradeMallBuy() = default;
};

struct TradeMallListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{160};
	unsigned char             page_id; //商品的分页
	TradeMallListReq() = default;
};

struct TradeMallListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{161};
	unsigned char             page_id; //商品的分页
	unsigned char             item_count; //商品数量
	MALL_ITEM_INFO            item_list[250]; //商品信息列表
	TradeMallListAck() = default;
};

struct TradeMallItemDetailReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{162};
	unsigned int              item_index; //商品index
	TradeMallItemDetailReq() = default;
};

struct TradeMallItemDetailAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{163};
	MALL_ITEM_DETAIL          item; //某商品详细信息
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
	unsigned char             item_count; //商品数量
	MALL_ITEM_INFO            item_list[5]; //商品信息列表
	TradeMallChartsAck() = default;
};

struct NpcTalkReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{166};
	char                      func[256]; //选择执行的NPC内容
	NpcTalkReqEx() = default;
};

struct NpcTalkAckEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{167};
	unsigned short            width; //NPC对话框面板的宽度
	unsigned short            height; //NPC对话框面板的高度
	unsigned short            talk_len; //NPC面板内容长度
	char                      talk[8000]; //NPC面板显示的内容
	char                      comp; //是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
	NpcTalkAckEx() = default;
};

struct QuestAccept{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{168};
	unsigned short            quest_id; //任务模板id
	QuestAccept() = default;
};

struct QuestAddNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{169};
	unsigned short            quest_id; //任务模板id
	char                      quest_name[256]; //任务的名称
	unsigned char             quest_type; //任务的类型, 显示用
	unsigned short            group_huntings_len; //组打怪计数
	QUEST_HUNTING_INFO        group_huntings[5]; //组打怪数据
	unsigned short            huntings_len; //打怪计数
	QUEST_HUNTING_INFO        huntings[5]; //打怪数据
	unsigned short            huntlevels_len; //打等级怪计数
	QUEST_HUNTLEVEL_INFO      huntlevels[5]; //打等级怪数据
	unsigned short            group_items_len; //组物品收集
	QUEST_ITEM_INFO           group_items[5]; //组收集数据
	unsigned short            collect_items_len; //物品收集
	QUEST_ITEM_INFO           collect_items[5]; //收集数据
	unsigned short            apply_items_len; //物品使用
	QUEST_ITEM_INFO           apply_items[5]; //收集使用
	unsigned short            npcs_len; //Npc
	QUEST_NPC_INFO            npcs[5]; //npc访问
	unsigned char             track_enabled; //是否开启追踪
	unsigned int              life; //剩余时间
	char                      progressing[256]; //任务进行时追踪文本
	char                      accomplishing[256]; //任务完成时追踪文本
	QuestAddNtf() = default;
};

struct QuestAccomplish{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{170};
	unsigned short            quest_id; //任务模板id
	unsigned short            select_index; //玩家选择项索引
	QuestAccomplish() = default;
};

struct QuestUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{171};
	unsigned short            quest_id; //任务模板id
	int                       data_type; //数据类型, 参考quest_track_state
	int                       id; //Id
	int                       value; //value
	QuestUpdateNtf() = default;
};

struct QuestTrackChange{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{172};
	unsigned short            quest_id; //任务模板id
	unsigned char             track_enabled; //是否开启追踪
	QuestTrackChange() = default;
};

struct QuestTrackChangeNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{173};
	unsigned short            quest_id; //任务模板id
	unsigned char             track_enabled; //是否开启追踪
	QuestTrackChangeNtf() = default;
};

struct QuestReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{174};
	unsigned short            quest_id; //任务模板id
	QuestReadyNtf() = default;
};

struct QuestCompleteNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{175};
	unsigned short            quest_id; //任务模板id
	QuestCompleteNtf() = default;
};

struct QuestDrop{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{176};
	unsigned short            quest_id; //任务模板id
	QuestDrop() = default;
};

struct QuestDropNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{177};
	unsigned short            quest_id; //任务模板id
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
	unsigned short            num; //数量
	unsigned short            quests[500]; //可接任务列表
	QuestQueryCanAcceptNtf() = default;
};

struct DelegateSellCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{180};		// PROTO_CLIENT3_DELEGATE_SELL_CMD
	uint64_t                  item_guid; //物品GUID
	unsigned int              item_value; //物品单价
	unsigned int              item_unit; //物品单位数量
	unsigned char             value_type; //价格类型：0、金币；1、元宝
	DelegateSellCmd() = default;
};

struct DelegateBuyCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{181};		// PROTO_CLIENT3_DELEGATE_BUY_CMD
	unsigned short            item_id; //物品模版ID
	unsigned int              item_count; //物品数量
	unsigned int              item_value; //物品单价
	unsigned int              item_unit; //物品单位数量
	unsigned char             value_type; //价格类型：0、金币；1、元宝
	DelegateBuyCmd() = default;
};

struct DelegateSellListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{182};		// PROTO_CLIENT3_DELEGATE_SELL_LIST_REQ
	unsigned int              start; //起始序列号
	unsigned int              count; //申请数量
	unsigned short            type; //分类
	unsigned short            subtype; //子分类
	char                      item_name[32]; //物品名称过滤
	unsigned char             is_reverse; //是否倒序
	DelegateSellListReq() = default;
};

struct DelegateSellListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{183};		// PROTO_CLIENT3_DELEGATE_SELL_LIST_ACK
	unsigned short            type; //分类
	unsigned short            subtype; //子分类
	unsigned int              total; //总数
	unsigned int              start; //起始序列号
	unsigned int              count; //申请数量
	DELEGATE_SELL_ITEM        items[20]; //物品列表
	DelegateSellListAck() = default;
};

struct DelegateBuyListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{184};		// PROTO_CLIENT3_DELEGATE_BUY_LIST_REQ
	unsigned int              start; //起始序列号
	unsigned int              count; //申请数量
	unsigned short            type; //分类
	unsigned short            subtype; //子分类
	char                      item_name[32]; //物品名称过滤
	unsigned char             is_reverse; //是否倒序
	DelegateBuyListReq() = default;
};
/*
struct DelegateBuyListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{185};		// PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK
	unsigned short            type; //分类
	unsigned short            subtype; //子分类
	unsigned int              total; //总数
	unsigned int              start; //起始序列号
	unsigned int              count; //申请数量
	DELEGATE_BUY_ITEM         items[20]; //物品列表
	DelegateBuyListAck() = default;
};
*/
struct MarketBuyCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{186};		// PROTO_CLIENT3_MARKET_BUY_CMD
	uint64_t                  trade_id; //交易号
	unsigned int              count; //购买数量
	MarketBuyCmd() = default;
};

struct MarketSellCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{187};		// PROTO_CLIENT3_MARKET_SELL_CMD
	uint64_t                  trade_id; //交易号
	uint64_t                  item_guid; //物品guid
	MarketSellCmd() = default;
};

struct DelegateCancel{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{188};	// PROTO_CLIENT3_DELEGATE_CANCEL
	uint64_t                  trade_id; //交易号
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
	unsigned int              count; //数量
	DELEGATE_INFO             trade[5]; //交易
	DelegateMineAck() = default;
};
*/
struct AttrShowExNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{191};
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, 可能是player/monster/npc's guid
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
	unsigned int              svr_time; //服务器当前时间(秒)
	unsigned int              count; //活动项数量
	CAMPAIGN_INFO             campaigns[50]; //活动项列表
	CampaignListAck() = default;
};

struct CampaignDetailReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{194};
	unsigned int              id; //活动id
	CampaignDetailReq() = default;
};

struct CampaignDetailAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{195};
	unsigned int              id; //活动id
	char                      npc[256]; //活动NPC
	char                      desc[256]; //描述内容
	char                      award[256]; //奖励内容
	CampaignDetailAck() = default;
};

struct InputDlgReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{196};
	unsigned int              dlg_id; //对话框id
	unsigned int              timeout; //弹框超时
	unsigned int              param_len; //输入框最大字符长度
	unsigned int              str_len; //文字内容的长度
	char                      str[8000]; //文字内容
	InputDlgReq() = default;
};

struct InputDlgAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{197};
	unsigned int              dlg_id; //对话框id
	unsigned int              str_len; //输入框内容长度
	char                      str[8000]; //输入框内容
	InputDlgAck() = default;
};

struct MsgDlgReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{198};
	unsigned int              dlg_id; //对话框id
	unsigned int              timeout; //弹框超时
	unsigned int              str_len; //文字内容的长度
	char                      str[8000]; //文字内容
	MsgDlgReq() = default;
};

struct MsgDlgAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{199};
	unsigned int              dlg_id; //对话框id
	unsigned char             key; //被点击按钮的序号
	MsgDlgAck() = default;
};

struct WebDlgNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{200};
	char                      title[256]; //网页标题
	char                      parm[256]; //网页属性
	unsigned int              url_len; //url长度
	char                      url[2048]; //url
	WebDlgNtf() = default;
};

struct OpenWebPageNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{201};
	unsigned int              url_len; //url长度
	char                      url[2048]; //url
	OpenWebPageNtf() = default;
};

struct GlobalNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{202};
	unsigned short            int_count; //整形数据个数
	IntData                   int_data[256]; //数据值
	unsigned short            str_count; //字符型数据个数
	StrData                   str_data[256]; //数据值
	GlobalNtf() = default;
};

struct SpeakerMsgAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{203};
	unsigned char             ret; //返回结果 0：成功 1：失败
	int                       ecode; //错误码
	char                      msg[256]; //消息内容
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
	unsigned int              count; //个数
	FAMILY_ALLY_INFO          table[MAX_ALLY_NUM]; //同盟关系表
	unsigned char             type; //1、结盟；2、解盟
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
	CUSTOM_INFO               info; //自定义数据
	PlayerCustomAck() = default;
};

struct WebPageNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{208};
	unsigned short            url_len; //url长度
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
	uint64_t                  player_guid; //玩家guid
	unsigned char             type; //0: int 1:string 255:not exist
	KEY_VALUE_PAIR            info; //Key->Value
	CustomBroadcast() = default;
};

struct ItemCustomNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{211};
	uint64_t                  role_guid; //role guid
	uint64_t                  item_guid; //item guid
	CUSTOM_INFO               info; //自定义数据
	ItemCustomNtf() = default;
};

struct TaobaoNpcBuy{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{212};
	unsigned short            shop_id; //shop_index
	uint64_t                  item_guid; //物品guid
	TaobaoNpcBuy() = default;
};

struct TaobaoNpcShopReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{213};
	unsigned short            shop_id; //shop_index
	unsigned char             item_index; //第一个商品在所有商品中的索引，0开始
	unsigned char             item_count; //请求商品数量
	TaobaoNpcShopReq() = default;
};

struct TaobaoNpcShopAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{214};
	unsigned short            shop_id; //shop_index
	unsigned char             total_count; //商品总数量
	unsigned char             item_index; //第一个商品在所有商品中的索引，0开始
	unsigned char             item_count; //当前发送商品数量
	TAOBAO_ITEM_INFO          item_list[20]; //商品信息列表
	TaobaoNpcShopAck() = default;
};

struct RunClientScriptNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{215};
	char                      lua_name[256]; //lua文件名
	char                      lua_func[256]; //lua函数名
	char                      lua_params[256]; //lua参数,以'#'号分割
	RunClientScriptNtf() = default;
};

struct ObjCustomNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{216};
	uint64_t                  obj_guid; //obj guid
	CUSTOM_INFO               info; //自定义数据
	ObjCustomNtf() = default;
};

struct CampaignJoinNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{217};
	unsigned int              id; //活动id
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
	unsigned short            count; //数量
	MAP_INFO                  info[512]; //信息
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
	unsigned int              info[1024]; //格子信息
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
	unsigned short            count; //数量
	TABLE_INFO                info[256]; //信息
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
	int                       size; //表数据大小
	unsigned char             buf[65536]; //表数据
	TableDataNtf() = default;
};

struct CampaignRunNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{226};
	unsigned int              id; //活动id
	CampaignRunNtf() = default;
};

struct RideReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{227};
	unsigned char             enable; //0:下马 1:上马
	RideReq() = default;
};

struct RideNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{228};
	unsigned char             enable; //0:下马 1:上马
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
	unsigned short            vip_level; //当前vip等级
	unsigned int              remain; //当前VIP等级剩余时间
	unsigned int              num; //VIP物品数量
	VIP_ITEM                  items[50]; //物品信息
	VipItemListAck() = default;
};

struct VipLevelBuyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{232};
	unsigned short            vip_level; //vip等级
	VipLevelBuyReq() = default;
};

struct VipLevelBuyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{233};
	unsigned short            vip_level; //vip等级
	unsigned int              errcode; //错误码
	VipLevelBuyAck() = default;
};

struct VipItemBuyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{234};
	unsigned short            id; //vip物品ID
	VipItemBuyReq() = default;
};

struct VipItemBuyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{235};
	unsigned short            id; //vip物品ID
	unsigned int              errcode; //错误码
	VipItemBuyAck() = default;
};

struct VipItemApplyReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{236};
	unsigned short            id; //vip物品ID
	VipItemApplyReq() = default;
};

struct VipItemApplyAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{237};
	unsigned short            id; //vip物品ID
	unsigned int              errcode; //错误码
	VipItemApplyAck() = default;
};

struct VipExpireNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{238};
	unsigned short            vip_level; //会员等级
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
	unsigned int              num; //VIP等级数量
	VIP_LEVEL                 levels[100]; //等级信息
	VipLevelListAck() = default;
};

struct TradeNpcShopNumNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{241};
	unsigned short            shop_id; //shop_index
	unsigned short            item_index; //item_index
	unsigned short            item_amount; //物品数量
	TradeNpcShopNumNtf() = default;
};

struct SubmitFormAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{242};
	char                      script_name[256]; //脚本名称
	char                      result[256]; //反馈
	SubmitFormAck() = default;
};

struct ItemAttrReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{243};
	uint64_t                  item_guid; //物品GUID
	unsigned int              attr_name; //物品属性名称
	int                       attr_value; //物品属性值
	ItemAttrReq() = default;
};

struct QuestStateReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{244};
	uint64_t                  npc_guid; //npc的GUID
	QuestStateReq() = default;
};

struct QuestStateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{245};
	uint64_t                  npc_guid; //npc的GUID
	QUEST_STATE_INFO          info; //任务状态项数据
	QuestStateNtf() = default;
};

struct QuestQueryReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{246};
	unsigned short            quest_id; //任务模板id
	unsigned char             use_context; //是否使用上下文检测
	QuestQueryReq() = default;
};

struct QuestQueryNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{247};
	unsigned short            quest_id; //任务模板id
	unsigned char             result_type; //查询的类型，共四种，0：无状态查询，1：新任务，2：未完成，3：已完成
	char                      quest_name[256]; //任务的名称
	unsigned int              life; //存活时间
	QuestQueryNtf() = default;
};

struct GloryFinishNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{248};
	GLORY_STATE               status; //成就状态
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
	unsigned short            count; //成就个数
	GLORY_STATE               glories[512]; //成就状态
	GloryStateAck() = default;
};

struct GloryAwardGet{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{251};
	unsigned short            id; //成就的模版ID
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
	unsigned char             state; //0：null，1：任务可交，2：任务可接，3：任务已接不可交
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
	char                      user_name[256]; //账号名
	RemoveClientNtf() = default;
};

struct SceneMagicAppearNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{256};
	uint64_t                  scenemagic_guid; //scenemaigc guid
	unsigned char             resource_type; //资源类型
	unsigned int              resource_id; //资源id
	unsigned int              property; //属性
	SceneMagicAppearNtf() = default;
};

struct DummyPackage{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{257};
	uint64_t                  dummy_guid; //dummy guid
	int                       package_len; //包长
	char                      package[65535]; //包体
	DummyPackage() = default;
};

struct DummyItemMove{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{258};
	uint64_t                  src_guid; //源guid
	uint64_t                  dst_guid; //目标guid
	unsigned short            dst_site; //目标site
	uint64_t                  item_guid; //物品GUID
	DummyItemMove() = default;
};

struct DummyControlNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{259};
	uint64_t                  dummy_guid; //guid
	unsigned char             is_open; //控制开关, 1、打开；0、关闭
	DummyControlNtf() = default;
};

struct ServantNumNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{260};
	unsigned int              num; //宝宝数量
	ServantNumNtf() = default;
};

struct DummyStateSwitchReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{261};
	uint64_t                  dummy_guid; //guid
	unsigned char             state; //想要切换的状态：1、客户端控制 2、跟随
	unsigned short            x; //守护状态时的x坐标
	unsigned short            y; //守护状态时的y坐标
	DummyStateSwitchReq() = default;
};

struct DummyStateSwitchAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{262};
	uint64_t                  dummy_guid; //guid
	int                       err_code; //切换是否成功：0、成功 其他、错误码
	unsigned char             state; //当前状态，参见DummyStateSwitchReq说明
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
	unsigned char             is_auto_fight; //是否开启自动打怪 0=不开启 1=开启
	unsigned char             is_auto_pick; //是否开启自动捡东西 0=不开启 1=开启
	unsigned int              auto_time; //自动开启时间 单位秒
	AutoSetOptNtf() = default;
};

struct AutoRunBeginNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{266};
	unsigned char             opt[256]; //挂机选项
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
	unsigned char             opt; //0=关闭 1=开启
	NetCheckNtf() = default;
};

struct HeroSkillSwitchReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{269};
	uint64_t                  hero_guid; //英雄guid
	unsigned short            skill_id; //技能id，为空则查看所有禁用的技能
	unsigned char             disable; //是否禁用该技能，1表示禁用，0表示不禁用
	HeroSkillSwitchReq() = default;
};

struct HeroSkillSwitchAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{270};
	uint64_t                  hero_guid; //英雄guid
	unsigned short            skill_num; //已经禁用的技能数量
	unsigned short            skill_id[64]; //已经禁用的技能链id(注意，不是技能id)
	HeroSkillSwitchAck() = default;
};

struct MoveReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{271};
	unsigned char             type; //移动类型 0=走 1=跑
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned int              idx; //客户端序列号
	unsigned int              tick; //gate收到此包的tick
	MoveReqEx() = default;
};

struct SpellTargetEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{272};
	unsigned short            id; //技能id
	uint64_t                  target; //目标, 可能是player/monster/npc's guid
	unsigned short            idx; //~
	unsigned int              tick; //gate收到此包的tick
	SpellTargetEx() = default;
};

struct SpellGridEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{273};
	unsigned short            id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	unsigned short            idx; //~
	uint64_t                  ref_target; //参照目标guid
	unsigned int              tick; //gate收到此包的tick
	SpellGridEx() = default;
};

struct HeroLockTargetCmd{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{274};
	uint64_t                  hero_guid; //英雄guid
	uint64_t                  target_guid; //目标guid
	HeroLockTargetCmd() = default;
};

struct ServantStatNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{275};
	uint64_t                  servant_guid; //随从guid
	unsigned char             stat; //状态 0=普通 1=战斗
	ServantStatNtf() = default;
};

struct JointHitNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{276};
	uint64_t                  actor; //主施放者, 可能是player/dummy's guid
	uint64_t                  helper; //协助施放者, 可能是player/dummy's guid
	unsigned short            id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	unsigned short            num; //有效目标数量
	uint64_t                  targets[50]; //目标集, 可能是player/monster/npc's guid
	JointHitNtf() = default;
};

struct JointHit{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{277};
	unsigned short            id; //技能id
	uint64_t                  hero; //合击的英雄guid
	uint64_t                  target; //目标, 可能是player/monster/npc's guid
	JointHit() = default;
};

struct QuestAcceptEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{278};
	unsigned short            quest_id; //任务模板id
	uint64_t                  npc_guid; //npc的GUID
	QuestAcceptEx() = default;
};

struct QuestAccomplishEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{279};
	unsigned short            quest_id; //任务模板id
	unsigned short            select_index; //玩家选择项索引
	uint64_t                  npc_guid; //npc的GUID
	QuestAccomplishEx() = default;
};

struct HeroLockTargetAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{280};
	uint64_t                  hero_guid; //英雄guid
	uint64_t                  target_guid; //目标guid
	unsigned int              err; //错误码
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
	uint64_t                  player_guid; //玩家guid
	PlayerQueryEx() = default;
};

struct PlayerQueryBrdEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{284};
	uint64_t                  target_guid; //玩家guid
	unsigned int              target_userid; //目标 userid
	PlayerQueryBrdEx() = default;
};

struct GSVersion{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{285};
	char                      version[256]; //版本号
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
	unsigned char             type; //移动类型 0=走 1=跑
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned int              idx; //客户端序列号
	unsigned int              tick; //gate收到此包的tick
	uint64_t                  check; //校验码
	MoveReq2() = default;
};

struct SpellTarget2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{288};
	unsigned short            id; //技能id
	uint64_t                  target; //目标, 可能是player/monster/npc's guid
	unsigned short            idx; //~
	unsigned int              tick; //gate收到此包的tick
	uint64_t                  check; //校验码
	SpellTarget2() = default;
};

struct SpellGrid2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{289};
	unsigned short            id; //技能id
	unsigned short            target_x; //目标逻辑格的X坐标
	unsigned short            target_y; //目标逻辑格的Y坐标
	unsigned short            idx; //~
	uint64_t                  ref_target; //参照目标guid
	unsigned int              tick; //gate收到此包的tick
	uint64_t                  check; //校验码
	SpellGrid2() = default;
};

struct NpcSelect2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{290};
	uint64_t                  npc_guid; //npc的GUID
	uint64_t                  check; //校验码
	NpcSelect2() = default;
};

struct NpcTalkReq2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{291};
	uint64_t                  npc_guid; //npc的GUID
	char                      func[256]; //选择执行的NPC内容
	uint64_t                  check; //校验码
	NpcTalkReq2() = default;
};

struct ClientVerNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{292};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	uint64_t                  client_ver; //校验码
	ClientVerNtf() = default;
};

struct ItemApply2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{293};
	uint64_t                  item_guid; //物品GUID
	uint64_t                  check; //校验码
	ItemApply2() = default;
};

struct MonsterAppearNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{294};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned int              cur_hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
	unsigned char             servant_lv; //随从等级
	unsigned short            move_speed; //移动速度
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      master_name[32]; //主人的名字
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	short                     seed; //校验种子
	MonsterAppearNtf2() = default;
};

struct ItemAppearNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{295};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned short            skill_id; //技能id
	char                      item_name[32]; //物品名称
	short                     seed; //校验种子
	ItemAppearNtf2() = default;
};

struct ClientKeepAliveEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{296};
	int                       seed; //校验种子
	short                     opt_num; //选项
	int                       opt[10]; //区域信息
	ClientKeepAliveEx() = default;
};

struct GSVersionEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{297};
	unsigned char             version[256]; //版本号
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
	unsigned int              gs_tick; //GS发送此请求tick
	unsigned int              gt_tick; //GT发送此请求tick
	unsigned int              sg_tick; //SG发送此请求tick
	unsigned char             ping; //是否ping 1=开始 0=结束
	NetDelayReq() = default;
};

struct NetDelayAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{300};
	int                       sg_elpase; //SG从发出NetDelayReq到收到NetDelayAck的耗时
	int                       gt_elpase; //GT从发出NetDelayReq到收到NetDelayAck的耗时
	int                       gs_elpase; //GS从发出NetDelayReq到收到NetDelayAck的耗时
	int                       baidu_delay; //百度的延时
	int                       taobao_delay; //淘宝的延时
	char                      sg_id[256]; //云网关id
	NetDelayAck() = default;
};

struct ClientVerNtfEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{301};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	uint64_t                  client_ver; //校验码
	ClientVerNtfEx() = default;
};

struct ClientVerReq2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{302};
	unsigned int              version; //版本号
	unsigned int              data_len; //数据长度
	unsigned char             data[4096]; //数据
	ClientVerReq2() = default;
};

struct ClientVerAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{303};
	unsigned int              version; //版本号
	unsigned int              data_len; //数据长度
	unsigned char             data[4096]; //数据
	ClientVerAck2() = default;
};

struct NpcTalkReq3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{304};
	uint64_t                  npc_guid; //npc的GUID
	char                      func[256]; //选择执行的NPC内容
	unsigned char             check[32]; //校验码
	NpcTalkReq3() = default;
};

struct NpcTalkAck3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{305};
	unsigned short            width; //NPC对话框面板的宽度
	unsigned short            height; //NPC对话框面板的高度
	uint64_t                  npc_guid; //npc的GUID
	unsigned short            talk_len; //NPC面板内容长度
	char                      talk[7500]; //NPC面板显示的内容
	unsigned short            quest_state_num; //任务状态数据数量
	QUEST_STATE_INFO          quest_states[2]; //任务状态数据
	char                      comp; //是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
	unsigned char             check[32]; //校验码
	NpcTalkAck3() = default;
};

struct AttrShowNtfEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{306};
	uint64_t                  actor; //actor, 可能是player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, 可能是player/monster/npc's guid
	unsigned char             type; //0=普通 1=爆击
	int                       actor_hp_ref; //actor hp显示值
	int                       target_hp_ref; //目标hp显示值
	int                       target_hp; //目标hp绝对值
	int                       actor_mp_ref; //actor mp显示值
	int                       target_mp_ref; //目标mp显示值
	AttrShowNtfEx() = default;
};

struct EnterGSReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{307};
	unsigned char             entertype; //进入类型 0=上线 1=跳服
	uint64_t                  roleguid; //角色guid
	unsigned char             fangchenmi; //是否防沉迷用户 1：是 0：否
	unsigned char             clienttype; //客户端类型 0=客户端 1=页游 2=手游
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
	unsigned short            version; //版本
	unsigned char             zip; //是否压缩
	unsigned int              seed; //加密种子
	int                       size; //二进制数据大小
	unsigned char             buf[7936]; //二进制数据
	BehaviorNtf() = default;
};

struct FashionReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{310};
	unsigned char             enable; //0:脱下 1:穿上
	FashionReq() = default;
};

struct FashionNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{311};
	unsigned char             enable; //0:脱下 1:穿上
	FashionNtf() = default;
};

struct ErrorNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{312};
	char                      errmsg[256]; //错误描述
	ErrorNtf() = default;
};

struct NpcTalkReqEx3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{313};
	char                      func[256]; //选择执行的NPC内容
	unsigned char             check[32]; //校验码
	NpcTalkReqEx3() = default;
};

struct NpcTalkAckEx3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{314};
	unsigned short            width; //NPC对话框面板的宽度
	unsigned short            height; //NPC对话框面板的高度
	unsigned short            talk_len; //NPC面板内容长度
	char                      talk[8000]; //NPC面板显示的内容
	char                      comp; //是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
	unsigned char             check[32]; //校验码
	NpcTalkAckEx3() = default;
};

struct SubmitForm2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{315};
	char                      script_name[256]; //脚本名称
	char                      function_name[256]; //函数名称
	unsigned short            num; //参数个数
	PARAM_INFO                info[100]; //参数信息
	unsigned char             check[32]; //校验码
	SubmitForm2() = default;
};

struct SubmitFormAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{316};
	char                      script_name[256]; //脚本名称
	char                      result[256]; //反馈
	unsigned char             check[32]; //校验码
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
	int                       seed; //校验种子
	short                     opt_num; //选项
	int                       opt[128]; //区域信息
	GetClientCheckInfoAck() = default;
};

struct GetMD5CheckListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{320};
	uint64_t                  seed_1; //seed_1
	uint64_t                  seed_2; //seed_2
	unsigned short            md5_list_num; //md5列表数
	CHECK_BUFF                md5_list[128]; //md5列表
	GetMD5CheckListReq() = default;
};

struct GetMD5CheckListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{321};
	unsigned short            md5_list_num; //md5列表数
	unsigned short            check_num[128]; //md5列表数
	CHECK_BUFF                md5_list[128]; //md5列表
	GetMD5CheckListAck() = default;
};

struct DelayCloseNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{322};
	int                       delay; //延迟毫秒数
	DelayCloseNtf() = default;
};

struct FamilyJoinInviteReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{323};
	unsigned char             action; //操作类型 1=请求 2=邀请
	uint64_t                  family_guid; //请求加入行会的guid
	char                      invite_name[256]; //邀请加入行会玩家的姓名
	FamilyJoinInviteReq() = default;
};

struct FamilyJoinInviteAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{324};
	unsigned char             action; //操作类型 1=请求 2=邀请
	uint64_t                  family_guid; //请求加入行会的guid
	char                      invite_name[256]; //邀请加入行会玩家的姓名
	unsigned char             result; //0=允许 1=不允许
	FamilyJoinInviteAck() = default;
};

struct FamilyRelationShipReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{325};
	unsigned char             type; //类型：1、结盟；2、敌对
	char                      family_name[32]; //对方行会名称
	FamilyRelationShipReq() = default;
};

struct FamilyRelationShipAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{326};
	unsigned char             type; //类型：1、结盟；2、敌对
	char                      family_name[32]; //对方行会名称
	unsigned char             result; //0=允许 1=不允许
	FamilyRelationShipAck() = default;
};

struct MonsterAppearNtf3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{327};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned int              cur_hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
	unsigned char             servant_lv; //随从等级
	unsigned short            move_speed; //移动速度
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      master_name[32]; //主人的名字
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	unsigned short            attack_speed; //攻击速度
	CUSTOM_INFO               custom; //自定义数据
	MonsterAppearNtf3() = default;
};

struct MonsterAppearNtf4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{328};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned int              cur_hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
	unsigned char             servant_lv; //随从等级
	unsigned short            move_speed; //移动速度
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      master_name[32]; //主人的名字
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	short                     seed; //校验种子
	unsigned short            attack_speed; //攻击速度
	CUSTOM_INFO               custom; //自定义数据
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
	unsigned char             list_size; //列表大小
	TEAM_MEMBER               list_data[20]; //列表内容
	GetAroundTeamAck() = default;
};

struct MigrateRoleDataNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{331};
	uint64_t                  role_guid; //玩家guid
	char                      user_name[256]; //账号名
	unsigned int              dst_zone_id; //目标区id
	unsigned int              status; //1=迁移开始 2=迁移结束
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	MigrateRoleDataNtf() = default;
};

struct PlayerAppearNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{332};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //名称
	unsigned char             gender; //性别
	unsigned char             job; //职业
	unsigned char             status; //人物状态 0=活着 1=死亡
	unsigned short            head; //头像
	unsigned int              level; //等级
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned short            hair; //头发
	unsigned short            hair_color; //头发颜色
	unsigned short            body; //身体
	unsigned short            weapon; //武器
	unsigned short            wings; //翅膀
	unsigned short            mount; //坐骑
	unsigned short            weapon_effect; //武器特效
	unsigned short            body_effect; //身体特效
	unsigned short            mount_effect; //坐骑特效
	unsigned int              hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned int              mp; //当前mp
	unsigned int              max_mp; //最大mp
	int                       pk; //pk
	unsigned short            move_speed; //移动速度
	unsigned short            attack_speed; //攻击速度
	unsigned short            title; //称号
	unsigned char             has_team; //是否有队伍
	unsigned char             stall; //0: 未摆摊 1: 摆摊准备 2: 摆摊中
	char                      stall_name[32]; //摆摊名称
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      family_name[32]; //行会名称
	char                      castle_name[256]; //城堡名称，可以多个用与符号分隔
	char                      family_title[32]; //行会称号
	char                      alias[64]; //别名
	CUSTOM_INFO               custom; //自定义数据
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	unsigned short            amulet; //法宝
	unsigned short            equip_num; //扩展装备数量
	EQUIP_INFO                equips[10]; //扩展装备信息
	PlayerAppearNtf2() = default;
};

struct RoleAppNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{333};
	uint64_t                  player_guid; //player guid
	unsigned short            hair; //头发
	unsigned short            hair_color; //头发颜色
	unsigned short            body; //身体
	unsigned short            weapon; //武器
	unsigned short            wings; //翅膀
	unsigned short            mount; //坐骑
	unsigned short            weapon_effect; //武器特效
	unsigned short            body_effect; //身体特效
	unsigned short            mount_effect; //坐骑特效
	unsigned short            amulet; //法宝
	unsigned short            equip_num; //扩展装备数量
	EQUIP_INFO                equips[10]; //扩展装备信息
	RoleAppNtf2() = default;
};

struct ItemBatchDestroyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{334};
	unsigned char             num; //物品数量
	uint64_t                  guids[200]; //物品guids
	ItemBatchDestroyNtf() = default;
};

struct SubmitForm3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{335};
	unsigned int              form_count; //表单计数
	unsigned char             script_name[256]; //脚本名称
	unsigned char             function_name[256]; //函数名称
	unsigned short            num; //参数个数
	PARAM_INFO2               info[100]; //参数信息
	SubmitForm3() = default;
};

struct SubmitFormAck3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{336};
	char                      script_name[256]; //脚本名称
	char                      result[256]; //反馈
	SubmitFormAck3() = default;
};

struct ItemAppearNtf3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{337};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //模板id
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned short            skill_id; //技能id
	char                      item_name[64]; //物品名称
	unsigned char             is_drop; //是否是掉落出现
	ItemAppearNtf3() = default;
};

struct ItemAppearNtf4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{338};
	uint64_t                  item_guid; //item guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned short            skill_id; //技能id
	char                      item_name[64]; //物品名称
	short                     seed; //校验种子
	unsigned char             is_drop; //是否是掉落出现
	ItemAppearNtf4() = default;
};

struct InnerForceLevelUpReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{339};
	unsigned char             type; //0 升一级 1 升到最高
	InnerForceLevelUpReq() = default;
};

struct InnerForceLevelUpAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{340};
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	InnerForceLevelUpAck() = default;
};

struct ClientFangChenMiNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{341};
	unsigned char             type; //类型，0=HOUR_1 1=HOUR_2 2=HOUR_3 3=HOUR_3_H 4=HOUR_4 5=HOUR_4_H 6=HOUR_5 7=HOUR_5_1 8=HOUR_5_2 9=HOUR_5_3 10=HOUR_6
	ClientFangChenMiNtf() = default;
};

struct DelegateMineAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{342};		// PROTO_CLIENT3_DELEGATE_MINE_ACK2
	unsigned int              count_buy; //买入数量
	unsigned int              count_sell; //卖出数量
	DELEGATE_BUY_ITEM2        buy_items[5];
	DELEGATE_SELL_ITEM        sell_items[5];
	DelegateMineAck2() = default;
};

struct DelegateBuyListAck2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{343};		// PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK2
	unsigned short            type; //分类
	unsigned short            subtype; //子分类
	unsigned int              total; //总数
	unsigned int              start; //起始序列号
	unsigned int              count; //申请数量
	DELEGATE_BUY_ITEM2        items[20]; //物品列表
	DelegateBuyListAck2() = default;
};

struct FashionWeaponReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{344};
	unsigned char             enable; //0:卸下 1:装备上
	FashionWeaponReq() = default;
};

struct FashionWeaponNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{345};
	unsigned char             enable; //0:卸下 1:装备上
	FashionWeaponNtf() = default;
};

struct PlayerAppearNtf3{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{346};
	uint64_t                  player_guid; //player guid
	char                      name[128]; //名称
	unsigned char             gender; //性别
	unsigned char             job; //职业
	unsigned char             status; //人物状态 0=活着 1=死亡
	unsigned short            head; //头像
	unsigned int              level; //等级
	unsigned short            dst_x; //目标点x
	unsigned short            dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned short            hair; //头发
	unsigned short            hair_color; //头发颜色
	unsigned short            body; //身体
	unsigned short            weapon; //武器
	unsigned short            wings; //翅膀
	unsigned short            mount; //坐骑
	unsigned short            weapon_effect; //武器特效
	unsigned short            body_effect; //身体特效
	unsigned short            mount_effect; //坐骑特效
	unsigned int              hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned int              mp; //当前mp
	unsigned int              max_mp; //最大mp
	int                       pk; //pk
	unsigned short            move_speed; //移动速度
	unsigned short            attack_speed; //攻击速度
	unsigned short            title; //称号
	unsigned char             has_team; //是否有队伍
	unsigned char             stall; //0: 未摆摊 1: 摆摊准备 2: 摆摊中
	char                      stall_name[32]; //摆摊名称
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      family_name[32]; //行会名称
	char                      castle_name[256]; //城堡名称，可以多个用与符号分隔
	char                      family_title[32]; //行会称号
	char                      alias[64]; //别名
	CUSTOM_INFO               custom; //自定义数据
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	unsigned short            amulet; //法宝
	unsigned short            equip_num; //扩展装备数量
	EQUIP_INFO                equips[10]; //扩展装备信息
	unsigned int              inner_force; //当前内功
	unsigned int              max_inner_force; //最大内功
	unsigned short            reserve_num; //保留字段数量
	unsigned int              reserve_values[10]; //保留字段
	PlayerAppearNtf3() = default;
};

struct MonsterAppearNtf5{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{347};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned int              cur_hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
	unsigned char             servant_lv; //随从等级
	unsigned short            move_speed; //移动速度
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      master_name[32]; //主人的名字
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	unsigned short            attack_speed; //攻击速度
	CUSTOM_INFO               custom; //自定义数据
	unsigned int              inner_force; //当前内功
	unsigned int              max_inner_force; //最大内功
	unsigned short            reserve_num; //保留字段数量
	unsigned int              reserve_values[10]; //保留字段
	MonsterAppearNtf5() = default;
};

struct MonsterAppearNtf6{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{348};
	uint64_t                  monster_guid; //monster guid
	unsigned short            template_id; //模板id
	int                       dst_x; //目标点x
	int                       dst_y; //目标点y
	unsigned char             dir; //方向
	unsigned int              cur_hp; //当前血量
	unsigned int              max_hp; //最大血量
	unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
	unsigned char             servant_lv; //随从等级
	unsigned short            move_speed; //移动速度
	unsigned short            buff_num; //Buff数量
	BUFF_INFO                 buffs[50]; //Buff信息
	char                      master_name[32]; //主人的名字
	unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
	short                     seed; //校验种子
	unsigned short            attack_speed; //攻击速度
	CUSTOM_INFO               custom; //自定义数据
	unsigned int              inner_force; //当前内功
	unsigned int              max_inner_force; //最大内功
	unsigned short            reserve_num; //保留字段数量
	unsigned int              reserve_values[10]; //保留字段
	MonsterAppearNtf6() = default;
};

struct CaptchaReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{349};
	unsigned short            seed; //种子
	unsigned short            type; //类型
	unsigned short            timeout; //倒计时
	unsigned char             qsize; //问题数据大小
	char                      qvalue[256]; //问题数据值
	unsigned short            size; //数据大小
	char                      value[4096]; //数据值
	CaptchaReq() = default;
};

struct CaptchaAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{350};
	unsigned char             check1; //选项1
	unsigned short            size1; //数据1大小
	char                      value1[256]; //数据1值
	unsigned char             check2; //选项2
	unsigned short            size2; //数据2大小
	char                      value2[256]; //数据2值
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
	char                      key[128]; //代理key
	AgentKeyAck() = default;
};

struct PlatformInfoNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{353};
	char                      platform[256]; //平台名称
	char                      info[4096]; //平台信息
	PlatformInfoNtf() = default;
};

struct AttrShowNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{354};
	uint64_t                  actor; //actor, 可能是player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, 可能是player/monster/npc's guid
	unsigned char             type; //0=普通 1=爆击
	int                       actor_hp_ref; //actor hp显示值
	int                       target_hp_ref; //目标hp显示值
	int                       target_hp; //目标hp绝对值
	int                       target_mp; //目标mp绝对值
	unsigned char             reserve_size; //保留字段数量
	int                       reserve[10]; //保留字段
	AttrShowNtf2() = default;
};

struct AttrShowNtfEx2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{355};
	uint64_t                  actor; //actor, 可能是player/monster/npc's guid
	unsigned short            skill_id; //skill id
	uint64_t                  target; //target, 可能是player/monster/npc's guid
	unsigned char             type; //0=普通 1=爆击
	int                       actor_hp_ref; //actor hp显示值
	int                       target_hp_ref; //目标hp显示值
	int                       target_hp; //目标hp绝对值
	int                       target_mp; //目标mp绝对值
	int                       actor_mp_ref; //actor mp显示值
	int                       target_mp_ref; //目标mp显示值
	unsigned char             reserve_size; //保留字段数量
	int                       reserve[10]; //保留字段
	AttrShowNtfEx2() = default;
};

struct BehaviorReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{356};
	unsigned int              seed; //加密种子
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
	unsigned char             size; //商店数量数量
	unsigned short            shops[20]; //商店id
	NpcShopIdsNtf() = default;
};

struct CreateMobaRoomReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{359};
	unsigned short            room_mode; //房间模式
	unsigned short            vs_num; //对战各方的最大人数
	unsigned short            map_id; //对战地图的map表对应索引
	char                      room_pwd[256]; //房间密码
	char                      room_name[256]; //房间名称
	CreateMobaRoomReq() = default;
};

struct CreateMobaRoomAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{360};
	int                       room_id; //创建失败room id = 0
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	CreateMobaRoomAck() = default;
};

struct EnterMobaRoomReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{361};
	int                       room_id; //room id
	char                      room_pwd[256]; //房间密码
	EnterMobaRoomReq() = default;
};

struct EnterMobaRoomAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{362};
	int                       room_id; //room id
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
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
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	ExitMobaRoomAck() = default;
};

struct GetMobaRoomListReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{365};
	unsigned short            begin_pos; //列表在总列表的其实位置 0为第一个房间
	GetMobaRoomListReq() = default;
};

struct MobaRoomListAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{366};
	unsigned short            begin_pos; //列表在总列表的其实位置 0为第一个房间
	unsigned short            all_pos; //总列表一共多少位置
	unsigned short            room_num; //列表信息中的信息数
	MOBA_ROOM_INFO            room_list[64]; //列表信息
	MobaRoomListAck() = default;
};

struct MobaRoomMemberListNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{367};
	int                       room_id; //room id
	unsigned char             member_num; //列表信息中的信息数
	MOBA_ROOM_MEMBER_INFO     member_list[256]; //列表信息
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
	uint64_t                  guid; //玩家guid
	MobaRoomKickReq() = default;
};

struct MobaRoomKickAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{370};
	uint64_t                  guid; //玩家guid
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
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
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	MobaRoomCampReadyAck() = default;
};

struct MobaRoomCampReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{374};
	unsigned char             camp; //阵营 1=red 2=blue
	unsigned char             yes; //0 未准备 1 已准备
	MobaRoomCampReadyNtf() = default;
};

struct MobaRoomGameStartNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{375};
	int                       room_id; //room id
	unsigned char             success; //成功与否 0 失败 1 成功
	MobaRoomGameStartNtf() = default;
};

struct MobaRoomSetViceHostReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{376};
	uint64_t                  guid; //玩家guid
	MobaRoomSetViceHostReq() = default;
};

struct MobaRoomSetViceHostAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{377};
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	MobaRoomSetViceHostAck() = default;
};

struct MobaRoomToggleCampReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{378};
	uint64_t                  guid; //玩家guid
	MobaRoomToggleCampReq() = default;
};

struct MobaRoomToggleCampAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{379};
	uint64_t                  guid; //玩家guid
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
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
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	MobaRoomMemberReadyAck() = default;
};

struct MobaRoomMemberReadyNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{383};
	uint64_t                  guid; //玩家guid
	unsigned char             yes; //0 未准备 1 已准备
	MobaRoomMemberReadyNtf() = default;
};

struct MobaRoomUpdateNameAndPasswordReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{384};
	char                      room_name[256]; //房间名称
	char                      room_pwd[256]; //房间密码
	MobaRoomUpdateNameAndPasswordReq() = default;
};

struct MobaRoomUpdateNameAndPasswordAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{385};
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	MobaRoomUpdateNameAndPasswordAck() = default;
};

struct MobaRoomNameUpdateNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{386};
	int                       room_id; //room id
	char                      room_name[256]; //房间名称
	MobaRoomNameUpdateNtf() = default;
};

struct MobaRoomChangeCampAndPosReq{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{387};
	unsigned char             change_camp; //是否更改阵营
	unsigned char             pos; //更改的位置
	MobaRoomChangeCampAndPosReq() = default;
};

struct MobaRoomChangeCampAndPosAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{388};
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
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
	unsigned short            size; //内容字节数
	unsigned char             content[4224]; //内容
	GameGuardReq() = default;
};

struct GameGuardAck{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{391};
	unsigned short            size; //内容字节数
	unsigned char             content[4224]; //内容
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
	unsigned short            size; //报告内容字节数
	unsigned char             content[4224]; //报告内容
	GameGuardHackRpt() = default;
};

struct GameGuardHeartBeat{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{394};
	unsigned int              seed; //种子
	unsigned short            size; //字节数
	unsigned char             content[6144]; //内容
	GameGuardHeartBeat() = default;
};

struct BangcleHeartBeat{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{395};
	unsigned int              seed; //种子
	unsigned short            size; //字节数
	unsigned char             content[6144]; //内容
	BangcleHeartBeat() = default;
};

struct TradeStallSetBuyList{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{396};
	unsigned short            buy_num; //物品种类数量
	unsigned short            item_ids[25]; //物品模板ID
	unsigned short            item_nums[25]; //单种物品收购数量
	unsigned char             price_types[25]; //物品价格类型 0=金币 1=元宝 2=积分
	int64_t                   item_prices[25]; //物品价格
	TradeStallSetBuyList() = default;
};

struct TradeStallQueryBuyGoodsNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{397};
	uint64_t                  player_guid; //player guid
	unsigned short            buy_num; //物品种类数量
	unsigned short            item_ids[25]; //物品模板ID
	unsigned short            item_nums[25]; //单种物品收购数量
	unsigned char             price_types[25]; //物品价格类型 0=金币 1=元宝 2=积分
	int64_t                   item_prices[25]; //物品价格
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
	uint64_t                  buyer_guid; //买家
	uint64_t                  seller_guid; //卖家
	uint64_t                  item_guid; //item's guid
	unsigned short            item_id; //物品id
	unsigned short            item_amount; //item's amount
	unsigned char             price_type; //物品价格类型 0=金币 1=元宝 2=积分
	int64_t                   price; //物品价格
	TradeStallSellNtf() = default;
};

struct TaobaoNpcShopReqEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{400};
	unsigned short            shop_id; //shop_index
	unsigned char             item_type; //物品类型
	unsigned char             item_index; //第一个商品在所有商品中的索引，0开始
	unsigned char             item_count; //请求商品数量
	TaobaoNpcShopReqEx() = default;
};

struct TaobaoNpcShopAckEx{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{401};
	unsigned short            shop_id; //shop_index
	unsigned char             item_type; //物品类型
	unsigned char             total_count; //商品总数量
	unsigned char             item_index; //第一个商品在所有商品中的索引，0开始
	unsigned char             item_count; //当前发送商品数量
	TAOBAO_ITEM_INFO          item_list[20]; //商品信息列表
	TaobaoNpcShopAckEx() = default;
};

struct SkillCDChangedNtf{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{402};
	unsigned short            skill_id; //技能ID
	unsigned int              new_cd; //技能冷却时间
	SkillCDChangedNtf() = default;
};

struct SubmitForm4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{403};
	unsigned int              form_count; //表单计数
	unsigned char             script_name[256]; //脚本名称
	unsigned char             function_name[256]; //函数名称
	unsigned short            num; //参数个数
	PARAM_INFO2               info[100]; //参数信息
	SubmitForm4() = default;
};

struct SubmitFormAck4{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{404};
	char                      script_name[256]; //脚本名称
	char                      result[256]; //反馈
	SubmitFormAck4() = default;
};

struct QuestAddNtf2{
	const unsigned short      moudleid{3};
	const unsigned short      protocolid{405};
	unsigned short            quest_id; //任务模板id
	char                      quest_name[256]; //任务的名称
	unsigned char             quest_type; //任务的类型, 显示用
	unsigned short            group_huntings_len; //组打怪计数
	QUEST_HUNTING_INFO        group_huntings[20]; //组打怪数据
	unsigned short            huntings_len; //打怪计数
	QUEST_HUNTING_INFO        huntings[20]; //打怪数据
	unsigned short            huntlevels_len; //打等级怪计数
	QUEST_HUNTLEVEL_INFO      huntlevels[20]; //打等级怪数据
	unsigned short            group_items_len; //组物品收集
	QUEST_ITEM_INFO           group_items[20]; //组收集数据
	unsigned short            collect_items_len; //物品收集
	QUEST_ITEM_INFO           collect_items[20]; //收集数据
	unsigned short            apply_items_len; //物品使用
	QUEST_ITEM_INFO           apply_items[20]; //收集使用
	unsigned short            npcs_len; //Npc
	QUEST_NPC_INFO            npcs[20]; //npc访问
	unsigned char             track_enabled; //是否开启追踪
	unsigned int              life; //剩余时间
	char                      progressing[256]; //任务进行时追踪文本
	char                      accomplishing[256]; //任务完成时追踪文本
	QuestAddNtf2() = default;
};

struct SkillCDPermenantChangedNtf { // 技能冷却永久重设通知
    const unsigned short      moudleid{3};
    const unsigned short      protocolid{406};
    unsigned short            skill_id; //技能ID
    unsigned int              new_cd; //技能冷却时间
    SkillCDPermenantChangedNtf() = default;
};

#pragma warning( pop ) 
//===============数据定义结束===============
//===============打包解包函数定义开始===============
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
//===============打包解包函数定义结束===============
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

//===============以下协议回调函数需要使用者来实现===============
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
