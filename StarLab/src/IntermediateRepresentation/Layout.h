#ifndef __SL_LAYOUT_H__
#define __SL_LAYOUT_H__

#include "Value.h"

#include <vector>

namespace StarLab
{
	class Layout
	{
	public:

		friend class IntermediateRepresentation;

		const std::string& GetName() const { return name; }
		const std::vector<Value>& GetValues() const { return values; }

	private:

		std::string name;
		std::vector<Value> values;
	};
}

#endif // !__SL_LAYOUT_H__
