#include "TextureArray.h"

namespace BlueBell
{
	TextureArray::TextureArray(float width, float height, Texture::Format format, int arraySize)
	{
		m_pTexture = BlueBerry()->Allocate<Texture>();

		D3D11_TEXTURE2D_DESC textDesc;
		textDesc.Width = width;
		textDesc.Height = height;
		textDesc.MipLevels = 1;
		textDesc.ArraySize = arraySize;
		textDesc.Format = (DXGI_FORMAT)format;
		textDesc.SampleDesc.Count = 1;
		textDesc.SampleDesc.Quality = 0;
		textDesc.Usage = D3D11_USAGE_DEFAULT;
		textDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
		textDesc.CPUAccessFlags = D3D10_CPU_ACCESS_READ;
		textDesc.MiscFlags = 0;

		Device* pDevice = Device::GetInstance();

		pDevice->GetDevice()->CreateTexture2D(&textDesc, nullptr, &m_pTexture->m_texture);
		pDevice->GetDevice()->CreateShaderResourceView(m_pTexture->m_texture, nullptr, &m_pTexture->m_shaderResourceView);
	}

	TextureArray::~TextureArray()
	{
		BlueBerry()->Deallocate(m_pTexture);
	}

	void TextureArray::Build()
	{
		Device* pDevice = Device::GetInstance();

		for (int i = 0; i < m_textures.GetSize(); i++)
		{
			Texture* pTexture = m_textures.At(i);

			pDevice->GetDeviceContext()->CopySubresourceRegion(m_pTexture->m_texture, i, 0, 0, 0, pTexture->GetTexture(), 0, nullptr);
		}
	}

	void TextureArray::Bind()
	{
		m_pTexture->Bind();
	}
}