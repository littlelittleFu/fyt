#include"S_timer.h"
#include"SMemoryPool.h"
#include<vector>
class Player {

public:
	void* operator new(size_t);
	void operator delete(void* p);

public:
	static SMemoryPool mPool;
	int a,b,c;
};

SMemoryPool Player::mPool(sizeof(Player));


void* Player::operator new(size_t) {
	return (Player*)mPool.Alloc();
}

void Player::operator delete(void* p) {
	mPool.Free(p);
}

void aa(char** dst, char* nst)
{
	dst = &nst;
}

int main() {


	{
		STimer s;
		auto player = new Player();
		player->a = 2;
		player->b = 4;
		player->c = 8;
		auto player1 = new Player();
		player1->a = 2;
		player1->b = 4;
		player1->c = 8;
		delete player1;
		auto player3 = new Player();
		player3->a = 2;
		player3->b = 4;
		player3->c = 8;
	}

	return 0;
};