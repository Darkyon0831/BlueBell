#ifndef __BFBX_POLYGON_H__
#define __BFBX_POLYGON_H__

#include "Vectors.h"
#include "LinearAllocator.h"
#include "IAllocator.h"

namespace BlueFBX
{
	class Polygon
	{
	public:

		Polygon(size_t memberCount, BlueBell::IAllocator* pParentAllocator);

		void SetIndex(int id, int index);
		void SetNormal(int id, Vector3D normal);
		void SetColor(int id, Vector4D color);
		void SetTangent(int id, Vector3D tangent);
		void SetBinormal(int id, Vector3D binormal);

		int GetIndex(int id);
		Vector3D GetNormal(int id);
		Vector4D GetColor(int id);
		Vector3D GetTanget(int id);
		Vector3D GetBinormal(int id);

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
