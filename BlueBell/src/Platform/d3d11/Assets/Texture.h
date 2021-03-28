#ifndef __BB_TEXTURE_H__
#define __BB_TEXTURE_H__

#include "Asset.h"
#include "../Device.h"

#include <d3d11.h>
#include <DDSTextureLoader.h>
#include <stdlib.h>
#include <codecvt>

namespace BlueBell
{
	class Texture : public Asset
	{
	public:

		friend class TextureArray;

		enum Format
		{
			FORMAT_Unknown = 0,
			FORMAT_R32G32B32A32 = 2,
			FORMAT_R32G32B32 = 6,
			FORMAT_R32G32 = 16,
			FORMAT_R32 = 41
		};

		Texture();
		~Texture();

		void Load(const std::string& texturePath);

		ID3D11Texture2D* GetTexture() { return m_texture; }
		ID3D11ShaderResourceView* GetShaderResourceView() { return m_shaderResourceView; }

		void Free();

		void Bind();

	private:

		ID3D11Texture2D* m_texture;
		ID3D11ShaderResourceView* m_shaderResourceView;
	};
}

#endif // !__BB_TEXTURE_H__
