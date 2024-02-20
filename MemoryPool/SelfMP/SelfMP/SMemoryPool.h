#pragma once
#include<stdlib.h>
#include<wtypes.h>
#define MEMPOOL_ALIGMENT 8 //对齐长度
class SMemoryPool;

class SMemoryBlock
{
	friend SMemoryPool;
private:
	SMemoryBlock(int nUnitSize, int nUnitAmount);
	~SMemoryBlock() {};

	static void* operator new(size_t, int nUnitSize, int nUnitAmount);
	static void operator delete(void*, int nUnitSize, int nUnitAmount);
	static void operator delete(void* _pBlock);

private:
	int mSize; //该内存块大小
	int mFree; //内存块还有多少可分配的单元
	char* pFree;//空闲块指针
	SMemoryBlock* pMem;
	SMemoryBlock* pNext;
	SMemoryBlock* pPre;
	char mData[1]; // 用于标记分配单元开始的位置
};

class SMemoryPool
{
public:
	SMemoryPool(int nUnitSize, int nGrowSize = 256, int nInitSize = 256);
	~SMemoryPool();

	void* Alloc();
	void Free(void* pFree);

private:
	int mInitSize; //初始大小
	int mGrowSize; //增长大小
	int mUnitSize; //分配单元大小
	SMemoryBlock* pBlock;
};