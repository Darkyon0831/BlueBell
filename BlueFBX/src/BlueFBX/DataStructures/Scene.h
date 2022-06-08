#ifndef __BFBX_SCENE_H__
#define __BFBX_SCENE_H__

#include "Mesh.h"

#include <Memory/IAllocator.h>
#include <Container/Vector.h>

namespace BlueFBX
{
	class Scene
	{
	public:

		friend class Importer;

		Scene(BlueBell::IAllocator* allocator) : m_allocator(allocator) {}

		Mesh* GetMesh(const int& id);
		Mesh* AddMesh(const size_t& polygonCount, const size_t& textureCount, const size_t& uvSetCount, const size_t& vertexCount); 
		Mesh* AddMesh();

		void InitMeshes(const size_t& meshCount) { m_meshes = BlueBell::Vector<Mesh>(meshCount, m_allocator); }

	private:
		
		BlueBell::Vector<Mesh> m_meshes;
		BlueBell::IAllocator* m_allocator;
	};
}

#endif // !__BFBX_SCENE_H__
