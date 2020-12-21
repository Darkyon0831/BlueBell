#ifndef __BB_GRAPHICSAPI_H__
#define __BB_GRAPHICSAPI_H__

#ifdef BB_D3D11
	#include "d3d11/D3D11.h"
#endif  

namespace BlueBell
{
	class GraphicsAPI
	{
	public:
		GraphicsAPI();
		~GraphicsAPI();

		#ifdef BB_D3D11
		void InitWindows(HWND& windowHandle);
		#endif 

		void Clear();
		void Render();
		void Present();

	private:

	#ifdef BB_D3D11
		D3D11* m_pD3D11Handle;
	#endif 

	};
}

#endif
