#include "CameraControllerComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../../Core/Clock.h"

namespace BlueBell
{
	BlueBell::CameraControllerComponent::CameraControllerComponent()
	{

	}
	
	BlueBell::CameraControllerComponent::~CameraControllerComponent()
	{

	}
	
	void BlueBell::CameraControllerComponent::OnBegin()
	{
		EventManager::GetInstance()->AddReceiverToEvent<OnInputArgs>(BB_BIND_FUNC(OnInput, this));
	}
	
	void BlueBell::CameraControllerComponent::OnUpdate(const float& deltaTime)
	{
		TransformComponent* pTransformComponent = GetGameObject()->GetComponent<TransformComponent>();

		if (deltaTime != 0)
		{
			pTransformComponent->position += (pTransformComponent->GetRight() * (((m_keyboardMovement.ldb.x + m_keyboardMovement.ruf.x) / deltaTime) * 0.000001f)) + 
				( pTransformComponent->GetForward() * (((m_keyboardMovement.ldb.z + m_keyboardMovement.ruf.z) / deltaTime) * 0.000001f));

			pTransformComponent->rotation.x = m_mouseMovement.pitch;
			pTransformComponent->rotation.y = m_mouseMovement.yaw;
		}
	}
	
	void BlueBell::CameraControllerComponent::OnInput(OnInputArgs& args)
	{
		if (args.device == InputDevice::Keyboard)
		{
			if (args.keyboard.keyState == InputKeyState::KeyDown)
			{
				char keyCode = args.keyboard.keyCode;

				if (keyCode == 'D') m_keyboardMovement.ruf.x = 1;
				if (keyCode == 'A') m_keyboardMovement.ldb.x = -1;
				if (keyCode == 'S') m_keyboardMovement.ldb.z = -1;
				if (keyCode == 'W') m_keyboardMovement.ruf.z = 1;
			}
			else if (args.keyboard.keyState == InputKeyState::KeyUp) 
			{
				char keyCode = args.keyboard.keyCode;

				if (keyCode == 'D') m_keyboardMovement.ruf.x = 0;
				if (keyCode == 'A') m_keyboardMovement.ldb.x = 0;
				if (keyCode == 'S') m_keyboardMovement.ldb.z = 0;
				if (keyCode == 'W') m_keyboardMovement.ruf.z = 0;
			}
		}
		/*else if (args.device == InputDevice::Mouse)
		{
			if (args.mouse.mouseType == InputMouseType::Position)
			{
				if (m_mouseMovement.first)
				{
					m_mouseMovement.lastX = args.mouse.mousePosition.absolute.x;
					m_mouseMovement.lastY = args.mouse.mousePosition.absolute.y;
					m_mouseMovement.first = false;
				}

				float x = args.mouse.mousePosition.absolute.x - m_mouseMovement.lastX;
				float y = args.mouse.mousePosition.absolute.y - m_mouseMovement.lastY;
				m_mouseMovement.lastX = args.mouse.mousePosition.absolute.x;
				m_mouseMovement.lastY = args.mouse.mousePosition.absolute.y;

				if (x == NAN)
					int i = 0;

				m_mouseMovement.pitch += y * Clock::GetInstance()->GetDeltaTime() * 600;
				m_mouseMovement.yaw += x * Clock::GetInstance()->GetDeltaTime() * 600;

				if(m_mouseMovement.pitch > 45.0f)
					m_mouseMovement.pitch = 45.0f;
				if(m_mouseMovement.pitch < -45.0f)
					m_mouseMovement.pitch = -45.0f;
			}
		}*/
	}
}
