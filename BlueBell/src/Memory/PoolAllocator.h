#ifndef __BB__POOLALLOCATOR_H__
#define __BB__POOLALLOCATOR_H__

#include "IAllocator.h"

namespace BlueBell
{
	class BB_API PoolAllocator : public IAllocator
	{
	public:

		enum Header
		{
			InCell,
			Outside
		};

		/**
		* Default constructor
		**/
		PoolAllocator() = default;

		/**
		* @param cellsCount: How many cells the pool allocator will have
		* @param varSize: Size of one cell
		* @param pParentAllocator: the allocator to ask new block from. if nullptr, malloc is used
		**/
		PoolAllocator(size_t cellsCount, size_t varSize, IAllocator* pParentAllocator = nullptr);
		~PoolAllocator() override;

		/**
		* Allocates an new variable
		*
		* @param size: not used
		* @param alignment: not used
		**/
		void* Allocate(const size_t size, const size_t alignment) override;

		/**
		* Deallocate memory from the allocator
		*
		* @param ptr: pointer to the memory to be deallocated
		**/
		void Deallocate(void** ptr) override;

		/**
		* Gets the memory left for this allocator
		**/
		size_t GetMemLeft() override;

	private:

		size_t m_cellsCount;
		size_t m_varSize;
	};

	#endif // !__BB__POOLALLOCATOR_H__
}
