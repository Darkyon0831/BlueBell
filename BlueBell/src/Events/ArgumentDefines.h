#ifndef __BB_ARGUMENTDEFINES_H__
#define __BB_ARGUMENTDEFINES_H__

#include <Windows.h>

#include "../Math/Vector2D.h"

namespace BlueBell
{
	struct OnWindowClosedArgs
	{
		HWND windowHandle;
	};

	struct OnImGuiRenderArgs
	{
		float deltaTime;
	};

	#pragma region Input
	enum InputKeyState
	{
		KeyDown,
		KeyUp
	};

	enum InputDevice
	{
		Keyboard,
		Mouse
	};

	struct InputKeyboard
	{
		InputKeyState keyState;
		char keyCode;
	};

	struct InputMouseWheel
	{
		unsigned short wheelDelta;
	};

	struct InputMousePosition
	{
		Vector2D absolute;
		Vector2D relative;
	};

	enum InputMouseButtonType
	{
		Left,
		Right
	};

	enum InputMouseButtonState
	{
		Up,
		Down
	};

	struct InputMouseButton
	{
		InputMouseButtonType buttonType;
		InputMouseButtonState buttonState;
	};

	enum InputMouseType
	{
		Wheel,
		Position,
		Button
	};

	struct InputMouse
	{
		InputMouse() {}

		InputMouseType mouseType;
		InputMouseWheel mouseWheel;
		InputMousePosition mousePosition;
		InputMouseButton mouseButton;
	};

	struct OnInputArgs
	{
		OnInputArgs() {}

		InputDevice device;
		InputKeyboard keyboard;
		InputMouse mouse;
	};
	#pragma endregion

}

#endif // !__BB_ARGUMENTDEFINES_H__
