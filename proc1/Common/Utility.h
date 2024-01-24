#pragma once
enum charactor_decode
{
	greater = 1,
	lesser = 2,
	equal = 3,
};

class Utility
{
public:
	static uint16_t CalcRelativeDir(uint16_t srcX, uint16_t srcY, uint16_t tarX, uint16_t tarY)
	{
		float dirX = tarX - srcX;
		float dirY = tarY - srcY;

		if (dirX == 0) {
			if (dirY < 0) {
				return dir_up;
			}
			else if (dirY > 0) {
				return dir_down;
			}
			else {
				return dir_max;
			}
		}

		const float TAN_225 = 0.414f;
		const float TAN_675 = 2.414f;

		float tanDir = abs(dirY / dirX);

		if (dirY < 0 && tanDir >= TAN_675) {
			return dir_up;
		}

		if (dirX > 0 && dirY < 0 && tanDir >= TAN_225 && tanDir <= TAN_675) {
			return dir_right_up;
		}

		if (dirX > 0 && tanDir <= TAN_225) {
			return dir_right;
		}

		if (dirX > 0 && dirY > 0 && tanDir >= TAN_225 && tanDir <= TAN_675) {
			return dir_right_down;
		}

		if (dirY > 0 && tanDir >= TAN_675) {
			return dir_down;
		}

		if (dirX < 0 && dirY > 0 && tanDir >= TAN_225 && tanDir <= TAN_675) {
			return dir_left_down;
		}

		if (dirX < 0 && tanDir <= TAN_225) {
			return dir_left;
		}

		if (dirX < 0 && dirY < 0 && tanDir >= TAN_225 && tanDir <= TAN_675) {
			return dir_left_up;
		}

		return dir_up;
	}

	static uint16_t CalcLongerDistance(uint16_t srcX, uint16_t srcY, uint16_t tarX, uint16_t tarY)
	{
		return std::max<uint16_t>(abs(srcX - tarX), abs(srcY - tarY));
	}

	static std::string UInt2IpStr(uint32_t ip)
	{
		static struct in_addr addr;
		addr.s_addr = ip;
		return inet_ntoa(addr);
	}
	static uint32_t IpStr2UInt(const std::string& ip)
	{
		return inet_addr(ip.c_str());
	}
	static bool CompareFunc(int type, int CurHP, int MaxHP)
	{
		switch (type)
		{
		case charactor_decode::greater:
			if (CurHP > MaxHP )return true;
			break;
		case charactor_decode::lesser:
			if (CurHP < MaxHP )return true;
			break;
		case charactor_decode::equal:
			if (CurHP == MaxHP)return true;
			break;
		default:
			return false;
		}
		return false;
	}
};
