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
//最大寻路深度
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

//障碍格类型
enum BlockType
{
	block_type_none = 0,    //非障碍
	block_type_dynamic = 1,    //动态障碍
	block_type_highland = 2,    //高地障碍
	block_type_abs = 3,    //绝对不能通过障碍
};

//寻路结果
enum FindPathResult
{
	path_none_exist = 0,    //搜索路径失败
	path_found_closest,     //目标点不可达，找到最接近目标点的路径
	path_found_target,      //找到可达目标点的路径
};

//路径点二维坐标(节点坐标)
struct stTilePoint
{
	int     x;
	int     y;

	stTilePoint() :x(0), y(0) {}
	stTilePoint(int x_, int y_) :x(x_), y(y_) {}
};

//路径点二维坐标(实际坐标)
struct stPos
{
	float     x;
	float     y;

	stPos() :x(0), y(0) {}
	stPos(float x_, float y_) :x(x_), y(y_) {}
};

//=======================================================
//A星寻路类
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

	//水平和竖直方向障碍格数量
	int m_nWTiles;
	int m_nHTiles;

	//障碍格大小
	int m_nTileSize;

	//开放列表和关闭列表标识
	int m_nOnCloseList;
	int m_nOnOpenList;

	//开放列表和关闭列表，通过标识确定节点是否在开放列表或者关闭列表
	int16_t* m_WhichList;

	//用于开放列表节点F值排序的最小二叉堆
	int16_t* m_OpenListMinBinaryHeap;

	//用于将二叉堆中的值对应到节点X和Y的数组
	int16_t* m_NodeX;
	int16_t* m_NodeY;

	int16_t* m_FCost;
	int16_t* m_GCost;
	int16_t* m_HCost;

	//父亲表
	int16_t* m_ParentX;
	int16_t* m_ParentY;

	std::list<stTilePoint> m_PathList;

	//寻路时间计算
	std::chrono::time_point<std::chrono::system_clock>  m_TimeBegin;
	std::chrono::time_point<std::chrono::system_clock>  m_TimeEnd;
};