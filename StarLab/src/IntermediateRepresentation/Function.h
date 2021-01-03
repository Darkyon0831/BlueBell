#ifndef __SL_FUNCTION_H__
#define __SL_FUNCTION_H__

#include "Value.h"

#include <vector>

namespace StarLab
{
	class Function
	{
	public:

		friend class IntermediateRepresentation;

		const std::vector<Value>& GetParams() { return params; }
		const Value& GetOut() { return out; }
		const std::string& GetCode() { return code; }
		const std::string& GetName() { return name; }

	private:

		std::vector<Value> params;
		Value out;
		std::string code;
		std::string name;
	};
}

#endif // !__SL_FUNCTION_H__
