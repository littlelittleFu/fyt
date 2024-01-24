#pragma once

#include <string>
#include "ISubject.h"

#define ROLE_ACTION_ATTR_START     100
#define ROLE_ACTION_ATTR_LEN       1000
#define ROLE_ACTION_ATTR_END       ROLE_ACTION_ATTR_START+ROLE_ACTION_ATTR_LEN-1

#define ROLE_ACTION_STATE_START    ROLE_ACTION_ATTR_END+1
#define ROLE_ACTION_STATE_LEN      100
#define ROLE_ACTION_STATE_END      ROLE_ACTION_STATE_START+ROLE_ACTION_STATE_LEN-1
								   
#define ROLE_ACTION_MOVE_START     ROLE_ACTION_STATE_END+1
#define ROLE_ACTION_MOVE_LEN       1000
#define ROLE_ACTION_MOVE_END	   ROLE_ACTION_MOVE_START+ROLE_ACTION_MOVE_LEN-1
								   
#define ROLE_ACTION_SKILL_START    ROLE_ACTION_MOVE_END+1
#define ROLE_ACTION_SKILL_LEN      2000
#define ROLE_ACTION_SKILL_END      ROLE_ACTION_SKILL_START+ROLE_ACTION_SKILL_LEN-1
								   
#define ROLE_ACTION_BUFF_START     ROLE_ACTION_SKILL_END+1
#define ROLE_ACTION_BUFF_LEN       1000
#define ROLE_ACTION_BUFF_END       ROLE_ACTION_BUFF_START+ROLE_ACTION_BUFF_LEN-1
								   
#define ROLE_ACTION_PACK_START     ROLE_ACTION_BUFF_END+1
#define ROLE_ACTION_PACK_LEN       5000
#define ROLE_ACTION_PACK_END       ROLE_ACTION_PACK_START+ROLE_ACTION_PACK_LEN-1

#define ROLE_ACTION_AVATAR_START   ROLE_ACTION_PACK_END+1
#define ROLE_ACTION_AVATAR_LEN     5000
#define ROLE_ACTION_AVATAR_END     ROLE_ACTION_AVATAR_START+ROLE_ACTION_AVATAR_LEN-1

#define ROLE_ACTION_RELATION_START ROLE_ACTION_AVATAR_END+1
#define ROLE_ACTION_RELATION_LEN   1000
#define ROLE_ACTION_RELATION_END   ROLE_ACTION_RELATION_START+ROLE_ACTION_RELATION_LEN-1


#define ROLE_ACTION_TASK_START     ROLE_ACTION_RELATION_END+1
#define ROLE_ACTION_TASK_LEN       5000
#define ROLE_ACTION_TASK_END       ROLE_ACTION_TASK_START+ROLE_ACTION_TASK_LEN-1


#define ROLE_ACTION_EQUIP_START	   ROLE_ACTION_TASK_END+1
#define ROLE_ACTION_EQUIP_LEN	   5000
#define ROLE_ACTION_EQUIP_END      ROLE_ACTION_EQUIP_START+ROLE_ACTION_EQUIP_LEN-1

#define ROLE_ACTION_TEAM_START	   ROLE_ACTION_EQUIP_END+1
#define ROLE_ACTION_TEAM_LEN	   5000
#define ROLE_ACTION_TEAM_END       ROLE_ACTION_TEAM_START+ROLE_ACTION_TEAM_LEN-1

#define ROLE_ACTION_VIP_START	   ROLE_ACTION_TEAM_END+1
#define ROLE_ACTION_VIP_LEN		   1000
#define ROLE_ACTION_VIP_END        ROLE_ACTION_VIP_START+ROLE_ACTION_VIP_LEN-1


enum
{
	role_action_min,
	role_action_attr = role_action_min,
	role_action_state,
	role_action_move,//2
	role_action_skill,
	role_action_buff,
	role_action_pack,
	role_action_avatar,
	role_action_relation,
	role_action_task,
	role_action_equip,
	role_action_team,
	role_action_vip,
	role_action_max
};

enum
{
	//detail attr action
	role_action_attr_start = ROLE_ACTION_ATTR_START,
	role_action_attr_role_id,
	role_action_attr_role_name,
	role_action_attr_role_alias,
	role_action_attr_role_status,
	role_action_attr_role_posx,
	role_action_attr_role_posy,
	role_action_attr_role_dir,
	role_action_attr_role_property,
	role_action_attr_role_property64,
	role_action_attr_end = ROLE_ACTION_ATTR_END,

	//detail state action
	role_action_state_start = ROLE_ACTION_STATE_START,
	role_action_state_role_state,
	role_action_state_end = ROLE_ACTION_STATE_END,

	//detail move action
	role_action_move_start = ROLE_ACTION_MOVE_START,
	role_action_move_role_ismoveing,
	role_action_move_role_tarx,
	role_action_move_role_tary,
	role_action_move_role_time_elapsed,
	role_action_move_end = ROLE_ACTION_MOVE_END,

	//detail skill action
	role_action_skill_start = ROLE_ACTION_SKILL_START,
	role_action_skill_role_skill_list,
	role_action_skill_end = ROLE_ACTION_SKILL_END,

	//detail buff action
	role_action_buff_start = ROLE_ACTION_BUFF_START,
	role_action_buff_role_buff_id,
	role_action_buff_role_skill_id,
	role_action_buff_role_buff_level,
	role_action_buff_role_buff_duration,
	role_action_buff_end = ROLE_ACTION_BUFF_END,

	//detail pack action
	role_action_pack_start = ROLE_ACTION_PACK_START,
	role_action_pack_end = ROLE_ACTION_PACK_END,


	//detail avatar action
	role_action_avatar_start = ROLE_ACTION_AVATAR_START,
	role_action_avatar_role_helmet_id,
	role_action_avatar_role_clothes_id,
	role_action_avatar_role_weapon_id,
	role_action_avatar_role_man_weapon_id,
	role_action_avatar_role_woman_weapon_id,
	role_action_avatar_role_weapon_item_id,
	role_action_avatar_role_wings_id,
	role_action_avatar_role_mount_id,
	role_action_avatar_role_mount_shadow_id,
	role_action_avatar_role_mount_item_id,
	role_action_avatar_role_shadow_id,
	role_action_avatar_role_weapon_effect,
	role_action_avatar_role_body_effect,
	role_action_avatar_role_mount_effect,
	role_action_avatar_role_magic_weap_id,
	role_action_avatar_role_shield_id,
	role_action_avatar_role_hair_color,
	role_action_avatar_role_hair_style,
	role_action_avatar_role_header,
	role_action_avatar_end = ROLE_ACTION_AVATAR_END,


	//detail relation action
	role_action_relation_start = ROLE_ACTION_RELATION_START,
	role_action_relation_family_name,
	role_action_relation_castle_name,
	role_action_relation_family_title,
	role_action_relation_master_name,
	role_action_relation_lover_name,
	role_action_relation_end = ROLE_ACTION_RELATION_END,

	//detail task action
	role_action_task_start = ROLE_ACTION_TASK_START,
	role_action_task_end = ROLE_ACTION_TASK_END,

	//detail equip action
	role_action_equip_start = ROLE_ACTION_EQUIP_START,
	role_action_equip_end = ROLE_ACTION_EQUIP_END
};

class Role;
class Player;
class PlayerDoplganr;

class RoleAction:public ISubject
{
public:
	RoleAction(Role* master = nullptr);
	virtual ~RoleAction();

public:
	virtual bool Init() { return true; };
	virtual void Update(int32_t delta) {};
	virtual Role* GetMaster() { return mMaster; }
	virtual const std::string & GetScriptName();
	virtual void UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue) {}
	virtual void CopyFromOwner(RoleAction* ra) {}
    void SetNeedUpdate(int flag);
    void ResetNeedUpdate(int flag);

protected:
    Player * GetPlayer();
    PlayerDoplganr * GetPlayerDoplganr();

protected:
	Role* mMaster;
};
