#include "IntermediateRepresentation.h"

#include <sstream>
#include <fstream>

namespace StarLab
{
	void IntermediateRepresentation::Load(const std::string& str)
	{
		Hjson::Value& root = Hjson::Unmarshal(str);

		Parse(root);
	}

	void IntermediateRepresentation::LoadFromFile(const std::string& file)
	{
		Hjson::Value& root = Hjson::UnmarshalFromFile(file);

		Parse(root);
	}

	void IntermediateRepresentation::LoadIncludes(const Hjson::Value& includes)
	{
		if (includes.defined())
		{
			for (int i = 0; i < includes.size(); i++)
			{
				std::string file = includes[i].to_string();

				std::stringstream ss;
				ss << "../../game/shaders/";
				ss << file.c_str();
				ss << ".starlab";

				Hjson::Value& root = Hjson::UnmarshalFromFile(ss.str());

				Parse(root);
			}
		}
	}

	void IntermediateRepresentation::CompileAndSaveToFile(const Stage& stage, std::string filename)
	{
		std::string compiledShader = Compile(stage);

		std::stringstream filePath;

		if (stage == Stage::STVertex)
			filePath << "../../game/shaders/temp/" << filename << "Vertex" << ".hlsl";
		else
			filePath << "../../game/shaders/temp/" << filename << "Pixel" << ".hlsl";

		std::ofstream out;
		out.open(filePath.str().c_str());

		out.write(compiledShader.c_str(), compiledShader.size());

		out.close();
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

		std::vector<Value*> constants;
		std::vector<Value*> textures;

		for (int i = 0; i < shader->usedProperties.size(); i++)
		{
			const Value& value = shader->usedProperties.at(i);

			auto filterPair = m_propertyFilter.find(value.type);

			if (filterPair != m_propertyFilter.end())
			{
				if (filterPair->second.isConstant)
				{
					constants.push_back(const_cast<Value*>(&value));
				}
				else if (filterPair->second.isTexture)
				{
					textures.push_back(const_cast<Value*>(&value));
				}
			}
		}

		// Write constant buffer layout

		if (constants.size() > 0)
		{
			compiledShaderBuilder << "cbuffer ConstantBuffer : register(b0)\n{\n";

			for (int i = 0; i < constants.size(); i++)
			{
				const Value& value = *constants.at(i);

				compiledShaderBuilder << "\t" << GetStringFromType(value.type).c_str() << " " << value.name.c_str() << ";\n";
			}

			compiledShaderBuilder << "};\n\n";
		}

		// Write textures

		if (textures.size() > 0)
		{
			for (int i = 0; i < textures.size(); i++)
			{
				const Value& value = *textures.at(i);

				compiledShaderBuilder << "Texture2D " << value.name.c_str() << " : register(t" << i << ")" << ";\n";
			}

			compiledShaderBuilder << "\n";
		}

		// Write sampler state

		if (shader->GetSamplerState().GetName() != "")
			compiledShaderBuilder << "SamplerState " << shader->GetSamplerState().GetName().c_str() << " : register(s0);" << "\n\n"; 

		// Write in

		compiledShaderBuilder << "struct " << GetStringFromStage(stage).c_str() << "Input" << "\n{\n";

		for (int i = 0; i < shader->in.size(); i++)
		{
			const Value& value = shader->in.at(i);

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
		else if (sType == "texture")
			return Type::SLTexture;
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

		// Get Sampler States

		Hjson::Value hSamplerStates = root["SamplerStates"];

		if (hSamplerStates.defined())
		{
			for (auto& it = hSamplerStates.begin(); it != hSamplerStates.end(); it++)
			{
				SamplerState samplerState;
				samplerState.m_name = it->first;

				Hjson::Value& samplerValue = it->second;
				
				if (samplerValue["Filter"].defined())
					samplerState.SetFilterFromString(samplerValue["Filter"].to_string());

				if (samplerValue["AddressU"].defined())
					samplerState.SetAddressModeFromString(samplerValue["AddressU"].to_string(), samplerState.m_addressU);

				if (samplerValue["AddressV"].defined())
					samplerState.SetAddressModeFromString(samplerValue["AddressV"].to_string(), samplerState.m_addressV);

				if (samplerValue["AddressW"].defined())
					samplerState.SetAddressModeFromString(samplerValue["AddressW"].to_string(), samplerState.m_addressW);

				if (samplerValue["MipLodBias"].defined())
					samplerState.m_mipLodBias = static_cast<float>(samplerValue["MipLodBias"].to_double());

				if (samplerValue["MaxAnisotropy"].defined())
					samplerState.m_maxAnisotropy = static_cast<unsigned int>(samplerValue["MipLodBias"].to_int64());

				if (samplerValue["ComparisonFunc"].defined())
					samplerState.SetComparisonFuncFromString(samplerValue["ComparisonFunc"].to_string());

				if (samplerValue["MinLod"].defined())
					samplerState.m_minLod = static_cast<float>(samplerValue["MinLod"].to_double());

				if (samplerValue["MaxLod"].defined())
					samplerState.m_maxLod = static_cast<float>(samplerValue["MaxLod"].to_double());

				samplerStates.push_back(samplerState);
			}
		}

		// Get vertex and pixel

		ParseShader(root["Stages"]["Vertex"], vertexShader, Stage::STVertex);
		ParseShader(root["Stages"]["Pixel"], pixelShader, Stage::STPixel);

		LoadIncludes(root["Includes"]);
	}

	void IntermediateRepresentation::ParseShader(Hjson::Value& stage, Shader& outShader, const Stage& shaderStage)
	{
		if (stage.defined() == false)
			return;

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

		if (shaderStage == Stage::STVertex)
			outShader.in = DefaultLayouts::DefaultStarLabIn;
		else
			outShader.in = DefaultLayouts::DefaultStarLabOut;

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

		Hjson::Value& usedSamplerStates = stage["SamplerState"];

		if (usedSamplerStates.defined())
		{
			Hjson::Value usedSamplerStateName = usedSamplerStates;

			for (int i = 0; i < samplerStates.size(); i++)
			{
				if (samplerStates.at(i).m_name == usedSamplerStateName)
				{
					outShader.samplerState = samplerStates.at(i);
				}
			}
		}

		if (shaderStage == Stage::STVertex)
			outShader.out = DefaultLayouts::DefaultStarLabOut;
		else
			outShader.out = DefaultLayouts::DefaultStarLabOutPixel;

		if (outShader.code == "")
			outShader.code = stage["Code"].to_string();
		else
		{
			outShader.code += "\n";
			outShader.code += stage["Code"].to_string();
		}
	}
}
