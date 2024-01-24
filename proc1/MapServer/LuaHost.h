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

public:             // 注册为LUA API需要public
    LuaHost() {}
    ~LuaHost() {}

public:
    void            RegisterLuaAPI(CLuaScript *luaScript);

public:             // Global export functions
    /**
    * @brief            获取游戏内数据
    * @param propType   global_prop_type_min - global_prop_type_max
    * @return           返回bool   
    *                   返回 true 通过LuaRet 接取数据
    */
    bool            GetGlobalProp(uint16_t propType);
    /**
    * @brief            获取角色等级表数据 role.csv
    * @param level      等级
    * @param job        职业
    * @param propType   role_prop_type_min -role_prop_type_max
    * @return           返回bool   
    *                   返回 true 通过LuaRet 接取数据
    */
    bool            GetRoleCfgValue(uint32_t level, uint8_t job, uint16_t propType);
    /**
    * @brief            获取buff表数据   buff.csv
    * @param buffID 
    * @param propType   buff_prop_type_min -buff_prop_type_max
    * @return           返回bool   
    *                   返回 true 通过LuaRet 接取数据
    */
    bool            GetBuffProp(uint16_t buffID, uint16_t propType);
    /**
    * @brief            根据两个buff组  返回他们的组关系的参数  buff_group.csv
    * @param g1 
    * @param g2 
    * @param propType   BUFF_GROUP_PROP_TYPE_MIN -BUFF_GROUP_PROP_TYPE_MAX
    * @return           返回bool   
    *                   返回 true 通过LuaRet 接取数据
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
    * @brief                获取技能表数据 skill.csv
    * @param skillID 
    * @param propType       skill_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetSkillProp(uint16_t skillID, uint16_t propType);
    /**
    * @brief                获取怪物表数据  monster.csv
    * @param monsterID 
    * @param propType       monster_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetMonsterProp(uint16_t monsterID, uint16_t propType);
    /**
    * @brief                获取npc表数据 npc.csv
    * @param monsterID 
    * @param propType       npc_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetNpcProp(uint16_t npcID, uint16_t propType);
    /**
    * @brief                获取Map表数据 map.csv
    * @param mapID 
    * @param propType       map_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetMapProp(uint16_t mapID, uint16_t propType);
    /**
    * @brief                获取物品表数据 item.csv
    * @param itemID 
    * @param propType       item_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetItemProp(uint16_t itemID, uint16_t propType);
    /**
    * @brief                获取物品表数据 item.csv
    * @param itemKeyName 
    * @param propType       item_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetItemPropByKeyName(const std::string& itemKeyName, uint16_t propType);
    /**
    * @brief                获取group_att.csv表数据
    * @param groupID 
    * @param propType       GROUP_ATTR_PROP_TYPE_MIN
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    * 
    GROUP_ATTR_PROP_TYPE_MIN = 0,
    GROUP_ATTR_PROP_ID,
    GROUP_ATTR_PROP_DESC,
    GROUP_ATTR_PROP_GROUPINFO,
    GROUP_ATTR_PROP_TYPE_MAX,
    */
    bool            GetGroupAttrProp(uint16_t groupID, uint16_t propType);
    /**
    * @brief                获取quest.csv表数据
    * @param questID 
    * @param propType       quest_prop_type_min
    * @return               返回bool   
    *                       返回 true 通过LuaRet 接取数据
    */
    bool            GetQuestProp(uint16_t questID, uint16_t propType);
    /**
    * @brief                设置自定义Custvar属性
    * @param belong         角色id  可以设置 玩家 怪物 npc Pet 物品 行会
    * @param name           自定义Custvar属性名字
    * @param value          自定义Custvar的属性
    * @param type           0:永久保留 1:一天后删除
    * @return               返回bool   
    */
    bool            SetCustVar(const std::string &belong, std::string name, std::string value, uint8_t type);
    /**
    * @brief                设置自定义Custvar属性
    * @param name           自定义Custvar属性名字
    * @param value          自定义Custvar的属性
    * @param type           0 永久保留 1 一天后删除
    * @param mergeType       
    * @return               返回bool   
    * cvmt_keep_main          = 0,        // 保留主区数据
    * cvmt_addup              = 1,        // 数据相加（字符型数据相连，数值型数据相加）
    * cvmt_choose_bigger      = 2,        // 取最大的数据（仅对数值型数据生效）
    * cvmt_choose_smaller     = 3,        // 取最小的数据（仅对数值型数据生效）
    * cvmt_delete             = 4         // 数据清除
    */
    bool            SetCustVarEx(std::string name, std::string value, uint8_t type, uint8_t mergeType);
    /**
    * @brief                获取CustVar属性
    * @param belong         角色id  
    * @param name           自定义Custvar属性名字
    * @return               value  
    */
    std::string     GetCustVar(const std::string &belong, const std::string &name);
    
    /**
    * @brief                出现读取lua脚本
    * @param scriptType     读取类型   搜索script type def
    * @return               无  
    */
    void            ReloadScript(uint32_t scriptType);
    /**
    * @brief                自定义装备位
    * @param luaObj 
    * @return               是否成功
    * luaObj 参考
    * GlobalData.CustomSubToSize = {
    * {equip_custom_1,{site_equip_custom_1}}, --界灵
    * {equip_custom_8,{site_equip_custom_8}},
    * }  
    * LuaHost:RegisterCustomSiteAndSub(GlobalData.CustomSubToSize)
    */
    bool            RegisterCustomSiteAndSub(const CLuaObject& luaObj);

    /**
    * @brief            获取服务器参数
    * @param key        读取类型   包括 "AreaServerOpenTime"  "MergeAreaServerTime"  "MergeAreaServerCnt"
    * @return           参数   
    */
    std::string     GetConstantCfg(const std::string& key);
    void            SetConstantCfg(const std::string& key, const std::string& value);
    /**
    * @brief            设置创建角色是否需要校验码
    * @param beSet      是否需要0不需要,1需要
    * @return           无
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
    * @brief            删除邮件
    * @return           无   
    */
    void            DeleteMallRemainedData();
    /**
    * @brief            通过玩家名字获取玩家并且执行回调函数
    * @param name 
    * @param callback   回调 lua 
    * @return           无   
    */
    void            CheckIfRoleExistByName(const std::string &name, const CLuaObject &callback);
    /**
    * @brief            通过玩家名字获取玩家并且执行回调函数
    * @param guid 
    * @param callback   回调 lua 
    * @return           无   
    */
    void            CheckIfRoleExistByGUID(const std::string &guid, const CLuaObject &callback);
    /**
    * @brief            定时任务
    * @param name       任务名称
    * @param type       1：指定时间执行一次 2：年  3：月 4：周 5：天
    * @param scheduled  {"20:00:00"}||{string.format("%d-%02d-%02d %02d:%02d:%02d",closeTime.year,closeTime.month,closeTime.day,closeTime.hour,closeTime.min,closeTime.sec)}
    * @param callBack   回调 lua 函数
    * @param params     回调 lua函数带参
    * @return           无   
    */
    uint32_t        AddScheduled(/*uint32_t id, */const std::string& name, uint16_t type, const CLuaObject& scheduled, const std::string& callBack, const std::string& params);
    /**
    * @brief            延时任务
    * @param Guid       "0"为服务器  可设置玩家guid
    * @param interval   毫秒
    * @param loop       是否循环
    * @param callBack   回调 lua 函数
    * @return           id 任务id   
    */
    uint32_t        AddLuaTimer(const std::string& Guid, uint32_t interval, bool loop, const std::string &callBack);
    /**
    * @brief            延时任务
    * @param Guid       "0"为服务器  可设置玩家guid
    * @param interval   毫秒
    * @param loop       是否循环
    * @param callBack   回调 lua 函数
    * @return           id 任务id   
    */
    uint32_t        AddLuaTimerEx(const std::string& Guid, uint32_t interval, bool loop, CLuaObject callBack);

    /**
    * @brief            删除延时任务
    * @param Guid       "0"为服务器  可设置玩家guid
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @return           无   
    */
    void            RemoveLuaTimer(const std::string& Guid, uint32_t timerID);
    /**
    * @brief            延时任务计数
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @param key        可自定义
    * @param val        次数
    * @return           无  
    */
    void            AddNumData(uint32_t timerID, const std::string& key, uint32_t val);
    /**
    * @brief            获取延时任务计数
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @param key        可自定义
    * @return           次数 
    */
    uint32_t        GetNumData(uint32_t timerID, const std::string& key);
    /**
    * @brief            删除延时任务计数
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @param key        可自定义
    * @return           无 
    */
    void            RemoveNumData(uint32_t timerID, const std::string& key);
    /**
    * @brief            延时任务增加自定义变量
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @param key        可自定义
    * @param val        数据
    * @return           无 
    */
    void            AddStrData(uint32_t timerID, const std::string& key, const std::string& val);
    /**
    * @brief            获取延时任务增加自定义变量
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @param key        可自定义
    * @return           val 数据
    */
    std::string     GetStrData(uint32_t timerID, const std::string& key);
    /**
    * @brief            删除延时任务增加自定义变量
    * @param timerID    为AddLuaTimer|| AddLuaTimerEx 返回值
    * @param key        可自定义
    * @return           无
    */
    void            RemoveStrData(uint32_t timerID, const std::string& key);
    /**
    * @brief            通过玩家名字发送邮件
    * @param Rolename   玩家名字
    * @param title      邮件标题
    * @param text       邮件内容
    * @param additions  参考 {{itemKey,1,0}}
    * @param currency   参考 1000
    * @param type       类型搜索 role_attr_ext
    * @return 是否成功
    */
    int             AddMailByName(const std::string& Rolename, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type);
    /**
    * @brief            通过Guid发送邮件
    * @param Guid       角色Guid
    * @param title      邮件标题
    * @param text       邮件内容
    * @param additions  参考 {{itemKey,1,0}}
    * @param currency   参考 1000
    * @param type       类型搜索 role_attr_ext
    * @return 是否成功
    */
    int             AddMailByGuid(const std::string& Guid, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type);
    /**
    * @brief                加监听
    * @param objGUID        角色Guid
    * @param eventID        Trigger_null
    * @param callBack       回调函数
    * @return 无
    */
    void            AddTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack);
    /**
    * @brief                删除监听
    * @param objGUID        角色Guid
    * @param eventID        Trigger_null
    * @param callBack       回调函数
    * @return 无
    */
    void            RemoveTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack);
    /**
    * @brief                获取所有在线玩家
    * @return               local all_list = LuaHost:GetAllOnlinePlayerGuid() for k , v in pairs(all_list) do
    */
    CLuaObject      GetAllOnlinePlayerGuid();
    /**
    * @brief                所有在线玩家执行
    * @param scriptName     lua函数
    * @param params         参数
    * @return 无
    */
    void            RunLuaScriptEveryOnlinePlayer(const std::string& scriptName,const std::string& params);

    /**
    * @brief                c++计算int64_t
    * @param lhs            lhs
    * @param rhs            rhs
    * @param type           参数
    * @return               计算结果
    * 
    * type：
    * simple_Arithmetic_add      = 1,
    * simple_Arithmetic_subtract = 2,
    * simple_Arithmetic_multiply = 3,
    * simple_Arithmetic_divide   = 4,
    */
    std::string     SimpleArithmetic(const std::string& lhs, const std::string& rhs, int type);

    /**
    * @brief                设置允许运行的函数
    * @param allowFuncs     lua函数
    * @return 无
    */
    void            SetFormAllowFunc(const CLuaObject &allowFuncs);

    /**
    * @brief                判断是否允许运行
    * @param allowFuncs     lua函数
    * @return               bool
    */
    bool            IsRunServScriptAllowedFunc(const std::string &func);
    /**
    * @brief                设置属性变化时是否回调
    * @param allowFuncs     table
    * @return 无
    * local attrList = {
    *        role_base_max_hp,
    *        role_base_max_mp,}
    * SetCallBackUpdateAttr32(attrList)
    */
    void            SetCallBackUpdateAttr32(const CLuaObject& allowFuncs);
    /**
    * @brief                设置64位属性变化时是否回调
    * @param allowFuncs     table
    * @return 无
    */
    void            SetCallBackUpdateAttr64(const CLuaObject& allowFuncs);
    /**
    * @brief                判断是否有属性回调
    * @param attrType       role_base_max_hp
    * @param beAttr32       是否32位属性
    * @return 无
    */
    bool            IsCallBackUpdateAttr(int32_t attrType, bool beAttr32 = true);
    //msg
    /**
    * @brief                发送聊天数据
    * @param params         内容
    * @return 无
    */
    void            SendChatMsg(const CLuaObject& params);
    /**
    * @brief                未实现
    */
    void            SendChatMsgTime(const std::string& startTime,const std::string& interval,uint16_t times,const CLuaObject& params) {};

    /**
    * @brief                获取排行榜信息
    * @return               返回排行榜信息
    * {{guid,value,desc,idx}，{guid,value,desc,idx}，{guid,value,desc,idx}...}
    */
    CLuaObject      GetCustListInfoByType(int type);


    /// Auction
    /**
    * @brief                设置拍卖信息
    * @param info          内容
    * @return 无
    */
    void            Auction_AddItemInfo(const CLuaObject& info);
     /**
    * @brief                拍卖行物品价格发生改变
    * @param guid          角色
    * @param orderID       订单
    * @param price         价格
    * @return              是否成功
    */
    bool            Auction_OfferPrice(const std::string& guid, const std::string& orderID, int price);
    /**
    * @brief               获得已经结束的拍卖物品数据
    * @param func          回调函数
    * @param few_time_ago  
    * @return              是否成功
    */
    void            Auction_GetFinishedItemTable(const std::string& func, uint32_t few_time_ago);

public:     // MapMgr export functions
    /**
    * @brief               创建地图
    * @param keyName       地图名字
    * @return              地图guid
    */
    std::string     MapMgr_CreateMap(const std::string &keyName);
     /**
    * @brief               删除地图
    * @param mapName       地图名字
    * @return              无
    */
    void            MapMgr_DestroyMap(const std::string& mapName);
     /**
    * @brief               寻找地图
    * @param mapName       地图名字
    * @return              地图guid
    */
    std::string     MapMgr_FindMap(const std::string& mapName);
    /**
    * @brief                创建镜像地图
    * @param sDgnMapName    地图名字
    * @param sPlayerGuid    玩家GUID
    * @param delayInit      是否延迟初始化
    * @param exitTime       结束时间
    * @param call_back      回调
    * @return               地图guid
    */
    std::string     MapMgr_CreateMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, bool delayInit, uint32_t exitTime, CLuaObject call_back);
    /**
    * @brief                销毁镜像地图
    * @param sDgnMapGuid    地图guid
    * @return               没找到返回1000
    */
    uint32_t	    MapMgr_DestroyMulDgnMap(const std::string& sDgnMapGuid);
     /**
    * @brief                绑定镜像地图到玩家
    * @param sDgnMapGuid    地图guid
    * @param sPlayerGuid    角色guid
    * @return               没找到返回1000
    */
    uint32_t	    MapMgr_BindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapGuid, const std::string& sPlayerGuid);
    /**
    * @brief                解除绑定镜像地图到玩家
    * @param sDgnMapGuid    地图guid
    * @param sPlayerGuid    角色guid
    * @return               没找到返回1000
    */
    uint32_t	    MapMgr_UnBindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid);
    /**
    * @brief                玩家进入镜像地图
    * @param sDgnMapName    地图名字
    * @param sPlayerGuid    角色guid
    * @param posX    
    * @param posY    
    * @param edlogInfo      日志
    * @return               没找到返回1000
    */
    uint32_t	    MapMgr_EnteryMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, uint16_t posX, uint16_t posY, const CLuaObject& edlogInfo);
    /**
    * @brief                玩家退出镜像地图
    * @param sDgnMapName    地图名字
    * @param sPlayerGuid    角色guid
    * @return               没找到返回1000
    */
    uint32_t	    MapMgr_ExitMulDgnMap(const std::string& sDgnMapGuid, const std::string& sPlayerGuid);
    /**
    * @brief                通过玩家找镜像地图
    * @param sDgnMapName    地图名字
    * @param sPlayerGuid    角色guid
    * @return               没找到返回1000
    */
    std::string	    MapMgr_GetMulDgnGuidByPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid);
public:     // Map export functions
    /**
    * @brief                进入地图
    * @param mapGuid        地图guid
    * @param roleGuid       角色guid
    * @return               
    */
    void            Map_RoleEnter(const std::string& mapGuid,const std::string& roleGuid);
    /**
    * @brief                离开地图
    * @param mapGuid        地图guid
    * @param roleGuid       角色guid
    * @return               
    */
    void            Map_RoleLeave(const std::string& mapGuid,const std::string& roleGuid);
    /**
    * @brief                设置地图块大小
    * @param mapGuid        地图guid
    * @param regionWidth    默认10
    * @param regionHeight   默认10
    * @return               
    */
    void            Map_SetRegionSize(const std::string& mapGuid, uint16_t regionWidth, uint16_t regionHeight);
    /**
    * @brief                召唤怪物
    * @param mapGuid        地图guid
    * @return               
    */
    void            Map_GenMapMonster(const std::string& mapGuid);
    /**
    * @brief                在范围内召唤怪物 
    * @param mapGuid        地图guid
    * @param Name           怪物名字
    * @param left        
    * @param top        
    * @param width        
    * @param height        
    * @param num            数量
    * @param dir            方向
    * @return               
    */
    void            Map_GenMapMonsterByName(const std::string& mapGuid, const std::string& Name, uint16_t left, uint16_t top,
                        uint16_t width, uint16_t height, uint16_t num, uint8_t dir);
    /**
    * @brief                在范围内召唤怪物 
    * @param id             怪物id
    * @return               
    */                
    void            Map_GenMapMonsterByID(const std::string& mapGuid, uint16_t id, uint16_t left, uint16_t top,
                        uint16_t width, uint16_t height, uint16_t num, uint8_t dir);
    /**
    * @brief                在地图内召唤npc 
    * @param mapGuid        地图guid
    * @param npcKeyName     npc名字
    * @param x             
    * @param y             
    * @param dir             
    * @return               
    */      
    std::string     Map_GenMapNPCByKeyName(const std::string& mapGuid, const std::string& npcKeyName, uint16_t x, uint16_t y, uint8_t dir);
     /**
    * @brief                删除npc 
    * @param npcGuid        npcguid           
    * @return               
    */      
    void            Map_DelMapNPCByGuid(const std::string& npcGuid);

    /**
    * @brief 发送消息到该地图
    * @param mapGuid 地图的guid
    * @param nMsgType 消息类型
    * @param sMsg 消息信息
    * @return 无
    */
    void            Map_SendSysMsg(const std::string& mapGuid, uint8_t nMsgType, const std::string& sMsg);

    /**
     * @brief 通过物品id生成地图场景物品
     * @param mapGuid 地图的guid
     * @param ownerGuid 拥有者guid   0:归于系统  1:归于系统，不需要等待场景物品保护时间 guid:玩家的guid
     * @param x 所生成物品x坐标
     * @param y 所生成物品y坐标
     * @param id 生成物品的id
     * @param amount 堆叠数量
     * @param bind 绑定类型          0:不绑定    1:绑定
     * @return 所生成场景物品的guid
    */
    std::string     Map_GenSceneItem(const std::string& mapGuid, const std::string& ownerGuid, uint16_t x, uint16_t y, uint16_t id, uint16_t amount, uint16_t bind);

    /**
     * @brief 通过物品KeyName生成地图场景物品
     * @param mapGuid 地图的guid
     * @param ownerGuid 拥有者guid   0:归于系统  1:归于系统，不需要等待场景物品保护时间 guid:玩家的guid
     * @param x 所生成物品x坐标
     * @param y 所生成物品y坐标
     * @param name 生成物品的KeyName
     * @param amount 堆叠数量
     * @param bind 绑定类型          0:不绑定    1:绑定
     * @return 所生成场景物品的guid
    */
    std::string     Map_GenSceneItemByName(const std::string& mapGuid, const std::string& ownerGuid, uint16_t x, uint16_t y, const std::string& name, uint16_t amount, uint16_t bind);

    /**
     * @brief 通过地图guid获取地图名字
     * @param mapGuid 地图的guid
     * @return 地图名字
    */
    std::string     Map_GetMapName(const std::string& mapGuid);

    /**
     * @brief 获取地图内改坐标的角色
     * @param mapGuid 地图的guid
     * @param posX x坐标
     * @param posY y坐标
     * @return 角色的guid
    */
    std::string     Map_GetRoleInPoint(const std::string& mapGuid, uint16_t posX, uint16_t posY);       //原Role*

    /**
     * @brief 坐标是否在安全区内
     * @param mapGuid 地图的guid
     * @param posx x坐标
     * @param posy y坐标
     * @return 是否在安全区内
    */
    bool            Map_IsSafeRegion(const std::string& mapGuid, uint16_t  posx, uint16_t posy);

    /**
     * @brief 该逻辑格是否是可利用的(是否不是阻挡点，且无玩家在内)
     * @param mapGuid 地图的guid
     * @param x x坐标
     * @param y y坐标
     * @return 该坐标是否可利用
    */
    bool            Map_IsGridAvail(const std::string& mapGuid, uint16_t x, uint16_t y);

    /**
     * @brief 获取地图内怪物数量
     * @param mapGuid 地图的guid
     * @return 怪物数量
    */
    int             Map_GetMonsterNum(const std::string& mapGuid);

    /**
     * @brief 获取地图id
     * @param mapGuid 地图的guid
     * @return 地图id
    */
    int             Map_GetID(const std::string& mapGuid);

    /**
     * @brief 是否是该类型的区域
     * @param mapGuid 地图的guid
     * @param posX 坐标x
     * @param posY 坐标y
     * @param type 区域类型  0:安全区域  1:摆摊区域  2:竞技区域(未实现)  3:复活区域  4:红名区域  5:出生区域  6:跳转区域(未实现)  7:矿区(未实现)  8:可穿透区域(未实现)
     * @return 地图id
    */
    bool            Map_IsThisMapGridType(const std::string& mapGuid, uint16_t posX, uint16_t posY, int type);

    /**
     * @brief 添加跳转点
     * @param from_guid 初始跳转地图guid
     * @param to_guid 跳转至地图guid
     * @param from_x 初始跳转地图x坐标
     * @param from_y 初始跳转地图y坐标
     * @param to_x 跳转至地图x坐标
     * @param to_y 跳转至地图y坐标
     * @param effect 跳转点特效
     * @return 无
    */
    void            Map_AddJumpPoint(const std::string& from_guid, const std::string& to_guid, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint32_t enterEffect, uint32_t leaveEffect);

    /**
     * @brief 删除跳转点
     * @param guid 初始跳转地图guid
     * @param x 初始跳转地图x坐标
     * @param y 初始跳转地图y坐标
     * @return 无
    */
    void            Map_DelJumpPoint(const std::string& guid, uint16_t x, uint16_t y);

    /**
     * @brief 获取地图中所有该类型的角色
     * @param mapGUID 地图guid
     * @param roleType 角色类型   0:所有角色  1:玩家  2:npc  3:怪物  4:宠物  5:玩家摆摊模型  6:玩家分身
     * @return 该类型的lua表  {guid1,guid2,guid3...}
    */
    CLuaObject      Map_GetAllRoleByType(const std::string &mapGUID, uint8_t roleType);

    /**
     * @brief 获取地图区域内所有空格子
     * @param mapguid 地图guid
     * @param x 中心点坐标x
     * @param y 中心点坐标y
     * @param rangeX 中心点到一边x的长度
     * @param rangeY 中心点到一边y的长度
     * @return 无
     * @LuaRet {{x1,y1},{x2,y2},{x3,y3}...}
    */
    void            Map_GetAllEmptyGrid(const std::string& mapguid, uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY); 

    /**
     * @brief 获取地图区域内所有空白格
     * @param mapguid 地图guid
     * @param x 中心点坐标x
     * @param y 中心点坐标y
     * @param rangeX 中心点到一边x的长度
     * @param rangeY 中心点到一边y的长度
     * @return 无
     * @LuaRet {{x1,y1},{x2,y2},{x3,y3}...}
    */
    void            Map_GetAllCanDropItemGrid(const std::string& mapguid, uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY);

    /**
     * @brief 删除改坐标的怪物尸体
     * @param mapguid 地图guid
     * @param x 坐标x
     * @param y 坐标y
     * @return 无
    */
    void            Map_DisappearMonsterCorpseInPoint(const std::string& mapguid,uint16_t x,uint16_t y);

    /**
     * @brief 获取地图内的BOSS信息
     * @param MapKey 地图名
     * @return 成功或者失败
     * @LuaRet {{地图名,怪物名,复活时间(0:怪物活着 time:怪物的复活时间 s)},{地图名,怪物名,复活时间}...}
    */
    bool            Map_GetBossInfo(const std::string&MapKey);

    /**
     * @brief 土城镜像最大数量
     * @param num 数量
     * @return 无
    */
    void            SetMaxImageCount(uint32_t num);
    //MapAoi& Map_GetMapAoi(std::string mapGuid);

public:             // RoleMgr export functions
    /**
     * @brief 获取玩家guid
     * @param name 玩家名字
     * @return 玩家guid
    */
    std::string     RoleMgr_GetPlayerGUID(const std::string &name);

    /**
     * @brief 获取角色是否存在
     * @param guid 玩家guid
     * @return 是否存在
    */
    bool            RoleMgr_IsRoleExist(const std::string &guid);

public:             // Role export functions
    /**
     * @brief 获取角色类型
     * @param guid 角色guid
     * @return 角色类型  0:无效的角色类型  1:玩家  2:npc  3:怪物  4:宠物  5:玩家摆摊模型  6:玩家分身
    */
    uint32_t        Role_GetType(const std::string &guid);

    /**
     * @brief 获取角色名字
     * @param guid 角色guid
     * @return 角色名字
    */
    std::string     Role_GetName(const std::string &guid);

    /**
     * @brief 设置角色名字(不支持玩家改名字)
     * @param guid 角色guid
     * @param name 角色名字
     * @return 无
    */
    void            Role_SetName(const std::string& guid, const string& name);

    /**
     * @brief 设置角色别名
     * @param guid 角色guid
     * @param name 角色别名
     * @return 无
    */
    void            Role_SetAlias(const std::string& guid, const string& name);

    /**
     * @brief 获取玩家当前地图guid
     * @param guid 角色guid
     * @return 当前地图的guid
    */
    std::string     Role_GetCurMapGUID(const std::string &guid);

    /**
     * @brief 获取角色属性
     * @param guid 角色guid
     * @param prop 属性key值
     * @return 角色当前属性值
    */
    int32_t         Role_GetProp(const std::string &guid, int prop);

    /**
     * @brief 添加角色属性
     * @param guid 角色guid
     * @param prop 属性key值
     * @param value 属性value值
     * @return 无
    */
    void            Role_AddProp(const std::string& guid, int32_t prop, int32_t value);

    /**
     * @brief 重置角色属性
     * @param guid 角色guid
     * @param prop 属性key值
     * @param value 属性value值
     * @return 无
    */
    void            Role_SetProp(const std::string &guid, int prop, int32_t value);

    /**
     * @brief 获取角色64位属性
     * @param guid 角色guid
     * @param prop 属性key值
     * @return 属性value值
    */
    std::string     Role_GetProp64(const std::string &guid, int prop);

    /**
     * @brief 增加角色64位属性值
     * @param guid 角色guid
     * @param prop 属性key值
     * @param delta 属性修改后的值
     * @param logInfo 日志打印值
     * @return 无
    */
    void            Role_ModProp64(const std::string &guid, int prop, double delta, const CLuaObject& logInfo);

    /**
     * @brief 通过字符串增加角色64位属性值
     * @param guid 角色guid
     * @param prop 属性key值
     * @param delta 属性修改后的值
     * @param logInfo 日志打印值
     * @return 无
    */
    void            Role_ModProp64ByStr(const std::string& guid, int prop, std::string delta, const CLuaObject& logInfo);

    /**
     * @brief 检测角色64位属性是否大于等于传入数量
     * @param guid 角色guid
     * @param prop 属性key值
     * @param needNum 属性修改后的值
     * @return 是否大于等于
    */
    bool            Role_CheckProp64Amount(const std::string &guid, int prop, const std::string &needNum);

    /**
     * @brief 获取角色x坐标
     * @param guid 角色guid
     * @return 角色x坐标
    */
    uint16_t        Role_GetPosX(const std::string &guid);

    /**
     * @brief 获取角色y坐标
     * @param guid 角色guid
     * @return 角色y坐标
    */
    uint16_t        Role_GetPosY(const std::string &guid);

    /**
     * @brief 设置角色坐标
     * @param guid 角色guid
     * @param x x坐标
     * @param y y坐标
     * @return 无
    */
    void            Role_SetPos(const std::string &guid, uint16_t x, uint16_t y);

    /**
     * @brief 获取角色方向
     * @param guid 角色guid
     * @return 角色当前方向
    */
    uint8_t         Role_GetDir(const std::string &guid);

    /**
     * @brief 设置角色方向
     * @param guid 角色guid
     * @param dir 角色方向
     * @return 无
    */
    void            Role_SetDir(const std::string &guid, uint8_t dir);

    /**
     * @brief 角色添加buff
     * @param guid 角色guid
     * @param buffID buffID
     * @param skillID 技能ID
     * @return 是否添加成功
    */
    bool            Role_AddBuff(const std::string &guid, uint16_t buffID, uint16_t skillID);

    /**
     * @brief 角色被施加buff通过释放者
     * @param guid 角色guid
     * @param buffID buffID
     * @param actorGUID 释放者GUID
     * @param skillID 技能ID
     * @param attrStr buff特殊属性 (属性;更新属性;万分比系数|;;|;;)
     * @param time 剩余时间 ms
     * @return 是否添加成功
    */
    bool            Role_AddBuffByRole(const std::string &guid, uint16_t buffID, const std::string &actorGUID, uint16_t skillID, const std::string& attrStr, uint32_t time = 0);

    /**
     * @brief 删除角色buff
     * @param guid 角色guid
     * @param buffID buffID
     * @return 是否删除成功
    */
    bool            Role_RemoveBuff(const std::string &guid, uint16_t buffID);

    /**
     * @brief 通过释放者GUID删除角色buff
     * @param guid 角色guid
     * @param buffID buffID
     * @param actorID 释放者guid
     * @return 是否删除成功
    */
    bool            Role_RemoveBuffWithActorID(const std::string &guid, uint16_t buffID, const std::string &actorID);

    /**
     * @brief buff是否存在
     * @param guid 角色guid
     * @param buffID buffID
     * @return 是否存在
    */
    bool            Role_BuffExist(const std::string &guid, uint16_t buffID);

    /**
     * @brief 通过buff组ID判断buff是否存在
     * @param guid 角色guid
     * @param buffID buffID
     * @param buffGroupID buff组ID
     * @return 是否存在
    */
    bool            Role_BuffExistByGroupID(const std::string& guid, uint16_t buffGroupID);

    /**
     * @brief 通过buff名判断buff是否存在
     * @param guid 角色guid
     * @param name buff名字
     * @return 是否存在
    */
    bool            Role_BuffExistByKeyName(const std::string& guid, const std::string&);

    /**
     * @brief 获取buff堆叠次数
     * @param guid 角色guid
     * @param buffID buffid
     * @return 堆叠次数
    */
    uint16_t        Role_GetBuffStack(const std::string& guid, uint16_t buffID);

    /**
     * @brief 获取buff剩余时间
     * @param guid 角色guid
     * @param buffID buffid
     * @return 剩余时间 -1:buff不存在 0:永久 >0:剩余时间 ms
    */
    std::string     Role_GetBuffLeftTime(const std::string& guid, uint16_t buffID);

    /**
     * @brief 获取buff列表
     * @param guid 角色guid
     * @return buff列表 {id1, id2, id3...}
    */
    CLuaObject      Role_GetBuffList(const std::string &guid);

    /**
     * @brief 追加buff堆叠次数
     * @param guid 角色guid
     * @param buffID buffID
     * @param diff 追加堆叠次数
     * @return 无
    */
    void            Role_UpdateBuffStack(const std::string& guid, uint16_t buffID, int16_t diff);

    /**
     * @brief 通过攻击者添加技能攻击
     * @param guid 角色guid
     * @param actorGUID 攻击者guid
     * @param skillID 技能ID
     * @param lossHP 损失血量
     * @param harmType 伤害类型
     * @return 无
    */
    void            Role_AttackedByRole(const std::string &guid, const std::string &actorGUID, uint16_t skillID, uint32_t lossHP, uint8_t harmType);

    /**
     * @brief 通过攻击者添加技能攻击
     * @param guid 角色guid
     * @param actorGUID 攻击者guid
     * @param actorName 攻击者名字
     * @param skillID 技能ID
     * @param lossHP 损失血量
     * @param harmType 伤害类型
     * @return 无
    */
    void            Role_AttackedByRole2(const std::string &guid, const std::string &actorGUID, const std::string &actorName,
                        uint16_t skillID, uint32_t lossHP, uint8_t harmType);

    /**
     * @brief 角色是否存活
     * @param guid 角色guid
     * @return 是否存活
    */
    bool            Role_IsAlive(const std::string &guid);

    /**
     * @brief 获取buff释放者guid
     * @param guid 角色guid
     * @param buffID buffid
     * @return 释放者guid
    */
    std::string     Role_GetBuffActorGuid(const std::string &guid, uint16_t buffID);

    /**
     * @brief 获取buff释放者名字
     * @param guid 角色guid
     * @param actorGuid 释放者guid
     * @param buffID buffID
     * @return 释放者名字
    */
    std::string     Role_GetBuffActorName(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief 获取buff释放者职业
     * @param guid 角色guid
     * @param actorGuid 释放者guid
     * @param buffID buffID
     * @return 释放者职业
    */
    uint8_t         Role_GetBuffActorJob(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief 获取buff释放者等级
     * @param guid 角色guid
     * @param actorGuid 释放者guid
     * @param buffID buffID
     * @return 释放者等级
    */
    uint32_t        Role_GetBuffActorLevel(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief 获取buff释放者技能ID
     * @param guid 角色guid
     * @param actorGuid 释放者guid
     * @param buffID buffID
     * @return 释放者技能ID
    */
    uint16_t        Role_GetBuffActorSkill(const std::string &guid, const std::string &actorGuid, uint16_t buffID);

    /**
     * @brief 增加角色血量
     * @param guid 角色guid
     * @param amount 增加数量
     * @param type 类型 0:普攻  1:暴击
     * @param notify 是否通知客户端
     * @return 无
    */
    void            Role_IncreaseHP(const std::string &guid, int32_t amount, uint8_t type, bool notify);

    /**
     * @brief 减少角色血量
     * @param guid 角色guid
     * @param amount 增加数量
     * @param type 类型 0:普攻  1:暴击
     * @param notify 是否通知客户端
     * @return 无
    */
    void            Role_DecreaseHP(const std::string &guid, int32_t amount, uint8_t type, bool notify);

    /**
     * @brief 改变角色外观
     * @param guid 角色guid
     * @param modelID 外观ID
     * @return 无
    */
    void            Role_ChangeAppearance(const std::string& guid, uint16_t modelID);

    /**
     * @brief 设置角色技能属性
     * @param guid 角色guid
     * @param skillID 技能ID
     * @param propType 技能属性类型 详见SKILL_PROP_TYPE
     * @param cfg 技能属性配置 详见技能属性配置
     * @return 无
    */
    void            Role_SetSkillProp(const std::string& guid, uint16_t skillID, uint16_t propType, const std::string& cfg);

    /**
     * @brief 获取角色技能属性
     * @param guid 角色guid
     * @param skillID 技能ID
     * @param propType 技能属性类型 详见SKILL_PROP_TYPE
     * @return 技能属性配置信息
    */
    bool            Role_GetSkillProp(const std::string& guid, uint16_t skillID, uint16_t propType);

    /**
     * @brief 角色跳转地图
     * @param guid 角色guid
     * @param mapGuid 地图guid
     * @param x 坐标x
     * @param y 坐标y
     * @return 是否跳转成功
    */
    bool            Role_JumpMapByGuid(const std::string& guid, const std::string& mapGuid, uint16_t x, uint16_t y);

    /**
     * @brief 角色随机坐标跳转地图
     * @param guid 角色guid
     * @param mapGuid 地图guid
     * @return 是否跳转成功
    */
    bool            Role_RandJumpMapByGuid(const std::string& guid, const std::string& mapGuid);

    /**
     * @brief 角色释放技能
     * @param guid 角色guid
     * @param skillID 技能ID
     * @param x 坐标x
     * @param y 坐标y
     * @param targetGUID 目标guid
     * @return 是否释放成功
    */
    bool            Role_ApplySkill(const std::string &guid, uint16_t skillID, uint16_t x, uint16_t y,
                                    const std::string &targetGUID);

    /**
     * @brief 角色获取主人guid
     * @param guid 角色guid
     * @return 主人guid
    */
    std::string     Role_GetMasterGUIDAsString(const std::string &guid);

    /**
     * @brief 设置骑马外观
     * @param guid 角色guid
     * @param value 外观id
     * @return 无
    */
    void Role_SetRideHorseModelid(const std::string& guid, int32_t value);

    /**
     * @brief 设置骑马开关
     * @param guid 角色guid
     * @param value 外观id
     * @return 无
    */
    void Role_SetRideHorseSwitch(const std::string& guid, bool value);

    /**
     * @brief 获取骑马外观
     * @param guid 角色guid
     * @return 外观id
    */
    int32_t Role_GetRideHorseModelid(const std::string& guid);

    /**
     * @brief 获取骑马开关
     * @param guid 角色guid
     * @return 开关状态
    */
    bool Role_GetRideHorseSwitch(const std::string& guid);
public:     // Player export functions
    /**
     * @brief 获取角色是否支持账号
     * @param guid 角色guid
     * @return 是否支持账号
    */
    bool            Player_IsSupport(const std::string& guid);
    /**
     * @brief 给客户端发送物品销毁协议 (无效接口)
     * @param guid 角色guid
     * @return 无
    */
    void            Player_SendItemDestroyAck(const std::string& guid);

    /**
     * @brief 给客户端发送复活表现
     * @param guid 角色guid
     * @param MapName 复活地图
     * @param hp 血量
     * @param mp 蓝量
     * @param x x坐标
     * @param y y坐标
     * @return 无
    */
    void            Player_SendPlayerReliveNtf(const std::string& guid, const std::string& MapName, int hp, int mp, int x, int y);

    /**
     * @brief 仅给此玩家发送血量蓝量表现信息(不设置血量蓝量)
     * @param guid 角色guid
     * @param hp 血量
     * @param mp 蓝量
     * @return 无
    */
    void            Player_SendPlayerShowNtf(const std::string& guid, int hp, int mp);

    /**
     * @brief 仅给此玩家发送AttrExtRef表现(不设置此属性)
     * @param guid 角色guid
     * @param attr 属性
     * @param delta value
     * @return 无
    */
    void            Player_SendRoleAttrExtRefNtf(const std::string &guid, uint16_t attr, int delta);

    /**
     * @brief 添加物品到玩家背包
     * @param guid 角色guid
     * @param tempid 物品模板id
     * @param logInfo 日志信息
     * @return 是否添加成功
    */
    bool            Player_AddPlayerItem(const std::string& guid, uint16_t tempid, const CLuaObject& logInfo);

    /**
     * @brief 添加玩家经验
     * @param guid 角色guid
     * @param exp 经验值
     * @param logInfo 日志信息
     * @return 无
    */
    void            Player_AddPlayerExperience(const std::string& guid, int64_t exp, const CLuaObject& logInfo);

    /**
     * @brief 添加玩家key为4的64位属性值(当前服务端定义为非绑金币)
     * @param guid 角色guid
     * @param goldid 增加值
     * @param logInfo 日志信息
     * @return 无
    */
    void            Player_AddPlayerGold(const std::string& guid, uint64_t goldid, const CLuaObject& logInfo);

    /**
     * @brief 执行客户端脚本表单
     * @param guid 角色guid
     * @param sScriptName 脚本表单名字
     * @param sContent 执行的表单内容
     * @param bCompress 表单内容是否压缩
     * @return 无
    */
    void            Player_RunClientScript(const std::string& guid, const std::string& sScriptName, const std::string& sContent, bool bCompress);
    /**
     * @brief 通知玩家成功移动到坐标值
     * @param guid 角色guid
     * @param nDstX 目标x坐标
     * @param nDstY 目标y坐标
     * @return 无
    */
    void            Player_NotifyPlayer_StartMove(const std::string& guid, uint16_t nDstX, uint16_t nDstY);

    /**
     * @brief 给玩家发送报错信息
     * @param guid 角色guid
     * @param type 错误类型
     * @param errMsg 错误打印
     * @return 无
    */
    void            Player_SendErrorAck(const std::string& guid, int32_t type, const char* errMsg);

    /**
     * @brief 给玩家发送对话框消息
     * @param guid 角色guid
     * @param msg 消息
     * @return 无
    */
    void            Player_SendPopDlgMsgNtf(const std::string &guid, const std::string &msg);
    void            Player_SendPlayerFamilyChangeNtf(const std::string &guid, const std::string &msg);

    /**
    * @brief 跳转到指定地图的随机点
    * @param guid 角色GUID
    * @param mapName 地图索引名
    * @return 无
    */
    void            Player_Jump(const std::string& guid, const std::string& mapName);

    /**
    * @brief 跳转到指定地图的特定点
    * @param guid 角色GUID
    * @param mapName 地图索引名，为空表示当前地图
    * @param posX 逻辑格坐标x
    * @param posY 逻辑格坐标y
    * @return 跳转是否成功
    */
    bool            Player_JumpMap(const std::string& guid, const std::string& mapName, uint16_t posX, uint16_t posY);

    /**
    * @brief 跳转到指定地图的随机点
    * @param guid 角色GUID
    * @param mapName 地图索引名
    * @param type 跳转类型
    * @return 无
    */
    void            Player_JumpWithType(const std::string& guid, const std::string& mapName, uint16_t type);

    /**
    * @brief 跳转到指定地图的特定点
    * @param guid 角色GUID
    * @param mapName 地图索引名
    * @param posX 逻辑格坐标x
    * @param posY 逻辑格坐标y
    * @param type 跳转类型
    * @return 跳转是否成功
    */
    bool            Player_JumpMapWithType(const std::string& guid, const std::string& mapName, uint16_t posX, uint16_t posY, uint16_t type);

    /**
    * @brief 通过神兽模板ID召唤神兽
    * @param guid 角色GUID
    * @param monsterID 神兽模板ID
    * @return 神兽GUID
    */
    std::string     Player_SummonMonsterByID(const std::string& guid, uint16_t monsterID);

    /**
    * @brief 通过神兽索引名召唤神兽
    * @param guid 角色GUID
    * @param monsterName 神兽索引名
    * @return 神兽GUID
    */
    std::string     Player_SummonMonsterByName(const std::string& guid, const std::string& monsterName);

    /**
    * @brief 销毁召唤出来的神兽
    * @param guid 角色GUID
    * @param sMonsterGUID 神兽GUID
    * @return 无
    */
    void            Player_DestroySummonMonster(const std::string& guid, const std::string& sMonsterGUID);

    /**
    * @brief 根据神兽模板ID获取神兽的GUID
    * @param guid 角色GUID
    * @param nTemplateID 神兽模板ID
    * @return 神兽GUID或空
    */
    std::string     Player_GetSummonMonster(const std::string& guid, uint16_t nTemplateID);

    /**
    * @brief 通过宠物模板ID召唤宠物
    * @param guid 角色GUID
    * @param monsterid 宠物模板ID
    * @return 宠物GUID
    */
    std::string     Player_PetMonsterByID(const std::string&guid,uint16_t monsterid);

    /**
    * @brief 通过宠物索引名召唤宠物
    * @param guid 角色GUID
    * @param monsterName 宠物索引名
    * @return 宠物GUID
    */
    std::string     Player_PetMonsterByName(const std::string& guid, const std::string& monsterName);

    /**
    * @brief 通过宠物模板ID召唤宠物并设置属性
    * @param guid 角色GUID
    * @param nTemplateID 宠物模板ID
    * @param luaObj 属性列表
    * @return 宠物GUID
    */
    std::string     Player_PetMonsterIDByAttrTable(const std::string& guid,uint16_t nTemplateID,const CLuaObject &luaObj);

    /**
    * @brief 通过宠物索引名召唤宠物并设置属性
    * @param guid 角色GUID
    * @param name 宠物索引名
    * @param luaObj 属性列表
    * @return 宠物GUID
    */
    std::string     Player_PetMonsterNameByAttrTable(const std::string& guid, const std::string& name, const CLuaObject& luaObj);

    /**
    * @brief 获取宠物列表
    * @param guid 角色GUID
    * @return 宠物GUID列表
    */
    CLuaObject      Player_GetPetList(const std::string& guid);

    /**
    * @brief 销毁宠物
    * @param guid 角色GUID
    * @param petguid 宠物GUID
    * @return 无
    */
    void            Player_DestroyPetMonster(const std::string& guid, const std::string& petguid);

    /**
    * @brief 销毁所有宠物
    * @param guid 角色GUID
    * @return 无
    */
    void            Player_DestroyAllPetMonster(const std::string& guid);

    /**
    * @brief 设置宠物AI的活动状态
    * @param guid 角色GUID
    * @param petguid 宠物GUID
    * @param status 活动状态
    * @return 无
    */
    void            Player_SetPetActivityStatus(const std::string& guid, const std::string& petguid, uint16_t status);

    /**
    * @brief 设置宠物是否可捡物
    * @param guid 角色GUID
    * @param petguid 宠物GUID
    * @param canPick 是否可捡物
    * @return 无
    */
    void            Player_SetPetPickItemStatus(const std::string& guid, const std::string& petguid, bool canPick);

    /**
    * @brief 进入商店
    * @param guid 角色GUID
    * @param nShopID 商店ID
    * @return 无
    */
    void            Player_EnterShop(const std::string& guid, uint16_t nShopID);

    /**
    * @brief 进入副本地图
    * @param guid 角色GUID
    * @param sMapKeyName 副本地图索引名
    * @param edlogInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_EnterDgnMap(const std::string& guid, const std::string& sMapKeyName, const CLuaObject& edlogInfo);

    /**
    * @brief 离开副本地图
    * @param guid 角色GUID
    * @return 0成功，其他失败
    */
    int             Player_ExitDgnMap(const std::string& guid);

    /**
    * @brief 判断玩家是否在副本地图内
    * @param guid 角色GUID
    * @return 是或否
    */
    bool            Player_IsInDgnMap(const std::string& guid);

    /**
    * @brief 获取背包空格数
    * @param guid 角色GUID
    * @return 背包空格数
    */
    uint16_t        Player_GetIdleBagCount(const std::string& guid);

    /**
    * @brief 获取背包第一空格索引
    * @param guid 角色GUID
    * @return 背包空格索引，0无效
    */
    uint16_t        Player_GetBagFirstFreeSite(const std::string& guid);

    /**
    * @brief 移动物品
    * @param guid 角色GUID
    * @param itemguid 物品GUID
    * @param site 背包目标位置索引
    * @return 成功或失败
    */
    bool            Player_ItemMove(const std::string& guid, const std::string& itemguid, uint16_t site);

    /**
    * @brief 添加单个物品
    * @param guid 角色GUID
    * @param tempid 物品模板ID
    * @param nBindRequire 是否绑定
    * @param logInfo 日志信息
    * @return 物品GUID
    */
    std::string     Player_AddSingleItem(const std::string& guid, uint16_t tempid, uint8_t nBindRequire, const CLuaObject& logInfo);

    /**
    * @brief 根据物品模板ID添加物品
    * @param guid 角色GUID
    * @param nTemplateID 物品模板ID
    * @param nNum 添加物品数量
    * @param nBindRequire 是否绑定
    * @param nSiteRange 物品范围
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_AddItem(const std::string& guid, uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, uint8_t nSiteRange, const CLuaObject& logInfo);

    /**
    * @brief 根据物品索引名添加物品
    * @param guid 角色GUID
    * @param sKeyName 物品索引名
    * @param nNum 添加物品数量
    * @param bBind 是否绑定
    * @param nJob 角色类型
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_AddItemByKeyName(const std::string& guid, const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, const CLuaObject& logInfo);

    /**
    * @brief 根据物品索引名添加物品到背包指定位置
    * @param guid 角色GUID
    * @param sKeyName 物品索引名
    * @param nNum 添加物品数量
    * @param bBind 是否绑定
    * @param nJob 角色类型
    * @param nSite 背包位置索引
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_AddItemByKeyNameToSite(const std::string& guid, const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, const CLuaObject& logInfo);

    /**
    * @brief 批量添加物品到背包
    * @param guid 角色GUID
    * @param luaObj 待添加物品列表
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_AddItems(const std::string& guid, const CLuaObject& luaObj, const CLuaObject& logInfo);

    /**
    * @brief 通过物品模板ID删除物品
    * @param guid 角色GUID
    * @param nTemplateID 物品模板ID
    * @param nNum 删除物品数量
    * @param bindRequire 是否绑定
    * @param nSiteRange 物品范围
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_RemoveItem(const std::string& guid, uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const CLuaObject& logInfo);

    /**
    * @brief 通过物品GUID删除物品
    * @param guid 角色GUID
    * @param itemGuid 物品GUID
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_RemoveItemByGuid(const std::string& guid, const std::string& itemGuid, const CLuaObject& logInfo);

    /**
    * @brief 通过物品GUID删除物品
    * @param playerGUID 角色GUID
    * @param itemGUID 物品GUID
    * @param num 删除物品数量
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_RemoveItemByGuid2(const std::string &playerGUID, const std::string &itemGUID,
                                             uint16_t num, const CLuaObject &logInfo);

    /**
    * @brief 根据物品索引名删除物品
    * @param guid 角色GUID
    * @param keyName 物品索引名
    * @param nNum 删除物品数量
    * @param bindRequire 是否绑定
    * @param nSiteRange 物品范围
    * @param logInfo 日志信息
    * @return 0成功，其他失败
    */
    int             Player_RemoveItemByKeyName(const std::string& guid, const std::string& keyName, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const CLuaObject& logInfo);

    /**
    * @brief 删除指定范围的所有物品
    * @param guid 角色GUID
    * @param type 物品范围类型
    * @return 0成功，其他失败
    */
    int             Player_RemoveAllItem(const std::string& guid, rolepack_opt_type type);

    /**
    * @brief 根据物品模板ID获取指定范围的物品数量
    * @param guid 角色GUID
    * @param templateID 物品模板ID
    * @param bindRequire 是否绑定
    * @param nSiteRange 物品范围
    * @return 物品数量
    */
    uint32_t        Player_GetItemNum(const std::string& guid, uint16_t templateID, uint8_t bindRequire, uint8_t nSiteRange);

    /**
    * @brief 根据物品索引名获取指定范围的物品数量
    * @param guid 角色GUID
    * @param keyName 物品索引名
    * @param bindRequire 是否绑定
    * @param nSiteRange 物品范围
    * @return 物品数量
    */
    uint32_t        Player_GetItemNumByKeyName(const std::string& guid, const std::string& keyName, uint8_t bindRequire, uint8_t nSiteRange);

    /**
    * @brief 获取指定物品数量
    * @param guid 角色GUID
    * @param itemguid 物品GUID
    * @return 物品数量
    */
    uint16_t        Player_GetItemAmount(const std::string& guid, const std::string& itemguid);

    /**
    * @brief 设置指定物品数量
    * @param guid 角色GUID
    * @param itemguid 物品GUID
    * @param num 物品数量
    * @param logInfo 日志信息
    * @return 成功或失败
    */
    bool            Player_SetItemAmount(const std::string& guid, const std::string& itemguid, uint32_t num, const CLuaObject& logInfo);

    /**
    * @brief 获取玩家所在团队成员数量
    * @param guid 角色GUID
    * @return 团队成员数量
    */
    uint16_t        Player_GetTeamMemNum(const std::string& guid);

    /**
    * @brief 获取玩家所在团队角色名列表
    * @param guid 角色GUID
    * @return 团队角色名列表，第一个参数表示是否是队长
    */
    CLuaObject      Player_GetTeamInfo(const std::string& guid);

    /**
    * @brief 获取玩家所在团队GUID
    * @param guid 角色GUID
    * @return 团队GUID
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
    * @brief 创建行会
    * @param guid 角色GUID
    * @param guildName 行会名
    * @return 0成功，其他失败
    */
    int             Player_CreateGuild(const std::string& guid, const std::string& guildName);

    /**
    * @brief 添加技能
    * @param guid 角色GUID
    * @param skillID 技能ID
    * @param active 是否激活
    * @return 0成功，其他失败
    */
    int             Player_AddSkill(const std::string& guid, uint16_t skillID, bool active);

    /**
    * @brief 删除技能
    * @param guid 角色GUID
    * @param skillID 技能ID
    * @param delAllInSameChain 是否删除同一技能链的所有技能
    * @return 无
    */
    void            Player_DeleteSkill(const std::string& guid, uint16_t skillID, bool delAllInSameChain = false);

    /**
    * @brief 判断技能是否存在
    * @param guid 角色GUID
    * @param skillID 技能ID
    * @param searchSkillChain 是否查找同一技能链中的技能
    * @return 是或否
    */
    bool            Player_SkillIsExist(const std::string& guid, uint16_t skillID, bool searchSkillChain = false);

    /**
    * @brief 获取玩家的技能ID列表
    * @param guid 角色GUID
    * @return 技能ID列表
    */
    CLuaObject      Player_GetSkillIDList(const std::string &guid);

    /**
    * @brief 通过技能链ID获取技能ID
    * @param guid 角色GUID
    * @param chainID 技能链ID
    * @return 技能ID
    */
    uint16_t        Player_GetSkillIDByChainID(const std::string &guid, uint32_t chainID);

    /**
    * @brief 获取仓库可用空间
    * @param guid 角色GUID
    * @return 仓库可用空间
    */
    uint16_t        Player_GetWarehouseFreeSize(const std::string& guid);

    /**
    * @brief 获取高级仓库可用空间
    * @param guid 角色GUID
    * @return 高级仓库可用空间
    */
    uint16_t        Player_GetAdvWarehouseFreeSize(const std::string& guid);

    /**
    * @brief 获取仓库第一个可用位置索引
    * @param guid 角色GUID
    * @return 位置索引
    */
    uint16_t        Player_GetWarehouseFirstFreeSite(const std::string& guid);

    /**
    * @brief 获取高级仓库第一个可用位置索引
    * @param guid 角色GUID
    * @return 位置索引
    */
    uint16_t        Player_GetAdvWarehouseFirstFreeSite(const std::string& guid);

    /**
    * @brief 获取GM权限等级
    * @param guid 角色GUID
    * @return 权限等级
    */
    uint16_t        Player_GetGmModLevel(const std::string& guid);

    /**
    * @brief 获取VIP特权列表
    * @param guid 角色GUID
    * @return 特权列表
    */
    CLuaObject      Player_GetVipExtePermissions(const std::string& guid);

    /**
    * @brief 是否有VIP特权
    * @param guid 角色GUID
    * @param permissions 特权
    * @return 是或否
    */
    bool            Player_HasVipExtePermissions(const std::string& guid, int32_t permissions);

    /**
    * @brief 发送客户端显示消息
    * @param type 发送范围
    * @param site 消息显示位置
    * @param foreground 消息前景颜色ID
    * @param background 消息背景颜色ID
    * @param msg 消息内容
    * @param guid 用于确定范围的GUID
    * @param count 消息滚动次数
    * @return 无
    */
    void            Player_SendMsgNtf(const uint8_t type, const uint8_t site, const uint8_t foreground,const uint8_t background,
                                      const std::string& msg,const std::string& guid="", const uint8_t count=1);

    /**
    * @brief 获取玩家在行会中的头衔
    * @param guid 角色GUID
    * @return 头衔ID
    */
    int             Player_GetGuildMemberTitle(const std::string &guid);

    /**
    * @brief 获取玩家在行会中的原头衔
    * @param guid 角色GUID
    * @return 原头衔ID
    */
    int             Player_GetGuildMemberOldTitle(const std::string &guid);

    /**
    * @brief 获取玩家在行会中的新头衔
    * @param guid 角色GUID
    * @return 新头衔ID
    */
    int             Player_GetGuildMemberNewTitle(const std::string &guid);

    /**
    * @brief 获取玩家所在行会GUID
    * @param playerGUID 角色GUID
    * @return 行会GUID
    */
    std::string     Player_GetGuildGUID(const std::string &playerGUID);

    /**
    * @brief 获取玩家所在行会名
    * @param guid 角色GUID
    * @return 行会名
    */
    std::string     Player_GetGuildName(const std::string& guid);

    /**
    * @brief 获取玩家对于行会的当前贡献度
    * @param playerGUID 角色GUID
    * @return 当前贡献度
    */
    uint32_t        Player_GetCurContrib(const std::string &playerGUID);

    /**
    * @brief 设置玩家对于行会的当前贡献度
    * @param playerGUID 角色GUID
    * @param contrib 当前贡献度
    * @return 无
    */
    void            Player_SetCurContrib(const std::string &playerGUID, uint32_t contrib);

    /**
    * @brief 获取玩家对于行会的累计贡献度
    * @param playerGUID 角色GUID
    * @return 累计贡献度
    */
    uint32_t        Player_GetTotalContrib(const std::string &playerGUID);

    /**
    * @brief 获取指定范围物品GUID列表
    * @param guid 角色GUID
    * @param type 物品范围
    * @return 通过LuaRet返回物品GUID列表
    */
    void            Player_GetRolePackInfo(const std::string& guid, const int type);

    /**
    * @brief 通过物品位置索引获取物品GUID
    * @param guid 角色GUID
    * @param site 物品位置索引
    * @return 物品GUID
    */
    std::string     Player_GetItemBySite(const std::string& guid, const int site); 
    
    /**
	* @brief 通过物品GUID获取物品位置
	* @param guid 角色GUID
	* @param itemguid 物品GUID
	* @return 物品site
	*/
    int     Player_GetItemSiteByGuid(const std::string& guid, const std::string& itemguid);

    /**
    * @brief 获取物品绑定类型
    * @param guid 角色GUID
    * @param itemguid 物品GUID
    * @return 物品绑定类型
    */
    int             Player_GetItemBindType(const std::string& guid, const std::string& itemguid);

    /**
    * @brief 设置物品绑定类型
    * @param guid 角色GUID
    * @param itemguid 物品GUID
    * @param type 物品绑定类型
    * @return 无
    */
    void            Player_SetItemBindType(const std::string& guid, const std::string& itemguid, int type);

    /**
    * @brief 设置自动捡物半径
    * @param guid 角色GUID
    * @param radius 自动捡物半径
    * @return 成功或失败
    */
    bool            Player_SetAutoPickItemRadius(const std::string &guid, uint8_t radius);

    /**
    * @brief 设置自动捡物相对坐标点
    * @param guid 角色GUID
    * @param relpos 捡物相对坐标点集
    * @return 成功或失败
    */
    bool            Player_SetAutoPickItemRelativePositions(const std::string &guid, const CLuaObject &relpos);

    /**
    * @brief 设置自动捡物的时间间隔，间隔时间内不能再次捡物
    * @param guid 角色GUID
    * @param interval 自动捡物时间间隔
    * @return 成功或失败
    */
    bool            Player_SetAutoPickItemInterval(const std::string &guid, uint16_t interval);

    /**
    * @brief 设置物品配置表
    * @param guid 角色GUID
    * @param itemguid 物品GUID
    * @param tab 物品配置表
    * @return 成功或失败
    */
    bool            Player_SetItemCfg(const std::string& guid, const std::string& itemguid, const CLuaObject& tab);

    /**
    * @brief 玩家改名
    * @param guid 角色GUID
    * @param name 新角色名
    * @return 成功或失败
    */
    bool            Player_SetName(const std::string& guid, const std::string& name);

    /**
    * @brief 添加称号
    * @param guid 角色GUID
    * @param titleName 称号
    * @return 成功或失败
    */
    bool            Player_AddTitle(const std::string& guid, const std::string& titleName);

    /**
    * @brief 删除称号
    * @param guid 角色GUID
    * @param titleName 称号
    * @return 成功或失败
    */
    bool            Player_DelTitle(const std::string& guid, const std::string& titleName);

    /**
    * @brief 判断是否有某个称号
    * @param guid 角色GUID
    * @param titleName 称号
    * @return 是或否
    */
    bool            Player_HasTitle(const std::string& guid, const std::string& titleName);

    /**
    * @brief 获取称号索引名
    * @param titleID 称号模板ID
    * @return 称号索引名
    */
    std::string     Player_TitleIDToName(uint32_t titleID);

    /**
    * @brief 获取称号模板ID
    * @param name 称号索引名
    * @return 称号模板ID
    */
    uint32_t        Player_TitleNameToID(const std::string& name);

    /**
    * @brief 通过礼包码领取礼包
    * @param guid 角色GUID
    * @param type 礼包码类型
    * @param code 礼包码
    * @return 无
    */
    void            Player_RedemptionActivationCode(const std::string& guid, uint16_t type, const std::string& code);

    /**
    * @brief 增加技能熟练度
    * @param guid 角色GUID
    * @param skillID 技能ID
    * @param value 增加的技能熟练度数值
    * @return 成功或失败
    */
    bool            Player_AddProficiencyValue(const std::string& guid, uint32_t skillID, uint32_t value);

    /**
    * @brief 更改技能等级
    * @param guid 角色GUID
    * @param skillID 技能ID
    * @return 成功或失败
    */
    bool            Player_SetSkillLevel(const std::string& guid, uint32_t skillID);
    /**
    * @brief 是否被禁言
    * @param guid 角色GUID
    * @return 是或否
    */
    bool            Player_IsProhibitChat(const std::string& guid);

    /**
    * @brief 获取属性列表
    * @param guid 角色GUID
    * @param type 属性类型
    * @param min 属性ID最小值
    * @param max 属性ID最大值
    * @return 属性ID、值列表
    */
    CLuaObject      Player_GetListProp(const std::string& guid, uint16_t type, uint16_t min, uint16_t max);

    /**
    * @brief 获取物品GUID列表
    * @param guid 角色GUID
    * @param min 物品位置索引最小值
    * @param max 物品位置索引最大值
    * @return 物品位置索引、GUID列表
    */
    CLuaObject      Player_ItemGuidList(const std::string& guid, uint16_t min, uint16_t max);

    /**
    * @brief 是否具备GM权限
    * @param guid 角色GUID
    * @return GM权限等级
    */
    uint16_t        Player_IsLuaGM(const std::string& guid);

    /**
    * @brief 投递排行榜信息
    * @param guid    玩家guid
    * @param type    排行榜类型
    * @param value   类型值
    * @param desc    描述
    * @return  是否插入成功
    */
    bool            Player_AddCustListInfo(const std::string& guid, int type, const std::string& value, const std::string& desc);

    /**
    * @brief 设置玩家性别
    * @param guid    玩家guid
    * @param gender  设置玩家性别 1：男性 2：女性
    * @return  是否设置成功
    */
    bool            Player_SetGender(const std::string& guid, int gender);

    /**
    * @brief 插入角色辅助信息
    * @param guid    角色guid
    * @param info    辅助信息内容(最大512字节)
    * @return  无
    */
    void               Role_InsertInfo(const std::string& guid, const std::string& info);

    /**
    * @brief 更新角色辅助信息
    * @param guid    角色guid
    * @param info    辅助信息内容(最大512字节)
    * @return  无
    */
    void               Role_UpdateInfo(const std::string& guid, const std::string& info);

    /**
    * @brief 清空角色辅助信息
    * @param guid    角色guid
    * @return  无
    */
    void               Role_ClearInfo(const std::string& guid );

    /**
    * @brief 删除角色辅助信息中的子串
    * @param guid    角色guid
    * @param info    待删除的字串信息
    * @return  无
    */
    void               Role_DelInfo(const std::string& guid, const std::string& info);

    /**
    * @brief 请求获取角色辅助信息
    * @param guid    角色guid
    * @return  无
    */
    void               Role_GetInfoReq(const std::string& guid );

    /**
    * @brief 获取角色辅助信息
    * @param guid    角色guid
    * @return  辅助信息内容
    */
    const std::string  Role_GetInfoAck(const std::string& guid );

    /**
    * @brief 设置角色动态属性
    * @param guid    角色guid
    * @param index   属性集的下标索引
    * @param attr    属性id
    * @param value   属性值
    * @return  无
    */
    void                Role_SetDynAttr(const std::string& guid, uint16_t index, uint16_t attr, int32_t value);

    /**
    * @brief 获取角色动态属性
    * @param guid    角色guid
    * @param index   属性集的下标索引
    * @return  lua对象,格式如下
    * {"index"= (uint16_t)下标索引,"attr"=(uint16_t)属性id,"value"=(int32_t)属性值)}
    */
    CLuaObject          Role_GetDynAttr(const std::string& guid, uint16_t index);

public:     // NPC export functions
    /**
    * @brief 与npc聊天结果(未使用)
    * @param guid     npc的guid
    * @param ack      数据内容
    * @return   处理结果,暂为0
    */
    uint16_t        Npc_NpcTalkAck(const std::string& guid, const std::string& ack);

    /**
    * @brief 获取npc配置的模板id
    * @param guid     npc的guid
    * @return   模板id
    */
    int             Npc_GetTemplateID(const std::string& guid);

    /**
    * @brief 获取npc索引名
    * @param guid     npc的guid
    * @return   npc索引名
    */
    std::string     NPC_GetKeyName(const string& guid);
public:     // Monster export functions
    /**
    * @brief 吸怪
    * @param guid   怪物的guid
    * @param x      目标x
    * @param y      目标y
    * @return       无
    */
    void Monster_BeSuckedAway(const std::string& guid, uint16_t x, uint16_t y);
    /**
    * @brief 设置怪物的昵称
    * @param guid         怪物的guid
    * @param sMasterName  怪物昵称
    * @return       无
    */
    void            Monster_SetMasterName(const std::string& guid, const std::string& sMasterName);

    /**
    * @brief 获取怪物的模板id
    * @param guid         怪物的guid
    * @return       怪物模板id
    */
    int             Monster_GetTemplateID(const std::string& guid);

    /**
    * @brief 获取怪物的模板id
    * @param KeyName  怪物的索引名
    * @return         怪物模板id
    */
    int             Monster_GetTemplateIDByName(const std::string KeyName);

    /**
    * @brief 获取怪物所属主人的guid
    * @param guid   怪物的guid
    * @return       怪物主人的guid
    */
    std::string     Monster_GetMasterGUIDAsString(const std::string& guid);

    /**
    * @brief 获取怪物被击杀后专属的角色guid
    * @param guid         怪物的guid
    * @return       专属的角色guid
    */
    std::string     Monster_GetBelongPlayerIDAsString(const std::string& guid);

    /**
    * @brief 设置怪物的召唤类型
    * @param guid         怪物的guid
    * @param type         类型
    * @return       无
    */
    void            Monster_SetSummonMonsterType(const std::string &guid, uint8_t type);

    /**
    * @brief 获取怪物所有的仇恨信息
    * @param guid         怪物的guid
    * @param type         类型
    * @return       lua对象,格式如下
    * {{ (uint64)角色guid1, (float)仇恨值1, (uint64)时间戳1},{ (uint64)角色guid2, (float)仇恨值2, (uint64)时间戳2}, ...}
    */
    CLuaObject            Monster_GetHateValueMap(const std::string& guid);

    /**
    * @brief 获取怪物当前锁定的目标角色
    * @param guid         怪物的guid
    * @return       目标角色guid
    */
    const std::string     Monster_GetCurAttackTar(const std::string& guid);

    /**
    * @brief 初始化镖车类怪物
    * @param guid         镖车类怪物的guid
    * @param targuid      所属主人的guid
    * @param x            目的地x坐标
    * @param y            目的地y坐标
    * @param range        跟随范围
    * @param finalRange   终点标范围
    * @param posRange     坐标范围
    * @param mPos         路径坐标集合
    * @param func         到达后的回调函数
    * @return       目标角色guid
    */
    void                  Monster_InitBiaoChe(const std::string &guid,const std::string & targuid,uint16_t x,uint16_t y,uint16_t range, uint16_t finalRange,
        uint8_t posRange,  const CLuaObject& posTable, const std::string&func);

    /**
    * @brief 注册怪物特殊行为
    * @param guid         怪物的guid
    * @param info         行为数据表,格式{{(monster_behaviour_trigger)行为id1,(string)回调参数1,(string)回调函数1},...}
    * @return       无
    */
    void                  Monster_RegisterBehavior(const std::string& guid, const CLuaObject& info );

    /**
    * @brief 注册怪物属性表
    * @param guid         怪物的guid
    * @param info         属性数据表,格式{(MonsterAI_Attribute)属性id1,...}
    * @return       无
    */
    void                  Monster_RegisterAttribute(const std::string& guid, const CLuaObject& info);

    /**
    * @brief 注销怪物特殊行为
    * @param guid         怪物的guid
    * @param behaviorID   行为id
    * @return       无
    */
    void                  Monster_RemoveMonsterBehavior(const std::string& guid, uint16_t behaviorID);

    /**
    * @brief 移除怪物,使怪物死亡
    * @param guid         怪物的guid
    * @param appearBody   是否有尸体
    * @return       无
    */
    void                  Monster_RemoveMonster(const std::string& guid, bool appearBody); // 没有掉落 没有经验 没有重生 仅移除怪物
    
    /**
    * @brief 设置怪物名显示的颜色
    * @param guid         怪物的guid
    * @param nameColor    颜色信息
    * @return       无
    */
    void                  Monster_SetNameColor(const std::string& guid, const std::string& nameColor);

    //触发反馈
    /**
    * @brief 设置怪物的当前技能组
    * @param guid         怪物的guid
    * @param skillGroup   技能组id
    * @return       无
    */
    void            Monster_SwapSkillGroup(const std::string& guid, uint16_t skillGroup);

    /**
    * @brief 标识怪物使用特殊技能
    * @param guid         怪物的guid
    * @param Skillid      技能id
    * @return       无
    */
    void            Monster_UseSpecialSkill(const std::string& guid, uint32_t Skillid);

    /**
    * @brief 触发怪物逃跑
    * @param guid         怪物的guid
    * @param dis          可逃跑的坐标轴半径
    * @return       无
    */
    void            Monster_Escape(const std::string& guid, int dis);

    /**
    * @brief 给怪物添加可释放的技能
    * @param guid         怪物的guid
    * @param skillinfo    待添加的技能信息,格式{(uint32_t)技能id,(uint32_t)技能权重}
    * @return       无
    */
    void            Monster_AddSkill(const std::string& guid, const CLuaObject& skillinfo);

    /**
    * @brief 移除怪物可释放的技能
    * @param guid         怪物的guid
    * @param SkillID      待移除的技能id
    * @return       无
    */
    void            Monster_RemoveSkill(const std::string& guid, uint32_t SkillID);

    /**
    * @brief 获取怪物可释放的技能组信息
    * @param guid         怪物的guid
    * @return       LuaRet,格式{{(int)技能id1,(int)技能权重1},{(int)技能id2,(int)技能权重2},...}
    */
    void            Monster_GetCurSkillGroup(const std::string& guid);

    /**
    * @brief 处理怪物掉落
    * @param guid         怪物的guid
    * @param killerGuid   击杀角色的guid
    * @return       无
    */
    void            Monster_DropItem(const std::string& guid,const std::string&killerGuid);

    /**
    * @brief 刷新镖车寻路
    * @param guid         怪物的guid
    * @return       是否刷新成功
    */
    bool            Monster_UpdateBiaocheAI(const std::string& guid);

    /**
    * @brief 设置道士宠物跟随主人攻击
    * @param guid   宠物的guid
    * @param state  设置状态 0：不跟随 1：跟随
    * @return 是否设置成功
    */
    bool            Monster_SetPetFollowMasterAttackState(const std::string& guid, uint8_t state);

public:             // Guild export functions
    /**
    * @brief 获取工会guid
    * @param guildName    工会名
    * @return       工会guid
    */
    std::string     Guild_GetGUIDByName(const std::string &guildName);

    /**
    * @brief 获取工会会长guid
    * @param guildName    工会guid
    * @return       会长guid
    */
    std::string     Guild_GetLeaderName(const std::string &guildGUID);

    /**
    * @brief 添加两工会互为盟友
    * @param myGuildName      工会1名
    * @param allyGuildName    工会2名
    * @return           添加结果
    */
    int             Guild_AddAlly(const std::string &myGuildName, const std::string &allyGuildName);

    /**
    * @brief 两工会互相解除盟友
    * @param myGuildName      工会1名
    * @param allyGuildName    工会2名
    * @return           解除结果
    */
    int             Guild_DelAlly(const std::string &myGuildName, const std::string &allyGuildName);

    /**
    * @brief 两工会是否为盟友
    * @param myGuildName      工会1名
    * @param allyGuildName    工会2名
    * @return           是否盟友
    */
    bool            Guild_IsAlly(const std::string &myGuildName, const std::string &allyGuildName);

    /**
    * @brief 添加两工会互为敌对
    * @param myGuildName      工会1名
    * @param allyGuildName    工会2名
    * @return           添加结果
    */
    int             Guild_AddEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    /**
    * @brief 两工会互相解除敌对
    * @param myGuildName      工会1名
    * @param allyGuildName    工会2名
    * @return           解除结果
    */
    int             Guild_DelEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    /**
    * @brief 两工会是否为敌对
    * @param myGuildName      工会1名
    * @param allyGuildName    工会2名
    * @return           是否敌对
    */
    bool            Guild_IsEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    /**
    * @brief            获取所有工会名
    * @return           lua对象,格式{(string)工会名1,(string)工会名2,...}
    */
    CLuaObject      Guild_GetGuildNameList();

    /**
    * @brief 获取指定工会的成员guid列表
    * @param GuildGUID        工会guid
    * @return           lua对象,格式{(string)角色guid1,(string)角色guid2,...}
    */
    CLuaObject      Guild_GetGuildMember(const std::string& GuildGUID);

    /**
    * @brief 让玩家直接加入工会
    * @param playerGuid       玩家guid
    * @param guildGuid        工会guid
    * @return           加入结果
    */
    int32_t         Guild_JoinGuild(const std::string& playerGuid, const std::string& guildGuid);

    /**
    * @brief 设置工会等级
    * @param guildGuid        工会guid
    * @param level            工会等级
    * @return           加入结果
    */
    int32_t         Guild_SetGuildLevel(const std::string& guildGuid, uint16_t level);

    /**
    * @brief 开启工会战
    * @param guildGuid        工会1guid
    * @param enemyGuildGuid   工会2guid
    * @param durTime          持续时间
    * @return           无
    */
    void            Guild_GuildWar(const std::string& guildGuid, const std::string& enemyGuildGuid, uint32_t durTime);
    
    /**
    * @brief 设置工会自动加入限制等级
    * @param GuildGUID        工会guid
    * @param level            角色所需等级
    * @return           设置结果
    */
    int32_t         Guild_SetGuildAutoJoinLevel(const std::string& GuildGUID, uint32_t level);

    /**
    * @brief 修改行会公告
    * @param guildGUID 工会GUID
    * @param notice 公告
    * @return 结果
    */
    int32_t         Guild_EditGuildNotice(const std::string& guildGuid, const std::string& notice);

    /**
    * @brief 修改行会成员title(设置非会长时,memberGUID不能为会长guid，转让会长直接设置其他成员为会长)
    * @param memberGUID 成员GUID
    * @param title title
    * @return 结果
    */
    int32_t         Guild_ChangeGuildMemberTitle(const std::string& memberGUID, uint8_t title);

    /**
    * @brief 踢人(可T会长以外的人)
    * @param memberGUID 成员GUID
    * @return 结果
    */
    int32_t         Guild_KickGuildMember(const std::string& memberGUID);

    /**
    * @brief 解散行会
    * @param guildGUID 工会GUID
    * @return 结果
    */
    int32_t         Guild_DestroyGuild(const std::string& guildGuid);
public:             // Item export functions
    /**
    * @brief 更新物品耐久度
    * @param guid             物品guid
    * @param value            更新值
    * @return           无
    */
    void            Item_UpdateDurability(const std::string& guid, int32_t value);

    /**
    * @brief 获取物品耐久度
    * @param guid             物品guid
    * @return           物品耐久度
    */
    int32_t         Item_Geturability(const std::string& guid);

    /**
    * @brief 设置物品动态属性
    * @param guid    物品guid
    * @param index   属性集的下标索引
    * @param attr    属性id
    * @param value   属性值
    * @return  无
    */
    void            Item_SetDynAttr(const std::string &guid, uint16_t index, uint16_t attr, int32_t value);

    /**
    * @brief 获取物品动态属性
    * @param guid    物品guid
    * @param index   属性集的下标索引
    * @return  lua对象,格式如下
    * {"index"= (uint16_t)下标索引,"attr"=(uint16_t)属性id,"value"=(int32_t)属性值)}
    */
    CLuaObject      Item_GetDynAttr(const std::string &guid, uint16_t index);

    /**
    * @brief 获取物品模板id
    * @param guid    物品guid
    * @return  物品模板id
    */
    int             Item_GetTempId(const std::string& guid);

    /**
    * @brief 物品信息json格式编码
    * @param guid    物品guid
    * @return  物品json格式信息
    */
    std::string     Item_ItemInfoEncodeToJson(const std::string& guid);

    /**
    * @brief 物品信息json格式解码
    * @param info     物品json格式信息
    * @param belong   物品所属角色guid
    * @return   物品guid
    */
    std::string     Item_DecodeJsonToAddItem(const std::string& info,const std::string &belong = "");

    /**
    * @brief 设置物品子类型
    * @param guid     物品guid
    * @param belong   物品所属角色guid
    * @param subtype  子类型id
    * @return   设置结果
    */
    bool            Item_SetSubType(const std::string& guid, const std::string& belong, uint16_t subtype);

    /**
    * @brief 设置物品名
    * @param playerguid       物品所属角色guid
    * @param guid             物品guid
    * @param Name             物品名
    * @return           设置结果
    */
    bool            Item_SetName(const std::string& playerguid, const std::string& guid, const std::string& Name);

    /**
    * @brief 获取物品绑定状态
    * @param guid             物品guid
    * @return           是否绑定
    */
    bool            Item_IsBind(const std::string &itemGUID);


public:             // log
    /**
    * @brief 活动日志
    * @param activeName       活动名称
    * @param rewardName       奖励名称
    * @param roleGuid         角色guid
    * @param itemInfo         奖励物品信息
    * @param goldInfo         奖励金币信息
    * @return           无
    */
    void            Log_ActivityData(const string& activeName, const string& rewardName, const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

    /**
    * @brief 奖励日志
    * @param rewardName       奖励名称
    * @param roleGuid         角色guid
    * @param itemInfo         奖励物品信息
    * @param goldInfo         奖励金币信息
    * @return           无
    */
    void            Log_RewardData(const string& rewardName, const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

    /**
    * @brief 礼包日志
    * @param giftName         礼包名称
    * @param roleGuid         角色guid
    * @param itemInfo         礼包物品信息
    * @param goldInfo         礼包金币信息
    * @return           无
    */
    void            Log_GiftPackData(const string& giftName, const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

    /**
    * @brief 回收日志
    * @param roleGuid         角色guid
    * @param itemInfo         回收物品信息
    * @param goldInfo         奖励金币信息
    * @return           无
    */
    void            Log_RecoveryData(const string& roleGuid, const CLuaObject& itemInfo, const CLuaObject& goldInfo);

public:             // shabak export functions
    /**
    * @brief 开始攻沙战
    * @param guildNames       参加攻沙战的所有工会名的集合,格式{(string)工会名1,(string)工会名2,...}
    * @param startTime        开始时间
    * @param duration         持续时间
    * @return           是否处理成功
    */
    bool            StartCastleWar(const CLuaObject &guildNames, const std::string &startTime, uint32_t duration);

    /**
    * @brief            停止攻沙战
    * @return           是否处理成功
    */
    bool            StopCastleWar();

    /**
    * @brief            获取所有参与攻沙的工会名
    * @return           lua对象,格式{(string)工会名1,(string)工会名2,...}
    */
    CLuaObject      GetCastleAttackFamily();

    /**
    * @brief            获取沙巴克归属的工会名
    * @return           工会名
    */
    std::string     GetCastleOwnFamily();

    /**
    * @brief 重置沙巴克归属的工会
    * @param guildName        新工会名
    * @return           无
    */
    void            SetCastleOwnFamily(std::string guildName);

    /**
    * @brief            查询攻沙战开始时间
    * @return           开始时间
    */
    std::string     QueryCastleStart();

    /**
    * @brief            查询攻沙战是否已经开始
    * @return           是否开始
    */
    bool            IsCastleWarStart();

    /**
    * @brief 生成攻沙怪物
    * @param type             怪物类型
    * @return           无
    */
    void            GenCastleMonster(uint32_t type);    // type: 1、正门怪物，2、皇宫大门怪，3，侧门怪

public:             // wanted list export functions
    /**
    * @brief            获取悬赏名单信息
    * @return           lua对象,格式
    * {{"guid"=(string)悬赏者guid1,"name"=(string)悬赏者名1,"online"=(bool)是否在线,"bounty"=(uint32_t)赏金,"desc"={{(string)描述,(uint64_t)发起悬赏时间},...}, "time"=(string)发起悬赏时间}, ...}
    */
    CLuaObject      GetWantedList();
    
    /**
    * @brief 发布悬赏名单信息
    * @param wantedByGUID     被悬赏者guid
    * @param wantedName       发布悬赏的玩家名
    * @param bounty           赏金
    * @param desc             悬赏描述信息
    * @return           无
    */
    void            PostBounty(const std::string &wantedByGUID, const std::string &wantedName, uint32_t bounty, const std::string &desc);

    /**
    * @brief 获取删档奖励信息
    * @param roleGuid         角色guid
    * @return           lua对象,格式{"RoleGuid"=(string)角色guid,"BeExist"=(bool)是否存在奖励, "BeUsed"=(bool)是否已经领取, "Money"=(string)奖励数量}
    */
    CLuaObject      GetRebateMoneyInfo(const std::string& roleGuid);

    /**
    * @brief 领取删档奖励
    * @param roleGuid         角色guid
    * @return           无
    */
    void            GetRebateMoney(const std::string& roleGuid);
    /**
    * @brief 正式服不能开启！！！！！！！！！
    * @brief 设置是否打印  和打印属性变化记录   设置1 开启  设置0 关闭   打印 1010  
    * @param roleGuid         角色guid
    * @param prop             属性id
    * @return           无
    */
    int32_t         Role_GetProp_Info(const std::string& guid, int prop);

    /**
    * @brief 按类型获取角色周围角色
    * @param guid             角色guid
    * @param type             角色类型   0:所有角色  1:玩家  2:npc  3:怪物  4:宠物  5:玩家摆摊模型  6:玩家分身
    * @return           角色列表 {guid1,guid2,guid3...}
    */
    CLuaObject       Role_GetRegionRoleByType(const std::string& guid, uint8_t type);

    /*
    @brief                访问链接
    */
    void            PostHttpCurl(const std::string& cmd, const std::string& custom, const std::string& callBackFunc);
    /**
   * @brief 设置移动延迟误差
   * @param num              万分比 
   * @return           无
   */
    void            SetMoveMistake(uint32_t num);
    /**
    * @brief            执行客户端脚本表单
     * @param guid 角色guid
     * @param sScriptName 脚本表单名字
     * @param sContent 执行的表单内容
     * @param bCompress 表单内容是否压缩
     * @param type 0玩家附近的人 1 地图  2 整个服务器
     * @return 无
    */
    void            Player_RunClientScript_plus(const std::string& guid, const std::string& sScriptName, const std::string& sContent, bool bCompress, uint16_t type);

    std::string     _LuaSerialize(const CLuaObject& luaObj, std::string& str);
    /**
        * @brief  c++ 序列化
        * @return string
    */
    std::string     LuaSerialize(const CLuaObject& luaObj);

    /**
   * @brief 是否win32环境
   * @return           是否
   */
    bool            IsWin32();

    /**
    * @brief 获取当前微秒
    * @return     
    */
    std::string     Getmicrosecond();

    /**
    * @brief 大数计算
    * @param num1 数据1
    * @param num2 数据2
    * @param type 1加法 2减法 3 乘法 4 除法
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
