#pragma once

#include <string>
#include "Role.h"
#include "ProtoMS.h"
#include "CNetManager.h"

#include "SessionFactory.h"
class CLuaScript;


class Player;
class Monster;
class Role;
class Npc;
class LuaHost
{
    DECL_SINGLETON(LuaHost);

public:             // ע��ΪLUA API��Ҫpublic
    LuaHost() {}
    ~LuaHost() {}

public:
    void            RegisterLuaAPI(CLuaScript *luaScript);

public:             // Global export functions
    /**
    * @brief            ��ȡ��Ϸ������
    * @param propType   global_prop_type_min - global_prop_type_max
    * @return           ����bool   
    *                   ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetGlobalProp(uint16_t propType);
    /**
    * @brief            ��ȡ��ɫ�ȼ������� role.csv
    * @param level      �ȼ�
    * @param job        ְҵ
    * @param propType   role_prop_type_min -role_prop_type_max
    * @return           ����bool   
    *                   ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetRoleCfgValue(uint32_t level, uint8_t job, uint16_t propType);
    /**
    * @brief            ��ȡbuff������   buff.csv
    * @param buffID 
    * @param propType   buff_prop_type_min -buff_prop_type_max
    * @return           ����bool   
    *                   ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetBuffProp(uint16_t buffID, uint16_t propType);
    /**
    * @brief            ��������buff��  �������ǵ����ϵ�Ĳ���  buff_group.csv
    * @param g1 
    * @param g2 
    * @param propType   BUFF_GROUP_PROP_TYPE_MIN -BUFF_GROUP_PROP_TYPE_MAX
    * @return           ����bool   
    *                   ���� true ͨ��LuaRet ��ȡ����
    * 
    *  BUFF_GROUP_PROP_TYPE_MIN = 0,
        BUFF_GROUP_PROP_ID,
        BUFF_GROUP_GROUPID_1,
        BUFF_GROUP_GROUPID_2,
        BUFF_GROUP_GROUPRELATION,
        BUFF_GROUP_PROP_TYPE_MAX,
    */
    bool            GetBuffGroupProp(uint16_t g1, uint16_t g2, uint16_t propType);
    /**
    * @brief                ��ȡ���ܱ����� skill.csv
    * @param skillID 
    * @param propType       skill_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetSkillProp(uint16_t skillID, uint16_t propType);
    /**
    * @brief                ��ȡ���������  monster.csv
    * @param monsterID 
    * @param propType       monster_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetMonsterProp(uint16_t monsterID, uint16_t propType);
    /**
    * @brief                ��ȡnpc������ npc.csv
    * @param monsterID 
    * @param propType       npc_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetNpcProp(uint16_t npcID, uint16_t propType);
    /**
    * @brief                ��ȡMap������ map.csv
    * @param mapID 
    * @param propType       map_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetMapProp(uint16_t mapID, uint16_t propType);
    /**
    * @brief                ��ȡ��Ʒ������ item.csv
    * @param itemID 
    * @param propType       item_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetItemProp(uint16_t itemID, uint16_t propType);
    /**
    * @brief                ��ȡ��Ʒ������ item.csv
    * @param itemKeyName 
    * @param propType       item_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetItemPropByKeyName(const std::string& itemKeyName, uint16_t propType);
    /**
    * @brief                ��ȡgroup_att.csv������
    * @param groupID 
    * @param propType       GROUP_ATTR_PROP_TYPE_MIN
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    * 
    GROUP_ATTR_PROP_TYPE_MIN = 0,
    GROUP_ATTR_PROP_ID,
    GROUP_ATTR_PROP_DESC,
    GROUP_ATTR_PROP_GROUPINFO,
    GROUP_ATTR_PROP_TYPE_MAX,
    */
    bool            GetGroupAttrProp(uint16_t groupID, uint16_t propType);
    /**
    * @brief                ��ȡquest.csv������
    * @param questID 
    * @param propType       quest_prop_type_min
    * @return               ����bool   
    *                       ���� true ͨ��LuaRet ��ȡ����
    */
    bool            GetQuestProp(uint16_t questID, uint16_t propType);
    /**
    * @brief                �����Զ���Custvar����
    * @param belong         ��ɫid  �������� ��� ���� npc Pet ��Ʒ �л�
    * @param name           �Զ���Custvar��������
    * @param value          �Զ���Custvar������
    * @param type           0:���ñ��� 1:һ���ɾ��
    * @return               ����bool   
    */
    bool            SetCustVar(const std::string &belong, std::string name, std::string value, uint8_t type);
    /**
    * @brief                �����Զ���Custvar����
    * @param name           �Զ���Custvar��������
    * @param value          �Զ���Custvar������
    * @param type           0 ���ñ��� 1 һ���ɾ��
    * @param mergeType       
    * @return               ����bool   
    * cvmt_keep_main          = 0,        // ������������
    * cvmt_addup              = 1,        // ������ӣ��ַ���������������ֵ��������ӣ�
    * cvmt_choose_bigger      = 2,        // ȡ�������ݣ�������ֵ��������Ч��
    * cvmt_choose_smaller     = 3,        // ȡ��С�����ݣ�������ֵ��������Ч��
    * cvmt_delete             = 4         // �������
    */
    bool            SetCustVarEx(std::string name, std::string value, uint8_t type, uint8_t mergeType);
    /**
    * @brief                ��ȡCustVar����
    * @param belong         ��ɫid  
    * @param name           �Զ���Custvar��������
    * @return               value  
    */
    std::string     GetCustVar(const std::string &belong, const std::string &name);
    
    /**
    * @brief                ���ֶ�ȡlua�ű�
    * @param scriptType     ��ȡ����   ����script type def
    * @return               ��  
    */
    void            ReloadScript(uint32_t scriptType);
    /**
    * @brief                �Զ���װ��λ
    * @param luaObj 
    * @return               �Ƿ�ɹ�
    * luaObj �ο�
    * GlobalData.CustomSubToSize = {
    * {equip_custom_1,{site_equip_custom_1}}, --����
    * {equip_custom_8,{site_equip_custom_8}},
    * }  
    * LuaHost:RegisterCustomSiteAndSub(GlobalData.CustomSubToSize)
    */
    bool            RegisterCustomSiteAndSub(const CLuaObject& luaObj);

    /**
    * @brief            ��ȡ����������
    * @param key        ��ȡ����   ���� "AreaServerOpenTime"  "MergeAreaServerTime"  "MergeAreaServerCnt"
    * @return           ����   
    */
    std::string     GetConstantCfg(const std::string& key);
    void            SetConstantCfg(const std::string& key, const std::string& value);
    /**
    * @brief            ���ô�����ɫ�Ƿ���ҪУ����
    * @param beSet      �Ƿ���Ҫ0����Ҫ,1��Ҫ
    * @return           ��
    */
    void            SetCreateRoleNeedCode(uint8_t beSet);
    /**
    * @brief            
    * @param str 
    * @return              
    */
    std::string     GBK2UTF8(const std::string &str);
    /**
    * @brief            
    * @param str 
    * @return              
    */
    std::string     UTF82GBK(const std::string &str);
    /**
    * @brief            ɾ���ʼ�
    * @return           ��   
    */
    void            DeleteMallRemainedData();
    /**
    * @brief            ͨ��������ֻ�ȡ��Ҳ���ִ�лص�����
    * @param name 
    * @param callback   �ص� lua 
    * @return           ��   
    */
    void            CheckIfRoleExistByName(const std::string &name, const CLuaObject &callback);
    /**
    * @brief            ͨ��������ֻ�ȡ��Ҳ���ִ�лص�����
    * @param guid 
    * @param callback   �ص� lua 
    * @return           ��   
    */
    void            CheckIfRoleExistByGUID(const std::string &guid, const CLuaObject &callback);
    /**
    * @brief            ��ʱ����
    * @param name       ��������
    * @param type       1��ָ��ʱ��ִ��һ�� 2����  3���� 4���� 5����
    * @param scheduled  {"20:00:00"}||{string.format("%d-%02d-%02d %02d:%02d:%02d",closeTime.year,closeTime.month,closeTime.day,closeTime.hour,closeTime.min,closeTime.sec)}
    * @param callBack   �ص� lua ����
    * @param params     �ص� lua��������
    * @return           ��   
    */
    uint32_t        AddScheduled(/*uint32_t id, */const std::string& name, uint16_t type, const CLuaObject& scheduled, const std::string& callBack, const std::string& params);
    /**
    * @brief            ��ʱ����
    * @param Guid       "0"Ϊ������  ���������guid
    * @param interval   ����
    * @param loop       �Ƿ�ѭ��
    * @param callBack   �ص� lua ����
    * @return           id ����id   
    */
    uint32_t        AddLuaTimer(const std::string& Guid, uint32_t interval, bool loop, const std::string &callBack);
    /**
    * @brief            ��ʱ����
    * @param Guid       "0"Ϊ������  ���������guid
    * @param interval   ����
    * @param loop       �Ƿ�ѭ��
    * @param callBack   �ص� lua ����
    * @return           id ����id   
    */
    uint32_t        AddLuaTimerEx(const std::string& Guid, uint32_t interval, bool loop, CLuaObject callBack);

    /**
    * @brief            ɾ����ʱ����
    * @param Guid       "0"Ϊ������  ���������guid
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @return           ��   
    */
    void            RemoveLuaTimer(const std::string& Guid, uint32_t timerID);
    /**
    * @brief            ��ʱ�������
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @param key        ���Զ���
    * @param val        ����
    * @return           ��  
    */
    void            AddNumData(uint32_t timerID, const std::string& key, uint32_t val);
    /**
    * @brief            ��ȡ��ʱ�������
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @param key        ���Զ���
    * @return           ���� 
    */
    uint32_t        GetNumData(uint32_t timerID, const std::string& key);
    /**
    * @brief            ɾ����ʱ�������
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @param key        ���Զ���
    * @return           �� 
    */
    void            RemoveNumData(uint32_t timerID, const std::string& key);
    /**
    * @brief            ��ʱ���������Զ������
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @param key        ���Զ���
    * @param val        ����
    * @return           �� 
    */
    void            AddStrData(uint32_t timerID, const std::string& key, const std::string& val);
    /**
    * @brief            ��ȡ��ʱ���������Զ������
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @param key        ���Զ���
    * @return           val ����
    */
    std::string     GetStrData(uint32_t timerID, const std::string& key);
    /**
    * @brief            ɾ����ʱ���������Զ������
    * @param timerID    ΪAddLuaTimer|| AddLuaTimerEx ����ֵ
    * @param key        ���Զ���
    * @return           ��
    */
    void            RemoveStrData(uint32_t timerID, const std::string& key);
    /**
    * @brief            ͨ��������ַ����ʼ�
    * @param Rolename   �������
    * @param title      �ʼ�����
    * @param text       �ʼ�����
    * @param additions  �ο� {{itemKey,1,0}}
    * @param currency   �ο� 1000
    * @param type       �������� role_attr_ext
    * @return �Ƿ�ɹ�
    */
    int             AddMailByName(const std::string& Rolename, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type);
    /**
    * @brief            ͨ��Guid�����ʼ�
    * @param Guid       ��ɫGuid
    * @param title      �ʼ�����
    * @param text       �ʼ�����
    * @param additions  �ο� {{itemKey,1,0}}
    * @param currency   �ο� 1000
    * @param type       �������� role_attr_ext
    * @return �Ƿ�ɹ�
    */
    int             AddMailByGuid(const std::string& Guid, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type);
    /**
    * @brief                �Ӽ���
    * @param objGUID        ��ɫGuid
    * @param eventID        Trigger_null
    * @param callBack       �ص�����
    * @return ��
    */
    void            AddTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack);
    /**
    * @brief                ɾ������
    * @param objGUID        ��ɫGuid
    * @param eventID        Trigger_null
    * @param callBack       �ص�����
    * @return ��
    */
    void            RemoveTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack);
    /**
    * @brief                ��ȡ�����������
    * @return               local all_list = LuaHost:GetAllOnlinePlayerGuid() for k , v in pairs(all_list) do
    */
    CLuaObject      GetAllOnlinePlayerGuid();
    /**
    * @brief                �����������ִ��
    * @param scriptName     lua����
    * @param params         ����
    * @return ��
    */
    void            RunLuaScriptEveryOnlinePlayer(const std::string& scriptName,const std::string& params);

    /**
    * @brief                c++����int64_t
    * @param lhs            lhs
    * @param rhs            rhs
    * @param type           ����
    * @return               ������
    * 
    * type��
    * simple_Arithmetic_add      = 1,
    * simple_Arithmetic_subtract = 2,
    * simple_Arithmetic_multiply = 3,
    * simple_Arithmetic_divide   = 4,
    */
    std::string     SimpleArithmetic(const std::string& lhs, const std::string& rhs, int type);

    /**
    * @brief                �����������еĺ���
    * @param allowFuncs     lua����
    * @return ��
    */
    void            SetFormAllowFunc(const CLuaObject &allowFuncs);

    /**
    * @brief                �ж��Ƿ���������
    * @param allowFuncs     lua����
    * @return               bool
    */
    bool            IsRunServScriptAllowedFunc(const std::string &func);
    /**
    * @brief                �������Ա仯ʱ�Ƿ�ص�
    * @param allowFuncs     table
    * @return ��
    * local attrList = {
    *        role_base_max_hp,
    *        role_base_max_mp,}
    * SetCallBackUpdateAttr32(attrList)
    */
    void            SetCallBackUpdateAttr32(const CLuaObject& allowFuncs);
    /**
    * @brief                ����64λ���Ա仯ʱ�Ƿ�ص�
    * @param allowFuncs     table
    * @return ��
    */
    void            SetCallBackUpdateAttr64(const CLuaObject& allowFuncs);
    /**
    * @brief                �ж��Ƿ������Իص�
    * @param attrType       role_base_max_hp
    * @param beAttr32       �Ƿ�32λ����
    * @return ��
    */
    bool            IsCallBackUpdateAttr(int32_t attrType, bool beAttr32 = true);
    //msg
    /**
    * @brief                ������������
    * @param params         ����
    * @return ��
    */
    void            SendChatMsg(const CLuaObject& params);
    /**
    * @brief                δʵ��
    */
    void            SendChatMsgTime(const std::string& startTime,const std::string& interval,uint16_t times,const CLuaObject& params) {};

    /**
    * @brief                ��ȡ���а���Ϣ
    * @return               �������а���Ϣ
    * {{guid,value,desc,idx}��{guid,value,desc,idx}��{guid,value,desc,idx}...}
    */
    CLuaObject      GetCustListInfoByType(int type);


    /// Auction
    /**
    * @brief                ����������Ϣ
    * @param info          ����
    * @return ��
    */
    void            Auction_AddItemInfo(const CLuaObject& info);
     /**
    * @brief                ��������Ʒ�۸����ı�
    * @param guid          ��ɫ
    * @param orderID       ����
    * @param price         �۸�
    * @return              �Ƿ�ɹ�
    */
    bool            Auction_OfferPrice(const std::string& guid, const std::string& orderID, int price);
    /**
    * @brief               ����Ѿ�������������Ʒ����
    * @param func          �ص�����
    * @param few_time_ago  
    * @return              �Ƿ�ɹ�
    */
    void            Auction_GetFinishedItemTable(const std::string& func, uint32_t few_time_ago);

public:     // MapMgr export functions
    /**
    * @brief               ������ͼ
    * @param keyName       ��ͼ����
    * @return              ��ͼguid
    */
    std::string     MapMgr_CreateMap(const std::string &keyName);
     /**
    * @brief               ɾ����ͼ
    * @param mapName       ��ͼ����
    * @return              ��
    */
    void            MapMgr_DestroyMap(const std::string& mapName);
     /**
    * @brief               Ѱ�ҵ�ͼ
    * @param mapName       ��ͼ����
    * @return              ��ͼguid
    */
    std::string     MapMgr_FindMap(const std::string& mapName);
    /**
    * @brief                ���������ͼ
    * @param sDgnMapName    ��ͼ����
    * @param sPlayerGuid    ���GUID
    * @param delayInit      �Ƿ��ӳٳ�ʼ��
    * @param exitTime       ����ʱ��
    * @param call_back      �ص�
    * @return               ��ͼguid
    */
    std::string     MapMgr_CreateMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, bool delayInit, uint32_t exitTime, CLuaObject call_back);
    /**
    * @brief                ���پ����ͼ
    * @param sDgnMapGuid    ��ͼguid
    * @return               û�ҵ�����1000
    */
    uint32_t	    MapMgr_DestroyMulDgnMap(const std::string& sDgnMapGuid);
     /**
    * @brief                �󶨾����ͼ�����
    * @param sDgnMapGuid    ��ͼguid
    * @param sPlayerGuid    ��ɫguid
    * @return               û�ҵ�����1000
    */
    uint32_t	    MapMgr_BindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapGuid, const std::string& sPlayerGuid);
    /**
    * @brief                ����󶨾����ͼ�����
    * @param sDgnMapGuid    ��ͼguid
    * @param sPlayerGuid    ��ɫguid
    * @return               û�ҵ�����1000
    */
    uint32_t	    MapMgr_UnBindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid);
    /**
    * @brief                ��ҽ��뾵���ͼ
    * @param sDgnMapName    ��ͼ����
    * @param sPlayerGuid    ��ɫguid
    * @param posX    
    * @param posY    
    * @param edlogInfo      ��־
    * @return               û�ҵ�����1000
    */
    uint32_t	    MapMgr_EnteryMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, uint16_t posX, uint16_t posY, const CLuaObject& edlogInfo);
    /**
    * @brief                ����˳������ͼ
    * @param sDgnMapName    ��ͼ����
    * @param sPlayerGuid    ��ɫguid
    * @return               û�ҵ�����1000
    */
    uint32_t	    MapMgr_ExitMulDgnMap(const std::string& sDgnMapGuid, const std::string& sPlayerGuid);
    /**
    * @brief                ͨ������Ҿ����ͼ
    * @param sDgnMapName    ��ͼ����
    * @param sPlayerGuid    ��ɫguid
    * @return               û�ҵ�����1000
    */
    std::string	    MapMgr_GetMulDgnGuidByPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid);
public:     // Map export functions
    /**
    * @brief                �����ͼ
    * @param mapGuid        ��ͼguid
    * @param roleGuid       ��ɫguid
    * @return               
    */
    void            Map_RoleEnter(const std::string& mapGuid,const std::string& roleGuid);
    /**
    * @brief                �뿪��ͼ
    * @param mapGuid        ��ͼguid
    * @param roleGuid       ��ɫguid
    * @return               
    */
    void            Map_RoleLeave(const std::string& mapGuid,const std::string& roleGuid);
    /**
    * @brief                ���õ�ͼ���С
    * @param mapGuid        ��ͼguid
    * @param regionWidth    Ĭ��10
    * @param regionHeight   Ĭ��10
    * @return               
    */
    void            Map_SetRegionSize(const std::string& mapGuid, uint16_t regionWidth, uint16_t regionHeight);
    /**
    * @brief                �ٻ�����
    * @param mapGuid        ��ͼguid
    * @return               
    */
    void            Map_GenMapMonster(const std::string& mapGuid);
    /**
    * @brief                �ڷ�Χ���ٻ����� 
    * @param mapGuid        ��ͼguid
    * @param Name           ��������
    * @param left        
    * @param top        
    * @param width        
    * @param height        
    * @param num            ����
    * @param dir            ����
    * @return               
    */
    void            Map_GenMapMonsterByName(const std::string& mapGuid, const std::string& Name, uint16_t left, uint16_t top,
                        uint16_t width, uint16_t height, uint16_t num, uint8_t dir);
    /**
    * @brief                �ڷ�Χ���ٻ����� 
    * @param id             ����id
    * @return               
    */                
    void            Map_GenMapMonsterByID(const std::string& mapGuid, uint16_t id, uint16_t left, uint16_t top,
                        uint16_t width, uint16_t height, uint16_t num, uint8_t dir);
    /**
    * @brief                �ڵ�ͼ���ٻ�npc 
    * @param mapGuid        ��ͼguid
    * @param npcKeyName     npc����
    * @param x             
    * @param y             
    * @param dir             
    * @return               
    */      
    std::string     Map_GenMapNPCByKeyName(const std::string& mapGuid, const std::string& npcKeyName, uint16_t x, uint16_t y, uint8_t dir);
     /**
    * @brief                ɾ��npc 
    * @param npcGuid        npcguid           
    * @return               
    */      
    void            Map_DelMapNPCByGuid(const std::string& npcGuid);

    /**
    * @brief ������Ϣ���õ�ͼ
    * @param mapGuid ��ͼ��guid
    * @param nMsgType ��Ϣ����
    * @param sMsg ��Ϣ��Ϣ
    * @return ��
    */
    void            Map_SendSysMsg(const std::string& mapGuid, uint8_t nMsgType, const std::string& sMsg);

    /**
     * @brief ͨ����Ʒid���ɵ�ͼ������Ʒ
     * @param mapGuid ��ͼ��guid
     * @param ownerGuid ӵ����guid   0:����ϵͳ  1:����ϵͳ������Ҫ�ȴ�������Ʒ����ʱ�� guid:��ҵ�guid
     * @param x ��������Ʒx����
     * @param y ��������Ʒy����
     * @param id ������Ʒ��id
     * @param amount �ѵ�����
     * @param bind ������          0:����    1:��
     * @return �����ɳ�����Ʒ��guid
    */
    std::string     Map_GenSceneItem(const std::string& mapGuid, const std::string& ownerGuid, uint16_t x, uint16_t y, uint16_t id, uint16_t amount, uint16_t bind);

    /**
     * @brief ͨ����ƷKeyName���ɵ�ͼ������Ʒ
     * @param mapGuid ��ͼ��guid
     * @param ownerGuid ӵ����guid   0:����ϵͳ  1:����ϵͳ������Ҫ�ȴ�������Ʒ����ʱ�� guid:��ҵ�guid
     * @param x ��������Ʒx����
     * @param y ��������Ʒy����
     * @param name ������Ʒ��KeyName
     * @param amount �ѵ�����
     * @param bind ������          0:����    1:��
     * @return �����ɳ�����Ʒ��guid
    */
    std::string     Map_GenSceneItemByName(const std::string& mapGuid, const std::string& ownerGuid, uint16_t x, uint16_t y, const std::string& name, uint16_t amount, uint16_t bind);

    /**
     * @brief ͨ����ͼguid��ȡ��ͼ����
     * @param mapGuid ��ͼ��guid
     * @return ��ͼ����
    */
    std::string     Map_GetMapName(const std::string& mapGuid);

    /**
     * @brief ��ȡ��ͼ�ڸ�����Ľ�ɫ
     * @param mapGuid ��ͼ��guid
     * @param posX x����
     * @param posY y����
     * @return ��ɫ��guid
    */
    std::string     Map_GetRoleInPoint(const std::string& mapGuid, uint16_t posX, uint16_t posY);       //ԭRole*

    /**
     * @brief �����Ƿ��ڰ�ȫ����
     * @param mapGuid ��ͼ��guid
     * @param posx x����
     * @param posy y����
     * @return �Ƿ��ڰ�ȫ����
    */
    bool            Map_IsSafeRegion(const std::string& mapGuid, uint16_t  posx, uint16_t posy);

    /**
     * @brief ���߼����Ƿ��ǿ����õ�(�Ƿ����赲�㣬�����������)
     * @param mapGuid ��ͼ��guid
     * @param x x����
     * @param y y����
     * @return �������Ƿ������
    */
    bool            Map_IsGridAvail(const std::string& mapGuid, uint16_t x, uint16_t y);

    /**
     * @brief ��ȡ��ͼ�ڹ�������
     * @param mapGuid ��ͼ��guid
     * @return ��������
    */
    int             Map_GetMonsterNum(const std::string& mapGuid);

    /**
     * @brief ��ȡ��ͼid
     * @param mapGuid ��ͼ��guid
     * @return ��ͼid
    */
    int             Map_GetID(const std::string& mapGuid);

    /**
     * @brief �Ƿ��Ǹ����͵�����
     * @param mapGuid ��ͼ��guid
     * @param posX ����x
     * @param posY ����y
     * @param type ��������  0:��ȫ����  1:��̯����  2:��������(δʵ��)  3:��������  4:��������  5:��������  6:��ת����(δʵ��)  7:����(δʵ��)  8:�ɴ�͸����(δʵ��)
     * @return ��ͼid
    */
    bool            Map_IsThisMapGridType(const std::string& mapGuid, uint16_t posX, uint16_t posY, int type);

    /**
     * @brief �����ת��
     * @param from_guid ��ʼ��ת��ͼguid
     * @param to_guid ��ת����ͼguid
     * @param from_x ��ʼ��ת��ͼx����
     * @param from_y ��ʼ��ת��ͼy����
     * @param to_x ��ת����ͼx����
     * @param to_y ��ת����ͼy����
     * @param effect ��ת����Ч
     * @return ��
    */
    void            Map_AddJumpPoint(const std::string& from_guid, const std::string& to_guid, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint32_t enterEffect, uint32_t leaveEffect);

    /**
     * @brief ɾ����ת��
     * @param guid ��ʼ��ת��ͼguid
     * @param x ��ʼ��ת��ͼx����
     * @param y ��ʼ��ת��ͼy����
     * @return ��
    */
    void            Map_DelJumpPoint(const std::string& guid, uint16_t x, uint16_t y);

    /**
     * @brief ��ȡ��ͼ�����и����͵Ľ�ɫ
     * @param mapGUID ��ͼguid
     * @param roleType ��ɫ����   0:���н�ɫ  1:���  2:npc  3:����  4:����  5:��Ұ�̯ģ��  6:��ҷ���
     * @return �����͵�lua��  {guid1,guid2,guid3...}
    */
    CLuaObject      Map_GetAllRoleByType(const std::string &mapGUID, uint8_t roleType);

    /**
     * @brief ��ȡ��ͼ���������пո���
     * @param mapguid ��ͼguid
     * @param x ���ĵ�����x
     * @param y ���ĵ�����y
     * @param rangeX ���ĵ㵽һ��x�ĳ���
     * @param rangeY ���ĵ㵽һ��y�ĳ���
     * @return ��
     * @LuaRet {{x1,y1},{x2,y2},{x3,y3}...}
    */
    void            Map_GetAllEmptyGrid(const std::string& mapguid, uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY); 

    /**
     * @brief ��ȡ��ͼ���������пհ׸�
     * @param mapguid ��ͼguid
     * @param x ���ĵ�����x
     * @param y ���ĵ�����y
     * @param rangeX ���ĵ㵽һ��x�ĳ���
     * @param rangeY ���ĵ㵽һ��y�ĳ���
     * @return ��
     * @LuaRet {{x1,y1},{x2,y2},{x3,y3}...}
    */
    void            Map_GetAllCanDropItemGrid(const std::string& mapguid, uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY);

    /**
     * @brief ɾ��������Ĺ���ʬ��
     * @param mapguid ��ͼguid
     * @param x ����x
     * @param y ����y
     * @return ��
    */
    void            Map_DisappearMonsterCorpseInPoint(const std::string& mapguid,uint16_t x,uint16_t y);

    /**
     * @brief ��ȡ��ͼ�ڵ�BOSS��Ϣ
     * @param MapKey ��ͼ��
     * @return �ɹ�����ʧ��
     * @LuaRet {{��ͼ��,������,����ʱ��(0:������� time:����ĸ���ʱ�� s)},{��ͼ��,������,����ʱ��}...}
    */
    bool            Map_GetBossInfo(const std::string&MapKey);

    /**
     * @brief ���Ǿ����������
     * @param num ����
     * @return ��
    */
    void            SetMaxImageCount(uint32_t num);
    //MapAoi& Map_GetMapAoi(std::string mapGuid);

public:             // RoleMgr export functions
    /**
     * @brief ��ȡ���guid
     * @param name �������
     * @return ���guid
    */
    std::string     RoleMgr_GetPlayerGUID(const std::string &name);

    /**
     * @brief ��ȡ��ɫ�Ƿ����
     * @param guid ���guid
     * @return �Ƿ����
    */
    bool            RoleMgr_IsRoleExist(const std::string &guid);

public:             // Role export functions
    /**
     * @brief ��ȡ��ɫ����
     * @param guid ��ɫguid
     * @return ��ɫ����  0:��Ч�Ľ�ɫ����  1:���  2:npc  3:����  4:����  5:��Ұ�̯ģ��  6:��ҷ���
    */
    uint32_t        Role_GetType(const std::string &guid);

    /**
     * @brief ��ȡ��ɫ����
     * @param guid ��ɫguid
     * @return ��ɫ����
    */
    std::string     Role_GetName(const std::string &guid);

    /**
     * @brief ���ý�ɫ����(��֧����Ҹ�����)
     * @param guid ��ɫguid
     * @param name ��ɫ����
     * @return ��
    */
    void            Role_SetName(const std::string& guid, const string& name);

    /**
     * @brief ���ý�ɫ����
     * @param guid ��ɫguid
     * @param name ��ɫ����
     * @return ��
    */
    void            Role_SetAlias(const std::string& guid, const string& name);

    /**
     * @brief ��ȡ��ҵ�ǰ��ͼguid
     * @param guid ��ɫguid
     * @return ��ǰ��ͼ��guid
    */
    std::string     Role_GetCurMapGUID(const std::string &guid);

    /**
     * @brief ��ȡ��ɫ����
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @return ��ɫ��ǰ����ֵ
    */
    int32_t         Role_GetProp(const std::string &guid, int prop);

    /**
     * @brief ��ӽ�ɫ����
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @param value ����valueֵ
     * @return ��
    */
    void            Role_AddProp(const std::string& guid, int32_t prop, int32_t value);

    /**
     * @brief ���ý�ɫ����
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @param value ����valueֵ
     * @return ��
    */
    void            Role_SetProp(const std::string &guid, int prop, int32_t value);

    /**
     * @brief ��ȡ��ɫ64λ����
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @return ����valueֵ
    */
    std::string     Role_GetProp64(const std::string &guid, int prop);

    /**
     * @brief ���ӽ�ɫ64λ����ֵ
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @param delta �����޸ĺ��ֵ
     * @param logInfo ��־��ӡֵ
     * @return ��
    */
    void            Role_ModProp64(const std::string &guid, int prop, double delta, const CLuaObject& logInfo);

    /**
     * @brief ͨ���ַ������ӽ�ɫ64λ����ֵ
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @param delta �����޸ĺ��ֵ
     * @param logInfo ��־��ӡֵ
     * @return ��
    */
    void            Role_ModProp64ByStr(const std::string& guid, int prop, std::string delta, const CLuaObject& logInfo);

    /**
     * @brief ����ɫ64λ�����Ƿ���ڵ��ڴ�������
     * @param guid ��ɫguid
     * @param prop ����keyֵ
     * @param needNum �����޸ĺ��ֵ
     * @return �Ƿ���ڵ���
    */
    bool            Role_CheckProp64Amount(const std::string &guid, int prop, const std::string &needNum);

    /**
     * @brief ��ȡ��ɫx����
     * @param guid ��ɫguid
     * @return ��ɫx����
    */
    uint16_t        Role_GetPosX(const std::string &guid);

    /**
     * @brief ��ȡ��ɫy����
     * @param guid ��ɫguid
     * @return ��ɫy����
    */
    uint16_t        Role_GetPosY(const std::string &guid);

    /**
     * @brief ���ý�ɫ����
     * @param guid ��ɫguid
     * @param x x����
     * @param y y����
     * @return ��
    */
    void            Role_SetPos(const std::string &guid, uint16_t x, uint16_t y);

    /**
     * @brief ��ȡ��ɫ����
     * @param guid ��ɫguid
     * @return ��ɫ��ǰ����
    */
    uint8_t         Role_GetDir(const std::string &guid);

    /**
     * @brief ���ý�ɫ����
     * @param guid ��ɫguid
     * @param dir ��ɫ����
     * @return ��
    */
    void            Role_SetDir(const std::string &guid, uint8_t dir);

    /**
     * @brief ��ɫ���buff
     * @param guid ��ɫguid
     * @param buffID buffID
     * @param skillID ����ID
     * @return �Ƿ���ӳɹ�
    */
    bool            Role_AddBuff(const std::string &guid, uint16_t buffID, uint16_t skillID);

    /**
     * @brief ��ɫ��ʩ��buffͨ���ͷ���
     * @param guid ��ɫguid
     * @param buffID buffID
     * @param actorGUID �ͷ���GUID
     * @param skillID ����ID
     * @param attrStr buff�������� (����;��������;��ֱ�ϵ��|;;|;;)
     * @param time ʣ��ʱ�� ms
     * @return �Ƿ���ӳɹ�
    */
    bool            Role_AddBuffByRole(const std::string &guid, uint16_t buffID, const std::string &actorGUID, uint16_t skillID, const std::string& attrStr, uint32_t time = 0);

    /**
     * @brief ɾ����ɫbuff
     * @param guid ��ɫguid
     * @param buffID buffID
     * @return �Ƿ�ɾ���ɹ�
    */
    bool            Role_RemoveBuff(const std::string &guid, uint16_t buffID);

    /**
     * @brief ͨ���ͷ���GUIDɾ����ɫbuff
     * @param guid ��ɫguid
     * @param buffID buffID
     * @param actorID �ͷ���guid
     * @return �Ƿ�ɾ���ɹ�
    */
    bool            Role_RemoveBuffWithActorID(const std::string &guid, uint16_t buffID, const std::string &actorID);

    /**
     * @brief buff�Ƿ����
     * @param guid ��ɫguid
     * @param buffID buffID
     * @return �Ƿ����
    */
    bool            Role_BuffExist(const std::string &guid, uint16_t buffID);

    /**
     * @brief ͨ��buff��ID�ж�buff�Ƿ����
     * @param guid ��ɫguid
     * @param buffID buffID
     * @param buffGroupID buff��ID
     * @return �Ƿ����
    */
    bool            Role_BuffExistByGroupID(const std::string& guid, uint16_t buffGroupID);

    /**
     * @brief ͨ��buff���ж�buff�Ƿ����
     * @param guid ��ɫguid
     * @param name buff����
     * @return �Ƿ����
    */
    bool            Role_BuffExistByKeyName(const std::string& guid, const std::string&);

    /**
     * @brief ��ȡbuff�ѵ�����
     * @param guid ��ɫguid
     * @param buffID buffid
     * @return �ѵ�����
    */
    uint16_t        Role_GetBuffStack(const std::string& guid, uint16_t buffID);

    /**
     * @brief ��ȡbuffʣ��ʱ��
     * @param guid ��ɫguid
     * @param buffID buffid
     * @return ʣ��ʱ�� -1:buff������ 0:���� >0:ʣ��ʱ�� ms
    */
    std::string     Role_GetBuffLeftTime(const std::string& guid, uint16_t buffID);

    /**
     * @brief ��ȡbuff�б�
     * @param guid ��ɫguid
     * @return buff�б� {id1, id2, id3...}
    */
    CLuaObject      Role_GetBuffList(const std::string &guid);

    /**
     * @brief ׷��buff�ѵ�����
     * @param guid ��ɫguid
     * @param buffID buffID
     * @param diff ׷�Ӷѵ�����
     * @return ��
    */
    void            Role_UpdateBuffStack(const std::string& guid, uint16_t buffID, int16_t diff);

    /**
     * @brief ͨ����������Ӽ��ܹ���
     * @param guid ��ɫguid
     * @param actorGUID ������guid
     * @param skillID ����ID
     * @param lossHP ��ʧѪ��
     * @param harmType �˺�����
     * @return ��
    */
    void            Role_AttackedByRole(const std::string &guid, const std::string &actorGUID, uint16_t skillID, uint32_t lossHP, uint8_t harmType);

    /**
     * @brief ͨ����������Ӽ��ܹ���
     * @param guid ��ɫguid
     * @param actorGUID ������guid
     * @param actorName ����������
     * @param skillID ����ID
     * @param lossHP ��ʧѪ��
     * @param harmType �˺�����
     * @return ��
    */
    void            Role_AttackedByRole2(const std::string &guid, const std::string &actorGUID, const std::string &actorName,
                        uint16_t skillID, uint32_t lossHP, uint8_t harmType);

    /**
     * @brief ��ɫ�Ƿ���
     * @param guid ��ɫguid
     * @return �Ƿ���
    */
    bool            Role_IsAlive(const std::string &guid);

    /**
     * @brief ��ȡbuff�ͷ���guid
     * @param guid ��ɫguid
     * @param buffID buffid
     * @return �ͷ���guid
    */
    std::string     Role_GetBuffActorGuid(const std::string &guid, uint16_t buffID);

    /**
     * @brief ��ȡbuff�ͷ�������
     * @param guid ��ɫguid
     * @param actorGuid �ͷ���guid
     * @param buffID buffID
     * @return �ͷ�������
    */
    std::string     Role_GetBuffActorName(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief ��ȡbuff�ͷ���ְҵ
     * @param guid ��ɫguid
     * @param actorGuid �ͷ���guid
     * @param buffID buffID
     * @return �ͷ���ְҵ
    */
    uint8_t         Role_GetBuffActorJob(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief ��ȡbuff�ͷ��ߵȼ�
     * @param guid ��ɫguid
     * @param actorGuid �ͷ���guid
     * @param buffID buffID
     * @return �ͷ��ߵȼ�
    */
    uint32_t        Role_GetBuffActorLevel(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief ��ȡbuff�ͷ��߼���ID
     * @param guid ��ɫguid
     * @param actorGuid �ͷ���guid
     * @param buffID buffID
     * @return �ͷ��߼���ID
    */
    uint16_t        Role_GetBuffActorSkill(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief ���ӽ�ɫѪ��
     * @param guid ��ɫguid
     * @param amount ��������
     * @param type ���� 0:�չ�  1:����
     * @param notify �Ƿ�֪ͨ�ͻ���
     * @return ��
    */
    void            Role_IncreaseHP(const std::string &guid, int32_t amount, uint8_t type, bool notify);

    /**
     * @brief ���ٽ�ɫѪ��
     * @param guid ��ɫguid
     * @param amount ��������
     * @param type ���� 0:�չ�  1:����
     * @param notify �Ƿ�֪ͨ�ͻ���
     * @return ��
    */
    void            Role_DecreaseHP(const std::string &guid, int32_t amount, uint8_t type, bool notify);

    /**
     * @brief �ı��ɫ���
     * @param guid ��ɫguid
     * @param modelID ���ID
     * @return ��
    */
    void            Role_ChangeAppearance(const std::string& guid, uint16_t modelID);

    /**
     * @brief ���ý�ɫ��������
     * @param guid ��ɫguid
     * @param skillID ����ID
     * @param propType ������������ ���SKILL_PROP_TYPE
     * @param cfg ������������ ���������������
     * @return ��
    */
    void            Role_SetSkillProp(const std::string& guid, uint16_t skillID, uint16_t propType, const std::string& cfg);

    /**
     * @brief ��ȡ��ɫ��������
     * @param guid ��ɫguid
     * @param skillID ����ID
     * @param propType ������������ ���SKILL_PROP_TYPE
     * @return ��������������Ϣ
    */
    bool            Role_GetSkillProp(const std::string& guid, uint16_t skillID, uint16_t propType);

    /**
     * @brief ��ɫ��ת��ͼ
     * @param guid ��ɫguid
     * @param mapGuid ��ͼguid
     * @param x ����x
     * @param y ����y
     * @return �Ƿ���ת�ɹ�
    */
    bool            Role_JumpMapByGuid(const std::string& guid, const std::string& mapGuid, uint16_t x, uint16_t y);

    /**
     * @brief ��ɫ���������ת��ͼ
     * @param guid ��ɫguid
     * @param mapGuid ��ͼguid
     * @return �Ƿ���ת�ɹ�
    */
    bool            Role_RandJumpMapByGuid(const std::string& guid, const std::string& mapGuid);

    /**
     * @brief ��ɫ�ͷż���
     * @param guid ��ɫguid
     * @param skillID ����ID
     * @param x ����x
     * @param y ����y
     * @param targetGUID Ŀ��guid
     * @return �Ƿ��ͷųɹ�
    */
    bool            Role_ApplySkill(const std::string &guid, uint16_t skillID, uint16_t x, uint16_t y,
                                    const std::string &targetGUID);

    /**
     * @brief ��ɫ��ȡ����guid
     * @param guid ��ɫguid
     * @return ����guid
    */
    std::string     Role_GetMasterGUIDAsString(const std::string &guid);

    /**
     * @brief �����������
     * @param guid ��ɫguid
     * @param value ���id
     * @return ��
    */
    void Role_SetRideHorseModelid(const std::string& guid, int32_t value);

    /**
     * @brief ����������
     * @param guid ��ɫguid
     * @param value ���id
     * @return ��
    */
    void Role_SetRideHorseSwitch(const std::string& guid, bool value);

    /**
     * @brief ��ȡ�������
     * @param guid ��ɫguid
     * @return ���id
    */
    int32_t Role_GetRideHorseModelid(const std::string& guid);

    /**
     * @brief ��ȡ������
     * @param guid ��ɫguid
     * @return ����״̬
    */
    bool Role_GetRideHorseSwitch(const std::string& guid);
public:     // Player export functions
    /**
     * @brief ��ȡ��ɫ�Ƿ�֧���˺�
     * @param guid ��ɫguid
     * @return �Ƿ�֧���˺�
    */
    bool            Player_IsSupport(const std::string& guid);
    /**
     * @brief ���ͻ��˷�����Ʒ����Э�� (��Ч�ӿ�)
     * @param guid ��ɫguid
     * @return ��
    */
    void            Player_SendItemDestroyAck(const std::string& guid);

    /**
     * @brief ���ͻ��˷��͸������
     * @param guid ��ɫguid
     * @param MapName �����ͼ
     * @param hp Ѫ��
     * @param mp ����
     * @param x x����
     * @param y y����
     * @return ��
    */
    void            Player_SendPlayerReliveNtf(const std::string& guid, const std::string& MapName, int hp, int mp, int x, int y);

    /**
     * @brief ��������ҷ���Ѫ������������Ϣ(������Ѫ������)
     * @param guid ��ɫguid
     * @param hp Ѫ��
     * @param mp ����
     * @return ��
    */
    void            Player_SendPlayerShowNtf(const std::string& guid, int hp, int mp);

    /**
     * @brief ��������ҷ���AttrExtRef����(�����ô�����)
     * @param guid ��ɫguid
     * @param attr ����
     * @param delta value
     * @return ��
    */
    void            Player_SendRoleAttrExtRefNtf(const std::string &guid, uint16_t attr, int delta);

    /**
     * @brief �����Ʒ����ұ���
     * @param guid ��ɫguid
     * @param tempid ��Ʒģ��id
     * @param logInfo ��־��Ϣ
     * @return �Ƿ���ӳɹ�
    */
    bool            Player_AddPlayerItem(const std::string& guid, uint16_t tempid, const CLuaObject& logInfo);

    /**
     * @brief �����Ҿ���
     * @param guid ��ɫguid
     * @param exp ����ֵ
     * @param logInfo ��־��Ϣ
     * @return ��
    */
    void            Player_AddPlayerExperience(const std::string& guid, int64_t exp, const CLuaObject& logInfo);

    /**
     * @brief ������keyΪ4��64λ����ֵ(��ǰ����˶���Ϊ�ǰ���)
     * @param guid ��ɫguid
     * @param goldid ����ֵ
     * @param logInfo ��־��Ϣ
     * @return ��
    */
    void            Player_AddPlayerGold(const std::string& guid, uint64_t goldid, const CLuaObject& logInfo);

    /**
     * @brief ִ�пͻ��˽ű���
     * @param guid ��ɫguid
     * @param sScriptName �ű�������
     * @param sContent ִ�еı�����
     * @param bCompress �������Ƿ�ѹ��
     * @return ��
    */
    void            Player_RunClientScript(const std::string& guid, const std::string& sScriptName, const std::string& sContent, bool bCompress);
    /**
     * @brief ֪ͨ��ҳɹ��ƶ�������ֵ
     * @param guid ��ɫguid
     * @param nDstX Ŀ��x����
     * @param nDstY Ŀ��y����
     * @return ��
    */
    void            Player_NotifyPlayer_StartMove(const std::string& guid, uint16_t nDstX, uint16_t nDstY);

    /**
     * @brief ����ҷ��ͱ�����Ϣ
     * @param guid ��ɫguid
     * @param type ��������
     * @param errMsg �����ӡ
     * @return ��
    */
    void            Player_SendErrorAck(const std::string& guid, int32_t type, const char* errMsg);

    /**
     * @brief ����ҷ��ͶԻ�����Ϣ
     * @param guid ��ɫguid
     * @param msg ��Ϣ
     * @return ��
    */
    void            Player_SendPopDlgMsgNtf(const std::string &guid, const std::string &msg);
    void            Player_SendPlayerFamilyChangeNtf(const std::string &guid, const std::string &msg);

    /**
    * @brief ��ת��ָ����ͼ�������
    * @param guid ��ɫGUID
    * @param mapName ��ͼ������
    * @return ��
    */
    void            Player_Jump(const std::string& guid, const std::string& mapName);

    /**
    * @brief ��ת��ָ����ͼ���ض���
    * @param guid ��ɫGUID
    * @param mapName ��ͼ��������Ϊ�ձ�ʾ��ǰ��ͼ
    * @param posX �߼�������x
    * @param posY �߼�������y
    * @return ��ת�Ƿ�ɹ�
    */
    bool            Player_JumpMap(const std::string& guid, const std::string& mapName, uint16_t posX, uint16_t posY);

    /**
    * @brief ��ת��ָ����ͼ�������
    * @param guid ��ɫGUID
    * @param mapName ��ͼ������
    * @param type ��ת����
    * @return ��
    */
    void            Player_JumpWithType(const std::string& guid, const std::string& mapName, uint16_t type);

    /**
    * @brief ��ת��ָ����ͼ���ض���
    * @param guid ��ɫGUID
    * @param mapName ��ͼ������
    * @param posX �߼�������x
    * @param posY �߼�������y
    * @param type ��ת����
    * @return ��ת�Ƿ�ɹ�
    */
    bool            Player_JumpMapWithType(const std::string& guid, const std::string& mapName, uint16_t posX, uint16_t posY, uint16_t type);

    /**
    * @brief ͨ������ģ��ID�ٻ�����
    * @param guid ��ɫGUID
    * @param monsterID ����ģ��ID
    * @return ����GUID
    */
    std::string     Player_SummonMonsterByID(const std::string& guid, uint16_t monsterID);

    /**
    * @brief ͨ�������������ٻ�����
    * @param guid ��ɫGUID
    * @param monsterName ����������
    * @return ����GUID
    */
    std::string     Player_SummonMonsterByName(const std::string& guid, const std::string& monsterName);

    /**
    * @brief �����ٻ�����������
    * @param guid ��ɫGUID
    * @param sMonsterGUID ����GUID
    * @return ��
    */
    void            Player_DestroySummonMonster(const std::string& guid, const std::string& sMonsterGUID);

    /**
    * @brief ��������ģ��ID��ȡ���޵�GUID
    * @param guid ��ɫGUID
    * @param nTemplateID ����ģ��ID
    * @return ����GUID���
    */
    std::string     Player_GetSummonMonster(const std::string& guid, uint16_t nTemplateID);

    /**
    * @brief ͨ������ģ��ID�ٻ�����
    * @param guid ��ɫGUID
    * @param monsterid ����ģ��ID
    * @return ����GUID
    */
    std::string     Player_PetMonsterByID(const std::string&guid,uint16_t monsterid);

    /**
    * @brief ͨ�������������ٻ�����
    * @param guid ��ɫGUID
    * @param monsterName ����������
    * @return ����GUID
    */
    std::string     Player_PetMonsterByName(const std::string& guid, const std::string& monsterName);

    /**
    * @brief ͨ������ģ��ID�ٻ����ﲢ��������
    * @param guid ��ɫGUID
    * @param nTemplateID ����ģ��ID
    * @param luaObj �����б�
    * @return ����GUID
    */
    std::string     Player_PetMonsterIDByAttrTable(const std::string& guid,uint16_t nTemplateID,const CLuaObject &luaObj);

    /**
    * @brief ͨ�������������ٻ����ﲢ��������
    * @param guid ��ɫGUID
    * @param name ����������
    * @param luaObj �����б�
    * @return ����GUID
    */
    std::string     Player_PetMonsterNameByAttrTable(const std::string& guid, const std::string& name, const CLuaObject& luaObj);

    /**
    * @brief ��ȡ�����б�
    * @param guid ��ɫGUID
    * @return ����GUID�б�
    */
    CLuaObject      Player_GetPetList(const std::string& guid);

    /**
    * @brief ���ٳ���
    * @param guid ��ɫGUID
    * @param petguid ����GUID
    * @return ��
    */
    void            Player_DestroyPetMonster(const std::string& guid, const std::string& petguid);

    /**
    * @brief �������г���
    * @param guid ��ɫGUID
    * @return ��
    */
    void            Player_DestroyAllPetMonster(const std::string& guid);

    /**
    * @brief ���ó���AI�Ļ״̬
    * @param guid ��ɫGUID
    * @param petguid ����GUID
    * @param status �״̬
    * @return ��
    */
    void            Player_SetPetActivityStatus(const std::string& guid, const std::string& petguid, uint16_t status);

    /**
    * @brief ���ó����Ƿ�ɼ���
    * @param guid ��ɫGUID
    * @param petguid ����GUID
    * @param canPick �Ƿ�ɼ���
    * @return ��
    */
    void            Player_SetPetPickItemStatus(const std::string& guid, const std::string& petguid, bool canPick);

    /**
    * @brief �����̵�
    * @param guid ��ɫGUID
    * @param nShopID �̵�ID
    * @return ��
    */
    void            Player_EnterShop(const std::string& guid, uint16_t nShopID);

    /**
    * @brief ���븱����ͼ
    * @param guid ��ɫGUID
    * @param sMapKeyName ������ͼ������
    * @param edlogInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_EnterDgnMap(const std::string& guid, const std::string& sMapKeyName, const CLuaObject& edlogInfo);

    /**
    * @brief �뿪������ͼ
    * @param guid ��ɫGUID
    * @return 0�ɹ�������ʧ��
    */
    int             Player_ExitDgnMap(const std::string& guid);

    /**
    * @brief �ж�����Ƿ��ڸ�����ͼ��
    * @param guid ��ɫGUID
    * @return �ǻ��
    */
    bool            Player_IsInDgnMap(const std::string& guid);

    /**
    * @brief ��ȡ�����ո���
    * @param guid ��ɫGUID
    * @return �����ո���
    */
    uint16_t        Player_GetIdleBagCount(const std::string& guid);

    /**
    * @brief ��ȡ������һ�ո�����
    * @param guid ��ɫGUID
    * @return �����ո�������0��Ч
    */
    uint16_t        Player_GetBagFirstFreeSite(const std::string& guid);

    /**
    * @brief �ƶ���Ʒ
    * @param guid ��ɫGUID
    * @param itemguid ��ƷGUID
    * @param site ����Ŀ��λ������
    * @return �ɹ���ʧ��
    */
    bool            Player_ItemMove(const std::string& guid, const std::string& itemguid, uint16_t site);

    /**
    * @brief ��ӵ�����Ʒ
    * @param guid ��ɫGUID
    * @param tempid ��Ʒģ��ID
    * @param nBindRequire �Ƿ��
    * @param logInfo ��־��Ϣ
    * @return ��ƷGUID
    */
    std::string     Player_AddSingleItem(const std::string& guid, uint16_t tempid, uint8_t nBindRequire, const CLuaObject& logInfo);

    /**
    * @brief ������Ʒģ��ID�����Ʒ
    * @param guid ��ɫGUID
    * @param nTemplateID ��Ʒģ��ID
    * @param nNum �����Ʒ����
    * @param nBindRequire �Ƿ��
    * @param nSiteRange ��Ʒ��Χ
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_AddItem(const std::string& guid, uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, uint8_t nSiteRange, const CLuaObject& logInfo);

    /**
    * @brief ������Ʒ�����������Ʒ
    * @param guid ��ɫGUID
    * @param sKeyName ��Ʒ������
    * @param nNum �����Ʒ����
    * @param bBind �Ƿ��
    * @param nJob ��ɫ����
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_AddItemByKeyName(const std::string& guid, const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, const CLuaObject& logInfo);

    /**
    * @brief ������Ʒ�����������Ʒ������ָ��λ��
    * @param guid ��ɫGUID
    * @param sKeyName ��Ʒ������
    * @param nNum �����Ʒ����
    * @param bBind �Ƿ��
    * @param nJob ��ɫ����
    * @param nSite ����λ������
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_AddItemByKeyNameToSite(const std::string& guid, const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, const CLuaObject& logInfo);

    /**
    * @brief ���������Ʒ������
    * @param guid ��ɫGUID
    * @param luaObj �������Ʒ�б�
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_AddItems(const std::string& guid, const CLuaObject& luaObj, const CLuaObject& logInfo);

    /**
    * @brief ͨ����Ʒģ��IDɾ����Ʒ
    * @param guid ��ɫGUID
    * @param nTemplateID ��Ʒģ��ID
    * @param nNum ɾ����Ʒ����
    * @param bindRequire �Ƿ��
    * @param nSiteRange ��Ʒ��Χ
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_RemoveItem(const std::string& guid, uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const CLuaObject& logInfo);

    /**
    * @brief ͨ����ƷGUIDɾ����Ʒ
    * @param guid ��ɫGUID
    * @param itemGuid ��ƷGUID
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_RemoveItemByGuid(const std::string& guid, const std::string& itemGuid, const CLuaObject& logInfo);

    /**
    * @brief ͨ����ƷGUIDɾ����Ʒ
    * @param playerGUID ��ɫGUID
    * @param itemGUID ��ƷGUID
    * @param num ɾ����Ʒ����
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_RemoveItemByGuid2(const std::string &playerGUID, const std::string &itemGUID,
                                             uint16_t num, const CLuaObject &logInfo);

    /**
    * @brief ������Ʒ������ɾ����Ʒ
    * @param guid ��ɫGUID
    * @param keyName ��Ʒ������
    * @param nNum ɾ����Ʒ����
    * @param bindRequire �Ƿ��
    * @param nSiteRange ��Ʒ��Χ
    * @param logInfo ��־��Ϣ
    * @return 0�ɹ�������ʧ��
    */
    int             Player_RemoveItemByKeyName(const std::string& guid, const std::string& keyName, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const CLuaObject& logInfo);

    /**
    * @brief ɾ��ָ����Χ��������Ʒ
    * @param guid ��ɫGUID
    * @param type ��Ʒ��Χ����
    * @return 0�ɹ�������ʧ��
    */
    int             Player_RemoveAllItem(const std::string& guid, rolepack_opt_type type);

    /**
    * @brief ������Ʒģ��ID��ȡָ����Χ����Ʒ����
    * @param guid ��ɫGUID
    * @param templateID ��Ʒģ��ID
    * @param bindRequire �Ƿ��
    * @param nSiteRange ��Ʒ��Χ
    * @return ��Ʒ����
    */
    uint32_t        Player_GetItemNum(const std::string& guid, uint16_t templateID, uint8_t bindRequire, uint8_t nSiteRange);

    /**
    * @brief ������Ʒ��������ȡָ����Χ����Ʒ����
    * @param guid ��ɫGUID
    * @param keyName ��Ʒ������
    * @param bindRequire �Ƿ��
    * @param nSiteRange ��Ʒ��Χ
    * @return ��Ʒ����
    */
    uint32_t        Player_GetItemNumByKeyName(const std::string& guid, const std::string& keyName, uint8_t bindRequire, uint8_t nSiteRange);

    /**
    * @brief ��ȡָ����Ʒ����
    * @param guid ��ɫGUID
    * @param itemguid ��ƷGUID
    * @return ��Ʒ����
    */
    uint16_t        Player_GetItemAmount(const std::string& guid, const std::string& itemguid);

    /**
    * @brief ����ָ����Ʒ����
    * @param guid ��ɫGUID
    * @param itemguid ��ƷGUID
    * @param num ��Ʒ����
    * @param logInfo ��־��Ϣ
    * @return �ɹ���ʧ��
    */
    bool            Player_SetItemAmount(const std::string& guid, const std::string& itemguid, uint32_t num, const CLuaObject& logInfo);

    /**
    * @brief ��ȡ��������Ŷӳ�Ա����
    * @param guid ��ɫGUID
    * @return �Ŷӳ�Ա����
    */
    uint16_t        Player_GetTeamMemNum(const std::string& guid);

    /**
    * @brief ��ȡ��������Ŷӽ�ɫ���б�
    * @param guid ��ɫGUID
    * @return �Ŷӽ�ɫ���б���һ��������ʾ�Ƿ��Ƕӳ�
    */
    CLuaObject      Player_GetTeamInfo(const std::string& guid);

    /**
    * @brief ��ȡ��������Ŷ�GUID
    * @param guid ��ɫGUID
    * @return �Ŷ�GUID
    */
    std::string     Player_GetTeamGuid(const std::string& guid);

    void            Player_StartQuestDialog(const std::string& guid, const std::string& npcGuid, uint16_t nQuestID, uint8_t nState);
    bool            Player_IsDoingQuest(const std::string& guid);
    int             Player_GetQuestState(const std::string& guid);
    CLuaObject      Player_GetAcceptableQuests(const std::string& guid);
    uint16_t        Player_GetCurQuestID(const std::string& guid);
    uint16_t        Player_GetPreQuestID(const std::string& guid);
    void            Player_TalkToNpc(const std::string& guid, const std::string& npcGuid, const std::string& dialog);

    /**
    * @brief �����л�
    * @param guid ��ɫGUID
    * @param guildName �л���
    * @return 0�ɹ�������ʧ��
    */
    int             Player_CreateGuild(const std::string& guid, const std::string& guildName);

    /**
    * @brief ��Ӽ���
    * @param guid ��ɫGUID
    * @param skillID ����ID
    * @param active �Ƿ񼤻�
    * @return 0�ɹ�������ʧ��
    */
    int             Player_AddSkill(const std::string& guid, uint16_t skillID, bool active);

    /**
    * @brief ɾ������
    * @param guid ��ɫGUID
    * @param skillID ����ID
    * @param delAllInSameChain �Ƿ�ɾ��ͬһ�����������м���
    * @return ��
    */
    void            Player_DeleteSkill(const std::string& guid, uint16_t skillID, bool delAllInSameChain = false);

    /**
    * @brief �жϼ����Ƿ����
    * @param guid ��ɫGUID
    * @param skillID ����ID
    * @param searchSkillChain �Ƿ����ͬһ�������еļ���
    * @return �ǻ��
    */
    bool            Player_SkillIsExist(const std::string& guid, uint16_t skillID, bool searchSkillChain = false);

    /**
    * @brief ��ȡ��ҵļ���ID�б�
    * @param guid ��ɫGUID
    * @return ����ID�б�
    */
    CLuaObject      Player_GetSkillIDList(const std::string &guid);

    /**
    * @brief ͨ��������ID��ȡ����ID
    * @param guid ��ɫGUID
    * @param chainID ������ID
    * @return ����ID
    */
    uint16_t        Player_GetSkillIDByChainID(const std::string &guid, uint32_t chainID);

    /**
    * @brief ��ȡ�ֿ���ÿռ�
    * @param guid ��ɫGUID
    * @return �ֿ���ÿռ�
    */
    uint16_t        Player_GetWarehouseFreeSize(const std::string& guid);

    /**
    * @brief ��ȡ�߼��ֿ���ÿռ�
    * @param guid ��ɫGUID
    * @return �߼��ֿ���ÿռ�
    */
    uint16_t        Player_GetAdvWarehouseFreeSize(const std::string& guid);

    /**
    * @brief ��ȡ�ֿ��һ������λ������
    * @param guid ��ɫGUID
    * @return λ������
    */
    uint16_t        Player_GetWarehouseFirstFreeSite(const std::string& guid);

    /**
    * @brief ��ȡ�߼��ֿ��һ������λ������
    * @param guid ��ɫGUID
    * @return λ������
    */
    uint16_t        Player_GetAdvWarehouseFirstFreeSite(const std::string& guid);

    /**
    * @brief ��ȡGMȨ�޵ȼ�
    * @param guid ��ɫGUID
    * @return Ȩ�޵ȼ�
    */
    uint16_t        Player_GetGmModLevel(const std::string& guid);

    /**
    * @brief ��ȡVIP��Ȩ�б�
    * @param guid ��ɫGUID
    * @return ��Ȩ�б�
    */
    CLuaObject      Player_GetVipExtePermissions(const std::string& guid);

    /**
    * @brief �Ƿ���VIP��Ȩ
    * @param guid ��ɫGUID
    * @param permissions ��Ȩ
    * @return �ǻ��
    */
    bool            Player_HasVipExtePermissions(const std::string& guid, int32_t permissions);

    /**
    * @brief ���Ϳͻ�����ʾ��Ϣ
    * @param type ���ͷ�Χ
    * @param site ��Ϣ��ʾλ��
    * @param foreground ��Ϣǰ����ɫID
    * @param background ��Ϣ������ɫID
    * @param msg ��Ϣ����
    * @param guid ����ȷ����Χ��GUID
    * @param count ��Ϣ��������
    * @return ��
    */
    void            Player_SendMsgNtf(const uint8_t type, const uint8_t site, const uint8_t foreground,const uint8_t background,
                                      const std::string& msg,const std::string& guid="", const uint8_t count=1);

    /**
    * @brief ��ȡ������л��е�ͷ��
    * @param guid ��ɫGUID
    * @return ͷ��ID
    */
    int             Player_GetGuildMemberTitle(const std::string &guid);

    /**
    * @brief ��ȡ������л��е�ԭͷ��
    * @param guid ��ɫGUID
    * @return ԭͷ��ID
    */
    int             Player_GetGuildMemberOldTitle(const std::string &guid);

    /**
    * @brief ��ȡ������л��е���ͷ��
    * @param guid ��ɫGUID
    * @return ��ͷ��ID
    */
    int             Player_GetGuildMemberNewTitle(const std::string &guid);

    /**
    * @brief ��ȡ��������л�GUID
    * @param playerGUID ��ɫGUID
    * @return �л�GUID
    */
    std::string     Player_GetGuildGUID(const std::string &playerGUID);

    /**
    * @brief ��ȡ��������л���
    * @param guid ��ɫGUID
    * @return �л���
    */
    std::string     Player_GetGuildName(const std::string& guid);

    /**
    * @brief ��ȡ��Ҷ����л�ĵ�ǰ���׶�
    * @param playerGUID ��ɫGUID
    * @return ��ǰ���׶�
    */
    uint32_t        Player_GetCurContrib(const std::string &playerGUID);

    /**
    * @brief ������Ҷ����л�ĵ�ǰ���׶�
    * @param playerGUID ��ɫGUID
    * @param contrib ��ǰ���׶�
    * @return ��
    */
    void            Player_SetCurContrib(const std::string &playerGUID, uint32_t contrib);

    /**
    * @brief ��ȡ��Ҷ����л���ۼƹ��׶�
    * @param playerGUID ��ɫGUID
    * @return �ۼƹ��׶�
    */
    uint32_t        Player_GetTotalContrib(const std::string &playerGUID);

    /**
    * @brief ��ȡָ����Χ��ƷGUID�б�
    * @param guid ��ɫGUID
    * @param type ��Ʒ��Χ
    * @return ͨ��LuaRet������ƷGUID�б�
    */
    void            Player_GetRolePackInfo(const std::string& guid, const int type);

    /**
    * @brief ͨ����Ʒλ��������ȡ��ƷGUID
    * @param guid ��ɫGUID
    * @param site ��Ʒλ������
    * @return ��ƷGUID
    */
    std::string     Player_GetItemBySite(const std::string& guid, const int site); 
    
    /**
	* @brief ͨ����ƷGUID��ȡ��Ʒλ��
	* @param guid ��ɫGUID
	* @param itemguid ��ƷGUID
	* @return ��Ʒsite
	*/
    int     Player_GetItemSiteByGuid(const std::string& guid, const std::string& itemguid);

    /**
    * @brief ��ȡ��Ʒ������
    * @param guid ��ɫGUID
    * @param itemguid ��ƷGUID
    * @return ��Ʒ������
    */
    int             Player_GetItemBindType(const std::string& guid, const std::string& itemguid);

    /**
    * @brief ������Ʒ������
    * @param guid ��ɫGUID
    * @param itemguid ��ƷGUID
    * @param type ��Ʒ������
    * @return ��
    */
    void            Player_SetItemBindType(const std::string& guid, const std::string& itemguid, int type);

    /**
    * @brief �����Զ�����뾶
    * @param guid ��ɫGUID
    * @param radius �Զ�����뾶
    * @return �ɹ���ʧ��
    */
    bool            Player_SetAutoPickItemRadius(const std::string &guid, uint8_t radius);

    /**
    * @brief �����Զ�������������
    * @param guid ��ɫGUID
    * @param relpos �����������㼯
    * @return �ɹ���ʧ��
    */
    bool            Player_SetAutoPickItemRelativePositions(const std::string &guid, const CLuaObject &relpos);

    /**
    * @brief �����Զ������ʱ���������ʱ���ڲ����ٴμ���
    * @param guid ��ɫGUID
    * @param interval �Զ�����ʱ����
    * @return �ɹ���ʧ��
    */
    bool            Player_SetAutoPickItemInterval(const std::string &guid, uint16_t interval);

    /**
    * @brief ������Ʒ���ñ�
    * @param guid ��ɫGUID
    * @param itemguid ��ƷGUID
    * @param tab ��Ʒ���ñ�
    * @return �ɹ���ʧ��
    */
    bool            Player_SetItemCfg(const std::string& guid, const std::string& itemguid, const CLuaObject& tab);

    /**
    * @brief ��Ҹ���
    * @param guid ��ɫGUID
    * @param name �½�ɫ��
    * @return �ɹ���ʧ��
    */
    bool            Player_SetName(const std::string& guid, const std::string& name);

    /**
    * @brief ��ӳƺ�
    * @param guid ��ɫGUID
    * @param titleName �ƺ�
    * @return �ɹ���ʧ��
    */
    bool            Player_AddTitle(const std::string& guid, const std::string& titleName);

    /**
    * @brief ɾ���ƺ�
    * @param guid ��ɫGUID
    * @param titleName �ƺ�
    * @return �ɹ���ʧ��
    */
    bool            Player_DelTitle(const std::string& guid, const std::string& titleName);

    /**
    * @brief �ж��Ƿ���ĳ���ƺ�
    * @param guid ��ɫGUID
    * @param titleName �ƺ�
    * @return �ǻ��
    */
    bool            Player_HasTitle(const std::string& guid, const std::string& titleName);

    /**
    * @brief ��ȡ�ƺ�������
    * @param titleID �ƺ�ģ��ID
    * @return �ƺ�������
    */
    std::string     Player_TitleIDToName(uint32_t titleID);

    /**
    * @brief ��ȡ�ƺ�ģ��ID
    * @param name �ƺ�������
    * @return �ƺ�ģ��ID
    */
    uint32_t        Player_TitleNameToID(const std::string& name);

    /**
    * @brief ͨ���������ȡ���
    * @param guid ��ɫGUID
    * @param type ���������
    * @param code �����
    * @return ��
    */
    void            Player_RedemptionActivationCode(const std::string& guid, uint16_t type, const std::string& code);

    /**
    * @brief ���Ӽ���������
    * @param guid ��ɫGUID
    * @param skillID ����ID
    * @param value ���ӵļ�����������ֵ
    * @return �ɹ���ʧ��
    */
    bool            Player_AddProficiencyValue(const std::string& guid, uint32_t skillID, uint32_t value);

    /**
    * @brief ���ļ��ܵȼ�
    * @param guid ��ɫGUID
    * @param skillID ����ID
    * @return �ɹ���ʧ��
    */
    bool            Player_SetSkillLevel(const std::string& guid, uint32_t skillID);
    /**
    * @brief �Ƿ񱻽���
    * @param guid ��ɫGUID
    * @return �ǻ��
    */
    bool            Player_IsProhibitChat(const std::string& guid);

    /**
    * @brief ��ȡ�����б�
    * @param guid ��ɫGUID
    * @param type ��������
    * @param min ����ID��Сֵ
    * @param max ����ID���ֵ
    * @return ����ID��ֵ�б�
    */
    CLuaObject      Player_GetListProp(const std::string& guid, uint16_t type, uint16_t min, uint16_t max);

    /**
    * @brief ��ȡ��ƷGUID�б�
    * @param guid ��ɫGUID
    * @param min ��Ʒλ��������Сֵ
    * @param max ��Ʒλ���������ֵ
    * @return ��Ʒλ��������GUID�б�
    */
    CLuaObject      Player_ItemGuidList(const std::string& guid, uint16_t min, uint16_t max);

    /**
    * @brief �Ƿ�߱�GMȨ��
    * @param guid ��ɫGUID
    * @return GMȨ�޵ȼ�
    */
    uint16_t        Player_IsLuaGM(const std::string& guid);

    /**
    * @brief Ͷ�����а���Ϣ
    * @param guid    ���guid
    * @param type    ���а�����
    * @param value   ����ֵ
    * @param desc    ����
    * @return  �Ƿ����ɹ�
    */
    bool            Player_AddCustListInfo(const std::string& guid, int type, const std::string& value, const std::string& desc);

    /**
    * @brief ��������Ա�
    * @param guid    ���guid
    * @param gender  ��������Ա� 1������ 2��Ů��
    * @return  �Ƿ����óɹ�
    */
    bool            Player_SetGender(const std::string& guid, int gender);

    /**
    * @brief �����ɫ������Ϣ
    * @param guid    ��ɫguid
    * @param info    ������Ϣ����(���512�ֽ�)
    * @return  ��
    */
    void               Role_InsertInfo(const std::string& guid, const std::string& info);

    /**
    * @brief ���½�ɫ������Ϣ
    * @param guid    ��ɫguid
    * @param info    ������Ϣ����(���512�ֽ�)
    * @return  ��
    */
    void               Role_UpdateInfo(const std::string& guid, const std::string& info);

    /**
    * @brief ��ս�ɫ������Ϣ
    * @param guid    ��ɫguid
    * @return  ��
    */
    void               Role_ClearInfo(const std::string& guid );

    /**
    * @brief ɾ����ɫ������Ϣ�е��Ӵ�
    * @param guid    ��ɫguid
    * @param info    ��ɾ�����ִ���Ϣ
    * @return  ��
    */
    void               Role_DelInfo(const std::string& guid, const std::string& info);

    /**
    * @brief �����ȡ��ɫ������Ϣ
    * @param guid    ��ɫguid
    * @return  ��
    */
    void               Role_GetInfoReq(const std::string& guid );

    /**
    * @brief ��ȡ��ɫ������Ϣ
    * @param guid    ��ɫguid
    * @return  ������Ϣ����
    */
    const std::string  Role_GetInfoAck(const std::string& guid );

    /**
    * @brief ���ý�ɫ��̬����
    * @param guid    ��ɫguid
    * @param index   ���Լ����±�����
    * @param attr    ����id
    * @param value   ����ֵ
    * @return  ��
    */
    void                Role_SetDynAttr(const std::string& guid, uint16_t index, uint16_t attr, int32_t value);

    /**
    * @brief ��ȡ��ɫ��̬����
    * @param guid    ��ɫguid
    * @param index   ���Լ����±�����
    * @return  lua����,��ʽ����
    * {"index"= (uint16_t)�±�����,"attr"=(uint16_t)����id,"value"=(int32_t)����ֵ)}
    */
    CLuaObject          Role_GetDynAttr(const std::string& guid, uint16_t index);

public:     // NPC export functions
    /**
    * @brief ��npc������(δʹ��)
    * @param guid     npc��guid
    * @param ack      ��������
    * @return   ������,��Ϊ0
    */
    uint16_t        Npc_NpcTalkAck(const std::string& guid, const std::string& ack);

    /**
    * @brief ��ȡnpc���õ�ģ��id
    * @param guid     npc��guid
    * @return   ģ��id
    */
    int             Npc_GetTemplateID(const std::string& guid);

    /**
    * @brief ��ȡnpc������
    * @param guid     npc��guid
    * @return   npc������
    */
    std::string     NPC_GetKeyName(const string& guid);
public:     // Monster export functions
    /**
    * @brief ����
    * @param guid   �����guid
    * @param x      Ŀ��x
    * @param y      Ŀ��y
    * @return       ��
    */
    void Monster_BeSuckedAway(const std::string& guid, uint16_t x, uint16_t y);
    /**
    * @brief ���ù�����ǳ�
    * @param guid         �����guid
    * @param sMasterName  �����ǳ�
    * @return       ��
    */
    void            Monster_SetMasterName(const std::string& guid, const std::string& sMasterName);

    /**
    * @brief ��ȡ�����ģ��id
    * @param guid         �����guid
    * @return       ����ģ��id
    */
    int             Monster_GetTemplateID(const std::string& guid);

    /**
    * @brief ��ȡ�����ģ��id
    * @param KeyName  �����������
    * @return         ����ģ��id
    */
    int             Monster_GetTemplateIDByName(const std::string KeyName);

    /**
    * @brief ��ȡ�����������˵�guid
    * @param guid   �����guid
    * @return       �������˵�guid
    */
    std::string     Monster_GetMasterGUIDAsString(const std::string& guid);

    /**
    * @brief ��ȡ���ﱻ��ɱ��ר���Ľ�ɫguid
    * @param guid         �����guid
    * @return       ר���Ľ�ɫguid
    */
    std::string     Monster_GetBelongPlayerIDAsString(const std::string& guid);

    /**
    * @brief ���ù�����ٻ�����
    * @param guid         �����guid
    * @param type         ����
    * @return       ��
    */
    void            Monster_SetSummonMonsterType(const std::string &guid, uint8_t type);

    /**
    * @brief ��ȡ�������еĳ����Ϣ
    * @param guid         �����guid
    * @param type         ����
    * @return       lua����,��ʽ����
    * {{ (uint64)��ɫguid1, (float)���ֵ1, (uint64)ʱ���1},{ (uint64)��ɫguid2, (float)���ֵ2, (uint64)ʱ���2}, ...}
    */
    CLuaObject            Monster_GetHateValueMap(const std::string& guid);

    /**
    * @brief ��ȡ���ﵱǰ������Ŀ���ɫ
    * @param guid         �����guid
    * @return       Ŀ���ɫguid
    */
    const std::string     Monster_GetCurAttackTar(const std::string& guid);

    /**
    * @brief ��ʼ���ڳ������
    * @param guid         �ڳ�������guid
    * @param targuid      �������˵�guid
    * @param x            Ŀ�ĵ�x����
    * @param y            Ŀ�ĵ�y����
    * @param range        ���淶Χ
    * @param finalRange   �յ�귶Χ
    * @param posRange     ���귶Χ
    * @param mPos         ·�����꼯��
    * @param func         �����Ļص�����
    * @return       Ŀ���ɫguid
    */
    void                  Monster_InitBiaoChe(const std::string &guid,const std::string & targuid,uint16_t x,uint16_t y,uint16_t range, uint16_t finalRange,
        uint8_t posRange,  const CLuaObject& posTable, const std::string&func);

    /**
    * @brief ע�����������Ϊ
    * @param guid         �����guid
    * @param info         ��Ϊ���ݱ�,��ʽ{{(monster_behaviour_trigger)��Ϊid1,(string)�ص�����1,(string)�ص�����1},...}
    * @return       ��
    */
    void                  Monster_RegisterBehavior(const std::string& guid, const CLuaObject& info );

    /**
    * @brief ע��������Ա�
    * @param guid         �����guid
    * @param info         �������ݱ�,��ʽ{(MonsterAI_Attribute)����id1,...}
    * @return       ��
    */
    void                  Monster_RegisterAttribute(const std::string& guid, const CLuaObject& info);

    /**
    * @brief ע������������Ϊ
    * @param guid         �����guid
    * @param behaviorID   ��Ϊid
    * @return       ��
    */
    void                  Monster_RemoveMonsterBehavior(const std::string& guid, uint16_t behaviorID);

    /**
    * @brief �Ƴ�����,ʹ��������
    * @param guid         �����guid
    * @param appearBody   �Ƿ���ʬ��
    * @return       ��
    */
    void                  Monster_RemoveMonster(const std::string& guid, bool appearBody); // û�е��� û�о��� û������ ���Ƴ�����
    
    /**
    * @brief ���ù�������ʾ����ɫ
    * @param guid         �����guid
    * @param nameColor    ��ɫ��Ϣ
    * @return       ��
    */
    void                  Monster_SetNameColor(const std::string& guid, const std::string& nameColor);

    //��������
    /**
    * @brief ���ù���ĵ�ǰ������
    * @param guid         �����guid
    * @param skillGroup   ������id
    * @return       ��
    */
    void            Monster_SwapSkillGroup(const std::string& guid, uint16_t skillGroup);

    /**
    * @brief ��ʶ����ʹ�����⼼��
    * @param guid         �����guid
    * @param Skillid      ����id
    * @return       ��
    */
    void            Monster_UseSpecialSkill(const std::string& guid, uint32_t Skillid);

    /**
    * @brief ������������
    * @param guid         �����guid
    * @param dis          �����ܵ�������뾶
    * @return       ��
    */
    void            Monster_Escape(const std::string& guid, int dis);

    /**
    * @brief ��������ӿ��ͷŵļ���
    * @param guid         �����guid
    * @param skillinfo    ����ӵļ�����Ϣ,��ʽ{(uint32_t)����id,(uint32_t)����Ȩ��}
    * @return       ��
    */
    void            Monster_AddSkill(const std::string& guid, const CLuaObject& skillinfo);

    /**
    * @brief �Ƴ�������ͷŵļ���
    * @param guid         �����guid
    * @param SkillID      ���Ƴ��ļ���id
    * @return       ��
    */
    void            Monster_RemoveSkill(const std::string& guid, uint32_t SkillID);

    /**
    * @brief ��ȡ������ͷŵļ�������Ϣ
    * @param guid         �����guid
    * @return       LuaRet,��ʽ{{(int)����id1,(int)����Ȩ��1},{(int)����id2,(int)����Ȩ��2},...}
    */
    void            Monster_GetCurSkillGroup(const std::string& guid);

    /**
    * @brief ����������
    * @param guid         �����guid
    * @param killerGuid   ��ɱ��ɫ��guid
    * @return       ��
    */
    void            Monster_DropItem(const std::string& guid,const std::string&killerGuid);

    /**
    * @brief ˢ���ڳ�Ѱ·
    * @param guid         �����guid
    * @return       �Ƿ�ˢ�³ɹ�
    */
    bool            Monster_UpdateBiaocheAI(const std::string& guid);

    /**
    * @brief ���õ�ʿ����������˹���
    * @param guid   �����guid
    * @param state  ����״̬ 0�������� 1������
    * @return �Ƿ����óɹ�
    */
    bool            Monster_SetPetFollowMasterAttackState(const std::string& guid, uint8_t state);

public:             // Guild export functions
    /**
    * @brief ��ȡ����guid
    * @param guildName    ������
    * @return       ����guid
    */
    std::string     Guild_GetGUIDByName(const std::string &guildName);

    /**
    * @brief ��ȡ����᳤guid
    * @param guildName    ����guid
    * @return       �᳤guid
    */
    std::string     Guild_GetLeaderName(const std::string &guildGUID);

    /**
    * @brief ��������ụΪ����
    * @param myGuildName      ����1��
    * @param allyGuildName    ����2��
    * @return           ��ӽ��
    */
    int             Guild_AddAlly(const std::string &myGuildName, const std::string &allyGuildName);

    /**
    * @brief �����ụ��������
    * @param myGuildName      ����1��
    * @param allyGuildName    ����2��
    * @return           ������
    */
    int             Guild_DelAlly(const std::string &myGuildName, const std::string &allyGuildName);

    /**
    * @brief �������Ƿ�Ϊ����
    * @param myGuildName      ����1��
    * @param allyGuildName    ����2��
    * @return           �Ƿ�����
    */
    bool            Guild_IsAlly(const std::string &myGuildName, const std::string &allyGuildName);

    /**
    * @brief ��������ụΪ�ж�
    * @param myGuildName      ����1��
    * @param allyGuildName    ����2��
    * @return           ��ӽ��
    */
    int             Guild_AddEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    /**
    * @brief �����ụ�����ж�
    * @param myGuildName      ����1��
    * @param allyGuildName    ����2��
    * @return           ������
    */
    int             Guild_DelEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    /**
    * @brief �������Ƿ�Ϊ�ж�
    * @param myGuildName      ����1��
    * @param allyGuildName    ����2��
    * @return           �Ƿ�ж�
    */
    bool            Guild_IsEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    /**
    * @brief            ��ȡ���й�����
    * @return           lua����,��ʽ{(string)������1,(string)������2,...}
    */
    CLuaObject      Guild_GetGuildNameList();

    /**
    * @brief ��ȡָ������ĳ�Աguid�б�
    * @param GuildGUID        ����guid
    * @return           lua����,��ʽ{(string)��ɫguid1,(string)��ɫguid2,...}
    */
    CLuaObject      Guild_GetGuildMember(const std::string& GuildGUID);

    /**
    * @brief �����ֱ�Ӽ��빤��
    * @param playerGuid       ���guid
    * @param guildGuid        ����guid
    * @return           ������
    */
    int32_t         Guild_JoinGuild(const std::string& playerGuid, const std::string& guildGuid);

    /**
    * @brief ���ù���ȼ�
    * @param guildGuid        ����guid
    * @param level            ����ȼ�
    * @return           ������
    */
    int32_t         Guild_SetGuildLevel(const std::string& guildGuid, uint16_t level);

    /**
    * @brief ��������ս
    * @param guildGuid        ����1guid
    * @param enemyGuildGuid   ����2guid
    * @param durTime          ����ʱ��
    * @return           ��
    */
    void            Guild_GuildWar(const std::string& guildGuid, const std::string& enemyGuildGuid, uint32_t durTime);
    
    /**
    * @brief ���ù����Զ��������Ƶȼ�
    * @param GuildGUID        ����guid
    * @param level            ��ɫ����ȼ�
    * @return           ���ý��
    */
    int32_t         Guild_SetGuildAutoJoinLevel(const std::string& GuildGUID, uint32_t level);

    /**
    * @brief �޸��лṫ��
    * @param guildGUID ����GUID
    * @param notice ����
    * @return ���
    */
    int32_t         Guild_EditGuildNotice(const std::string& guildGuid, const std::string& notice);

    /**
    * @brief �޸��л��Աtitle(���÷ǻ᳤ʱ,memberGUID����Ϊ�᳤guid��ת�û᳤ֱ������������ԱΪ�᳤)
    * @param memberGUID ��ԱGUID
    * @param title title
    * @return ���
    */
    int32_t         Guild_ChangeGuildMemberTitle(const std::string& memberGUID, uint8_t title);

    /**
    * @brief ����(��T�᳤�������)
    * @param memberGUID ��ԱGUID
    * @return ���
    */
    int32_t         Guild_KickGuildMember(const std::string& memberGUID);

    /**
    * @brief ��ɢ�л�
    * @param guildGUID ����GUID
    * @return ���
    */
    int32_t         Guild_DestroyGuild(const std::string& guildGuid);
public:             // Item export functions
    /**
    * @brief ������Ʒ�;ö�
    * @param guid             ��Ʒguid
    * @param value            ����ֵ
    * @return           ��
    */
    void            Item_UpdateDurability(const std::string& guid, int32_t value);

    /**
    * @brief ��ȡ��Ʒ�;ö�
    * @param guid             ��Ʒguid
    * @return           ��Ʒ�;ö�
    */
    int32_t         Item_Geturability(const std::string& guid);

    /**
    * @brief ������Ʒ��̬����
    * @param guid    ��Ʒguid
    * @param index   ���Լ����±�����
    * @param attr    ����id
    * @param value   ����ֵ
    * @return  ��
    */
    void            Item_SetDynAttr(const std::string &guid, uint16_t index, uint16_t attr, int32_t value);

    /**
    * @brief ��ȡ��Ʒ��̬����
    * @param guid    ��Ʒguid
    * @param index   ���Լ����±�����
    * @return  lua����,��ʽ����
    * {"index"= (uint16_t)�±�����,"attr"=(uint16_t)����id,"value"=(int32_t)����ֵ)}
    */
    CLuaObject      Item_GetDynAttr(const std::string &guid, uint16_t index);

    /**
    * @brief ��ȡ��Ʒģ��id
    * @param guid    ��Ʒguid
    * @return  ��Ʒģ��id
    */
    int             Item_GetTempId(const std::string& guid);

    /**
    * @brief ��Ʒ��Ϣjson��ʽ����
    * @param guid    ��Ʒguid
    * @return  ��Ʒjson��ʽ��Ϣ
    */
    std::string     Item_ItemInfoEncodeToJson(const std::string& guid);

    /**
    * @brief ��Ʒ��Ϣjson��ʽ����
    * @param info     ��Ʒjson��ʽ��Ϣ
    * @param belong   ��Ʒ������ɫguid
    * @return   ��Ʒguid
    */
    std::string     Item_DecodeJsonToAddItem(const std::string& info,const std::string &belong = "");

    /**
    * @brief ������Ʒ������
    * @param guid     ��Ʒguid
    * @param belong   ��Ʒ������ɫguid
    * @param subtype  ������id
    * @return   ���ý��
    */
    bool            Item_SetSubType(const std::string& guid, const std::string& belong, uint16_t subtype);

    /**
    * @brief ������Ʒ��
    * @param playerguid       ��Ʒ������ɫguid
    * @param guid             ��Ʒguid
    * @param Name             ��Ʒ��
    * @return           ���ý��
    */
    bool            Item_SetName(const std::string& playerguid, const std::string& guid, const std::string& Name);

    /**
    * @brief ��ȡ��Ʒ��״̬
    * @param guid             ��Ʒguid
    * @return           �Ƿ��
    */
    bool            Item_IsBind(const std::string &itemGUID);


public:             // log
    /**
    * @brief ���־
    * @param activeName       �����
    * @param rewardName       ��������
    * @param roleGuid         ��ɫguid
    * @param itemInfo         ������Ʒ��Ϣ
    * @param goldInfo         ���������Ϣ
    * @return           ��
    */
    void            Log_ActivityData(const string& activeName, const string& rewardName, const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

    /**
    * @brief ������־
    * @param rewardName       ��������
    * @param roleGuid         ��ɫguid
    * @param itemInfo         ������Ʒ��Ϣ
    * @param goldInfo         ���������Ϣ
    * @return           ��
    */
    void            Log_RewardData(const string& rewardName, const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

    /**
    * @brief �����־
    * @param giftName         �������
    * @param roleGuid         ��ɫguid
    * @param itemInfo         �����Ʒ��Ϣ
    * @param goldInfo         ��������Ϣ
    * @return           ��
    */
    void            Log_GiftPackData(const string& giftName, const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

    /**
    * @brief ������־
    * @param roleGuid         ��ɫguid
    * @param itemInfo         ������Ʒ��Ϣ
    * @param goldInfo         ���������Ϣ
    * @return           ��
    */
    void            Log_RecoveryData(const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

public:             // shabak export functions
    /**
    * @brief ��ʼ��ɳս
    * @param guildNames       �μӹ�ɳս�����й������ļ���,��ʽ{(string)������1,(string)������2,...}
    * @param startTime        ��ʼʱ��
    * @param duration         ����ʱ��
    * @return           �Ƿ���ɹ�
    */
    bool            StartCastleWar(const CLuaObject &guildNames, const std::string &startTime, uint32_t duration);

    /**
    * @brief            ֹͣ��ɳս
    * @return           �Ƿ���ɹ�
    */
    bool            StopCastleWar();

    /**
    * @brief            ��ȡ���в��빥ɳ�Ĺ�����
    * @return           lua����,��ʽ{(string)������1,(string)������2,...}
    */
    CLuaObject      GetCastleAttackFamily();

    /**
    * @brief            ��ȡɳ�Ϳ˹����Ĺ�����
    * @return           ������
    */
    std::string     GetCastleOwnFamily();

    /**
    * @brief ����ɳ�Ϳ˹����Ĺ���
    * @param guildName        �¹�����
    * @return           ��
    */
    void            SetCastleOwnFamily(std::string guildName);

    /**
    * @brief            ��ѯ��ɳս��ʼʱ��
    * @return           ��ʼʱ��
    */
    std::string     QueryCastleStart();

    /**
    * @brief            ��ѯ��ɳս�Ƿ��Ѿ���ʼ
    * @return           �Ƿ�ʼ
    */
    bool            IsCastleWarStart();

    /**
    * @brief ���ɹ�ɳ����
    * @param type             ��������
    * @return           ��
    */
    void            GenCastleMonster(uint32_t type);    // type: 1�����Ź��2���ʹ����Ź֣�3�����Ź�

public:             // wanted list export functions
    /**
    * @brief            ��ȡ����������Ϣ
    * @return           lua����,��ʽ
    * {{"guid"=(string)������guid1,"name"=(string)��������1,"online"=(bool)�Ƿ�����,"bounty"=(uint32_t)�ͽ�,"desc"={{(string)����,(uint64_t)��������ʱ��},...}, "time"=(string)��������ʱ��}, ...}
    */
    CLuaObject      GetWantedList();
    
    /**
    * @brief ��������������Ϣ
    * @param wantedByGUID     ��������guid
    * @param wantedName       �������͵������
    * @param bounty           �ͽ�
    * @param desc             ����������Ϣ
    * @return           ��
    */
    void            PostBounty(const std::string &wantedByGUID, const std::string &wantedName, uint32_t bounty, const std::string &desc);

    /**
    * @brief ��ȡɾ��������Ϣ
    * @param roleGuid         ��ɫguid
    * @return           lua����,��ʽ{"RoleGuid"=(string)��ɫguid,"BeExist"=(bool)�Ƿ���ڽ���, "BeUsed"=(bool)�Ƿ��Ѿ���ȡ, "Money"=(string)��������}
    */
    CLuaObject      GetRebateMoneyInfo(const std::string& roleGuid);

    /**
    * @brief ��ȡɾ������
    * @param roleGuid         ��ɫguid
    * @return           ��
    */
    void            GetRebateMoney(const std::string& roleGuid);
    /**
    * @brief ��ʽ�����ܿ���������������������
    * @brief �����Ƿ��ӡ  �ʹ�ӡ���Ա仯��¼   ����1 ����  ����0 �ر�   ��ӡ 1010  
    * @param roleGuid         ��ɫguid
    * @param prop             ����id
    * @return           ��
    */
    int32_t         Role_GetProp_Info(const std::string& guid, int prop);

    /**
    * @brief �����ͻ�ȡ��ɫ��Χ��ɫ
    * @param guid             ��ɫguid
    * @param type             ��ɫ����   0:���н�ɫ  1:���  2:npc  3:����  4:����  5:��Ұ�̯ģ��  6:��ҷ���
    * @return           ��ɫ�б� {guid1,guid2,guid3...}
    */
    CLuaObject       Role_GetRegionRoleByType(const std::string& guid, uint8_t type);

    /*
    @brief                ��������
    */
    void            PostHttpCurl(const std::string& cmd, const std::string& custom, const std::string& callBackFunc);
    /**
   * @brief �����ƶ��ӳ����
   * @param num              ��ֱ� 
   * @return           ��
   */
    void            SetMoveMistake(uint32_t num);
    /**
    * @brief            ִ�пͻ��˽ű���
     * @param guid ��ɫguid
     * @param sScriptName �ű�������
     * @param sContent ִ�еı�����
     * @param bCompress �������Ƿ�ѹ��
     * @param type 0��Ҹ������� 1 ��ͼ  2 ����������
     * @return ��
    */
    void            Player_RunClientScript_plus(const std::string& guid, const std::string& sScriptName, const std::string& sContent, bool bCompress, uint16_t type);

    std::string     _LuaSerialize(const CLuaObject& luaObj, std::string& str);
    /**
        * @brief  c++ ���л�
        * @return string
    */
    std::string     LuaSerialize(const CLuaObject& luaObj);

    /**
   * @brief �Ƿ�win32����
   * @return           �Ƿ�
   */
    bool            IsWin32();

    /**
    * @brief ��ȡ��ǰ΢��
    * @return     
    */
    std::string     Getmicrosecond();

    /**
    * @brief ��������
    * @param num1 ����1
    * @param num2 ����2
    * @param type 1�ӷ� 2���� 3 �˷� 4 ����
    * @return
    */
    std::string     BigNumberCalculation(const std::string& num1, const std::string& num2, int type);

    bool            GetRecordhistory() { return mRecordhistory; }
    void            SetRecordhistory(bool brecord) { mRecordhistory = brecord; }
private:
    inline Role *   GetRole(const std::string &guid);
    inline Map *    GetMap(const std::string& mapGuid);
    inline Player*  GetPlayerByGuid(const std::string& guid);
    inline Npc*     GetNpcByGuid(const std::string& guid);
    inline Monster* GetMonsterByGuid(const std::string& guid);

    void SendCheckRoleExistenceReqToCS(uint32_t seq, uint8_t by, const std::string &name, uint64_t guid);

private:
    std::set<std::string>       mRunServScriptAllowedFuncs;
    std::set<int32_t>           mCallBackUpdateAttrs32;
    std::set<int32_t>           mCallBackUpdateAttrs64;
    bool                        mRecordhistory = false;
};
