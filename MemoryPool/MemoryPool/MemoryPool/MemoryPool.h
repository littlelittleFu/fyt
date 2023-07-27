#pragma once
#define MEMORYPOOL_DEFAULT_BLOCK_SIZE 1024 * 1024

#include<iostream>

namespace Memory {
	namespace Declare {
		enum class MemoryErr {
			err_cannot_create_memory_pool,
			err_cannot_create_block,
			err_out_of_pool,
			err_exceeds_max_size,
			err_cannot_create_block_chain,
		};

		struct MemoryBlockHeader {
			size_t blockSize;
			size_t offset;

			MemoryBlockHeader* next;
			MemoryBlockHeader* prev;

			size_t numberOfAllocated;
			size_t numberOfDeleted;
		};

		struct MemoryUnitHeader {
			size_t length;
			MemoryBlockHeader* container;
		};

		struct MemoryScopeHeader {
			size_t scopeOffset;
			MemoryBlockHeader* firstScopeBlock;
			MemoryScopeHeader* prevScope;
		};

		class MemoryPool {
		public:
			MemoryPool(size_t block_size = MEMORYPOOL_DEFAULT_BLOCK_SIZE);
			~MemoryPool();

		private:
			MemoryBlockHeader* firstBlock;
			MemoryBlockHeader* currentBlock;

			size_t defaultBlockSize;

			MemoryScopeHeader* currentScope;

		public:
			void CreateMemoryBlock(size_t block_size = MEMORYPOOL_DEFAULT_BLOCK_SIZE);

			void* Allocate(size_t size);
			template<typename T>
			T* Allocate(size_t instances);

			void* Reallocate(void* unit_pointer_start, size_t new_size);
			template<typename T>
			T* Reallocate(T* unit_pointer_start, size_t new_size);

			void Free(void* unit_pointer_start);
			void DumpPoolData();
			void StartScope();
			void EndScope();
		};

		template<typename T>
		inline T* MemoryPool::Allocate(size_t instances) {
			return reinterpret_cast<T*>(this->Allocate(instances * sizeof(T)));
		}

		template<typename T>
		inline T* MemoryPool::Reallocate(T* uint_pointer_start, size_t new_size) {
			return reinterpret_cast<T*>(this->Reallocate(static_cast<void*>(uint_pointer_start), new_size * sizeof(T)));
		}
	}
}


extern void* operator new(std::size_t size, Memory::Declare::MemoryPool* mp);
extern void* operator new[](std::size_t size, Memory::Declare::MemoryPool* mp);