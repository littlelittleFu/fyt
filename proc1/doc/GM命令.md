## GM命令格式

| 字段       | 类型   | 长度 | 取值 |
| ---------- | ------ | ---- | ---- |
| moduleid   | uint16 |      | 3    |
| protocolid | uint16 |      | 25   |
| sn         | int32  |      |      |
| cmd        | string | 256  |      |
| param      | string | 256  |      |

## 服务端响应消息格式

| 字段       | 类型   | 取值 |
| ---------- | ------ | ---- |
| moduleid   | uint16 | 7    |
| protocolid | uint16 | 29   |
| sn         | int32  |      |
| ecode      | int32  |      |
| guid       | uint64 |      |

### IssueGoods

**Param: *json***

| 字段   | 类型   | 说明         |
| ------ | ------ | ------------ |
| order  | string | 订单号       |
| role   | string | 角色GUID     |
| type   | uint8  | 支付类型     |
| goods  | uint32 | 商品ID       |
| count  | uint32 | 购买数量     |
| amount | uint32 | 支付金额(分) |

**Return:** 0 成功；38 失败

## AddItem

**Params:** \<PlayerName\> \<ItemKeyName\> \<ItemNum\> \<BindType\>

BindType: 0 无绑定；1 拾取绑定；2 使用绑定

**Return:** 0 成功；38 失败；其他 添加物品失败错误码

## RemoveItem

**Params:** \<PlayerName\> \<ItemKeyName\> \<ItemNum\> \<BindType\>

**Return:** 0 成功；38 失败；其他 删除物品失败错误码

## SetPlayerProp

**Params:** \<PlayerName\> \<PropID\> \<Value\>

**Return:** 0 成功；38 失败
