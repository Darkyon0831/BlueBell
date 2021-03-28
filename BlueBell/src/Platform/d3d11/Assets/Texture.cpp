#include "Texture.h"

namespace BlueBell
{
	void Texture::Free()
	{
		m_texture->Release();
		m_texture = nullptr;
		m_shaderResourceView->Release();
		m_shaderResourceView = nullptr;
	}

	void Texture::Bind()
	{
		Device::GetInstance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_shaderResourceView);
	}

	Texture::Texture()
		: Asset(Assets::Texture)
		, m_texture(nullptr)
		, m_shaderResourceView(nullptr)
	{
		
	}

	Texture::~Texture()
	{
		if (m_texture != nullptr)
			m_texture->Release();

		if (m_shaderResourceView != nullptr)
			m_shaderResourceView->Release();
	}

	void Texture::Load(const std::string& texturePath)
	{
		ID3D11Resource* pResource = nullptr;
		m_shaderResourceView = nullptr;
		m_texture = nullptr;

		std::wstring vsWS = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(texturePath);

		HRESULT hr = DirectX::CreateDDSTextureFromFile(Device::GetInstance()->GetDevice(), vsWS.c_str(), &pResource, &m_shaderResourceView);

		pResource->QueryInterface(IID_ID3D11Texture2D, reinterpret_cast<void**>(&m_texture));
	}
}
