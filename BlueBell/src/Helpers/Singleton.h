#ifndef __BB_SINGLETON_H__
#define __BB_SINGLETON_H__

#include "../Core/BlueBerry.h"

#include <typeinfo>

namespace BlueBell
{
	template<typename Single>
	class Singleton
	{
	public:

		template<typename... Args> 
		static void CreateInstance(Args... args);

		static Single* GetInstance();

		static void DeleteInstance();

	private:
		static Single* m_instance(int flag);
	};

	template<typename Single>
	template<typename... Args> 
	inline void Singleton<Single>::CreateInstance(Args... args)
	{
		const type_info& singleType = typeid(Single);

		BB_ASSERT(m_instance(0) == nullptr, "Instance of type {0} have already been initialized", singleType.name());
		m_instance(2);
	}

	template<typename Single>
	inline Single* Singleton<Single>::GetInstance()
	{
		const type_info& singleType = typeid(Single);

		BB_ASSERT(m_instance(0) != nullptr, "Could not get an instance of type {0} that not been initialized", singleType.name())
		return m_instance(0);
	}

	template<typename Single>
	inline void Singleton<Single>::DeleteInstance()
	{
		const type_info& singleType = typeid(Single);

		BB_ASSERT(m_instance(0) != nullptr, "Could not delete an instance of type {0} that not been initialized", singleType.name())
		m_instance(1);
	}

	template<typename Single>
	inline Single* Singleton<Single>::m_instance(int flag)
	{
		static Single* instance = nullptr;

		if (flag == 0)
			return instance;
		else if (flag == 1)
		{
			BlueBerry()->Deallocate(instance);
			return nullptr;
		}
		else if (flag == 2)
		{
			instance = BlueBerry()->Allocate<Single>();
			return nullptr;
		}
	}

}

#endif // !__BB_SINGLETON_H__
