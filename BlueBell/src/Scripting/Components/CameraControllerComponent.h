#ifndef __BB_CAMERACONTROLLERCOMPONENT_H__
#define __BB_CAMERACONTROLLERCOMPONENT_H__

#include "../../ECS/Component.h"
#include "../../Events/EventManager.h"
#include "../../Math/Vector3D.h"

namespace BlueBell
{
	class CameraControllerComponent : public Component
	{
	public:

		struct KeyboardMovement
		{
			Vector3D ldb = Vector3D::Zero;
			Vector3D ruf = Vector3D::Zero;
		};

		struct MouseMovement
		{
			float lastX = 0.0f;
			float lastY = 0.0f;
			bool first = true;

			float pitch = 0.0f;
			float yaw = 0.0f;
		};

		CameraControllerComponent();
		~CameraControllerComponent();

		void OnBegin() override;
		void OnUpdate(const float& deltaTime) override;

		void OnInput(OnInputArgs& args);

	private:
		KeyboardMovement m_keyboardMovement;
		MouseMovement m_mouseMovement;
	};
}

#endif // !__BB_CAMERACONTROLLERCOMPONENT_H__
