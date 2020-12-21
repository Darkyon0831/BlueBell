#ifndef __BB_MESH_H__
#define __BB_MESH_H__

#include "Asset.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "Memory/RefPtr.h"

namespace BlueBell 
{
	class Mesh : public Asset
	{
	public:

		Mesh(void*& rVertices, const int& rVerticesSize, void*& rIndicies, const int& rIndiciesSize);
		Mesh(void*& rVertices, const int& rVerticesSize, const int& rIndiciesSize);
		Mesh(const int& rVerticesSize, void*& rIndicies, const int& rIndiciesSize);
		Mesh(const int& rVerticesSize, const int& rIndiciesSize);

		void SetVertices(void*& rVertices, const int& rSize);
		void SetIndicies(void*& rIndicies, const int& rSize);

	private:
		VertexBuffer* m_pVertexBuffer;
		IndexBuffer* m_pIndexBuffer;
	};
}

#endif
