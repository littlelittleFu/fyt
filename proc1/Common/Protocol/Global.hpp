#pragma once

#include "netdata.h"

//===============����������Э���ļ�===============
#include "DataInfo.hpp"
 //===============�궨�忪ʼ===============
//===============�궨�����===============

//===============���ݶ��忪ʼ===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct ErrorAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       ecode; //������
	uint64_t                  guid; //guid
	char                      detail[256]; //��������
	ErrorAck():moudleid(7),protocolid(0){}
};

struct GenServantNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //���˵�GUID
	SERVANT_INFO              servant; //�����Ϣ
	GenServantNtf():moudleid(7),protocolid(1){}
};

struct KillServantNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //���˵�GUID
	uint64_t                  servant_guid; //�����Ϣ
	KillServantNtf():moudleid(7),protocolid(2){}
};

struct ServantDieNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //���˵�GUID
	uint64_t                  servant_guid; //�����Ϣ
	ServantDieNtf():moudleid(7),protocolid(3){}
};

struct ServantModeNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             mode; //���˵�ģʽ 0=ս�� 1=��Ϣ
	uint64_t                  master_guid; //���˵�GUID
	uint64_t                  servant_guid; //�����Ϣ
	ServantModeNtf():moudleid(7),protocolid(4){}
};

struct ServantModeResult{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  master_guid; //���˵�GUID
	uint64_t                  servant_guid; //�����Ϣ
	unsigned char             result; //���˵�ģʽ 0=�Ҳ�����ӡ�ʧ�� 1=ģʽ����ɹ�
	ServantModeResult():moudleid(7),protocolid(5){}
};

struct DgnCreateRpt{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  map_code; //������ͼ����
	unsigned short            dgn_id; //����ģ��id
	unsigned int              create_time; //��������ʱ��
	unsigned int              life_time; //������������
	unsigned char             load_grid; //�Ƿ�����߼��� 0=�� 1=��
	DgnCreateRpt():moudleid(7),protocolid(6){}
};

struct DgnDestroyRpt{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  map_code; //������ͼ����
	DgnDestroyRpt():moudleid(7),protocolid(7){}
};

struct TipsMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      msg[256]; //��Ϣ����
	TipsMsgNtf():moudleid(7),protocolid(8){}
};

struct TopMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             foreground; //��Ϣǰ����ɫID
	unsigned char             background; //��Ϣ������ɫID
	unsigned char             count; //��Ϣ��������
	char                      msg[256]; //��Ϣ����
	TopMsgNtf():moudleid(7),protocolid(9){}
};

struct CenterMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             foreground; //��Ϣǰ����ɫID
	unsigned char             background; //��Ϣ������ɫID
	char                      msg[256]; //��Ϣ����
	CenterMsgNtf():moudleid(7),protocolid(10){}
};

struct BottomMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             foreground; //��Ϣǰ����ɫID
	unsigned char             background; //��Ϣ������ɫID
	char                      msg[256]; //��Ϣ����
	BottomMsgNtf():moudleid(7),protocolid(11){}
};

struct PopDlgMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      msg[256]; //��Ϣ����
	PopDlgMsgNtf():moudleid(7),protocolid(12){}
};

struct JumpToRoleReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      role_name[256]; //�Է���ɫ������
	uint64_t                  self_guid; //���ѵ�GUID
	JumpToRoleReq():moudleid(7),protocolid(13){}
};

struct JumpToRoleAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  map_guid; //�Է���ͼGUID
	unsigned short            pos_x; //�Է���ͼx����
	unsigned short            pos_y; //�Է���ͼy����
	uint64_t                  self_guid; //�Լ���GUID
	JumpToRoleAck():moudleid(7),protocolid(14){}
};

struct DragRoleNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      role_name[256]; //�Է���ɫ������
	char                      self_name[256]; //���ѽ�ɫ������
	DragRoleNtf():moudleid(7),protocolid(15){}
};

struct LogInfo{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      role_name[256]; //��ɫ������
	int                       action; //����
	char                      map_name[256]; //��ͼ����
	unsigned short            x; //x
	unsigned short            y; //y
	char                      item_name[256]; //��Ʒ����
	uint64_t                  item_guid; //��Ʒguid
	char                      target_name[256]; //Ŀ������
	int64_t                   src_value; //ԭ����
	int64_t                   ref_value; //�ı���
	char                      descript[256]; //����
	unsigned int              create_time; //����ʱ��
	char                      detail[32768]; //ϸ��
	LogInfo():moudleid(7),protocolid(16){}
};

struct RoleCallBackNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //��GUID
	char                      callback[256]; //�ص����� ��ʽ���ļ�:������
	char                      param[256]; //�ص������Ĳ���
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
	uint64_t                  master_guid; //���˵�GUID
	uint64_t                  servant_guid; //�����Ϣ
	unsigned char             result; //0=����ʧ�� 1=���ɳɹ�
	GenServantResult():moudleid(7),protocolid(19){}
};

struct CastleOwnerNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      castle_name[256]; //�Ǳ�����
	char                      family_name[256]; //�л�����
	CastleOwnerNtf():moudleid(7),protocolid(20){}
};

struct GSTrigScriptNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      callback[256]; //�ص�����
	unsigned short            param_len; //��������
	unsigned char             param[1024]; //����
	GSTrigScriptNtf():moudleid(7),protocolid(21){}
};

struct EscortFailNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  escorter; //�ڳ����˵�GUID
	EscortFailNtf():moudleid(7),protocolid(22){}
};

struct BoardMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      title[256]; //��Ϣ����
	char                      msg[256]; //��Ϣ����
	unsigned int              timeout; //��Ϣ����ʱ��
	BoardMsgNtf():moudleid(7),protocolid(23){}
};

struct DummyJumpMapBrd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  dummy_guid; //����guid
	uint64_t                  map_guid; //Ŀ��map��guid
	unsigned short            map_x; //Ŀ������
	unsigned short            map_y; //Ŀ������
	uint64_t                  lord_guid; //���Ʒ�guid, û����0
	char                      json_added[1024]; //������ʱ���ݣ�json��ʽ
	DummyJumpMapBrd():moudleid(7),protocolid(24){}
};

struct DummyStateSwitchBrd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  dummy_guid; //����guid
	uint64_t                  player_guid; //����guid
	DummyStateSwitchBrd():moudleid(7),protocolid(25){}
};

struct DummyQuitBrd{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  dummy_guid; //����guid
	unsigned int              dummy_login_time; //��������ʱ��
	uint64_t                  player_guid; //����guid
	DummyQuitBrd():moudleid(7),protocolid(26){}
};

struct GS2GTNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned short            int_count; //�������ݸ���
	IntData                   int_data[256]; //����ֵ
	unsigned short            str_count; //�ַ������ݸ���
	StrData                   str_data[256]; //����ֵ
	GS2GTNtf():moudleid(7),protocolid(27){}
};

#pragma warning( pop ) 
//===============���ݶ������===============
//===============�������������忪ʼ===============
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
//===============�����������������===============
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

//===============����Э��ص�������Ҫʹ������ʵ��===============
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
