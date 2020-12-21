#ifndef __BB_SWAPCHAIN_H__
#define __BB_SWAPCHAIN_H__

#include <d3d11.h>

namespace BlueBell
{
	class SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		void Init(HWND& windowHandle);

		ID3D11Resource* GetBackBuffer();

		void Present(UINT syncInterval, UINT flags);

	private:
		IDXGISwapChain* m_pSwapChain;
	};
}

#endif // !__BB_SWAPCHAIN_H__
