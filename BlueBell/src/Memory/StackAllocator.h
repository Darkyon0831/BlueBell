#ifndef __BB_STACKALLOCATOR_H__
#define __BB_STACKALLOCATOR_H__

#include "IAllocator.h"
#include "../Logging/Logger.h"

namespace BlueBell
{
	class BB_API StackAllocator : public IAllocator
	{
	public:

		enum UseHeader
		{
			Use,
			NotUse
		};

		struct StackHeader
		{
			size_t chunkSize;
			size_t padding;
		};

		/**
		* @param useHeader: if an header shall be used for this stack allocator, note: the allocator will not be able to allocate more than one unique type if noHeader
		* @param varSize: if noHeader is given, the size of the variable to be used
		* @param startSize: start block size of the allocator
		* @param pParentAllocator: the allocator to ask new block from. if nullptr, malloc is used
		**/
		StackAllocator(const UseHeader useHeader, const size_t varSize = 0, const size_t startSize = 0, IAllocator* pParentAllocator = nullptr);

		/**
		* @param startSize: start block size of the allocator
		* @param pParentAllocator: the allocator to ask new block from. if nullptr, malloc is used
		**/
		StackAllocator(const size_t startSize = 0, IAllocator* pParentAllocator = nullptr);
		~StackAllocator();

		/**
		* Allocated an new variable of the given size and the given alignment, note: will not be used if no header
		*
		* @param size: size of the variable to be allocated
		* @param alignment: alignment of the variable to be allocated
		**/
		void* Allocate(const size_t size, const size_t alignment) override;

		/**
		* Deallocated memory from the allocator
		* 
		* @param ptr: pointer to the memory to be deallocated
		**/
		void Deallocate(void** ptr);

		/**
		* Gets the memory left in bytes of this allocator
		**/
		size_t GetMemLeft() override { return m_blockSize - m_offset; }

		/**
		* Get the header size of the stack allocator
		**/
		size_t GetHeaderSize() { return sizeof(StackHeader); }

		/**
		* Get the offset of the stack allocator
		**/
		size_t GetOffset() { return m_offset; }

		/**
		* Clears an chunk of memory from the stack allocator
		**/
		void ClearChunk(size_t startAddress, size_t bytesToClear);

	private:
		size_t m_offset;
		size_t m_varSize;
		UseHeader m_useHeader;
	};
}

#endif 


