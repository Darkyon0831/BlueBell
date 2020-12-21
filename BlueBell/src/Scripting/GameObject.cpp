#include "GameObject.h"
#include "Components/TransformComponent.h"

namespace BlueBell
{
	GameObject::GameObject()
	{
		BlueBell::Scene* pScene = BlueBell::SceneManager::GetInstance()->GetActiveScene();
		BB_ASSERT(pScene != nullptr, "Could not create an new GameObject!, an active scene have not been set");

		(*this) = *reinterpret_cast<GameObject*>(&pScene->CreateEntity());
		CreateComponent<TransformComponent>();
	}

	GameObject::~GameObject()
	{
		BlueBell::Scene* pScene = BlueBell::SceneManager::GetInstance()->GetActiveScene();

		pScene->DeleteEntity(m_id);
	}
}
