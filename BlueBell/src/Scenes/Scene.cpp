#include "Scene.h"

#include "../ECS/EntityManager.h"
#include "../Core/BlueBerry.h"

namespace BlueBell
{
	Scene::Scene(const char* name)
		: m_name(name)
	{
		m_entityManager = BlueBerry()->Allocate<EntityManager>();
		m_componentManager = BlueBerry()->Allocate<ComponentManager>();
	}

	Scene::~Scene()
	{
		BlueBerry()->Deallocate(m_entityManager);
		BlueBerry()->Deallocate(m_componentManager);
	}

	void Scene::UpdateScene(const float& deltaTime)
	{
		m_componentManager->UpdateComponents(deltaTime);
	}
}
