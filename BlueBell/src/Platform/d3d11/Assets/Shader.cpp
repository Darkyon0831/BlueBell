#include "Shader.h"
#include "../Device.h"
#include "../../../Logging/Logger.h"

#include <string>
#include <d3dcompiler.h>

namespace BlueBell
{
	Shader::Shader()
		: Asset(Asset::Shader)
		, m_pVertexShader(nullptr)
		, m_pPixelShader(nullptr)
		, m_pVSShaderBlob(nullptr)
		, m_pPSShaderBlob(nullptr)
	{

	}

	Shader::~Shader()
	{
		m_pVertexShader->Release();
		m_pPixelShader->Release();
		m_pVSShaderBlob->Release();
		m_pPSShaderBlob->Release();
	}

	void Shader::Load(const char* vsShaderFile, const char* psShaderFile)
	{
		ID3D10Blob* pVSErrorBlob = nullptr;
		ID3D10Blob* pPSErrorBlob = nullptr;

		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		size_t vsSize = strlen(vsShaderFile);
		size_t psSize = strlen(psShaderFile);

		std::wstring vsWFile = std::wstring(vsSize, L'#');
		mbstowcs(&vsWFile[0], vsShaderFile, vsSize);

		std::wstring psWFile = std::wstring(psSize, L'#');
		mbstowcs(&psWFile[0], psShaderFile, psSize);

		unsigned int vsCompileFlags;
		unsigned int psCompileFlags;

		#ifdef DEBUG
			vsCompileFlags = psCompileFlags = 0;
		#endif

		#ifdef RELEASE
			vsCompileFlags = psCompileFlags = D3DCOMPILE_OPTIMIZATION_LEVEL2;
		#endif // RELEASE
		
		auto fileLogger = Logger::CreateNewFileLogger("../../game/fileoutputs/ShaderError.txt");

		HRESULT hr = D3DCompileFromFile(
			vsWFile.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"vs_5_0",
			D3DCOMPILE_DEBUG,
			0,
			&m_pVSShaderBlob,
			&pVSErrorBlob);

		if (FAILED(hr))
		{
			fileLogger->info(reinterpret_cast<char*>(pVSErrorBlob->GetBufferPointer()));
			BB_CHECK_HR(hr, reinterpret_cast<char*>(pVSErrorBlob->GetBufferPointer()));
		}

		hr = D3DCompileFromFile(
			psWFile.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"ps_5_0",
			D3DCOMPILE_DEBUG,
			0,
			&m_pPSShaderBlob,
			&pPSErrorBlob);

		if (FAILED(hr))
		{
			fileLogger->info(reinterpret_cast<char*>(pPSErrorBlob->GetBufferPointer()));
			BB_CHECK_HR(hr, reinterpret_cast<char*>(pPSErrorBlob->GetBufferPointer()));
		}
			

		BB_CHECK_HR(pDevice->CreateVertexShader(
			m_pVSShaderBlob->GetBufferPointer(),
			m_pVSShaderBlob->GetBufferSize(),
			nullptr,
			&m_pVertexShader
		), "Could not create vertex shader")
		
		BB_CHECK_HR(pDevice->CreatePixelShader(
			m_pPSShaderBlob->GetBufferPointer(),
			m_pPSShaderBlob->GetBufferSize(),
			nullptr, 
			&m_pPixelShader
		), "Could not create pixel shader")

		int size = sizeof(*m_pVertexShader);

		int intAddress = *(int*)m_pVertexShader;
		int intAddressPixel = *(int*)m_pPixelShader;

		const FreeListAllocator* allocator = BlueBerry()->GetAllocator();

		int value = BlueBerry()->GetIntValueOfMemory(m_pVertexShader, 4);
		int valuePixel = BlueBerry()->GetIntValueOfMemory(m_pPixelShader, 4);

		if(pVSErrorBlob != nullptr)
			pVSErrorBlob->Release();

		if (pPSErrorBlob != nullptr)
			pPSErrorBlob->Release();

		int i = 0;
	}

	void Shader::Bind()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		int size = sizeof(*m_pVertexShader);

		int value = BlueBerry()->GetIntValueOfMemory(m_pVertexShader, 4);
		
		pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
		pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

		int i = 0;
	}
}
