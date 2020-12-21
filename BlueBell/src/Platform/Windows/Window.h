#ifndef __BB_WINDOW_H__
#define __BB_WINDOW_H__

#include "../../Core/Core.h"
#include "../../Input/Input.h"

#include <Windows.h>

namespace BlueBell
{
	class BB_API Window
	{
	public:

		Window(); 
		~Window();

		void Create();
		void Show();
		void Close();

		void HandleMessages();

		void SetInputHandle(Input*& pInput) { m_pInput = pInput; }
		void InitInput();
		Input* GetInput() { return m_pInput; }

		HWND& GetWindowHandle() { return m_windowHandle; }

	private:
		Input* m_pInput;
		HINSTANCE m_applicationInstance;
		HWND m_windowHandle;
		const wchar_t* m_windowName;
	};
}

#endif