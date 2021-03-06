#include "D3D11.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scripting/Components/CameraComponent.h"
#include "../../Scripting/GameObject.h"
#include "../../Scripting/Components/TransformComponent.h"

#include <d3d11sdklayers.h>

namespace BlueBell
{
	D3D11::D3D11()
	{
		Device::CreateInstance();

		D3D11_RASTERIZER_DESC rasterDesc;
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.DepthBias = false;
		rasterDesc.DepthBiasClamp = 0;
		rasterDesc.SlopeScaledDepthBias = 0;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.ScissorEnable = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.AntialiasedLineEnable = false;

		m_shader.Load("../../game/shaders/basictriangleVS.hlsl", "../../game/shaders/basictrianglePS.hlsl");

		Vertex vertex[4];
		vertex[0].position = Vector3D(-10.0f, -0.5f, 0.0f);
		vertex[0].color = Vector4D(0.2f, 0.5f, 0.2f, 1.0f);
		
		vertex[1].position = Vector3D(-10.0f, 0.5f, 0.0f);
		vertex[1].color = Vector4D(0.2f, 0.5f, 0.2f, 1.0f);

		vertex[2].position = Vector3D(10.0f, 0.5f, 0.0f);
		vertex[2].color = Vector4D(0.2f, 0.5f, 0.2f, 1.0f);

		vertex[3].position = Vector3D(10.0f, -0.5f, 0.0f);
		vertex[3].color = Vector4D(0.2f, 0.5f, 0.2f, 1.0f);

		int indicies[6];
		indicies[0] = 0;
		indicies[1] = 1;
		indicies[2] = 2;
		indicies[3] = 2;
		indicies[4] = 3;
		indicies[5] = 0;

		BufferLayout layout = BufferLayout(
		{
			{"POSITION", BufferLayout::VariableDataType::Float3},
			{"COLOR", BufferLayout::VariableDataType::Float4}
		}, m_shader);

		m_pVertexBuffer = BlueBerry()->Allocate<VertexBuffer>(vertex, 4 * sizeof(Vertex));
		m_pIndexBuffer = BlueBerry()->Allocate<IndexBuffer>(indicies, 6 * sizeof(int));
		m_pConstantBuffer = BlueBerry()->Allocate<ConstantBuffer>(sizeof(ModelViewProjection));

		m_pVertexBuffer->SetInputLayout(layout);

		BB_CHECK_HR(pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizerState), "Could not create rasterizer state");

		int i = 0;
	}

	D3D11::~D3D11()
	{
		BlueBerry()->Deallocate(m_pSwapChain);
		Device::DeleteInstance();

		BlueBerry()->Deallocate(m_pVertexBuffer);
		BlueBerry()->Deallocate(m_pIndexBuffer);
		BlueBerry()->Deallocate(m_pConstantBuffer);

		m_pRenderTargetView->Release();
		m_pRasterizerState->Release();
		m_pD3D11DebugHandle->Release();
	}

	void D3D11::InitSwapChain(HWND& windowHandle)
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();
		pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_pD3D11DebugHandle));

		m_pSwapChain = BlueBerry()->Allocate<SwapChain>();
		m_pSwapChain->Init(windowHandle);

		RECT rect;
		GetClientRect(windowHandle, &rect);

		m_viewPort.TopLeftX = 0;
		m_viewPort.TopLeftY = 0;
		m_viewPort.Width = 2564;
		m_viewPort.Height = 990;
		m_viewPort.MinDepth = 0;
		m_viewPort.MaxDepth = 1;

		ID3D11Resource* pBackBuffer = m_pSwapChain->GetBackBuffer();

		BB_CHECK_HR(Device::GetInstance()->GetDevice()->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView), "Could not create render target view from back buffer");

		pBackBuffer->Release();
	}

	void D3D11::Clear()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

		float color[4] = { 0, 0, 0, 1 };
		pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, color);
	}

	void D3D11::Render()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();
		Scene* pActiveScene = SceneManager::GetInstance()->GetActiveScene();

		CameraComponent* pCameraComponent = pActiveScene->GetComponentBegin<CameraComponent>();
		pCameraComponent->Begin();
		
		ModelViewProjection modelViewProj;
		modelViewProj.model = Matrix::identity;
		modelViewProj.projection = pCameraComponent->GetProjectionMatrix().Transpose(true);
		modelViewProj.view = pCameraComponent->GetViewMatrix().Transpose(true);

		m_pConstantBuffer->SetData(&modelViewProj, sizeof(modelViewProj));

		unsigned int stride = 4 * sizeof(float);
		unsigned int offset = 0;

		m_pVertexBuffer->Bind();
		m_pIndexBuffer->Bind();
		m_pConstantBuffer->Bind(ConstantBuffer::BindStage::VS);

		m_shader.Bind();

		pDeviceContext->RSSetState(m_pRasterizerState);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pDeviceContext->DrawIndexed(6, 0, 0);
	}

	void D3D11::Present()
	{
		m_pSwapChain->Present(0, 0);
	}
}
