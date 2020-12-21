#ifndef __BB_TEXTURE_H__
#define __BB_TEXTURE_H__

#include "Asset.h"

#include <d3d11.h>

namespace BlueBell
{
	class Texture : public Asset
	{
	public:
		Texture();
		~Texture();

		ID3D11Texture2D* GetTexture() { return m_texture; }
		ID3D11ShaderResourceView* GetShaderResourceView() { return m_shaderResourceView; }

	private:
		ID3D11Texture2D* m_texture;
		ID3D11ShaderResourceView* m_shaderResourceView;
	};
}

#endif // !__BB_TEXTURE_H__
