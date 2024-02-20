#include"SMemoryPool.h"

SMemoryBlock::SMemoryBlock(int nUnitSize, int nUnitAmount):
mSize(nUnitAmount /** nUnitSize*/),
mFree(nUnitAmount - 1),
pFree(nullptr),
pNext(nullptr),
pPre(nullptr){
	//初始化数组连接
	char* pData = mData;
	for (int i = 0; i < mSize; i++) {
		*(char**)pData = pData + nUnitSize;
		pData += nUnitSize;
	}
	// 最后一块指向空
	*(char**)pData = nullptr;
}

void* SMemoryBlock::operator new(size_t, int nUnitSize, int nUnitAmount)
{
	return ::operator new(sizeof(SMemoryBlock) + nUnitSize * nUnitAmount);
}

void SMemoryBlock::operator delete(void*, int nUnitSize, int nUnitAmount)
{

}

void SMemoryBlock::operator delete(void* _pBlock)
{
	::operator delete(_pBlock);
}


SMemoryPool::SMemoryPool(int nUnitSize, int nGrowSize, int nInitSize)
{
	nUnitSize += 4;//每一个单元指向下一个单元的指针
	this->mInitSize = nInitSize;
	this->mGrowSize = nGrowSize;
	pBlock = nullptr;
	if (nUnitSize > 4)
		//取补齐长度倍数
		mUnitSize = (nUnitSize + (MEMPOOL_ALIGMENT - 1)) & ~(MEMPOOL_ALIGMENT - 1);
	else if (nUnitSize < 2)
		mUnitSize = 2;
	else
		mUnitSize = 4;
}

SMemoryPool::~SMemoryPool()
{	
	SMemoryBlock* pMyBlock = pBlock;
	while (pMyBlock != nullptr) {
		SMemoryBlock* pNextBlock = pMyBlock->pNext;
		delete(pMyBlock);
		pMyBlock = pNextBlock;
	}
}

void* SMemoryPool::Alloc()
{
	if (nullptr == pBlock) {
		pBlock = (SMemoryBlock*)new(mUnitSize, mInitSize) SMemoryBlock(mUnitSize, mInitSize);
		//指向下一块空闲区域
		char* mem = pBlock->mData;
		pBlock->pFree = *(char**)pBlock->mData;
		*(SMemoryBlock**)mem = pBlock;
		return (void*)(mem + 4);
	}

	SMemoryBlock* pMyBlock = pBlock;
	while (pMyBlock != nullptr && 0 == pMyBlock->mFree)
		pMyBlock = pMyBlock->pNext;

	if (pMyBlock != nullptr) {
		char* mem = pMyBlock->pFree;
		pMyBlock->pFree = *(char**)pMyBlock->pFree;
		*(SMemoryBlock**)mem = pBlock;
		pMyBlock->mFree--;

		return (void*)(mem + 4);
	}
	else {
		if (0 == mGrowSize) {
			return nullptr;
		}

		pMyBlock = (SMemoryBlock*)new(mUnitSize, mGrowSize)SMemoryBlock(mUnitSize, mGrowSize);
		if (nullptr == pMyBlock)
			return nullptr;

		pBlock->pNext = pMyBlock;
		pMyBlock->pPre = pBlock;

		char* mem = pMyBlock->mData;
		pMyBlock->pFree = *(char**)pMyBlock->mData;
		*(SMemoryBlock**)mem = pMyBlock;

		return (void*)(mem + 4);
	}
}

void SMemoryPool::Free(void* pFree)
{
	SMemoryBlock* pMyBlock = *(SMemoryBlock**)((char*)pFree - 4);

	if ((pMyBlock->pNext != nullptr || pMyBlock->pPre != nullptr) && pMyBlock->mFree == mInitSize) {
		if (!pMyBlock->pPre) {
			pMyBlock->pNext->pPre = pMyBlock->pPre;
			pBlock = pMyBlock->pNext;
		}
		else if(!pMyBlock->pNext){
			pMyBlock->pPre->pNext = nullptr;
		}
		else {
			pMyBlock->pNext->pPre = pMyBlock->pPre;
			pMyBlock->pPre->pNext = pMyBlock->pNext;
		}
		delete(pMyBlock);

		return;
	}


	if (nullptr != pMyBlock) {
		char* mem = (char*)pFree - 4;
		if (pMyBlock->mFree == 0) {
			*(char**)mem = nullptr;
			pMyBlock->pFree = mem;
		}
		else {
			*(char**)mem = pMyBlock->pFree;
			pMyBlock->pFree = mem;
		}
		pMyBlock->mFree++;
	}
}