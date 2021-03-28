#ifndef __BB_CONSTANTBUFFER_H__
#define __BB_CONSTANTBUFFER_H__

#include <d3d11.h>

namespace BlueBell
{
	// TODO: constant buffer elements must be on an 16 byte alignment

	class ConstantBuffer
	{
	public:

		enum BindStage
		{
			PS,
			VS
		};

		ConstantBuffer(void* pMem, size_t size);
		ConstantBuffer(size_t size);
		~ConstantBuffer();

		void SetData(void* pMem, size_t size);

		void Bind(BindStage bindStage);

	private:
		ID3D11Buffer* m_pBuffer;
		size_t m_size;
	};
}

#endif // !__BB_CONSTANTBUFFER_H__
