#pragma once
#include <unordered_map>


struct MapServer
{
	uint32_t  mSessionID;      // ���ķ��������ͼ������֮���session id
	std::string m_Ip;
	uint32_t m_Port;
};

//ssignMapServer �����������map server����ȻĿǰ���ֻ��һ̨map server������֧�ֺ�����̨map server�ļܹ��������ҿ��Ծ�����ҽ����ͼ��
class AssignMapServer
{
	DECL_SINGLETON(AssignMapServer);
public:


	MapServer& GetMapServerById(uint16_t id);
	void  UpdateMapServerTableById(const uint16_t & id, MapServer mapserver);
	const std::unordered_map<uint16_t, MapServer> &  GetMapServerTable() const { return mMapServerTable; }
private:
	AssignMapServer() {};
	~AssignMapServer() {};
	std::unordered_map<uint16_t, MapServer> mMapServerTable;//ά��һ�ű�����ͼID��map server��
};


