#ifndef __BB_SYSTEMMANAGER_H__
#define __BB_SYSTEMMANAGER_H__

#include "../Container/Vector.h"
#include "../Core/BlueBerry.h"
#include "../Helpers/Singleton.h"
#include "System.h"

#define SystemAllocatorSize 256 * 16
#define StartSystemSize 64

namespace BlueBell
{
	class BB_API SystemManager : public Singleton<SystemManager>
	{
	public:

		SystemManager();
		~SystemManager();

		template<typename CSystem, typename... Args>
		CSystem* AddSystem(Args... args);

		void StartSystems();
		void UpdateSystems();

		void PreUpdateSystems();

	private:
		Vector<System*> m_systems;
		Allocator<StackAllocator>* m_systemAllocator;
	};

	template<typename CSystem, typename... Args>
	inline CSystem* SystemManager::AddSystem(Args... args)
	{
		BB_STATIC_ASSERT(std::is_base_of<System, CSystem>::value, "template variable CSystem must derive from System!");

		CSystem* system = m_systemAllocator->Allocate<CSystem>(std::forward<Args>(args)...);
		m_systems.PushBack(reinterpret_cast<System*>(system));

		return system;
	}
}

#endif
