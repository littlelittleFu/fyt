
- Player_SetAutoPickItemRadius
  设置自动捡物半径
- 参数:
  - guid: string; 角色GUID
  - radius: number; 自动捡物半径; 0-`AutoPickupMaxDistance`(见备注)，0取消自动捡物
- 返回值: boolean
- 备注:
  - 地图需要支持自动捡物，否则无效。`map.csv`表`AutoPickItem`非0表示支持
  - `global.csv`表`AutoPickupMaxDistance`控制自动捡物的最远距离，默认10

---

- Player_SetAutoPickItemRelativePositions
  设置自动捡物相对坐标点
- 参数:
  - guid: string; 角色GUID
  - relpos: table; 捡物相对坐标点集，格式: { {-1, -1}, {0, 1}, ... }; 最多16个，为空取消自动捡物
- 返回值: boolean
- 备注: 同上

---

- Player_SetAutoPickItemInterval
  设置自动捡物的时间间隔，间隔时间内不能再次捡物
- 参数:
  - guid: string; 角色GUID
  - interval: number; \[50, 60000\] ms，默认300
- 返回值: boolean

---

- Player_AddSkill
  添加技能
- 参数:
  - guid: string; 角色GUID
  - skillID: number; 技能ID
  - active: boolean; 是否处于激活状态
- 返回值: number: 0 成功; 1100 配置表中没有相关技能; 1132 技能已存在; 1134 存在同一技能链中的技能

---

- Player_DeleteSkill
  删除技能
- 参数:
  - guid: string; 角色GUID
  - skillID: number; 技能ID
  - delAllInSameChain: boolean; 是否删除同一技能链的所有技能; 默认值: false
- 返回值: 无

---

- Player_SkillIsExist
  判断技能是否存在
- 参数:
  - guid: string; 角色GUID
  - skillID: number; 技能ID
  - searchSkillChain: boolean; 是否查找同一技能链中的技能; 默认值: false
- 返回值: boolean

---

- Player_GetSkillIDList
  获取玩家的技能ID列表
- 参数: guid: string; 角色GUID
- 返回值: table: 数组

---

- Player_GetSkillIDByChainID
  通过技能链ID获取技能ID
- 参数:
  - guid: string; 角色GUID
  - skillChainID: number; 技能链ID
- 返回值: number

---

- SetFormAllowFunc
  远程调用服务端脚本时，设置哪些函数可以调用
- 参数: allowFuncs: table; 可调用的函数列表; 例: { "JpUp.main", "JpUp.AddStar", ... }
- 返回值: 无

---

- Role_GetBuffList
  获取BUFF ID列表
- 参数: guid: string; 角色GUID
- 返回值: table: 数组

---

- Role_ApplySkill
  使用技能
- 参数:
  - guid: string; 角色GUID
  - skillID: uint16; 技能ID
  - x: uint16; x坐标
  - y: uint16; y坐标
  - targetGUID: string; 目标GUID
- 返回值: bool

---

- Role_GetMasterGUIDAsString
  获取角色（宠物、分身）主人GUID
- 参数: guid: string; 角色GUID
- 返回值: string

---

- Guild_GetGUIDByName
  通过行会名获取行会GUID
- 参数: guildName: string; 行会名
- 返回值: string

---

- SetCastleOwnFamily
  设置攻沙胜者行会
- 参数: guildName: string; 行会名
- 返回值: 无

---

- Player_RemoveItemByGuid2
  删除物品
- 参数:
  - playerGUID: string; 角色GUID
  - itemGUID: string; 物品GUID
  - num: uint16; 数量
  - logInfo: table; 包含一个日志字符串
- 返回值: 0 成功; 其他 失败

---

- Item_IsBind
  判断物品是否绑定
- 参数: itemGUID: string; 物品GUID
- 返回值: true 绑定; false 未绑定

---

- Map_GetAllRoleByType
  按类型获取指定地图中所有角色列表
- 参数:
  - mapGUID: string; 地图GUID
  - roleType: uint8; 角色类型; 0 所有，1 玩家，2 npc，3 怪物，4 宠物
- 返回值: table: 角色GUID列表