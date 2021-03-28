#ifndef __BB_TEXTUREARRAY_H__
#define __BB_TEXTUREARRAY_H__

#include "Texture.h"
#include "Container/Vector.h"

namespace BlueBell
{
	class TextureArray
	{
	public:

		TextureArray(float width, float height, Texture::Format format, int arraySize);
		~TextureArray();

		void Add(Texture* pTexture) { m_textures.PushBack(pTexture); }
		void Clear() { m_textures.Clear(); }

		void Build();
		void Bind();

	private:
		Vector<Texture*> m_textures;
		
		Texture* m_pTexture;
	};
}

#endif // !__BB_TEXTUREARRAY_H__