#include "Component.h"

#include "../Scenes/SceneManager.h"

namespace BlueBell
{
	GameObject* Component::GetGameObject()
	{
		Scene* pActiveScene = SceneManager::GetInstance()->GetActiveScene();
		BB_ASSERT(pActiveScene != nullptr, "Could not create an new GameObject!, an active scene have not been set");

		return reinterpret_cast<GameObject*>(pActiveScene->GetEntity(m_entityID));
	}
}
