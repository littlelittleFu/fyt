#include "MemoryPool.h"

Memory::Declare::MemoryPool::MemoryPool(size_t block_size) {
	this->firstBlock = this->currentBlock = nullptr;
	this->defaultBlockSize = block_size;
	this->currentScope = nullptr;
	this->CreateMemoryBlock(block_size);
}

Memory::Declare::MemoryPool::~MemoryPool() {
	MemoryBlockHeader* block_it = firstBlock;

	while (nullptr != block_it) {
		MemoryBlockHeader* next_it = block_it->next;
		delete (block_it);
		block_it = next_it;
	}
}

void Memory::Declare::MemoryPool::CreateMemoryBlock(size_t block_size) {

	MemoryBlockHeader* block = reinterpret_cast<MemoryBlockHeader*>(new char[sizeof(MemoryBlockHeader) + block_size]);
	if (nullptr == block) throw MemoryErr::err_cannot_create_block;

	block->blockSize = block_size;
	block->offset = 0;
	block->numberOfAllocated = 0;
	block->numberOfDeleted = 0;

	if (nullptr != this->firstBlock) {
		block->next = nullptr;
		block->prev = this->currentBlock;
		this->currentBlock->next = block;
		this->currentBlock = block;
	}
	else {
		block->next = block->prev = nullptr;
		this->firstBlock = block;
		this->currentBlock = block;
	}

}

void* Memory::Declare::MemoryPool::Allocate(size_t size) {
	if (size + sizeof(MemoryUnitHeader) < this->currentBlock->blockSize - this->currentBlock->offset) {
		//this->CreateMemoryBlock(MEMORYPOOL_DEFAULT_BLOCK_SIZE);
	}
	else if (size + sizeof(MemoryUnitHeader) >= this->defaultBlockSize) {
		this->CreateMemoryBlock(size + sizeof(MemoryUnitHeader));
	}
	else {
		this->CreateMemoryBlock(this->defaultBlockSize);
	}

	MemoryUnitHeader* unit = reinterpret_cast<MemoryUnitHeader*>(reinterpret_cast<char*>
		(this->currentBlock) + sizeof(MemoryBlockHeader) + this->currentBlock->offset);

	unit->length = size;
	unit->container = this->currentBlock;
	this->currentBlock->numberOfAllocated++;
	this->currentBlock->offset += sizeof(MemoryUnitHeader) + size;

	return reinterpret_cast<char*>(unit) + sizeof(MemoryUnitHeader);
}

void* Memory::Declare::MemoryPool::Reallocate(void* unit_pointer_start, size_t new_size) {
	if (nullptr == unit_pointer_start)return nullptr;

	MemoryUnitHeader* unit = reinterpret_cast<MemoryUnitHeader*>(reinterpret_cast<char*>(unit_pointer_start) - sizeof(MemoryUnitHeader));
	MemoryBlockHeader* block = unit->container;

	if (reinterpret_cast<char*>(block) + sizeof(MemoryBlockHeader) + block->offset == 
		reinterpret_cast<char*>(unit) + sizeof(MemoryUnitHeader) + unit->length
		&& block->blockSize > block->offset + new_size - unit->length) {
		block->offset += new_size - unit->length;
		unit->length = new_size;
		return unit_pointer_start;
	}

	void* temp_pointer = this->Allocate(new_size);
	std::memcpy(temp_pointer, unit_pointer_start, unit->length);
	this->Free(unit_pointer_start);
	return temp_pointer;
}

void Memory::Declare::MemoryPool::Free(void* unit_pointer_start) {
	if (nullptr == unit_pointer_start)return;

	MemoryUnitHeader* unit = reinterpret_cast<MemoryUnitHeader*>(reinterpret_cast<char*>(unit_pointer_start) - sizeof(MemoryUnitHeader));
	MemoryBlockHeader* block = unit->container;

	if (reinterpret_cast<char*>(block) + sizeof(MemoryBlockHeader) + block->offset == reinterpret_cast<char*>(unit) + sizeof(MemoryUnitHeader) + unit->length) {
		block->offset -= sizeof(MemoryUnitHeader) + unit->length;
		block->numberOfAllocated--;
	}
	else {
		block->numberOfDeleted++;
	}

	if (this->currentBlock != this->firstBlock && (block->offset == 0 || block->numberOfAllocated == block->numberOfDeleted)) {
		if (block == this->firstBlock) {
			this->firstBlock = block->next;
			this->firstBlock->prev = nullptr;
		}
		else if (block == this->currentBlock) {
			this->currentBlock = block->prev;
			this->currentBlock->next = nullptr;
		}
		else {
			block->prev->next = block->next;
			block->next->prev = block->prev;
		}

		delete(block);
		block = nullptr;
	}
}

void Memory::Declare::MemoryPool::DumpPoolData() {
	MemoryBlockHeader* block = this->firstBlock;
	MemoryUnitHeader* unit;
	size_t current_unit_offset;
	size_t block_counter = 1;
	size_t unit_counter = 1;

	while (nullptr == block) {
		std::cout << "block" << block_counter << ": " << std::endl;
		std::cout << "\t" << "used: " << (float)(block_counter) / (float)(block->blockSize) * 100 << "%" << "(" << block->offset << "/" << block->blockSize << ")" << std::endl;

		if (block->offset == 0) {
			block = block->next;
			block_counter++;
			continue;
		}

		std::cout << "\t" << "Units:======================" << std::endl;
		current_unit_offset = 0;
		unit_counter = 1;
		while (current_unit_offset < block->offset) {
			unit = reinterpret_cast<MemoryUnitHeader*>(reinterpret_cast<char*>(block + 1) + current_unit_offset);
			std::cout << "\t\t" << "unit " << unit_counter << ": " << unit->length + sizeof(MemoryUnitHeader) << std::endl;
			current_unit_offset += sizeof(MemoryUnitHeader) + unit->length;
			unit_counter++;
		}

		std::cout << "\t" << "=====================" << std::endl;

		block = block->next;
		block_counter++;
	}
}

void Memory::Declare::MemoryPool::StartScope() {
	if (nullptr == this->currentScope) {
		this->currentScope = new (this) MemoryScopeHeader;
		this->currentScope->prevScope = nullptr;
	}
	else {
		MemoryScopeHeader* new_scope = new(this)MemoryScopeHeader;
		new_scope->prevScope = this->currentScope;
		this->currentScope = new_scope;
	}

	this->currentScope->scopeOffset = this->currentBlock->offset - sizeof(MemoryScopeHeader) - sizeof(MemoryUnitHeader);
	this->currentScope->firstScopeBlock = this->currentBlock;
}

void Memory::Declare::MemoryPool::EndScope() {
	while (this->currentBlock != this->currentScope->firstScopeBlock) {
		this->currentBlock = this->currentBlock->prev;
		delete(this->currentBlock->next);
		this->currentBlock->next = nullptr;
	}

	this->currentBlock->offset = this->currentScope->scopeOffset;
}

void* operator new(size_t size, Memory::Declare::MemoryPool* mp) {
	return mp->Allocate(size);
}

void* operator new[](size_t size, Memory::Declare::MemoryPool* mp) {
	return mp->Allocate(size);
}