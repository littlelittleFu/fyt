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
    uint16_t HelmetID;      //ͷ��ID
    uint16_t ClothesID;     //�·�ID
    uint16_t WeaponID;      //����ID
    uint16_t ManWeaponID;   //����ID
    uint16_t WManWeaponID;  //����ID
    uint16_t WeaponItemID;  //����ID
    uint16_t WingsID;       //���ID
    uint16_t MountID;       //����ID
    uint16_t MountShadowID; //����ID
    uint16_t MountItemID;   //����ID
    uint16_t ShadowID;      //Ӱ��ID
    uint16_t WeaponEffect;  //������Ч
    uint16_t BodyEffect;    //������Ч
    uint16_t MountEffect;   //������Ч
    uint16_t MagicWeapID;	//����
    uint16_t ShieldID;		//����
    uint32_t HairColor;     //������ɫ
    uint32_t HairStyle;     //����
    uint32_t Header;        //ͷ��

};
