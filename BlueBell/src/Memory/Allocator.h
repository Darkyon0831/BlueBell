#ifndef __BB_ALLOCATOR_H__
#define __BB_ALLOCATOR_H__

#include "../Core/Core.h"
#include "IAllocator.h"
#include "MemoryProfiler.h"

#include <type_traits>

namespace BlueBell
{
	template<typename _IAllocator>
	class Allocator
	{
		BB_STATIC_ASSERT(std::is_base_of<IAllocator, _IAllocator>::value, "template variable allocator must derive from IAllocator!");
		BB_STATIC_ASSERT(std::is_pointer<_IAllocator>::value == false, "template variable allocator cannot be an pointer");

	public:

		/**
		* @param args: arguments to allocate the raw allocator with
		**/
		template <typename... Args>
		Allocator(Args... args);
		virtual ~Allocator();

		inline void EnableProfiler() { m_profiling = true; }
		inline void DisableProfiler() { m_profiling = false; }

		/**
		* Allocate an new variable of type and forwars args to the type constructor
		*
		* @param args: arguments to be forwarded to the type constructor
		**/
		template <typename Type, typename... Args>
		Type* Allocate(Args... args);

		/**
		* Allocate an new array of type
		*
		* @param size: number of elements of array
		**/
		template <typename Type>
		Type* AllocateArray(size_t size);

		/**
		* Deallocates variable with type
		*
		* @param pType: The variable to be deallocated
		**/
		template <typename Type>
		void Deallocate(Type*& pType);

		int GetIntValueOfMemory(const void* memory, size_t size);

		/**
		* Gets the underlying raw allocator of this object allocator
		**/
		_IAllocator* GetAllocator() { return m_allocator; }

	private:
		_IAllocator* m_allocator;
		bool m_profiling;

		#ifdef DEBUG
		MemoryProfiler profiler;
		#endif // DEBUG


		template<typename type>
		struct IsPointer { static const bool value = false; };

		template<typename type>
		struct IsPointer<type*> { static const bool value = true; };
	};

#endif // !__BB_ALLOCATOR_H__

	template<typename _IAllocator>
	template<typename... Args>
	inline Allocator<_IAllocator>::Allocator(Args... args)
		: m_profiling(false)
		, m_allocator(new _IAllocator(std::forward<Args>(args)...))
	{

	}

	template<typename _IAllocator>
	inline Allocator<_IAllocator>::~Allocator()
	{
		#ifdef DEBUG
		if (m_profiling)
		{
			profiler.Profile("../../game/fileoutputs/MemoryProfiler.txt");
			m_allocator->DebugMemory();
		}
		#endif // DEBUG

		delete m_allocator;
	}

	template<typename _IAllocator>
	inline int Allocator<_IAllocator>::GetIntValueOfMemory(const void* memory, size_t size)
	{
		int value = 0;

		for (int i = 0; i < size; i++)
		{
			char addressChar = (reinterpret_cast<const char*>(memory))[i];

			value += (int)addressChar;
		}

		return value;
	}

	template<typename _IAllocator>
	template <typename Type, typename... Args>
	inline Type* Allocator<_IAllocator>::Allocate(Args... args)
	{		
		BB_LOG_INFO("Allocated type: {0}", typeid(Type).name());

		BB_STATIC_ASSERT(std::is_pointer<Type>::value == false, "template variable Type cannot be an pointer")

		Type* ptr = reinterpret_cast<Type*>(m_allocator->Allocate(sizeof(Type), alignof(Type)));

		#ifdef DEBUG
		if (m_profiling)
			profiler.Add(sizeof(Type), reinterpret_cast<void*>(ptr), typeid(Type).name());
		#endif // DEBUG

		if (ptr == nullptr)
			int i = 0;

		new(ptr) Type(args...);

		return ptr;
	}

	template<typename _IAllocator>
	template<typename Type>
	inline Type* Allocator<_IAllocator>::AllocateArray(size_t size)
	{
		BB_LOG_INFO("Allocated array type: {0}", typeid(Type).name());

		BB_STATIC_ASSERT(std::is_pointer<Type>::value == false, "template variable Type cannot be an pointer")

		Type* ptr = reinterpret_cast<Type*>(m_allocator->Allocate(sizeof(Type) * size, alignof(Type)));

		#ifdef DEBUG
		if (m_profiling)
			profiler.Add(sizeof(Type) * size, reinterpret_cast<void*>(ptr), typeid(Type).name());
		#endif // DEBUG

		return ptr;
	}

	template<typename _IAllocator>
	template<typename Type>
	inline void Allocator<_IAllocator>::Deallocate(Type*& pType)
	{
		BB_LOG_INFO("Deallocated type: {0}", typeid(Type).name());

		BB_STATIC_ASSERT(std::is_pointer<Type>::value == false, "template variable Type cannot be an pointer")

		#ifdef DEBUG
		if (m_profiling)
			profiler.Remove(reinterpret_cast<void*>(pType));
		#endif // DEBUG

		pType->~Type();
		m_allocator->Deallocate(reinterpret_cast<void**>(&pType));

		pType = nullptr;
	}
}

