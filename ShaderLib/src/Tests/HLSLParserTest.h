#ifndef __HLSLParserTest_H__
#define __HLSLParserTest_H__

#include "glslang/Public/ShaderLang.h"
#include "spirv_glsl.hpp"

class HLSLParser 
{
public:

	void ReadFile(const char* filePath, char* outputStr);

	void Parse();
};

#endif