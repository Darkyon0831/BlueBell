#include "IAllocator.h"

namespace BlueBell
{
	void IAllocator::AllocateBlock(const size_t blockSize, const size_t varAlignment)
	{
		if (blockSize == 524288)
			int i = 0;

		if (blockSize != 0) 
		{
			void* newBlock = nullptr;
			size_t newBlockSize = blockSize;

			size_t alignment = varAlignment;
			if (alignment == 0) alignment = newBlockSize < 4 ? newBlockSize : 4;

			if (m_parentAllocator != nullptr)
				newBlock = reinterpret_cast<char*>(m_parentAllocator->Allocate(newBlockSize, alignment)); 
			else
				newBlock = reinterpret_cast<char*>(_aligned_malloc(newBlockSize, alignment)); 

			if (m_block != nullptr)
			{
				if (newBlockSize <= m_blockSize)
					memcpy(newBlock, m_block, newBlockSize);
				else
					memcpy(newBlock, m_block, m_blockSize);

				if (m_parentAllocator == nullptr)
					_aligned_free(m_block);
				else
					m_parentAllocator->Deallocate(reinterpret_cast<void**>(&m_block));

				m_block = reinterpret_cast<char*>(newBlock);
				m_blockSize = newBlockSize;
			}
			else
			{
				memset(newBlock, 0x0, newBlockSize);
				m_block = reinterpret_cast<char*>(newBlock);
				m_blockSize = newBlockSize;
			}
		}
		else
			BB_LOG_WARN("Could not allocate new block with blockSize 0");
	}


	void IAllocator::DebugMemory()
	{
		std::string m_fileoutput;
		m_fileoutput += '\n';

		for (int i = 0; i < 1024; i++)
		{
			char mem = m_block[i];

			m_fileoutput += " ";
			m_fileoutput += std::to_string(mem);

			if (i % 50 == 0 && i != 0)
				m_fileoutput += '\n';
		}

		auto fileLogger = Logger::CreateNewFileLogger("../../game/fileoutputs/output.txt");
		fileLogger->info(m_fileoutput);
	}
}
