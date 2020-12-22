#include "HLSLParserTest.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void HLSLParser::ReadFile(const char* filePath, char* outputStr)
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

	outputStr = new char[ss.gcount() + 1];

	ss.get(outputStr, ss.gcount());

	memset(&outputStr[ss.gcount()], 0x00, 1);
}

void HLSLParser::Parse()
{
	std::string vsShaderPath = "../../game/shaders/basictriangleVS.hlsl";
	std::string psShaderPath = "../../game/shaders/basictrianglePS.hlsl";

	char* vsStr = nullptr;
	char* psStr = nullptr;

	ReadFile(vsShaderPath.c_str(), vsStr);
	ReadFile(psShaderPath.c_str(), psStr);

	int i = 0;

	glslang::TShader vsShader(EShLanguage::EShLangVertex);
	glslang::TShader psShader(EShLanguage::EShLangFragment);
	
	glslang::TProgram program;

	program.addShader(&vsShader);
	program.addShader(&psShader);


}
