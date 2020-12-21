#ifndef __BB_EVENTMANAGER_H__
#define __BB_EVENTMANAGER_H__

#include "../Container/Vector.h"
#include "../Helpers/Singleton.h"
#include "Event.h"
#include "ArgumentDefines.h"

#include <typeinfo>

#define BB_BIND_STATIC_FUNC(func, className) [](auto& args) { className::func(args); }
#define BB_BIND_FUNC(func, instance) [instance](auto& args) { instance->func(args); }

namespace BlueBell
{
	class BB_API EventManager : public Singleton<EventManager>
	{
	public:

		template<typename Args>
		Event<Args>& AddEvent();

		template<typename Args>
		void DeleteEvent();

		template<typename Args>
		inline Event<Args>& GetEvent() { return m_event<Args>(); }

		template<typename Args>
		void AddReceiverToEvent(std::function<void(Args&)> Callback);

		template<typename Args>
		void TriggerEvent(Args& args);

	private:

		template<typename Args>
		static Event<Args>* m_event(int flag);
	};

	template<typename Args>
	inline Event<Args>& EventManager::AddEvent()
	{
		return *m_event<Args>(2);
	}

	template<typename Args>
	inline void EventManager::DeleteEvent()
	{
		m_event<Args>(1);
	}

	template<typename Args>
	inline void EventManager::AddReceiverToEvent(std::function<void(Args&)> Callback)
	{
		m_event<Args>(0)->AddReceiver(Callback);
	}

	template<typename Args>
	inline void EventManager::TriggerEvent(Args& args)
	{
		m_event<Args>(0)->Trigger(args);
	}

	template<typename Args>
	inline Event<Args>* EventManager::m_event(int flag)
	{
		static Event<Args>* _event = nullptr;
		
		if (flag == 0)
			return _event;
		else if (flag == 1)
		{
			BlueBerry()->Deallocate(_event);
			return nullptr;
		}
		else if (flag == 2)
		{
			const std::type_info& argType = typeid(Args);

			BB_ASSERT(_event == nullptr, "Event with args {0} already exist!", argType.name())
				
			_event = BlueBerry()->Allocate<Event<Args>>(); 
			return _event;
		}
	}
}

#endif 




