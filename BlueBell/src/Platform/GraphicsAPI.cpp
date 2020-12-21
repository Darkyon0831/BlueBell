#include "GraphicsAPI.h"

#include "../Core/BlueBerry.h"

namespace BlueBell
{
	GraphicsAPI::GraphicsAPI()
	{
		#ifdef BB_D3D11
			m_pD3D11Handle = BlueBerry()->Allocate<D3D11>();
		#endif 
	}

	GraphicsAPI::~GraphicsAPI()
	{
		#ifdef BB_D3D11
			BlueBerry()->Deallocate(m_pD3D11Handle);
		#endif 
	}

	void GraphicsAPI::InitWindows(HWND& windowHandle)
	{
		m_pD3D11Handle->InitSwapChain(windowHandle);
	}

	void GraphicsAPI::Clear()
	{
		m_pD3D11Handle->Clear();
	}

	void GraphicsAPI::Render()
	{
		m_pD3D11Handle->Render();
	}

	void GraphicsAPI::Present()
	{
		m_pD3D11Handle->Present();
	}
}
