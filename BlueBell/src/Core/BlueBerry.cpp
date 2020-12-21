#include "BlueBerry.h"

namespace BlueBell
{
	Allocator<FreeListAllocator>* SBlueBerry::BlueBerry = nullptr;

	void InitBlueBerry()
	{ 
		SBlueBerry::BlueBerry = new Allocator<FreeListAllocator>(BLUEBERRY_BUFFER_SIZE, FreeListAllocator::EFindBest); 
		SBlueBerry::BlueBerry->EnableProfiler();
	}

	void DeleteBlueBerry()
	{
		int i = 0;		
		delete SBlueBerry::BlueBerry;
	}

	Allocator<FreeListAllocator>* BlueBerry()
	{ 
		return SBlueBerry::BlueBerry; 
	}
}