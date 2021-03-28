#include "VertexBuffer.h"

#include "Device.h"

BlueBell::VertexBuffer::VertexBuffer(void* pVertexData, size_t size)
	: m_bufferLayout()
{
	ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = pVertexData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, &data, &m_pVertexBuffer);

	BB_CHECK_HR(hr, "Could not create vertex buffer");
}

BlueBell::VertexBuffer::VertexBuffer(size_t size)
{
	ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	BB_CHECK_HR(pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pVertexBuffer), "Could not create vertex buffer");
}

BlueBell::VertexBuffer::~VertexBuffer()
{
	m_pVertexBuffer->Release();
}

void BlueBell::VertexBuffer::SetInputLayout(const BufferLayout& bufferLayout)
{
	m_bufferLayout = bufferLayout;
}

void BlueBell::VertexBuffer::SetVerticies(void* pVerticies, size_t size)
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

	memcpy(mappedSubresource.pData, pVerticies, size);

	pDeviceContext->Unmap(m_pVertexBuffer, 0);
}

void BlueBell::VertexBuffer::Bind()
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

	const size_t& stride = m_bufferLayout.GetStride();
	const size_t offset = 0;

	m_bufferLayout.Bind();
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
}
