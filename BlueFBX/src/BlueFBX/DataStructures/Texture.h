#ifndef __BFBX_TEXTURE_H__
#define __BFBX_TEXTURE_H__

#include <string>

namespace BlueFBX
{
	class Texture
	{
	public:

		Texture(const std::string& texturePath) : m_texturePath(texturePath) { }

		const std::string& GetTexturePath() { return m_texturePath; }

	private:
		std::string m_texturePath;
	};
}

#endif // !__BFBX_TEXTURE_H__
