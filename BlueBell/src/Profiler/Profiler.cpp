#include "Profiler.h"

namespace BlueBell
{
	Vector<Profile> Profiler::m_profiles = Vector<Profile>();

	Profiler::Profiler()
	{
	}

	Profiler::~Profiler()
	{
	}

	void Profiler::Begin(char* name)
	{
		Vector<Profile>::iterator it = m_profiles.Begin();
		Vector<Profile>::iterator currentProfileIT = nullptr;

		for (it; it != m_profiles.End(); it++)
		{
			if (std::strcmp(it->m_name, name) == 0)
			{
				currentProfileIT = it;
				break;
			}
		}

		if (currentProfileIT == nullptr)
			m_profiles.EmplaceBack(name);
	}

	void Profiler::End(char* name, bool isNoEnd)
	{
		Vector<Profile>::iterator it = m_profiles.Begin();
		Vector<Profile>::iterator currentProfileIT = nullptr;

		for (it; it != m_profiles.End(); it++)
		{
			if (std::strcmp(it->m_name, name) == 0)
			{
				currentProfileIT = it;
				break;
			}
		}

		if (currentProfileIT != nullptr)
		{
			if (isNoEnd == false)
				m_profiles.Erase(currentProfileIT);
			else
			{
				auto time = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> duration = time - currentProfileIT->m_timeStamp;
				currentProfileIT->m_currentTime += duration.count();
				currentProfileIT->m_timeStamp = time;
			}
		}
	}
}

