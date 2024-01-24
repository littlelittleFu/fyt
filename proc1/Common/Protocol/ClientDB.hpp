#pragma once

//===============包含的其他协议文件===============

 //===============宏定义开始===============
//===============宏定义结束===============

//===============数据定义开始===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct LoginReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      UserName[256]; //账号名
	unsigned int              ip; //登陆ip地址
	unsigned int              pwd_len; //密码密文长度
	unsigned char             password[128]; //密码密文
	char                      hwid[256]; //硬件码
	LoginReq():moudleid(1),protocolid(0){}
};

struct LoginAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              dbobjid; //客户端在DB上的objid
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	LoginAck():moudleid(1),protocolid(1){}
};

struct LogoutRpt{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             info; //登出类型
	LogoutRpt():moudleid(1),protocolid(2){}
};

struct CreateRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	ROLE_BRIEF_INFO           createrole; //新建角色的基础信息
	CreateRoleReq():moudleid(1),protocolid(3){}
};

struct CreateRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	ROLE_BRIEF_INFO           newrole; //角色简要信息列表
	CreateRoleAck():moudleid(1),protocolid(4){}
};

struct DeleteRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //要删除的角色guid
	DeleteRoleReq():moudleid(1),protocolid(5){}
};

struct DeleteRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //被删除的角色guid
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	DeleteRoleAck():moudleid(1),protocolid(6){}
};

struct RecoverRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //要恢复的角色guid
	RecoverRoleReq():moudleid(1),protocolid(7){}
};

struct RecoverRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	ROLE_BRIEF_INFO           recoverrole; //角色简要信息列表
	RecoverRoleAck():moudleid(1),protocolid(8){}
};

struct GetRoleListReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	GetRoleListReq():moudleid(1),protocolid(9){}
};

struct GetRoleListAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	unsigned char             rolenum; //角色列表中的角色数量
	uint64_t                  last_role; //上次选择角色
	ROLE_BRIEF_INFO           rolelist[10]; //角色简要信息列表
	GetRoleListAck():moudleid(1),protocolid(10){}
};

struct KickUserNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	KickUserNtf():moudleid(1),protocolid(11){}
};

struct RandKeyNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              code_len; //随机密钥长度
	unsigned char             code[128]; //随机密钥
	RandKeyNtf():moudleid(1),protocolid(12){}
};

struct ReLoginReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              user_id; //账号id
	char                      session_key[256]; //会话密钥
	ReLoginReq():moudleid(1),protocolid(13){}
};

struct ReLoginAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	ReLoginAck():moudleid(1),protocolid(14){}
};

struct LoginReq3rd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      user_name[256]; //用户名
	unsigned int              token_len; //token长度
	unsigned char             token[16384]; //token
	char                      platform[256]; //平台名称
	unsigned int              login_ip; //登陆ip
	char                      hwid[256]; //硬件码
	LoginReq3rd():moudleid(1),protocolid(15){}
};

struct EncryptNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              encode_len; //加密函数长度
	unsigned char             encode_data[4096]; //data
	unsigned int              decode_len; //解密密函数长度
	unsigned char             decode_data[4096]; //data
	EncryptNtf():moudleid(1),protocolid(16){}
};

struct KickUserReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              user_id; //账号id
	int                       errcode; //错误码
	char                      errmsg[256]; //错误描述
	KickUserReq():moudleid(1),protocolid(17){}
};

struct KickUserAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              user_id; //账号id
	int                       errcode; //错误码
	KickUserAck():moudleid(1),protocolid(18){}
};

struct HeartBeatReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	HeartBeatReq():moudleid(1),protocolid(19){}
};

struct HeartBeatAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	HeartBeatAck():moudleid(1),protocolid(20){}
};

struct ClientTypeNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //0客户端 1页游 2手游
	ClientTypeNtf():moudleid(1),protocolid(21){}
};

struct GTLoginReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      UserName[256]; //账号名
	unsigned int              ip; //登陆ip地址
	unsigned int              pwd_len; //密码密文长度
	unsigned char             password[128]; //密码密文
	char                      hwid[256]; //硬件码
	char                      platform[256]; //平台名称
	char                      platform_info[4096]; //平台额外信息
	GTLoginReq():moudleid(1),protocolid(22){}
};

#pragma warning( pop ) 
//===============数据定义结束===============
//===============打包解包函数定义开始===============
int EnCodeLoginReq(void* pHost, CNetData* poNetData);
int DeCodeLoginReq(void* pHost, CNetData* poNetData);
int EnCodeLoginAck(void* pHost, CNetData* poNetData);
int DeCodeLoginAck(void* pHost, CNetData* poNetData);
int EnCodeLogoutRpt(void* pHost, CNetData* poNetData);
int DeCodeLogoutRpt(void* pHost, CNetData* poNetData);
int EnCodeCreateRoleReq(void* pHost, CNetData* poNetData);
int DeCodeCreateRoleReq(void* pHost, CNetData* poNetData);
int EnCodeCreateRoleAck(void* pHost, CNetData* poNetData);
int DeCodeCreateRoleAck(void* pHost, CNetData* poNetData);
int EnCodeDeleteRoleReq(void* pHost, CNetData* poNetData);
int DeCodeDeleteRoleReq(void* pHost, CNetData* poNetData);
int EnCodeDeleteRoleAck(void* pHost, CNetData* poNetData);
int DeCodeDeleteRoleAck(void* pHost, CNetData* poNetData);
int EnCodeRecoverRoleReq(void* pHost, CNetData* poNetData);
int DeCodeRecoverRoleReq(void* pHost, CNetData* poNetData);
int EnCodeRecoverRoleAck(void* pHost, CNetData* poNetData);
int DeCodeRecoverRoleAck(void* pHost, CNetData* poNetData);
int EnCodeGetRoleListReq(void* pHost, CNetData* poNetData);
int DeCodeGetRoleListReq(void* pHost, CNetData* poNetData);
int EnCodeGetRoleListAck(void* pHost, CNetData* poNetData);
int DeCodeGetRoleListAck(void* pHost, CNetData* poNetData);
int EnCodeKickUserNtf(void* pHost, CNetData* poNetData);
int DeCodeKickUserNtf(void* pHost, CNetData* poNetData);
int EnCodeRandKeyNtf(void* pHost, CNetData* poNetData);
int DeCodeRandKeyNtf(void* pHost, CNetData* poNetData);
int EnCodeReLoginReq(void* pHost, CNetData* poNetData);
int DeCodeReLoginReq(void* pHost, CNetData* poNetData);
int EnCodeReLoginAck(void* pHost, CNetData* poNetData);
int DeCodeReLoginAck(void* pHost, CNetData* poNetData);
int EnCodeLoginReq3rd(void* pHost, CNetData* poNetData);
int DeCodeLoginReq3rd(void* pHost, CNetData* poNetData);
int EnCodeEncryptNtf(void* pHost, CNetData* poNetData);
int DeCodeEncryptNtf(void* pHost, CNetData* poNetData);
int EnCodeKickUserReq(void* pHost, CNetData* poNetData);
int DeCodeKickUserReq(void* pHost, CNetData* poNetData);
int EnCodeKickUserAck(void* pHost, CNetData* poNetData);
int DeCodeKickUserAck(void* pHost, CNetData* poNetData);
int EnCodeHeartBeatReq(void* pHost, CNetData* poNetData);
int DeCodeHeartBeatReq(void* pHost, CNetData* poNetData);
int EnCodeHeartBeatAck(void* pHost, CNetData* poNetData);
int DeCodeHeartBeatAck(void* pHost, CNetData* poNetData);
int EnCodeClientTypeNtf(void* pHost, CNetData* poNetData);
int DeCodeClientTypeNtf(void* pHost, CNetData* poNetData);
int EnCodeGTLoginReq(void* pHost, CNetData* poNetData);
int DeCodeGTLoginReq(void* pHost, CNetData* poNetData);

//===============打包解包函数定义结束===============
//std::function<int(void* pHost, CNetData* poNetData)>EnCodeFuncClientDBs;
typedef int (*EnCodeFuncClientDB)(void *pHost, CNetData* poNetData);
typedef int (*DeCodeFuncClientDB)(void *pHost, CNetData* poNetData);

class CClientDB
{
public:
	CClientDB();
	~CClientDB();
	int BuildProtocol(void* pHost, char *pNet, int iNetSize);

	bool HandleProtocol(char *pNet, int iNetSize, void* pHost);

	static inline unsigned short GetModuleID(void){ return 1; }

	static inline unsigned short GetProtocolNum(void){ return 23; }

	static const unsigned short module_id = 1;

	static const unsigned short protocol_num = 23;//代码这里写死不好，后面再优化

//===============以下协议回调函数需要使用者来实现===============
	virtual void OnRecv_LoginReq(LoginReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_LoginAck(LoginAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_LogoutRpt(LogoutRpt& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CreateRoleReq(CreateRoleReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CreateRoleAck(CreateRoleAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DeleteRoleReq(DeleteRoleReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_DeleteRoleAck(DeleteRoleAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RecoverRoleReq(RecoverRoleReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RecoverRoleAck(RecoverRoleAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetRoleListReq(GetRoleListReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetRoleListAck(GetRoleListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_KickUserNtf(KickUserNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RandKeyNtf(RandKeyNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ReLoginReq(ReLoginReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ReLoginAck(ReLoginAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_LoginReq3rd(LoginReq3rd& rstProtocol){ rstProtocol; };
	virtual void OnRecv_EncryptNtf(EncryptNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_KickUserReq(KickUserReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_KickUserAck(KickUserAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeartBeatReq(HeartBeatReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_HeartBeatAck(HeartBeatAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ClientTypeNtf(ClientTypeNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GTLoginReq(GTLoginReq& rstProtocol){ rstProtocol; };
	
private:
	EnCodeFuncClientDB m_EnCodeFuncArray[protocol_num];
	EnCodeFuncClientDB m_DeCodeFuncArray[protocol_num];
};
