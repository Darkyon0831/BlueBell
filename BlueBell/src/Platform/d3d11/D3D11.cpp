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

		rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.DepthBias = false;
		rasterDesc.DepthBiasClamp = 0;
		rasterDesc.SlopeScaledDepthBias = 0;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.ScissorEnable = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.AntialiasedLineEnable = false;

		// Mesh(void*& rVertices, const int& rVerticesSize, int*& rIndicies, const int& rIndiciesSize);

		// Bottom left
		Vertex vertex[4];
		vertex[0].position = Vector3D(-0.5f, -0.5f, 0.0f);
		vertex[0].color = Vector4D(1.0f, 0.0f, 0.0f, 1.0f);
		vertex[0].uv = Vector2D(0.0f, 0.0f);
		
		// Upper left
		vertex[1].position = Vector3D(-0.5f, 0.5f, 0.0f);
		vertex[1].color = Vector4D(0.0f, 1.0f, 0.0f, 1.0f);
		vertex[1].uv = Vector2D(0.0f, 1.0f);

		// Upper right
		vertex[2].position = Vector3D(0.5f, 0.5f, 0.0f);
		vertex[2].color = Vector4D(0.0f, 0.0f, 1.0f, 1.0f);
		vertex[2].uv = Vector2D(1.0f, 1.0f);

		// Bottom right
		vertex[3].position = Vector3D(0.5f, -0.5f, 0.0f);
		vertex[3].color = Vector4D(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[3].uv = Vector2D(1.0f, 0.0f);

		int indicies[6];
		indicies[0] = 0;
		indicies[1] = 1;
		indicies[2] = 2;
		indicies[3] = 2;
		indicies[4] = 3;
		indicies[5] = 0;

		m_pMesh = BlueBerry()->Allocate<Mesh>((void*)vertex, 4, indicies, 6);

		m_pMaterial = BlueBerry()->Allocate<Material>("StarLabTesting");

		m_pMaterial->SetTexture("ColorMap", "../../game/textures/Test4.dds");

		Material::Value ambientStrength = { 0 };
		Material::Value lightColor = { 0 };

		ambientStrength.vF = 1.0f;
		lightColor.vV4D = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);

		m_pMaterial->SetPropertyValue("ambientStrength", ambientStrength);
		m_pMaterial->SetPropertyValue("lightColor", lightColor);

		//m_pMesh->GetVertexBuffer()->SetInputLayout(*m_pMaterial->GetLayout());

		BB_CHECK_HR(pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizerState), "Could not create rasterizer state");

		const ID3D11VertexShader* vertexShader = m_pMaterial->GetShader()->GetVertexShader();

		int value = BlueBerry()->GetIntValueOfMemory(vertexShader, 4);

		int i = 0;
	}

	D3D11::~D3D11()
	{
		BlueBerry()->Deallocate(m_pSwapChain);
		Device::DeleteInstance();

		BlueBerry()->Deallocate(m_pMaterial);

		m_pRenderTargetView->Release();
		m_pRasterizerState->Release();

#ifdef DEBUG
		m_pD3D11DebugHandle->Release();
#endif // DEBUG
	}

	void D3D11::InitSwapChain(HWND& windowHandle)
	{
#ifdef DEBUG
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();
		pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_pD3D11DebugHandle));
#endif // DEBUG

		m_pSwapChain = BlueBerry()->Allocate<SwapChain>();
		m_pSwapChain->Init(windowHandle);

		RECT rect;
		GetClientRect(windowHandle, &rect);

		m_viewPort.TopLeftX = 0;
		m_viewPort.TopLeftY = 0;
		m_viewPort.Width = 1920;
		m_viewPort.Height = 1080;
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

		float color[4] = { 0.25f, 0.25f, 0.25f, 1 };
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

		Material::Value value = { 0 };
		Material::Value value2 = { 0 };
		Material::Value value3 = { 0 };
		value.vM = modelViewProj.model;
		m_pMaterial->SetPropertyValue("modelMatrix", value);

		value2.vM = modelViewProj.view;
		m_pMaterial->SetPropertyValue("viewMatrix", value2);

		value3.vM = modelViewProj.projection;
		m_pMaterial->SetPropertyValue("projectionMatrix", value3);

		m_pMaterial->Build();

		unsigned int stride = 4 * sizeof(float);
		unsigned int offset = 0;

		m_pMesh->Bind();
		
		m_pMaterial->Bind();

		pDeviceContext->RSSetState(m_pRasterizerState);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//pDeviceContext->DrawIndexed(36, 0, 0);
	}

	void D3D11::Present()
	{
		m_pSwapChain->Present(0, 0);
	}
}
