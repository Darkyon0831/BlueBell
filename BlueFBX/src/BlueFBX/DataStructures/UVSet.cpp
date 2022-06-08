#include "UVSet.h"

namespace BlueFBX
{
	UVSet::UVSet(size_t numUVS, BlueBell::IAllocator* allocator)
		: m_numUVs(numUVS)
		, m_allocator(allocator)
	{
		m_uvs = reinterpret_cast<Vector2D*>(allocator->Allocate(numUVS * sizeof(Vector2D), alignof(Vector2D)));
	}

	UVSet::~UVSet()
	{
		m_allocator->Deallocate(reinterpret_cast<void**>(&m_uvs));
	}

	void UVSet::SetUV(const int& id, const Vector2D& uv)
	{
		if (id < m_numUVs)
			m_uvs[id] = uv;
	}

	void UVSet::SetTextureID(const int& id)
	{
		m_textureID = id;
	}

	const Vector2D& UVSet::GetUV(const int& id)
	{
		if (id < m_numUVs)
			return m_uvs[id];
		else
			return Vector2D { 0.0f, 0.0f };
	}

	const int& UVSet::GetTextureID()
	{
		return m_textureID;
	}
}

