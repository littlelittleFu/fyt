#pragma once

#include "netdata.h"

//===============包含的其他协议文件===============
#include "DataInfo.hpp"
 //===============宏定义开始===============
//===============宏定义结束===============

//===============数据定义开始===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct ErrorAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       ecode; //错误码
	uint64_t                  guid; //guid
	char                      detail[256]; //错误描述
	ErrorAck():moudleid(7),protocolid(0){}
};

struct GenServantNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //主人的GUID
	SERVANT_INFO              servant; //随从信息
	GenServantNtf():moudleid(7),protocolid(1){}
};

struct KillServantNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //主人的GUID
	uint64_t                  servant_guid; //随从信息
	KillServantNtf():moudleid(7),protocolid(2){}
};

struct ServantDieNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //主人的GUID
	uint64_t                  servant_guid; //随从信息
	ServantDieNtf():moudleid(7),protocolid(3){}
};

struct ServantModeNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             mode; //主人的模式 0=战斗 1=休息
	uint64_t                  master_guid; //主人的GUID
	uint64_t                  servant_guid; //随从信息
	ServantModeNtf():moudleid(7),protocolid(4){}
};

struct ServantModeResult{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //主人的GUID
	uint64_t                  servant_guid; //随从信息
	unsigned char             result; //主人的模式 0=找不到随从、失败 1=模式变更成功
	ServantModeResult():moudleid(7),protocolid(5){}
};

struct DgnCreateRpt{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  map_code; //副本地图索引
	unsigned short            dgn_id; //副本模板id
	unsigned int              create_time; //副本创建时间
	unsigned int              life_time; //副本创建生存
	unsigned char             load_grid; //是否加载逻辑格 0=否 1=是
	DgnCreateRpt():moudleid(7),protocolid(6){}
};

struct DgnDestroyRpt{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  map_code; //副本地图索引
	DgnDestroyRpt():moudleid(7),protocolid(7){}
};

struct TipsMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      msg[256]; //消息内容
	TipsMsgNtf():moudleid(7),protocolid(8){}
};

struct TopMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             foreground; //消息前景颜色ID
	unsigned char             background; //消息背景颜色ID
	unsigned char             count; //消息滚动次数
	char                      msg[256]; //消息内容
	TopMsgNtf():moudleid(7),protocolid(9){}
};

struct CenterMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             foreground; //消息前景颜色ID
	unsigned char             background; //消息背景颜色ID
	char                      msg[256]; //消息内容
	CenterMsgNtf():moudleid(7),protocolid(10){}
};

struct BottomMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             foreground; //消息前景颜色ID
	unsigned char             background; //消息背景颜色ID
	char                      msg[256]; //消息内容
	BottomMsgNtf():moudleid(7),protocolid(11){}
};

struct PopDlgMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      msg[256]; //消息内容
	PopDlgMsgNtf():moudleid(7),protocolid(12){}
};

struct JumpToRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      role_name[256]; //对方角色的名字
	uint64_t                  self_guid; //自已的GUID
	JumpToRoleReq():moudleid(7),protocolid(13){}
};

struct JumpToRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  map_guid; //对方地图GUID
	unsigned short            pos_x; //对方地图x坐标
	unsigned short            pos_y; //对方地图y坐标
	uint64_t                  self_guid; //自己的GUID
	JumpToRoleAck():moudleid(7),protocolid(14){}
};

struct DragRoleNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      role_name[256]; //对方角色的名字
	char                      self_name[256]; //自已角色的名字
	DragRoleNtf():moudleid(7),protocolid(15){}
};

struct LogInfo{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      role_name[256]; //角色的名字
	int                       action; //动作
	char                      map_name[256]; //地图名称
	unsigned short            x; //x
	unsigned short            y; //y
	char                      item_name[256]; //物品名称
	uint64_t                  item_guid; //物品guid
	char                      target_name[256]; //目标名称
	int64_t                   src_value; //原数据
	int64_t                   ref_value; //改变量
	char                      descript[256]; //描述
	unsigned int              create_time; //创建时间
	char                      detail[32768]; //细节
	LogInfo():moudleid(7),protocolid(16){}
};

struct RoleCallBackNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //角GUID
	char                      callback[256]; //回调函数 格式：文件:函数名
	char                      param[256]; //回调函数的参数
	RoleCallBackNtf():moudleid(7),protocolid(17){}
};

struct StopSvrNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	StopSvrNtf():moudleid(7),protocolid(18){}
};

struct GenServantResult{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //主人的GUID
	uint64_t                  servant_guid; //随从信息
	unsigned char             result; //0=生成失败 1=生成成功
	GenServantResult():moudleid(7),protocolid(19){}
};

struct CastleOwnerNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      castle_name[256]; //城堡名称
	char                      family_name[256]; //行会名称
	CastleOwnerNtf():moudleid(7),protocolid(20){}
};

struct GSTrigScriptNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      callback[256]; //回调函数
	unsigned short            param_len; //参数长度
	unsigned char             param[1024]; //参数
	GSTrigScriptNtf():moudleid(7),protocolid(21){}
};

struct EscortFailNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  escorter; //镖车主人的GUID
	EscortFailNtf():moudleid(7),protocolid(22){}
};

struct BoardMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      title[256]; //消息标题
	char                      msg[256]; //消息内容
	unsigned int              timeout; //消息存在时间
	BoardMsgNtf():moudleid(7),protocolid(23){}
};

struct DummyJumpMapBrd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  dummy_guid; //假人guid
	uint64_t                  map_guid; //目标map的guid
	unsigned short            map_x; //目标坐标
	unsigned short            map_y; //目标坐标
	uint64_t                  lord_guid; //控制方guid, 没有填0
	char                      json_added[1024]; //附加临时数据，json格式
	DummyJumpMapBrd():moudleid(7),protocolid(24){}
};

struct DummyStateSwitchBrd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  dummy_guid; //假人guid
	uint64_t                  player_guid; //主人guid
	DummyStateSwitchBrd():moudleid(7),protocolid(25){}
};

struct DummyQuitBrd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  dummy_guid; //假人guid
	unsigned int              dummy_login_time; //假人上线时间
	uint64_t                  player_guid; //主人guid
	DummyQuitBrd():moudleid(7),protocolid(26){}
};

struct GS2GTNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned short            int_count; //整形数据个数
	IntData                   int_data[256]; //数据值
	unsigned short            str_count; //字符型数据个数
	StrData                   str_data[256]; //数据值
	GS2GTNtf():moudleid(7),protocolid(27){}
};

#pragma warning( pop ) 
//===============数据定义结束===============
//===============打包解包函数定义开始===============
int EnCodeErrorAck(void* pHost, CNetData* poNetData);
int DeCodeErrorAck(void* pHost, CNetData* poNetData);
int EnCodeGenServantNtf(void* pHost, CNetData* poNetData);
int DeCodeGenServantNtf(void* pHost, CNetData* poNetData);
int EnCodeKillServantNtf(void* pHost, CNetData* poNetData);
int DeCodeKillServantNtf(void* pHost, CNetData* poNetData);
int EnCodeServantDieNtf(void* pHost, CNetData* poNetData);
int DeCodeServantDieNtf(void* pHost, CNetData* poNetData);
int EnCodeServantModeNtf(void* pHost, CNetData* poNetData);
int DeCodeServantModeNtf(void* pHost, CNetData* poNetData);
int EnCodeServantModeResult(void* pHost, CNetData* poNetData);
int DeCodeServantModeResult(void* pHost, CNetData* poNetData);
int EnCodeDgnCreateRpt(void* pHost, CNetData* poNetData);
int DeCodeDgnCreateRpt(void* pHost, CNetData* poNetData);
int EnCodeDgnDestroyRpt(void* pHost, CNetData* poNetData);
int DeCodeDgnDestroyRpt(void* pHost, CNetData* poNetData);
int EnCodeTipsMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeTipsMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeTopMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeTopMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeCenterMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeCenterMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeBottomMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeBottomMsgNtf(void* pHost, CNetData* poNetData);
int EnCodePopDlgMsgNtf(void* pHost, CNetData* poNetData);
int DeCodePopDlgMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeJumpToRoleReq(void* pHost, CNetData* poNetData);
int DeCodeJumpToRoleReq(void* pHost, CNetData* poNetData);
int EnCodeJumpToRoleAck(void* pHost, CNetData* poNetData);
int DeCodeJumpToRoleAck(void* pHost, CNetData* poNetData);
int EnCodeDragRoleNtf(void* pHost, CNetData* poNetData);
int DeCodeDragRoleNtf(void* pHost, CNetData* poNetData);
int EnCodeLogInfo(void* pHost, CNetData* poNetData);
int DeCodeLogInfo(void* pHost, CNetData* poNetData);
int EnCodeRoleCallBackNtf(void* pHost, CNetData* poNetData);
int DeCodeRoleCallBackNtf(void* pHost, CNetData* poNetData);
int EnCodeStopSvrNtf(void* pHost, CNetData* poNetData);
int DeCodeStopSvrNtf(void* pHost, CNetData* poNetData);
int EnCodeGenServantResult(void* pHost, CNetData* poNetData);
int DeCodeGenServantResult(void* pHost, CNetData* poNetData);
int EnCodeCastleOwnerNtf(void* pHost, CNetData* poNetData);
int DeCodeCastleOwnerNtf(void* pHost, CNetData* poNetData);
int EnCodeGSTrigScriptNtf(void* pHost, CNetData* poNetData);
int DeCodeGSTrigScriptNtf(void* pHost, CNetData* poNetData);
int EnCodeEscortFailNtf(void* pHost, CNetData* poNetData);
int DeCodeEscortFailNtf(void* pHost, CNetData* poNetData);
int EnCodeBoardMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeBoardMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeDummyJumpMapBrd(void* pHost, CNetData* poNetData);
int DeCodeDummyJumpMapBrd(void* pHost, CNetData* poNetData);
int EnCodeDummyStateSwitchBrd(void* pHost, CNetData* poNetData);
int DeCodeDummyStateSwitchBrd(void* pHost, CNetData* poNetData);
int EnCodeDummyQuitBrd(void* pHost, CNetData* poNetData);
int DeCodeDummyQuitBrd(void* pHost, CNetData* poNetData);
int EnCodeGS2GTNtf(void* pHost, CNetData* poNetData);
int DeCodeGS2GTNtf(void* pHost, CNetData* poNetData);
//===============打包解包函数定义结束===============
typedef int (*EnCodeFuncGlobal)(void *pHost, CNetData* poNetData);
typedef int (*DeCodeFuncGlobal)(void *pHost, CNetData* poNetData);

class CGlobal
{
public:
	CGlobal();
	~CGlobal();
	int BuildProtocol(void* pHost, char *pNet, int iNetSize);

	bool HandleProtocol(char *pNet, int iNetSize, void* pHost);

	static inline unsigned short GetModuleID(void){ return 7; }

	static inline unsigned short GetProtocolNum(void){ return 28; }

	static const unsigned short module_id = 7;

	static const unsigned short protocol_num = 28;

//===============以下协议回调函数需要使用者来实现===============
	virtual void OnRecv_ErrorAck(ErrorAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GenServantNtf(GenServantNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_KillServantNtf(KillServantNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ServantDieNtf(ServantDieNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ServantModeNtf(ServantModeNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ServantModeResult(ServantModeResult& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DgnCreateRpt(DgnCreateRpt& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DgnDestroyRpt(DgnDestroyRpt& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TipsMsgNtf(TipsMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TopMsgNtf(TopMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CenterMsgNtf(CenterMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BottomMsgNtf(BottomMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PopDlgMsgNtf(PopDlgMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_JumpToRoleReq(JumpToRoleReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_JumpToRoleAck(JumpToRoleAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DragRoleNtf(DragRoleNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_LogInfo(LogInfo& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RoleCallBackNtf(RoleCallBackNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_StopSvrNtf(StopSvrNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GenServantResult(GenServantResult& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CastleOwnerNtf(CastleOwnerNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GSTrigScriptNtf(GSTrigScriptNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EscortFailNtf(EscortFailNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_BoardMsgNtf(BoardMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyJumpMapBrd(DummyJumpMapBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyStateSwitchBrd(DummyStateSwitchBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DummyQuitBrd(DummyQuitBrd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GS2GTNtf(GS2GTNtf& rstProtocol){ rstProtocol; };
private:
	EnCodeFuncGlobal m_EnCodeFuncArray[28];
	EnCodeFuncGlobal m_DeCodeFuncArray[28];
};
