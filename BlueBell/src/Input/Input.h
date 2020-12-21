#ifndef __BB_INPUT_H__
#define __BB_INPUT_H__

#include "../Events/EventManager.h"

namespace BlueBell
{
	class Input
	{
	public:

		Input();
		~Input();

		#ifdef BB_PLATFORM_WINDOWS
		void SetupRawInput();

		void ReadFromWndProc(WPARAM wParam, LPARAM lParam, unsigned int message);
		void ReadFromRawInput(LPARAM lParam);
		#endif // BB_PLATFORM_WINDOWS

	private:
		float m_lastAbosoluteMouseX;
		float m_lastAbosoluteMouseY;
	};
}

#endif // !__BB_INPUT_H__
