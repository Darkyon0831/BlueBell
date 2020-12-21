#ifndef __BB_COMPONENT_H__
#define __BB_COMPONENT_H__

namespace BlueBell
{
	class GameObject;

	class Component
	{
	public:

		friend class ComponentManager;

		Component() {}
		virtual ~Component() {}

		virtual void OnBegin() {}

		virtual void OnUpdate(const float& deltaTime) {}

		GameObject* GetGameObject();

	private:
		unsigned int m_entityID;
	};
}
#endif // !__BB_COMPONENT_H__
