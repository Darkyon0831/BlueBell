#include "IndexBuffer.h"

#include "Device.h"

namespace BlueBell
{
	IndexBuffer::IndexBuffer(int* pIndicies, size_t size)
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = pIndicies;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		BB_CHECK_HR(pDevice->CreateBuffer(&bufferDesc, &data, &m_pIndexBuffer), "Could not create vertex buffer");

		int i = 0;
	}

	IndexBuffer::IndexBuffer(size_t size)
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		BB_CHECK_HR(pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pIndexBuffer), "Could not create vertex buffer");
	}

	void IndexBuffer::SetIndicies(int* pIndicies, size_t size)
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		pDeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

		memcpy(mappedSubresource.pData, pIndicies, size);

		pDeviceContext->Unmap(m_pIndexBuffer, 0);
	}
	
	IndexBuffer::~IndexBuffer()
	{
		m_pIndexBuffer->Release();
	}

	void IndexBuffer::Bind()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	}
}
