#ifndef __BB_EVENT_H__
#define __BB_EVENT_H__

#include "../Container/Vector.h"
#include "EventReceiver.h"
#include "../Core/BlueBerry.h"

// TODO: Remember to fix the bug where the engine crash when having multible of same event saved, will not happend if we reserve space in the m_reveivers vector

namespace BlueBell
{
	template<typename Args>
	class Event
	{
	public:

		Event();

		void AddReceiver(std::function<void(Args&)>& Callback);
		void Trigger(Args& args);

	private:
		Vector<EventReceiver<Args>> m_receivers;
	};

	template<typename Args>
	inline Event<Args>::Event()
		: m_receivers(10, BlueBerry()->GetAllocator())
	{
	}

	template<typename Args>
	inline void Event<Args>::AddReceiver(std::function<void(Args&)>& Callback)
	{
		m_receivers.EmplaceBack(Callback);
	}

	template<typename Args>
	inline void Event<Args>::Trigger(Args& args)
	{
		for (int i = 0; i < m_receivers.GetSize(); i++)
		{
			EventReceiver<Args>& eventReveiver = m_receivers.At(i);
			eventReveiver.m_Callback(args);
		}
	}

}

#endif