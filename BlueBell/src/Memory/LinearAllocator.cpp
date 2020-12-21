#include "LinearAllocator.h"

namespace BlueBell
{
	LinearAllocator::LinearAllocator(const size_t blockSize)
		: m_offset(0)
	{
		AllocateBlock(blockSize);
	}
	
	LinearAllocator::~LinearAllocator()
	{
		Free();
	}
	
	void* LinearAllocator::Allocate(const size_t size, const size_t alignment)
	{
		BB_ASSERT(m_block == nullptr, "Cannot allocate memory, the block is null (has not been initialized with memory)")
	
		size_t currentAddress = reinterpret_cast<size_t>(m_block + m_offset);
		size_t padding = GetPadding(currentAddress, alignment);
	
		BB_ASSERT(m_blockSize - m_offset >= size + padding, "Cannot allocate memory, the required size exceeds the free memory on block");
		
		void* ptr = reinterpret_cast<void*>(currentAddress + padding);
	
		m_offset += size + padding;
	
		return ptr;
	}
}
