/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
--auther:   szg
--time:     2017.9.16  12:47
--desc:     find path on map
--++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "stdafx.h"
#include "AStarPathFinder.h"
#include <math.h>
#include"Monster.h"

IMPL_SINGLETON(CAStarPathFinder);

CAStarPathFinder::CAStarPathFinder()
{

}

CAStarPathFinder::~CAStarPathFinder()
{
    Reset();
}

bool CAStarPathFinder::Init(int nWTiles,int nHTiles,int nTileSize)
{
    m_nWTiles                           = nWTiles;
    m_nHTiles                           = nHTiles;
    m_nTileSize                         = nTileSize;

	m_WhichList                         = new int16_t[int64_t(m_nWTiles) * m_nHTiles];
	m_OpenListMinBinaryHeap             = new int16_t[int64_t(m_nWTiles) * m_nHTiles];

	m_NodeX                             = new int16_t[int64_t(m_nWTiles) * m_nHTiles];
	m_NodeY                             = new int16_t[int64_t(m_nWTiles) * m_nHTiles];

	m_nOnCloseList                      = 10;
	m_nOnOpenList                       = m_nOnCloseList - 1;

	m_FCost                             = new int16_t[int64_t(m_nWTiles) * m_nHTiles];
	m_GCost                             = new int16_t[int64_t(m_nWTiles) * m_nHTiles];
	m_HCost                             = new int16_t[int64_t(m_nWTiles) * m_nHTiles];

	m_ParentX                           = new int16_t[int64_t(m_nWTiles) * m_nHTiles];
	m_ParentY                           = new int16_t[int64_t(m_nWTiles) * m_nHTiles];

	memset(m_WhichList, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_OpenListMinBinaryHeap, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_NodeX, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_NodeY, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_FCost, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_GCost, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_HCost, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_ParentX, 0, sizeof(int16_t) * nWTiles * nHTiles);
	memset(m_ParentY, 0, sizeof(int16_t) * nWTiles * nHTiles);

    return true;
}

void CAStarPathFinder::Reset()
{
	SAFE_DELETE_ARRAY(m_WhichList);
	SAFE_DELETE_ARRAY(m_OpenListMinBinaryHeap);
	SAFE_DELETE_ARRAY(m_NodeX);
	SAFE_DELETE_ARRAY(m_NodeY);
	SAFE_DELETE_ARRAY(m_FCost);
	SAFE_DELETE_ARRAY(m_GCost);
	SAFE_DELETE_ARRAY(m_HCost);
	SAFE_DELETE_ARRAY(m_ParentX);
	SAFE_DELETE_ARRAY(m_ParentY);
}

void CAStarPathFinder::Clear()
{
    m_PathList.clear();
}

FindPathResult CAStarPathFinder::FindPathToTarget(int nStartX,int nStartY,int nTargetX,int nTargetY,int nDepth, bool avoidTrap, Map* curmap)
{
    if(nStartX < 0 || nStartX >= m_nWTiles)
        return path_none_exist;
    if (nStartY < 0 || nStartY >= m_nHTiles)
        return path_none_exist;
    if(nTargetX < 0 || nTargetX >= m_nWTiles)
        return path_none_exist;
    if (nTargetY < 0 || nTargetY >= m_nHTiles)
        return path_none_exist;
    if (!curmap) return path_none_exist;
    auto &mapGrid = curmap->GetMapGrid();
    int nStartTileX = nStartX;
    int nStartTileY = nStartY;
    int nTargetTileX = nTargetX;
    int nTargetTileY = nTargetY;

    if(nStartTileX == nTargetTileX && nStartTileY == nTargetTileY)
        return path_none_exist;

    if(m_nOnCloseList > 32760) {
        memset(m_WhichList, 0, sizeof(int16_t) * m_nWTiles * m_nHTiles);
        m_nOnCloseList = 10;
    }

    m_nOnCloseList = m_nOnCloseList + 2;
    m_nOnOpenList = m_nOnCloseList - 1;

    int nPathLenth = 0;
    int nOpenListItemCount = 1;
    int nNewNodeIDInHeap = 1;

    //1.将起始点放入开放列表
    m_OpenListMinBinaryHeap[1] = nNewNodeIDInHeap;
    m_NodeX[m_OpenListMinBinaryHeap[1]] = nStartTileX;
    m_NodeY[m_OpenListMinBinaryHeap[1]] = nStartTileY;

    //离目标点最近的节点和ID
    int nFindPathNearX = nStartTileX;
    int nFindPathNearY = nStartTileY;
    int nFindPathNearID = m_OpenListMinBinaryHeap[1];

    int nParentNodeX;
    int nParentNodeY;

    int nOriginHCost = (abs(nStartTileX - nTargetTileX) + abs(nStartTileY - nTargetTileY)) * 10;
	m_HCost[nFindPathNearID] = nOriginHCost;
    bool bFindFirst = false;

    //u和v用来给开放列表最小二叉堆排序，在循环外部申请可以提高寻路速度
    int u,v,nTemp;
    int a = 0, b = 0;
    bool bConorCheck;
    int nAddedGCost;
    int nTempGCost;
    int m;
    int x;
    //
    FindPathResult nResult = path_none_exist;
    while (true)
    {
        if(nOpenListItemCount > 0)
        {
            //取出开放列表中F值最小的节点，并把它放进关闭列表
            nParentNodeX = m_NodeX[m_OpenListMinBinaryHeap[1]];
            nParentNodeY = m_NodeY[m_OpenListMinBinaryHeap[1]];
            m_WhichList[nParentNodeX + nParentNodeY * m_nWTiles] = m_nOnCloseList;

            if(m_HCost[m_OpenListMinBinaryHeap[1]] < m_HCost[nFindPathNearID])
            {
                nFindPathNearX = nParentNodeX;
                nFindPathNearY = nParentNodeY;
                nFindPathNearID = m_OpenListMinBinaryHeap[1];
            }
            else if (m_HCost[m_OpenListMinBinaryHeap[1]] == m_HCost[nFindPathNearID])
            {
                if (m_FCost[m_OpenListMinBinaryHeap[1]] < m_FCost[nFindPathNearID])
                {
                    nFindPathNearX = nParentNodeX;
                    nFindPathNearY = nParentNodeY;
                    nFindPathNearID = m_OpenListMinBinaryHeap[1];
                }
                else if(!bFindFirst && m_HCost[m_OpenListMinBinaryHeap[1]] < nOriginHCost)
                {
                    if(nParentNodeX != nStartTileX || nParentNodeY != nStartTileY)
                    {
                        bFindFirst = true;
                        nFindPathNearX = nParentNodeX;
                        nFindPathNearY = nParentNodeY;
                        nFindPathNearID = m_OpenListMinBinaryHeap[1];
                    }
                }
            }

            //
            m_OpenListMinBinaryHeap[1] = m_OpenListMinBinaryHeap[nOpenListItemCount];
            nOpenListItemCount = nOpenListItemCount - 1;
            v = 1;
            do
            {
                u = v;
                if (nOpenListItemCount >= 2 * u + 1)
                {
                    if (m_FCost[m_OpenListMinBinaryHeap[u]] >= m_FCost[m_OpenListMinBinaryHeap[2 * u]])
                        v = 2 * u;
                    if (m_FCost[m_OpenListMinBinaryHeap[v]] >= m_FCost[m_OpenListMinBinaryHeap[2 * u + 1]])
                        v = 2 * u + 1;
                }
                else if (nOpenListItemCount >= 2 * u)
                {
                    if (m_FCost[m_OpenListMinBinaryHeap[u]] >= m_FCost[m_OpenListMinBinaryHeap[2 * u]])
                        v = 2 * u;
                }

                if (u != v)
                {
                    nTemp = m_OpenListMinBinaryHeap[u];
                    m_OpenListMinBinaryHeap[u] = m_OpenListMinBinaryHeap[v];
                    m_OpenListMinBinaryHeap[v] = nTemp;
                }
                else
                {
                    break;
                }
            } while (true);

            nPathLenth++;
            if(nPathLenth >= nDepth)
            {
                nResult = path_found_closest;
                return nResult;
                goto FindPathExit;
            }

            //遍历周围8个格子
            for(b = nParentNodeY-1;b <= nParentNodeY+1;b++)
            {
                for(a = nParentNodeX-1;a <= nParentNodeX+1;a++)
                {
                    if((a >= 0 && a < m_nWTiles) && (b >= 0 && b < m_nHTiles))
                    {
                        if(m_WhichList[a+b*m_nWTiles] != m_nOnCloseList)
                        {
                            if(!mapGrid.IsForbid(a,b) || (a == nTargetTileX && b == nTargetTileY))
                            {
                                bConorCheck = true;

                                if(m_WhichList[a+b*m_nWTiles] != m_nOnOpenList)
                                {
                                    //
                                    nNewNodeIDInHeap += 1;
                                    m = nOpenListItemCount + 1;
                                    m_OpenListMinBinaryHeap[m] = nNewNodeIDInHeap;
                                    m_NodeX[nNewNodeIDInHeap] = a;
                                    m_NodeY[nNewNodeIDInHeap] = b;

                                    if (abs(a - nParentNodeX) == 1 && abs(b - nParentNodeY) == 1)
                                        nAddedGCost = 10;
                                    else
                                        nAddedGCost = 10;
                                    if (avoidTrap)
                                    {
                                        if (curmap)
                                        {
                                            if (curmap->IsTrapPoint(a, b))
                                                nAddedGCost = 50;
                                             
                                        }
                                    }

                                    m_GCost[a + b * m_nWTiles] = m_GCost[nParentNodeX + nParentNodeY * m_nWTiles] + nAddedGCost;
                                    m_HCost[nNewNodeIDInHeap] = (abs(a - nTargetTileX) + abs(b - nTargetTileY)) * 10;
                                    m_FCost[nNewNodeIDInHeap] = m_GCost[a + b * m_nWTiles] + m_HCost[nNewNodeIDInHeap];
                                    m_ParentX[a + b * m_nWTiles] = nParentNodeX;
                                    m_ParentY[a + b * m_nWTiles] = nParentNodeY;

                                    while(m != 1)
                                    {
										int f1 = m_FCost[m_OpenListMinBinaryHeap[m]];
										int f2 = m_FCost[m_OpenListMinBinaryHeap[m / 2]];
                                        if(m_FCost[m_OpenListMinBinaryHeap[m]] <= m_FCost[m_OpenListMinBinaryHeap[m/2]])
                                        {
                                            nTemp = m_OpenListMinBinaryHeap[m/2];
                                            m_OpenListMinBinaryHeap[m/2] = m_OpenListMinBinaryHeap[m];
                                            m_OpenListMinBinaryHeap[m] = nTemp;
                                            m = m/2;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }

                                    nOpenListItemCount += 1;

                                    m_WhichList[a + b * m_nWTiles] = m_nOnOpenList;
                                }
                                else
                                {
                                    if (abs(a - nParentNodeX) == 1 && abs(b - nParentNodeY) == 1)
                                        nAddedGCost = 10;
                                    else
                                        nAddedGCost = 10;

                                    nTempGCost = m_GCost[nParentNodeX + nParentNodeY * m_nWTiles] + nAddedGCost;
                                    if(nTempGCost < m_GCost[a + b * m_nWTiles])
                                    {
                                        m_ParentX[a + b * m_nWTiles] = nParentNodeX;
                                        m_ParentY[a + b * m_nWTiles] = nParentNodeY;
                                        m_GCost[a + b * m_nWTiles] = nTempGCost;

                                        for(x = 1;x <= nOpenListItemCount;x++)
                                        {
                                            if(m_NodeX[m_OpenListMinBinaryHeap[x]] == a && m_NodeY[m_OpenListMinBinaryHeap[x]] == b)
                                            {
                                                m_FCost[m_OpenListMinBinaryHeap[x]] = m_GCost[a + b * m_nWTiles] + m_HCost[m_OpenListMinBinaryHeap[x]];

                                                m = x;

                                                while(m != 1)
                                                {
                                                    if (m_FCost[m_OpenListMinBinaryHeap[m]] < m_FCost[m_OpenListMinBinaryHeap[m/2]])
                                                    {
                                                        nTemp = m_OpenListMinBinaryHeap[m/2];
                                                        m_OpenListMinBinaryHeap[m/2] = m_OpenListMinBinaryHeap[m];
                                                        m_OpenListMinBinaryHeap[m] = nTemp;
                                                        m = m/2;
                                                    }
                                                    else
                                                    {
                                                        break;
                                                    }
                                                }

                                                break;
                                            }
                                        }
                                    }
                                }
                                
                            }
                        }
                    }
                }
            }
        }
        else
        {
            nResult = path_found_closest;
            break;
        }

        if(m_WhichList[nTargetTileX + nTargetTileY * m_nWTiles] == m_nOnOpenList)
        {
            nResult = path_found_target;
            break;
        }
    }

FindPathExit:
    int nTempTargetX = -1;
    int nTempTargetY = -1;
    if(nResult == path_found_target)
    {
        nTempTargetX = nTargetTileX;
        nTempTargetY = nTargetTileY;
    }
    else if(nResult == path_found_closest)
    {
        if(nFindPathNearID > 1)
        {
            nTempTargetX = nFindPathNearX;
            nTempTargetY = nFindPathNearY;
        }
        else
        {
            return path_none_exist;
        }
    }

    //
    m_PathList.clear();
    int nPathX = nTempTargetX, nPathY = nTempTargetY;
    m_PathList.push_front(stTilePoint(nPathX, nPathY));
    do
    {
        int nTempPathX = m_ParentX[nPathX + nPathY * m_nWTiles];
        int nTempPathY = m_ParentY[nPathX + nPathY * m_nWTiles];
		nPathX = nTempPathX;
		nPathY = nTempPathY;

		m_PathList.push_front(stTilePoint(nPathX, nPathY));

        if(nPathX == nStartTileX && nPathY == nStartTileY)
        {
            break;
        }
    } while (true);

    //优化最终的路径
   // OptimizePath(nIgnoreType);

    return nResult;
}

void CAStarPathFinder::InterpolatePath(std::vector<std::pair<int, int>>& list_pos)
{
	int path_count = list_pos.size();
	if (path_count < 2)
		return;

	std::vector<std::pair<int, int>> temp_list;
	float x, y;
	
	for (int i = 0; i < path_count - 1; ++i)
	{
		temp_list.push_back(list_pos[i]);

        std::pair<int, int> cur = list_pos[i];
        std::pair<int, int> next = list_pos[i+1];
		
		int cur_tile_x = cur.first / m_nTileSize;
		int cur_tile_y = cur.second / m_nTileSize;
		int next_tile_x = next.first / m_nTileSize;
		int next_tile_y = next.second / m_nTileSize;

		x = cur.first;
		y = cur.second;

		if(abs(cur_tile_x - next_tile_x) <= 1 && abs(cur_tile_y - next_tile_y) <= 1)
			continue;

		if (abs(cur_tile_x - next_tile_x) >= abs(cur_tile_y - next_tile_y))
		{
			float delta = (next.first - cur.second) / (next.first - cur.second);
			if (cur_tile_x < next_tile_x)
			{
				do
				{
					x += m_nTileSize;
					
					if (x < next.first)
					{
						y = delta * (x - cur.first) + cur.second;
						temp_list.push_back(std::make_pair(x,y));
					}
					else
					{
						break;
					}
				} while (true);
			}
			else
			{
				do
				{
					x -= m_nTileSize;

					if (x > next.first)
					{
						y = delta * (x - cur.first) + cur.second;
						temp_list.push_back(std::make_pair(x, y));
					}
					else
					{
						break;
					}
					
				} while (true);
			}
			
		}
		else
		{
			float delta = (next.first - cur.second) / (next.first - cur.second);
			if (cur_tile_y < next_tile_y)
			{
				do
				{
					y += m_nTileSize;

					if (y < next.second)
					{
						x = delta * (y - cur.second) + cur.first;
						temp_list.push_back(std::make_pair(x, y));
					}
					else
					{
						break;
					}
					
				} while (true);
			}
			else
			{
				do
				{
					y -= m_nTileSize;
					if (y > next.second)
					{
						x = delta * (y - cur.second) + cur.first;
						temp_list.push_back(std::make_pair(x, y));
					}
					else
					{
						break;
					}
					
				} while (true);
			}

		}
	}

	temp_list.push_back(list_pos[path_count-1]);

	list_pos.clear();

	for (int i = 0; i < temp_list.size(); ++i)
	{
		list_pos.push_back(temp_list[i]);
	}

	temp_list.clear();
}

void CAStarPathFinder::GetFinalPath(std::vector<std::pair<int, int>>& list_pos)
{
    for(std::list<stTilePoint>::iterator itr = m_PathList.begin();itr != m_PathList.end();++itr)
    {
        stTilePoint& tile_point = *itr;
		std::pair<int,int> _stPos;

        _stPos.first = tile_point.x * m_nTileSize + 0.5f * m_nTileSize;
        _stPos.second = tile_point.y * m_nTileSize + 0.5f * m_nTileSize;

        list_pos.push_back(_stPos);
    }

	InterpolatePath(list_pos);
}

FindPathResult CAStarPathFinder::FindPathToTarget(std::pair<int, int> posStart, std::pair<int, int> posEnd, int nDepth,bool avoidTrap, Map* curmap)
{
	int nGridStartX = posStart.first / m_nTileSize;
	int nGridStartY = posStart.second / m_nTileSize;
	int nGridEndX = posEnd.first / m_nTileSize;
	int nGridEndY = posEnd.second / m_nTileSize;
	auto result = FindPathToTarget(nGridStartX, nGridStartY, nGridEndX, nGridEndY, nDepth,avoidTrap, curmap);
	return result;
}

void CAStarPathFinder::FindPathCalcTimeBegin()
{
    m_TimeBegin = std::chrono::system_clock::now();
}

void CAStarPathFinder::FindPathCalcTimeEnd()
{
    m_TimeEnd = std::chrono::system_clock::now();
}

int CAStarPathFinder::GetPathCostTime()
{
    return (m_TimeEnd - m_TimeBegin).count();
}

bool CAStarPathFinder::IsStraightPath(int nStartX, int nStartY, int nTargetX,  int nTargetY, Monster* master, uint16_t dir)
{
    auto tmpPosX = nStartX + DirOffsetData[dir].XOffset;
    auto tmpPosY = nStartY + DirOffsetData[dir].YOffset;
    for (int i = 0; i < master->GetConfig()->TraRange; ++i) {
        if (tmpPosX == nTargetX && tmpPosY == nTargetY) {
            return true;
        }
        if (!master->CheckTakeGrid(tmpPosX, tmpPosY)) {
            return false;
        }
        if (master->IsMonster() && master->GetAIMonster()->IsAIAttrSet(monster_ai_mAvoidTrap))
        {
            if (master->GetAIMonster()->IsTrapPoint(tmpPosX, tmpPosY))
                return false;
        }
        dir = Utility::CalcRelativeDir(tmpPosX, tmpPosY, nTargetX, nTargetY);
        tmpPosX += DirOffsetData[dir].XOffset;
        tmpPosY += DirOffsetData[dir].YOffset;
    }
    return false;
}