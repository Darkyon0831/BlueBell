#ifndef __BB_LINEARALLOCATOR_H__
#define __BB_LINEARALLOCATOR_H__

#include "IAllocator.h"
#include "../Logging/Logger.h"

namespace BlueBell
{
	class BB_API LinearAllocator : public IAllocator
	{
	public:
		
		LinearAllocator(const size_t blockSize = 0);
		~LinearAllocator();
		
		/**
		* Allocate an new variable with size and alignment
		*
		* @param size: size to be allocated from allocator
		* @param alignment: alignment of the variable
		**/
		void* Allocate(const size_t size, const size_t alignment) override;

		/**
		* Deallocates memory from allocator
		*
		* @param ptr: pointer to the memory to be deallocated
		**/
		void Deallocate(void** ptr) override { BB_LOG_WARN("Cannot deallocate seperate memory from an linear allocator") }

		/**
		* Gets the memory left in bytes of this allocator
		**/
		size_t GetMemLeft() override { return m_blockSize - m_offset; }

		/**
		* Gets the offset from the block address of this linear allocator
		**/
		size_t GetOffset() { return m_offset; }
	
	private:
		size_t m_offset;
	};
}

#endif 
