#include "DeltaTime.h"

namespace BlueBell
{
	BlueBell::DeltaTime::DeltaTime()
		: m_deltaTime(0.0f)
		, m_first(true)
	{
		
	}
	
	BlueBell::DeltaTime::~DeltaTime()
	{
		
	}
	
	void BlueBell::DeltaTime::Now()
	{
		if (m_first == false)
		{
			m_last = m_now;
			m_now = std::chrono::duration_cast<ms>(std::chrono::high_resolution_clock::now().time_since_epoch());

			m_deltaTime = (m_now - m_last).count();
		}
		else
		{
			m_now = std::chrono::duration_cast<ms>(std::chrono::high_resolution_clock::now().time_since_epoch());
			m_deltaTime = 0.0f;

			m_first = false;
		}
	}
}