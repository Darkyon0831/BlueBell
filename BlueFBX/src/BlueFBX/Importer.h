#ifndef __BFBX_IMPORTER_H__
#define __BFBX_IMPORTER_H__

#include <string>

#include <fbxsdk.h>

namespace BlueFBX
{
	class Importer
	{
	public:

		void Import(const std::string& filePath);

	private:
	};
}

#endif // !__BFBX_IMPORTER_H__
