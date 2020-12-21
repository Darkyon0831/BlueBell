#ifndef __BB_MEMORYPROFILER_H__
#define __BB_MEMORYPROFILER_H__

#include "../Container/Vector.h"

namespace BlueBell
{
	class BB_API MemoryProfiler
	{
	public:

		struct AllocatedMemory
		{
			AllocatedMemory(size_t _size, void* _pointer, const char* _varName) : size(_size), pointer(_pointer), varName(_varName) {} 

			size_t size;
			void* pointer;
			const char* varName;
		};

		MemoryProfiler() = default;
		~MemoryProfiler() = default;

		void Add(size_t size, void* memory, const char* varName);
		void Remove(void* memory);

		void Profile(const char* filepath);
			
	private:
		Vector<AllocatedMemory> m_allocatedMemory;
	};
}

#endif 
