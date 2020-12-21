#include "TransformComponent.h"

#include "../GameObject.h"

namespace BlueBell
{
	TransformComponent::TransformComponent()
		: rotation(Vector3D::Zero)
		, position(Vector3D::Zero)
		, scale(Vector3D(1.0f, 1.0f, 1.0f))
	{
		
	}

	Matrix& TransformComponent::GetModelMatrix()
	{
		m_worldMatrix = Matrix::identity;
		m_worldMatrix.ScaleRotateTranslate(scale, rotation, position, BlueBell::Matrix::CombineFunc::Replace);

		return m_worldMatrix;
	}

	Vector3D TransformComponent::GetForward()
	{
		Matrix& worldMatrix = GetModelMatrix();

		Vector3D forward;
		forward.Set(worldMatrix[2], worldMatrix[6], worldMatrix[10]);
		forward.Normilize();

		return forward;
	}

	Vector3D TransformComponent::GetUp()
	{
		Matrix& worldMatrix = GetModelMatrix();

		Vector3D up;
		up.Set(worldMatrix[1], worldMatrix[5], worldMatrix[9]);
		up.Normilize();

		return up;
	}

	Vector3D TransformComponent::GetRight()
	{
		Matrix& worldMatrix = GetModelMatrix();

		Vector3D right;
		right.Set(worldMatrix[0], worldMatrix[4], worldMatrix[8]);
		right.Normilize();

		return right;
	}

	void TransformComponent::SetForward()
	{
	}

	void TransformComponent::SetUp()
	{
	}

	void TransformComponent::SetRight()
	{
	}
}
