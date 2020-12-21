#include "FreeListAllocator.h"

namespace BlueBell
{
	FreeListAllocator::FreeListAllocator(const size_t size, const FindAlgorithm findAlgorithm, IAllocator* pParentAllocator)
		: IAllocator(pParentAllocator)
		, m_findAlgorithm(findAlgorithm)
	{
		AllocateBlock(size);

		LinkedList<FreeNodeHeader>::Node* pNode = reinterpret_cast<LinkedList<FreeNodeHeader>::Node*>(m_block);
		pNode->pNext = nullptr;
		pNode->header.size = m_blockSize;

		m_linkedList.SetHead(pNode);
	}

	FreeListAllocator::~FreeListAllocator()
	{
		Free();
	}

	void* FreeListAllocator::Allocate(const size_t size, const size_t alignment)
	{
		NodePtr pPrevNode = nullptr;
		NodePtr pCurrentNode = nullptr;
		size_t padding;

		Find(size, alignment, pPrevNode, pCurrentNode, padding);

		if (pCurrentNode == nullptr)
			return nullptr;

		const size_t currentSize = pCurrentNode->header.size + sizeof(LinkedList<FreeNodeHeader>::Node);
		const size_t neededSize = size + padding + sizeof(DataHeader);

		m_linkedList.Pop(pPrevNode, pCurrentNode);

		// Create new node if needed
		if (currentSize > neededSize)
		{
			NodePtr newNode = reinterpret_cast<NodePtr>(reinterpret_cast<size_t>(pCurrentNode) + neededSize);
			newNode->header.size = currentSize - neededSize - sizeof(LinkedList<FreeNodeHeader>::Node);
			m_linkedList.Push(pPrevNode, newNode);
		}

		DataHeader* pHeader = reinterpret_cast<DataHeader*>(reinterpret_cast<size_t>(pCurrentNode) + padding);
		pHeader->padding = padding;
		pHeader->size = size;

		void* ptr = reinterpret_cast<void*>(reinterpret_cast<size_t>(pHeader) + sizeof(DataHeader));

		if (ptr == nullptr)
			int i = 0;

		CheckBiggestNodeDebug();

		return ptr;
	}

	void FreeListAllocator::Deallocate(void** ptr)
	{
		//BB_ASSERT(*ptr != nullptr, "Attempted to deallocate an nullptr!");

		size_t nodeSize = sizeof(LinkedList<FreeNodeHeader>::Node);
		size_t dataSize = sizeof(DataHeader);

		DataHeader* pHeader = reinterpret_cast<DataHeader*>(reinterpret_cast<size_t>(*ptr) - sizeof(DataHeader));
		size_t blockSize = pHeader->padding + pHeader->size + sizeof(DataHeader);

		void* blockPtr = reinterpret_cast<void*>(reinterpret_cast<size_t>(pHeader) - pHeader->padding);

		memset(blockPtr, 0x0, pHeader->padding + pHeader->size + sizeof(DataHeader));

		NodePtr nodePtr = reinterpret_cast<NodePtr>(blockPtr);
		nodePtr->header.size = blockSize - sizeof(LinkedList<FreeNodeHeader>::Node);

		NodePtr pPrevNode = nullptr;

		FindPrevNode(reinterpret_cast<size_t>(blockPtr), pPrevNode);

		m_linkedList.Push(pPrevNode, nodePtr);

		MergeNodes(pPrevNode, nodePtr);

		*ptr = nullptr;

		CheckBiggestNodeDebug();
	}

	size_t FreeListAllocator::GetHeaderSize(void* ptr)
	{
		size_t nodeSize = sizeof(LinkedList<FreeNodeHeader>::Node);
		size_t dataSize = sizeof(DataHeader);

		DataHeader* pHeader = reinterpret_cast<DataHeader*>(reinterpret_cast<size_t>(ptr) - sizeof(DataHeader));
		size_t blockSize = pHeader->padding + pHeader->size + sizeof(DataHeader);

		return pHeader->size;
	}

	void FreeListAllocator::Find(const size_t size, const size_t alignment, NodePtr& pPrevNode, NodePtr& pCurrentNode, size_t& rPadding)
	{
		if (m_findAlgorithm = FindAlgorithm::EFindFirst)
			FindFirst(size, alignment, pPrevNode, pCurrentNode, rPadding);
		else 
			FindBest(size, alignment, pPrevNode, pCurrentNode, rPadding);
	}

	void FreeListAllocator::FindFirst(const size_t size, const size_t alignment, NodePtr& pPrevNode, NodePtr& pCurrentNode, size_t& rPadding)
	{
		pPrevNode = nullptr;
		pCurrentNode = m_linkedList.GetHead();

		rPadding = 0;
		bool found = false;

		while (pCurrentNode != nullptr && found == false)
		{
			rPadding = GetPaddingWithHeader(reinterpret_cast<size_t>(pCurrentNode), sizeof(DataHeader), alignment);

			const size_t currentSize = pCurrentNode->header.size + sizeof(LinkedList<FreeNodeHeader>::Node);
			const size_t neededSize = size + rPadding + sizeof(DataHeader);

			if (neededSize <= currentSize)
			{
				if (currentSize == neededSize)
					found = true;
				else if (currentSize - neededSize >= sizeof(LinkedList<FreeNodeHeader>::Node))
					found = true;
			}
			else
			{
				pPrevNode = pCurrentNode;
				pCurrentNode = pCurrentNode->pNext;
			}
		}
	}

	void FreeListAllocator::FindBest(const size_t size, const size_t alignment, NodePtr& pPrevNode, NodePtr& pCurrentNode, size_t& rPadding)
	{
		pPrevNode = nullptr;
		NodePtr pNode = m_linkedList.GetHead();
		NodePtr pPrev = nullptr;
		size_t _currentSise = 0;

		rPadding = 0;

		while (pNode != nullptr)
		{
			rPadding = GetPaddingWithHeader(reinterpret_cast<size_t>(pNode), sizeof(DataHeader), alignment);

			const size_t currentSize = pNode->header.size + sizeof(sizeof(LinkedList<FreeNodeHeader>::Node));
			const size_t neededSize = size + rPadding + sizeof(DataHeader);

			if ( (pCurrentNode == nullptr && currentSize >= neededSize) || (currentSize >= neededSize && pCurrentNode->header.size < _currentSise) )
			{
				if (currentSize == neededSize)
				{
					_currentSise = pNode->header.size;
					pPrevNode = pPrev;
					pCurrentNode = pNode;
				}
				else if (currentSize - neededSize >= sizeof(LinkedList<FreeNodeHeader>::Node))
				{
					_currentSise = pNode->header.size;
					pPrevNode = pPrev;
					pCurrentNode = pNode;
				}
			}
			
			pPrev = pNode;
			pNode = pNode->pNext;
		}
	}

	void FreeListAllocator::FindPrevNode(const size_t blockAddress, NodePtr& pPrevNode)
	{
		NodePtr tempPrev = m_linkedList.GetHead();
		
		size_t currentAddress = reinterpret_cast<size_t>(tempPrev);
		size_t nextAddress = currentAddress + tempPrev->header.size + sizeof(LinkedList<FreeNodeHeader>::Node);

		while ( currentAddress < blockAddress && tempPrev != nullptr)
		{
			pPrevNode = tempPrev;
			tempPrev = tempPrev->pNext;

			currentAddress = reinterpret_cast<size_t>(tempPrev);

			nextAddress = currentAddress + tempPrev->header.size + sizeof(LinkedList<FreeNodeHeader>::Node);
		}
	}

	void FreeListAllocator::MergeNodes(NodePtr pPrevNode, NodePtr pCurrentNode)
	{
		size_t prevNodeAddress = 0;
		size_t nextNodeAddress = 0;
		size_t currentNodeAddress = reinterpret_cast<size_t>(pCurrentNode);

		if (pPrevNode != nullptr)
			prevNodeAddress = reinterpret_cast<size_t>(pPrevNode);

		if (pCurrentNode->pNext != nullptr)
			nextNodeAddress = reinterpret_cast<size_t>(pCurrentNode->pNext);

		size_t test = 0;

		if (nextNodeAddress != 0)
			test = currentNodeAddress + (sizeof(LinkedList<FreeNodeHeader>::Node) + pCurrentNode->header.size);

		if (nextNodeAddress != 0 && currentNodeAddress + (sizeof(LinkedList<FreeNodeHeader>::Node) + pCurrentNode->header.size) == nextNodeAddress)
		{
			pCurrentNode->header.size += pCurrentNode->pNext->header.size + sizeof(LinkedList<FreeNodeHeader>::Node);

			NodePtr ptrToReset = pCurrentNode->pNext;

			pCurrentNode->pNext = pCurrentNode->pNext->pNext;

			memset(ptrToReset, 0x0, sizeof(LinkedList<FreeNodeHeader>::Node));
		}

		size_t test2 = 0;

		if (prevNodeAddress != 0)
			test2 = currentNodeAddress - (sizeof(LinkedList<FreeNodeHeader>::Node) + pPrevNode->header.size);

		if (prevNodeAddress != 0 && currentNodeAddress - (sizeof(LinkedList<FreeNodeHeader>::Node) + pPrevNode->header.size) == prevNodeAddress)
		{
			pPrevNode->header.size += pCurrentNode->header.size + sizeof(LinkedList<FreeNodeHeader>::Node);

			NodePtr ptrToReset = pCurrentNode;

			pPrevNode->pNext = pCurrentNode->pNext;
		
			memset(ptrToReset, 0x0,  sizeof(LinkedList<FreeNodeHeader>::Node));
		}
	}

	void FreeListAllocator::CheckBiggestNodeDebug()
	{
		/*NodePtr node = m_linkedList.GetHead();
		size_t currentBiggestSize = node->header.size;

		while (node != nullptr)
		{
			if (node->header.size >= currentBiggestSize)
				currentBiggestSize = node->header.size;

			node = node->pNext;
		}

		BB_LOG_INFO("Current biggest node size is {0}", currentBiggestSize);*/
	}
}
