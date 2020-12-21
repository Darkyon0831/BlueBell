#ifndef __BB_GAMEOBJECT_H__
#define __BB_GAMEOBJECT_H__

#include "../ECS/Entity.h"
#include "../Scenes/SceneManager.h"

namespace BlueBell
{
	class GameObject : public Entity
	{
	public:

		GameObject();
		~GameObject();

		template<typename Component, typename... Args>
		Component* CreateComponent(Args&&... args);

		template<typename Component>
		bool HaveComponent();

		template<typename Component>
		Component* GetComponent();
	};

	#endif // !__BB_GAMEOBJECT_H__

	template<typename Component, typename... Args>
	inline Component* GameObject::CreateComponent(Args&&... args)
	{
		BlueBell::Scene* pScene = BlueBell::SceneManager::GetInstance()->GetActiveScene();

		return pScene->CreateComponent<Component>(m_id, std::forward<Args>(args)...);
	}

	template<typename Component>
	inline bool GameObject::HaveComponent()
	{
		BlueBell::Scene* pScene = BlueBell::SceneManager::GetInstance()->GetActiveScene();

		return pScene->HaveComponent<Component>(m_id);
	}

	template<typename Component>
	inline Component* GameObject::GetComponent()
	{
		BlueBell::Scene* pScene = BlueBell::SceneManager::GetInstance()->GetActiveScene();

		return pScene->GetComponent<Component>(m_id);
	}
}
