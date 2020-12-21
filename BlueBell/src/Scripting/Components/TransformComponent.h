#ifndef __BB_TRANSFORMCOMPONENT_H__
#define __BB_TRANSFORMCOMPONENT_H__

#include "../../Math/Vector3D.h"
#include "../../Math/Matrix.h"

#include "../../ECS/Component.h"

namespace BlueBell
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		~TransformComponent() = default;

		BlueBell::Matrix& GetModelMatrix();

		BlueBell::Vector3D GetForward();
		BlueBell::Vector3D GetUp();
		BlueBell::Vector3D GetRight();

		void SetForward();
		void SetUp();
		void SetRight();

		BlueBell::Vector3D rotation;
		BlueBell::Vector3D position;
		BlueBell::Vector3D scale;

	private:
		BlueBell::Matrix m_worldMatrix;
	};
}

#endif // !__TRANSFORMCOMPONENT_H__
