#include "Scene.h"

namespace BlueFBX
{
	Mesh* Scene::GetMesh(const int& id)
	{
		if (id < m_meshes.GetSize())
			return &m_meshes.At(id);
		else
			return nullptr;
	}

	Mesh* Scene::AddMesh(const size_t& polygonCount, const size_t& textureCount, const size_t& uvSetCount, const size_t& vertexCount)
	{
		Mesh mesh = Mesh(polygonCount, uvSetCount, textureCount, vertexCount, m_allocator);

		m_meshes.PushBack(mesh);

		Mesh rmesh = m_meshes.At(m_meshes.GetSize() - 1);

		return m_meshes.End() - 1;
	}

	Mesh* Scene::AddMesh()
	{
		Mesh mesh = Mesh(m_allocator);

		m_meshes.PushBack(mesh);

		return m_meshes.End() - 1;
	}
}
