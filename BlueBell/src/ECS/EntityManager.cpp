#include "EntityManager.h"

#include "../Events/EventManager.h"

namespace BlueBell
{
	EntityManager::EntityManager()
		: m_currentID(0)
	{
		EventManager::GetInstance()->AddEvent<NewEntityArgs>();
	}

	EntityManager::~EntityManager()
	{
		EventManager::GetInstance()->DeleteEvent<NewEntityArgs>();
	}

	Entity& EntityManager::CreateEntity()
	{
		m_entites.EmplaceBack(m_currentID);

		NewEntityArgs entityArgs;
		entityArgs.entityID = m_currentID;
		EventManager::GetInstance()->TriggerEvent(entityArgs);

		m_currentID++;

		return m_entites.At(m_currentID - 1);
	}

	Entity* EntityManager::GetEntity(unsigned int& id)
	{
		int index = 0;
		bool found = false;

		Entity* pEntity = nullptr;

		while(found == false && index <= m_entites.GetSize() - 1)
		{
			Entity& entity = m_entites.At(index);

			if (entity.GetID() == id)
			{
				pEntity = &entity;
				found = true;
			}
			else
				index++;
		}

		return pEntity;	
	}

	void EntityManager::DeleteEntity(unsigned int& id)
	{
		int index = 0;
		bool found = false;

		if (m_entites.GetSize() > 0)
		{
			while(found == false && index < m_entites.GetSize() - 1)
			{
				Entity& entity = m_entites.At(index);

				if (entity.GetID() == id)
					found = true;
				else
					index++;
			}

			if (found == true)
				m_entites.Erase(m_entites.Begin() + index);
		}
	}
}
