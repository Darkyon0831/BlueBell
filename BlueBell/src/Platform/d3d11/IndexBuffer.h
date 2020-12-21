#ifndef __BB_INDEXBUFFER_H__
#define __BB_INDEXBUFFER_H__

#include <d3d11.h>

namespace BlueBell 
{
	class IndexBuffer
	{
	public:

		IndexBuffer(int* pIndicies, size_t size);
		IndexBuffer(size_t size);

		void SetIndicies(int* pIndicies, size_t size);

		~IndexBuffer();

		void Bind();

	private:
		ID3D11Buffer* m_pIndexBuffer;
	};
}

#endif
