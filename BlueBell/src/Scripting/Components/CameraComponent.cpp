#include "CameraComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../../Platform/d3d11/Device.h"

namespace BlueBell
{
	CameraComponent::CameraComponent(float startX, float startY, float width, float height, float nearPlane, float farPlane)
		: m_viewport(startX, startY, width, height)
		, m_nearPlane(nearPlane)
		, m_farPlane(farPlane)
	{
		
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::OnBegin()
	{
		TransformComponent* pTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
		
		pTransformComponent->position.z = -1.0f;
	}

	void CameraComponent::ApplyOrtho()
	{
		m_projectionMatrix = Matrix::identity;
		m_projectionMatrix.ApplyOrthoMatrixOffCenter(m_viewport.GetStartX(), m_viewport.GetWidth() - m_viewport.GetStartX(), m_viewport.GetHeight() - m_viewport.GetStartY(), m_viewport.GetStartY(), -1, 1);
	}

	void CameraComponent::ApplyPerspective(float& aspectRatio, float& fov)
	{
		m_projectionMatrix = Matrix::identity;
		m_projectionMatrix.ApplyPerspectiveMatrix(aspectRatio, fov, m_nearPlane, m_farPlane);
	}

	void CameraComponent::CalculateViewMatrix()
	{
		TransformComponent* pTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
		Vector3D cameraForward = pTransformComponent->GetForward();

		m_viewMatrix = Matrix::identity;
		m_viewMatrix.ApplyViewMatrix(pTransformComponent->position, pTransformComponent->position + cameraForward);
	}

	void CameraComponent::Begin()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		CalculateViewMatrix();
		pDeviceContext->RSSetViewports(1, &m_viewport.GetD3D11Viewport());
	}
}
