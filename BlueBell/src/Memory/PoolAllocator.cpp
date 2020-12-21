#include "PoolAllocator.h"

BlueBell::PoolAllocator::PoolAllocator(const size_t cellsCount, const size_t varSize, IAllocator* pParentAllocator)
	: IAllocator(pParentAllocator)
	, m_cellsCount(cellsCount)
	, m_varSize(varSize)
{
	AllocateBlock(m_cellsCount * sizeof(int) + m_cellsCount * varSize);

	memset(&m_block[sizeof(int) * m_cellsCount], 0x0, m_blockSize - (sizeof(int) * m_cellsCount));

	for (int i = 0; i < sizeof(int) * m_cellsCount; i+=4)
		memset(&m_block[i], 1, 1);
}

BlueBell::PoolAllocator::~PoolAllocator()
{
	Free();
}

void* BlueBell::PoolAllocator::Allocate(const size_t size, const size_t alignment)
{
	BB_NOT_USE(size)
	BB_NOT_USE(alignment)

	int* usedArray = reinterpret_cast<int*>(m_block);
	bool found = false;
	int i = 0;

	while (found == false)
	{
		if (usedArray[i] == 1)
		{
			found = true;
			usedArray[i] = 0;
		}
		else
			i++;
	}

	void* ptr = reinterpret_cast<void*>(m_block + sizeof(int) * m_cellsCount + m_varSize * i);
	return ptr;
}

void BlueBell::PoolAllocator::Deallocate(void** ptr)
{
	size_t addressDiff = reinterpret_cast<size_t>(m_block) - reinterpret_cast<size_t>(*ptr);

	addressDiff -= sizeof(int) * m_cellsCount;

	int index = addressDiff / m_varSize;

	memset(*ptr, 0x0, m_varSize);

	int* usedArray = reinterpret_cast<int*>(m_block);
	usedArray[index] = 1;

	*ptr = nullptr;
}

size_t BlueBell::PoolAllocator::GetMemLeft()
{
	size_t count = 0;
	int* usedArray = reinterpret_cast<int*>(m_block);

	for (unsigned int i = 0; i < m_cellsCount; i++)
	{
		if (usedArray[i] == 1)
			count++;
	}

	return count;
}
