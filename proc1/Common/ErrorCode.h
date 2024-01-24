#pragma once

enum ErrorCode
{
	error_ok,
    error_nullptr,
    error_exception,
    error_invalid_cfg_value,
    error_not_player,

	//技能相关
	error_skill_begin = 100,
	error_skill_cfg_not_exist,							//技能配置不存在
	error_skill_not_exist,								//技能不存在
	error_skill_role_not_exist,							//角色不存在
	error_skill_master_die,								//死亡状态不能使用技能
	error_skill_stall,									//摆摊状态不能使用技能
	error_skill_rush,									//冲锋状态不能使用技能
	error_skill_back,									//被击退状态不能使用技能
	error_skill_in_cd,									//技能尚未冷却
	error_skill_mp_not_enough,							//技能耗蓝不足
    error_skill_out_of_range,                           //不在范围内
    error_skill_target_not_exist,                       //目标不存在
    error_skill_inactive,                               //开关技能未打开
    error_skill_no_fire_time,                           //烈火时间为0
    error_skill_not_player,                             //不是玩家
	error_skill_end = error_skill_begin + 200,

	//移动相关
	error_move_begin = error_skill_end + 1,
	error_move_role_not_exist,							//角色不存在
	error_move_map_not_exist,							//地图不存在
	error_move_point_forbid,							//当前点不可达
	error_move_role_cant_move,							//角色不可移动
	error_move_stall,									//摆摊状态不能移动
	error_move_rush,									//冲锋状态不能移动
	error_move_back,									//被击退状态不能移动
	error_move_same_pos,								//目标点跟当前点是同一个位置
	error_move_pos_cant_reach,							//移动失败，目标点不可达
	error_move_map_aoi_not_exist,						//mapaoi 不存在
    error_move_invalid_speed,                           //移动速度无效
	error_move_end = error_move_begin + 200,
};

enum
{
    move_result_success = 0,
    move_result_fail = 1
};
