#ifndef __BB_BLUEBERRY_H__
#define __BB_BLUEBERRY_H__

#include "../Memory/Allocator.h"
#include "../Memory/FreeListAllocator.h"

#define BLUEBERRY_BUFFER_SIZE 1024 * 1024 * 4

namespace BlueBell
{
	struct BB_API SBlueBerry
	{
		static Allocator<FreeListAllocator>* BlueBerry;
	};

	BB_API void DeleteBlueBerry();
	BB_API void InitBlueBerry();
	BB_API Allocator<FreeListAllocator>* BlueBerry();
}

#endif 

