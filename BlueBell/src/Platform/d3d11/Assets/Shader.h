#ifndef __BB_SHADER_H__
#define __BB_SHADER_H__

#include "Asset.h"

#include <d3d11.h>

namespace BlueBell
{
	class Shader : public Asset
	{
	public:

		Shader();
		~Shader();

		void Load(const char* vsShaderFile, const char* psShaderFile);

		ID3D10Blob* GetVSBlob() { return m_pVSShaderBlob; }
		ID3D10Blob* GetPSBlob() { return m_pPSShaderBlob; }

		ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
		ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }

		void Bind();

	private:

		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;

		ID3D10Blob* m_pVSShaderBlob;
		ID3D10Blob* m_pPSShaderBlob;
	};
}

#endif // !__BB_SHADER_H__
