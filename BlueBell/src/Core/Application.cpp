#include "Application.h"

#include <imgui_memory_editor.h>

namespace BlueBell
{
	Application::Application()
		: m_running(1)
	{
		EventManager::CreateInstance();
		SystemManager::CreateInstance();
		SceneManager::CreateInstance();
		ShaderCache::CreateInstance();
		Clock::CreateInstance();
		Scene* pScene = SceneManager::GetInstance()->CreateScene("DefaultScene");
		SceneManager::GetInstance()->SetActiveScene(pScene);

		m_pGraphicsAPI  = BlueBerry()->Allocate<GraphicsAPI>();

		m_pInput = BlueBerry()->Allocate<Input>();
		m_pImGuiRenderer = BlueBerry()->Allocate<ImGuiRenderer>();
		m_pDeltaTime = BlueBerry()->Allocate<DeltaTime>();

		#ifdef BB_PLATFORM_WINDOWS
		m_pWindow = BlueBerry()->Allocate<Window>();
		m_pWindow->Create();
		m_pWindow->SetInputHandle(m_pInput);
		m_pWindow->InitInput();
		#endif 	

		m_pGraphicsAPI->InitWindows(m_pWindow->GetWindowHandle());

		EventManager::GetInstance()->AddReceiverToEvent<OnWindowClosedArgs>(BB_BIND_FUNC(OnWindowClosed, this));
		EventManager::GetInstance()->AddReceiverToEvent<OnInputArgs>(BB_BIND_FUNC(OnInput, this));
	}

	Application::~Application()
	{
		BlueBerry()->Deallocate(m_pInput);
		BlueBerry()->Deallocate(m_pImGuiRenderer);
		BlueBerry()->Deallocate(m_pWindow);
		BlueBerry()->Deallocate(m_pGraphicsAPI);
		BlueBerry()->Deallocate(m_pDeltaTime);

		Clock::DeleteInstance();
		ShaderCache::DeleteInstance();
		SceneManager::DeleteInstance();
		SystemManager::DeleteInstance();
		EventManager::DeleteInstance();
	}

	void Application::OnWindowClosed(OnWindowClosedArgs& args)
	{
		m_running = 0;
	}

	void Application::Run()
	{
		#ifdef BB_PLATFORM_WINDOWS
		m_pWindow->Show();	
		#endif

		Scene* pScene = SceneManager::GetInstance()->GetActiveScene();

		Device* pDevice = BlueBell::Device::GetInstance();

		SystemManager::GetInstance()->StartSystems();
		m_pImGuiRenderer->Init(m_pWindow->GetWindowHandle(), pDevice->GetDevice(), pDevice->GetDeviceContext());

		RECT rect;
		GetClientRect(m_pWindow->GetWindowHandle(), &rect);

		POINT point;
		point.x = rect.right / 2.0f;
		point.y = rect.bottom / 2.0f;

		ClientToScreen(m_pWindow->GetWindowHandle(), &point);

		while (m_running == 1) 
		{		
			Clock* pClock = Clock::GetInstance();
			pClock->Now();

			m_pDeltaTime->Now();

			pScene->UpdateScene(pClock->GetDeltaTime());

			m_pGraphicsAPI->Clear();	
		
			m_pGraphicsAPI->Render();

			m_pImGuiRenderer->Render(pClock->GetDeltaTime());

			m_pGraphicsAPI->Present();
	
			m_pWindow->HandleMessages();	
		}
	}

	void Application::OnInput(OnInputArgs& args)
	{
		
	}
}