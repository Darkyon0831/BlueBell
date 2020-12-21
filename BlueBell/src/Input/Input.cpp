#include "Input.h"

#include "../Logging/Logger.h"
#include "../Core/BlueBerry.h"

#include <windowsx.h>

namespace BlueBell
{
	Input::Input()
		: m_lastAbosoluteMouseX(0.0f)
		, m_lastAbosoluteMouseY(0.0f)
	{
		EventManager::GetInstance()->AddEvent<OnInputArgs>();
	}

	Input::~Input()
	{
		EventManager::GetInstance()->DeleteEvent<OnInputArgs>();
	}

	void Input::SetupRawInput()
	{
		RAWINPUTDEVICE Rid[1];

		// Keyboard 
		Rid[0].usUsagePage = 0x01; 
		Rid[0].usUsage = 0x06; 
		Rid[0].dwFlags = 0; 
		Rid[0].hwndTarget = 0;

		BB_ASSERT(RegisterRawInputDevices(Rid, 1, sizeof(RAWINPUTDEVICE)), "Could not register raw input devices, got error code {0}", GetLastError());	
	}

	void Input::ReadFromWndProc(WPARAM wParam, LPARAM lParam, unsigned int message)
	{
		if (message == WM_MOUSEMOVE)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Mouse;
			inputArgs.mouse.mouseType = InputMouseType::Position;

			inputArgs.mouse.mousePosition.absolute.x = GET_X_LPARAM(lParam);
			inputArgs.mouse.mousePosition.absolute.y = GET_Y_LPARAM(lParam);

			if (m_lastAbosoluteMouseX == 0.0f && m_lastAbosoluteMouseY == 0.0f)
			{
				inputArgs.mouse.mousePosition.relative.x = 0.0f;
				inputArgs.mouse.mousePosition.relative.y = 0.0f;
			}
			else
			{
				inputArgs.mouse.mousePosition.relative.x = inputArgs.mouse.mousePosition.absolute.x - m_lastAbosoluteMouseX;
				inputArgs.mouse.mousePosition.relative.y = inputArgs.mouse.mousePosition.absolute.y - m_lastAbosoluteMouseY;
				inputArgs.mouse.mousePosition.relative.Normalize();
			}

			m_lastAbosoluteMouseX = inputArgs.mouse.mousePosition.absolute.x;
			m_lastAbosoluteMouseY = inputArgs.mouse.mousePosition.absolute.y;

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}
		else if (message == WM_MOUSEWHEEL)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Mouse;
			inputArgs.mouse.mouseType = InputMouseType::Wheel;

			inputArgs.mouse.mouseWheel.wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}
		else if (message == WM_LBUTTONDOWN)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Mouse;
			inputArgs.mouse.mouseType = InputMouseType::Button;

			inputArgs.mouse.mouseButton.buttonType = InputMouseButtonType::Left;
			inputArgs.mouse.mouseButton.buttonState = InputMouseButtonState::Down;

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}
		else if (message == WM_LBUTTONUP)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Mouse;
			inputArgs.mouse.mouseType = InputMouseType::Button;

			inputArgs.mouse.mouseButton.buttonType = InputMouseButtonType::Left;
			inputArgs.mouse.mouseButton.buttonState = InputMouseButtonState::Up;

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}
		else if (message == WM_RBUTTONDOWN)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Mouse;
			inputArgs.mouse.mouseType = InputMouseType::Button;

			inputArgs.mouse.mouseButton.buttonType = InputMouseButtonType::Right;
			inputArgs.mouse.mouseButton.buttonState = InputMouseButtonState::Down;

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}
		else if (message == WM_RBUTTONUP)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Mouse;
			inputArgs.mouse.mouseType = InputMouseType::Button;

			inputArgs.mouse.mouseButton.buttonType = InputMouseButtonType::Right;
			inputArgs.mouse.mouseButton.buttonState = InputMouseButtonState::Up;

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}
	}

	void Input::ReadFromRawInput(LPARAM lParam)
	{
		unsigned int bufferSize = 0;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &bufferSize, sizeof(RAWINPUTHEADER));

		char* rawInputBuffer = BlueBerry()->AllocateArray<char>(bufferSize);

		BB_ASSERT(GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawInputBuffer, &bufferSize, sizeof(RAWINPUTHEADER)), "Could not get raw input data, got wrong buffer size");

		RAWINPUT* raw = (RAWINPUT*)rawInputBuffer;

		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			OnInputArgs inputArgs;

			inputArgs.device = InputDevice::Keyboard;

			if (raw->data.keyboard.Message == WM_KEYDOWN)
				inputArgs.keyboard.keyState = InputKeyState::KeyDown;
			else if (raw->data.keyboard.Message == WM_KEYUP)
				inputArgs.keyboard.keyState = InputKeyState::KeyUp;

			inputArgs.keyboard.keyCode = raw->data.keyboard.VKey;

			EventManager::GetInstance()->TriggerEvent<OnInputArgs>(inputArgs);
		}

		BlueBerry()->Deallocate(rawInputBuffer);
	}
}
