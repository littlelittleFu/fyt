#include "stdafx.h"
#include "RoleMove.h"

#include "Role.h"
#include "Map.h"


#define MAX_MOVE_DIS		2

const DirOffset INVALID_DIR_OFFSET = DirOffset();

RoleMove::RoleMove(Role* master) : RoleAction(master)
, mIsMoving(false)
, mReady(true)
, mTarX(0)
, mTarY(0)
, mTimeElapsed(0)
{

}

RoleMove::~RoleMove()
{

}

bool RoleMove::Init()
{
	return true;
}

void RoleMove::Update(int32_t delta)
{
	UpdateMove(delta);
}

uint16_t RoleMove::MoveTo(uint16_t x, uint16_t y, uint8_t type)
{
	auto master = GetMaster();
	if (nullptr == master) {
		return error_move_role_not_exist;
	}

	auto map = master->GetCurMap();
	if (nullptr == map) {
		return error_move_map_not_exist;
	}

	if (x < 0 || x >= map->GetWidth() || y < 0 || y >= map->GetHeight()) {
		return error_move_point_forbid;
	}

	RoleState* roleState = master->GetRoleState();
	if (nullptr == roleState) {
		return error_move_role_not_exist;
	}

	if (role_state_stall == roleState->GetState()) {
		return error_move_stall;
	}

	if (role_state_rush == roleState->GetState()) {
		return error_move_rush;
	}

	if (role_state_back == roleState->GetState()) {
		return error_move_back;
	}

	RoleAttr* attr = master->GetRoleAttr();
	if (nullptr == attr) {
		return error_move_role_not_exist;
	}

	if (attr->GetRoleProp(role_can_walk) <= 0 && attr->GetRoleProp(role_can_run) <= 0) {
		return error_move_role_cant_move;
	}

	uint16_t x0 = 0, y0 = 0;
	attr->GetRolePos(x0, y0);
	if ((x == x0) && (y == y0)) {
		return error_move_same_pos;
	}

	if (!IsPointCanReach(x0, y0, x, y)) {
		return error_move_pos_cant_reach;
	}

    attr->SetMoveType(type);

	StartMove(x, y);
	if (master->IsPlayer()) {
		if (type == move_type_run)
		{
			UpdateMove(0);
		}
		UpdateMove(0);
	}
	return error_ok;
}

bool RoleMove::IsPointCanReach(uint16_t x0, uint16_t y0, uint16_t x, uint16_t y)
{
	int dis_x = std::abs(x - x0);
	int dis_y = std::abs(y - y0);
	if ((dis_x ==0) && (dis_y == 0)) {
		return false;
	}

	//判断是否超出移动的最大距离
	if (dis_x > MAX_MOVE_DIS || dis_y > MAX_MOVE_DIS) {
		return false;
	}

	//判断是否是8方向移动
	if ((dis_x > 0) && (dis_y > 0) && (dis_x != dis_y)) {
		return false;
	}

	auto master = GetMaster();
	if (nullptr == master) {
		return false;
	}

	auto map = master->GetCurMap();
	if (nullptr == map) {
		return false;
	}
	auto& grid = map->GetMapGrid();

	//向右移动
	if (y == y0 && x > x0) {
		for (int i = x0 + 1; i <= x; ++i) {

			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(i, y0, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(i, y0)) {
					return false;
				}
			}
		}
		return true;
	}

	//右上移动
	if (x > x0 && y < y0) {
		for (int i = 1; i <= x - x0; ++i) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0 + i, y0 - i, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0 + i, y0 - i)) {
					return false;
				}
			}
		}
		return true;
	}

	//向上移动
	if (x == x0 && y < y0) {
		for (int i = y0 - 1; i >= y; --i) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0, i, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0, i)) {
					return false;
				}
			}
		}
		return true;
	}

	//左上移动
	if (x < x0 && y < y0) {
		for (int i = -1; i >= y - y0; --i) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0 + i, y0 + i, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0 + i, y0 + i)) {
					return false;
				}
			}
		}
		return true;
	}

	//向左移动
	if (y == y0 && x < x0) {
		for (int i = -1; i >= x - x0; --i) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0 + i, y0, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0 + i, y0)) {
					return false;
				}
			}
		}
		return true;
	}

	//左下移动
	if (x < x0 && y > y0) {
		for (int i = -1; i >= x - x0; --i) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0 + i, y0 - i, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0 + i, y0 - i)) {
					return false;
				}
			}
		}
		return true;
	}

	//向下移动
	if (x == x0 && y > y0) {
		for (int i = 1; i <= y - y0; ++i) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0, y0 + i, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0, y0 + i)) {
					return false;
				}
			}
		}
		return true;
	}

	//右下移动
	if (x > x0 && y > y0) {
		for (int i = 1; i <= x - x0; i++) {
			if (master->IsPlayer())
			{
				if (grid.IsForbid_PlayerMoveAck(x0 + i, y0 + i, master))
					return false;
			}
			else
			{
				if (grid.IsForbid(x0 + i, y0 + i)) {
					return false;
				}
			}
		}
		return true;
	}

	return false;
}

void RoleMove::StartMove(uint16_t x, uint16_t y)
{
	mIsMoving = true;
	mReady = true;
	mTarX = x;
	mTarY = y;
	mTimeElapsed = 0;

	auto master = GetMaster();
	if (nullptr != master) {
		master->StartMove(x, y);
        master->SetNeedUpdateFlag(move_need_update_flag);
	}
}

void RoleMove::EndMove(bool success, bool checkJumpPoint)
{
	mIsMoving = false;
	mTarX = 0;
	mTarY = 0;
	mTimeElapsed = 0;

	auto master = GetMaster();
	if (nullptr != master) {
		master->EndMove(success);
		if (checkJumpPoint) master->CheckJump();
        master->ResetNeedUpdateFlag(move_need_update_flag);
	}
}

void RoleMove::UpdateMove(int delta)
{
	if (!mIsMoving) {
		return;
	}

	if (mTarX < 0 || mTarY < 0) {    //地图边缘也能移动    <=  改为  <
		EndMove(false);
		return;
	}

	auto master = GetMaster();
	if (nullptr == master) {
		EndMove(false);
		return;
	}

	auto roleAttr = master->GetRoleAttr();
	if (nullptr == roleAttr) {
		EndMove(false);
		return;
	}

	if (!CanMove()) {
		EndMove(false);
		return;
	}

	uint16_t x, y;
	roleAttr->GetRolePos(x, y);
	if (x == mTarX && y == mTarY) {
		EndMove(false);
		return;
	}

    auto moveSpeed = roleAttr->GetRoleProp(role_move_speed);    // 移动1格需要的毫秒数
    if (moveSpeed <= 0) {
        EndMove(false);
        return;
    }

    auto moveType = roleAttr->GetMoveType();
    if (moveType == move_type_walk && moveSpeed > 1) moveSpeed *= 2;     // 跑是走的2倍速度

	auto map = master->GetCurMap();
	if (nullptr == map) {
		EndMove(false);
		return;
	}

	mTimeElapsed += delta;
	// 移动浮动区间 
	int32_t moveSpeedRange = moveSpeed * 0.85;
	if (master->IsPlayer()) {
		if (true || mTimeElapsed / moveSpeedRange >= 1) {
			DirOffset offset = GetDirOffset(x, y, mTarX, mTarY);
			uint16_t dx = x + offset.XOffset;
			uint16_t dy = y + offset.YOffset;

			if (!master->CheckTakeGrid(dx, dy)) {

				// 移动失败后增加返回
				ProtoGS_MoveAck moveAck;
				auto player = static_cast<Player*>(master);
				if (player) {
					moveAck.clsessid = player->GetClSessionID();
					moveAck.role_guid = player->GetGUID();
					moveAck.ret = move_result_fail;
					moveAck.dst_x = player->GetRolePosX();
					moveAck.dst_y = player->GetRolePosY();
					SendDataBySessionID(player->GetGsSessionID(), moveAck);
				}

				EndMove(false);
				return;
			}
			roleAttr->SetRolePos(dx, dy);
			roleAttr->SetRoleDir((uint8_t)offset.dir);
			master->RemoveBuffWhenMove();

			mTimeElapsed -= moveSpeedRange;
			if (dx == mTarX && dy == mTarY) {
				EndMove(true);
			}
		}
	}
	else {
		if (mReady || mTimeElapsed / moveSpeed >= 1) {
			mReady = false;
			DirOffset offset = GetDirOffset(x, y, mTarX, mTarY);
			uint16_t dx = x + offset.XOffset;
			uint16_t dy = y + offset.YOffset;

			if (!master->CheckTakeGrid(dx, dy)) {
				EndMove(false);
				return;
			}
			roleAttr->SetRolePos(dx, dy);
			roleAttr->SetRoleDir((uint8_t)offset.dir);
			master->RemoveBuffWhenMove();

			mTimeElapsed -= moveSpeed;
			if (dx == mTarX && dy == mTarY) {
				EndMove(true);
			}
		}
	}

}

const DirOffset& RoleMove::GetDirOffset(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
{
	if (y1 == y0 && x1 > x0) {
		return DirOffsetData[dir_right];
	}

	if (y1 < y0 && x1 > x0) {
		return DirOffsetData[dir_right_up];
	}

	if (y1 < y0 && x1 == x0) {
		return DirOffsetData[dir_up];
	}

	if (y1 < y0 && x1 < x0) {
		return DirOffsetData[dir_left_up];
	}

	if (y1 == y0 && x1 < x0) {
		return DirOffsetData[dir_left];
	}

	if (y1 > y0 && x1 < x0) {
		return DirOffsetData[dir_left_down];
	}

	if (y1 > y0 && x1 == x0) {
		return DirOffsetData[dir_down];
	}

	if (y1 > y0 && x1 > x0) {
		return DirOffsetData[dir_right_down];
	}

	return INVALID_DIR_OFFSET;
}

bool RoleMove::CanMove()
{
	auto master = GetMaster();
	if (nullptr == master || !master->CheckAlive()) {
		return false;
	}

	RoleState* roleState = master->GetRoleState();
	if (nullptr == roleState) {
		return false;
	}

	if (role_state_stall == roleState->GetState()) {
		return false;
	}

	if (role_state_rush == roleState->GetState()) {
		return false;
	}

	if (role_state_back == roleState->GetState()) {
		return false;
	}

	RoleAttr* attr = master->GetRoleAttr();
	if (nullptr == attr) {
		return false;
	}

	if (attr->GetRoleProp(role_can_walk) <= 0 && attr->GetRoleProp(role_can_run) <= 0) {
		return false;
	}

	return true;
}