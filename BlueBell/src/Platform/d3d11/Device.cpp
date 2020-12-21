#include "Device.h"

namespace BlueBell
{
	Device::Device()
	{
		IDXGIFactory* pFactory;
		IDXGIAdapter* pAdapter;
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

		BB_CHECK_HR(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory)), "Could not create DXGI factory");
		BB_CHECK_HR(pFactory->EnumAdapters(0, &pAdapter), "Could not find an adapter");

		BB_CHECK_HR(D3D11CreateDevice(
			nullptr, 
			D3D_DRIVER_TYPE_HARDWARE, 
			nullptr, 
			D3D11_CREATE_DEVICE_DEBUG,
			&featureLevel, 
			1, 
			D3D11_SDK_VERSION, 
			&m_pDevice, 
			nullptr, 
			&m_pDeviceContext),	
			"Could not create D3D11 device and D3D11 device context");

		pFactory->Release();
		pAdapter->Release();
	}

	Device::~Device()
	{
		m_pDevice->Release();
		m_pDeviceContext->Release();
	}
}
