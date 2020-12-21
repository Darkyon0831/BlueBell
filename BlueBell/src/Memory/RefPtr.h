#ifndef __BB_REFPTR_H__
#define __BB_REFPTR_H__

#include "../Core/BlueBerry.h"

#include <mutex>

namespace BlueBell
{
	template<typename T>
	class RefPtr;

	template<typename U, typename... Args>
	RefPtr<U> MakeRefPtr(Args... args);

	template<typename T>
	class RefPtr
	{
	public:

		RefPtr();
		~RefPtr();

		template<typename U, typename... Args>
		friend RefPtr<U> MakeRefPtr<U>(Args... args);

		RefPtr(const RefPtr& rRefPtr);

		RefPtr& operator=(const RefPtr& rRefPtr);

		T* Get();

	private:
		T* m_pMem;
		unsigned int* m_pRefCount;

		static std::mutex m_mutex;
	};

	#endif

	template<typename U, typename... Args>
	RefPtr<U> MakeRefPtr(Args... args)
	{
		RefPtr<U> refPtr;
		refPtr.m_pMem = BlueBerry()->Allocate<U>(std::forward<Args>(args)...);
		refPtr.m_pRefCount = BlueBerry()->Allocate<unsigned int>(1);

		return refPtr;
	}

	template<typename T>
	std::mutex RefPtr<T>::m_mutex;

	template<typename T>
	inline RefPtr<T>::RefPtr()
		: m_pMem(nullptr)
		, m_pRefCount(nullptr)
	{
		
	}

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
	inline T* RefPtr<T>::Get()
	{
		return m_pMem;
	}

	template<typename T>
	inline RefPtr<T>::~RefPtr()
	{
		if (m_pMem != nullptr)
		{
			m_mutex.lock();

			(*m_pRefCount)--;

			if (*m_pRefCount == 0)
			{
				BlueBerry()->Deallocate(m_pMem);
				BlueBerry()->Deallocate(m_pRefCount);
			}

			m_mutex.unlock();
		}
	}
}
