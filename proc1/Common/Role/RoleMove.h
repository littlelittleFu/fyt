#pragma once
#include "RoleAction.h"


struct DirOffset
{
	DirOffset() : XOffset(0), YOffset(0), dir(-1) {}
	DirOffset(int x, int y, int dir) : XOffset(x), YOffset(y), dir(dir) {}
	int XOffset;
	int YOffset;
    int dir;
};

const DirOffset DirOffsetData[dir_max] =
{
    { 0,	-1, dir_up },
	{ 1,	-1, dir_right_up },
	{ 1,	0,  dir_right },
    { 1,	1,  dir_right_down },
	{ 0,	1,  dir_down },
    { -1,	1,  dir_left_down },
	{ -1,	0,  dir_left },
	{ -1,	-1, dir_left_up }
};

class RoleMove : public RoleAction
{
public:
    RoleMove(Role* master = nullptr);
    ~RoleMove();


public:
    bool Init() override;
    void Update(int32_t delta) override;
    uint16_t MoveTo(uint16_t x, uint16_t y, uint8_t type = 0);
    bool IsPointCanReach(uint16_t x0, uint16_t y0, uint16_t x, uint16_t y);
    void StopMove(bool checkJumpPoint = true) { EndMove(true, checkJumpPoint); }
    bool CanMove();
    bool IsMoving() { return mIsMoving; }
protected:
    void StartMove(uint16_t x, uint16_t y);
    void EndMove(bool success = true, bool checkJumpPoint = true);
    void UpdateMove(int delta);
	const DirOffset& GetDirOffset(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
protected:
    bool mIsMoving;
    bool mReady;
    uint16_t mTarX;
    uint16_t mTarY;
    int32_t mTimeElapsed;
};
