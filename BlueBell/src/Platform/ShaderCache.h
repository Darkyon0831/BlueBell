#ifndef __BB_SHADERCACHE_H__
#define __BB_SHADERCACHE_H__

#include "Helpers/Singleton.h"
#include "IntermediateRepresentation/IntermediateRepresentation.h"
#include "Memory/RefPtr.h"
#include "Container/Vector.h"

namespace BlueBell
{
	class ShaderCache : public Singleton<ShaderCache>
	{
	public:

		ShaderCache();

	private:

		struct Shader
		{
			Shader(std::string _name, RefPtr<StarLab::IntermediateRepresentation> _ir) : name(_name), ir(_ir) {}

			std::string name;
			RefPtr<StarLab::IntermediateRepresentation> ir;
		};

	public:

		void AddCache(const std::string& name, const RefPtr<StarLab::IntermediateRepresentation>& ir);
		bool CheckCache(const std::string& name, RefPtr<StarLab::IntermediateRepresentation>& ir);

	private:

		Vector<Shader> m_shaderCache;
	};
}

#endif // !__BB_SHADERCACHE_H__
