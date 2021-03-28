#include "MeshComponent.h"

namespace BlueBell
{
	MeshComponent::MeshComponent(std::string meshFilepath, std::string shaderPath)
		: m_mesh(meshFilepath)
		, m_material(shaderPath)
	{

	}

	MeshComponent::~MeshComponent()
	{

	}
}
