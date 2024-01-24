#pragma once

enum ErrorCode
{
	error_ok,
    error_nullptr,
    error_exception,
    error_invalid_cfg_value,
    error_not_player,

	//�������
	error_skill_begin = 100,
	error_skill_cfg_not_exist,							//�������ò�����
	error_skill_not_exist,								//���ܲ�����
	error_skill_role_not_exist,							//��ɫ������
	error_skill_master_die,								//����״̬����ʹ�ü���
	error_skill_stall,									//��̯״̬����ʹ�ü���
	error_skill_rush,									//���״̬����ʹ�ü���
	error_skill_back,									//������״̬����ʹ�ü���
	error_skill_in_cd,									//������δ��ȴ
	error_skill_mp_not_enough,							//���ܺ�������
    error_skill_out_of_range,                           //���ڷ�Χ��
    error_skill_target_not_exist,                       //Ŀ�겻����
    error_skill_inactive,                               //���ؼ���δ��
    error_skill_no_fire_time,                           //�һ�ʱ��Ϊ0
    error_skill_not_player,                             //�������
	error_skill_end = error_skill_begin + 200,

	//�ƶ����
	error_move_begin = error_skill_end + 1,
	error_move_role_not_exist,							//��ɫ������
	error_move_map_not_exist,							//��ͼ������
	error_move_point_forbid,							//��ǰ�㲻�ɴ�
	error_move_role_cant_move,							//��ɫ�����ƶ�
	error_move_stall,									//��̯״̬�����ƶ�
	error_move_rush,									//���״̬�����ƶ�
	error_move_back,									//������״̬�����ƶ�
	error_move_same_pos,								//Ŀ������ǰ����ͬһ��λ��
	error_move_pos_cant_reach,							//�ƶ�ʧ�ܣ�Ŀ��㲻�ɴ�
	error_move_map_aoi_not_exist,						//mapaoi ������
    error_move_invalid_speed,                           //�ƶ��ٶ���Ч
	error_move_end = error_move_begin + 200,
};

enum
{
    move_result_success = 0,
    move_result_fail = 1
};
