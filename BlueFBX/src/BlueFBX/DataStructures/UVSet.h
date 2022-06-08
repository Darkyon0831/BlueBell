#ifndef __BFBX_UVSET_H__
#define __BFBX_UVSET_H__

#include "Vectors.h"

#include <Memory/IAllocator.h>

namespace BlueFBX
{
	class UVSet
	{
	public:

		UVSet(size_t numUVS, BlueBell::IAllocator* pAllocator);
		~UVSet();

		void SetUV(const int& id, const Vector2D& uv);
		void SetTextureID(const int& id);

		const Vector2D& GetUV(const int& id);
		const int& GetTextureID();

	private:

		int m_textureID;
		Vector2D* m_uvs;

		size_t m_numUVs;

		BlueBell::IAllocator* m_allocator;
	};
}

#endif // !__BFBX_UVSET_H__
