#include "Texture.h"

namespace BlueBell
{
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
}
