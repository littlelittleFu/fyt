#pragma once

enum RoleType
{
	role_type_none,						//无效的角色类型
	role_type_player,					//玩家
	role_type_npc,						//npc
	role_type_monster,					//怪物
	role_type_pet,                      //宠物
	role_type_stall_dummy,		        //玩家摆摊模型
    role_type_player_doplganr,         //玩家的分身

	role_type_cnt,
};

enum custRoleType
{
	cust_role_red_name,                //红名玩家
};

//怪物类型，对应monster.xml中的Type字段
enum
{
	monster_type_normal = 1,			//普通怪
	monster_type_elite = 2,				//精英怪
	monster_type_leader = 3,			//头目
	monster_type_boss = 4,				//BOSS
	monster_type_guard = 5,				//守卫
	monster_type_protector = 6,			//守城怪
	monster_type_biaoche = 7,			//镖车
    monster_type_treasure = 8,          //宝物
};
