#ifndef	__BB_IMGUIRENDERER_H__
#define __BB_IMGUIRENDERER_H__

#include <Windows.h>

#include "examples/imgui_impl_dx11.h"
#include "examples/imgui_impl_win32.h"
#include "../Platform/d3d11/Device.h"
#include "../Events/EventManager.h"

namespace BlueBell
{
	class ImGuiRenderer
	{
	public:

		ImGuiRenderer();
		~ImGuiRenderer();

		void Init(HWND windowHandle, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

		void Render(const float& deltaTime);

	private: 
		void Begin();
		void End();
	};
}

#endif // !__BB_IMGUIRENDERER_H__
