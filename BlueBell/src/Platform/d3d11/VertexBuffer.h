#ifndef __BB_VERTEXBUFFER_H__
#define __BB_VERTEXBUFFER_H__

#include <d3d11.h>

#include "../../Logging/Logger.h"
#include "BufferLayout.h"

namespace BlueBell
{
	class VertexBuffer
	{
	public:

		VertexBuffer(void* pVertexData, size_t size);
		VertexBuffer(size_t size);
		~VertexBuffer();

		void SetInputLayout(const BufferLayout& bufferLayout);
		void SetVerticies(void* pVerticies, size_t size);

		void Bind();

	private:

		BufferLayout m_bufferLayout;
		ID3D11Buffer* m_pVertexBuffer;
	};
}

#endif // !__BB_VERTEXBUFFER_H__
