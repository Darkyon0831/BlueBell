#include "Material.h"

#include "Core/BlueBerry.h"
#include "Platform/d3d11/Assets/Shader.h"

#include <vector>

namespace BlueBell
{
	Material::Material(const std::string& rShaderName)
		: m_vertexConstantBufferSize(0)
		, m_pixelConstantBufferSize(0)
		, m_pBufferLayout(nullptr)
		, m_pVertexConstantBuffer(nullptr)
		, m_pPixelConstantBuffer(nullptr)
		, m_pVertexSamplerState(nullptr)
		, m_pPixelSamplerState(nullptr)
		, m_pShader(nullptr)
		, m_properties(0, BlueBerry()->GetAllocator())
		, m_vertexUsedProperties(0, BlueBerry()->GetAllocator())
		, m_pixelUsedProperties(0, BlueBerry()->GetAllocator())
		, m_textures(0, BlueBerry()->GetAllocator())
	{
		m_whiteTexture = BlueBerry()->Allocate<Texture>();
		m_whiteTexture->Load("../../game/textures/White.dds");

		LoadFromStarLab(rShaderName);
	}

	Material::~Material()
	{
		BlueBerry()->Deallocate(m_pBufferLayout);
		BlueBerry()->Deallocate(m_pVertexConstantBuffer);
		//BlueBerry()->Deallocate(m_pPixelConstantBuffer);
		BlueBerry()->Deallocate(m_pShader);
		
		BlueBerry()->Deallocate(m_pVertexCBDataTEMP);
		//BlueBerry()->Deallocate(m_pPixelCBDataTEMP);

		if (m_pVertexSamplerState != nullptr)
			m_pVertexSamplerState->Release();

		if (m_pPixelSamplerState != nullptr)
			m_pPixelSamplerState->Release();
	}

	void Material::SetPropertyValue(const std::string& rName, Value& value)
	{
		Property* pProperty = nullptr;

		for (int i = 0; i < m_properties.GetSize(); i++)
		{
			if (m_properties.At(i).name == rName)
			{
				pProperty = &m_properties.At(i);
				break;
			}
		}

		pProperty->value = value;
	}

	void Material::SetTexture(const std::string& rTextureName, const std::string& texturePath)
	{
		Property* pProperty = nullptr;

		int textureNum = 0;

		for (int i = 0; i < m_properties.GetSize(); i++)
		{
			if (m_properties.At(i).name == rTextureName)
			{
				pProperty = &m_properties.At(i);
				break;
			}

			if (m_properties.At(i).type == Type::MTTexture)
				textureNum++;
		}

		pProperty->texturePath = texturePath;

		Texture* pTexture = m_textures.At(textureNum);

		if (pTexture != m_whiteTexture)
			pTexture->Free();

		pTexture->Load(texturePath);

		int i = 0;
	}

	void Material::SetSamplerStateFromStarLab(const StarLab::SamplerState& samplerState, ID3D11SamplerState** m_pSamplerState)
	{
		D3D11_SAMPLER_DESC sampleDesc;

		sampleDesc.Filter = static_cast<D3D11_FILTER>(samplerState.GetFilter());
		sampleDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(samplerState.GetAddressU());
		sampleDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(samplerState.GetAddressV());
		sampleDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(samplerState.GetAddressW());
		sampleDesc.MipLODBias = samplerState.GetMipLodBias();
		sampleDesc.MaxAnisotropy = samplerState.GetMaxAnisotropy();
		sampleDesc.ComparisonFunc = static_cast<D3D11_COMPARISON_FUNC>(samplerState.GetComparisonFunc());
		sampleDesc.MinLOD = samplerState.GetMinLod();
		sampleDesc.MaxLOD = samplerState.GetMaxLod();

		Device* pDevice = Device::GetInstance();

		HRESULT hr = pDevice->GetDevice()->CreateSamplerState(&sampleDesc, m_pSamplerState);

		BB_CHECK_HR(hr, "Could not create sampler state");
	}

	void Material::LoadFromStarLab(const std::string& rShaderName)
	{
		RefPtr<StarLab::IntermediateRepresentation> starlabIR;

		if (ShaderCache::GetInstance()->CheckCache(rShaderName, starlabIR) == false)
		{
			starlabIR = RefPtr<StarLab::IntermediateRepresentation>();
			ShaderCache::GetInstance()->AddCache(rShaderName, starlabIR);

			std::stringstream filePath;
			filePath << "../../game/shaders/";
			filePath << rShaderName.c_str();
			filePath << ".starlab";

			starlabIR->LoadFromFile(filePath.str());
			starlabIR->CompileAndSaveToFile(StarLab::IntermediateRepresentation::Stage::STVertex, rShaderName);
			starlabIR->CompileAndSaveToFile(StarLab::IntermediateRepresentation::Stage::STPixel, rShaderName);
		}

		const std::vector<StarLab::Value>& rProperties = starlabIR->GetProperties();

		for (int i = 0; i < rProperties.size(); i++)
		{
			Property mProperty = { rProperties.at(i).GetName(), (Material::Type)rProperties.at(i).GetType(), "", 1 };

			if (mProperty.type == Type::MTTexture)
			{
				Texture* pTexture = m_whiteTexture;
				m_textures.PushBack(pTexture);
			}

			m_properties.PushBack(mProperty);
		}

		const std::vector<StarLab::Value>& rUsedVertexProperties = starlabIR->GetVertexShader().GetUsedProperties();

		if (rUsedVertexProperties.size() > 0)
		{
			for (int i = 0; i < rUsedVertexProperties.size(); i++)
			{
				StageProperty mProperty = { rUsedVertexProperties.at(i).GetName(), (Type)rUsedVertexProperties.at(i).GetType() };

				m_vertexUsedProperties.PushBack(mProperty); 

				size_t typeSize = GetTypeSize(mProperty.type);

				int remainder = typeSize % 16;

				if (remainder > 0)
					typeSize = typeSize + 16 - remainder;

				m_vertexConstantBufferSize += typeSize;
			}

			m_pVertexConstantBuffer = BlueBerry()->Allocate<ConstantBuffer>(m_vertexConstantBufferSize);
			m_pVertexCBDataTEMP = BlueBerry()->AllocateArray<char>(m_vertexConstantBufferSize);
		}

		const std::vector<StarLab::Value>& rUsedPixelProperties = starlabIR->GetPixelShader().GetUsedProperties();

		if (rUsedPixelProperties.size() > 0)
		{
			bool doCreate = false;

			for (int i = 0; i < rUsedPixelProperties.size(); i++)
			{
				if (rUsedPixelProperties.at(i).GetType() != StarLab::Type::SLTexture)
				{		
					StageProperty mProperty = { rUsedPixelProperties.at(i).GetName(), (Type)rUsedPixelProperties.at(i).GetType() };

					m_pixelUsedProperties.PushBack(mProperty); 

					size_t typeSize = GetTypeSize(mProperty.type);

					int remainder = typeSize % 16;

					if (remainder > 0)
						typeSize = typeSize + 16 - remainder;

					m_pixelConstantBufferSize += typeSize;

					doCreate = true;
				}
			}

			if (doCreate)
			{
				m_pPixelConstantBuffer = BlueBerry()->Allocate<ConstantBuffer>(m_pixelConstantBufferSize);
				m_pPixelCBDataTEMP = BlueBerry()->AllocateArray<char>(m_pixelConstantBufferSize);
			}
		}

		Vector<BufferLayout::Variable> bufferInitList(starlabIR->GetVertexShader().GetIn().size(), BlueBerry()->GetAllocator());

		const std::vector<StarLab::Value> inValues = starlabIR->GetVertexShader().GetIn();

		for (int i = 0; i < inValues.size(); i++)
		{
			BufferLayout::Variable blVariable = { inValues.at(i).GetSemantic().c_str(), (BufferLayout::VariableDataType)inValues.at(i).GetType() };

			bufferInitList.PushBack(blVariable);
		}

		if (starlabIR->GetPixelShader().GetSamplerState().GetName() != "")
			SetSamplerStateFromStarLab(starlabIR->GetPixelShader().GetSamplerState(), &m_pPixelSamplerState);

		if (starlabIR->GetVertexShader().GetSamplerState().GetName() != "")
			SetSamplerStateFromStarLab(starlabIR->GetVertexShader().GetSamplerState(), &m_pVertexSamplerState);

		std::stringstream vertexFile;
		std::stringstream pixelFile;
		vertexFile << "../../game/shaders/temp/";
		pixelFile << "../../game/shaders/temp/";
		vertexFile << rShaderName.c_str() << "Vertex.hlsl";
		pixelFile << rShaderName.c_str() << "Pixel.hlsl";

		m_pShader = BlueBerry()->Allocate<Shader>();
		m_pShader->Load(vertexFile.str().c_str(), pixelFile.str().c_str());

		int i = 0;

		m_pBufferLayout = BlueBerry()->Allocate<BufferLayout>(bufferInitList, m_pShader);
	}

	void Material::Build()
	{
		int currentOffset = 0;

		if (m_vertexConstantBufferSize > 0)
		{
			for (int i = 0; i < m_vertexUsedProperties.GetSize(); i++)
			{
				StageProperty sProperty = m_vertexUsedProperties.At(i);

				Property* pProperty = nullptr;

				for (int j = 0; j < m_properties.GetSize(); j++)
				{
					Property mProperty = m_properties.At(j);

					if (mProperty.name == sProperty.name)
					{
						pProperty = &mProperty;
						break;
					}
				}

				size_t variableSize = GetTypeSize(sProperty.type);

				memcpy(&m_pVertexCBDataTEMP[currentOffset], &pProperty->value, variableSize);
				currentOffset += variableSize;

				int remainder = currentOffset % 16;

				if (remainder > 0)
					currentOffset = currentOffset + 16 - remainder;
			}

			m_pVertexConstantBuffer->SetData((void*)m_pVertexCBDataTEMP, m_vertexConstantBufferSize);
		}

		if (m_pixelConstantBufferSize > 0)
		{
			currentOffset = 0;

			for (int i = 0; i < m_pixelUsedProperties.GetSize(); i++)
			{
				StageProperty sProperty = m_pixelUsedProperties.At(i);

				Property* pProperty = nullptr;

				for (int j = 0; j < m_properties.GetSize(); j++)
				{
					Property mProperty = m_properties.At(j);

					if (mProperty.name == sProperty.name)
					{
						pProperty = &mProperty;
						break;
					}
				}

				size_t variableSize = GetTypeSize(sProperty.type);

				memcpy(&m_pPixelCBDataTEMP[currentOffset], &pProperty->value, variableSize);
				currentOffset += variableSize;

				int remainder = currentOffset % 16;

				if (remainder > 0)
					currentOffset = currentOffset + 16 - remainder;
			}

			m_pPixelConstantBuffer->SetData((void*)m_pPixelCBDataTEMP, m_pixelConstantBufferSize);
		}
	}

	void Material::Bind()
	{
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance()->GetDeviceContext();

		if (m_vertexConstantBufferSize > 0)
			m_pVertexConstantBuffer->Bind(ConstantBuffer::BindStage::VS);

		if (m_pixelConstantBufferSize > 0)
			m_pPixelConstantBuffer->Bind(ConstantBuffer::BindStage::PS);

		if (m_pPixelSamplerState != nullptr)
			pDeviceContext->PSSetSamplers(0, 1, &m_pPixelSamplerState);

		if (m_pVertexSamplerState != nullptr)
			pDeviceContext->VSSetSamplers(0, 1, &m_pVertexSamplerState);

		if (m_textures.GetSize() > 0)
		{
			ID3D11ShaderResourceView** shaderResourceViews = BlueBerry()->AllocateArray<ID3D11ShaderResourceView*>(m_textures.GetSize());

			for (int i = 0; i < m_textures.GetSize(); i++)
			{
				shaderResourceViews[i] = m_textures.At(i)->GetShaderResourceView();
			}

			pDeviceContext->PSSetShaderResources(0, m_textures.GetSize(), shaderResourceViews);

			BlueBerry()->Deallocate(shaderResourceViews);
		}

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
