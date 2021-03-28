#ifndef __SL_DEFAULTLAYOUTS_H__
#define __SL_DEFAULTLAYOUTS_H__

#include <vector>

#include "../IntermediateRepresentation/Value.h"

namespace StarLab
{

	class DefaultLayouts
	{
	public:
		static const std::vector<Value> DefaultStarLabIn;
		static const std::vector<Value> DefaultStarLabOut;
		static const std::vector<Value> DefaultStarLabOutPixel;
	};
}

#endif // !SL_DEFAULTLAYOUTS_H__
