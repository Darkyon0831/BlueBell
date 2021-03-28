#ifndef __BB_STACKPTR_H__
#define __BB_STACKPTR_H__

#include "../Core/BlueBerry.h"

namespace BlueBell
{
	template<typename T>
	class StackPtr
	{
	public:

		~StackPtr();

		template<typename... Args>
		StackPtr(Args... args);

		StackPtr(StackPtr& rStackPtr);

		StackPtr& operator=(StackPtr& rStackPtr);
		void operator=(const T& t);
		T* operator->();
		T& operator*();

		void Transfare(StackPtr& rStackPtr);

		T* Get() { return m_pMem; }

	private:
		T* m_pMem;
	};

	template<typename T>
	inline StackPtr<T>::~StackPtr()
	{
		if (m_pMem != nullptr)
			BlueBerry()->Deallocate(m_pMem);
	}

	template<typename T>
	inline StackPtr<T>::StackPtr(StackPtr& rStackPtr)
	{
		m_pMem = rStackPtr.m_pMem;
		rStackPtr.m_pMem = nullptr;
	}

	template<typename T>
	inline StackPtr<T>& StackPtr<T>::operator=(StackPtr& rStackPtr)
	{
		m_pMem = rStackPtr.m_pMem;
		rStackPtr.m_pMem = nullptr;
	}

	template<typename T>
	inline void StackPtr<T>::operator=(const T& t)
	{
		*m_pMem = t;
	}

	template<typename T>
	inline T* StackPtr<T>::operator->()
	{
		return m_pMem;
	}

	template<typename T>
	inline T& StackPtr<T>::operator*()
	{
		return *m_pMem;
	}

	template<typename T>
	inline void StackPtr<T>::Transfare(StackPtr& rStackPtr)
	{
		m_pMem = rStackPtr.m_pMem;
		rStackPtr.m_pMem = nullptr;
	}

	template<typename T>
	template<typename ...Args>
	inline StackPtr<T>::StackPtr(Args ...args)
	{
		m_pMem = BlueBerry()->Allocate<T>(std::forward<Args>(args)...);
	}
}

#endif // !__BB_STACKPTR_H__
