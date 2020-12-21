#ifndef __BB_STACKPTR_H__
#define __BB_STACKPTR_H__

#include "../Core/BlueBerry.h"

namespace BlueBell
{
	template<typename T>
	class StackPtr;

	template<typename T, typename... Args>
	StackPtr<T> MakeStackPtr(Args... args);

	template<typename T>
	class StackPtr
	{
	public:

		StackPtr();
		~StackPtr();

		template<typename U, typename... Args>
		friend StackPtr<U> MakeStackPtr<U>(Args... args);

		StackPtr(StackPtr& rStackPtr);

		StackPtr& operator=(StackPtr& rStackPtr);
		T* operator->();
		T& operator*();

		void Transfare(StackPtr& rStackPtr);

		T* Get() { return m_pMem; }

	private:
		T* m_pMem;
	};

	template<typename T, typename... Args>
	StackPtr<T> MakeStackPtr(Args... args)
	{
		StackPtr<T> stackPtr;
		stackPtr.m_pMem = BlueBerry()->Allocate<T>(std::forward<Args>(args)...);

		return stackPtr;
	}

	template<typename T>
	inline StackPtr<T>::StackPtr()
		: m_pMem(nullptr)
	{
		int i = 0;
	}

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
}

#endif // !__BB_STACKPTR_H__
