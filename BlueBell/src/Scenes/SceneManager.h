#ifndef __BB_SCENEMANAGER_H__
#define __BB_SCENEMANAGER_H__

#include "../Helpers/Singleton.h"
#include "Scene.h"
#include "../Container/Vector.h"

namespace BlueBell
{
	class SceneManager : public Singleton<SceneManager>
	{
	public:

		SceneManager();
		~SceneManager(); 

		Scene* CreateScene(const char* name);
		Scene* GetScene(const char* name);
		void SetActiveScene(const char* name);
		void SetActiveScene(Scene* pScene);

		Scene* GetActiveScene() { return m_pActiveScene; }
		void StartScenes();
		void UpdateActiveScene();
		
	private:
		Scene* m_pActiveScene;

		Vector<Scene*> m_scenes;
	};
}

#endif // !__BB_SCENEMANAGER_H__
