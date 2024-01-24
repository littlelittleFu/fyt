#pragma once
#include "RoleAction.h"


class RoleRelation : public RoleAction
{
public:
    RoleRelation(Role* master = nullptr);
    ~RoleRelation();

public:
    bool Init() override;
    void Update(int32_t delta) override;

public:
    char family_name[64];  //�л�����
    char castle_name[256]; //�Ǳ����ƣ����Զ��������ŷָ�
    char family_title[64]; //�л�ƺ�
    char master_name[64];  // ʦ������
    char lover_name[64];   // ��ż����

};
