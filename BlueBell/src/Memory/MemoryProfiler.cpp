#include "MemoryProfiler.h"

#include "../Logging/Logger.h"

namespace BlueBell
{
	void BlueBell::MemoryProfiler::Add(size_t size, void* memory, const char* varName)
	{
		m_allocatedMemory.EmplaceBack(size, memory, varName);
	}

	void BlueBell::MemoryProfiler::Remove(void* memory)
	{
		int i = 0;
		bool found = false;
		
		while (found == false)
		{
			if (m_allocatedMemory.At(i).pointer == memory)
				found = true;
			else if (i == m_allocatedMemory.GetSize() - 1)
				return;
			else
				i++;
		}

		m_allocatedMemory.Erase(m_allocatedMemory.Begin() + i);
	}

	void MemoryProfiler::Profile(const char* filepath)
	{
		auto fileLogger = Logger::CreateNewFileLogger(filepath);
		std::string output = "\n";

		for (auto it = m_allocatedMemory.Begin(); it != m_allocatedMemory.End(); it++)
		{
			std::stringstream ss;
			ss << it->pointer;  

			output += "Found allocated memory at ";
			output += ss.str();
			output += " with size ";
			output += std::to_string(it->size);
			output += " and type ";
			output += it->varName;
			output += '\n';
		}

		fileLogger->info(output);
	}
}
