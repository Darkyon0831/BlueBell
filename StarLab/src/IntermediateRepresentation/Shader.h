#ifndef __SL_SHADER_H__
#define __SL_SHADER_H__

#include "Value.h"
#include "Function.h"
#include "SamplerState.h"

#include <vector>

namespace StarLab
{
	class Shader
	{
	public:

		friend class IntermediateRepresentation;

		const std::vector<Function>& GetExportedFunctions() const { return exportedFunctions; }
		const std::vector<Value>& GetIn() const { return in; }
		const std::vector<Value>& GetUsedProperties() const { return usedProperties; }
		const std::vector<Value>& GetOut() const { return out; }
		const std::string& GetCode() const { return code; }
		const SamplerState& GetSamplerState() const { return samplerState; }

	private:

		SamplerState samplerState;
		std::vector<Function> exportedFunctions;	
		std::vector<Value> in;
		std::vector<Value> usedProperties;
		std::vector<Value> out;
		std::string code;
	};
}

#endif // !__SL_SHADER_H__
