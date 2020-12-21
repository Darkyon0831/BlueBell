#ifndef __BB_COMPONENTMANAGER_H__
#define __BB_COMPONENTMANAGER_H__

#include "../Container/Vector.h"
#include "../Core/BlueBerry.h"
#include "EntityManager.h"
#include "../Profiler/Profiler.h"
#include "../Helpers/Singleton.h"

#include <typeinfo>

#define StartComponentTypeSize 64
#define StartComponentPerEntitySize 32

class Component;

namespace BlueBell
{
	class BB_API ComponentManager
	{
	public:

		struct ComponentBlock
		{
			ComponentBlock(size_t _componentSize, size_t* _pSize, void* _pBlock) : componentSize(_componentSize), pSize(_pSize), pBlock(_pBlock) {} 

			size_t componentSize;
			size_t* pSize;
			void* pBlock;
		};

		ComponentManager();
		~ComponentManager();

		struct Keys
		{
		public:
			
			Keys() : keyCheck(StartComponentPerEntitySize, BlueBerry()->GetAllocator()), componentID(StartComponentPerEntitySize, BlueBerry()->GetAllocator()) {}
			~Keys() 
			{ 
				
			}

			template <typename TComponent>
			int GetComponentID() 
			{
				int i = 0;
				bool found = false;

				for (auto it = keyCheck.Begin(); it != keyCheck.End(); it++)
				{
					if (typeid(TComponent).hash_code() == *it)
					{
						found = true;
						break;
					}
					else
						i++;
				}

				if (found == true)
					return componentID.At(i);
				else
					return -1;
			}

			template <typename TComponent>
			void SetComponentID(int& id) 
			{  
				keyCheck.PushBack(typeid(TComponent).hash_code());
				componentID.PushBack(id);
			}

		private:
			
			Vector<size_t> keyCheck;
			Vector<int> componentID;
		};

		friend class EntityManager;

		template<typename TComponent>
		TComponent* GetComponent(unsigned int& entityID);

		template<typename TComponent>
		void DeleteComponent(int& entityID);

		template<typename TComponent>
		bool HaveComponent(unsigned int& entityID);

		template<typename TComponent, typename... Args>
		TComponent* CreateComponent(unsigned int& entityID, Args&&... args);

		void OnNewEntity(EntityManager::NewEntityArgs& args);
	
		template<typename TComponent>
		inline TComponent* GetComponentBegin() { return m_components<TComponent>().Begin(); }

		template<typename TComponent>
		inline TComponent* GetComponentEnd() { return m_components<TComponent>().End(); }

		void UpdateComponents(const float& deltaTime);

	private:

		Vector<Keys> m_keys;
		Vector<ComponentBlock> m_componentBlock;

		template<typename TComponent>
		static Vector<TComponent>& m_components(bool* isInit = nullptr)
		{ 
			static bool sIsInit = false;
			static Vector<TComponent> _components;

			if (sIsInit == false)
			{
				_components = Vector<TComponent>(StartComponentTypeSize, BlueBell::BlueBerry()->GetAllocator());

				if (isInit != nullptr)
					*isInit = true;

				sIsInit = true;
			}

			return _components; 
		}
	};

	template<typename TComponent>
	inline TComponent* ComponentManager::GetComponent(unsigned int& entityID)
	{
		int componentID = m_keys.At(entityID).GetComponentID<TComponent>();
		BB_ASSERT(componentID != -1, "Entity with id {0} does not have component of type {1}", entityID, typeid(TComponent).name())

		return &m_components<TComponent>().At(componentID);
	}

	template<typename TComponent>
	inline void ComponentManager::DeleteComponent(int& entityID)
	{
		int componentID = m_keys.At(entityID).GetComponentID<TComponent>();

		if (componentID != -1)
			m_components<TComponent>().Erase(m_components<TComponent>().Begin() + componentID);
	}

	template<typename TComponent>
	inline bool ComponentManager::HaveComponent(unsigned int& entityID)
	{
		int componentID = m_keys.At(entityID).GetComponentID<TComponent>();

		if (componentID != -1)
			return true;
		else
			return false;
	}

	template<typename TComponent, typename... Args>
	inline TComponent* ComponentManager::CreateComponent(unsigned int& entityID, Args&&... args)
	{
		BB_STATIC_ASSERT(std::is_base_of<Component, TComponent>::value, "An component must have Component as base class")
		BB_ASSERT(HaveComponent<TComponent>(entityID) == false, "This entity already have component of type {1}", typeid(TComponent).name())

		bool isInit = false;
		Vector<TComponent>& components = m_components<TComponent>(&isInit);
		components.EmplaceBack(std::forward<Args>(args)...);

		if (isInit == true)
		{
			void* pBlock = reinterpret_cast<void*>(components.GetBuffer());
			size_t& size = components.GetSize();

			m_componentBlock.EmplaceBack(sizeof(TComponent), &size, pBlock);

			int i = 0;
		}

		int index = m_components<TComponent>().GetSize() - 1;
		TComponent& tComponent = m_components<TComponent>().At(index);
		tComponent.m_entityID = entityID;

		m_keys.At(entityID).SetComponentID<TComponent>(index);

		tComponent.OnBegin();

		return &tComponent;
	}
}

#endif 
