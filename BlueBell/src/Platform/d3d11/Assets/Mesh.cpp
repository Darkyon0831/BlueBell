#include "Mesh.h"

namespace BlueBell
{
	Mesh::Mesh(void*& rVertices, const int& rVerticesSize, int*& rIndicies, const int& rIndiciesSize)
		: Asset(Asset::Mesh)
		, m_pVertexBuffer(BlueBerry()->Allocate<VertexBuffer>(rVertices, rVerticesSize))
		, m_pIndexBuffer(BlueBerry()->Allocate<IndexBuffer>(rIndicies, rIndiciesSize))
	{

	}

	Mesh::Mesh(void*& rVertices, const int& rVerticesSize, const int& rIndiciesSize)
		: Asset(Asset::Mesh)
		, m_pVertexBuffer(BlueBerry()->Allocate<VertexBuffer>(rVertices, rVerticesSize))
		, m_pIndexBuffer(BlueBerry()->Allocate<IndexBuffer>(rIndiciesSize))
	{

	}

	Mesh::Mesh(const int& rVerticesSize, int*& rIndicies, const int& rIndiciesSize)
		: Asset(Asset::Mesh)
		, m_pVertexBuffer(BlueBerry()->Allocate<VertexBuffer>(rVerticesSize))
		, m_pIndexBuffer(BlueBerry()->Allocate<IndexBuffer>(rIndicies, rIndiciesSize))
	{

	}

	Mesh::Mesh(const int& rVerticesSize, const int& rIndiciesSize)
		: Asset(Asset::Mesh)
		, m_pVertexBuffer(BlueBerry()->Allocate<VertexBuffer>(rVerticesSize))
		, m_pIndexBuffer(BlueBerry()->Allocate<IndexBuffer>(rIndiciesSize))
	{

	}

	void Mesh::SetVertices(void*& rVertices, const int& rSize)
	{
		m_pVertexBuffer->SetVerticies(rVertices, rSize);
	}

	void Mesh::SetIndicies(int*& rIndicies, const int& rSize)
	{
		m_pIndexBuffer->SetIndicies(rIndicies, rSize);
	}

}
