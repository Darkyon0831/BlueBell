#ifndef __BB_IALLOCATOR_H__
#define __BB_IALLOCATOR_H__

#include "../Logging/Logger.h"

#include <sstream>
#include <memory>

namespace BlueBell
{
	class BB_API IAllocator
	{
	public:
	
		IAllocator(IAllocator* pParentAllocator = nullptr) : m_block(nullptr), m_blockSize(0), m_parentAllocator(pParentAllocator) {}
		virtual ~IAllocator() {}
	
		virtual void* Allocate(const size_t, const size_t) { return Allocate(); };
		virtual void* Allocate() { return nullptr; };
		virtual void Deallocate(void**) = 0;

		void SetParentAllocator(IAllocator* parentAllocator) { m_parentAllocator = parentAllocator; }
		const IAllocator* GetParentAllocator() const { return m_parentAllocator; }

		char* GetBlock() const { return m_block; }
		size_t GetBlockSize() const { return m_blockSize; }
	
		virtual void AllocateBlock(const size_t blockSize, const size_t varAlignment = 0);

		inline void Free() 
		{ 
			if (m_block == nullptr)
				return;

			if (m_parentAllocator == nullptr)
				_aligned_free(m_block); 
			else
				m_parentAllocator->Deallocate(reinterpret_cast<void**>(&m_block));

			m_block = nullptr;
		}
	
		inline size_t AlignAdress(size_t address, size_t alignment)
		{
			size_t alignedAddress = ((address - 1) & ~(alignment - 1)) + alignment;
			return alignedAddress;
		}
	
		inline size_t GetPadding(size_t address, size_t alignment)
		{
			size_t alignedAddress = ((address - 1) & ~(alignment - 1)) + alignment;
			return alignedAddress - address;
		}
	
		inline size_t GetPaddingWithHeader(size_t address, size_t headerSize, size_t varAlignment)
		{
			size_t alignedAddress = AlignAdress(address, varAlignment);
			size_t headerAddress = alignedAddress - headerSize; 
	
			size_t insideOldMem = address - headerAddress;
	
			if (insideOldMem > 0)
			{
				alignedAddress = AlignAdress(address + insideOldMem, varAlignment);
				headerAddress = alignedAddress - headerSize; 
			}
	
			return insideOldMem;
		}

		virtual size_t GetMemLeft() = 0;

		void DebugMemory();
	
	protected:
		size_t m_blockSize;
		char* m_block;
		IAllocator* m_parentAllocator;
	};
}

#endif 
