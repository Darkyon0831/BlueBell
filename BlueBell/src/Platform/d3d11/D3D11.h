#ifndef __BB_D3D11_H__
#define __BB_D3D11_H__

#include "SwapChain.h"
#include "Device.h"
#include "Assets/Texture.h"
#include "Assets/Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

#include "../../Math/Vector3D.h"
#include "../../Math/Vector4D.h"
#include "../../Math/Matrix.h"

namespace BlueBell
{
	class D3D11
	{
	public:

		D3D11();
		~D3D11();

		struct ModelViewProjection
		{
			Matrix model;
			Matrix view;
			Matrix projection;
		};

		struct Vertex
		{
			Vector3D position;
			Vector4D color;
		};

		void InitSwapChain(HWND& windowHandle);

		void Clear();

		void Render();

		void Present();

	private:
		SwapChain* m_pSwapChain;

		D3D11_VIEWPORT m_viewPort;
		ID3D11RenderTargetView* m_pRenderTargetView;

		#ifdef DEBUG
			ID3D11Debug* m_pD3D11DebugHandle;
		#endif // DEBUG

		Shader m_shader;
		ID3D11RasterizerState* m_pRasterizerState;

		VertexBuffer* m_pVertexBuffer;
		IndexBuffer* m_pIndexBuffer;
		ConstantBuffer* m_pConstantBuffer;
	};
}

#endif // !__BB_D3D11_H__
