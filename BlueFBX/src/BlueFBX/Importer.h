#ifndef __BFBX_IMPORTER_H__
#define __BFBX_IMPORTER_H__

#include "DataStructures/Scene.h"

#include <dirent.h>
#include <string>
#include <fbxsdk.h>
#include <Memory/IAllocator.h>
#include <Container/Vector.h>

namespace BlueFBX
{
	class Importer
	{
	public:

		Importer();
		void Import(const std::string& filePath, Scene& scene);

	private: 

		void GetAllTexturesNames(const std::string& filePath, BlueBell::IAllocator* allocator);

		BlueBell::Vector<std::string> m_textureNames;
	};
}

#endif // !__BFBX_IMPORTER_H__
