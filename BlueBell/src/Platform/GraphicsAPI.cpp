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
		#ifdef BB_D3D11
			m_pD3D11Handle->InitSwapChain(windowHandle);
		#endif 
	}

	void GraphicsAPI::Clear()
	{
		#ifdef BB_D3D11
			m_pD3D11Handle->Clear();
		#endif 
	}

	void GraphicsAPI::Render()
	{
		#ifdef BB_D3D11
			m_pD3D11Handle->Render();
		#endif 
	}

	void GraphicsAPI::Present()
	{
		#ifdef BB_D3D11
			m_pD3D11Handle->Present();
		#endif 
	}
}
