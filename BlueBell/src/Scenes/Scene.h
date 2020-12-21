#ifndef __BB_SCENE_H__
#define __BB_SCENE_H__

#include "../Container/Vector.h"
#include "../ECS/EntityManager.h"
#include "../ECS/ComponentManager.h"
#include "../ECS/SystemManager.h"

namespace BlueBell
{
	class Scene
	{
	public:

		Scene(const char* name);
		~Scene();
		
		#pragma region EntityManager

		Entity& CreateEntity() { return m_entityManager->CreateEntity(); }
		Entity* GetEntity(unsigned int& id) { return m_entityManager->GetEntity(id); }
		void DeleteEntity(unsigned int& id) { m_entityManager->DeleteEntity(id); }

		#pragma endregion

		#pragma region ComponentManager

		template<typename Component>
		Component* GetComponent(unsigned int& entityID) { return m_componentManager->GetComponent<Component>(entityID); }

		template<typename Component>
		bool HaveComponent(int& entityID) { return m_componentManager->HaveComponent<Component>(entityID); }

		template<typename Component, typename... Args>
		Component* CreateComponent(unsigned int& entityID, Args&&... args) { return m_componentManager->CreateComponent<Component>(entityID, std::forward<Args>(args)...); }

		template<typename Component>
		inline Component* GetComponentBegin() { return m_componentManager->GetComponentBegin<Component>(); }

		template<typename Component>
		inline Component* GetComponentEnd() { return m_componentManager->GetComponentEnd<Component>(); }

		#pragma endregion

		const char* GetName() { return m_name; }

		void UpdateScene(const float& deltaTime);

	private:
		EntityManager* m_entityManager;
		ComponentManager* m_componentManager;

		const char* m_name;
	};
}

#endif // !__BB_SCENE_H__
