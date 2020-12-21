#ifndef __BB_DELTATIME_H__
#define __BB_DELTATIME_H__

#include <chrono>

namespace BlueBell
{
	class DeltaTime
	{
	public:

		DeltaTime();
		~DeltaTime();

		using ms = std::chrono::duration<float>;

		void Now();

		const double& GetDelta() const { return m_deltaTime; }

	private:
		ms m_now;
		ms m_last;

		float m_deltaTime;

		bool m_first;
	};
}

#endif // !__BB_DELTATIME_H__
