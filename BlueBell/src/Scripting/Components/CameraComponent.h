#ifndef __BB_CAMERACOMPONENT_H__
#define __BB_CAMERACOMPONENT_H__

#include "../../ECS/Component.h"
#include "../../Platform/d3d11/Viewport.h"
#include "../../Math/Matrix.h"
#include "../../Events/EventManager.h"

namespace BlueBell
{
	class CameraComponent : public Component
	{
	public:

		CameraComponent(float startX, float startY, float width, float height, float nearPlane, float farPlane);
		~CameraComponent();

		void OnBegin() override;

		void ApplyOrtho();
		void ApplyPerspective(float& aspectRatio, float& fov);

		void CalculateViewMatrix();

		Matrix& GetViewMatrix() { return m_viewMatrix; }
		Matrix& GetProjectionMatrix() { return m_projectionMatrix; }

		void Begin();

	private:
		Viewport m_viewport;
		
		Matrix m_projectionMatrix;
		Matrix m_viewMatrix;
		float m_nearPlane;
		float m_farPlane;
	};
}

#endif // !__BB_CAMERACOMPONENT_H__
