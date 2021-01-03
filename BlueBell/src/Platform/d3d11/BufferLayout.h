#ifndef __BB_BUFFERLAYOUT_H__
#define __BB_BUFFERLAYOUT_H__

#include "../../Container/Vector.h"
#include "Assets/Shader.h"

#include <d3d11.h>
#include <initializer_list>
#include <memory>

namespace BlueBell
{
	class BufferLayout
	{
	public:

		enum VariableDataType
		{
			BLFloat, 
			BLFloat2, 
			BLFloat3,
			BLFloat4, 
			BLInt
		};

		inline size_t GetVariableSize(VariableDataType dataType)
		{
			switch (dataType)
			{
				case BlueBell::BufferLayout::BLFloat:	return 4;
				case BlueBell::BufferLayout::BLFloat2:	return 4 * 2;
				case BlueBell::BufferLayout::BLFloat3:	return 4 * 3;
				case BlueBell::BufferLayout::BLFloat4:	return 4 * 4;
				case BlueBell::BufferLayout::BLInt:		return 4;
				default:								return 0;
			}
		}

		inline DXGI_FORMAT GetD3D11DataType(VariableDataType dataType)
		{
			switch (dataType)
			{
				case BlueBell::BufferLayout::BLFloat:		return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				case BlueBell::BufferLayout::BLFloat2:	return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				case BlueBell::BufferLayout::BLFloat3:	return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				case BlueBell::BufferLayout::BLFloat4:	return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				case BlueBell::BufferLayout::BLInt:		return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
				default:								return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
			}
		}

		struct Variable
		{
			Variable(const char* _name, VariableDataType _dataType) : name(_name), dataType(_dataType), size(0), offset(0) {}

			const char* name;
			VariableDataType dataType;
			size_t size;
			size_t offset;
		};

		BufferLayout();
		BufferLayout(const std::initializer_list<Variable>& variables, Shader& rShader);
		BufferLayout(const Vector<Variable>& variables, Shader& rShader);
		BufferLayout(const BufferLayout& rBufferLayout);
		~BufferLayout();

		BufferLayout& operator=(const BufferLayout& rBufferLayout);

		void Bind();

		const size_t& GetStride() const { return m_stride; }

	private:

		Vector<Variable> m_variables;
		ID3D11InputLayout* m_pInputLayout;
		
		size_t m_stride;
	};
}

#endif // !__BB_BUFFERLAYOUT_H__
