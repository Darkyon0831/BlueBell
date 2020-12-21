#ifndef __BB_APPLICATION_H__
#define __BB_APPLICATION_H__

#include "Core.h"
#include "BlueBerry.h"
#include "../Events/EventManager.h"
#include "../Scenes/SceneManager.h"
#include "../ECS/SystemManager.h"
#include "../Input/Input.h"
#include "../ImGui/ImGuiRenderer.h"
#include "../Platform/GraphicsAPI.h"
#include "../Core/DeltaTime.h"
#include "Clock.h"

#ifdef BB_PLATFORM_WINDOWS
#include "../Platform/Windows/Window.h"
#endif

namespace BlueBell
{
	class BB_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void CreateEntities() = 0;

		void OnWindowClosed(OnWindowClosedArgs& args);

		void Run();

		Window* m_pWindow;

		void OnInput(OnInputArgs& args);

	private:

		DeltaTime* m_pDeltaTime;
		GraphicsAPI* m_pGraphicsAPI;
		ImGuiRenderer* m_pImGuiRenderer;
		Input* m_pInput;
		int m_running;
	};

	Application* CreateApplication();
}

#endif // !__BB_APPLICATION_H__