#ifndef __BB_MESHCOMPONENT_H__
#define __BB_MESHCOMPONENT_H__

#include "../../ECS/Component.h"
#include "../../Platform/d3d11/Material.h"
#include "../../Platform/d3d11/Assets/Mesh.h"

namespace BlueBell
{
	class MeshComponent : public Component
	{
	public:

		MeshComponent(std::string meshFilepath, std::string shaderPath);
		~MeshComponent();

		Mesh m_mesh;
		Material m_material;
	};
}
#endif // !__BB_MESHCOMPONENT_H__