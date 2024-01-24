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
    char family_name[64];  //行会名称
    char castle_name[256]; //城堡名称，可以多个用与符号分隔
    char family_title[64]; //行会称号
    char master_name[64];  // 师傅名称
    char lover_name[64];   // 配偶姓名

};
