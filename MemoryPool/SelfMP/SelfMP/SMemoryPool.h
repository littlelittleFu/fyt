#pragma once
#include<stdlib.h>
#include<wtypes.h>
#define MEMPOOL_ALIGMENT 8 //���볤��
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
	int mSize; //���ڴ���С
	int mFree; //�ڴ�黹�ж��ٿɷ���ĵ�Ԫ
	char* pFree;//���п�ָ��
	SMemoryBlock* pMem;
	SMemoryBlock* pNext;
	SMemoryBlock* pPre;
	char mData[1]; // ���ڱ�Ƿ��䵥Ԫ��ʼ��λ��
};

class SMemoryPool
{
public:
	SMemoryPool(int nUnitSize, int nGrowSize = 256, int nInitSize = 256);
	~SMemoryPool();

	void* Alloc();
	void Free(void* pFree);

private:
	int mInitSize; //��ʼ��С
	int mGrowSize; //������С
	int mUnitSize; //���䵥Ԫ��С
	SMemoryBlock* pBlock;
};