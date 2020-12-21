#include "Window.h"

#include "../../Logging/Logger.h"
#include "../../Events/EventManager.h"
#include "../../ImGui/ImGuiRenderer.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace BlueBell
{
	LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);

		switch (uMsg)
		{
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);

			OnWindowClosedArgs args;
			args.windowHandle = hwnd;
			EventManager::GetInstance()->TriggerEvent<OnWindowClosedArgs>(args);

			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_INPUT:
		{
			Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			Input* pInput = pWindow->GetInput();

			pInput->ReadFromRawInput(lParam);

			break;
		}
		case WM_NCCREATE:
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			Window* pWindow = static_cast<Window*>(lpcs->lpCreateParams);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		}
		default:
		{
			if (uMsg == WM_MOUSEMOVE || uMsg == WM_MOUSEWHEEL || uMsg == WM_LBUTTONUP || uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_RBUTTONDOWN)
			{
				Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
				Input* pInput = pWindow->GetInput();

				pInput->ReadFromWndProc(wParam, lParam, uMsg);
			}

			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		}

		return 0;
	}

	Window::Window()
		: m_windowName(L"BlueBell")
	{
		m_applicationInstance = GetModuleHandle(NULL);
		EventManager::GetInstance()->AddEvent<OnWindowClosedArgs>();
	}

	Window::~Window()
	{
		EventManager::GetInstance()->DeleteEvent<OnWindowClosedArgs>();
	}

	void Window::Create()
	{
		WNDCLASS wc = { };

		wc.lpfnWndProc   = WindowProc;
		wc.hInstance     = m_applicationInstance;
		wc.lpszClassName = m_windowName;

		RegisterClass(&wc);

		m_windowHandle = CreateWindowEx(
			NULL,
			m_windowName,
			L"BlueBell game engine",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			m_applicationInstance,
			this
		);

		BB_ASSERT(m_windowHandle != nullptr, "Error creating window handle, CreateWindowEx returned nullptr!");
	}

	void Window::Show()
	{
		ShowWindow(m_windowHandle, SW_SHOW);
		
		RECT rect;

		GetClientRect(m_windowHandle, &rect);

		int i = 0;
	}

	void Window::Close()
	{
		CloseWindow(m_windowHandle);
	}

	void Window::HandleMessages()
	{
		MSG message;
		BOOL isMessage;

		while (isMessage = PeekMessage(&message, m_windowHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	void Window::InitInput()
	{
		m_pInput->SetupRawInput();
	}
}
