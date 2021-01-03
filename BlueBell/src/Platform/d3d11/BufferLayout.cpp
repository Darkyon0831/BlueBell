#include "BufferLayout.h"

#include "../../Core/BlueBerry.h"
#include "Device.h"

namespace BlueBell
{
	BufferLayout::BufferLayout()
		: m_variables(0, BlueBerry()->GetAllocator())
		, m_stride(0)
		, m_pInputLayout(nullptr)
	{
	}

	BufferLayout::BufferLayout(const std::initializer_list<Variable>& variables, Shader& rShader)
		: m_variables(variables, BlueBerry()->GetAllocator())
		, m_stride(0)
		, m_pInputLayout()
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		size_t size = BlueBerry()->GetAllocator()->GetHeaderSize(m_variables.GetAllocator().GetBlock());

		size_t offset = 0;
		size_t stride = 0;

		int i = 0;

		D3D11_INPUT_ELEMENT_DESC* pElementDesc = BlueBerry()->AllocateArray<D3D11_INPUT_ELEMENT_DESC>(m_variables.GetSize());

		for (auto it = m_variables.Begin(); it != m_variables.End(); it++)
		{
			it->size = GetVariableSize(it->dataType);
			stride += it->size;
			it->offset = offset;
			offset += it->size;

			pElementDesc[i].SemanticName = it->name;
			pElementDesc[i].SemanticIndex = 0;
			pElementDesc[i].Format = GetD3D11DataType(it->dataType);
			pElementDesc[i].InputSlot = 0;
			pElementDesc[i].AlignedByteOffset = it->offset;
			pElementDesc[i].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			pElementDesc[i].InstanceDataStepRate = 0;

			i++;
		}

		m_stride = stride;

		ID3D10Blob* pVertexBlob = rShader.GetVSBlob();

		HRESULT hr = pDevice->CreateInputLayout(pElementDesc, m_variables.GetSize(), pVertexBlob->GetBufferPointer(), pVertexBlob->GetBufferSize(), &m_pInputLayout);

		BlueBerry()->Deallocate(pElementDesc);
		BB_CHECK_HR(hr, "Could not create input layout");
	}

	BufferLayout::BufferLayout(const Vector<Variable>& variables, Shader& rShader)
		: m_variables(variables, BlueBerry()->GetAllocator())
		, m_stride(0)
		, m_pInputLayout(nullptr)
	{
		ID3D11Device* pDevice = Device::GetInstance()->GetDevice();

		size_t size = BlueBerry()->GetAllocator()->GetHeaderSize(m_variables.GetAllocator().GetBlock());

		size_t offset = 0;
		size_t stride = 0;

		int i = 0;

		D3D11_INPUT_ELEMENT_DESC* pElementDesc = BlueBerry()->AllocateArray<D3D11_INPUT_ELEMENT_DESC>(m_variables.GetSize());

		for (auto it = m_variables.Begin(); it != m_variables.End(); it++)
		{
			it->size = GetVariableSize(it->dataType);
			stride += it->size;
			it->offset = offset;
			offset += it->size;

			pElementDesc[i].SemanticName = it->name;
			pElementDesc[i].SemanticIndex = 0;
			pElementDesc[i].Format = GetD3D11DataType(it->dataType);
			pElementDesc[i].InputSlot = 0;
			pElementDesc[i].AlignedByteOffset = it->offset;
			pElementDesc[i].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			pElementDesc[i].InstanceDataStepRate = 0;

			i++;
		}

		m_stride = stride;

		ID3D10Blob* pVertexBlob = rShader.GetVSBlob();

		HRESULT hr = pDevice->CreateInputLayout(pElementDesc, m_variables.GetSize(), pVertexBlob->GetBufferPointer(), pVertexBlob->GetBufferSize(), &m_pInputLayout);

		BlueBerry()->Deallocate(pElementDesc);
		BB_CHECK_HR(hr, "Could not create input layout");
	}

	BufferLayout::~BufferLayout()
	{
		m_pInputLayout->Release();
	}

	BufferLayout& BufferLayout::operator=(const BufferLayout & rBufferLayout)
	{
		m_stride = rBufferLayout.m_stride;
		m_variables = rBufferLayout.m_variables;
		m_pInputLayout = rBufferLayout.m_pInputLayout;
		m_pInputLayout->AddRef();

		return *this;
	}

	BufferLayout::BufferLayout(const BufferLayout& rBufferLayout)
	{
		m_stride = rBufferLayout.m_stride;
		m_variables = rBufferLayout.m_variables;
		m_pInputLayout = rBufferLayout.m_pInputLayout;
		m_pInputLayout->AddRef();
	}

	void BufferLayout::Bind()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		pDeviceContext->IASetInputLayout(m_pInputLayout);
	}
}
