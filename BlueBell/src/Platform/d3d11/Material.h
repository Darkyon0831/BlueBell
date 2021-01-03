#ifndef __BB_MATERIAL_H__
#define __BB_MATERIAL_H__

#include "BufferLayout.h"
#include "ConstantBuffer.h"

#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Matrix.h"

#include "IntermediateRepresentation/IntermediateRepresentation.h"

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
			MTFloat4x4
		};

		struct Property
		{
			std::string name;
			Type type;
			Value value;
		};

		struct StageProperty
		{
			std::string name;
			Type type;
		};

		Material();

		void SetPropertyValue(const std::string& rName, Value& value);

		void LoadFromStarLab(const StarLab::IntermediateRepresentation& rIr);

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

		std::vector<Property> m_properties;
		std::vector<StageProperty> m_vertexUsedProperties;
		std::vector<StageProperty> m_pixelUsedProperties;

		BufferLayout* m_pBufferLayout;
		ConstantBuffer* m_pVertexConstantBuffer;
		ConstantBuffer* m_pPixelConstantBuffer;
		Shader* m_pShader;
	};
}

#endif // !__BB_MATERIAL_H__
