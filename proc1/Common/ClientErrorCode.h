#pragma once

enum EErrCode
{
    ERR_OK = 0,		//成功		
    ERR_SYSTEM,		//系统错误
    ERR_UNKNOW,		//未知错误
    ERR_ALREADYONLINE,	//账号已在线
    ERR_INLOADUSERDATA, //账号信息加载中
    ERR_DATABASEERR,    //数据库操作失败
    ERR_NOUSERDATA,     //无账号数据
    ERR_NOROLEDATA,     //无角色数据
    ERR_ROLEDELLIMIT,   //每日只能删除一个角色
    ERR_CREATEMAXROLE,  //达到创建角色最大数
    ERR_USESTATEWRONG,  //角色状态错误
    ERR_ROLENAMEEXIST,  //角色名已存在
    ERR_LOGINTIMEOUT,   //账号登陆超时
    ERR_ROLEINCREATE,   //角色创建中
    ERR_ROLEGENDER,     //非法的角色性别
    ERR_ROLEJOB,        //非法的角色职业
    ERR_GETROLEDATA,    //获取角色数据失败
    ERR_NOROLEINLIST,   //角色列表中无此角色
    ERR_ROLEDESTROY,    //角色已删除
    ERR_ALREADYINGAME,  //角色已经在游戏中
    ERR_GSNOTEXIST,     //Game Server不存在
    ERR_SELECTTIMEOUT,  //选角色超时
    ERR_CREATETIMEOUT,  //创建角色超时
    ERR_ENTERGSTIMEOUT, //进入Game Server超时
    ERR_ROLEACTIONFAIL, //角色执行错误
    ERR_UNKNOWEXITTYPE, //未知的下线类型
    ERR_NOMAPDATA,      //找不到地图信息
    ERR_MOVEFAIL,       //移动失败
    ERR_MOVETOOFAST,    //移动速度太快
    ERR_MOVESTIFF,      //移动时处于硬直状态
    ERR_TURNFAIL,       //转向失败
    ERR_TURNSTIFF,      //转向时处于硬直状态
    ERR_NOMOVABLEPOINT, //没有可移动点
    ERR_REPEATLOGIN,    //同一帐号重复登陆
    ERR_NOGRID,         //没有逻辑格信息
    ERR_NOMONSTER,      //没有怪物信息
    ERR_TARGETTOOFAR,   //目标距离太远
    ERR_NOGMCMD,        //GM指令不存在
    ERR_EXEGMCMDFAIL,   //GM指令执行失败
    ERR_GMCMDNORIGHT,   //无权限执行GM指令
    ERR_RULECHECKFAIL,  //地图规则检查失败
    ERR_BANWORD,        //请不要使用敏感词
    ERR_ILLEGALITY,     //包含非法字符
    ERR_BAG_MAPPINGS,   //背包映射异常
    ERR_VERIFY_FAIL_AGAIN,    //验证码输入有误，请重试
    ERR_VERIFY_FAIL_CANCEL,   //验证码输入有误
    ERR_LOGIN_WRONG_USER,         // 无此用户
    ERR_LOGIN_WRONG_PASSWORD,     // 密码输入有误
    ERR_NOUSCMD,        //用户指令不存在
    ERR_NOUSSCRIPT,     //用户指令脚本不存在
    ERR_EXECUSCMDFAIL,  //用户指令执行失败
    ERR_MOVE_PUNISH_CONTINUOUS,     /// 移动连续异常惩罚
    ERR_MOVE_PUNISH_SAMPLING,       /// 移动采样异常惩罚
    ERR_MS_PUNISH_SAMPLING,         /// MS采样异常惩罚
    ERR_GS_KICK_PLAYER,             /// GS踢人具体原因在协议中描述
    ERR_GP_PUNISH,                  /// 反外挂惩罚
    ERR_SVR_STOP,                   /// 服务器停止
    ERR_NAME_LENGTH,                /// 名字太短
    ERR_CREATE_ROLE_IN_COMBAT,      /// 不能在对战区创建角色
    ERR_GS_OVERLOAD,                /// GS人数已达上限
    ERR_GS_MIGRATE_DATA,            /// GS迁移玩家数据
    ERR_USERDATA_ABNORMAL,          /// 账号数据异常
    ERR_CREATE_ROLE_IN_CFG,         /// 暂时关闭创建角色功能
    ERR_BAG_SPACE_NOT_ENOUGH,       /// 背包空间不足
    ERR_NO_CFG,                     /// 未找到配置
    ERR_INVALID_CFG,                /// 配置无效
    ERR_CREATE_ROLE_CODE_NOTMATTCH, /// 创建角色邀请码不存在
    //////////////////////////////////////////////////////////////////////////
    ERR_ITEM_NOT_ENOUGH = 1000,     /// 物品不足
    ERR_ITEM_SPACE_FULL,            /// 背包已满
    ERR_ITEM_ADD,                   /// 物品添加失败
    ERR_ITEM_DESTROY,               /// 物品删除失败
    ERR_ITEM_MOVE,                  /// 物品移动失败
    ERR_ITEM_SPLIT,                 /// 物品拆分失败
    ERR_ITEM_BIND,                  /// 物品绑定失败
    ERR_ITEM_APPLY,                 /// 物品使用失败
    ERR_ITEM_SCRIPT_NOT_EXIST,      /// 物品脚本不存在
    ERR_ITEM_CANT_EQUIP,            /// 该物品不可装备
    ERR_ITEM_NOT_EQUIP_SITE,        /// 目标位置不是装备位
    ERR_ITEM_EQUIP_NOT_SUIT_SITE,   /// 装备不匹配装备位
    ERR_ITEM_EQUIP_JOB,             /// 职业不匹配
    ERR_ITEM_EQUIP_GENDER,          /// 性别不匹配
    ERR_ITEM_EQUIP_LEVEL,           /// 未达到装备等级
    ERR_ITEM_EQUIP_BIND_TYPE,       /// 装备绑定类型不匹配
    ERR_ITEM_EQUIP_WEIGHT,          /// 装备负重不足
    ERR_ITEM_MAX_BRAWN,             /// 腕力不足
    ERR_ITEM_MAX_PHY_ATK,           /// 物理攻击不足
    ERR_ITEM_MAX_MAG_ATK,           /// 魔法攻击不足
    ERR_ITEM_MAX_TAO_ATK,           /// 道术攻击不足
    ERR_ITEM_ARRANGE,               /// 物品整理失败
    ERR_ITEM_PICKUP,                /// 物品拾取失败
    ERR_ITEM_PICKUP_OWNER,          /// 该物品目前不属于你
    ERR_ITEM_PICKUP_TEAM,           /// 你不在可拾取人的队伍中
    ERR_ITEM_DROP,                  /// 物品丢弃失败
    ERR_ITEM_DROP_NOT_BAG_SITE,     /// 物品不在背包不可丢弃
    ERR_ITEM_DROP_MAP,              /// 当前地图不可丢弃物品
    ERR_ITEM_DROP_ITEM,             /// 该物品不可丢弃
    ERR_ITEM_TIE_UP,                /// 物品打捆失败
    ERR_ITEM_ENHANCE_OK,            /// 强化完成
    ERR_ITEM_ENHANCE_MUST_WEAPON,   /// 只有武器才能强化
    ERR_ITEM_ENHANCE_DISABLE,       /// 该武器不可强化
    ERR_ITEM_ENHANCE_UPGRADING,     /// 强化物品已经处于升级中
    ERR_ITEM_ENHANCE_MAX_LEVEL,     /// 已经强化到最高等级
    ERR_ITEM_ENHANCE_ITEM,          /// 强化物品首饰不正确
    ERR_ITEM_ENHANCE_MATERIAL,      /// 强化物品材料不正确
    ERR_ITEM_DRILL_OK,              /// 打孔完成
    ERR_ITEM_DRILL_MUST_EQUIP,      /// 只有装备才能打孔
    ERR_ITEM_DRILL_DISABLE,         /// 该装备不可打孔
    ERR_ITEM_DRILL_MATERIAL,        /// 需要打孔材料
    ERR_ITEM_DRILL_FULL,            /// 装备孔数量已达到上限
    ERR_ITEM_DRILL_RATE,            /// 打孔失败
    ERR_ITEM_SYNTHESIS_OK,          /// 装备合成成功
    ERR_ITEM_SYNTHESIS_MATERIAL,    /// 合成材料不正确
    ERR_ITEM_SYNTHESIS_GEM_ENOUGH,  /// 合成宝石不足
    ERR_ITEM_SYNTHESIS_GEM_ID,      /// 宝石类型不相同
    ERR_ITEM_SYNTHESIS_CANT,        /// 物品不可合成
    ERR_ITEM_SYNTHESIS_LEVEL,       /// 合成符不正确
    ERR_ITEM_SYNTHESIS_RATE,        /// 合成失败
    ERR_ITEM_EMBED_OK,              /// 宝石镶嵌成功
    ERR_ITEM_EMBED_DISABLE,         /// 宝石不可镶嵌
    ERR_ITEM_EMBED_FULL,            /// 物品镶嵌已满
    ERR_ITEM_EMBED_MATERIAL,        /// 镶嵌材料不正确
    ERR_ITEM_EMBED_MISMATCH,        /// 宝石不匹配
    ERR_ITEM_EMBED_RATE,            /// 镶嵌失败
    ERR_ITEM_DIG_OK,                /// 宝石摘除成功
    ERR_ITEM_DIG_SLOT,              /// 宝石槽位不正确
    ERR_ITEM_DIG_MATERIAL,          /// 摘除材料不正确
    ERR_ITEM_DIG_MATERIAL_LEVEL,    /// 宝石摘除符等级不符
    ERR_ITEM_IDENTIFY_OK,           /// 装备鉴定
    ERR_ITEM_IDENTIFY_DISABLE,      /// 该装备不可鉴定
    ERR_ITEM_REFINE_OK,             /// 装备精炼成功
    ERR_ITEM_REFINE_DISABLE,        /// 该装备不可精炼
    ERR_ITEM_REFINE_TOP_LEVEL,      /// 该装备已精炼到顶级
    ERR_ITEM_REFINE_LEVEL,          /// 精炼等级不正确
    ERR_ITEM_REFINE_MATERIAL,       /// 精炼材料不正确
    ERR_ITEM_REFINE_NOT_ENOUGH,     /// 精炼材料不足
    ERR_ITEM_REFINE_RATE,           /// 精炼失败
    ERR_ITEM_REPAIR_OK,             /// 装备修理成功
    ERR_ITEM_REPAIR_DISABLE,        /// 该装备不可修理
    ERR_ITEM_REPAIR_INFINITE,       /// 该装备耐久无限
    ERR_ITEM_REPAIR_MAX_DURABILITY, /// 该装备持久已满
    ERR_ITEM_NOT_EXIST,             /// 该物品不存在
    ERR_ITEM_DUP_SITE,              /// 发现重合物品
    ERR_ITEM_USEZEROAUTODEL,        /// 使用次数为零自动删除
    ERR_ITEM_DURZEROAUTODEL,        /// 持久为零为零自动删除
    ERR_ITEM_TIMEUPAUTODEL,         /// 物品使用时间到自动删除
    ERR_ITEM_BAG_WEIGHT,            /// 你背不动这么多东西
    ERR_ITEM_GUID_MAPPING,          /// 发现物品GUID映射不一致
    ERR_ITEM_NO_DATA_ROW,           /// 物品模板不存在
    ERR_ITEM_SITE,                  /// 物品位置发生异常
    ERR_ITEM_AMOUNT,                /// 物品数量发生异常
    ERR_ITEM_EXPIRED,               /// 物品已经过期
    ERR_ITEM_CREATE_BAG,            /// 创建包裹失败
    ERR_ITEM_SWAP,                  /// 交换物品失败
    ERR_ITEM_ADD_BIND_TYPE,         /// 添加物品类绑定类型错误
    ERR_ITEM_DROP_IN_SAFE,          /// 安全区不可丢弃物品
    ERR_ITEM_BAG_OPT,               /// 包裹已锁定
    ERR_ITEM_FORBID_HERO_BAG,       /// 物品禁止进入英雄包裹
    ERR_ITEM_FORBID_WAREHOUS,       /// 物品禁止放入仓库
    ERR_ITEM_PICK_UP_DROPED,        /// 不能拾取已经丢弃的物品
    ERR_ITEM_RANGE_PICK_UP_NON,     /// 范围拾取 物品已拾取
    ERR_ITEM_PICK_UP_NON,           /// 单个拾取 物品为空
    ERR_ITEM_PICK_UP_NO_SHOW,       /// 不显示的错误码
    //////////////////////////////////////////////////////////////////////////
    ERR_SKILL_NOT_EXIST = 1100,     /// 技能不存在
    ERR_SKILL_NOT_LEARNED,          /// 技能还没学习
    ERR_SKILL_NO_TARGET,            /// 目标不存在
    ERR_SKILL_SWITCH,               /// 技能开关失败
    ERR_SKILL_CD_CHAIN,             /// 技能还在冷却
    ERR_SKILL_COST_ATTR,            /// 技能属性开销不足
    ERR_SKILL_COST_ITEM,            /// 技能物品开销不足
    ERR_SKILL_NEED_WEAPON,          /// 技能需要武器
    ERR_SKILL_JUJU,                 /// 需要正确的符咒
    ERR_SKILL_CAST_DISTANCE,        /// 技能施放距离不符
    ERR_SKILL_MISS,                 /// 技能MISS
    ERR_SKILL_ROLE_DEAD,            /// 玩家已死
    ERR_SKILL_CANT_PHY_ATK,         /// 不能使用物理攻击
    ERR_SKILL_CANT_MAG_ATK,         /// 不能使用魔法攻击
    ERR_SKILL_COLLIDE,              /// 处于冲撞状态不能使用技能
    ERR_SKILL_REPELLED,             /// 处于击退状态不能使用技能
    ERR_SKILL_FIRE_ACTIVE,          /// 烈火生效
    ERR_SKILL_FIRE_EXPIRE,          /// 烈焰已过期
    ERR_SKILL_CANT_USE,             /// 技能不可使用
    ERR_SKILL_DIG_MEAT,             /// 没有挖到任何物品
    ERR_SKILL_POWER_HIT_ACTIVE,     /// 攻杀允许
    ERR_SKILL_POWER_HIT_DONE,       /// 攻杀结束
    ERR_SKILL_ATTACK_TIME,          /// 普攻时间未到
    ERR_SKILL_FIRE_EMPTY,           /// 烈火击空
    ERR_SKILL_POWER_DISABLE,        /// 攻杀时机未到
    ERR_SKILL_POWER_EMPTY,          /// 攻杀击空
    ERR_SKILL_CISHA_EMPTY,          /// 刺杀击空
    ERR_SKILL_BANYUE_EMPTY,         /// 半月击空
    ERR_SKILL_NORMAL_EMPTY,         /// 普攻击空
    ERR_SKILL_REPEL_COLLIDE,        /// 冲撞打断
    ERR_SKILL_SCRIPT_NOT_EXIST,     /// 技能脚本不存在
    ERR_SKILL_UNVALID,              /// 技能被禁止
    ERR_SKILL_ALREADY_EXIST,        /// 技能已存在
    ERR_SKILL_JOB_MISMATCH,         /// 职业不匹配
    ERR_SKILL_EXIST_SAME_CHAIN,     /// 同一技能链的技能已存在
    ERR_SKILL_REACH_UPLIMIT,        /// 已达上限

    //////////////////////////////////////////////////////////////////////////
    ERR_BUFF_NOT_EXIST = 1200,      /// BUFF不存在
    ERR_BUFF_CANT_CANCEL,           /// BUFF不能取消
    //////////////////////////////////////////////////////////////////////////
    ERR_TEAM_ALREADY_EXIST = 1300,  /// 队伍已存在，队伍创建失败
    ERR_TEAM_MAP,                   /// 该地图不可组队
    ERR_TEAM_TARGET_MAP,            /// 对方所在地图不可组队
    ERR_TEAM_SWITCH_REFUSE,         /// 对方设置了拒绝组队
    ERR_TEAM_NO_PLAYER,             /// 玩家不存在或已下线
    ERR_TEAM_TARGET_HAS_TEAM,       /// 对方已经有队伍
    ERR_TEAM_TARGET_NO_TEAM,        /// 对方没有队伍
    ERR_TEAM_NO_RIGHT,              /// 没有权限
    ERR_TEAM_FULL,                  /// 队伍已满
    ERR_TEAM_INVITER_OFFLINE,       /// 邀请者已经下线 
    ERR_TEAM_INVITE_EXPIRE,         /// 邀请已过期
    ERR_TEAM_REFUSE,                /// 对方拒绝组队
    ERR_TEAM_TARGET_LEADER_OFFLINE, /// 对方队长不在线
    ERR_TEAM_JOIN_REFUSE,           /// 对方队长不同意你加入队伍
    ERR_TEAM_INVITE_TIME,           /// 邀请过于频繁
    ERR_TEAM_JOIN_TIME,             /// 申请过于频繁
    ERR_TEAM_AUTH_TIME,             /// 权限变更过于频繁
    ERR_TEAM_QUERY_TIME,            /// 队伍查询过于频繁
    ERR_TEAM_JOIN_EXPIRE,           /// 申请已过期
    //////////////////////////////////////////////////////////////////////////
    ERR_QUICK_BAR_ITEM_NOT_EXIST = 1400,    /// 物品不存在
    ERR_QUICK_BAR_SKILL_NOT_EXIST,          /// 技能不存在
    //////////////////////////////////////////////////////////////////////////
    ERR_DEPOSIT_SAVE_OK = 1500,             /// 存金币成功
    ERR_DEPOSIT_TALK_OK,                    /// 取金币成功
    ERR_DEPOSIT_DROP_OK,                    /// 丢金币成功
    ERR_DEPOSIT_NOT_ENOUGH_GOLD,            /// 金币不足
    ERR_DEPOSIT_NOT_ENOUGH_BIND_GOLD,       /// 绑定金币不足
    //////////////////////////////////////////////////////////////////////////
    ERR_TRADE_P2P_OK = 1600,                /// 交易成功
    ERR_TRADE_P2P_TRADING,                  /// 对方交易中
    ERR_TRADE_P2P_INVITE_EXPIRE,            /// 交易邀请已过期
    ERR_TRADE_P2P_REFUSE,                   /// 对方拒绝交易
    ERR_TRADE_P2P_NOT_ENOUGH_GOLD,          /// 没有足够的金币
    ERR_TRADE_P2P_GOLD_FULL,                /// 金币溢出
    ERR_TRADE_P2P_DATA,                     /// 交易数据已变更
    ERR_TRADE_P2P_ITEM_BIND,                /// 绑定物品不可交易
    ERR_TRADE_P2P_ITEM_TRADABLE,            /// 该物品不可交易
    ERR_TRADE_P2P_ITEM_SITE,                /// 物品必须在背包中
    ERR_TRADE_P2P_DUP_ITEM,                 /// 交易数据已上架
    ERR_TRADE_P2P_FAILED,                   /// 交易失败
    ERR_TRADE_P2P_GOLD_LOCK,                /// 金币未解锁
    ERR_TRADE_P2P_LEVEL,                    /// 交易双方等级不够

    ERR_TRADE_STALL_OK = 1620,              /// 摆摊成功
    ERR_TRADE_STALL_LEVEL,                  /// 摆摊等级不足
    ERR_TRADE_STALL_PK_RED,                 /// 红名不可摆摊
    ERR_TRADE_STALL_PK_BLACK,               /// 黑名不可摆摊
    ERR_TRADE_STALL_GOLD_COST,              /// 摆摊金币不足
    ERR_TRADE_STALL_GRID,                   /// 该位置不可摆摊
    ERR_TRADE_STALL_REFUSE,                 /// 附近已经有人摆摊
    ERR_TRADE_STALL_NOT_READY,              /// 摆摊未准备
    ERR_TRADE_STALL_ITEM,                   /// 摆摊物品有误
    ERR_TRADE_STALL_PRICE_LESS_ZERO,        /// 摆摊物品单价不可小于零
    ERR_TRADE_STALL_PRICE_TYPE,             /// 摆摊物品价格类型不符
    ERR_TRADE_STALL_ITEM_AMOUNT,            /// 物品数量为零不可上架
    ERR_TRADE_STALL_ITEM_BIND,              /// 已绑定物品不可摆摊销售
    ERR_TRADE_STALL_ITEM_TRADABLE,          /// 该物品不可交易
    ERR_TRADE_STALL_ITEM_SITE,              /// 摆摊时物品必须在背包中
    ERR_TRADE_STALL_ARRANGE,                /// 不在摆摊状态不可上下架
    ERR_TRADE_STALL_TARGET_NOT_START,       /// 对方尚未开始摆摊
    ERR_TRADE_STALL_ITEM_DATA,              /// 物品数据已变更
    ERR_TRADE_STALL_ITEM_NOT_ENOUGH,        /// 物品数量不足
    ERR_TRADE_STALL_ITEM_NOT_SELL,          /// 物品没有上架
    ERR_TRADE_STALL_READY_CD,               /// 摆摊准备冷却时间未到
    ERR_TRADE_STALL_ITEM_NOT_BUY,           /// 摊位不收购该物品
    ERR_TRADE_STALL_ITEM_MAX_BUY_AMOUNT,    /// 达到收购数量上限
    ERR_TRADE_STALL_OWNER_BAG_FULL,         /// 摊主背包已满

    //////////////////////////////////////////////////////////////////////////
    ERR_ROLE_OK = 1650,                     /// 成功
    ERR_ROLE_NOT_ENOUGH_POINT,              /// 属性点不足
    ERR_ROLE_QUERY_NULL,                    /// 目标不存在或不在线
    ERR_ROLE_LC_DOWN,                       /// 你的武器被诅咒
    ERR_ROLE_DROP_GRID,                     /// 地上没有空闲的位置可以丢弃
    ERR_ROLE_SITE,                          /// 无效的背包位置
    ERR_ROLE_REQUEST_SEG_TO_FAST,           /// 物品请求过快
    ERR_ROLE_PK,                            /// PK值上升
    ERR_ROLE_ARRANGE_BAG_TOO_FAST,          /// 物品整理过于频繁
    ERR_ROLE_PK_PROTECTED,                  /// 正常防卫规则保护
    ERR_ROLE_QUEST_QUERY_TOO_FAST,          /// 任务查询过于频繁
    ERR_ROLE_MOVE_ITEM_TOO_FAST,            /// 物品移动过于频繁
    ERR_ROLE_RIDE_TOO_FAST,                 /// 骑马操作过于频繁
    ERR_ROLE_RIDE_NULL,                     /// 请先装备坐骑
    ERR_ROLE_RIDE_DIE,                      /// 坐骑已死
    ERR_ROLE_RIDE_NOT_USE,                  /// 骑乘状态下不可使用
    ERR_ROLE_FASHION_TOO_FAST,              /// 时装操作过于频繁
    ERR_ROLE_FASHION_NULL,                  /// 请先装备时装
    ERR_ROLE_FASHION_DIE,                   /// 时装耐久不足
    ERR_ROLE_FASHION_WEAPON_TOO_FAST,       /// 时装武器操作过于频繁
    ERR_ROLE_FASHION_WEAPON_NULL,           /// 请先装备时装武器
    ERR_ROLE_FASHION_WEAPON_DIE,            /// 时装武器耐久不足

    //////////////////////////////////////////////////////////////////////////
    ERR_NODGNDATA = 1700,                   /// 副本数据找不到
    ERR_NODGNMAP,                           /// 副本地图不存在
    ERR_CHECKDGNMAP,                        /// 副本地图检查失败

	ERR_VIP_ENABLE = 1800,					///VIP已经激活
	ERR_VIP_INVALID,						///VIP等级无效
	ERR_VIP_INGOT,							///元宝不足
	ERR_VIP_ITEM_ENABLE,					///VIP道具已激活
	ERR_VIP_ITEM_BUY,						///VIP道具已购买
	ERR_VIP_ITEM_INVALID,					///VIP道具无效
	ERR_VIP_ITEM_NOTSELL,					///VIP道具已下架
    ERR_VIP_ITEM_DISABLE,                   ///VIP道具不能单买
	ERR_VIP_APPLY,							///VIP道具未激活
	ERR_VIP_SCRIPT,							///VIP道具脚本不存在

    ERR_DUMMY_NO_ACCESS = 1900,             ///没有控制英雄的权限
    ERR_DUMMY_TOO_FAR,                      ///距离英雄太远
    ERR_DUMMY_NOT_ATTACK,                   ///英雄不在攻击状态
    ERR_DUMMY_NOT_JOINT_SKILL,              ///不是合击技能
    ERR_DUMMY_HAS_JOINT,                    ///已经准备合击了
    ERR_DUMMY_NOT_ENOUGH_XP,                ///怒气未满
    ERR_HERO_LORD_OFFLINE,                  ///主人不在线
    ERR_MAP_CANT_GEN_HERO,                  ///地图禁止召唤英雄

    //////////////////////////////////////////////////////////////////////////
    ERR_ETASK_FULL = 2300,                  /// 任务已满
    ERR_QUEST_IN_FINISHED,                  /// 任务已经完成过了
    ERR_QUEST_IN_CURRENT,                   /// 任务已经接过了
    ERR_QUEST_REQ_WEEK_COUNT,               /// 本周可接次数已满
    ERR_QUEST_REQ_DAY_COUNT,                /// 今日可接次数已满
    ERR_QUEST_REQ_TIME,                     /// 任务需求时间不符
    ERR_QUEST_REQ_LEVEL,                    /// 任务需求等级不符
    ERR_QUEST_REQ_ATT,                      /// 任务需求属性不符
    ERR_QUEST_REQ_PROLOGUE,                 /// 任务需求前置不符
    ERR_QUEST_REQ_ITEM,                     /// 任务需求物品不符
    ERR_QUEST_REQ_JOB,                      /// 任务需求职业不符
    ERR_QUEST_REQ_GENDER,                   /// 任务需求性别不符
    ERR_QUEST_NOT_IN_CURRENT,               /// 任务没有接过
    ERR_QUEST_CONSISTENCY,                  /// 任务已变更
    ERR_QUEST_SELECT_INDEX,                 /// 选择的物品索引不正确
    ERR_QUEST_ACHIEVE_TIME,                 /// 任务已超时
    ERR_QUEST_ACHIEVE_GROUP_HUNTING,        /// 任务完成组打怪计数不符
    ERR_QUEST_ACHIEVE_HUNTING,              /// 任务完成打怪计数不符
    ERR_QUEST_ACHIEVE_HUNTLEVEL,            /// 任务完成打等级怪计数不符
    ERR_QUEST_ACHIEVE_GROUP_ITEM,           /// 任务完成组物品收集计数不符
    ERR_QUEST_ACHIEVE_ITEM,                 /// 任务完成物品收集计数不符
    ERR_QUEST_ACHIEVE_APPLY_ITEM,           /// 任务完成物品使用计数不符
    ERR_QUEST_ACHIEVE_NPC,                  /// 任务完成npc拜访计数不符
    ERR_QUEST_REQ_SCRIPT,                   /// 任务需求脚本不符
    ERR_QUEST_ACHIEVE_SCRIPT,               /// 任务完成脚本不符
    ERR_QUEST_ACHIEVE_LEVEL,                /// 任务完成等级不符
    ERR_QUEST_NULL,                         /// 任务不存在
    ERR_QUEST_FORCE_READY,                  /// 任务无法强制完成

    //////////////////////////////////////////////////////////////////////////
    ERR_NORELIVEMAP = 2400,         /// 找不到复活地图
    ERR_ATKTOOFAST,                 /// 攻击频率过快
    
    ERR_NOTARGET,                   // 找不到目标
    ERR_NODATATYPE,                 //无此数据类型

    //////////////////////////////////////////////////////////////////////////
    ERR_NPC_NOSHOP = 2500,          //商店不存在
    ERR_NPC_NOITEM,                 //商品不存在
    ERR_NPC_ITEMNOENOUGH,           //商品数量不足
    ERR_NPC_TOOFAR,                 //距离NPC太远
    ERR_NPC_NO_ACCEPT,              //本店不收购此类物品
    ERR_NPC_NO_REPAIR,              /// 本店不修理此类物品
    ERR_NPC_MUST_BIND,              /// 只能使用绑定金币购买
    ERR_NPC_MUST_UNBIND,            /// 只能使用金币购买

    //////////////////////////////////////////////////////////////////////////
    ERR_MAP_ITEM_FORBID = 2600,             /// 地图禁止使用此物品
    ERR_MAP_SKILL_FORBID,                   /// 地图禁止使用此技能
    ERR_MAP_RIDE_FORBID,                    /// 地图禁止使用坐骑

    //////////////////////////////////////////////////////////////////////////
    ERR_EXP_NOT_ENOUGH = 3000,      /// 经验不足
    ERR_INGOT_NOT_ENOUGH,           /// 元宝不足
    ERR_BIND_INGOT_NOT_ENOUGH,      /// 绑定元宝不足
    ERR_INTEGRAL_NOT_ENOUGH,        /// 积分不足
    ERR_GOLD_NOT_ENOUGH,            /// 金币不足
    ERR_BIND_GOLD_NOT_ENOUGH,       /// 绑定金币不足
    ERR_LOCKSWITCH,                 /// 财产未解锁
    ERR_OWNER_INGOT_NOT_ENOUGH,     /// 摊主元宝不足
    ERR_OWNER_GOLD_NOT_ENOUGH,      /// 摊主金币不足
    ERR_NON_CURRENCY_TYPE,          /// 无此货币类型
    
    //////////////////////////////////////////////////////////////////////////
    // 邮件系统错误码
    //////////////////////////////////////////////////////////////////////////
    ERR_MAIL_MAILBOX_FULL = 3100,   /// 对方收件箱已满
    ERR_MAIL_NO_MAIL,               /// 不存在的邮件
    ERR_MAIL_NO_ATTACH,             /// 没有这个附件或附件已经领取
    ERR_MAIL_NO_PLAYER,             /// 没有这个玩家
    ERR_MAIL_NOT_EMPTY,             /// 邮件非空
    ERR_MAIL_ADD_ITEMNAME_STYLE,    /// 添加邮件标题类型错误
    ERR_MAIL_ADD_ITEMNUM_STYLE,     /// 添加邮件物品数量类型错误
    ERR_MAIL_ADD_ITEMBIND_STYLLE,   /// 添加邮件物品绑定类型错误
    ERR_MAIL_ADD_NON_ITERMNAME,     /// 添加邮件附加品索引名错误
    ERR_MAIL_ADD_NUM_MORE_THAN_STACK,  /// 添加邮件附加品数量超过最大堆叠数量
    ERR_MAIL_ADD_NONPLAYER,            /// 添加邮件无该玩家
    ERR_MAIL_NON_ADDITION_INDEX,       /// 添加邮件附件序列数错误
    ERR_MAIL_ADDTION_ITEM_NUM,         /// 添加邮件附加品种类数量错误
    ERR_MAIL_NO_ADD_TYPE,              /// 无此添加邮件类型
    ERR_MAIL_ADD_CURRENCY_TYPE,        /// 添加邮件货币类型错误
    ERR_MAIL_ADD_CURRENCY_TYPE_NUM,    /// 添加邮件货币种类超过最大数量
    ERR_MAIL_HAD_GETED_ATTACHMENT,     /// 邮件已领取
    ERR_MAIL_NON_DEL,                  /// 邮件有附件或者货币无法删除
    ERR_MAIL_ADD_FAILED,               /// 邮件添加失败
    ERR_MAIL_ATTACH_ON_INDEX_NON_ITEM, 

    //////////////////////////////////////////////////////////////////////////
    // 寄售系统错误码
    //////////////////////////////////////////////////////////////////////////
    ERR_MARKET_MAX_NUM = 3150,      /// 委托数量已经到达上限
    ERR_MARKET_MAX_COUNT,           /// 你收购这么多货，想干啥呢
    ERR_MARKET_NOT_EXIST,           /// 该笔挂单不存在或已撤销
    ERR_MARKET_ITEM_MATCH,          /// 对方没有收购该物品
    ERR_MARKET_ITEM_MUCH,           /// 对方没有收购这么多数量
    ERR_MARKET_UNIT,                /// 物品单位数量与总数不匹配
    ERR_MARKET_CANT_PURCHASE,       /// 不能收购该物品
    ERR_MARKET_PRICE_ERROR,         /// 总价格错误
    ERR_MARKET_CANT_SELL,           /// 不能出售该物品
    ERR_MARKET_NOT_ENOUHG_GOLD,     /// 金币不足
    ERR_MARKET_NOT_ENOUHG_INGOT,    /// 元宝不足
    //////////////////////////////////////////////////////////////////////////
    // 行会错误码
    //////////////////////////////////////////////////////////////////////////
    ERR_FAMILY_HAS_JOINED = 3500,   /// 对方已经加入过行会了
    ERR_FAMILY_LOW_LEVEL,           /// 在行会中级别不够
    ERR_FAMILY_NO_FAMILY,           /// 没有加入任何行会
    ERR_FAMILY_OFFLINE,             /// 对方不在线
    ERR_FAMILY_NOT_EXSIT,           /// 该行会不存在
    ERR_FAMILY_IN_FAMILY,           /// 你已经有行会了
    ERR_FAMILY_NOT_MEMBER,          /// 不是本行会成员
    ERR_FAMILY_TITLE_NOT_EXSIT,     /// 不存在的封号
    ERR_FAMILY_NOT_EMPTY,           /// 行会中还有成员存在
    ERR_FAMILY_LEADER_OFFLINE,      /// 对方会长不在线
    ERR_FAMILY_HAS_ALLY,            /// 已经是联盟行会了
    ERR_FAMILY_HAS_ENEMY,           /// 已经是敌对行会了
    ERR_FAMILY_ALLY_WITH_ENEMY,     /// 不能和敌对行会结盟
    ERR_FAMILY_ENEMY_WITH_ALLY,     /// 请先解除行会联盟
    ERR_FAMILY_NO_ENOUGH_TITLE,     /// 该职位人数已满
    ERR_FAMILY_IS_NOT_SUBLEADER,    /// 对方不是副会长
    ERR_FAMILY_IS_NOT_INIT,         /// 行会系统正在初始化，请稍候再试
    ERR_FAMILY_NAME_EXSIT,          /// 行会名称已经存在，请重新想一个吧
    ERR_FAMILY_ALLY_MAX,            /// 已经达到最大的联盟行会数
    ERR_FAMILY_P_ALLY_MAX,          /// 对方已经达到最大的联盟行会数
    ERR_FAMILY_ENEMY_MAX,           /// 已经达到最大的敌对行会数
    ERR_FAMILY_LEADER_CANT_LEAVE,   /// 行会会长不能脱离行会
    ERR_FAMILY_TEXT_TOO_LONG,       /// 文本超过最大长度
    ERR_FAMILY_SAME_TITLE,          /// 封号名称不能相同
    ERR_FAMILY_MAX_TITLE_MEMBER,    /// 该封号人数达到上限
    ERR_FAMILY_MAX_MEMBER_NUM,      /// 行会人数已满
    ERR_FAMILY_SELF,                /// 不能和自己结盟或敌对
    ERR_FAMILY_LEVEL,               /// 等级不足
    ERR_FAMILY_NO_RELATION,         /// 行会之间没关系
    ERR_FAMILY_CAN_NOT_TITLE,       /// title设置失败
    ERR_FAMILY_CAN_NOT_KICK,        /// 踢人失败
    ERR_FAMILY_CAN_NOT_DESTORY,     /// 解散失败

    ERR_FAMILY_END,                 /// 行会错误码结束符

    //////////////////////////////////////////////////////////////////////////
    // 聊天小喇叭错误码
    //////////////////////////////////////////////////////////////////////////
    ERR_SPEAKER_NOT_EXIST,          ///道具小喇叭不存在

    //禁止登陆
    ERR_FORBIDLOGIN_IP,             ///IP禁止登陆
    ERR_FORBIDLOGIN_NAME,           ///角色禁止登陆
    ERR_FORBIDLOGIN_ACCOUNT,        ///帐号禁止登陆
	ERR_FORBIDLOGIN_HARDWARE,		///硬件码禁止登陆

    //成就
    ERR_GLORY_LEVEL,                ///等级不足
    ERR_GLORY_UNFINISH,             ///成就未完成
    ERR_GLORY_HAS_AWARDED,          ///奖励已经领取


    //怪物
    ERR_MONSTER_ALLOC,              ///分配Monster*失败
    ERR_MONSTER_BORNPOS,            ///怪物没有出生点
    ERR_MONSTER_APPEAR,             ///怪物出现包错误
    ERR_MONSTER_NOTMAP,              ///怪物没有地图信息
    ERR_MONSTER_NOTCONFIG,           ///怪物没有模板信息

    //用户指令
    ERR_UCMD_OK,                    ///用户指令执行成功
    ERR_UCMD_FAIL,                  ///用户指令执行失败

    //
    ERR_MIGRATE_IN_DEAL,            ///同账号上一个数据迁移处理中
    ERR_MIGRATE_TIMEOUT,            ///数据迁移超时
    ERR_MIGRATE_LOGIC,              ///数据迁移逻辑错误
    ERR_MIGRATE_NO_MD,              ///数据迁移连接中转服务器失败
    ERR_MIGRATE_NO_DST,             ///数据迁移连接目标区服务器失败
    ERR_MIGRATE_NO_ACK,             ///数据迁移目标区无应答
    ERR_MIGRATE_AGENT,              ///数据迁移只能在同一个代理的区之间
    ERR_MIGRATE_TYPE,               ///数据迁移只能在测试区或正式区之间
    ERR_MIGRATE_SVR_INFO,           ///数据迁移找不到目标区的配置信息
    ERR_FAMILY_NO_JOIN_REQUEST,     ///没有加入行会的请求

    //////////////////////////////////////////////////////////////////////////
    // 内功
    //////////////////////////////////////////////////////////////////////////
    ERR_INNER_FORCE_LEVEL_UP_FAILED,    ///内功升级失败

    ERR_MOBA_NO_VALID_ROOM_ID = 3600,   /// 无可用的房间号
    ERR_MOBA_ALREADY_IN_ROOM,           /// 已经在房间中
    ERR_MOBA_NO_ROOM,                   /// 房间不存在
    ERR_MOBA_MAX_ROOM_MEMBER,           /// 房间人数已满
    ERR_MOBA_ROOM_PWD,                  /// 房间密码错误
    ERR_MOBA_ROOM_NAME_DUPLICATE,       /// 房间名字重复
    ERR_MOBA_INVALID_ROOM_OP,           /// 非法的房间操作
    ERR_MOBA_ROOM_STATE_CANT_OP,        /// 此房间状态下不能进行该操作
    ERR_MOBA_ROOM_MEMBER_NOT_EXIST,     /// 房间成员不存在
    ERR_MOBA_SET_VICE_HOST,             /// 只能提升对方阵营玩家为副房主
    ERR_MOBA_ROOM_MODE,                 /// 房间模式错误
    ERR_MOBA_ROOM_VS_NUM,               /// 房间对战人数错误
    ERR_MOBA_ALREADY_IN_GAME,           /// 此房间已经在游戏中

    ERR_SERVER_STATUS = 3800,
    ERR_SERVER_STATUS_MAINTENANCE,  /// 维护

    //改名
    ERR_CHANGE_NAME_REPEAT = 3900,      /// 名字重复
    ERR_CHANGE_NAME_NOT_EXIST,          /// 玩家不存在
    ERR_CHANGE_NAME_ILLEGAL_CHARACTERS, /// 名字含非法字符

    //称号
    ERR_TITLE_DEL_ERR = 4000,   /// 称号删除失败

    //请在此项之上添加错误码
    ERR_COUNT,
};
