#include "SystemManager.h"


namespace BlueBell
{
	SystemManager::SystemManager()
		: m_systems(StartSystemSize, BlueBerry()->GetAllocator())
		, m_systemAllocator(BlueBerry()->Allocate<Allocator<StackAllocator>>(SystemAllocatorSize, BlueBerry()->GetAllocator()))
	{

	}

	SystemManager::~SystemManager()
	{
		for (int i = 0; i < m_systems.GetSize(); i++)
			m_systemAllocator->Deallocate(m_systems.At(i));

		BlueBerry()->Deallocate(m_systemAllocator);
	}

	void SystemManager::StartSystems()
	{
		for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->PreStart();
		}

		for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->Start();
		}

		for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->PostStart();
		}
	}

	void SystemManager::UpdateSystems()
	{
		/*for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->PreUpdate();
		}
*/
		for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->Update();
		}

		for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->PostUpdate();
		}
	}

	void SystemManager::PreUpdateSystems()
	{
		for (auto it = m_systems.Begin(); it != m_systems.End(); it++)
		{
			(*it)->PreUpdate();
		}
	}
}
