#include "StackAllocator.h"

namespace BlueBell
{
	StackAllocator::StackAllocator(const UseHeader useHeader, const size_t varSize, const size_t startSize, IAllocator* pParentAllocator)
		: IAllocator(pParentAllocator)
		, m_useHeader(useHeader)
		, m_varSize(varSize)
		, m_offset(0)
	{
		if (startSize > 0)
			AllocateBlock(startSize);
	}

	StackAllocator::StackAllocator(const size_t startSize, IAllocator* pParentAllocator)
		: IAllocator(pParentAllocator)
		, m_useHeader(UseHeader::Use)
		, m_varSize(0)
		, m_offset(0)
	{
		if (startSize > 0)
			AllocateBlock(startSize);
	}
	
	StackAllocator::~StackAllocator()
	{
		Free();
	}
	
	void* StackAllocator::Allocate(const size_t size, const size_t alignment)
	{
		BB_ASSERT(m_block != nullptr, "Cannot allocate memory, the block is null (has not been initialized with memory)")
	
		size_t currentAddress = reinterpret_cast<size_t>(m_block + m_offset);
		const size_t headerSize = sizeof(StackHeader);
		size_t padding = 0;

		if (m_useHeader == UseHeader::Use)
			padding = GetPaddingWithHeader(currentAddress, headerSize, alignment);
		else
			padding = GetPadding(currentAddress, alignment);
	
		BB_ASSERT(m_blockSize - m_offset >= size + padding, "Cannot allocate memory, the required size exceeds the free memory on block");
		
		void* ptr = nullptr;

		if (m_useHeader == UseHeader::Use)
		{
			StackHeader* pHeader = reinterpret_cast<StackHeader*>(currentAddress + padding);
			pHeader->chunkSize = size;
			pHeader->padding = padding;
	
			currentAddress += padding + headerSize;
	
			ptr = reinterpret_cast<void*>(currentAddress);

			m_offset += padding + headerSize + size;
		}
		else 
		{
			m_offset += padding + size;
			ptr = reinterpret_cast<void*>(currentAddress + padding);
		}

		return ptr;
	}
	
	void StackAllocator::Deallocate(void** ptr)
	{
		//BB_ASSERT(ptr != nullptr && *ptr != nullptr, "Attempted to deallocate an nullptr");
	
		// Check if the pointer is inside the block
	
		size_t address = reinterpret_cast<size_t>(*ptr);
		size_t blockAddress = reinterpret_cast<size_t>(m_block);
	
		if (address < blockAddress + m_offset && address >= blockAddress)
		{
			void* pChunk = nullptr;
			size_t bytesToRemove = 0;

			if (m_useHeader == UseHeader::Use)
			{
				StackHeader* pHeader = reinterpret_cast<StackHeader*>(address - sizeof(StackHeader));
				size_t chunkSize = pHeader->chunkSize;

				bytesToRemove = sizeof(StackHeader) + chunkSize + pHeader->padding;

				pChunk = reinterpret_cast<void*>(reinterpret_cast<size_t>(pHeader) - pHeader->padding);
			}
			else
			{
				pChunk = reinterpret_cast<void*>(address);

				bytesToRemove = m_varSize;
			}
	
			memset(reinterpret_cast<void*>(pChunk), 0x00, bytesToRemove);
			m_offset -= bytesToRemove;
		}
		else
			BB_LOG_WARN("Attempted to deallocate memory not from allocator");
	}

	void StackAllocator::ClearChunk(size_t startAddress, size_t bytesToClear)
	{
		size_t endAddress = startAddress + bytesToClear;
		size_t blockAddress = reinterpret_cast<size_t>(m_block);

		if (startAddress >= blockAddress && endAddress <= blockAddress + m_offset )
		{
			m_offset = startAddress - blockAddress;
			memset(reinterpret_cast<void*>(startAddress), 0x00, bytesToClear);
		}
	}
}