#ifndef __BB_EVENTRECEIVER_H__
#define __BB_EVENTRECEIVER_H__

#include <functional>

template<typename Args>
class EventReceiver
{
public:

	EventReceiver(std::function<void(Args&)>& Callback) : m_Callback(std::move(Callback)) {}

	std::function<void(Args&)> m_Callback;
};

#endif 
