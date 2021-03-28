#ifndef __BB_MATERIAL_H__
#define __BB_MATERIAL_H__

#include "BufferLayout.h"
#include "ConstantBuffer.h"
#include "Assets/Texture.h"
#include "Memory/RefPtr.h"

#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Matrix.h"
#include "../ShaderCache.h"

#include "IntermediateRepresentation/IntermediateRepresentation.h"
#include "IntermediateRepresentation/SamplerState.h"

namespace BlueBell
{
	class Material
	{
	public:

		union Value
		{
			float vF;
			int vI;
			Vector2D vV2D;
			Vector3D vV3D;
			Vector4D vV4D;
			Matrix vM;
		};

		enum Type
		{
			MTFloat,
			MTFloat2,
			MTFloat3,
			MTFloat4,
			MTInt,
			MTFloat4x4,
			MTTexture
		};

		struct Property
		{
			std::string name;
			Type type;
			std::string texturePath;
			Value value;
		};

		struct StageProperty
		{
			std::string name;
			Type type;
		};

		Material(const std::string& rShaderName);
		~Material();

		void SetPropertyValue(const std::string& rName, Value& value);
		void SetTexture(const std::string& rTextureName, const std::string& texturePath);

		void SetSamplerStateFromStarLab(const StarLab::SamplerState& samplerState, ID3D11SamplerState** m_pSamplerState);

		void LoadFromStarLab(const std::string& rShaderName);

		void Build();
		void Bind();

		const BufferLayout* GetLayout() const { return m_pBufferLayout; }
		const ConstantBuffer* GetVertexConstantBuffer() const { return m_pVertexConstantBuffer; }
		const ConstantBuffer* GetPixelConstantBuffer() const { return m_pPixelConstantBuffer; }
		const Shader* GetShader() const { return m_pShader; }

	private:

		size_t GetTypeSize(const Type& rType);

		int m_vertexConstantBufferSize;
		int m_pixelConstantBufferSize;

		Vector<Property> m_properties;
		Vector<StageProperty> m_vertexUsedProperties;
		Vector<StageProperty> m_pixelUsedProperties;
		Vector<Texture*> m_textures;

		BufferLayout* m_pBufferLayout;
		ConstantBuffer* m_pVertexConstantBuffer;
		ConstantBuffer* m_pPixelConstantBuffer;

		ID3D11SamplerState* m_pVertexSamplerState;
		ID3D11SamplerState* m_pPixelSamplerState;

		Shader* m_pShader;

		Texture* m_whiteTexture;

		char* m_pVertexCBDataTEMP;
		char* m_pPixelCBDataTEMP;
	};
}

#endif // !__BB_MATERIAL_H__
