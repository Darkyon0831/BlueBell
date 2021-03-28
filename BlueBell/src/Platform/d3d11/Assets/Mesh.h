#ifndef __BB_MESH_H__
#define __BB_MESH_H__

#include "Asset.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Vector2D.h"

#include "Core/BlueBerry.h"

#include <fbxsdk.h>

namespace BlueBell 
{
	class Mesh : public Asset
	{
	public:

		struct Vertex
		{
			Vector3D position;
			Vector4D color;
			Vector2D uv;
		};

		Mesh(std::string meshFilepath);
		Mesh(void*& rVertices, const int& rVerticesSize, int*& rIndicies, const int& rIndiciesSize);
		Mesh(void*& rVertices, const int& rVerticesSize, const int& rIndiciesSize);
		Mesh(const int& rVerticesSize, int*& rIndicies, const int& rIndiciesSize);
		Mesh(const int& rVerticesSize, const int& rIndiciesSize);

		void SetVertices(void*& rVertices, const int& rSize);
		void SetIndicies(int*& rIndicies, const int& rSize);

		const VertexBuffer* GetVertexBuffer() const { return m_pVertexBuffer; }
		const IndexBuffer* GetIndexBuffer() const { return m_pIndexBuffer; }
		VertexBuffer* GetVertexBuffer() { return m_pVertexBuffer; }
		IndexBuffer* GetIndexBuffer() { return m_pIndexBuffer; }

		void Bind();

	private:

		void InitVertexBuffer(Vertex* verticies, size_t count);
		void InitIndexBuffer(int* indicies, size_t count);

		void LoadFromFBX(const std::string& filePath);

		VertexBuffer* m_pVertexBuffer;
		IndexBuffer* m_pIndexBuffer;
	};
}

#endif
