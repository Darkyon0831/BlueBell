#include "HLSLParserTest.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

int HLSLParser::ReadFile(const char* filePath, char*& outputStr)
{
	std::ifstream file;
	file.open(filePath, std::ios::in);

	std::string line;
	std::stringstream ss;

	if (file.is_open())
	{
		while (std::getline(file,line))
		{
		  ss << line << '\n';
		}

		file.close();
	}

	ss.seekg(0, ss.end);
	int count = ss.tellg();
	ss.seekg (0, ss.beg);

	outputStr = new char[count + 1];

	ss.read(outputStr, count);

	memset(outputStr + count, 0x00, 1);

	return count;
}

void HLSLParser::SaveDebugLogToFile(const char* debugLog)
{
	const char* filePath = "../../game/fileoutputs/debugLog.txt";

	std::ofstream file;
	file.open(filePath, std::ios::out);

	file.write(debugLog, strlen(debugLog));

	file.close();
}

void HLSLParser::SaveShaderCode(const char* shaderCode, const char* fileName, const char* extension)
{
	std::stringstream ss;

	ss << "../../game/fileoutputs/" << fileName << extension;

	ss.seekg(0, ss.end);
	int count = ss.tellg();
	ss.seekg (0, ss.beg);

	char* filePath = new char[count + 1];

	ss.read(filePath, count);

	memset(filePath + count, 0x00, 1);

	std::ofstream file;

	file.open(filePath, std::ios::out);

	file.write(shaderCode, strlen(shaderCode));

	file.close();
}

std::string HLSLParser::ConvertSVRToGlsl(glslang::TProgram* program, EShLanguage stage)
{
	std::vector<unsigned int> spirv;

	const glslang::TIntermediate* intermediate = program->getIntermediate(stage);
	glslang::GlslangToSpv(*intermediate, spirv);

	spirv_cross::CompilerGLSL glsl(std::move(spirv));

	spirv_cross::CompilerGLSL::Options options;
	options.version = 310;
	options.es = true;
	glsl.set_common_options(options);

	return glsl.compile();
}

void HLSLParser::Parse()
{
	glslang::InitializeProcess();

	std::string vsShaderPath = "../../game/shaders/basictriangleVS.hlsl";
	std::string psShaderPath = "../../game/shaders/basictrianglePS.hlsl";
	
	char* vsStr = nullptr;
	char* psStr = nullptr;

	int vsCount = ReadFile(vsShaderPath.c_str(), vsStr);
	int psCount = ReadFile(psShaderPath.c_str(), psStr);


	glslang::TShader vsShader(EShLanguage::EShLangVertex);
	glslang::TShader psShader(EShLanguage::EShLangFragment);

	vsShader.setStrings(&vsStr, 1);
	psShader.setStrings(&psStr, 1);

	vsShader.setEntryPoint("main");

	vsShader.setEnvInput(glslang::EShSource::EShSourceHlsl, EShLanguage::EShLangVertex, glslang::EShClient::EShClientOpenGL, 100);
	vsShader.setEnvClient(glslang::EShClient::EShClientOpenGL, glslang::EShTargetClientVersion::EShTargetOpenGL_450);
	vsShader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);

	psShader.setEntryPoint("main");

	psShader.setEnvInput(glslang::EShSource::EShSourceHlsl, EShLanguage::EShLangFragment, glslang::EShClient::EShClientOpenGL, 100);
	psShader.setEnvClient(glslang::EShClient::EShClientOpenGL, glslang::EShTargetClientVersion::EShTargetOpenGL_450);
	psShader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);

	TBuiltInResource resources;

	vsShader.parse(&resources, 0, false, EShMessages::EShMsgDefault);
	psShader.parse(&resources, 0, false, EShMessages::EShMsgDefault);

	glslang::TProgram program;
	program.addShader(&vsShader);
	program.addShader(&psShader);

	program.link(EShMessages::EShMsgDefault);

	program.buildReflection();

	int index = program.getReflectionIndex("vIn.position");
	int liveBlocks = program.getNumLiveUniformBlocks();
	int liveInputs = program.getNumPipeInputs();
	int liveVariables = program.getNumUniformVariables();

	const glslang::TObjectReflection& reflection = program.getPipeInput(1);

	std::string glslVertexSource = ConvertSVRToGlsl(&program, EShLanguage::EShLangVertex);
	std::string glslFragmentSource = ConvertSVRToGlsl(&program, EShLanguage::EShLangFragment);

	SaveShaderCode(glslVertexSource.c_str(), "hlslVertexSource", ".hlsl");
	SaveShaderCode(glslFragmentSource.c_str(), "hlslFragmentSource", ".hlsl");

	glslang::FinalizeProcess();
}
