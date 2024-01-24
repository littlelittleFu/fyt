#pragma once

//===============����������Э���ļ�===============

 //===============�궨�忪ʼ===============
//===============�궨�����===============

//===============���ݶ��忪ʼ===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct LoginReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      UserName[256]; //�˺���
	unsigned int              ip; //��½ip��ַ
	unsigned int              pwd_len; //�������ĳ���
	unsigned char             password[128]; //��������
	char                      hwid[256]; //Ӳ����
	LoginReq():moudleid(1),protocolid(0){}
};

struct LoginAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              dbobjid; //�ͻ�����DB�ϵ�objid
	int                       errcode; //������
	char                      errmsg[256]; //��������
	LoginAck():moudleid(1),protocolid(1){}
};

struct LogoutRpt{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             info; //�ǳ�����
	LogoutRpt():moudleid(1),protocolid(2){}
};

struct CreateRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	ROLE_BRIEF_INFO           createrole; //�½���ɫ�Ļ�����Ϣ
	CreateRoleReq():moudleid(1),protocolid(3){}
};

struct CreateRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //������
	char                      errmsg[256]; //��������
	ROLE_BRIEF_INFO           newrole; //��ɫ��Ҫ��Ϣ�б�
	CreateRoleAck():moudleid(1),protocolid(4){}
};

struct DeleteRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //Ҫɾ���Ľ�ɫguid
	DeleteRoleReq():moudleid(1),protocolid(5){}
};

struct DeleteRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //��ɾ���Ľ�ɫguid
	int                       errcode; //������
	char                      errmsg[256]; //��������
	DeleteRoleAck():moudleid(1),protocolid(6){}
};

struct RecoverRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //Ҫ�ָ��Ľ�ɫguid
	RecoverRoleReq():moudleid(1),protocolid(7){}
};

struct RecoverRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //������
	char                      errmsg[256]; //��������
	ROLE_BRIEF_INFO           recoverrole; //��ɫ��Ҫ��Ϣ�б�
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
	int                       errcode; //������
	char                      errmsg[256]; //��������
	unsigned char             rolenum; //��ɫ�б��еĽ�ɫ����
	uint64_t                  last_role; //�ϴ�ѡ���ɫ
	ROLE_BRIEF_INFO           rolelist[10]; //��ɫ��Ҫ��Ϣ�б�
	GetRoleListAck():moudleid(1),protocolid(10){}
};

struct KickUserNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //������
	char                      errmsg[256]; //��������
	KickUserNtf():moudleid(1),protocolid(11){}
};

struct RandKeyNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              code_len; //�����Կ����
	unsigned char             code[128]; //�����Կ
	RandKeyNtf():moudleid(1),protocolid(12){}
};

struct ReLoginReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              user_id; //�˺�id
	char                      session_key[256]; //�Ự��Կ
	ReLoginReq():moudleid(1),protocolid(13){}
};

struct ReLoginAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       errcode; //������
	char                      errmsg[256]; //��������
	ReLoginAck():moudleid(1),protocolid(14){}
};

struct LoginReq3rd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      user_name[256]; //�û���
	unsigned int              token_len; //token����
	unsigned char             token[16384]; //token
	char                      platform[256]; //ƽ̨����
	unsigned int              login_ip; //��½ip
	char                      hwid[256]; //Ӳ����
	LoginReq3rd():moudleid(1),protocolid(15){}
};

struct EncryptNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              encode_len; //���ܺ�������
	unsigned char             encode_data[4096]; //data
	unsigned int              decode_len; //�����ܺ�������
	unsigned char             decode_data[4096]; //data
	EncryptNtf():moudleid(1),protocolid(16){}
};

struct KickUserReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              user_id; //�˺�id
	int                       errcode; //������
	char                      errmsg[256]; //��������
	KickUserReq():moudleid(1),protocolid(17){}
};

struct KickUserAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              user_id; //�˺�id
	int                       errcode; //������
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
	unsigned char             type; //0�ͻ��� 1ҳ�� 2����
	ClientTypeNtf():moudleid(1),protocolid(21){}
};

struct GTLoginReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      UserName[256]; //�˺���
	unsigned int              ip; //��½ip��ַ
	unsigned int              pwd_len; //�������ĳ���
	unsigned char             password[128]; //��������
	char                      hwid[256]; //Ӳ����
	char                      platform[256]; //ƽ̨����
	char                      platform_info[4096]; //ƽ̨������Ϣ
	GTLoginReq():moudleid(1),protocolid(22){}
};

#pragma warning( pop ) 
//===============���ݶ������===============
//===============�������������忪ʼ===============
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

//===============�����������������===============
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

	static const unsigned short protocol_num = 23;//��������д�����ã��������Ż�

//===============����Э��ص�������Ҫʹ������ʵ��===============
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
