#pragma once
#include "RoleAction.h"


class RoleAvatar : public RoleAction
{
public:
    RoleAvatar(Role* master = nullptr);
    ~RoleAvatar();

public:
    bool Init() override;
    void Update(int32_t delta) override;

public:
    uint16_t HelmetID;      //头盔ID
    uint16_t ClothesID;     //衣服ID
    uint16_t WeaponID;      //武器ID
    uint16_t ManWeaponID;   //武器ID
    uint16_t WManWeaponID;  //武器ID
    uint16_t WeaponItemID;  //武器ID
    uint16_t WingsID;       //翅膀ID
    uint16_t MountID;       //坐骑ID
    uint16_t MountShadowID; //坐骑ID
    uint16_t MountItemID;   //坐骑ID
    uint16_t ShadowID;      //影子ID
    uint16_t WeaponEffect;  //武器特效
    uint16_t BodyEffect;    //身体特效
    uint16_t MountEffect;   //坐骑特效
    uint16_t MagicWeapID;	//法宝
    uint16_t ShieldID;		//盾牌
    uint32_t HairColor;     //发型颜色
    uint32_t HairStyle;     //发型
    uint32_t Header;        //头像

};
