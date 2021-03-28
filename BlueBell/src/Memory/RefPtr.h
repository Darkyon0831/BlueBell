#ifndef __BB_REFPTR_H__
#define __BB_REFPTR_H__

#include "../Core/BlueBerry.h"

namespace BlueBell
{
	template<typename T>
	class RefPtr
	{
	public:

		~RefPtr();

		template<typename... Args>
		RefPtr(Args... args);

		RefPtr(const RefPtr& rRefPtr);


		RefPtr& operator=(const RefPtr& rRefPtr);
		void operator=(const T& t);
		T* operator->();
		T& operator*();

		T* Get();

	private:
		T* m_pMem;
		unsigned int* m_pRefCount;
	};

	template<typename T>
	inline RefPtr<T>::RefPtr(const RefPtr& rRefPtr)
	{
		m_pMem = rRefPtr.m_pMem;
		m_pRefCount = rRefPtr.m_pRefCount;

		(*m_pRefCount)++;
	}

	template<typename T>
	inline RefPtr<T>& RefPtr<T>::operator=(const RefPtr& rRefPtr)
	{
		this->~RefPtr(); 

		m_pMem = rRefPtr.m_pMem;
		m_pRefCount = rRefPtr.m_pRefCount;

		(*m_pRefCount)++;

		return *this;
	}

	template<typename T>
	inline void RefPtr<T>::operator=(const T& t)
	{
		*m_pMem = t;
	}

	template<typename T>
	inline T* RefPtr<T>::operator->()
	{
		return m_pMem;
	}

	template<typename T>
	inline T& RefPtr<T>::operator*()
	{
		return *m_pMem; 
	}

	template<typename T>
	inline T* RefPtr<T>::Get()
	{
		return m_pMem;
	}

	template<typename T>
	inline RefPtr<T>::~RefPtr()
	{
		if (m_pMem != nullptr)
		{
			(*m_pRefCount)--;

			if (*m_pRefCount == 0)
			{
				BlueBerry()->Deallocate(m_pMem);
				BlueBerry()->Deallocate(m_pRefCount);
			}
		}
	}

	template<typename T>
	template<typename ...Args>
	inline RefPtr<T>::RefPtr(Args... args)
	{
		m_pMem = BlueBerry()->Allocate<T>(std::forward<Args>(args)...);
		m_pRefCount = BlueBerry()->Allocate<unsigned int>(1);
	}
}

#endif
