#include "SceneManager.h"

namespace BlueBell
{
	SceneManager::SceneManager()
		: m_scenes(4, BlueBerry()->GetAllocator())
		, m_pActiveScene(nullptr)
	{

	}

	SceneManager::~SceneManager()
	{
		for (auto it = m_scenes.Begin(); it != m_scenes.End(); it++)
			BlueBerry()->Deallocate(*it); 
	}

	Scene* SceneManager::CreateScene(const char* name)
	{
		Scene* pScene = BlueBerry()->Allocate<Scene>(name);
		m_scenes.PushBack(pScene);

		return pScene; 
	}

	Scene* SceneManager::GetScene(const char* name)
	{
		int index = 0;
		bool found = false;

		Scene* pScene = nullptr;

		while (found == false && index != m_scenes.GetSize() - 1)
		{
			Scene* pScene = m_scenes.At(index);

			if (std::strcmp(name, pScene->GetName()) == 0)
				found = true;
			else
				index++;
		}

		return pScene;
	}

	void SceneManager::SetActiveScene(const char* name)
	{
		Scene* pScene = GetScene(name);
		m_pActiveScene = pScene;
	}

	void SceneManager::SetActiveScene(Scene* pScene)
	{
		m_pActiveScene = pScene;
	}
}