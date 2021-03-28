#include "ShaderCache.h"

namespace BlueBell
{
	ShaderCache::ShaderCache()
		: m_shaderCache(0, BlueBerry()->GetAllocator())
	{
	}

	void ShaderCache::AddCache(const std::string& name, const RefPtr<StarLab::IntermediateRepresentation>& ir)
	{
		Shader shader = Shader(name, ir);

		m_shaderCache.PushBack(shader);
	}

	bool ShaderCache::CheckCache(const std::string& name, RefPtr<StarLab::IntermediateRepresentation>& ir)
	{
		for (int i = 0; i < m_shaderCache.GetSize(); i++)
		{
			if (m_shaderCache.At(i).name == name)
			{
				ir = m_shaderCache.At(i).ir;
				return true;
			}
		}

		return false;
	}
}
