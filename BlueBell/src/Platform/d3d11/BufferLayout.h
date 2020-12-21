#ifndef __BB_BUFFERLAYOUT_H__
#define __BB_BUFFERLAYOUT_H__

#include "../../Container/Vector.h"
#include "Assets/Shader.h"
#include "../../Memory/RefPtr.h"

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
			Float, Flaot2, Float3, Float4, Int, Int2, Int3, Int4, Bool
		};

		inline size_t GetVariableSize(VariableDataType dataType)
		{
			switch (dataType)
			{
				case BlueBell::BufferLayout::Float:		return 4;
				case BlueBell::BufferLayout::Flaot2:	return 4 * 2;
				case BlueBell::BufferLayout::Float3:	return 4 * 3;
				case BlueBell::BufferLayout::Float4:	return 4 * 4;
				case BlueBell::BufferLayout::Int:		return 4;
				case BlueBell::BufferLayout::Int2:		return 4 * 2;
				case BlueBell::BufferLayout::Int3:		return 4 * 3;
				case BlueBell::BufferLayout::Int4:		return 4 * 4;
				case BlueBell::BufferLayout::Bool:		return 1;
				default:								return 0;
			}
		}

		inline DXGI_FORMAT GetD3D11DataType(VariableDataType dataType)
		{
			switch (dataType)
			{
				case BlueBell::BufferLayout::Float:		return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				case BlueBell::BufferLayout::Flaot2:	return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				case BlueBell::BufferLayout::Float3:	return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				case BlueBell::BufferLayout::Float4:	return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				case BlueBell::BufferLayout::Int:		return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
				case BlueBell::BufferLayout::Int2:		return DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
				case BlueBell::BufferLayout::Int3:		return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
				case BlueBell::BufferLayout::Int4:		return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
				case BlueBell::BufferLayout::Bool:		return DXGI_FORMAT::DXGI_FORMAT_R8_UINT;
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
