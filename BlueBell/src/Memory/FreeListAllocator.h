#ifndef __BB_FREELISTALLOCATOR_H__
#define __BB_FREELISTALLOCATOR_H__

#include "IAllocator.h"
#include "LinkedList.h"

namespace BlueBell
{
	class BB_API FreeListAllocator : public IAllocator
	{
	public:

		enum FindAlgorithm
		{
			EFindFirst,
			EFindBest
		};

		struct FreeNodeHeader
		{	
			size_t size;
		};

		struct DataHeader
		{
			size_t size;
			size_t padding;
		};

		/**
		* Default constructor
		**/
		FreeListAllocator() : m_findAlgorithm(EFindBest) {}

		/**
		* @param size: block size of this allocator
		* @param FindAlgorithm: algorithm to use when allocating new memory
		* @param pParentAllocator: the allocator to ask new block from. if nullptr, malloc is used
		**/
		FreeListAllocator(const size_t size, const FindAlgorithm findAlgorithm, IAllocator* pParentAllocator = nullptr);
		~FreeListAllocator() override;



		using NodePtr = LinkedList<FreeNodeHeader>::Node*;

		/**
		* Allocate new variable with size and alignment.
		*
		* @param size: Needed size to allocate with.
		* @param alignment: Alignment of the variable to be allocated.
		**/
		void* Allocate(const size_t size, const size_t alignment) override;

		/**
		* Deallocates memory from this allocator
		*
		* @param ptr: memory to be freed from allocator
		**/
		void Deallocate(void** ptr) override;

		size_t GetMemLeft() override { return 0; }

		size_t GetHeaderSize(void* ptr);

	private:

		void Find(const size_t size, const size_t alignment, NodePtr& pPrevNode, NodePtr& pCurrentNode, size_t& rPadding);
		void FindFirst(const size_t size, const size_t alignment, NodePtr& pPrevNode, NodePtr& pCurrentNode, size_t& rPadding);
		void FindBest(const size_t size, const size_t alignment, NodePtr& pPrevNode, NodePtr& pCurrentNode, size_t& rPadding);

		void FindPrevNode(const size_t blockAddress, NodePtr& pPrevNode);

		void MergeNodes(NodePtr pPrevNode, NodePtr pCurrentNode);

		void CheckBiggestNodeDebug();

		FindAlgorithm m_findAlgorithm;
		LinkedList<FreeNodeHeader> m_linkedList;

	};
}

#endif

