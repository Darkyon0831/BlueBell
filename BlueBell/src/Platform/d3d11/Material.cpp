#include "Material.h"

#include "Core/BlueBerry.h"
#include "Platform/d3d11/Assets/Shader.h"

#include <vector>

namespace BlueBell
{
	Material::Material()
		: m_vertexConstantBufferSize(0)
		, m_pixelConstantBufferSize(0)
		, m_pBufferLayout(nullptr)
		, m_pVertexConstantBuffer(nullptr)
		, m_pPixelConstantBuffer(nullptr)
		, m_pShader(nullptr)
	{
	}

	Material::~Material()
	{
		BlueBerry()->Deallocate(m_pBufferLayout);
		BlueBerry()->Deallocate(m_pVertexConstantBuffer);
		//BlueBerry()->Deallocate(m_pPixelConstantBuffer);
		BlueBerry()->Deallocate(m_pShader);
		
		BlueBerry()->Deallocate(m_pVertexCBDataTEMP);
		//BlueBerry()->Deallocate(m_pPixelCBDataTEMP);
	}

	void Material::SetPropertyValue(const std::string& rName, Value& value)
	{
		Property* pProperty = nullptr;

		for (int i = 0; i < m_properties.size(); i++)
		{
			if (m_properties.at(i).name == rName)
			{
				pProperty = &m_properties.at(i);
				break;
			}
		}

		pProperty->value = value;
	}

	void Material::LoadFromStarLab(const StarLab::IntermediateRepresentation& rIr)
	{
		const std::vector<StarLab::Value>& rProperties = rIr.GetProperties();

		for (int i = 0; i < rProperties.size(); i++)
		{
			Property mProperty = { rProperties.at(i).GetName(), (Material::Type)rProperties.at(i).GetType(), 1 };

			m_properties.push_back(mProperty);
		}

		const std::vector<StarLab::Value>& rUsedVertexProperties = rIr.GetVertexShader().GetUsedProperties();

		if (rUsedVertexProperties.size() > 0)
		{
			for (int i = 0; i < rUsedVertexProperties.size(); i++)
			{
				StageProperty mProperty = { rUsedVertexProperties.at(i).GetName(), (Type)rUsedVertexProperties.at(i).GetType() };

				m_vertexUsedProperties.push_back(mProperty); 

				m_vertexConstantBufferSize += GetTypeSize(mProperty.type);
			}

			m_pVertexConstantBuffer = BlueBerry()->Allocate<ConstantBuffer>(m_vertexConstantBufferSize);
			m_pVertexCBDataTEMP = BlueBerry()->AllocateArray<char>(m_vertexConstantBufferSize);
		}

		const std::vector<StarLab::Value>& rUsedPixelProperties = rIr.GetPixelShader().GetUsedProperties();

		if (rUsedPixelProperties.size() > 0)
		{
			for (int i = 0; i < rUsedPixelProperties.size(); i++)
			{
				StageProperty mProperty = { rUsedPixelProperties.at(i).GetName(), (Type)rUsedPixelProperties.at(i).GetType() };

				m_pixelUsedProperties.push_back(mProperty); 

				m_pixelConstantBufferSize += GetTypeSize(mProperty.type);
			}

			m_pPixelConstantBuffer = BlueBerry()->Allocate<ConstantBuffer>(m_pixelConstantBufferSize);
			m_pPixelCBDataTEMP = BlueBerry()->AllocateArray<char>(m_pixelConstantBufferSize);
		}

		Vector<BufferLayout::Variable> bufferInitList(rIr.GetVertexShader().GetIn().GetValues().size(), BlueBerry()->GetAllocator());

		const std::vector<StarLab::Value> layoutValues = rIr.GetVertexShader().GetIn().GetValues();

		for (int i = 0; i < layoutValues.size(); i++)
		{
			BufferLayout::Variable blVariable = { layoutValues.at(i).GetSemantic().c_str(), (BufferLayout::VariableDataType)layoutValues.at(i).GetType() };

			bufferInitList.PushBack(blVariable);
		}

		m_pShader = BlueBerry()->Allocate<Shader>();
		m_pShader->Load("../../game/fileoutputs/OutputVertex.hlsl", "../../game/fileoutputs/OutputPixel.hlsl");

		m_pBufferLayout = BlueBerry()->Allocate<BufferLayout>(bufferInitList, m_pShader);

		int i = 0;
	}

	void Material::Build()
	{
		int currentOffset = 0;

		if (m_vertexConstantBufferSize > 0)
		{
			for (int i = 0; i < m_vertexUsedProperties.size(); i++)
			{
				StageProperty sProperty = m_vertexUsedProperties.at(i);

				Property* pProperty = nullptr;

				for (int j = 0; j < m_properties.size(); j++)
				{
					Property mProperty = m_properties.at(j);

					if (mProperty.name == sProperty.name)
					{
						pProperty = &mProperty;
						break;
					}
				}

				size_t variableSize = GetTypeSize(sProperty.type);

				memcpy(&m_pVertexCBDataTEMP[currentOffset], &pProperty->value, variableSize);
				currentOffset += variableSize;
			}

			m_pVertexConstantBuffer->SetData((void*)m_pVertexCBDataTEMP, m_vertexConstantBufferSize);
		}

		if (m_pixelConstantBufferSize > 0)
		{
			currentOffset = 0;

			for (int i = 0; i < m_pixelUsedProperties.size(); i++)
			{
				StageProperty sProperty = m_pixelUsedProperties.at(i);

				Property* pProperty = nullptr;

				for (int j = 0; j < m_properties.size(); j++)
				{
					Property mProperty = m_properties.at(j);

					if (mProperty.name == sProperty.name)
					{
						pProperty = &mProperty;
						break;
					}
				}

				size_t variableSize = GetTypeSize(sProperty.type);

				memcpy(&m_pPixelCBDataTEMP[currentOffset], &pProperty->value, variableSize);
				currentOffset += variableSize;
			}

			m_pPixelConstantBuffer->SetData((void*)m_pPixelCBDataTEMP, m_pixelConstantBufferSize);
		}
	}

	void Material::Bind()
	{
		if (m_vertexConstantBufferSize > 0)
			m_pVertexConstantBuffer->Bind(ConstantBuffer::BindStage::VS);

		if (m_pixelConstantBufferSize > 0)
			m_pPixelConstantBuffer->Bind(ConstantBuffer::BindStage::PS);

		m_pBufferLayout->Bind();
		m_pShader->Bind();
	}

	size_t Material::GetTypeSize(const Type& rType)
	{
		if (rType == MTFloat)
			return 4;
		else if (rType == MTFloat2)
			return 4 * 2;
		else if (rType == MTFloat3)
			return 4 * 3;
		else if (rType == MTFloat4)
			return 4 * 4;
		else if (rType == MTInt)
			return 4;
		else if (rType == MTFloat4x4)
			return 4 * 4 * 4;
		else
			return 0;
	}
}
