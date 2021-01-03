#ifndef __HLSLParserTest_H__
#define __HLSLParserTest_H__

#include "glslang/Public/ShaderLang.h"
#include "glslang/SPIRV/GlslangToSpv.h"
#include "glslang/SPIRV/disassemble.h"

#include "spirv_glsl.hpp"
#include "spirv_hlsl.hpp"

class HLSLParser 
{
public:

	int ReadFile(const char* filePath, char*& outputStr);
	void SaveDebugLogToFile(const char* debugLog);

	void SaveShaderCode(const char* shaderCode, const char* fileName, const char* extension);
	std::string ConvertSVRToGlsl(glslang::TProgram* program, EShLanguage stage);

	void Parse();
};

#endif