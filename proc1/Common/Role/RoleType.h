#pragma once

enum RoleType
{
	role_type_none,						//��Ч�Ľ�ɫ����
	role_type_player,					//���
	role_type_npc,						//npc
	role_type_monster,					//����
	role_type_pet,                      //����
	role_type_stall_dummy,		        //��Ұ�̯ģ��
    role_type_player_doplganr,         //��ҵķ���

	role_type_cnt,
};

enum custRoleType
{
	cust_role_red_name,                //�������
};

//�������ͣ���Ӧmonster.xml�е�Type�ֶ�
enum
{
	monster_type_normal = 1,			//��ͨ��
	monster_type_elite = 2,				//��Ӣ��
	monster_type_leader = 3,			//ͷĿ
	monster_type_boss = 4,				//BOSS
	monster_type_guard = 5,				//����
	monster_type_protector = 6,			//�سǹ�
	monster_type_biaoche = 7,			//�ڳ�
    monster_type_treasure = 8,          //����
};
