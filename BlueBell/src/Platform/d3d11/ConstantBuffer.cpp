#include "ConstantBuffer.h"
#include "Device.h"

namespace BlueBell
{
	BlueBell::ConstantBuffer::ConstantBuffer(void* pMem, size_t size)
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subresourceData;
		subresourceData.pSysMem = pMem;
		subresourceData.SysMemPitch = 0;
		subresourceData.SysMemSlicePitch = 0;

		BB_CHECK_HR(pDevice->CreateBuffer(&bufferDesc, &subresourceData, &m_pBuffer), "Could not create constant buffer");
	}

	ConstantBuffer::ConstantBuffer(size_t size)
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		HRESULT hr = pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pBuffer);

		int i = 0;

		BB_CHECK_HR(hr, "Could not create constant buffer");
	}

	BlueBell::ConstantBuffer::~ConstantBuffer()
	{
		m_pBuffer->Release();
	}

	void ConstantBuffer::SetData(void* pMem, size_t size)
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

		memcpy(mappedSubresource.pData, pMem, size);

		pDeviceContext->Unmap(m_pBuffer, 0);
	}

	void ConstantBuffer::Bind(BindStage bindStage)
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		if (bindStage = BindStage::VS)
			pDeviceContext->VSSetConstantBuffers(0, 1, &m_pBuffer);
		else
			pDeviceContext->PSSetConstantBuffers(0, 1, &m_pBuffer);
	}
}
