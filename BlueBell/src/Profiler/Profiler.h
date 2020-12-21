#ifndef __BB_PROFILER_H__
#define __BB_PROFILER_H__

#include "../Container/Vector.h"

#include <chrono>

#define BB_PROFILE_SCOPE(name) BlueBell::Profile ___bbprofile = BlueBell::Profile(name);
#define BB_PROFILE_BEGIN(name) BlueBell::Profiler::Begin(name);
#define BB_PROFILE_END(name) BlueBell::Profiler::End(name);
#define BB_PROFILE_TIME(name) BlueBell::Profiler::End(name, true);

BB_DISABLE_WARNING_PUSH
BB_DISABLE_WARNING(4251)

namespace BlueBell
{
	struct Profile
	{
		Profile(char* name) : m_timeStamp(std::chrono::high_resolution_clock::now()), m_name(name), m_currentTime(0) { }

		~Profile()
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = currentTime - m_timeStamp;

			if (m_currentTime == 0)
			{
				BB_LOG_INFO("{0}: Took {1} seconds to finish", m_name, duration.count());
			}
			else
			{
				BB_LOG_INFO("{0}: Took {1} seconds to finish", m_name, m_currentTime);
			}
		}

		std::chrono::time_point<std::chrono::high_resolution_clock> m_timeStamp;
		double m_currentTime;
		char* m_name;
	};

	class BB_API Profiler
	{
	public:

		Profiler();
		~Profiler();

		static void Begin(char* name);
		static void End(char* name, bool isNoEnd = false);

	private:
		static BlueBell::Vector<Profile> m_profiles;
	};
}

BB_DISABLE_WARNING_POP

#endif 
