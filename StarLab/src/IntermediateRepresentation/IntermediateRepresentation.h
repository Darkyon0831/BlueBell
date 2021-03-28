#ifndef __SL_INTERMEDIATEREPRESENTATION_H__
#define __SL_INTERMEDIATEREPRESENTATION_H__

#include "Value.h"
#include "Layout.h"
#include "Function.h"
#include "Shader.h"
#include "SamplerState.h"
#include "../Defaults/DefaultLayouts.h"

#include <hjson/hjson.h>
#include <vector>

namespace StarLab
{
	class IntermediateRepresentation
	{
	public:

		enum Stage
		{
			STVertex,
			STPixel
		};

		struct PropertyFilter
		{
			PropertyFilter(bool _isContant, bool _isTexture) : isConstant(_isContant), isTexture(_isTexture) {}

			bool isConstant;
			bool isTexture;
		};

		const std::map<Type, PropertyFilter> m_propertyFilter {
			{ Type::SLFloat, PropertyFilter( true, false ) },
			{ Type::SLFloat2, PropertyFilter( true, false ) },
			{ Type::SLFloat3, PropertyFilter( true, false ) },
			{ Type::SLFloat4, PropertyFilter( true, false ) },
			{ Type::SLFloat4x4, PropertyFilter( true, false ) },
			{ Type::SLInt, PropertyFilter( true, false ) },
			{ Type::SLTexture, PropertyFilter( false, true ) }
		};

		const std::vector<Value>& GetProperties() const { return properties; }
		const std::vector<Function>& GetFunctions() const { return functions; }

		const Shader& GetVertexShader() const { return vertexShader; }
		const Shader& GetPixelShader() const { return pixelShader; }

		void Load(const std::string& str);
		void LoadFromFile(const std::string& file);
		void LoadIncludes(const Hjson::Value& includes);

		void CompileAndSaveToFile(const Stage& stage, std::string filename);
		std::string Compile(const Stage& stage);

	private:

		std::vector<Value> properties;
		std::vector<Function> functions;
		Shader vertexShader;
		Shader pixelShader;
		std::vector<SamplerState> samplerStates;

		std::string GetStringFromStage(const Stage& stage);

		std::vector<std::string> Split(const std::string& str, char&& delimiter);

		Type GetTypeFromString(std::string& sType);
		std::string GetStringFromType(const Type& type);
		void Parse(Hjson::Value& root);

		void ParseShader(Hjson::Value& stage, Shader& outShades, const Stage& shaderStage);
	};
}

#endif
