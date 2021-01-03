#ifndef __SL_INTERMEDIATEREPRESENTATION_H__
#define __SL_INTERMEDIATEREPRESENTATION_H__

#include "Value.h"
#include "Layout.h"
#include "Function.h"
#include "Shader.h"

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

		const std::vector<Value>& GetProperties() const { return properties; }
		const std::vector<Layout>& GetLayouts() const { return layouts; }
		const std::vector<Function>& GetFunctions() const { return functions; }

		const Shader& GetVertexShader() const { return vertexShader; }
		const Shader& GetPixelShader() const { return pixelShader; }

		void Load(std::string&& str);
		void LoadFromFile(std::string&& file);

		void CompileAndSaveToFile(Stage&& stage, std::string filename);
		std::string Compile(Stage&& stage);
		std::string Compile(const Stage& stage);

	private:

		std::vector<Value> properties;
		std::vector<Layout> layouts;
		std::vector<Function> functions;

		std::string GetStringFromStage(const Stage& stage);

		std::vector<std::string> Split(const std::string& str, char&& delimiter);

		Type GetTypeFromString(std::string& sType);
		std::string GetStringFromType(const Type& type);
		void Parse(Hjson::Value& root);

		void ParseShader(Hjson::Value& stage, Shader& outShades);

		Shader vertexShader;
		Shader pixelShader;
	};
}

#endif
