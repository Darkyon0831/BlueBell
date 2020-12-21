#ifndef __BB_ENTITY_H__
#define __BB_ENTITY_H__

#include <utility>
#include "../Core/Core.h"
 
namespace BlueBell
{
	class BB_API Entity
	{
	public:
		Entity() {}
		Entity(unsigned int& uniqueID) : m_id(uniqueID) {} 
		virtual ~Entity() {}

		unsigned int& GetID() { return m_id; };

	protected:
		unsigned int m_id;
	};
}

#endif 
