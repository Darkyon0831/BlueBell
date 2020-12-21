#include "SwapChain.h"

#include "../../Logging/Logger.h"
#include "Device.h"

namespace BlueBell
{
	SwapChain::SwapChain()
	{
		
	}

	SwapChain::~SwapChain()
	{
		m_pSwapChain->Release();
	}

	void SwapChain::Init(HWND& windowHandle)
	{
		IDXGIFactory* pFactory;

		BB_CHECK_HR(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory)), "Could not create DXGI factory");
		DXGI_SWAP_CHAIN_DESC swap;

		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();
		IDXGIDevice* pDxgiDevice;
	
		BB_CHECK_HR(pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDxgiDevice)), "Could not query interface");

		RECT rect;
		GetClientRect(windowHandle, &rect);

		ZeroMemory(&swap, sizeof(DXGI_SWAP_CHAIN_DESC));
		swap.BufferCount = 1;
		swap.OutputWindow = windowHandle;
		swap.Windowed = true;
		swap.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
		swap.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap.BufferDesc.Width = rect.right - rect.left;
		swap.BufferDesc.Height = rect.bottom - rect.top;
		swap.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap.SampleDesc.Count = 1;

		BB_CHECK_HR(pFactory->CreateSwapChain(pDxgiDevice, &swap, &m_pSwapChain), "Could not create swap chain");

		pFactory->Release();
		pDxgiDevice->Release();
		//pDevice->Release();
	}

	ID3D11Resource* SwapChain::GetBackBuffer()
	{
		ID3D11Resource* backbuffer;
		BB_CHECK_HR(m_pSwapChain->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer), "Could not get back buffer from the swap chain");

		return backbuffer;

		int i = 0;
	}

	void SwapChain::Present(UINT syncInterval, UINT flags)
	{
		m_pSwapChain->Present(syncInterval, flags);
	}
}
