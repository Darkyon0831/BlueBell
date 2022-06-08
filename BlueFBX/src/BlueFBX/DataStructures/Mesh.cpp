#include "Mesh.h"

namespace BlueFBX
{
	Mesh::Mesh(BlueBell::IAllocator* allocator)
		: m_allocator(allocator)
		, m_polygons(0, allocator)
		, m_textures(0, allocator)
		, m_verticies(0, allocator)
		, m_uvSets(0, allocator)
	{

	}

	Mesh::Mesh(const size_t& polygonCount, 
		const size_t& uvSetCount, 
		const size_t& textureCount, 
		const size_t& verticiesCount, 
		BlueBell::IAllocator* allocator)
		: m_allocator(allocator)
		, m_polygons(polygonCount, allocator)
		, m_textures(textureCount, allocator)
		, m_verticies(verticiesCount, allocator)
		, m_uvSets(uvSetCount, allocator) 
	{

	}

	Polygon* Mesh::AddPolygon(const size_t& memberCount)
	{
		Polygon polygon(memberCount, m_allocator);

		m_polygons.PushBack(polygon);

		return m_polygons.End() - 1;
	}

	UVSet* Mesh::AddUVSet(const size_t& uvsCount)
	{
		UVSet uvSet(uvsCount, m_allocator);

		m_uvSets.PushBack(uvSet);

		return m_uvSets.End() - 1;
	}

	Texture* Mesh::AddTexture(const std::string& texturePath)
	{
		Texture texture(texturePath);

		m_textures.PushBack(texture);

		return m_textures.End() - 1;
	}

	Vector3D* Mesh::AddVertex(const Vector3D& vertex)
	{
		m_verticies.PushBack(vertex);

		return m_verticies.End() - 1;
	}

	Polygon* Mesh::GetPolygon(int id)
	{
		if (id < m_polygons.GetSize())
			return &m_polygons.At(id);
		else 
			return nullptr;
	}

	UVSet* Mesh::GetUVSet(int id)
	{
		if (id < m_uvSets.GetSize())
			return &m_uvSets.At(id);
		else 
			return nullptr;
	}

	Texture* Mesh::GetTexture(int id)
	{
		if (id < m_textures.GetSize())
			return &m_textures.At(id);
		else 
			return nullptr;
	}

	Vector3D* Mesh::GetVertex(int id)
	{
		if (id < m_verticies.GetSize())
			return &m_verticies.At(id);
		else 
			return nullptr;
	}

	size_t Mesh::GetPolygonCount()
	{
		return m_polygons.GetSize();
	}

	size_t Mesh::GetUVSetCount()
	{
		return m_uvSets.GetSize();
	}

	size_t Mesh::GetTextureCount()
	{
		return m_textures.GetSize();
	}

	size_t Mesh::GetVertexCount()
	{
		return m_verticies.GetSize();
	}
}
