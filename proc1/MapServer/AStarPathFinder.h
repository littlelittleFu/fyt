/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
--auther:   szg
--time:     2017.9.16  11:29
--desc:     find path on map
--++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#pragma once
#include "Types.h"
#include <list>
#include <vector>
#include <chrono>
#include <string>
#include "MapGrid.h"
//���Ѱ·���
#define MAX_PTH 10
#define MAX_DEPTH 80
#define GRID_SIZE 1
#define DIF_RANGE 1

class Monster;
#define SAFE_DELETE(p)          \
if(p != NULL)                   \
{                               \
    delete p;                   \
    p = NULL;                   \
}

#define SAFE_DELETE_ARRAY(p)    \
if(p != NULL)                   \
{                               \
    delete[] p;                 \
    p = NULL;                   \
}             

//�ϰ�������
enum BlockType
{
	block_type_none = 0,    //���ϰ�
	block_type_dynamic = 1,    //��̬�ϰ�
	block_type_highland = 2,    //�ߵ��ϰ�
	block_type_abs = 3,    //���Բ���ͨ���ϰ�
};

//Ѱ·���
enum FindPathResult
{
	path_none_exist = 0,    //����·��ʧ��
	path_found_closest,     //Ŀ��㲻�ɴ�ҵ���ӽ�Ŀ����·��
	path_found_target,      //�ҵ��ɴ�Ŀ����·��
};

//·�����ά����(�ڵ�����)
struct stTilePoint
{
	int     x;
	int     y;

	stTilePoint() :x(0), y(0) {}
	stTilePoint(int x_, int y_) :x(x_), y(y_) {}
};

//·�����ά����(ʵ������)
struct stPos
{
	float     x;
	float     y;

	stPos() :x(0), y(0) {}
	stPos(float x_, float y_) :x(x_), y(y_) {}
};

//=======================================================
//A��Ѱ·��
class CAStarPathFinder
{
    DECL_SINGLETON(CAStarPathFinder);

public:
	bool Init(int nWTiles, int nHTiles, int nTileSize);
	void Reset();
	void GetFinalPath(std::vector<std::pair<int, int>>& list_pos);
	FindPathResult FindPathToTarget(std::pair<int, int> posStart, std::pair<int, int> posEnd, int nDepth, bool avoidTrap,Map*curmap);
	FindPathResult FindPathToTarget(int nStartX, int nStartY, int nTargetX, int nTargetY, int nDepth, bool avoidTrap, Map* curmap);
	void FindPathCalcTimeBegin();
	void FindPathCalcTimeEnd();
	int GetPathCostTime();

	void Clear();
	static bool IsStraightPath(int nStartX, int nStartY, int nTargetX, int nTargetY, Monster* master, uint16_t dir);

protected:
	CAStarPathFinder();
	~CAStarPathFinder();
	void InterpolatePath(std::vector<std::pair<int, int>>& list_pos);

protected:

	//ˮƽ����ֱ�����ϰ�������
	int m_nWTiles;
	int m_nHTiles;

	//�ϰ����С
	int m_nTileSize;

	//�����б�͹ر��б��ʶ
	int m_nOnCloseList;
	int m_nOnOpenList;

	//�����б�͹ر��б�ͨ����ʶȷ���ڵ��Ƿ��ڿ����б���߹ر��б�
	int16_t* m_WhichList;

	//���ڿ����б�ڵ�Fֵ�������С�����
	int16_t* m_OpenListMinBinaryHeap;

	//���ڽ�������е�ֵ��Ӧ���ڵ�X��Y������
	int16_t* m_NodeX;
	int16_t* m_NodeY;

	int16_t* m_FCost;
	int16_t* m_GCost;
	int16_t* m_HCost;

	//���ױ�
	int16_t* m_ParentX;
	int16_t* m_ParentY;

	std::list<stTilePoint> m_PathList;

	//Ѱ·ʱ�����
	std::chrono::time_point<std::chrono::system_clock>  m_TimeBegin;
	std::chrono::time_point<std::chrono::system_clock>  m_TimeEnd;
};