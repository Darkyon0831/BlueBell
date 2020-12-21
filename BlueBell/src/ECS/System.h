#ifndef __BB_SYSTEM_H__
#define __BB_SYSTEM_H__

namespace BlueBell
{
	class BB_API System
	{
	public:
		System() {}
		virtual ~System() {}

		virtual void PreStart() {}
		virtual void Start() {}
		virtual void PostStart() {}

		virtual void PreUpdate() {}
		virtual void Update() {}
		virtual void PostUpdate() {}
	};
}

#endif // !__BB_SYSTEM_H__
