#ifndef __BFBX_MESH_H__
#define __BFBX_MESH_H__

#include "UVSet.h"
#include "Texture.h"
#include "Polygon.h"
#include "Vectors.h"

#include <Container/Vector.h>
#include <Memory/IAllocator.h>

namespace BlueFBX
{
	class Mesh
	{
	public:

		Mesh(BlueBell::IAllocator* allocator);

		Mesh(const size_t& polygonCount,
			const size_t& uvSetCount,
			const size_t& textureCount,
			const size_t& verticiesCount,
			BlueBell::IAllocator* allocator);

		Polygon* AddPolygon(const size_t& memberCount);
		UVSet* AddUVSet(const size_t& uvsCount);
		Texture* AddTexture(const std::string& texturePath);
		Vector3D* AddVertex(const Vector3D& vertex);

		Polygon* GetPolygon(int id);
		UVSet* GetUVSet(int id);
		Texture* GetTexture(int id);
		Vector3D* GetVertex(int id);

		size_t GetPolygonCount();
		size_t GetUVSetCount();
		size_t GetTextureCount();
		size_t GetVertexCount();

		void SetName(const std::string& name) { m_name = name; }

	private:

		BlueBell::Vector<Polygon> m_polygons;
		BlueBell::Vector<UVSet> m_uvSets;
		BlueBell::Vector<Texture> m_textures;
		BlueBell::Vector<Vector3D> m_verticies;
		std::string m_name;

		BlueBell::IAllocator* m_allocator;
	};
}

#endif // !__BFBX_MESH_H__
