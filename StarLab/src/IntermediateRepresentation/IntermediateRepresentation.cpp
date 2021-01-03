#include "IntermediateRepresentation.h"

#include <sstream>
#include <fstream>

namespace StarLab
{
	void IntermediateRepresentation::Load(std::string&& str)
	{
		Hjson::Value& root = Hjson::Unmarshal(str);

		Parse(root);
	}

	void IntermediateRepresentation::LoadFromFile(std::string&& file)
	{
		Hjson::Value& root = Hjson::UnmarshalFromFile(file);

		Parse(root);
	}

	void IntermediateRepresentation::CompileAndSaveToFile(Stage&& stage, std::string filename)
	{
		std::string compiledShader = Compile(stage);

		std::stringstream filePath;
		filePath << "../../game/fileoutputs/" << filename << ".hlsl";

		std::ofstream out;
		out.open(filePath.str().c_str());

		out.write(compiledShader.c_str(), compiledShader.size());

		out.close();
	}

	std::string IntermediateRepresentation::Compile(Stage&& stage)
	{
		const Shader* shader;
		std::string compiledShader;
		std::stringstream compiledShaderBuilder;

		if (stage == Stage::STVertex)
			shader = &vertexShader;
		else
			shader = &pixelShader;

		// Write constant buffer layout
		compiledShaderBuilder << "cbuffer ConstantBuffer : register(b0)\n{\n";

		for (int i = 0; i < shader->usedProperties.size(); i++)
		{
			const Value& value = shader->usedProperties.at(i);

			compiledShaderBuilder << "\t" << GetStringFromType(value.type).c_str() << " " << value.name.c_str() << ";\n";
		}

		compiledShaderBuilder << "} Properties;\n\n";

		// Write in

		compiledShaderBuilder << "struct " << GetStringFromStage(stage).c_str() << "Input" << "\n{\n";

		for (int i = 0; i < shader->in.values.size(); i++)
		{
			const Value& value = shader->in.values.at(i);

			compiledShaderBuilder << "\t" << GetStringFromType(value.type) << " " << value.name << " : " << value.semantic << ";\n";
		}

		compiledShaderBuilder << "}\n\n";

		// Write out

		compiledShaderBuilder << "struct " << GetStringFromStage(stage).c_str() << "Output" << "\n{\n";

		for (int i = 0; i < shader->out.size(); i++)
		{
			const Value& value = shader->out.at(i);

			compiledShaderBuilder << "\t" << GetStringFromType(value.type) << " " << value.name << " : " << value.semantic << ";\n";
		}

		compiledShaderBuilder << "}\n\n";

		// Write functions

		for (int i = 0; i < shader->exportedFunctions.size(); i++)
		{
			Function function = shader->exportedFunctions.at(i);

			compiledShaderBuilder << GetStringFromType(function.out.type).c_str() << " " << function.name.c_str() << "(";

			for (int j = 0; j < function.params.size(); j++)
			{
				const Value& param = function.params.at(j);

				compiledShaderBuilder << GetStringFromType(param.type) << " " << param.name.c_str();

				if (j < function.params.size() - 1)
					compiledShaderBuilder << ", ";
			}

			compiledShaderBuilder << ")\n{\n";

			std::vector<std::string> functionCodeSplit = Split(function.code, '\n');

			for (int j = 0; j < functionCodeSplit.size(); j++)
			{
				const std::string& str = functionCodeSplit.at(j);

				compiledShaderBuilder << "\t" << str.c_str() << "\n";
			}

			compiledShaderBuilder << "}\n\n";
		}

		// Write main code

		compiledShaderBuilder << GetStringFromStage(stage).c_str() << "Output main(" << GetStringFromStage(stage).c_str() << "Input In)\n{\n\t" << GetStringFromStage(stage).c_str() << "Output Out;\n";

		std::vector<std::string> mainCodeSplit = Split(shader->code, '\n');

		for (int i = 0; i < mainCodeSplit.size(); i++)
		{
			std::string str = mainCodeSplit.at(i);

			compiledShaderBuilder << "\t" << str.c_str() << "\n";
		}

		compiledShaderBuilder << "\n\treturn Out;\n}";

		compiledShader = compiledShaderBuilder.str();

		return compiledShader;
	}

	std::string IntermediateRepresentation::Compile(const Stage& stage)
	{
		const Shader* shader;
		std::string compiledShader;
		std::stringstream compiledShaderBuilder;

		if (stage == Stage::STVertex)
			shader = &vertexShader;
		else
			shader = &pixelShader;

		// Write constant buffer layout

		if (shader->usedProperties.size() > 0)
		{
			compiledShaderBuilder << "cbuffer ConstantBuffer : register(b0)\n{\n";

			for (int i = 0; i < shader->usedProperties.size(); i++)
			{
				const Value& value = shader->usedProperties.at(i);

				compiledShaderBuilder << "\t" << GetStringFromType(value.type).c_str() << " " << value.name.c_str() << ";\n";
			}

			compiledShaderBuilder << "};\n\n";
		}

		// Write in

		compiledShaderBuilder << "struct " << GetStringFromStage(stage).c_str() << "Input" << "\n{\n";

		for (int i = 0; i < shader->in.values.size(); i++)
		{
			const Value& value = shader->in.values.at(i);

			compiledShaderBuilder << "\t" << GetStringFromType(value.type) << " " << value.name << " : " << value.semantic << ";\n";
		}

		compiledShaderBuilder << "};\n\n";

		// Write out

		compiledShaderBuilder << "struct " << GetStringFromStage(stage).c_str() << "Output" << "\n{\n";

		for (int i = 0; i < shader->out.size(); i++)
		{
			const Value& value = shader->out.at(i);

			compiledShaderBuilder << "\t" << GetStringFromType(value.type) << " " << value.name << " : " << value.semantic << ";\n";
		}

		compiledShaderBuilder << "};\n\n";

		// Write functions

		for (int i = 0; i < shader->exportedFunctions.size(); i++)
		{
			Function function = shader->exportedFunctions.at(i);

			compiledShaderBuilder << GetStringFromType(function.out.type).c_str() << " " << function.name.c_str() << "(";

			for (int j = 0; j < function.params.size(); j++)
			{
				const Value& param = function.params.at(j);

				compiledShaderBuilder << GetStringFromType(param.type) << " " << param.name.c_str();

				if (j < function.params.size() - 1)
					compiledShaderBuilder << ", ";
			}

			compiledShaderBuilder << ")\n{\n";

			std::vector<std::string> functionCodeSplit = Split(function.code, '\n');

			for (int j = 0; j < functionCodeSplit.size(); j++)
			{
				const std::string& str = functionCodeSplit.at(j);

				compiledShaderBuilder << "\t" << str.c_str() << "\n";
			}

			compiledShaderBuilder << "};\n\n";
		}

		// Write main code

		compiledShaderBuilder << GetStringFromStage(stage).c_str() << "Output main(" << GetStringFromStage(stage).c_str() << "Input In)\n{\n\t" << GetStringFromStage(stage).c_str() << "Output Out;\n";

		std::vector<std::string> mainCodeSplit = Split(shader->code, '\n');

		for (int i = 0; i < mainCodeSplit.size(); i++)
		{
			std::string str = mainCodeSplit.at(i);

			compiledShaderBuilder << "\t" << str.c_str() << "\n";
		}

		compiledShaderBuilder << "\n\treturn Out;\n};";

		compiledShader = compiledShaderBuilder.str();

		return compiledShader;
	}

	std::string IntermediateRepresentation::GetStringFromStage(const Stage& stage)
	{
		if (stage == Stage::STPixel)
			return "Pixel";
		else 
			return "Vertex";
	}

	std::vector<std::string> IntermediateRepresentation::Split(const std::string& str, char&& delimiter)
	{
		std::vector<std::string> out;
		std::vector<int> foundIndexes;

		auto it = std::find(str.begin(), str.end(), delimiter);

		if (it == str.end())
		{
			out.push_back(str);
			return out;
		}

		while (it != str.end())
		{
			int indexFromStart = it - str.begin();

			foundIndexes.push_back(indexFromStart);

			it = std::find(str.begin() + indexFromStart + 1, str.end(), delimiter);
		}

		int currentIndex = 0;
		int nextIndex = foundIndexes.at(0);
		int currentFoundIndexes = 1;

		while (currentIndex < str.size())
		{
			int length = nextIndex - currentIndex;

			out.push_back(str.substr(currentIndex, length));

			currentIndex = nextIndex + 1;

			if (currentFoundIndexes < foundIndexes.size())
			{
				nextIndex = foundIndexes.at(currentFoundIndexes);
				currentFoundIndexes++;
			}
			else
			{
				nextIndex = str.size();
			}
		}

		return out;
	}

	Type IntermediateRepresentation::GetTypeFromString(std::string& sType)
	{
		if (sType == "float")
			return Type::SLFloat;
		else if (sType == "float2")
			return Type::SLFloat2;
		else if (sType == "float3")
			return Type::SLFloat3;
		else if (sType == "float4")
			return Type::SLFloat4;
		else if (sType == "float4x4")
			return Type::SLFloat4x4;
		else if (sType == "int")
			return Type::SLInt;
		else
			return Type::SLUnknown;
	}

	std::string IntermediateRepresentation::GetStringFromType(const Type& type)
	{
		if (type == Type::SLFloat)
			return "float";
		else if (type == Type::SLFloat2)
			return "float2";
		else if (type == Type::SLFloat3)
			return "float3";
		else if (type == Type::SLFloat4)
			return "float4";
		else if (type == Type::SLFloat4x4)
			return "float4x4";
		else if (type == Type::SLInt)
			return "int";
		else
			return "";
	}

	void IntermediateRepresentation::Parse(Hjson::Value& root)
	{
		// Get properties

		Hjson::Value& properties = root["Properties"];

		if (properties.defined())
		{
			for (int i = 0; i < properties.size(); i++)
			{
				Hjson::Value& property = properties[i];

				Value value;

				value.type = GetTypeFromString(property["type"].to_string());
				value.name = property["name"].to_string();

				this->properties.push_back(value);
			}
		}

		// Get layouts

		Hjson::Value& layouts = root["Layouts"];

		if (layouts.defined())
		{
			for (auto& it = layouts.begin(); it != layouts.end(); it++)
			{
				Layout layout;

				layout.name = it->first;
				
				Hjson::Value layoutValues = it->second;

				for (int i = 0; i < layoutValues.size(); i++)
				{
					Hjson::Value layoutValue = layoutValues[i];
					Value value;

					value.type = GetTypeFromString(layoutValue["type"].to_string());
					value.name = layoutValue["name"].to_string();
					value.semantic = layoutValue["semantic"].to_string();

					layout.values.push_back(value);
				}

				this->layouts.push_back(layout);
			}
		}

		// Get functions

		Hjson::Value functions = root["Functions"];

		if (functions.defined())
		{
			for (auto& it = functions.begin(); it != functions.end(); it++)
			{
				Hjson::Value functionValue = it->second;
				Function function;

				function.name = it->first;

				Hjson::Value functionParams = functionValue["Params"];

				for (int i = 0; i < functionParams.size(); i++)
				{
					Hjson::Value paramValue = functionParams[i];
					Value param;

					param.type = GetTypeFromString(paramValue["type"].to_string());
					param.name = paramValue["name"].to_string();

					function.params.push_back(param);
				}

				Hjson::Value outValue = functionValue["Out"];
				Value out;

				out.type = GetTypeFromString(outValue["type"].to_string());

				function.out = out;
				function.code = functionValue["Code"].to_string();

				this->functions.push_back(function);
			}
		}

		// Get vertex and pixel

		ParseShader(root["Stages"]["Vertex"], vertexShader);
		ParseShader(root["Stages"]["Pixel"], pixelShader);
	}

	void IntermediateRepresentation::ParseShader(Hjson::Value& stage, Shader& outShader)
	{
		Hjson::Value exportedFunctionsValue = stage["ExportedFunctions"];

		if (exportedFunctionsValue.defined())
		{
			for (int i = 0; i < exportedFunctionsValue.size(); i++)
			{
				std::string functionName = exportedFunctionsValue[i].to_string();

				for (int i = 0; i < functions.size(); i++)
				{
					if (functions.at(i).name == functionName)
					{
						outShader.exportedFunctions.push_back(functions.at(i));
						break;
					}
				}
			}
		}

		Hjson::Value in = stage["In"];

		std::string& nameLookingFor = in.to_string();
		for (auto& it = layouts.begin(); it != layouts.end(); it++)
		{
			if (it->name == nameLookingFor)
			{
				outShader.in = *it;
				break;
			}
		}

		Hjson::Value usedPropertiesValue = stage["Properties"];

		if (usedPropertiesValue.defined())
		{
			for (int i = 0; i < usedPropertiesValue.size(); i++)
			{
				Hjson::Value usedPropertyName = usedPropertiesValue[i];

				for (int i = 0; i < properties.size(); i++)
				{
					if (properties.at(i).name == usedPropertyName)
					{
						outShader.usedProperties.push_back(properties.at(i));
					}
				}
			}
		}

		Hjson::Value outValue = stage["Out"];

		for (int i = 0; i < outValue.size(); i++)
		{
			Hjson::Value out = outValue[i];
			Value value;

			value.type = GetTypeFromString(out["type"].to_string());
			value.name = out["name"].to_string();
			value.semantic = out["semantic"].to_string();

			outShader.out.push_back(value);
		}

		outShader.code = stage["Code"].to_string();
	}
}
