#ifndef __BFBX_POLYGON_H__
#define __BFBX_POLYGON_H__

#include "Vectors.h"

#include <Memory/LinearAllocator.h>
#include <Memory/IAllocator.h>

namespace BlueFBX
{
	class Polygon
	{
	public:

		Polygon(size_t memberCount, BlueBell::IAllocator* pParentAllocator);

		void SetIndex(const int& id, const int& index);
		void SetNormal(const int& id, const Vector3D& normal);
		void SetColor(const int& id, const Vector4D& color);
		void SetTangent(const int& id, const Vector3D& tangent);
		void SetBinormal(const int& id, const Vector3D& binormal);

		const int& GetIndex(const int& id);
		const Vector3D& GetNormal(const int& id);
		const Vector4D& GetColor(const int& id);
		const Vector3D& GetTanget(const int& id);
		const Vector3D& GetBinormal(const int& id);

	private:

		int* m_indicies;
		Vector3D* m_normals;
		Vector4D* m_colors;
		Vector3D* m_tangents;
		Vector3D* m_binormals;

		BlueBell::LinearAllocator m_linearAllocator;
		size_t m_memberCount;
	};
}

#endif // !__BFBX_POLYGON_H__
