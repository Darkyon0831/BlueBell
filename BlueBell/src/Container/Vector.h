#ifndef __BB_VECTOR_H__
#define __BB_VECTOR_H__

#include "../Memory/StackAllocator.h"

#include <utility>

namespace BlueBell
{
	template <typename T>
	class Vector 
	{
	public:
		Vector(const std::initializer_list<T>& elements, IAllocator* pParentAllocator = nullptr);
		Vector(const size_t capacity = 0, IAllocator* pParentAllocator = nullptr); // TODO: remove pParent allocator
		~Vector();

		using iterator = T*;

		T& operator[](int index);

		void operator=(const Vector& rVector);

		/**
		* Gets how many slots this vector have
		**/
		size_t& GetCapacity() { return m_capacity; }

		/**
		* Gets how many elements this vector have
		**/
		size_t& GetSize() { return m_size; }
		const size_t& GetSize() const { return m_size; }

		/**
		* Gets the underlying buffer of the allocator
		**/
		T* GetBuffer() { return reinterpret_cast<T*>(m_stackAllocator.GetBlock()); }

		/**
		* Gets the underlying stack allocator of this vector
		**/
		StackAllocator& GetAllocator() { return m_stackAllocator; }

		/**
		* Preallocates space with new capacity, if already allocated. the element data is copied to the new one.
		*
		* @param newCapacity: new capacity of the vector
		**/
		void Reserve(size_t newCapacity);

		/**
		* Gets the element at the index
		**/
		T& At(int index);

		/**
		* Pushes an new element into the vector to the last 
		*
		* @param t: variable to be added
		**/
		void PushBack(T&& t);

		/**
		* Pushes an new element into the vector to the last 
		*
		* @param t: variable to be added
		**/
		void PushBack(const T& t);

		/**
		* Erases an element at the iterator element
		*
		* @param it: iterator pointing to the element to get removed
		**/
		void Erase(iterator it);

		/**
		* Clears all the element from the vector
		**/
		void Clear();

		/**
		* Shrinks the vector to the elements allocated
		**/
		void ShrinkToFit();

		/**
		* Initializes an new element of type and adds it to the last position of the vector
		*
		* @param args: argument to be forwarded to the type contructor
		**/
		template <typename... Args>
		void EmplaceBack(Args&&... args);

		/**
		* Gets the iterator at the first position
		**/
		iterator Begin();
		const T* Begin() const;

		/**
		* Gets the iterator at the last position
		**/
		iterator End();
		const T* End() const;

	private:
		StackAllocator m_stackAllocator;

		size_t m_capacity;
		size_t m_size;

		template<typename T>
		struct IsPointer { static const bool value = false; };

		template<typename T>
		struct IsPointer<T*> { static const bool value = true; };
	};

	template<typename T>
	inline Vector<T>::Vector(const std::initializer_list<T>& elements, IAllocator* pParentAllocator = nullptr)
		: m_capacity(0)
		, m_size(0)
		, m_stackAllocator(StackAllocator::UseHeader::NotUse, sizeof(T), 0, pParentAllocator)
	{
		Reserve(elements.size());

		for (auto it = elements.begin(); it != elements.end(); it++)
			PushBack(*it);
	}

	template<typename T>
	inline Vector<T>::Vector(const size_t capacity, IAllocator* pParentAllocator)
		: m_capacity(capacity)
		, m_size(0)
		, m_stackAllocator(StackAllocator::UseHeader::NotUse, sizeof(T), capacity * sizeof(T), pParentAllocator)
	{
		int i = 0;
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		Clear();
	}

	template<typename T>
	inline T& Vector<T>::operator[](int index)
	{
		return At(index);
	}

	template<typename T>
	inline void Vector<T>::operator=(const Vector& rVector)
	{
		Clear();
		m_stackAllocator.Free();
		m_size = 0;
		m_capacity = 0;

		Reserve(rVector.GetSize());

		for (auto it = rVector.Begin(); it != rVector.End(); it++)
		{
			this->PushBack(*it);
		}
	}

	template<typename T>
	inline T& Vector<T>::At(int index)
	{
		BB_ASSERT(index >= 0 && index < m_size, "Index out of range of vector");
		
		char* pBlock = m_stackAllocator.GetBlock();
		
		size_t chunkSize = sizeof(T);

		return *(reinterpret_cast<T*>(pBlock + chunkSize * index)); 
	}

	template<typename T>
	inline void Vector<T>::Erase(iterator it)
	{
		if (reinterpret_cast<size_t>(it) > reinterpret_cast<size_t>(End()))
			return;

		char* block = m_stackAllocator.GetBlock();
		size_t offset = m_stackAllocator.GetOffset();

		void* oldAddress = nullptr;

		if (IsPointer<T>::value == true)
		{
			oldAddress = it;

			m_stackAllocator.Deallocate(&oldAddress);
		}
		else
		{
			oldAddress = reinterpret_cast<void*>(it);
			it->~T();
			m_stackAllocator.Deallocate(reinterpret_cast<void**>(&it));
		}

		if (it != End())
		{
			size_t bytesToCopy = reinterpret_cast<size_t>(block) + offset - ( reinterpret_cast<size_t>(oldAddress) + sizeof(T) );
			memcpy(oldAddress, reinterpret_cast<void*>(reinterpret_cast<size_t>(oldAddress) + sizeof(T)), bytesToCopy);
		}

		m_size--;
	}

	template<typename T>
	inline void Vector<T>::Clear()
	{
		size_t startAddress = reinterpret_cast<size_t>(m_stackAllocator.GetBlock());
		size_t bytesToRemove = m_stackAllocator.GetOffset();

		if (IsPointer<T>::value == false)
		{
			for (unsigned int i = 0; i < m_size; i++)
			{
				size_t varAddress = startAddress + i * sizeof(T);
				T* varPtr = reinterpret_cast<T*>(varAddress);
				varPtr->~T();
			}
		}

		m_size = 0;
		m_stackAllocator.ClearChunk(startAddress, bytesToRemove);

		int i = 0;
	}

	template<typename T>
	inline void Vector<T>::ShrinkToFit()
	{
		m_stackAllocator.AllocateBlock(m_size * sizeof(T), alignof(T));

		m_capacity = m_size;
	}

	template<typename T>
	inline T* Vector<T>::Begin()
	{
		return reinterpret_cast<Vector<T>::iterator>(m_stackAllocator.GetBlock());
	}

	template<typename T>
	inline const T* Vector<T>::Begin() const
	{
		return reinterpret_cast<Vector<T>::iterator>(m_stackAllocator.GetBlock());
	}

	template<typename T>
	inline T* Vector<T>::End()
	{
		return reinterpret_cast<Vector<T>::iterator>(m_stackAllocator.GetBlock() + m_size * sizeof(T));
	}

	template<typename T>
	inline const T* Vector<T>::End() const
	{
		return reinterpret_cast<Vector<T>::iterator>(m_stackAllocator.GetBlock() + m_size * sizeof(T));
	}

	template<typename T>
	inline void Vector<T>::Reserve(size_t newCapacity)
	{
		if (newCapacity > m_capacity)
		{
			m_capacity = newCapacity;
			m_stackAllocator.AllocateBlock(m_capacity * sizeof(T), alignof(T));
		}
	}

	template<typename T>
	inline void Vector<T>::PushBack(T&& t)
	{
		if (m_capacity == m_size)
		{
			if (m_capacity == 0)
				m_capacity = 1;
			else
				m_capacity *= 2;

			m_stackAllocator.AllocateBlock(m_capacity * sizeof(T), alignof(T));
		}

		void* ptr = m_stackAllocator.Allocate(sizeof(t), 1);
		*(T*)ptr = std::move(t);
		m_size += 1;
	}

	template<typename T>
	inline void Vector<T>::PushBack(const T& t)
	{
		if (m_capacity == m_size)
		{
			if (m_capacity == 0)
				m_capacity = 1;
			else
				m_capacity *= 2;

			m_stackAllocator.AllocateBlock(m_capacity * sizeof(T), alignof(T));
		}

		void* ptr = m_stackAllocator.Allocate(sizeof(t), 1);
		*(T*)ptr = t;
		m_size += 1;
	}

	template<typename T>
	template<typename... Args>
	inline void Vector<T>::EmplaceBack(Args&&... args)
	{
		if (IsPointer<T>::value == false)
		{
			if (m_capacity == m_size)
			{
				if (m_capacity == 0)
					m_capacity = 1;
				else
					m_capacity *= 2;

				m_stackAllocator.AllocateBlock(m_capacity * sizeof(T), alignof(T));
			}

			void* ptr = m_stackAllocator.Allocate(sizeof(T), 1);
			new(ptr) T(std::forward<Args>(args)...);
			m_size += 1;
		}
	}
}

#endif // !__BB_VECTOR_H__
