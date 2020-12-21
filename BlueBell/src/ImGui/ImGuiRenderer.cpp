#include "ImGuiRenderer.h"

namespace BlueBell
{
	ImGuiRenderer::ImGuiRenderer()
	{ 
		EventManager::GetInstance()->AddEvent<OnImGuiRenderArgs>();
	}
	
	ImGuiRenderer::~ImGuiRenderer()
	{
		EventManager::GetInstance()->DeleteEvent<OnImGuiRenderArgs>();

		ImGui_ImplDX11_Shutdown();
	    ImGui_ImplWin32_Shutdown();
	    ImGui::DestroyContext();
	}
	
	void ImGuiRenderer::Init(HWND windowHandle, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	{
	    IMGUI_CHECKVERSION();
	    ImGui::CreateContext();
	    ImGuiIO& io = ImGui::GetIO(); (void)io;
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       
	    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         
	    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         
	
	    ImGui::StyleColorsDark();
	
	    ImGuiStyle& style = ImGui::GetStyle();
	    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	    {
	        style.WindowRounding = 0.0f;
	        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	    }
	
		ImGui_ImplWin32_Init(windowHandle);
		ImGui_ImplDX11_Init(pDevice, pDeviceContext);
	}
	
	void ImGuiRenderer::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
	    ImGui::NewFrame();
	}
	
	void ImGuiRenderer::End()
	{
		ImGui::Render();
	    ImGuiIO& io = ImGui::GetIO(); (void)io;
	    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	    {
	        ImGui::UpdatePlatformWindows();
	        ImGui::RenderPlatformWindowsDefault();
	    }
	}
	
	void ImGuiRenderer::Render(const float& deltaTime)
	{ 
		Begin();

		OnImGuiRenderArgs args;
		args.deltaTime = deltaTime;
		EventManager::GetInstance()->TriggerEvent<OnImGuiRenderArgs>(args);

		End();
	}
}
