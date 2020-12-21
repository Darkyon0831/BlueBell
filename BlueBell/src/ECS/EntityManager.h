#ifndef __BB_ENTITYMANAGER_H__
#define __BB_ENTITYMANAGER_H__

#include "Entity.h"
#include "../Container/Vector.h"
#include "../Core/BlueBerry.h"
#include "../Helpers/Singleton.h"

#define StartEntitySize 64

namespace BlueBell
{
	class BB_API EntityManager
	{
	public:

		EntityManager();
		~EntityManager();

		struct NewEntityArgs
		{
			int entityID;
		};

		Entity& CreateEntity();
		Entity* GetEntity(unsigned int& id);
		void DeleteEntity(unsigned int& id);

 	private:
		unsigned int m_currentID;
		Vector<Entity> m_entites;
	};
}

#endif // !__BB_ENTITYMANAGER_H__
