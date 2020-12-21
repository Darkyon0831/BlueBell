#include "ComponentManager.h"
#include "../Events/EventManager.h"

#include "Component.h"

namespace BlueBell
{
	ComponentManager::ComponentManager()
		: m_keys(0, BlueBerry()->GetAllocator())
		, m_componentBlock(10, BlueBerry()->GetAllocator())
	{
		int i = 0;

		EventManager::GetInstance()->AddReceiverToEvent<EntityManager::NewEntityArgs>(BB_BIND_FUNC(OnNewEntity, this));

		int d = 0;
	}

	ComponentManager::~ComponentManager()
	{
		int i = 0;
	}

	void ComponentManager::OnNewEntity(EntityManager::NewEntityArgs& args)
	{
		m_keys.EmplaceBack();
		Keys& keys = m_keys.At(0);

		int i = 0;
	}

	void ComponentManager::UpdateComponents(const float& deltaTime)
	{
		for (auto it = m_componentBlock.Begin(); it != m_componentBlock.End(); it++)
		{
			for (int i = 0; i < *it->pSize; i++)
			{
				Component* pComponent = reinterpret_cast<Component*>(reinterpret_cast<char*>(it->pBlock) + i * it->componentSize);

				pComponent->OnUpdate(deltaTime);
			}
		}
	}
}
